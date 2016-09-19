#include "query_funcs.h"
#include <string.h>

void exit_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

void parse_player(MYSQL *conn){
  FILE* fp=fopen("player.txt","r");
  char* line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,fp)>0){
    if(line==NULL) continue;
    char* item=strtok(line," \n");
    if(item==NULL) continue;
    int team_id=atoi(strtok(NULL," \n"));
    int jersey_num=atoi(strtok(NULL," \n"));
    char *first_name=strdup(strtok(NULL," \n"));
    char *last_name=strdup(strtok(NULL," \n"));
    int mpg=atoi(strtok(NULL," \n"));
    int ppg=atoi(strtok(NULL," \n"));
    int rpg=atoi(strtok(NULL," \n"));
    int apg=atoi(strtok(NULL," \n"));
    double spg=atof(strtok(NULL," \n"));
    double bpg=atof(strtok(NULL," \n"));
    add_player(conn,team_id,jersey_num,first_name,last_name,mpg,ppg,rpg,apg,spg,bpg);
    free(line);
    free(first_name);
    free(last_name);
    line=NULL;
  }
  free(line);
  fclose(fp);
}

void add_player(MYSQL *conn, int team_id, int jersey_num, char *first_name, char *last_name,int mpg, int ppg, int rpg, int apg, double spg, double bpg){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"INSERT INTO PLAYER(TEAM_ID,UNIFORM_NUM,FIRST_NAME,LAST_NAME,MPG,PPG,RPG,APG,SPG,BPG) "
                  "VALUES(%d,%d,'%s','%s',%d,%d,%d,%d,%f,%f)",team_id,jersey_num,first_name,last_name,mpg,ppg,rpg,apg,spg,bpg);
  sqlQuery(conn,command);
  free(command);
}

void parse_team(MYSQL *conn){
  FILE* fp=fopen("team.txt","r");
  char* line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,fp)>0){
    if(line==NULL) continue;
    char* item=strtok(line," \n");
    if(item==NULL) continue;
    char *name=strdup(strtok(NULL," \n"));
    int state_id=atoi(strtok(NULL," \n"));
    int color_id=atoi(strtok(NULL," \n"));
    int wins=atoi(strtok(NULL," \n"));
    int losses=atoi(strtok(NULL," \n"));
    add_team(conn,name,state_id,color_id,wins,losses);
    free(line);
    free(name);
    line=NULL;
  }
  free(line);
  fclose(fp);
}

void add_team(MYSQL *conn, char *name, int state_id, int color_id, int wins, int losses){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"INSERT INTO TEAM(NAME,STATE_ID,COLOR_ID,WINS,LOSSES) "
                  "VALUES('%s',%d,%d,%d,%d)",name,state_id,color_id,wins,losses);
  sqlQuery(conn,command);
  free(command);
}

void parse_state(MYSQL *conn){
  FILE* fp=fopen("state.txt","r");
  char* line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,fp)>0){
    if(line==NULL) continue;
    char* item=strtok(line," \n");
    if(item==NULL) continue;
    char *name=strdup(strtok(NULL," \n"));
    add_state(conn,name);
    free(line);
    free(name);
    line=NULL;
  }
  free(line);
  fclose(fp);
}

void add_state(MYSQL *conn, char *name){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"INSERT INTO STATE(NAME) VALUES('%s')",name);
  sqlQuery(conn,command);
  free(command);
}

void parse_color(MYSQL *conn){
  FILE* fp=fopen("color.txt","r");
  char* line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,fp)>0){
    if(line==NULL) continue;
    char* item=strtok(line," \n");
    if(item==NULL) continue;
    char *name=strdup(strtok(NULL," \n"));
    add_color(conn,name);
    free(line);
    free(name);
    line=NULL;
  }
  free(line);
  fclose(fp);
}

void add_color(MYSQL *conn, char *name){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"INSERT INTO COLOR(NAME) VALUES('%s')",name);
  sqlQuery(conn,command);
  free(command);
}


void query1(MYSQL *conn,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            ){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"SELECT * FROM PLAYER WHERE true AND ");
  if(use_mpg==1){
    sprintf(command+strlen(command),"MPG >= %d AND MPG <= %d AND ",min_mpg,max_mpg);
  }
  if(use_ppg==1){
    sprintf(command+strlen(command),"PPG >= %d AND PPG <= %d AND ",min_ppg,max_ppg);
  }
  if(use_rpg==1){
    sprintf(command+strlen(command),"RPG >= %d AND RPG <= %d AND ",min_rpg,max_rpg);
  }
  if(use_apg==1){
    sprintf(command+strlen(command),"APG >= %d AND APG <= %d AND ",min_apg,max_apg);
  }
  if(use_spg==1){
    sprintf(command+strlen(command),"SPG >= %f AND SPG <= %f AND ",min_spg,max_spg);
  }
  if(use_bpg==1){
    sprintf(command+strlen(command),"BPG >= %f AND BPG <= %f AND ",min_bpg,max_bpg);
  }
  sprintf(command+strlen(command),"true");
  sqlQuery(conn,command);
  free(command);
  display(conn);
}


void query2(MYSQL *conn, char *team_color){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"SELECT TEAM.NAME FROM COLOR JOIN TEAM "
                  "WHERE COLOR.COLOR_ID = TEAM.COLOR_ID AND COLOR.NAME = '%s'",team_color);
  sqlQuery(conn,command);
  free(command);
  display(conn); 
}


void query3(MYSQL *conn, char *team_name){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"SELECT P.FIRST_NAME,P.LAST_NAME FROM PLAYER AS P JOIN TEAM AS T "
                  "WHERE P.TEAM_ID = T.TEAM_ID AND T.NAME = '%s' ORDER BY P.PPG DESC",team_name);
  sqlQuery(conn,command);
  free(command);
  display(conn);
}


void query4(MYSQL *conn, char *team_state, char *team_color){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"SELECT P.FIRST_NAME,P.LAST_NAME,P.UNIFORM_NUM "
                  "FROM PLAYER AS P JOIN TEAM AS T JOIN STATE AS S JOIN COLOR AS C "
                  "WHERE P.TEAM_ID = T.TEAM_ID AND T.STATE_ID = S.STATE_ID AND T.COLOR_ID = C.COLOR_ID "
                  "AND S.NAME = '%s' AND C.NAME = '%s'",team_state,team_color);
  sqlQuery(conn,command);
  free(command);
  display(conn);
}


void query5(MYSQL *conn, int num_wins){
  char* command=malloc(256*sizeof(*command));
  sprintf(command,"SELECT FIRST_NAME,LAST_NAME,NAME,WINS FROM PLAYER JOIN TEAM "
                  "WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND WINS > %d",num_wins);
  sqlQuery(conn,command);
  free(command);
  display(conn);
}

void display(MYSQL* conn){
  int status=0;
  do {
      //Get the result set (MYSQL_RES is a structure)
    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
      exit_with_error(conn);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;
    MYSQL_FIELD *field;
    
    while (field = mysql_fetch_field(result)) {
            printf("%s ", field->name);
    }
    printf("\n");

      //Fetch each row from the result set and print each field value
    while (row = mysql_fetch_row(result)) {
      for (int i=0; i < num_fields; i++) {
        printf("%s ", row[i] ? row[i] : "NULL");
      }
      printf("\n");
    }
    printf("\n");

    mysql_free_result(result);

    status = mysql_next_result(conn);

    if (status > 0) {
      exit_with_error(conn);
    } //if

  } while (status == 0);
}
