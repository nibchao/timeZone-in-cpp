/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
*/

#ifndef TIMEMETHODS_H
#define TIMEMETHODS_H

#include <string>

using namespace std;

class timeMethods
{
private:
	struct Node
	{
		int hour;
		int minute;
		string zone;
		string meridiem;
		Node* next;
	};

	int nodeCount = 0;
	Node* head;

public:
	timeMethods()
	{
		nodeCount = 0;
		head = nullptr;
	}

	~timeMethods();

	void storeTime(int, int, string, string);
	void deleteTime(int, int, string, string);
	void displayStoredTimes() const;
	bool searchTime(int, int, string, string);

	int HourToUTC(int, string);
	int MinuteToUTC(int, string);
	int convertHourUTCtoZoneHour(int, string);
	int convertMinuteUTCtoZoneMinute(int, string);
};
#endif