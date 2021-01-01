/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
*  Accepted time zones in this program are based on the ones listed on https://www.timeanddate.com/time/current-number-time-zones.html
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

	Node* head;
	int clockType;

public:
	timeMethods()
	{
		head = nullptr;
		clockType = 12;
	}

	~timeMethods();

	void storeTime(int, int, string, string);
	void storeTime(int, int, string);

	void deleteTime(int, int, string, string);
	void deleteTime(int, int, string);

	void displayStoredTimes() const;

	bool searchTime(int, int, string, string);
	bool searchTime(int, int, string);

	int HourToUTC(int, string);
	int MinuteToUTC(int, string);

	int convertHourUTCtoZoneHour(int, string);
	int convertMinuteUTCtoZoneMinute(int, string);

	int setClockTypeTo12();
	int setClockTypeTo24();

	int getClockType();

	bool isEmpty();
};
#endif