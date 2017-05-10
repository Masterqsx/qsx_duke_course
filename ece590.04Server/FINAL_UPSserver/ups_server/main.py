#! /usr/bin/python3

import ups_connector as uc
import ups_handler as uh
import threading
from queue import Queue

class t_con(threading.Thread):
  Q = None;
  con = None;
  def __init__(self, i_Q, con):
    threading.Thread.__init__(self);
    self.Q = i_Q;
    self.con = con;

class t_con1_recv(t_con):
  def __init__(self, Q, con):
    super().__init__(Q, con);
  def run(self):
    self.con.from_world(self.Q);

class t_con1_send(t_con):
  def __init__(self, Q, con):
    super().__init__(Q, con);
  def run(self):
    self.con.to_world(self.Q);

class t_con2_recv(t_con):
  def __init__(self, Q, con):
    super().__init__(Q, con);
  def run(self):
    self.con.from_amazon(self.Q);

class t_con2_send(t_con):
  def __init__(self, Q, con):
    super().__init__(Q, con);
  def run(self):
    self.con.to_amazon(self.Q);

class t_ahandler(threading.Thread):
  Q3 = None;
  Q4 = None;
  handler = None;
  def __init__(self, Q3, Q4, handler):
    threading.Thread.__init__(self);
    self.Q3 = Q3;
    self.Q4 = Q4;
    self.handler = handler;
  def run(self):
    self.handler.amain_handler(self.Q3, self.Q4);

class t_whandler(threading.Thread):
  Q1 = None;
  Q2 = None;
  handler = None;
  def __init__(self, Q1, Q2, handler):
    threading.Thread.__init__(self);
    self.Q1 = Q1;
    self.Q2 = Q2;
    self.handler = handler;
  def run(self):
    self.handler.wmain_handler(self.Q1, self.Q2);
    
class t_scheduler(threading.Thread):
  Q = None;
  wait = 5;
  handler = None;
  def __init__(self, Q, wait, handler):
    threading.Thread.__init__(self);
    self.Q = Q;
    self.wait = wait;
    self.handler = handler;
  def run(self):
    self.handler.deliver_scheduler(self.Q, self.wait); 

QU1 = Queue();
QU2 = Queue();
QU3 = Queue();
QU4 = Queue();

handler_scheduler = uh.ups_handler();
th_scheduler = t_scheduler(QU2, 5, handler_scheduler);
th_scheduler.daemon = True;
th_scheduler.start();

handler1 = uh.ups_handler();
handler2 = uh.ups_handler();
th1 = t_ahandler(QU3, QU2, handler1);
th1.daemon = True;
th1.start();
th2 = t_whandler(QU1, QU4, handler2);
th2.daemon = True;
th2.start();

con1 = uc.ups_connector('colab-sbx-pvt-08.oit.duke.edu', 12345);
con1.connect_to_world(1000);
t1_recv = t_con1_recv(QU1, con1);
t1_send = t_con1_send(QU2, con1);
t1_recv.daemon = True;
t1_recv.start();
t1_send.daemon = True;
t1_send.start();

con2 = uc.ups_connector('', 34567);
con2.connect_to_amazon();
print('Successfully connect to Amazon');
t2_recv = t_con2_recv(QU3, con2);
t2_send = t_con2_send(QU4, con2);
t2_recv.daemon = True;
t2_recv.start();
t2_send.daemon = True;
t2_send.start();

input();
