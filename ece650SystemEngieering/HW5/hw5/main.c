#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "exerciser.h"


void sqlQuery(MYSQL *conn,const char* command);
int main (int argc, char *argv[]) 
{
  
  char* pwd=NULL;
  char* command=NULL;
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
  sqlQuery(conn,"DROP TABLE IF EXISTS PLAYER");
  sqlQuery(conn,"DROP TABLE IF EXISTS TEAM");
  sqlQuery(conn,"DROP TABLE IF EXISTS STATE");
  sqlQuery(conn,"DROP TABLE IF EXISTS COLOR");
  sqlQuery(conn,"CREATE TABLE PLAYER (PLAYER_ID INTEGER PRIMARY KEY AUTO_INCREMENT UNIQUE,"
                                      "TEAM_ID INTEGER,UNIFORM_NUM INTEGER,FIRST_NAME TEXT,"
                                      "LAST_NAME TEXT,"
                                      "MPG INTEGER,"
                                      "PPG INTEGER,"
                                      "RPG INTEGER,"
                                      "APG INTEGER,"
                                      "SPG FLOAT,"
                                      "BPG FLOAT)");
  
  sqlQuery(conn,"CREATE TABLE TEAM (TEAM_ID INTEGER PRIMARY KEY AUTO_INCREMENT UNIQUE,"
                                    "NAME TEXT,"
                                    "STATE_ID INTEGER,"
                                    "COLOR_ID INTEGER,"
                                    "WINS INTEGER,"
                                    "LOSSES INTEGER)");

  sqlQuery(conn,"CREATE TABLE STATE (STATE_ID INTEGER PRIMARY KEY AUTO_INCREMENT UNIQUE,"
                                     "NAME TEXT)");
  sqlQuery(conn,"CREATE TABLE COLOR (COLOR_ID INTEGER PRIMARY KEY AUTO_INCREMENT UNIQUE,"
                                    "NAME TEXT)");
 /* 
  pwd=getcwd(NULL,256);
  command=malloc(256*sizeof(*command));
  strcat(pwd,"/player.txt' INTO TABLE PLAYER FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n'");
  strcpy(command,"LOAD DATA INFILE '");
  strcat(command,pwd);
  sqlQuery(conn,command);
  free(pwd);
  free(command);
*/parse_player(conn);
/*
  pwd=getcwd(NULL,256);
  command=malloc(256*sizeof(*command));
  strcat(pwd,"/team.txt' INTO TABLE TEAM FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n'");
  strcpy(command,"LOAD DATA INFILE '");
  strcat(command,pwd);
  sqlQuery(conn,command);
  free(pwd);
  free(command);
*/parse_team(conn);
/*
  pwd=getcwd(NULL,256);
  command=malloc(256*sizeof(*command));
  strcat(pwd,"/state.txt' INTO TABLE STATE FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n'");
  strcpy(command,"LOAD DATA INFILE '");
  strcat(command,pwd);
  sqlQuery(conn,command);
  free(pwd);
  free(command);
*/parse_state(conn);
/*
  pwd=getcwd(NULL,256);
  command=malloc(256*sizeof(*command));
  strcat(pwd,"/color.txt' INTO TABLE COLOR FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n'");
  strcpy(command,"LOAD DATA INFILE '");
  strcat(command,pwd);
  sqlQuery(conn,command);
*/parse_color(conn);

  free(pwd);
  free(command);

  exercise(conn);


  //Close database connection
  mysql_close(conn);

  return 0;
}

void sqlQuery(MYSQL *conn,const char* command){
  if (mysql_query(conn, command)) {
      exit_with_error(conn);
  }
}


