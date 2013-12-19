#include <iostream> 
#include <windows.h> 
#include <stdio.h> 
#include <mysql.h> 

#include "db_credentials.h"
#include "db_mysql_database_class.h"
using namespace std;

int main()
{
	//MYSQL mysql;
	//MYSQL * conn;
	//
	//mysql_init(&mysql);

	////connect to mySQL database
	//conn = mysql_real_connect (&mysql, HOST, USER, PASS, DB, PORT, 0, 0); 

	//if (conn == NULL)
	//{
	//	cout << "Keine Verbindung zur Datenbank" << endl;
	//}
	//else
	//{
	//	cout << "Erfolgreich verbunden" << endl;
	//}

	//system("pause");

	//mysql_close(conn);


	mysql_database database;
	char query[] = "SELECT * FROM test";
	char *result = NULL;

	cout << dberror(database.openConnection(HOST, USER, PASS, DB));
	cout << endl;

	result = database.stringQuery(query);

	database.outputQuery(query);
	database.disconnect();

	system("pause");

	return 0;
}