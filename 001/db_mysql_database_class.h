/**************
* File Name:	db_mysql_database_class.h
* Author:		Marco Schmitz
* Purpose:		mysql database class
* Created:		2013-12-18
**************/

#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h> 

using namespace std;

/**************
* Database Error Definitions
**************/
#define SUCCESS			200
#define ERR201			201
#define ERR202			202
#define ERR203			203
#define MAX_QUERY_LEN	500


class mysql_database
{
	public:
		//class constructor
		mysql_database();

		// connect & disconnect
		int		openConnection(char *host, char *user, char *pass, char *db);
		bool	disconnect();

		//querying
		MYSQL_RES	*query			(char *query);	//return result set
		char		*stringQuery	(char *query);	//return string
		int			intQuery		(char *query);	//return integer
		bool		boolQuery		(char *query);	//return boolean
		bool		updateQuery		(char *query);	//updates, returns true if update went through
		int			outputQuery		(char *query);

		//free the query results
		bool free();

	private:
		MYSQL		*sock;
		MYSQL_RES	*result;
		MYSQL_ROW	row;
		MYSQL_FIELD	*field;
		char		*qbuf[MAX_QUERY_LEN];
};

char *dberror(int errorcode); //return a string for this error message


#endif //DATABASE_H