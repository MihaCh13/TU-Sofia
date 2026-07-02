#include "main.h"

int main ()
{
	db_check();
	db_create();
	db_insert();
	db_select();
    db_last_id();
	db_fetch_col();
	db_multi_command();

	return 0;
}

void db_check()
{
	printf ("MySQL get client info: %s\n",mysql_get_client_info());
}

void db_error(MYSQL* conn)
{
	fprintf(stderr,"MySQL Error: %s\n",mysql_error(conn));
	mysql_close(conn);
	system("pause");
	exit(1);
}

void db_create()
{
	MYSQL *conn = mysql_init(NULL);

	if (conn == NULL)
	{
		fprintf(stderr, "MySQL Error: %s\n", mysql_error(conn));
		exit (1);
	}

	if (mysql_real_connect(conn,"localhost","root","",NULL,0,NULL,0) == NULL)
		db_error(conn);

	if (mysql_query(conn,"drop database if exists mydbtest;")!=0)
		db_error(conn);

	if (mysql_query(conn,"drop user dani@localhost;")!=0)
		db_error(conn);

	if (mysql_query(conn,"create database mydbtest character set=utf8;")!=0)
		db_error(conn);

	if (mysql_query(conn,"create user dani@localhost identified by 'daniela';")!=0)
		db_error(conn);

	if (mysql_query(conn,"grant all on mydbtest.* to dani@localhost;")!=0)
		db_error(conn);

	mysql_close(conn);
}

void db_insert()
{
	MYSQL *conn = mysql_init(NULL);

	if (conn == NULL)
	{
		fprintf(stderr, "MySQL Error: %s\n", mysql_error(conn));
		exit (1);
	}

	if (mysql_real_connect(conn,"localhost","dani","daniela","mydbtest",0,NULL,0) == NULL)
		db_error(conn);

	if (mysql_query(conn,"drop table if exists cars")!=0)
		db_error(conn);

	if (mysql_query(conn,"create table cars (id int, name text, price int)")!=0)
		db_error(conn);

	if (mysql_query(conn,"insert into cars values (1,'audi',56423),(2,'mercedes',57127),(3,'skoda',9000),(4,'volvo',29000),(5,'bentley',35000),(6,'citroen',21000),(7,'hummer',41400),(8,'volkswagen',21600)")!=0)
		db_error(conn);

	mysql_close(conn);
}

void db_select()
{
	MYSQL *conn = mysql_init(NULL);
	MYSQL_RES *result;
	int num_fields;
	MYSQL_ROW row;
	int i;

	if (conn == NULL)
	{
		fprintf(stderr, "MySQL Error: %s\n", mysql_error(conn));
		exit (1);
	}

	if (mysql_real_connect(conn,"localhost","dani","daniela","mydbtest",0,NULL,0) == NULL)
		db_error(conn);

	if (mysql_query(conn,"select * from cars")!=0)
		db_error(conn);

	result = mysql_store_result(conn);
	num_fields = mysql_num_fields(result);

	while ((row = mysql_fetch_row(result))) {
		for(i = 0; i < num_fields; i++) {
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);
	mysql_close(conn);
}

void db_last_id()
{
	MYSQL *conn = mysql_init(NULL);
	int id;

	if (conn == NULL)
	{
		fprintf(stderr, "MySQL Error: %s\n", mysql_error(conn));
		exit (1);
	}

	if (mysql_real_connect(conn,"localhost","dani","daniela","mydbtest",0,NULL,0) == NULL)
		db_error(conn);

	if (mysql_query(conn,"drop table if exists writers")!=0)
		db_error(conn);

	if (mysql_query(conn,"create table writers (id int primary key auto_increment, name text)")!=0)
		db_error(conn);

	if (mysql_query(conn,"insert into writers(name) values ('Leo Tolstoy'),('Jack London'),('Honore de Balsac')")!=0)
		db_error(conn);

	id = mysql_insert_id(conn);
	printf ("Last inserted ID is %d\n",id);

	mysql_close(conn);
}

void db_fetch_col()
{
	MYSQL *conn = mysql_init(NULL);
	MYSQL_RES *result;
	int num_fields;
	MYSQL_ROW row;
	int i;
	MYSQL_FIELD *field;

	if (conn == NULL)
	{
		fprintf(stderr, "MySQL Error: %s\n", mysql_error(conn));
		exit (1);
	}

	if (mysql_real_connect(conn,"localhost","dani","daniela","mydbtest",0,NULL,0) == NULL)
		db_error(conn);

	if (mysql_query(conn,"select * from cars limit 3")!=0)
		db_error(conn);

	result = mysql_store_result(conn);
	num_fields = mysql_num_fields(result);

	while ((row = mysql_fetch_row(result))) {
		for(i = 0; i < num_fields; i++) {
			if (i==0)
			{
				while((field = mysql_fetch_field(result)) != NULL) {
					printf("%s ", field->name);
				}
				printf("\n");
			}
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);
	mysql_close(conn);
}

void db_multi_command()
{
	MYSQL *conn = mysql_init(NULL);
	MYSQL_RES *result;
	MYSQL_ROW row;
	int status;

	if (conn == NULL)
	{
		fprintf(stderr, "MySQL Error: %s\n", mysql_error(conn));
		exit (1);
	}

	if (mysql_real_connect(conn,"localhost","dani","daniela","mydbtest",0,NULL,CLIENT_MULTI_STATEMENTS) == NULL)
		db_error(conn);

	if (mysql_query(conn,"SELECT Name FROM Cars WHERE Id=2; SELECT Name FROM Cars WHERE Id=3; SELECT Name FROM Cars WHERE Id=6")!=0)
		db_error(conn);

	do
	{
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
		printf("%s ", row[0]);

		mysql_free_result(result);

		status = mysql_next_result(conn);
		if (status > 0)
			db_error(conn);
	} while (status==0);

	mysql_close(conn);
}
