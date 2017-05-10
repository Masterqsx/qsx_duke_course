import psycopg2 as py2

conn = None;
try:
  conn = py2.connect(database='ups', user='postgres', password='passw0rd', host='127.0.0.1', port='');
except Exception as e:
  print(e);
  exit();
print('Connect to database "ups" successfully');
cur = conn.cursor();
cur.execute('drop table if exists package;');
cur.execute('drop table if exists pickup;');
cur.execute('drop table if exists delivery;');
cur.execute('drop table if exists truck;');
try:
  conn.commit();
except Exception as e:
  print(e);
  exit();
print('Successfully clean the database');
cur.execute('''create table package
(id serial primary key,
package_id bigint,
user_id varchar(100),
info varchar(1000),
status int,
pri int,
ship_id int);''');
cur.execute('''create table pickup
(id serial primary key,
truck_id int,
package_id bigint,
wh_id int,
status int);''');
cur.execute('''create table delivery
(id serial primary key,
truck_id int,
package_id bigint,
x int,
y int,
status int);''');
cur.execute('''create table truck
(truck_id int primary key,
x int,
y int,
status int);''');
try:
  conn.commit();
except Exception as e:
  print(e);
  exit();
print('Successfully create tabel "package", "pickup" and "delivery"');
n_truck = 3;
for i in range(n_truck):
  cur.execute('''insert into truck (truck_id, x, y, status) 
  values (''' + str(i) + ''', 0, 0, -1);''');
  try:
    conn.commit();
  except Exception as e:
    print(e);
    exit();
  print('Insert truck info ' + str(i));
