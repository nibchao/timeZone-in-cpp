/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
*  Accepted time zones in this program are based on the ones listed on https://www.timeanddate.com/time/current-number-time-zones.html
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "timeMethods.h"
#include <sstream>

using namespace std;

const int MAX_TIME_ZONE_ABBREVIATION_LENGTH = 5;
const int MIN_TIME_VALUE = 0;
const int TWELVE_HOUR_CLOCK = 12;
const int TWENTY_FOUR_HOUR_CLOCK = 24;
const int MAX_MINUTE_VALUE = 60;
const int MERIDIEM_ABBREVIATION_LENGTH = 2;

int menu(int);

int validHours(int);
int validMinutes();
string validZone();

bool confirmDelete();

string validMeridiem();
int validClockType(bool);

bool noIntegersZoneName(string);

int validConvertedHour(int, int);
int validConvertedMinute(int);
string validDuplicateTimeZone(string, string);

int main()
{
	// variables to be used in program
	int menuChoice = 0;

	int hours = 0;
	int minutes = 0;
	string zoneName = "";
	string meridiem = ""; // represents AM/PM for 12 hour clock

	int hourUTC = 0;
	int minuteUTC = 0;

	int hourDesired = 0;
	int minuteDesired = 0;
	string zoneDesired = "";
	string meridiemDesired = "";

	string tempZone = "";

	int clockHourType = 0;
	//

	timeMethods time;

	do
	{
		clockHourType = time.getClockType();
		menuChoice = menu(clockHourType);

		switch (menuChoice)
		{
			case 1: // store a time
				if (time.getClockType() == TWELVE_HOUR_CLOCK)
				{
					cout << "Storing time in 12-Hour format:" << endl << endl;
					hours = validHours(time.getClockType());
					hours = validConvertedHour(hours, time.getClockType());
					cout << endl;
					minutes = validMinutes();
					cout << endl;
					meridiem = validMeridiem();
					cout << endl;
					zoneName = validZone();
					time.storeTime(hours, minutes, meridiem, zoneName);
				}
				else
				{
					cout << "Storing time in 24-Hour format:" << endl << endl;
					hours = validHours(time.getClockType());
					cout << endl;
					minutes = validMinutes();
					cout << endl;
					zoneName = validZone();
					time.storeTime(hours, minutes, zoneName);
				}
				break;
			case 2: // delete a time
				if (time.getClockType() == TWELVE_HOUR_CLOCK)
				{
					cout << endl;
					hours = validHours(time.getClockType());
					cout << endl;
					minutes = validMinutes();
					cout << endl;
					meridiem = validMeridiem();
					cout << endl;
					zoneName = validZone();
					cout << endl;
					time.deleteTime(hours, minutes, meridiem, zoneName);
				}
				else
				{
					cout << endl;
					hours = validHours(time.getClockType());
					cout << endl;
					minutes = validMinutes();
					cout << endl;
					zoneName = validZone();
					cout << endl;
					time.deleteTime(hours, minutes, zoneName);
				}
				break;
			case 3: // convert a time to another time zone
				if (time.getClockType() == TWELVE_HOUR_CLOCK)
				{
					// test 11 AM PST -> 5:00 AM AEST - case for where desired time is nearly a day ahead
					// test 11 AM PST -> 2 PM EST - case for where desired time has the opposite meridiem
					// test 4 AM PST -> 7 AM EST - case for where desired time has same meridiem
					cout << "Input the hours, minutes, meridiem (AM/PM), and time zone abbreviation of the time to convert." << endl << endl;
					hours = validHours(time.getClockType());
					cout << endl;
					minutes = validMinutes();
					cout << endl;
					meridiem = validMeridiem();
					cout << endl;
					zoneName = validZone();
					cout << endl;

					if (time.searchTime(hours, minutes, meridiem, zoneName) == true)
					{
						cout << "Input the time zone abbreviation to convert the time to:" << endl << endl;
						zoneDesired = validZone();
						tempZone = zoneDesired;

						if (zoneDesired == zoneName)
						{
							cout << "Error: Time zone to convert to is the same time zone as the stored time." << endl;
							break;
						}

						if (zoneDesired == "BST" || zoneDesired == "CST" || zoneDesired == "IST" || zoneDesired == "WST" || zoneDesired == "AMST" || zoneDesired == "GST" || zoneDesired == "ADT" || zoneDesired == "AMT" || zoneDesired == "AST" || zoneDesired == "CDT")
						{
							zoneDesired = validDuplicateTimeZone(zoneDesired, tempZone);

							hourUTC = time.HourToUTCDuplicateAbbreviation(hours, zoneName);

							hourDesired = time.convertHourUTCtoZoneHourDuplicateAbbreviation(hourUTC, zoneDesired);
							hourDesired = validConvertedHour(hourDesired, time.getClockType());

							hourUTC = validConvertedHour(hourUTC, time.getClockType());
							minuteUTC = time.MinuteToUTC(minutes, zoneName);
							minuteUTC = validConvertedMinute(minuteUTC);

							minuteDesired = time.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							if (minutes < 10 && minuteDesired < 10)
							{
								cout << hours << ":0" << minutes << " " << meridiem << " " << zoneName << " is " << hourDesired << ":0" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
							else
							{
								cout << hours << ":" << minutes << " " << meridiem << " " << zoneName << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
						}
						else
						{
							hourUTC = time.HourToUTC(hours, zoneName);

							//meridiemDesired = "PM"; need to figure out how to obtain correct meridiem post conversion

							hourDesired = time.convertHourUTCtoZoneHour(hourUTC, zoneDesired);
							hourDesired = validConvertedHour(hourDesired, time.getClockType());

							// possible idea is to treat AM as 0-11 (12:00 AM - 11:59 AM) and PM as 12-23 (12:00 PM - 11:59 PM)?
							// would have to modify the validConvertedX functions and remove the % 12/% 24 or % 60 parts

							hourUTC = validConvertedHour(hourUTC, time.getClockType());
							minuteUTC = time.MinuteToUTC(minutes, zoneName);
							minuteUTC = validConvertedMinute(minuteUTC);

							minuteDesired = time.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							if (minutes < 10 && minuteDesired < 10)
							{
								cout << hours << ":0" << minutes << " " << meridiem << " " << zoneName << " is " << hourDesired << ":0" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
							else
							{
								cout << hours << ":" << minutes << " " << meridiem << " " << zoneName << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
						}
					}
				}
				else
				{
					cout << "Enter the hours, minutes, and time zone of the time you would like to convert." << endl;
					hours = validHours(time.getClockType());
					minutes = validMinutes();
					zoneName = validZone();

					if (time.searchTime(hours, minutes, zoneName) == true)
					{
						cout << "Input the time zone abbrevation you would like to convert the time to: " << endl;
						zoneDesired = validZone();
						if (zoneDesired == zoneName)
						{
							cout << "Error: Desired time zone is the same as the stored time." << endl;
							break;
						}

						hourUTC = time.HourToUTC(hours, zoneName);
						hourUTC = validConvertedHour(hourUTC, time.getClockType());
						minuteUTC = time.MinuteToUTC(minutes, zoneName);
						minuteUTC = validConvertedMinute(minuteUTC);

						hourDesired = time.convertHourUTCtoZoneHour(hourUTC, zoneDesired);
						hourDesired = validConvertedHour(hourDesired, time.getClockType());
						minuteDesired = time.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
						minuteDesired = validConvertedMinute(minuteDesired);

						if (minutes < 10 && minuteDesired < 10)
						{
							cout << hours << ":0" << minutes << " " << zoneName << " is " << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
						}
						else
						{
							cout << hours << ":" << minutes << " " << zoneName << " is " << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
						}
					}
				}
				break;
			case 4: // display times stored
				time.displayStoredTimes();
				break;
			case 5: // choose between 12-hour clock and 24-hour clock
				clockHourType = validClockType(time.isEmpty());
				if (clockHourType == TWELVE_HOUR_CLOCK)
				{
					time.setClockTypeTo12();
				}
				else if (clockHourType == TWENTY_FOUR_HOUR_CLOCK)
				{
					time.setClockTypeTo24();
				}
				cout << endl;
				break;
			case 6: // exit
				cout << "Exiting program.";
				break;
			case 999: // destructor option
				if (confirmDelete() == true)
				{
					time.~timeMethods();
					cout << endl << "Deleted ALL stored times." << endl << endl;
				}
				else
				{
					cout << endl << "Deletion was canceled." << endl << endl;
				}
				break;
			default: // default case
				cout << endl << "Input out of bounds. Enter any key to return." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				break;
		}	
	} while (menuChoice != 6);
	return 0;
}

int menu(int clockHourType)
{
	int menuChoice = 0;

	cout << "1. Store a time" << endl;
	cout << "2. Delete a time" << endl;
	cout << "3. Convert a time to a specific time zone" << endl;
	cout << "4. Display all times stored" << endl;
	cout << "5. Select 12-Hour Clock or 24-Hour Clock (Currently set to: " << clockHourType << ")" << endl;
	cout << "6. Exit" << endl;
	cout << "999. DELETE ALL STORED TIMES" << endl << endl;

	cout << "Enter your input: ";
	cin >> menuChoice;
	cin.clear();
	cin.ignore(10000, '\n');
	return menuChoice;
}

int validHours(int clockHourType)
{
	int hours = 0;
	string str = "";

	cout << "Enter hours: ";

	if (clockHourType == TWELVE_HOUR_CLOCK)
	{
		while (getline(cin, str))
		{
			stringstream stream(str);
			if (stream >> hours)
			{
				if (stream.eof() && hours > MIN_TIME_VALUE && hours <= clockHourType)
				{
					break;
				}
			}
			cout << endl << "Error: A zero/negative hour value was found, a non-integer was found, or hour value was greater than " << clockHourType << "." << endl;
			cout << endl << "Enter hours: ";
		}
	}
	else
	{
		while (getline(cin, str))
		{
			stringstream stream(str);
			if (stream >> hours)
			{
				if (stream.eof() && hours >= MIN_TIME_VALUE && hours <= clockHourType)
				{
					break;
				}
			}
			cout << endl << "Error: A zero/negative hour value was found, a non-integer was found, or hour value was greater than " << clockHourType << "." << endl;
			cout << endl << "Enter hours: ";
		}
	}
	return hours;
}

int validMinutes()
{
	int minutes = 0;
	string str = "";

	cout << "Enter minutes: ";
	
	while (getline(cin, str))
	{
		stringstream stream(str);
		if (stream >> minutes)
		{
			if (stream.eof() && minutes >= MIN_TIME_VALUE && minutes < MAX_MINUTE_VALUE)
			{
				break;
			}
		}
		cout << endl << "Error: A negative minute value was found, a non-integer was found, or minutes value was greater than or equal to " << MAX_MINUTE_VALUE << "." << endl;
		cout << endl << "Enter minutes: ";
	}
	return minutes;
}

string validZone()
{
	string zoneName = "";
	cout << "Enter time zone abbreviation: ";
	getline(cin, zoneName);

	while (zoneName == "" || zoneName.find_first_not_of(' ') || zoneName.length() > MAX_TIME_ZONE_ABBREVIATION_LENGTH || noIntegersZoneName(zoneName) == false)
	{
		cout << endl << "Error: Time zone name is too long (maximum of 5 characters), blank characters were found, or integers were found." << endl;
		cout << endl << "Enter time zone abbrevation: ";
		getline(cin, zoneName);
	}
	transform(zoneName.begin(), zoneName.end(), zoneName.begin(), ::toupper);
	return zoneName;
}

bool confirmDelete()
{
	int response = 0;
	cout << "Enter '1' to confirm deletion." << endl;
	cout << "Enter anything else to cancel deletion." << endl;
	cin >> response;
	cin.clear();
	cin.ignore(10000, '\n');

	if (response == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string validMeridiem()
{
	string meridiem = "";
	cout << "Enter AM or PM: ";
	getline(cin, meridiem);
	transform(meridiem.begin(), meridiem.end(), meridiem.begin(), ::toupper);

	while (meridiem == "" || meridiem.find_first_not_of(' ') || meridiem.length() > MERIDIEM_ABBREVIATION_LENGTH || (meridiem != "AM" && meridiem != "PM"))
	{
		cout << endl << "Error: Input contained blank characters, was too long, or was not an accepted input (AM or PM)." << endl;
		cout << endl << "Enter AM or PM: ";
		getline(cin, meridiem);
		transform(meridiem.begin(), meridiem.end(), meridiem.begin(), ::toupper);
	}
	return meridiem;
}

int validClockType(bool empty)
{
	int clockHourType = 0;

	if (empty == true)
	{
		cout << "Enter '12' to select the 12-Hour clock type or enter '24' to select the 24-Hour clock type." << endl;
		cin >> clockHourType;
		cin.clear();
		cin.ignore(10000, '\n');

		while (clockHourType != TWELVE_HOUR_CLOCK && clockHourType != TWENTY_FOUR_HOUR_CLOCK)
		{
			cout << endl << "Error: Input was not an accepted input (12 or 24)." << endl;
			cout << "Enter '12' to select the 12-Hour clock type or enter '24' to select the 24-Hour clock type." << endl;
			cin >> clockHourType;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	else
	{
		cout << "Error: Stored times were found so clock type cannot be changed until all stored times are deleted." << endl;
	}
	return clockHourType;
}

int validConvertedHour(int hours, int clockHourType)
{
	if (clockHourType == TWELVE_HOUR_CLOCK)
	{
		if (hours < 0) // check if hours is negative first
		{
			hours = hours * -1;
		}
		if (hours == 0) // check if hours is 0
		{
			hours = 12;
		}
		if (hours > 12) // check if hours is greater than 12
		{
			hours = hours % 12;
		}
		if (hours == 0) // check if hours is 0 again
		{
			hours = 12;
		}
	}
	else
	{
		if (hours < 0) // check if hours is negative first
		{
			hours = hours * -1;
		}
		if (hours == 24)
		{
			hours = 0;
		}
		if (hours > 24) // check if hours is greater than 24
		{
			hours = hours % 24;
		}
		if (hours == 24)
		{
			hours = 0;
		}
	}
	return hours;
}

int validConvertedMinute(int minutes)
{
	if (minutes < 0) // check if minutes is negative first
	{
		minutes = minutes * -1;
	}
	if (minutes > 60) // check if minutes is greater than 60
	{
		minutes = minutes % 60;
	}
	return minutes;
}

bool noIntegersZoneName(string str)
{
	if (none_of(str.begin(), str.end(), [](unsigned char c) {return isdigit(c); }))
	{
		return true;
	}
	return false;
}

string validDuplicateTimeZone(string zoneDesired, string tempZone)
{
	int zoneDesiredLength = 0;

	cout << endl << "Multiple time zones found with " << tempZone << " abbreviation." << endl << endl;
	cout << "Enter the full time zone name for " << tempZone << ": ";
	getline(cin, zoneDesired);
	transform(zoneDesired.begin(), zoneDesired.end(), zoneDesired.begin(), ::tolower);
	zoneDesiredLength = zoneDesired.length();
	for (int cnt = 0; cnt < zoneDesiredLength; cnt++)
	{
		if (cnt == 0)
		{
			zoneDesired[cnt] = toupper(zoneDesired[cnt]);
		}
		else if (zoneDesired[cnt - 1] == ' ')
		{
			zoneDesired[cnt] = toupper(zoneDesired[cnt]);
		}
	}

	while (zoneDesired == "" || zoneDesired.find_first_not_of(' ') || noIntegersZoneName(zoneDesired) == false
			|| (zoneDesired != "West Samoa Time" && zoneDesired != "Bougainville Standard Time" && zoneDesired != "China Standard Time" && zoneDesired != "Bangladesh Standard Time" && zoneDesired != "India Standard Time" && zoneDesired != "Armenia Summer Time"
			&& zoneDesired != "Gulf Standard Time" && zoneDesired != "Arabia Daylight Time" && zoneDesired != "Armenia Time" && zoneDesired != "Arabia Standard Time" && zoneDesired != "Israel Standard Time" && zoneDesired != "British Summer Time"
			&& zoneDesired != "Irish Standard Time" && zoneDesired != "Western Sahara Summer Time" && zoneDesired != "South Georgia Time" && zoneDesired != "Atlantic Daylight Time" && zoneDesired != "Amazon Summer Time" && zoneDesired != "Amazon Time"
			&& zoneDesired != "Atlantic Standard Time" && zoneDesired != "Cuba Daylight Time" && zoneDesired != "Central Daylight Time" && zoneDesired != "Cuba Standard Time" && zoneDesired != "Central Standard Time"))
	{
		cout << endl << "Error: Time zone name does not exist, blank characters were found, or integers were found." << endl;
		cout << endl << "Enter the full time zone name for " << tempZone << ": ";
		getline(cin, zoneDesired);
		transform(zoneDesired.begin(), zoneDesired.end(), zoneDesired.begin(), ::tolower);
		zoneDesiredLength = zoneDesired.length();
		for (int cnt = 0; cnt < zoneDesiredLength; cnt++)
		{
			if (cnt == 0)
			{
				zoneDesired[cnt] = toupper(zoneDesired[cnt]);
			}
			else if (zoneDesired[cnt - 1] == ' ')
			{
				zoneDesired[cnt] = toupper(zoneDesired[cnt]);
			}
		}
	}
	return zoneDesired;
}
