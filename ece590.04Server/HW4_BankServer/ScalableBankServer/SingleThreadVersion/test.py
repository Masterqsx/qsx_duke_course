#!/usr/bin/env python3

import xmlPaser as xp
import xmlReceiver as xr
import socket
import sys
import struct

data = r'<?xml version="1.0" encoding="UTF-8"?><transactions reset="true"><create ref="c1"><account>1234</account><balance>500</balance></create><create ref="c2"><account>5678</account></create><create ref="c3"><account>1000</account><balance>500000</balance></create><create ref="c4"><account>1001</account><balance>5000000</balance></create><transfer ref="1"><to>1234</to><from>1000</from><amount>9568.34</amount><tag>paycheck</tag><tag>monthly</tag></transfer><transfer ref="2"><from>1234</from><to>1001</to><amount>100.34</amount><tag>food</tag></transfer><transfer ref="3"><from>1234</from><to>5678</to><amount>345.67</amount><tag>saving</tag></transfer><balance ref="xyz"><account>1234</account></balance><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><greater amount="100"/><tag info="food"/></query><create ref="c1"><account>1234</account><balance>500</balance></create><create ref="c2"><account>5678</account></create><create ref="c3"><account>1000</account><balance>500000</balance></create><create ref="c4"><account>1001</account><balance>5000000</balance></create><transfer ref="1"><to>1234</to><from>1000</from><amount>9568.34</amount><tag>paycheck</tag><tag>monthly</tag></transfer><transfer ref="2"><from>1234</from><to>1001</to><amount>100.34</amount><tag>food</tag></transfer><transfer ref="3"><from>1234</from><to>5678</to><amount>345.67</amount><tag>saving</tag></transfer><balance ref="xyz"><account>1234</account></balance><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><greater amount="100"/><tag info="food"/></query><create ref="c1"><account>1234</account><balance>500</balance></create><create ref="c2"><account>5678</account></create><create ref="c3"><account>1000</account><balance>500000</balance></create><create ref="c4"><account>1001</account><balance>5000000</balance></create><transfer ref="1"><to>1234</to><from>1000</from><amount>9568.34</amount><tag>paycheck</tag><tag>monthly</tag></transfer><transfer ref="2"><from>1234</from><to>1001</to><amount>100.34</amount><tag>food</tag></transfer><transfer ref="3"><from>1234</from><to>5678</to><amount>345.67</amount><tag>saving</tag></transfer><balance ref="xyz"><account>1234</account></balance><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><greater amount="100"/><tag info="food"/></query><create ref="c1"><account>1234</account><balance>500</balance></create><create ref="c2"><account>5678</account></create><create ref="c3"><account>1000</account><balance>500000</balance></create><create ref="c4"><account>1001</account><balance>5000000</balance></create><transfer ref="1"><to>1234</to><from>1000</from><amount>9568.34</amount><tag>paycheck</tag><tag>monthly</tag></transfer><transfer ref="2"><from>1234</from><to>1001</to><amount>100.34</amount><tag>food</tag></transfer><transfer ref="3"><from>1234</from><to>5678</to><amount>345.67</amount><tag>saving</tag></transfer><balance ref="xyz"><account>1234</account></balance><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><greater amount="100"/><tag info="food"/></query></transactions>';
data = data.encode();
data = struct.pack('!Q%ds'%(len(data), ), len(data), data);
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
host = '127.0.0.1';
port = 12345;
s.connect((host, port));
s.send(data);

print(xr.Receiver(s));
s.close();
