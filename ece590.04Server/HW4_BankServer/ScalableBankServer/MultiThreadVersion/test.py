#!/usr/bin/env python3

import xmlParser as xp
import xmlReceiver as xr
import socket
import sys
import struct
import time
import threading
import re
from math import *

class myThread(threading.Thread):
    res = None;
    id = 0;
    def __init__(self, res, id):
        threading.Thread.__init__(self);
        self.res = res;
        self.id = id;
    def run(self):
        try:
            tester(self.res, self.id, 'false');
        except Exception as e:
            print(e);

def tester(res, id, label):
    data = r'<?xml version="1.0" encoding="UTF-8"?><transactions reset="' + label + r'"><create ref="c1"><account>1234</account><balance>500</balance></create><create ref="c2"><account>5678</account></create><create ref="c3"><account>1000</account><balance>500000</balance></create><create ref="c4"><account>1001</account><balance>5000000</balance></create><transfer ref="1"><to>1234</to><from>1000</from><amount>9568.34</amount><tag>paycheck</tag><tag>monthly</tag></transfer><transfer ref="2"><from>1234</from><to>1001</to><amount>100.34</amount><tag>food</tag></transfer><transfer ref="3"><from>1234</from><to>5678</to><amount>345.67</amount><tag>saving</tag></transfer><balance ref="xyz"><account>1234</account></balance><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><not><less amount="100"/></not></query></transactions>';
    data = data.encode();
    data = struct.pack('!Q%ds'%(len(data), ), len(data), data);
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
    
    host = '127.0.0.1';
    if len(sys.argv) > 1:
        host = sys.argv[1];
    port = 12345;
    try:
        start = time.time()
        s.connect((host, port));
        s.sendall(data);
        
        if len(sys.argv) > 2 and sys.argv[2] == 'func':
            print(xr.Receiver(s));
        else:
            xr.Receiver(s);
        if label != 'true':
            res[id] = (time.time() - start);
        s.close();
    except Exception as e:
        print(e);

tester(None, None, 'true');
n = 1;
if len(sys.argv) > 3 and re.match(r'^[1-9][0-9]*$', sys.argv[3]) is not None:
    n = int(sys.argv[3]);
res = [0.0 for i in range(n)];
t = [None for i in range(n)];
for i in range(n):
    t[i] = myThread(res, i);
    t[i].daemon = True;

for i in range(n):
    t[i].start();

for i in range(n):
    t[i].join();

print(fsum(res) / n);



