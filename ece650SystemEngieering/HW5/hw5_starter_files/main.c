#include <stdlib.h>
#include <stdio.h>
#include "exerciser.h"


int main (int argc, char *argv[]) 
{
  //Allocate & initialize a MYSQL object
  MYSQL *conn = mysql_init(NULL); 

  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  //Establish a connection to the database
  //Parameters: connection handler, host name, user name, password,
  //            database name, port numbrer, unix socket, client flag
  if (mysql_real_connect(conn, "localhost", "myuser", "passw0rd", "ACC_BBALL", 0, NULL, 0) == NULL) {
    exit_with_error(conn);
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files


  exercise(conn);


  //Close database connection
  mysql_close(conn);

  return 0;
}


