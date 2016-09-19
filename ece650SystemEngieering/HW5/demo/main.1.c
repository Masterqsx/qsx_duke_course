#include <stdlib.h>
#include <stdio.h>
#include <my_global.h>   //includes some global function declarations
#include <mysql.h>       //includes mysql function

int main (int argc, char *argv[]) 
{
  printf("MySQL client version: %s\n", mysql_get_client_info());

  //Allocate & initialize a MYSQL object
  MYSQL *conn = mysql_init(NULL); 

  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return -1;
  }

  //Establish a connection to the database
  //Parameters: connection handler, host name, user name, password,
  //            database name, port numbrer, unix socket, client flag
  if (mysql_real_connect(conn, "localhost", "root", "passw0rd", NULL, 0, NULL, 0) == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }

  //Execute an SQL statement (in this case create a new database)
  if (mysql_query(conn, "CREATE DATABASE testdb")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }

  //Close database connection
  mysql_close(conn);

  return 0;
}


