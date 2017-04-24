#!/usr/bin/env python3

import xmlParser as xp
import xmlReceiver as xr
import threading
from _thread import *
import time
import sys
import re
from queue import Queue

QUE = Queue();


class myThread1(threading.Thread):
    QUE = None;
    receiver = None;
    def __init__(self, QUE, receiver):
        threading.Thread.__init__(self);
        self.QUE = QUE;
        self.receiver = receiver;
    def run(self):
        rec(self.QUE, self.receiver);

class myThread2(threading.Thread):
    QUE = None;
    def __init__(self, QUE):
        threading.Thread.__init__(self);
        self.QUE = QUE;
    def run(self):
        par(self.QUE);

def rec(QUE, receiver):
    try:
        receiver.xmlReceive(QUE);
    except Exception as e:
        print(e);

def par(QUE):
    trans = None;
    try:
        trans = xp.xmlParser();
        trans.xmlParseInit(QUE);
    except Exception as e:
        print(e);

receiver = None;
receiver = xr.xmlReceiver();
n_recv = 1;
n_par = 1;
if len(sys.argv) > 1 and re.match(r'^[1-9][0-9]*$', sys.argv[1]) is not None:
    n_recv = int(sys.argv[1]);
if len(sys.argv) > 2 and re.match(r'^[1-9][0-9]*$', sys.argv[2]) is not None:
    n_par = int(sys.argv[2]);

print("start receiving module");
for i in range(n_recv):
    t = myThread1(QUE, receiver);
    t.daemon = True;
    t.start();
    print("receiving module ", i);

print("start parsing module");
for i in range(n_par):
    t = myThread2(QUE);
    t.daemon = True;
    t.start();
    print("parsing module ", i);

user_input = input();

