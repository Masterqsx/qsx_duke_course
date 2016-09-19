#include "query_funcs.h"

void exit_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}


void add_player(MYSQL *conn, int team_id, int jersey_num, char *first_name, char *last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
}


void add_team(MYSQL *conn, char *name, int state_id, int color_id, int wins, int losses)
{
}


void add_state(MYSQL *conn, char *name)
{
}


void add_color(MYSQL *conn, char *name)
{
}


void query1(MYSQL *conn,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
}


void query2(MYSQL *conn, char *team_color)
{
}


void query3(MYSQL *conn, char *team_name)
{
}


void query4(MYSQL *conn, char *team_state, char *team_color)
{
}


void query5(MYSQL *conn, int num_wins)
{
}
