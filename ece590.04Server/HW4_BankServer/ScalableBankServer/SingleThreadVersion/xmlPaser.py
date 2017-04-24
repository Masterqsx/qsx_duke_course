import xml.etree.ElementTree as ET
import xmlCheck as xc
import psycopg2 as py2
import socket
import struct

class xmlTrans:
    recvData = '';
    tree = '';
    sendData = '';
    conn = None;
    sc = None;
    def __init__(self):
        self.conn = py2.connect(database='bankserver', user='qianshengxin', password='', host='127.0.0.1', port='')
        self.sendData += '<?xml version="1.0" encoding="UTF-8"?>\n<results>';
        print("Opened database successfully")
    
    def __del__(self):
        self.conn.close();
        print("Closed database successfully")

    def reset(self):
        cur = self.conn.cursor();
        cur.execute('delete from bank;');
        cur.execute('delete from transfer;');
        self.conn.commit();
        print("Database reset")

    
    def errMsg(self, msg, ref):
        self.sendData += '\n<error ref=\"' + ref + '\">' + msg + '</error>'; 
    
    def successMsg(self, msg, ref):
        self.sendData += '\n<success ref=\"' + ref + '\">' + msg + '</success>';

    def xmlInit(self, QUE):
        que_tuple = QUE.get()
        QUE.task_done();
        print('receive data');
        self.recvData = que_tuple[1];
        self.sc = que_tuple[0];

    def clean(self):
        self.sc = None;
        self.recvData = '';
        self.sendData = '';

    def xmlParse(self):
        if len(self.recvData) == 0:
            return;
        self.tree = ET.fromstring(self.recvData);
        
        if not xc.rootCheck(self.tree):
            errMsg('transactions tag missing', '');
            return;
        
        if 'reset' in self.tree.attrib and self.tree.attrib['reset'] == 'true':
            self.reset(); 

        for op in self.tree:
            if op.tag == 'create':
                self.createOp(op);
            elif op.tag == 'transfer':
                self.transferOp(op);
            elif op.tag == 'balance':
                self.balanceOp(op);
            elif op.tag == 'query':
                self.queryOp(op);
        
        self.sendData = self.sendData.encode();
        self.sendData = struct.pack('!Q%ds'%(len(self.sendData), ), len(self.sendData), self.sendData);
        
        self.sc.send(self.sendData);
        print('Return to ', self.sc);
        self.sc.close();
        self.clean();

    def createOp(self, root):
# input semantic check
        if not xc.createCheck(root):
            print('err create');
            self.errMsg('Create Invalid Format', '');
            return;

# retrieve info from DOM
        account_id = root.find('account').text;
        balance = '0';
        if root.find('balance') is not None:
            balance = root.find('balance').text;

# check if account exist, make sure one id match one account
        cur = self.conn.cursor();
        cur.execute('select * from bank where account = ' + account_id + ' for update;');
        if len(cur.fetchall()) != 0:
            self.errMsg('Already exists', root.attrib['ref']);
            return;

# create new account
        cur.execute('insert into bank (account, balance) \
                values (' + account_id + ',' + balance + ');');
        self.conn.commit()
        self.successMsg('created', root.attrib['ref']);
        print('Created account ', account_id, ' with balance ', balance);


    def transferOp(self, root):
# input semantic check
        if not xc.transferCheck(root):
            print('err transfer');
            self.errMsg('Transfer Invalid Format','');

# retrieve from DOM
        to_id = root.find('to').text;
        from_id = root.find('from').text;
        amount = float(root.find('amount').text);

# check if account exist
        cur = self.conn.cursor();
        cur.execute('select balance from bank where account = ' + to_id + ' for update;');
        to_amount = cur.fetchone();
        if len(to_amount) == 0:
            self.errMsg('to account does not exist', root.attrib['ref']);
            self.conn.commit();
            return;
        to_amount = float(to_amount[0]);

        cur.execute('select balance from bank where account = ' + from_id + ' for update;');
        from_amount = cur.fetchone();
        if len(from_amount) == 0:
            self.errMsg('from account does not exist', root.attrib['ref']);
            self.conn.commit();
            return;
        from_amount = float(from_amount[0]);

