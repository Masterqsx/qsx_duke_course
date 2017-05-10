import ups_pb2
import to_amazon_pb2
import psycopg2 as py2
import time
from queue import Queue

class ups_handler:
  conn = None;
  def __init__(self):
    self.conn = py2.connect(database='ups', user='postgres', password='passw0rd', host='127.0.0.1', port='');
    print('Open database "ups" successfully');

  def __del__(self):
    if self.conn is not None:
      self.conn.close();
    print("Close connection to database successfully");

  def main_handler(self, QUE1, QUE2):
    while True:
      que_tuple = QUE1.get();
      QUE1.task_done();
      if que_tuple[0] == 0:
        self.world_handler(QUE2, que_tuple[1]);
      elif que_tuple[0] == 1:
        self.amazon_handler(QUE2, que_tuple[1]);
      else:
        print('Wrong tuple in QUE1');
  
  def amain_handler(self, QUE3, QUE4):
    while True:
      que_tuple = QUE3.get();
      QUE3.task_done();
      self.amazon_handler(QUE3, QUE4, que_tuple[1]);

  def wmain_handler(self, QUE1, QUE2):
    while True:
      que_tuple = QUE1.get();
      QUE1.task_done();
      self.world_handler(QUE2, que_tuple[1]);
  
  def make_deliver(self, QUE4, pri):
    cur = self.conn.cursor();
    cur.execute('select d.truck_id, p.ship_id, d.x, d.y, d.package_id from delivery as d, package as p, truck as t where d.package_id = p.package_id and d.truck_id = t.truck_id and t.status = -1 and p.pri = ' + str(pri) + ' and d.status = -1 for update');
    rows = cur.fetchall();
    ucom = ups_pb2.UCommands();
    ucom.simspeed = 100000;
    truck_dict = {};
    for row in rows:
      if row[0] not in truck_dict:
        truck_dict[row[0]] = ucom.deliveries.add();
        truck_dict[row[0]].truckid = row[0];
        cur.execute('update truck set status = 2 where truck_id = ' + str(row[0]) + ';');
      deli_loc = truck_dict[row[0]].packages.add();
      deli_loc.packageid = row[1];
      deli_loc.x = row[2];
      deli_loc.y = row[3];
      cur.execute('update delivery set status = 0 where package_id = ' + str(row[4]) + ';');
      cur.execute('update package set status = 2 where package_id = ' + str(row[4]) + ';');
    self.conn.commit();
    if len(rows) > 0:
      QUE4.put((0, ucom));
      print('from scheduler');
      print(ucom);


  def deliver_scheduler(self, QUE4, wait=5):
    while True:
      time.sleep(wait);
      self.make_deliver(QUE4, 1);
      time.sleep(wait);
      self.make_deliver(QUE4, 0);


  def amazon_handler(self, QUE3, QUE4, au):
    if au.flag == 0:
      cur = self.conn.cursor();
      flag = True;
      rows = None;
      cur.execute('select truck_id from truck where status = -1 for update;');
      rows = cur.fetchall();
      if len(rows) == 0:
        self.conn.commit();
        QUE3.put((1, au)); 
        return
      #while flag:
      #  cur.execute('select truck_id from truck where status = -1 for update;');
      #  rows = cur.fetchall();
      #  if len(rows) != 0:
      #    flag = False;    
      #  self.conn.commit();
      #  time.sleep(1);
      truck_id = rows[0][0];
      package_id = hash(str(au.shipid) + str(truck_id) + str(au.whid));
      user_id = 'None';
      info = 'None';
      if au.HasField('detailofpackage'):
        info = au.detailofpackage;
      if au.HasField('ups_id'):
        user_id = au.ups_id;
      cur.execute('''insert into package (package_id, user_id, info, status, pri, ship_id) 
      values (''' + str(package_id) + ', \'' + user_id + '\', \'' + info + '\', 0, 0, ' + str(au.shipid) + ');');
      cur.execute('''insert into pickup (truck_id, package_id, wh_id, status) 
      values (''' + str(truck_id) + ', ' + str(package_id) + ', ' + str(au.whid) + ', 0);');
      cur.execute('update truck set status = 0 where truck_id = ' + str(truck_id) + ';');
      self.conn.commit();
      ucom = ups_pb2.UCommands();
      ucom.simspeed = 100000;
      pick = ucom.pickups.add();
      pick.truckid = truck_id;
      pick.whid = au.whid;
      QUE4.put((0, ucom));
      print('Successfully receive pack msg from Amazon');
      print('QUE4 in amazon_handler');
      print(QUE4);
    
    elif au.flag == 1 and au.HasField('packageid'):
      cur = self.conn.cursor();
      cur.execute('select truck_id, ship_id from pickup, package where pickup.package_id = package.package_id and package.package_id = ' + str(au.packageid) + ';');
      rows = cur.fetchall();
      if len(rows) > 1:
        print('one package has multiple pickup record');
      if len(rows) == 0:
        print('pickup has no record of package');
      for row in rows:
        truck_id = row[0];
        cur.execute('insert into delivery (truck_id, package_id, x, y, status) values (' + str(truck_id) + ', ' + str(au.packageid) + ', ' + str(au.x) + ', ' + str(au.y) + ', -1);');
        cur.execute('update truck set status = -1 where truck_id = ' + str(truck_id) + ';');
        cur.execute('update package set status = -1 where status = 1 and package_id = ' + str(au.packageid) + ';');
        print('Successfully receive load msg from Amazon');
        self.conn.commit();
        
        
        #ucom = ups_pb2.UCommands();
        #ucom.simspeed = 100000;
        #deli = ucom.deliveries.add();
        #deli.truckid = truck_id;
        #deli_loc = deli.packages.add();
        #deli_loc.packageid = row[1];
        #deli_loc.x = au.x;
        #deli_loc.y = au.y;
        #QUE4.put((0, ucom));
    else:
      print('load msg from Amazon has invalid flag or has not packageid');

  def world_handler(self, QUE2, ures):
    print('The response in world_handler is :');
    print(ures);
    for completion in ures.completions:
      print('World pickuped');
      cur = self.conn.cursor();
      cur.execute('select pickup.truck_id, pickup.package_id, package.ship_id from pickup, package where package.package_id = pickup.package_id and pickup.status = 0 and pickup.truck_id = ' + str(completion.truckid) + ' for update;');
      rows = cur.fetchall();
      if len(rows) > 1:
        print('table "pickup" contains multiple pickup for one truck');
      if len(rows) == 0:
        print(ures);
        print('table "pickup" contains no pickup for one truck');
      #  self.conn.commit();
      #  cur.execute('select delivery.truck_id, delivery.package_id, package.ship_id from delivery, package where package.package_id = delivery.package_id and delivery.status = 0 and delivery.truck_id = ' + str(completion.truckid) + ' for update;');
      #  n_rows = cur.fetchall();
      #  if len(n_rows) > 1:
      #    print('table "delivery" contains multiple delivery for one truck');
      #  if len(n_rows) == 0:
      #    print('talbe "delivery" contains no delivery for one truck');
      #  for n_row in n_rows:
      #    print('Successfully receive delivery complete msg from world');
      #    cur.execute('update package set status = 3 where status = 2 and package_id = ' + str(n_row[1]) + ';');
      #    cur.execute('update delivery set status = 1 where status = 0 and truck_id = ' + str(n_row[0]) + ' and package_id = ' + str(n_row[1]) + ';');


      for row in rows:
        ua = to_amazon_pb2.UA();
        ua.shipid = row[2];
        ua.packageid = row[1];
        ua.truckid = row[0];
        QUE2.put((1, ua));
        print('Successfully receive pickup complete msg from world');
        cur.execute('update package set status = 1 where status = 0 and package_id = ' + str(row[1]) + ';');
        cur.execute('update pickup set status = 1 where status = 0 and truck_id = ' + str(row[0]) + ' and package_id = ' + str(row[1]) + ';');
      if len(rows) > 0:
        cur.execute('update truck set x = ' + str(completion.x) + ', y = ' + str(completion.y) + ', status = 1 where truck_id = ' + str(completion.truckid) + ';');
      else:
        cur.execute('update truck set x = ' + str(completion.x) + ', y = ' + str(completion.y) + ', status = -1 where truck_id = ' + str(completion.truckid) + ';');
      self.conn.commit();

    for deliver in ures.delivered:
      print('World delivered');
      cur = self.conn.cursor();
      cur.execute('select d.truck_id, d.package_id from delivery as d, package as p where d.status = 0 and d.truck_id = ' + str(deliver.truckid) + ' and p.ship_id = ' + str(deliver.packageid) + ' for update;');
      rows = cur.fetchall();
      if len(rows) > 1:
        print('table "delivery" contains multiple deliver for one truck');
      if len(rows) == 0:
        print('table "delivery" contains no deliver for one truck');
      for row in rows:
        cur.execute('update package set status = 3 where status = 2 and package_id = ' + str(row[1]) + ';');
        cur.execute('update delivery set status = 1 where status = 0 and truck_id = ' + str(deliver.truckid) + ' and package_id = ' + str(row[1]) + ' ;');
        print("Successfully receive delivered msg from world")
      self.conn.commit();
