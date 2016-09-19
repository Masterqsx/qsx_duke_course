#include <stdlib.h>
#include <stdio.h>
#include <my_global.h>   //includes some global function declarations
#include <mysql.h>       //includes mysql function

void exit_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

int main (int argc, char *argv[]) 
{
  int status = 0;

  //Allocate & initialize a MYSQL object
  MYSQL *conn = mysql_init(NULL); 

  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  //Establish a connection to the database
  //Parameters: connection handler, host name, user name, password,
  //            database name, port numbrer, unix socket, client flag
  if (mysql_real_connect(conn, "localhost", "myuser", "passw0rd", 
			 "testdb", 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL) {
    exit_with_error(conn);
  }

  //Retrieve all data from the Employee table
  if (mysql_query(conn, "SELECT FirstName FROM Employee WHERE DepartmentID=1; \
                        SELECT FirstName FROM Employee WHERE DepartmentID=2")) {
    exit_with_error(conn);
  }

  do {
    //Get the result set (MYSQL_RES is a structure)
    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
      exit_with_error(conn);
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    printf("%s\n", row[0]);

    mysql_free_result(result);

    status = mysql_next_result(conn);

    if (status > 0) {
      exit_with_error(conn);
    } //if

  } while (status == 0);

  //Close database connection
  mysql_close(conn);

  return 0;
}