# check the balance meet the transfer
        if amount > 0:
            if from_amount < amount:
                self.errMsg('from account balance is inadequate', root.attrib['ref']);
                self.conn.commit();
                return;
        elif amount < 0:
            if to_amount < -amount:
                self.errMsg('to account balance is inadequate', root.attrib['ref']);
                self.conn.commit();
                return;
        else:
            self.successMsg('transferred', root.attrib['ref']);
            self.conn.commit();
            return;


# update accounts info
        to_amount = to_amount + amount;
        from_amount = from_amount - amount;
        cur.execute('update bank set balance = ' + str(to_amount) + ' where account = ' + to_id + ';');
        cur.execute('update bank set balance = ' + str(from_amount) + ' where account = ' + from_id + ';');
        transfer_insert = 'insert into transfer (transfer_id, transfer_to, transfer_from, transfer_amount, transfer_tag) values (\'' + root.attrib['ref'] + '\', ' + to_id + ', ' + from_id + ', ' + str(amount) + ', \'{';
        flag = 0;
        if root.find('tag') is not None:
            for node in root.findall('tag'):
                if flag == 0:
                    transfer_insert += '\"';
                    flag = 1;
                else:
                    transfer_insert += '\", \"';
                transfer_insert += node.text;
            transfer_insert += '\"';
        transfer_insert += '}\');';
        cur.execute(transfer_insert);
        self.conn.commit();
        self.successMsg('transfered', root.attrib['ref']);
        print('account ', to_id, ' become ', str(to_amount));
        print('account ', from_id, ' become ', str(from_amount));

    def balanceOp(self, root):
# input semantic check
        if not xc.balanceCheck(root):
            print('err balance');
            self.errMsg('Balance Invalid Format', '');
            return; 
# retrieve from DOM
        account_id = root.find('account').text;

# retrieve balance from database
        cur = self.conn.cursor();
        cur.execute('select balance from bank where account = ' + account_id + ';');
        self.successMsg(str(cur.fetchone()[0]), root.attrib['ref']);

    
    def queryParse(self, root):
        res = '';
        logic = ' AND ';
        if root.tag == 'query' or root.tag == 'and':
            res += '(TRUE';
        elif root.tag == 'or':
            res += '(FALSE';
            logic = ' OR ';
        elif root.tag == 'not':
            res += '(NOT (TRUE'
        for child in root:
            if child.tag == 'and' or \
                child.tag == 'or' or \
                child.tag == 'not':
                try:
                    res += (logic + self.queryParse(child));
                except:
                    raise;
            elif child.tag == 'equals':
                res += (logic + '(transfer_' + next(iter(child.attrib)) + ' = ' + child.attrib[next(iter(child.attrib))] + ')');
            elif child.tag == 'greater':
                res += (logic + '(transfer_' + next(iter(child.attrib)) + ' > ' + child.attrib[next(iter(child.attrib))] + ')');
            elif child.tag == 'less':
                res += (logic + '(transfer_' + next(iter(child.attrib)) + ' < ' + child.attrib[next(iter(child.attrib))] + ')');
            elif child.tag == 'tag':
                res += (logic + '(\'' + child.attrib['info'] + '\' = any (transfer_tag))');
            else:
                raise NameError('invalid tag: ' + child.tag);
        res += ')';
        if root.tag == 'not':
            res += ')';
        return res;

    def queryRes(self, root, row):
        self.sendData += '\n<transfer>\n<from>' + str(row[3]) + '</from>\n<to>' + str(row[2]) + '</to>\n<amount>' + str(row[4]) + '</amount>\n<tags>';
        for e in row[5]:
            self.sendData += '<tag>' + e + '</tag>';
        self.sendData += '</tags>\n</transfer>'
        
    def queryOp(self, root):
        cur = self.conn.cursor();
        try:
            cur.execute('select * from transfer where ' + self.queryParse(root));
            rows = cur.fetchall();
            self.sendData += '\n<results ref=\"' + root.attrib['ref'] + '\">';
            for row in rows:
                self.queryRes(root, row);
            self.sendData += '\n</results>';
        except Exception as e:
            print(e);


