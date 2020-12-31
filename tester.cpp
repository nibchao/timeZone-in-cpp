/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
*  Accepted time zones in this program are based on the ones listed on https://www.timeanddate.com/time/current-number-time-zones.html
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "timeMethods.h"

using namespace std;

const int MAX_TIME_ZONE_ABBREVIATION_LENGTH = 5;
const int MIN_TIME_VALUE = 0;

int menu();
int validHours();
int validMinutes();
string validZone();
bool confirmDelete();
string validMeridiem();
int validClockType();

int validConvertedHour(int, int);
string validConvertedHour(int, string);
int validConvertedMinute(int);

int main()
{
	// initial values for variables used in program
	int response = 0;
	int hours = 0;
	int minutes = 0;
	string zoneName = "";
	string meridiem = ""; // used to represent the AM/PM for a 12 hour clock

	int hourUTC = 0;
	int minuteUTC = 0;

	int hourDesired = 0;
	int minuteDesired = 0;
	string zoneDesired = "";
	string meridiemDesired = "";

	int clockHourType = 0;
	//

	timeMethods time;

	do
	{
		response = menu();
		switch (response)
		{
		case 1: // store a time
			if (time.getClockType() == 12)
			{
				cout << "Storing time in 12-Hour format:" << endl;
				hours = validHours();
				minutes = validMinutes();
				meridiem = validMeridiem();
				zoneName = validZone();
				time.storeTime(hours, minutes, meridiem, zoneName);
			}
			else
			{
				cout << "Storing time in 24-Hour format:" << endl;
				hours = validHours();
				minutes = validMinutes();
				zoneName = validZone();
				time.storeTime(hours, minutes, zoneName);
			}
			break;
		case 2: // delete a time
			if (time.getClockType() == 12)
			{
				hours = validHours();
				minutes = validMinutes();
				meridiem = validMeridiem();
				zoneName = validZone();
				time.deleteTime(hours, minutes, meridiem, zoneName);
			}
			else
			{
				hours = validHours();
				minutes = validMinutes();
				zoneName = validZone();
				time.deleteTime(hours, minutes, zoneName);
			}
			break;
		case 3: // convert a time to another time zone
			if (time.getClockType() == 12)
			{
				cout << "Enter the hours, minutes, AM/PM, and time zone of the time you would like to convert." << endl;
				hours = validHours();
				minutes = validMinutes();
				meridiem = validMeridiem();
				zoneName = validZone();

				if (time.searchTime(hours, minutes, meridiem, zoneName) == true)
				{
					cout << "Input the time zone abbrevation you would like to convert the time to: " << endl;
					zoneDesired = validZone();
					if (zoneDesired == zoneName)
					{
						cout << "Error: Desired time zone is the same as the stored time." << endl;
						break;
					}

					// maybe make a third method (maybe overload HourToUTC) and its purpose is to return the UTC meridiem which is then used as the meridiemDesired/meridiem ? not sure
					// below example assumes 11:00 AM PST want to convert to 2:00 PM EST
					hourUTC = time.HourToUTC(hours, zoneName); // 11 PST -> 7 UTC
					hourUTC = validConvertedHour(hourUTC, time.getClockType()); // yes, hourUTC is a valid hour value
					minuteUTC = time.MinuteToUTC(minutes, zoneName); // 00 PST -> 00 UTC
					minuteUTC = validConvertedMinute(minuteUTC); // yes, minuteUTC is a valid minute value

					hourDesired = time.convertHourUTCtoZoneHour(hourUTC, zoneDesired); // 7 UTC -> 2 EST


					meridiemDesired = validConvertedHour(hourDesired, meridiem); // returns 'meridiemDesired' which is equal to 'meridiem' which has a value of 'AM' because hourDesired (2) fails all of the if-statements 


					hourDesired = validConvertedHour(hourDesired, time.getClockType()); // yes, hourDesired is a valid hour value
					minuteDesired = time.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired); // 00 UTC -> 00 EST
					minuteDesired = validConvertedMinute(minuteDesired); // yes, minuteDesired is a valid minute value

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
			else
			{
				cout << "Enter the hours, minutes, and time zone of the time you would like to convert." << endl;
				hours = validHours();
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
			cout << endl << "Displaying the stored times:" << endl;
			time.displayStoredTimes();
			cout << endl;
			break;
		case 5: // choose between 12-hour clock and 24-hour clock
			clockHourType = validClockType();
			if (clockHourType == 12)
			{
				time.setClockTypeTo12();
			}
			else
			{
				time.setClockTypeTo24();
			}
			cout << endl;
			break;
		case 6: // exit
			cout << "Exiting program.";
			break;
		case 10: // destructor option
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
	} while (response != 6);
	return 0;
}

int menu()
{
	int response = 0;

	cout << "1. Store a time" << endl;
	cout << "2. Delete a time" << endl;
	cout << "3. Convert a time to a specific time zone" << endl;
	cout << "4. Display all times stored" << endl;
	cout << "5. Select 12-Hour Clock or 24-Hour Clock (DEFAULT: 12-HOUR CLOCK)" << endl;
	cout << "6. Exit" << endl;
	cout << "10. DELETE ALL STORED TIMES" << endl;

	cout << endl << "Enter your input: ";
	cin >> response;
	cin.clear();
	cin.ignore(10000, '\n');
	return response;
}

int validHours()
{
	int hours = 0;
	cout << "Enter hours: ";
	cin >> hours;
	cin.clear();
	cin.ignore(10000, '\n');

	while (hours < MIN_TIME_VALUE)
	{
		cout << endl << "Error: A negative value was found for hours. No negative time values allowed." << endl;
		cout << endl << "Enter hours: ";
		cin >> hours;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return hours;
}

int validMinutes()
{
	int minutes = 0;
	cout << "Enter minutes: ";
	cin >> minutes;
	cin.clear();
	cin.ignore(10000, '\n');

	while (minutes < MIN_TIME_VALUE)
	{
		cout << endl << "Error: A negative value was found for minutes. No negative time values allowed." << endl;
		cout << endl << "Enter minutes: ";
		cin >> minutes;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return minutes;
}

string validZone()
{
	string zoneName = "";
	cout << "Enter time zone abbreviation: ";
	getline(cin, zoneName);

	// NEED TO ADD VALIDATION AND ACCEPT ONLY LETTERS; INTEGERS ARE ACCEPTED WHEN THEY SHOULDN'T, maybe look at first letter of all time zones checked in timeMethods.cpp and check for it in the first position of user input below?

	while (zoneName == "" || zoneName.find_first_not_of(' ') || zoneName.length() > MAX_TIME_ZONE_ABBREVIATION_LENGTH)
	{
		cout << endl << "Error: Time zone name is too long (maximum of 5 characters) or blank characters were found." << endl;
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
	cout << "Enter AM or PM on the 12-hour clock: ";
	getline(cin, meridiem);
	transform(meridiem.begin(), meridiem.end(), meridiem.begin(), ::toupper);

	while (meridiem == "" || meridiem.find_first_not_of(' ') || meridiem.length() > 2 || (meridiem != "AM" && meridiem != "PM"))
	{
		cout << endl << "Error: Input contained blank characters, was too long, or was not an accepted input (AM or PM)." << endl;
		cout << endl << "Enter AM or PM on the 12-hour clock: ";
		getline(cin, meridiem);
		transform(meridiem.begin(), meridiem.end(), meridiem.begin(), ::toupper);
	}
	return meridiem;
}

// NEED TO ADD VALIDATION FOR WHERE THIS CANNOT BE DONE IF A STORED TIME WAS FOUND - EXAMPLE IF I STORED A TIME IN 12-HOUR TYPE AND THEN WANTED TO SWITCH TO 24-HOUR TYPE; THIS SHOULD NOT BE ALLOWED UNLESS THE STORED TIME IS REMOVED OR DESTRUCTOR IS USED
int validClockType()
{
	int clockHourType = 0;

	cout << "Enter '12' to select the 12-Hour clock type or enter '24' to select the 24-Hour clock type." << endl;
	cin >> clockHourType;
	cin.clear();
	cin.ignore(10000, '\n');

	while (clockHourType != 12 && clockHourType != 24)
	{
		cout << endl << "Error: Input was not a valid input (12 or 24)." << endl;
		cout << "Enter 12 to choose 12-hour clock type" << endl;
		cout << "Enter 24 to choose 24-hour clock type" << endl;
		cin >> clockHourType;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return clockHourType;
}

// used when validating converted hour to UTC
int validConvertedHour(int hours, int clockHourType)
{
	if (clockHourType == 12)
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

// this does not work as intended - example is converting 11 AM PST to EST gives 2 AM EST

// used when validating converted hour to desired time zone
string validConvertedHour(int hours, string meridiemDesired) // overloaded function of validConvertedHour
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
		meridiemDesired = "PM";
	}
	if (hours == 0) // check if hours is 0 again
	{
		hours = 12;
		meridiemDesired = "AM";
	}
	return meridiemDesired;
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