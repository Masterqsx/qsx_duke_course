import socket
import xmlPaser as xp
from queue import Queue
import struct

def xmlReceive(QUE):
    host = '';
    port = 12345;
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        server.bind((host, port));
    except socket.error as e:
        print(e);
        return;

    try:
        server.listen(20);
        trans = xp.xmlTrans();
        while True:
            print("Waiting for connection");
            sc, addr = server.accept();
            print('connection setup');
            QUE.put((sc, Receiver(sc)));
            print('xml Received');
            trans.xmlInit(QUE);
            trans.xmlParse();
            print('xml Returned');
    except:
        server.close();
        


def Receiver(sc):
    data = '';
    res = '';
    count = 3072;
    flag = 1;
    while count > 0:
        data = sc.recv(2048);
        print(data)
        if not data:
            break;
        if flag == 1:
            flag = 0;
            int_size = struct.calcsize("!Q");
            (count,), data = struct.unpack("!Q", data[:int_size]), data[int_size:];
        count -= len(data);
        res += data.decode('utf-8');
    return res;
