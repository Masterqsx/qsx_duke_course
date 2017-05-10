import to_amazon_pb2
import socket
from google.protobuf.internal.decoder import _DecodeVarint32
from google.protobuf.internal.encoder import _EncodeVarint

def msg_recv(soc):
    n = 1;
    flag = True;
    data = None;
    while n > 0:
      buf = soc.recv(1024);
      if not buf:
        break;
      if flag:
        flag = False;
        msg_len, new_pos = _DecodeVarint32(buf, 0);
        buf = buf[new_pos:];
        n = msg_len - len(buf);
        data = buf;
        continue;
      data += buf;
      n -= len(buf);
    return data;

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
server.connect(('colab-sbx-pvt-25.oit.duke.edu', 12345));
#au = to_amazon_pb2.AU();
#au.flag = 0;
#au.shipid = 0;
#au.whid = 1;
#au.x = 0;
#au.y = 0;
uconnect = ups_pb2.UConnect();
uconnected = ups_pb2.UConnected();

uconnect.reconnectid = wordId;
server.

ucom = ups_pb2.UCommands();
ucom.simspeed = 100000;
deli = ucom.deliveries.add();
deli.truckid = 0;
deli_loc = deli.packages.add();
deli_loc.packageid = -522778490509236461;
deli_loc.x = 888;
deli_loc.y = 888;

msg = ucom.SerializeToString();
_EncodeVarint(server.sendall, len(msg));
server.sendall(msg);
msg_recv(server);
input();
