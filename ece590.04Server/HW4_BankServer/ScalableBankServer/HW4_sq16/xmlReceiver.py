import socket
import xmlParser as xp
from queue import Queue
import struct

class xmlReceiver:
    host = '';
    port = 12345;
    server = None;
    def __init__(self):
        host = '';
        port = 12345;
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
        self.server.bind((host, port));
        self.server.listen(20);
  
    def __del__(self):
        if self.server is not None:
            self.server.close();
        print("Closed server socket successfully");

    def xmlReceive(self, QUE):
        sc = None;
        try:
            while True:
                #print("Waiting for connection");
                sc, addr = self.server.accept();
                #print('connection setup');
                QUE.put((sc, Receiver(sc)));
                #print('xml Received');
        except Exception as e:
            print(e);
            #sc.close();
        
def Receiver(sc):
    data = '';
    res = '';
    count = 3072;
    flag = 1;
    while count > 0:
        try:
            data = sc.recv(1024);
        except Exception as e:
            print(e);
            return res;
        if not data:
            break;
        if flag == 1:
            flag = 0;
            int_size = struct.calcsize("!Q");
            (count,), data = struct.unpack("!Q", data[:int_size]), data[int_size:];
        count -= len(data);
        res += data.decode('utf-8');
    return res;
