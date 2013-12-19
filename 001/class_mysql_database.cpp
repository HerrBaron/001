/******************************************************************************
* File Name:	class_database.cpp
* Author:		Marco Schmitz
* Purpose:		mysql database class
* Created:		2013-12-18
******************************************************************************/

//#include <mysql.h> 
#include <windows.h>
#include <stdio.h> 

#include "db_mysql_database_class.h"

using namespace std;



/******************************************************************************
* Purpose:			default constructor, initialize class values
* Precondition:		none
* Postcondition:	none
******************************************************************************/

mysql_database::mysql_database()
{
	//initialize the mysql fields
	sock	= NULL;
	row		= NULL;
	result  = NULL;
	field	= NULL;
}


/******************************************************************************
* Purpose:			connect to the appropriate database
* Precondition:		host, database, user name and password
* Postcondition:	connected to that database
******************************************************************************/

int mysql_database::openConnection(char *host, char *user, char *pass, char *db)
{
	if (sock)
	{
		disconnect();
	}

	sock = mysql_init(0);

	//something went wrong with the socket
	if (!sock)
	{
		return ERR201;
	}

	//try connecting to the database  
	if (!mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0))
	{
		return ERR202;
	}

	//successfully connected to the database    
	return SUCCESS;
}


/******************************************************************************
* Purpose:			disconnect from the database
* Precondition:		none
* Postcondition:	socket closed
******************************************************************************/
bool mysql_database::disconnect()
{
	//they have a socket open
	if (sock)
	{
		mysql_close(sock);

		//release result data
		free();

		//database disconnected
		return true;
	}
	else
	{
		return false;
	}	
}


/******************************************************************************
* Purpose:			free the results from the database query
* Precondition:		none
* Postcondition:	results no longer there
******************************************************************************/
bool mysql_database::free()
{
	if (result)
	{
		mysql_free_result(result);
		return true;
	}
	return false;
}


/******************************************************************************
* Purpose:			return the approprite error message
* Precondition:		error code
* Postcondition:	string with the error returned
******************************************************************************/
char *dberror(int errorcode)
{
	//display the appropriate error message for this error    
	switch (errorcode)
	{
		case SUCCESS: return "SUCCESS";
			break;

		case ERR201: return "201 SOCKET ERROR: SOCKET FAILURE";
			break;

		case ERR202: return "202 CONNECTION ERROR: CANNOT ACCESS THE SERVER";
			break;

		case ERR203: return "203 DATABASE ERROR: QUERY FAILED";
			break;
	}
	return NULL; //no error, return null char
}


/******************************************************************************
* Purpose:			return the result set of the query
* Precondition:		the query string
* Postcondition:	result set returned (or null)
******************************************************************************/
MYSQL_RES *mysql_database::query(char *query)
{
	//query the database
	mysql_query(sock, query);

	//store the results
	result = mysql_store_result(sock);

	return result;
}


/******************************************************************************
* Purpose:			update the database no result returned
* Precondition:		the query string
* Postcondition:	false if failed, true if suceess
******************************************************************************/
bool mysql_database::updateQuery(char *query)
{
	if (!mysql_query(sock, query))
	{
		//failed query
		return 0; 
	}
	else
	{
		//successful query
		return 1; 
	}
		
}


/******************************************************************************
* Purpose:			return the result set of the query
* Precondition:		the query string
* Postcondition:	the FIRST result is returned (or null) will not return 
*					multiple rows, only the first
******************************************************************************/
char *mysql_database::stringQuery(char *query)
{
	//if old results exist, free them
	//free();

	//query the database
	mysql_query(sock, query);

	//store the results
	result = mysql_store_result(sock);

	if (!result)
	{
		return NULL; //no results
	}

	//fetch the row
	row = mysql_fetch_row(result);

	//store the result & convert it to a number
	char* stringResult = row[0];

	//free the results
	//free();

	return stringResult;
}


/******************************************************************************
* Purpose:			return the result set of the query
* Precondition:		the query string
* Postcondition:	the FIRST result is returned (or null) will not return 
*					multiple rows, only the first
******************************************************************************/
int mysql_database::intQuery(char *query)
{
	//query the database
	mysql_query(sock, query);

	//store the results
	result = mysql_store_result(sock);

	if (!result)
	{
		return -1; //no results
	}		

	//fetch the row
	row = mysql_fetch_row(result);

	//store the result & convert it to a number
	int id = atoi(row[0]);

	//free the results
	//free();

	return id; //return the id number
}


/******************************************************************************
* Purpose:			return the result set of the query
* Precondition:		the query string
* Postcondition:	the FIRST result is returned (or null) will not return 
*					multiple rows, only the first
******************************************************************************/
bool mysql_database::boolQuery(char *query)
{

	//query the database
	mysql_query(sock, query);

	//store the results
	result = mysql_store_result(sock);

	return (bool)row[0];
}


/******************************************************************************
* Purpose:			return the result set of the query
* Precondition:		the query string
* Postcondition:	complete resultset - basic formatting
******************************************************************************/
int mysql_database::outputQuery(char *query)
{
	unsigned int	num_fields;
	MYSQL_RES		*result;

	//query the database
	mysql_query(sock, query);

	//store the results
	result = mysql_store_result(sock);

	num_fields = mysql_num_fields(result);

	while ((row = mysql_fetch_row(result)))
	{
		unsigned long	*lengths;
		unsigned int	i;

		lengths = mysql_fetch_lengths(result);

		for (i = 0; i < num_fields; i++)
		{
			printf("[%.*s] \t", (int)lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}
	return 0;
}