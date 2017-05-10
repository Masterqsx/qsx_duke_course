import socket
import ups_pb2
import to_amazon_pb2
import io
from queue import Queue
from google.protobuf.internal.decoder import _DecodeVarint32
from google.protobuf.internal.encoder import _EncodeVarint
from google.protobuf.internal.encoder import _VarintBytes

class ups_connector:
  host = '';
  port = 12345;
  soc = None;
  server = None;  

  def __init__(self, i_host, i_port): #use for connect to world
    self.host = i_host;
    self.port = i_port;
    try:
      if self.host == '':
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
        self.server.bind((self.host, self.port));
        self.server.listen(20);
      else:
        self.soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
        self.soc.connect((self.host, self.port));
    except Exception as e:
      print(e);
      exit();
  
  def __del__(self):
    if self.soc is not None:
      self.soc.close(); 
    if self.server is not None:
      self.server.close();
    print("Close Socket Successfully");

  def connect_to_world(self, wordId):
    uconnect = ups_pb2.UConnect();
    uconnected = ups_pb2.UConnected();

    uconnect.reconnectid = wordId;
    self.msg_send(uconnect);
    uconnected.ParseFromString(self.amsg_recv());
    print(uconnected);

  def connect_to_amazon(self):
    self.soc, addr = self.server.accept();

  def to_world(self, QUE2): #tuple format in queue: [0]: target type 0 -> world, 1 -> amazon [1]: command object
    while True:
      que_tuple = QUE2.get();
      QUE2.task_done();
      print('to_world');
      print(que_tuple[1]);
      self.msg_send(que_tuple[1]);

  def from_world(self, QUE1):
    while True:
      ures = ups_pb2.UResponses();
      ures.ParseFromString(self.amsg_recv());
      print('from_world');
      print(ures);
      QUE1.put((0, ures));

  def to_amazon(self, QUE4):
    while True:
      que_tuple = QUE4.get();
      QUE4.task_done();
      print('to_amazon');
      print(que_tuple[1]);
      self.msg_send(que_tuple[1]);

  def from_amazon(self, QUE3):
    while True:
      au = to_amazon_pb2.AU();
      au.ParseFromString(self.amsg_recv());
      print('from_amazon');
      print(au);
      QUE3.put((1, au));

  #def amsg_send(self, msg):
    
  def msg_send(self, msg):
    _EncodeVarint(self.soc.sendall, msg.ByteSize());
    self.soc.sendall(msg.SerializeToString());

  def amsg_recv(self):
    l = self.soc.recv(1)
    msg_len, new_pos = _DecodeVarint32(l, 0);
    buf = io.BytesIO()
    if new_pos < 4:
      buf.write(l[new_pos:])

    while msg_len > 0:
      b = self.soc.recv(min(8096, msg_len));
      buf.write(b);
      msg_len = msg_len - len(b);
    return buf.getvalue();

  def msg_recv(self):
    n = 1;
    flag = True;
    data = None;
    while n > 0:
      buf = self.soc.recv(1024);
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
