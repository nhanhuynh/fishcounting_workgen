/*
 * Database.h
 * Query the database
 *  Created on: Sep 10, 2013
 *      Author: zac
 */
#include <string>
#include <mysql/mysql.h>
#include <vector>
#include <memory>
using namespace std;
class Database
{
public:
	//initalize the database connection
	Database( string db, string server="ox.cs.pdx.edu", string usr="root", string pwd="bees")
	{
		connect=mysql_init(NULL); // Initialise the instance
		/* This If is irrelevant and you don't need to show it. I kept it in for Fault Testing.*/
		if(!connect)    /* If instance didn't initialize say so and exit with fault.*/
		{
			//fprintf(stderr,"MySQL Initialization Failed");
		}
		/* Now we will actually connect to the specific database.*/

		connect=mysql_real_connect(connect,server.c_str(),usr.c_str(),pwd.c_str(),db.c_str(),0,NULL,0);
		/* Following if statements are unneeded too, but it's worth it to show on your
		unique_ptrfirst app, so that if your database is empty or the query didn't return anything it
		will at least let you know that the connection to the mysql server was established. */
	}

	//query database and return the result
	vector<MYSQL_ROW> query(string query)
	{
		vector<MYSQL_ROW> result;
		MYSQL_RES *res_set; /* Create a pointer to recieve the return value.*/
		MYSQL_ROW row;  /* Assign variable for rows. */
		mysql_query(connect,query.c_str());
		/* Send a query to the database. */
		res_set = mysql_store_result(connect); /* Receive the result and store it in res_set */

		unsigned int numrows = mysql_num_rows(res_set); /* Create the count to print all rows */
		if (numrows == 0)
			return result;
		//populate result into vector
		while ((row = mysql_fetch_row(res_set)) != NULL){
			result.push_back(row);
		}
		return result;
	}
	~Database()
	{
		delete connect;
	}
private:
	MYSQL* connect;
};



