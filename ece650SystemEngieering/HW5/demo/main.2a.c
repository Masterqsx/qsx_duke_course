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
  //Allocate & initialize a MYSQL object
  MYSQL *conn = mysql_init(NULL); 

  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  //Establish a connection to the database
  //Parameters: connection handler, host name, user name, password,
  //            database name, port numbrer, unix socket, client flag
  if (mysql_real_connect(conn, "localhost", "myuser", "passw0rd", "testdb", 0, NULL, 0) == NULL) {
    exit_with_error(conn);
  }

  if (mysql_query(conn, "DROP TABLE IF EXISTS Employee")) {
    exit_with_error(conn);
  }

  if (mysql_query(conn, "CREATE TABLE Employee(Id INT, FirstName TEXT, LastName TEXT, DepartmentID INT)")) {
    exit_with_error(conn);
  }

  if (mysql_query(conn, "INSERT INTO Employee VALUES(1, 'John', 'Doe', 3)")) {
    exit_with_error(conn);
  }

  if (mysql_query(conn, "INSERT INTO Employee VALUES(2, 'Jane', 'Doe', 1)")) {
    exit_with_error(conn);
  }

  if (mysql_query(conn, "INSERT INTO Employee VALUES(3, 'George', 'Washington', 3)")) {
    exit_with_error(conn);
  }

  if (mysql_query(conn, "INSERT INTO Employee VALUES(4, 'Jim', 'Smith', 2)")) {
    exit_with_error(conn);
  }

  //Close database connection
  mysql_close(conn);

  return 0;
}


