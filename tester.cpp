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

int main()
{
	// initial values for variables used in program
	int response = 0;
	int hours = 0;
	int minutes = 0;
	string zoneName = "";

	int hourUTC = 0;
	int minuteUTC = 0;

	int hourDesired = 0;
	int minuteDesired = 0;
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
			zoneName = validZone();
			time.storeTime(hours, minutes, zoneName);
			break;
		case 2: // delete a time
			time.deleteTime(hours, minutes, zoneName); // temporary
			break;
		case 3: // convert a time to another time zone

			// add a function that asks user to input time they want to convert and search for nodes in the list to see if it exists; if so, runs necessary functions
			// one condition is check if head is nullptr and return no times found in list
			// make a separate string to represent the desired time zone and replace the second zoneName in the cout statement below
			// add necessary checks/validation of input wherever needed


			// need to add a check for if the time exists or if converting is possible (maybe check if head is still nullptr?)
			hourUTC = time.HourToUTC(hours, zoneName);
			minuteUTC = time.MinuteToUTC(minutes, zoneName);
			hourDesired = time.convertHourUTCtoZoneHour(hourUTC, zoneName);
			minuteDesired = time.convertMinuteUTCtoZoneMinute(minuteUTC, zoneName);

			cout << hours << ":" << minutes << " in " << zoneName << " is " << hourDesired << ":" << minuteDesired << " " << zoneName << endl << endl;

			// also need to check if hour when converted to UTC is greater than 12 or a negative hour value
			// same with if minute converted to UTC is greater than 60 or a negative minute value

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