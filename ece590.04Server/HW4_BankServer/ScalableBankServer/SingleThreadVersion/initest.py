#!/usr/bin/env python3

import xmlPaser as xp

trans = xp.xmlTrans();
#trans.recvData = '<?xml version="1.0" encoding="UTF-8"?>\n<transactions reset="true">\n<create ref=\'a0\'>\n<account>1234</account>\n<balance>300</balance>\n</create>\n<create ref=\'a1\'>\n<account>123</account>\n<balance>1.4</balance>\n</create>\n<balance ref=\'a2\'>\n<account>123</account>\n</balance>\n<transfer ref=\'a3\'><to>123</to><tag>food</tag><tag>check</tag><from>1234</from><amount>200.1</amount></transfer><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><greater amount="100"/><tag info="check"/></query></transactions>';
trans.recvData = r'<?xml version="1.0" encoding="UTF-8"?><transactions reset="true"><create ref="c1"><account>1234</account><balance>500</balance></create><create ref="c2"><account>5678</account></create><create ref="c3"><account>1000</account><balance>500000</balance></create><create ref="c4"><account>1001</account><balance>5000000</balance></create><transfer ref="1"><to>1234</to><from>1000</from><amount>9568.34</amount><tag>paycheck</tag><tag>monthly</tag></transfer><transfer ref="2"><from>1234</from><to>1001</to><amount>100.34</amount><tag>food</tag></transfer><transfer ref="3"><from>1234</from><to>5678</to><amount>345.67</amount><tag>saving</tag></transfer><balance ref="xyz"><account>1234</account></balance><query ref="4"><or><equals from="1234"/><equals to="5678"/></or><greater amount="100"/><tag info="food"/></query></transactions>'
trans.xmlParse();
print(trans.sendData);

