#include "exerciser.h"


void exercise(MYSQL *conn) {
   query1(conn, 1, 20, 25, 
  	 0, 0, 0,
  	 0, 0, 0,
  	 0, 0, 0,
  	 0, 0, 0,
  	 0, 0, 0);
  query2(conn, "Black");
  query3(conn, "Clemson");
  query4(conn, "NC", "DarkBlue");
  query5(conn, 5);

  return;
}

