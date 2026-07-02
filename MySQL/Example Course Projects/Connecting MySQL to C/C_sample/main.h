#include <my_global.h>
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>

void db_check();
void db_create();
void db_insert();
void db_error(MYSQL * conn);
void db_select();
void db_last_id();
void db_fetch_col();
void db_multi_command();
