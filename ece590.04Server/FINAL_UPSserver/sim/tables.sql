DROP TABLE trucks;
DROP TABLE deliveries;
DROP TABLE warehouse;
DROP TABLE whstock;
DROP TABLE whready;
DROP TABLE truckhas;
DROP TABLE whincoming;
DROP TABLE shipments;
DROP SEQUENCE worldids;
CREATE TABLE trucks (
       wid int8,
       trid int4,
       trstate int4,
       x int4,
       y int4,
       currid int8,
       statechange timestamp,
       CONSTRAINT trucksKey PRIMARY KEY(wid,trid)
);
CREATE TABLE deliveries (
   wid int8,
   trid int4,
   sid int8,
   num bigserial,
   x int4,
   y int4
);
CREATE INDEX delids ON deliveries (wid,trid);

CREATE TABLE warehouse (
   wid int8,
   hid int4,
   x int4,
   y int4,
   CONSTRAINT whkey PRIMARY KEY (wid, hid),
   UNIQUE(wid,x,y)
);
CREATE TABLE truckhas (
   wid int8,
   sid int8,
   trid int4,
   CONSTRAINT thpkey PRIMARY KEY (wid,sid)
);
   
CREATE TABLE whstock (
   wid int8,
   hid int4,
   pid int8,
   descr text,
   num int8,
   CONSTRAINT whpkey PRIMARY KEY (wid,hid,pid)
 );

CREATE TABLE whready (
   wid int8,
   hid int4,
   sid int8,
   whenready timestamp,
   notified bool,
   CONSTRAINT whrkey PRIMARY KEY (wid, hid,sid)
);

CREATE INDEX whreadywhen ON whready (whenready);

CREATE SEQUENCE worldids START WITH 1000;

CREATE TABLE whincoming (
       wid int8,
       hid int4,
       pid int8,
       descr text,
       num int4,
       artime timestamp
);
CREATE INDEX whinctime ON whincoming (artime);

CREATE TABLE shipments (
       wid int8,
       sid int8,
       descr text,
       num int4,
       completed bool
);       

CREATE INDEX shipids ON shipments (wid,sid);
