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
		string fullZoneName; // will need to use this to represent the full time zone name so there is a way to differentiate between multiple stored time zones with the same abbreviation 
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

	// 12-Hour Clock Function Prototypes
	void storeTime(int, int, string, string, string);
	void deleteTime(int, int, string, string);
	bool searchTime(int, int, string, string);

	// 24-Hour Clock Function Prototypes
	void storeTime(int, int, string, string);
	void deleteTime(int, int, string);
	bool searchTime(int, int, string);

	void displayStoredTimes() const;

	int HourToUTC(int, string);
	int HourToUTCDuplicateAbbreviation(int, string);
	int MinuteToUTC(int, string);

	int convertHourUTCtoZoneHour(int, string);
	int convertHourUTCtoZoneHourDuplicateAbbreviation(int, string);
	int convertMinuteUTCtoZoneMinute(int, string);

	int setClockTypeTo12();
	int setClockTypeTo24();

	int getClockType();

	bool isEmpty();
};
#endif