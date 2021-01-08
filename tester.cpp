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

const int TWELVE_HOUR_CLOCK = 12;
const int TWENTY_FOUR_HOUR_CLOCK = 24;

const int MIN_TIME_VALUE = 0;
const int MAX_MINUTE_VALUE = 60;

const int MAX_ZONE_ABBREVIATION_LENGTH = 5;
const int MERIDIEM_ABBREVIATION_LENGTH = 2;

// function prototypes
int displayMenu(int);

int validHourInput(int);
int validMinuteInput();
string validZoneInput();
string validMeridiemInput();

int validClockType(bool);

bool noIntegersInZoneName(string);

int validConvertedHour(int, int);
int validConvertedMinute(int);
string validDuplicateTimeZone(string, string);

void formatTwentyFourHourClockOutput(int, int, string, int, int, string);
//

int main()
{
	// variables to be used in program
	int menuChoice = 0;

	int hourInput = 0;
	int minuteInput = 0;
	string zoneInput = "";
	string meridiemInput = ""; // represents AM/PM for 12 hour clock

	int hourUTC = 0;
	int minuteUTC = 0;

	int hourDesired = 0;
	int minuteDesired = 0;
	string zoneDesired = "";
	string meridiemDesired = "";

	string tempZoneInput = "";

	int clockType = 0;
	//

	int tempHourUTC = 0;
	int tempHourDesired = 0;
	int tempHourDesiredUTC = 0;

	timeMethods timeMethods;

	do
	{
		clockType = timeMethods.getClockType();
		menuChoice = displayMenu(clockType);

		switch (menuChoice)
		{
			case 1: // store a time
				if (timeMethods.getClockType() == TWELVE_HOUR_CLOCK)
				{
					cout << "Storing time in " << clockType << "-Hour Clock Type:" << endl << endl;

					hourInput = validHourInput(timeMethods.getClockType());
					hourInput = validConvertedHour(hourInput, timeMethods.getClockType());

					minuteInput = validMinuteInput();
					meridiemInput = validMeridiemInput();
					zoneInput = validZoneInput();

					timeMethods.storeTime(hourInput, minuteInput, meridiemInput, zoneInput);
				}
				else
				{
					cout << "Storing time in " << clockType << "-Hour Clock Type:" << endl << endl;

					hourInput = validHourInput(timeMethods.getClockType());
					minuteInput = validMinuteInput();
					zoneInput = validZoneInput();

					timeMethods.storeTime(hourInput, minuteInput, zoneInput);
				}
				break;
			case 2: // delete a time
				if (timeMethods.getClockType() == TWELVE_HOUR_CLOCK)
				{
					cout << endl;
					hourInput = validHourInput(timeMethods.getClockType());
					minuteInput = validMinuteInput();
					meridiemInput = validMeridiemInput();
					zoneInput = validZoneInput();

					timeMethods.deleteTime(hourInput, minuteInput, meridiemInput, zoneInput);
				}
				else
				{
					cout << endl;
					hourInput = validHourInput(timeMethods.getClockType());
					minuteInput = validMinuteInput();
					zoneInput = validZoneInput();

					timeMethods.deleteTime(hourInput, minuteInput, zoneInput);
				}
				break;
			case 3: // convert a time to another time zone
				if (timeMethods.getClockType() == TWELVE_HOUR_CLOCK) // 12-Hour Clock Case
				{
					// test 11 AM PST -> 5:00 AM AEST - case for where desired time is nearly a day ahead
					// test 11 AM PST -> 2 PM EST - case for where desired time has the opposite meridiem @@@@@@@@@@@@@@@@@@@ this case fails
					// test 4 AM PST -> 7 AM EST - case for where desired time has same meridiem
					cout << "Input the hours, minutes, meridiem (AM/PM), and time zone abbreviation of the time to convert." << endl << endl;
					hourInput = validHourInput(timeMethods.getClockType());
					minuteInput = validMinuteInput();
					meridiemInput = validMeridiemInput();
					zoneInput = validZoneInput();

					if (timeMethods.searchTime(hourInput, minuteInput, meridiemInput, zoneInput) == true)
					{
						cout << "Input the time zone abbreviation to convert the time to:" << endl << endl;
						zoneDesired = validZoneInput();
						tempZoneInput = zoneDesired;

						if (zoneDesired == zoneInput)
						{
							cout << "Error: Desired time zone is the same time zone as the stored time! Returning to menu." << endl;
							break;
						}

						if (zoneDesired == "BST" || zoneDesired == "CST" || zoneDesired == "IST" || zoneDesired == "WST" || zoneDesired == "AMST" || zoneDesired == "GST" || zoneDesired == "ADT" || zoneDesired == "AMT" || zoneDesired == "AST" || zoneDesired == "CDT") // Duplicate Zone Abbreviation Case - need to add meridiem fix
						{
							zoneDesired = validDuplicateTimeZone(zoneDesired, tempZoneInput);

							hourUTC = timeMethods.HourToUTCDuplicateAbbreviation(hourInput, zoneInput);

							hourDesired = timeMethods.convertHourUTCtoZoneHourDuplicateAbbreviation(hourUTC, zoneDesired);
							hourDesired = validConvertedHour(hourDesired, timeMethods.getClockType());

							hourUTC = validConvertedHour(hourUTC, timeMethods.getClockType());
							minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInput);
							minuteUTC = validConvertedMinute(minuteUTC);

							minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							if (minuteInput < 10 && minuteDesired < 10)
							{
								cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":0" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
							else
							{
								cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
						}
						else // Every Other Time Zone - need to make meridiem fix here
						{
							// possible idea is to treat AM as 0-11 (12:00 AM - 11:59 AM) and PM as 12-23 (12:00 PM - 11:59 PM)?
							// would have to modify the validConvertedX functions and remove the % 12/% 24 or % 60 parts

							// original ordering of code
							// convert hour to UTC, validate the UTC hours; convert minute to UTC, validate the UTC minutes
							// use the validated UTC hours to convert to the time zone; validate the new time zone hours; use the validated UTC minutes to convert to the zome zone; validate the new time zone minutes
							// print and format the newly converted time
							hourUTC = timeMethods.HourToUTC(hourInput, zoneInput);

							tempHourUTC = hourUTC; // assuming 11 AM PST, tempHourUTC = 19

							//hourDesired = timeMethods.convertHourUTCtoZoneHour(hourUTC, zoneDesired);
							//tempHourDesired = hourDesired;

							hourUTC = validConvertedHour(hourUTC, timeMethods.getClockType()); // hourUTC = 7 now
							minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInput);
							minuteUTC = validConvertedMinute(minuteUTC);

							hourDesired = timeMethods.convertHourUTCtoZoneHour(tempHourUTC, zoneDesired); // hourDesired = 14
							
							// need to figure out how to get hourDesired into UTC using tempHourUTC (?) somehow; like going from tempHourUTC = 19 to tempHourDesired = 22 somehow
							// then do comparisons in the below if-else statement to get the correct meridiem

							tempHourDesiredUTC = timeMethods.HourToUTC(hourDesired, zoneDesired); // tempHourDesiredUTC = 19

							tempHourDesired = hourDesired;

							if ((tempHourUTC % 24) > (tempHourDesired % 24))
							{
								meridiemDesired = "AM";
							}
							else
							{
								meridiemDesired = "PM";
							}

							hourDesired = validConvertedHour(hourDesired, timeMethods.getClockType());
							minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							if (minuteInput < 10 && minuteDesired < 10)
							{
								cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":0" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
							else
							{
								cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
							}
						}
					}
				}
				else // 24-Hour Clock Case
				{
					cout << "Input the hours, minutes, and time zone abbreviation of the time to convert." << endl << endl;
					hourInput = validHourInput(timeMethods.getClockType());
					minuteInput = validMinuteInput();
					zoneInput = validZoneInput();

					if (timeMethods.searchTime(hourInput, minuteInput, zoneInput) == true)
					{
						cout << "Input the time zone abbreviation to convert the time to:" << endl << endl;
						zoneDesired = validZoneInput();
						tempZoneInput = zoneDesired;

						if (zoneDesired == zoneInput)
						{
							cout << "Error: Desired time zone is the same time zone as the stored time! Returning to menu." << endl;
							break;
						}

						if (zoneDesired == "BST" || zoneDesired == "CST" || zoneDesired == "IST" || zoneDesired == "WST" || zoneDesired == "AMST" || zoneDesired == "GST" || zoneDesired == "ADT" || zoneDesired == "AMT" || zoneDesired == "AST" || zoneDesired == "CDT") // Duplicate Zone Abbreviation Case
						{
							zoneDesired = validDuplicateTimeZone(zoneDesired, tempZoneInput);

							hourUTC = timeMethods.HourToUTCDuplicateAbbreviation(hourInput, zoneInput);

							hourDesired = timeMethods.convertHourUTCtoZoneHourDuplicateAbbreviation(hourUTC, zoneDesired);
							hourDesired = validConvertedHour(hourDesired, timeMethods.getClockType());

							hourUTC = validConvertedHour(hourUTC, timeMethods.getClockType());
							minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInput);
							minuteUTC = validConvertedMinute(minuteUTC);

							minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							formatTwentyFourHourClockOutput(hourInput, minuteInput, zoneInput, hourDesired, minuteDesired, zoneDesired);
							break;
						}

						hourUTC = timeMethods.HourToUTC(hourInput, zoneInput);
						hourUTC = validConvertedHour(hourUTC, timeMethods.getClockType());
						minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInput);
						minuteUTC = validConvertedMinute(minuteUTC);

						hourDesired = timeMethods.convertHourUTCtoZoneHour(hourUTC, zoneDesired);
						hourDesired = validConvertedHour(hourDesired, timeMethods.getClockType());
						minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
						minuteDesired = validConvertedMinute(minuteDesired);

						formatTwentyFourHourClockOutput(hourInput, minuteInput, zoneInput, hourDesired, minuteDesired, zoneDesired);
						break;
					}
				}
				break;
			case 4: // display times stored
				timeMethods.displayStoredTimes();
				break;
			case 5: // choose between 12-hour clock and 24-hour clock
				clockType = validClockType(timeMethods.isEmpty());

				if (clockType == TWELVE_HOUR_CLOCK)
				{
					timeMethods.setClockTypeTo12();
				}
				else if (clockType == TWENTY_FOUR_HOUR_CLOCK)
				{
					timeMethods.setClockTypeTo24();
				}
				cout << endl;
				break;
			case 6: // exit
				cout << "Exiting program.";
				break;
			case 999: // destructor option
				timeMethods.~timeMethods();
				cout << endl << "Deleted all stored times." << endl << endl;
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

int displayMenu(int clockType)
{
	int menuChoice = 0;

	cout << "1. Store a time" << endl;
	cout << "2. Delete a time" << endl;
	cout << "3. Convert a time to a specific time zone" << endl;
	cout << "4. Display all times stored" << endl;
	cout << "5. Select 12-Hour Clock or 24-Hour Clock (Currently set to: " << clockType << ")" << endl;
	cout << "6. Exit" << endl;
	cout << "999. DELETE ALL STORED TIMES" << endl << endl;

	cout << "Enter your menu choice: ";
	cin >> menuChoice;
	cin.clear();
	cin.ignore(10000, '\n');

	return menuChoice;
}

int validHourInput(int clockType)
{
	int hourInput = 0;
	string str = "";

	cout << "Enter the hours: ";

	if (clockType == TWELVE_HOUR_CLOCK)
	{
		while (getline(cin, str))
		{
			stringstream stream(str);
			if (stream >> hourInput)
			{
				if (stream.eof() && hourInput > MIN_TIME_VALUE && hourInput <= clockType)
				{
					break;
				}
			}
			cout << endl << "Error: A zero/negative hour value was found, a non-integer was found, or inputted hour value was greater than " << clockType << "." << endl;
			cout << endl << "Enter the hours: ";
		}
	}
	else
	{
		while (getline(cin, str))
		{
			stringstream stream(str);
			if (stream >> hourInput)
			{
				if (stream.eof() && hourInput >= MIN_TIME_VALUE && hourInput <= clockType)
				{
					break;
				}
			}
			cout << endl << "Error: A zero/negative hour value was found, a non-integer was found, or inputted hour value was greater than " << clockType << "." << endl;
			cout << endl << "Enter the hours: ";
		}
	}
	cout << endl;

	return hourInput;
}

int validMinuteInput()
{
	int minuteInput = 0;
	string str = "";

	cout << "Enter the minutes: ";
	
	while (getline(cin, str))
	{
		stringstream stream(str);
		if (stream >> minuteInput)
		{
			if (stream.eof() && minuteInput >= MIN_TIME_VALUE && minuteInput < MAX_MINUTE_VALUE)
			{
				break;
			}
		}
		cout << endl << "Error: A negative minute value was found, a non-integer was found, or inputted minutes were greater than or equal to " << MAX_MINUTE_VALUE << "." << endl;
		cout << endl << "Enter the minutes: ";
	}
	cout << endl;

	return minuteInput;
}

// need to add validation for when user inputs a time zone that does not exist such as typing a word
// maybe have to add something similar to (meridiemInput != "AM" && meridiemInput != "PM") in the while condition
string validZoneInput()
{
	string zoneInput = "";
	cout << "Enter the time zone abbreviation: ";
	getline(cin, zoneInput);

	while (zoneInput == "" || zoneInput.find_first_not_of(' ') || zoneInput.length() > MAX_ZONE_ABBREVIATION_LENGTH || noIntegersInZoneName(zoneInput) == false)
	{
		cout << endl << "Error: Input was too long (maximum of 5 characters), blank characters were found, or integers were found." << endl;
		cout << endl << "Enter the time zone abbrevation: ";
		getline(cin, zoneInput);
	}
	transform(zoneInput.begin(), zoneInput.end(), zoneInput.begin(), ::toupper);

	return zoneInput;
}

string validMeridiemInput()
{
	string meridiemInput = "";
	cout << "Enter AM or PM: ";
	getline(cin, meridiemInput);
	transform(meridiemInput.begin(), meridiemInput.end(), meridiemInput.begin(), ::toupper);

	while (meridiemInput == "" || meridiemInput.find_first_not_of(' ') || meridiemInput.length() > MERIDIEM_ABBREVIATION_LENGTH || (meridiemInput != "AM" && meridiemInput != "PM"))
	{
		cout << endl << "Error: Input was too long, contained blank characters, or was not an accepted input (AM or PM)." << endl;
		cout << endl << "Enter AM or PM: ";
		getline(cin, meridiemInput);
		transform(meridiemInput.begin(), meridiemInput.end(), meridiemInput.begin(), ::toupper);
	}
	cout << endl;

	return meridiemInput;
}

int validClockType(bool noStoredTimes)
{
	int clockType = 0;

	if (noStoredTimes == true)
	{
		cout << "Enter '12' to select the 12-Hour clock type or enter '24' to select the 24-Hour clock type: ";
		cin >> clockType;
		cin.clear();
		cin.ignore(10000, '\n');

		while (clockType != TWELVE_HOUR_CLOCK && clockType != TWENTY_FOUR_HOUR_CLOCK)
		{
			cout << endl << "Error: Input was not an accepted input (12 or 24)." << endl;
			cout << "Enter '12' to select the 12-Hour clock type or enter '24' to select the 24-Hour clock type: ";
			cin >> clockType;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	else
	{
		cout << "Error: Stored times were found. Clock type cannot be changed until ALL stored times are deleted." << endl;
	}

	return clockType;
}

// first - make hourInput positive if it's negative
// second - check if hourInput is equal to 0
// third - check if hourInput exceeds the largest valid hour value
// fourth - check if hourInput is equal to 0 if doing modulo on hourInput resulted in 0
int validConvertedHour(int hourInput, int clockType)
{
	if (clockType == TWELVE_HOUR_CLOCK)
	{
		if (hourInput < 0)
		{
			hourInput = hourInput * -1;
		}
		if (hourInput == 0)
		{
			hourInput = 12;
		}
		if (hourInput > 12)
		{
			hourInput = hourInput % 12;
		}
		if (hourInput == 0)
		{
			hourInput = 12;
		}
	}
	else
	{
		if (hourInput < 0)
		{
			hourInput = hourInput * -1;
		}
		if (hourInput == 24)
		{
			hourInput = 0;
		}
		if (hourInput > 24)
		{
			hourInput = hourInput % 24;
		}
		if (hourInput == 24)
		{
			hourInput = 0;
		}
	}

	return hourInput;
}

// first - make minuteInput positive if it's negative
// second - check if minuteInput exceeds the largest valid minute value
int validConvertedMinute(int minuteInput)
{
	if (minuteInput < 0) // check if minuteInput is negative first
	{
		minuteInput = minuteInput * -1;
	}
	if (minuteInput > 60) // check if minuteInput is greater than 60
	{
		minuteInput = minuteInput % 60;
	}

	return minuteInput;
}

bool noIntegersInZoneName(string zoneInput)
{
	if (none_of(zoneInput.begin(), zoneInput.end(), [](unsigned char c) {return isdigit(c); }))
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

	while (zoneDesired == "" || zoneDesired.find_first_not_of(' ') || noIntegersInZoneName(zoneDesired) == false
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

void formatTwentyFourHourClockOutput(int hourInput, int minuteInput, string zoneInput, int hourDesired, int minuteDesired, string zoneDesired)
{
	if (hourInput < 10 && minuteInput < 10 && hourDesired < 10 && minuteDesired < 10)
	{
		cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput < 10 && hourDesired < 10 && minuteDesired < 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput > 10 && hourDesired < 10 && minuteDesired < 10)
	{
		cout << hourInput << ":" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput > 10 && hourDesired > 10 && minuteDesired < 10)
	{
		cout << hourInput << ":" << minuteInput << " " << zoneInput << " is " << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput > 10 && hourDesired > 10 && minuteDesired > 10)
	{
		cout << hourInput << ":" << minuteInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput < 10 && hourDesired > 10 && minuteDesired < 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << zoneInput << " is " << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput < 10 && hourDesired > 10 && minuteDesired > 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput > 10 && hourDesired < 10 && minuteDesired > 10)
	{
		cout << hourInput << ":" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput < 10 && hourDesired < 10 && minuteDesired > 10)
	{
		cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput < 10 && hourDesired > 10 && minuteDesired > 10)
	{
		cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput > 10 && hourDesired > 10 && minuteDesired > 10)
	{
		cout << "0" << hourInput << ":" << minuteInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput > 10 && hourDesired < 10 && minuteDesired > 10)
	{
		cout << "0" << hourInput << ":" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput < 10 && hourDesired > 10 && minuteDesired > 10)
	{
		cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput > 10 && minuteInput < 10 && hourDesired < 10 && minuteDesired > 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput < 10 && hourDesired > 10 && minuteDesired < 10)
	{
		cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " is " << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
	else if (hourInput < 10 && minuteInput > 10 && hourDesired < 10 && minuteDesired < 10)
	{
		cout << "0" << hourInput << ":" << minuteInput << " " << zoneInput << " is 0" << hourDesired << ":0" << minuteDesired << " " << zoneDesired << endl << endl;
	}
}
