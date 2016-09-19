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

  //Retrieve all data from the Employee table
  if (mysql_query(conn, "SELECT * FROM Employee")) {
    exit_with_error(conn);
  }

  //Get the result set (MYSQL_RES is a structure)
  MYSQL_RES *result = mysql_store_result(conn);

  if (result == NULL) {
    exit_with_error(conn);
  }

  //Get the number of fields (columns) from the result set
  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  MYSQL_FIELD *field;

  //Fetch each row from the result set and print each field value
  while (row = mysql_fetch_row(result)) {
    for (int i=0; i < num_fields; i++) {
      if (i == 0) {
	while (field = mysql_fetch_field(result)) {
	  printf("%s ", field->name);
	}
	printf("\n");
      }
      printf("%s ", row[i] ? row[i] : "NULL");
    }
  }

  //Free result set
  mysql_free_result(result);

  //Close database connection
  mysql_close(conn);

  return 0;
}


