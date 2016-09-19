#gcc -o test -I/usr/include/mysql main.c

gcc -std=gnu99 -o test main.c `mysql_config --cflags --libs`
