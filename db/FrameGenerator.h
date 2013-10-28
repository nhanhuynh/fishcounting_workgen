/*
 * FrameGenerator.h
 * Generate fish frame (know and unknow) from database to various format
 * Currently support: XML
 *
 *  Created on: Sep 10, 2013
 *      Author: zac
 */

#ifndef FRAMEGENERATOR_H_
#define FRAMEGENERATOR_H_
#include <string>
#include "database.h"
#include <algorithm>
#include <sstream>
using namespace std;

enum FRAMETYPE{KNOW, UNKNOW};
enum FORMAT{XML,JSON};
class FrameGenerator
{
public:
	string generateFrames(int know_qty, int unknow, FORMAT format);
	FrameGenerator(string dbName="fishimg", string url="http://api.metacaptcha.com/public/images/"): db(dbName), url(url){};
	/*
	 * Return the list of frame (the numbere of frame return could
	 * be less than "qty" parameter). This function guarantee that different calls to the same
	 * object never return frame with the same frame ID.
	 * @return:
	 * XML format
	 * if type is know:
	 * 	<knowframes>
	 * 	 <frame>
	 * 		<frameID></frameID>
	 * 		<x></x>
	 * 		<y></y>
	 * 		<width></width>
	 * 		<height></height>
	 * 	 </frame>
	 * 	</knowframe>
	 * 	if type is unknow
	 * 	<unknowframes>
	 * 	 <frame>
	 * 		<frameID></frameID>
	 * 	 </frame>
	 * 	</unknowframes>
	 */
	int getFrames( string &filled_string, int qty, FRAMETYPE type, FORMAT format);
	string getNotInClause();
private:
	/*
	 * Remember the frameID that has been return so that they won't be return again
	 * in the subsequent calls
	 */
	void addFrameToExcludedList(vector<MYSQL_ROW>  &rows, int index);
	/*
	 * return the frameID stored in frameID_vector as string for used
	 * in the SQL query
	 */
	/*
	 * compose vector of mysql row into XML format
	 */
	string convertRowsToString(vector<MYSQL_ROW> &rows, FRAMETYPE type, FORMAT format);
	vector<string> frameID_vector;
	Database db;
	string url;
};




#endif /* FRAMEGENERATOR_H_ */
