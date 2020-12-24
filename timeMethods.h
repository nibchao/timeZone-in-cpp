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

	void storeTime(int, int, string);
	void deleteTime(int, int, string);
	void displayStoredTimes() const;

	int HourToUTC(int, string);
	int MinuteToUTC(int, string);
	int convertHourUTCtoZoneHour(int, string);
	int convertMinuteUTCtoZoneMinute(int, string);
};
#endif