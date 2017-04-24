1. Server can be run with command:
  python3 main.py [# of receive threads] [# of parse threads]
You can use the script "bank-st" to run the server with 1 receive thread and 1 parse thread. 
You can use the script "bank-mt" to run the server with 1 receive thread and 4 parse thread which is the best setting on 2015 Macbook Pro 13-inch.

example:
  python3 main.py 1 1 #server running with 1 receive thread and 1 parse thread
  ./bank-st
  ./bank-mt

2. Test program can be run with command:
  python3 test.py [server ip] [test type] [# of concurrent requests]
  [test type] is 'func' or 'load'. When you choose 'func' test, the return xml file will be printed out. On the contrary, when you choose 'load', only the average waiting time of each request will be calculated.
You can use the script "func-test [server ip]" to run the test with 1 concurrent request.
You can use the script "load-test [server ip]" to run the test with 500 concurrent request.

example:
  python3 test.py 127.0.0.1 func 1
  python3 test.py 127.0.0.1 load 500
  ./func-test
  ./load-test

3. When you start to run the server program, make sure your PostgreSQL setting match the arguments in class "xmlParser"'s constructor.
