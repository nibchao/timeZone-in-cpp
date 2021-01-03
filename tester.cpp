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

int menu(int);
int validHours(int);
int validMinutes();
string validZone();
bool confirmDelete();
string validMeridiem();
int validClockType(bool);

bool noIntegersZoneName(string);

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

	string tempZone = "";
	int zoneDesiredLength = 0;

	int clockHourType = 0;
	//

	timeMethods time;

	do
	{
		clockHourType = time.getClockType();
		response = menu(clockHourType);

		switch (response)
		{
		case 1: // store a time
			if (time.getClockType() == TWELVE_HOUR_CLOCK)
			{
				cout << "Storing time in 12-Hour format:" << endl;
				hours = validHours(time.getClockType());
				hours = validConvertedHour(hours, time.getClockType());
				minutes = validMinutes();
				meridiem = validMeridiem();
				zoneName = validZone();
				time.storeTime(hours, minutes, meridiem, zoneName);
			}
			else
			{
				cout << "Storing time in 24-Hour format:" << endl;
				hours = validHours(time.getClockType());
				minutes = validMinutes();
				zoneName = validZone();
				time.storeTime(hours, minutes, zoneName);
			}
			break;
		case 2: // delete a time
			if (time.getClockType() == TWELVE_HOUR_CLOCK)
			{
				hours = validHours(time.getClockType());
				minutes = validMinutes();
				meridiem = validMeridiem();
				zoneName = validZone();
				time.deleteTime(hours, minutes, meridiem, zoneName);
			}
			else
			{
				hours = validHours(time.getClockType());
				minutes = validMinutes();
				zoneName = validZone();
				time.deleteTime(hours, minutes, zoneName);
			}
			break;
		case 3: // convert a time to another time zone
			if (time.getClockType() == TWELVE_HOUR_CLOCK)
			{
				cout << "Enter the hours, minutes, AM/PM, and time zone of the time you would like to convert." << endl;
				hours = validHours(time.getClockType());
				minutes = validMinutes();
				meridiem = validMeridiem();
				zoneName = validZone();

				if (time.searchTime(hours, minutes, meridiem, zoneName) == true)
				{
					cout << "Input the time zone abbreviation you would like to convert the time to: " << endl;
					zoneDesired = validZone();
					tempZone = zoneDesired;
					if (zoneDesired == zoneName)
					{
						cout << "Error: Desired time zone is the same as the stored time." << endl;
						break;
					}

					// need to figure out how to move this large if-statement into separate function
					if (zoneDesired == "BST" || zoneDesired == "CST" || zoneDesired == "IST" || zoneDesired == "WST" || zoneDesired == "AMST" || zoneDesired == "GST" || zoneDesired == "ADT" || zoneDesired == "AMT" || zoneDesired == "AST" || zoneDesired == "CDT")
					{
						cout << endl << "Multiple time zones found with " << tempZone << " as time zone abbreviation." << endl;
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

						while (zoneDesired == "" || zoneDesired.find_first_not_of(' ') || noIntegersZoneName(zoneDesired) == false 
							|| (zoneDesired != "West Samoa Time" 
							&& zoneDesired != "Bougainville Standard Time" 
							&& zoneDesired != "China Standard Time" 
							&& zoneDesired != "Bangladesh Standard Time" 
							&& zoneDesired != "India Standard Time" 
							&& zoneDesired != "Armenia Summer Time"
							&& zoneDesired != "Gulf Standard Time"
							&& zoneDesired != "Arabia Daylight Time"
							&& zoneDesired != "Armenia Time"
							&& zoneDesired != "Arabia Standard Time"
							&& zoneDesired != "Israel Standard Time"
							&& zoneDesired != "British Summer Time"
							&& zoneDesired != "Irish Standard Time"
							&& zoneDesired != "Western Sahara Summer Time"
							&& zoneDesired != "South Georgia Time"
							&& zoneDesired != "Atlantic Daylight Time"
							&& zoneDesired != "Amazon Summer Time"
							&& zoneDesired != "Amazon Time"
							&& zoneDesired != "Atlantic Standard Time"
							&& zoneDesired != "Cuba Daylight Time"
							&& zoneDesired != "Central Daylight Time"
							&& zoneDesired != "Cuba Standard Time"
							&& zoneDesired != "Central Standard Time"))
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
						// reminder to use duplicate versions of functions // cout << time.HourToUTCDuplicateAbbreviation(hours, zoneDesired);
						break; // need to make a copy of code below except use the 'DuplicateAbbreviation' version of the functions
					}

					hourUTC = time.HourToUTC(hours, zoneName);

					hourDesired = time.convertHourUTCtoZoneHour(hourUTC, zoneDesired);

					// maybe need to split HourToUTC into two functions and convertHourUTCtoZoneHour into two functions - ones that subtract to get to UTC (ahead of UTC) and ones that add to get to UTC (behind UTC)
					// then based on which version of the functions are called, use a corresponding if-statement below using some arbitrary value to differ between the two types of if-statements
					// this idea kind of links back to my comments in timeMethods.cpp where a question should be asked about to figure out where the converted time zone will be to

					if (hourUTC > hourDesired) // this case only works when the time to be converted is > 12 such as 11 AM PST -> 5 AM AEST
					//if (hours > hourDesired) // this case only works when the time to be converted is < 12 such as 4 AM PST -> 7 AM EST
					{
						meridiemDesired = "PM";
					}
					else
					{
						meridiemDesired = "AM";
					}

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

int menu(int clockHourType)
{
	int response = 0;

	cout << "1. Store a time" << endl;
	cout << "2. Delete a time" << endl;
	cout << "3. Convert a time to a specific time zone" << endl;
	cout << "4. Display all times stored" << endl;
	cout << "5. Select 12-Hour Clock or 24-Hour Clock (Currently set to: " << clockHourType << ")" << endl;
	cout << "6. Exit" << endl;
	cout << "10. DELETE ALL STORED TIMES" << endl << endl;

	cout << "Enter your input: ";
	cin >> response;
	cin.clear();
	cin.ignore(10000, '\n');
	return response;
}

// need to add validation for when user inputs a value higher than 12 (if on 12-Hour Clock Type) or 24 (if on 24-Hour Clock Type)
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
				if (stream.eof() && hours > MIN_TIME_VALUE)
				{
					break;
				}
			}
			cout << endl << "Error: A zero or negative hour value was found or a non-integer was found in input." << endl;
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
				if (stream.eof() && hours >= MIN_TIME_VALUE)
				{
					break;
				}
			}
			cout << endl << "Error: A negative hour value was found or non-integers were found." << endl;
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
			if (stream.eof() && minutes >= MIN_TIME_VALUE)
			{
				break;
			}
		}
		cout << endl << "Error: A negative minute value was found or non-integers were found." << endl;
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
		cout << "There were stored times found so the clock type cannot be changed until all stored times are deleted." << endl;
	}
	return clockHourType;
}

// used when validating converted hour to UTC
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

bool noIntegersZoneName(string str)
{
	if (none_of(str.begin(), str.end(), [](unsigned char c) {return isdigit(c); }))
	{
		return true;
	}
	return false;
}