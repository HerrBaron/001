#include <iostream> 
#include <windows.h> 
#include <stdio.h> 
#include <mysql.h> 

#include "db_credentials.h"
using namespace std;
MYSQL mysql;
MYSQL * conn;

int main()
{
	mysql_init(&mysql);

	//connect to mySQL database
	conn = mysql_real_connect (&mysql, HOST, USER, PASS, DB, PORT, 0, 0); 

	if (conn == NULL)
	{
		cout << "Keine Verbindung zur Datenbank" << endl;
	}
	else
	{
		cout << "Erfolgreich verbunden" << endl;
	}

	system("pause");

	mysql_close(conn);
	
	return 0;
}