/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
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
	//

	timeMethods time;

	do
	{
		response = menu();
		switch (response)
		{
		case 1: // store a time
			hours = validHours();
			minutes = validMinutes();
			meridiem = validMeridiem();
			zoneName = validZone();
			time.storeTime(hours, minutes, meridiem, zoneName);
			break;
		case 2: // delete a time
			//time.deleteTime(hours, minutes, zoneName); // temporary
			break;
		case 3: // convert a time to another time zone

			// add validation to every area that requires user input and move everything into separate functions

			cout << "Enter the hours, minutes, AM/PM, and time zone of the time you would like to convert." << endl;
			cout << "The hours: ";
			cin >> hours;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << endl << "The minutes: ";
			cin >> minutes;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << endl << "AM or PM: ";
			getline(cin, meridiem);
			transform(meridiem.begin(), meridiem.end(), meridiem.begin(), ::toupper);
			cout << endl << "The time zone abbreviation: ";
			getline(cin, zoneName);
			transform(zoneName.begin(), zoneName.end(), zoneName.begin(), ::toupper);

			cout << "Starting search for the specified time in the list of stored times." << endl;
			if (time.searchTime(hours, minutes, meridiem, zoneName) == true)
			{
				cout << "Input the time zone abbrevation you would like to convert the time to: " << endl;
				zoneDesired = validZone();
				if (zoneDesired == zoneName)
				{
					cout << "Error: Desired time zone is the same as the stored time." << endl;
					break;
				}
				hourUTC = time.HourToUTC(hours, zoneName);
				if (hourUTC < 0) // check if hourUTC is negative first
				{
					hourUTC = hourUTC * -1;
				}
				if (hourUTC == 0) // check if hourUTC is 0
				{
					hourUTC = 12;
				}
				if (hourUTC > 12) // check if hourUTC is greater than 12
				{
					hourUTC = hourUTC % 12;
				}
				if (hourUTC == 0) // check if hourUTC is 0 again
				{
					hourUTC = 12;
				}
				minuteUTC = time.MinuteToUTC(minutes, zoneName);
				if (minuteUTC < 0) // check if minuteUTC is negative first
				{
					minuteUTC = minuteUTC * -1;
				}
				if (minuteUTC > 60) // check if minuteUTC is greater than 60
				{
					minuteUTC = hourUTC % 60;
				}
				hourDesired = time.convertHourUTCtoZoneHour(hourUTC, zoneDesired);
				if (hourDesired < 0) // check if hourDesired is negative first
				{
					hourDesired = hourDesired * -1;
				}
				if (hourDesired == 0) // check if hourDesired is 0
				{
					hourDesired = 12;
					meridiemDesired = "AM";
				}
				meridiemDesired = "AM";
				if (hourDesired > 12) // check if hourDesired is greater than 12
				{
					hourDesired = hourDesired % 12;
					meridiemDesired = "PM";
				}
				if (hourDesired == 0) // check if hourDesired is 0 again
				{
					hourDesired = 12;
					meridiemDesired = "AM";
				}
				minuteDesired = time.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
				if (minuteDesired < 0) // check if minuteDesired is negative first
				{
					minuteDesired = minuteDesired * -1;
				}
				if (minuteDesired > 60) // check if minuteDesired is greater than 60
				{
					minuteDesired = minuteDesired % 60;
				}
				//cout << hours << ":" << minutes << " in " << zoneName << " is " << hourUTC << ":" << minuteUTC << " " << zoneDesired << endl << endl; // testing UTC converter function
				cout << hours << ":" << minutes << " " << meridiem << " " << zoneName << " in " << zoneDesired << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
			}
			else
			{
				break;
			}
			break;
		case 4: // display times stored
			cout << endl << "Displaying the stored times:" << endl;
			time.displayStoredTimes();
			cout << endl;
			break;
		case 5: // exit
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
	} while (response != 5);
	return 0;
}

int menu()
{
	int response = 0;

	cout << "1. Store a time" << endl;
	cout << "2. Delete a time" << endl;
	cout << "3. Convert a time to a specific time zone" << endl;
	cout << "4. Display all times stored" << endl;
	cout << "5. Exit" << endl;
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