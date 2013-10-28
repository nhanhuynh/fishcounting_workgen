/*
 * FrameGenerator.cpp
 *
 *  Created on: Sep 11, 2013
 *      Author: zac
 */
#include "FrameGenerator.h"

string FrameGenerator::generateFrames(int know_qty, int unknow_qty, FORMAT format)
{
	string str;
	ostringstream os;
	os<<"{\"url\": \""<<url<<"\",";

	//get unknown frame first;
	int actual_unknow_qty = getFrames(str, unknow_qty, UNKNOW, JSON );
	if  (actual_unknow_qty != 0)
	{
		//in case getFrames return less frames than we need
		//adjust (increase) the know_qty
		know_qty = know_qty + (unknow_qty - actual_unknow_qty);
		os<<str<<",";
	}

	getFrames(str, know_qty, KNOW, JSON );
	os<<str<<"}";
	return os.str();
}
int FrameGenerator::getFrames( string &filled_string, int qty, FRAMETYPE type, FORMAT format)
{
	//reset filled_string first
	filled_string = "";
	string query;
	int actual_qty ;
	vector <MYSQL_ROW> rows;
	ostringstream os;
	if (type == KNOW)
	{
		//randomly select know frames

		 //exclude previously selected frames ( if any )in the query
		string not_in = getNotInClause();
		if (not_in == "")
		{
			os<<"select rects.FrameID, Name, x,y,width,height from rects, frames where rects.FrameID = frames.FrameID  order by rand() LIMIT "<<qty;
			query = os.str();
		}
		else
		{
			//select rects.FrameID,Name, x,y,width,height from rects, frames where rects.FrameID = frames.FrameID and rects.FrameID not in (506) LIMIT 3
			os<<"select rects.FrameID, Name, x,y,width,height from rects, frames  where rects.FrameID = frames.FrameID  and rects.FrameID not in "<<not_in<<"  order by rand() LIMIT "<<qty;
			query = os.str();
		}
		rows= db.query(query);
		actual_qty = rows.size();
		if (actual_qty < qty)
			return 0;
		//store the selected frame so that they won't be selected again
		addFrameToExcludedList(rows, 0);
		//convert the rows to desired format
		filled_string = convertRowsToString(rows, KNOW,format);
	}
	else if (type == UNKNOW){
		string not_in = getNotInClause();
		if (not_in == "")
		{
			os<<"select VideoID,FrameID,Name from frames where status =-1  order by rand() LIMIT "<<qty;
			query = os.str();
		}
		else
		{
			os<<"select VideoID,FrameID,Name from frames where status =-1  and FrameID not in "<<not_in<<" order by rand() LIMIT "<<qty;
			query = os.str();
		}
		rows= db.query(query);
		actual_qty = rows.size();
		//if actual_qty < qty, reset all frame status to -1
		//then perform the query again
		if (actual_qty < qty)
		{
			db.query("update frames set status = -1");
			rows= db.query(query);
			actual_qty = rows.size();
		}
		//store the selected frame so that they won't be selected again
		addFrameToExcludedList(rows, 1);
		//convert the rows to desired format
		filled_string = convertRowsToString(rows, UNKNOW, format);
	}
	return actual_qty;

}


string FrameGenerator::convertRowsToString(vector<MYSQL_ROW> &rows, FRAMETYPE type, FORMAT format)
	{
		//boundary check
		int size = rows.size();
		if (size == 0)
			return "";
		string result ="";
		if (format == XML)
		{

			if (type==KNOW)
			{
				result += "<knowframes>";
				MYSQL_ROW row;
				for (int i = 0; i < size; i++)
				{
					result += "<frame>";
					row = rows.at(i);
					result += (string)("<frameID>") + row[0] + "</frameID>";
					result += (string)"<name>" + row[1] +"</name>";
					result += (string)"<x>" + row[2] +"</x>";
					result += (string)"<y>" + row[3] + "</y>";

					result += (string)"<width>" + row[4] + "</width>";
					result += (string)"<height>" + row[5] + "</height>";
					result += "</frame>";
				}

				result += "</knowframes>";

			}
			else if (type==UNKNOW)
			{

				result += "<unknowframes>";
				MYSQL_ROW row;
				for (int i = 0; i < size; i++)
				{
					row = rows.at(i);
					result += "<frame>";
					result += (string)("<videoID>") + row[0] + "</videoID>";
					result += (string)("<frameID>") + row[1] + "</frameID>";
					result += (string)("<name>") + row[2] + "</name>";
					result += "</frame>";
				}
				result += "</unknowframes>";

			}
		}
		if (format == JSON)
		{
			if (type==KNOW)
			{
				result += "\"knowframes\":[";
				MYSQL_ROW row;
				for (int i = 0; i < size; i++)
				{
					result += "{";
					row = rows.at(i);
					result += (string)("\"frameID\":") + row[0] + ",";
					result += (string)("\"name\":\"") + row[1] + "\",";
					result += (string)"\"x\":" + row[2]  + ",";
					result += (string)"\"y\":" + row[3] +  ",";

					result += (string)"\"width\":" + row[4] +   ",";
					result += (string)"\"height\":"+ row[5] ;
					result += "}";
					if (i !=size -1)
						result += ",";
				}

				result += "]";

			}
			else if (type==UNKNOW)
			{
				result += "\"unknowframes\":[";
				MYSQL_ROW row;
				for (int i = 0; i < size; i++)
				{
					result += "{";
					row = rows.at(i);
					result += (string)("\"videoID\":") + row[0] + ",";
					result += (string)"\"frameID\":" + row[1]  + ",";
					result += (string)"\"name\":\"" + row[2]+"\""   ;
					result += "}";
					if (i !=size -1)
						result += ",";
				}

				result += "]";


			}

		}
		return result;
	}

void FrameGenerator::addFrameToExcludedList(vector<MYSQL_ROW>  &rows, int index)
{
	int size = rows.size();
	if (size == 0)
		return;
	MYSQL_ROW row;
	string frameID ;
	for (int i = 0; i < size; i++)
	{
		row = rows.at(i);
		frameID = row[index];
		//if (std::find(frameID_vector.begin(), frameID_vector.end(), frameID) != frameID_vector.end())
			//return ; //TODO Throw exception
		frameID_vector.push_back( frameID);
	}
}
string FrameGenerator::getNotInClause()
{
	int size = frameID_vector.size();
	//if vector is empty return empty string
	if (size == 0 )
		return "";
	string s ="";
	//else, return string in this form " (frameID_vector[0], frameID_vector[1])"
	s += "(";
	for (int i = 0; i < size; i++)
	{
		s += frameID_vector.at(i);
		if (i!=size -1)
			s += ", ";
	}
	s += ")";
	return s;
}
