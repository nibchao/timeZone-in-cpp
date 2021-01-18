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

using std::cout;
using std::endl;
using std::cin;
using std::stringstream;

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
void formatTwelveHourClockOutput(int, int, string, string, int, int, string, string);

string getZoneAbbreviation(string);
string getMeridiemDesired(int);
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
	int tempHourUTC = 0;
	int tempHourDesired = 0;

	string zoneInputAbbreviation = "";

	bool searchTime = NULL;

	//

	timeMethods timeMethods;

	do
	{
		clockType = timeMethods.getClockType();
		menuChoice = displayMenu(clockType);

		switch (menuChoice)
		{
			case 1: // store a time
				if (clockType == TWELVE_HOUR_CLOCK)
				{
					cout << "===Storing time in " << clockType << "-Hour Clock Type===" << endl;

					hourInput = validHourInput(clockType);
					minuteInput = validMinuteInput();

					meridiemInput = validMeridiemInput();

					zoneInput = validZoneInput();
					zoneInputAbbreviation = getZoneAbbreviation(zoneInput);

					timeMethods.storeTime(hourInput, minuteInput, meridiemInput, zoneInputAbbreviation, zoneInput);
				}
				else
				{
					cout << "===Storing time in " << clockType << "-Hour Clock Type===" << endl;

					hourInput = validHourInput(clockType);
					minuteInput = validMinuteInput();

					zoneInput = validZoneInput();
					zoneInputAbbreviation = getZoneAbbreviation(zoneInput);

					timeMethods.storeTime(hourInput, minuteInput, zoneInputAbbreviation, zoneInput);
				}
				break;
			case 2: // delete a time
				if (clockType == TWELVE_HOUR_CLOCK)
				{
					cout << endl;
					hourInput = validHourInput(clockType);
					minuteInput = validMinuteInput();

					meridiemInput = validMeridiemInput();

					zoneInput = validZoneInput();

					timeMethods.deleteTime(hourInput, minuteInput, meridiemInput, zoneInput);
				}
				else
				{
					cout << endl;
					hourInput = validHourInput(clockType);
					minuteInput = validMinuteInput();

					zoneInput = validZoneInput();

					timeMethods.deleteTime(hourInput, minuteInput, zoneInput);
				}
				break;
			case 3: // convert a time to another time zone
				if (clockType == TWELVE_HOUR_CLOCK)
				{
					cout << "===Enter the hours, minutes, meridiem, and time zone abbreviation of the time to convert===" << endl;
					hourInput = validHourInput(clockType);
					minuteInput = validMinuteInput();

					meridiemInput = validMeridiemInput();

					zoneInput = validZoneInput();
					zoneInputAbbreviation = getZoneAbbreviation(zoneInput);

					searchTime = timeMethods.searchTime(hourInput, minuteInput, meridiemInput, zoneInput);

					if (searchTime)
					{
						cout << "===Input the time zone abbreviation to convert the time to===" << endl;
						zoneDesired = validZoneInput();
						tempZoneInput = zoneDesired;

						if (zoneDesired == zoneInputAbbreviation)
						{
							cout << "Error: Desired time zone is the same time zone as the stored time! Returning to menu." << endl;
							break;
						}

						if (zoneDesired == "BST" || zoneDesired == "CST" || zoneDesired == "IST" || zoneDesired == "WST" || zoneDesired == "AMST" || zoneDesired == "GST" || zoneDesired == "ADT" || zoneDesired == "AMT" || zoneDesired == "AST" || zoneDesired == "CDT") // Duplicate Zone Abbreviation Case
						{
							zoneDesired = validDuplicateTimeZone(zoneDesired, tempZoneInput);

							hourUTC = timeMethods.HourToUTCDuplicateAbbreviation(hourInput, zoneInputAbbreviation);
							tempHourUTC = hourUTC;
							hourUTC = validConvertedHour(hourUTC, clockType);

							minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInputAbbreviation);
							minuteUTC = validConvertedMinute(minuteUTC);

							hourDesired = timeMethods.convertHourUTCtoZoneHour(tempHourUTC, zoneDesired);
							tempHourDesired = hourDesired;

							meridiemDesired = getMeridiemDesired(tempHourDesired);

							hourDesired = validConvertedHour(hourDesired, clockType);

							minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							formatTwelveHourClockOutput(hourInput, minuteInput, meridiemInput, zoneInputAbbreviation, hourDesired, minuteDesired, meridiemDesired, zoneDesired);
							break;
						}
						else // Every Other Time Zone
						{
							hourUTC = timeMethods.HourToUTC(hourInput, zoneInputAbbreviation); // 11:00 AM AST (Atlantic Standard Time) -> 6:00 AM EST (Eastern Standard Time); need to add duplicate time zone abbreviation cases to all XToUTC functions and convertXUTCtoZoneHour/Minute functions
																							   // need to apply the fix to this to every conversion case (12-hour duplicate/not duplicate, 24-hour duplicate/not duplicate)
							tempHourUTC = hourUTC;
							hourUTC = validConvertedHour(hourUTC, clockType);

							minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInputAbbreviation);
							minuteUTC = validConvertedMinute(minuteUTC);

							hourDesired = timeMethods.convertHourUTCtoZoneHour(tempHourUTC, zoneDesired);
							tempHourDesired = hourDesired;

							meridiemDesired = getMeridiemDesired(tempHourDesired);

							hourDesired = validConvertedHour(hourDesired, clockType);

							minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							formatTwelveHourClockOutput(hourInput, minuteInput, meridiemInput, zoneInputAbbreviation, hourDesired, minuteDesired, meridiemDesired, zoneDesired);
							break;
						}
					}
				}
				else // 24-Hour Clock Case
				{
					cout << "Input the hours, minutes, and time zone abbreviation of the time to convert." << endl << endl;
					hourInput = validHourInput(clockType);
					minuteInput = validMinuteInput();
					zoneInput = validZoneInput();

					zoneInputAbbreviation = getZoneAbbreviation(zoneInput);

					searchTime = timeMethods.searchTime(hourInput, minuteInput, zoneInput);

					if (searchTime)
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
							hourDesired = validConvertedHour(hourDesired, clockType);

							hourUTC = validConvertedHour(hourUTC, clockType);
							minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInput);
							minuteUTC = validConvertedMinute(minuteUTC);

							minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
							minuteDesired = validConvertedMinute(minuteDesired);

							formatTwentyFourHourClockOutput(hourInput, minuteInput, zoneInputAbbreviation, hourDesired, minuteDesired, zoneDesired);
							break;
						}

						hourUTC = timeMethods.HourToUTC(hourInput, zoneInput);
						hourUTC = validConvertedHour(hourUTC, clockType);
						minuteUTC = timeMethods.MinuteToUTC(minuteInput, zoneInput);
						minuteUTC = validConvertedMinute(minuteUTC);

						hourDesired = timeMethods.convertHourUTCtoZoneHour(hourUTC, zoneDesired);
						hourDesired = validConvertedHour(hourDesired, clockType);
						minuteDesired = timeMethods.convertMinuteUTCtoZoneMinute(minuteUTC, zoneDesired);
						minuteDesired = validConvertedMinute(minuteDesired);

						zoneInputAbbreviation = getZoneAbbreviation(zoneInput);

						formatTwentyFourHourClockOutput(hourInput, minuteInput, zoneInputAbbreviation, hourDesired, minuteDesired, zoneDesired);
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

	return minuteInput;
}

string validZoneInput()
{
	string zoneInput = "";
	cout << "Enter the time zone abbreviation: ";
	getline(cin, zoneInput);
	transform(zoneInput.begin(), zoneInput.end(), zoneInput.begin(), ::toupper);

	if (zoneInput == "BST" || zoneInput == "CST" || zoneInput == "IST" || zoneInput == "WST" || zoneInput == "AMST" || zoneInput == "GST" || zoneInput == "ADT" || zoneInput == "AMT" || zoneInput == "AST" || zoneInput == "CDT") // duplicate case 
	{
		zoneInput = validDuplicateTimeZone(zoneInput, zoneInput);
		return zoneInput;
	}

	while (zoneInput == "" || zoneInput.find_first_not_of(' ') || noIntegersInZoneName(zoneInput) == false || 
		(zoneInput != "LINT" && zoneInput != "TOST" &&
		zoneInput != "CHADT" && zoneInput != "NZDT" && zoneInput != "FJST" && zoneInput != "PHOT" && zoneInput != "TKT" && zoneInput != "TOT" &&
		zoneInput != "ANAT" && zoneInput != "ANAST" && zoneInput != "FJT" && zoneInput != "GILT" && zoneInput != "M" && zoneInput != "MAGST" && zoneInput != "MHT" && zoneInput != "NFDT" && zoneInput != "NRT" && zoneInput != "NZST" && zoneInput != "PETST" && zoneInput != "PETT" && zoneInput != "TVT" && zoneInput != "WAKT" && zoneInput != "WFT" &&
		zoneInput != "AEDT" && zoneInput != "KOST" && zoneInput != "L" && zoneInput != "LHDT" && zoneInput != "MAGT" && zoneInput != "NCT" && zoneInput != "NFT" && zoneInput != "PONT" && zoneInput != "SAKT" && zoneInput != "SBT" && zoneInput != "SRET" && zoneInput != "VLAST" && zoneInput != "VUT" &&
		zoneInput != "ACDT" && zoneInput != "LHST" && zoneInput != "AEST" && zoneInput != "CHUT" && zoneInput != "CHST" && zoneInput != "DDUT" && zoneInput != "K" && zoneInput != "PGT" && zoneInput != "VLAT" && zoneInput != "YAKST" && zoneInput != "YAPT" &&
		zoneInput != "ACST" && zoneInput != "JST" && zoneInput != "AWDT" && zoneInput != "CHOST" && zoneInput != "I" && zoneInput != "IRKST" && zoneInput != "KST" && zoneInput != "PWT" && zoneInput != "TLT" && zoneInput != "ULAST" && zoneInput != "WIT" && zoneInput != "YAKT" &&
		zoneInput != "ACWST" && zoneInput != "AWST" && zoneInput != "BNT" && zoneInput != "CAST" && zoneInput != "CHOT" && zoneInput != "H" && zoneInput != "HKT" && zoneInput != "HOVST" && zoneInput != "IRKT" && zoneInput != "KRAST" && zoneInput != "MYT" && zoneInput != "PHT" && zoneInput != "SGT" && zoneInput != "ULAT" && zoneInput != "WITA" &&
		zoneInput != "WIB" && zoneInput != "CXT" && zoneInput != "DAVT" && zoneInput != "G" && zoneInput != "HOVT" && zoneInput != "ICT" && zoneInput != "KRAT" && zoneInput != "NOVST" && zoneInput != "NOVT" && zoneInput != "OMSST" &&
		zoneInput != "MMT" && zoneInput != "CCT" && zoneInput != "ALMT" && zoneInput != "BTT" && zoneInput != "F" && zoneInput != "IOT" && zoneInput != "KGT" && zoneInput != "OMST" && zoneInput != "QYZT" && zoneInput != "VOST" && zoneInput != "YEKST" &&
		zoneInput != "NPT" && zoneInput != "UZT" && zoneInput != "AQTT" && zoneInput != "AZST" && zoneInput != "E" && zoneInput != "MAWT" && zoneInput != "MVT" && zoneInput != "ORAT" && zoneInput != "PKT" && zoneInput != "TFT" && zoneInput != "TJT" && zoneInput != "TMT" && zoneInput != "YEKT" &&
		zoneInput != "AFT" && zoneInput != "IRDT" && zoneInput != "AZT" && zoneInput != "D" && zoneInput != "GET" && zoneInput != "KUYT" && zoneInput != "MSD" && zoneInput != "MUT" && zoneInput != "RET" && zoneInput != "SAMT" && zoneInput != "SCT" &&
		zoneInput != "IRST" && zoneInput != "MSK" && zoneInput != "C" && zoneInput != "EAT" && zoneInput != "EEST" && zoneInput != "FET" && zoneInput != "IDT" && zoneInput != "SYOT" && zoneInput != "TRT" &&
		zoneInput != "EET" && zoneInput != "B" && zoneInput != "CAT" && zoneInput != "CEST" && zoneInput != "SAST" && zoneInput != "WAST" &&
		zoneInput != "CET" && zoneInput != "A" && zoneInput != "WAT" && zoneInput != "WEST" &&
		zoneInput != "GMT" && zoneInput != "AZOST" && zoneInput != "EGST" && zoneInput != "WET" && zoneInput != "WT" && zoneInput != "Z" &&
		zoneInput != "CVT" && zoneInput != "AZOT" && zoneInput != "EGT" && zoneInput != "N" &&
		zoneInput != "BRST" && zoneInput != "FNT" && zoneInput != "O" && zoneInput != "PMDT" && zoneInput != "UYST" && zoneInput != "WGST" &&
		zoneInput != "ART" && zoneInput != "BRT" && zoneInput != "CLST" && zoneInput != "FKST" && zoneInput != "GFT" && zoneInput != "P" && zoneInput != "PMST" && zoneInput != "PYST" && zoneInput != "ROTT" && zoneInput != "SRT" && zoneInput != "UYT" && zoneInput != "WARST" && zoneInput != "WGT" && zoneInput != "NST" &&
		zoneInput != "VET" && zoneInput != "BOT" && zoneInput != "CIDST" && zoneInput != "CLT" && zoneInput != "EDT" && zoneInput != "FKT" && zoneInput != "GYT" && zoneInput != "PYT" && zoneInput != "Q" &&
		zoneInput != "EST" && zoneInput != "ACT" && zoneInput != "CIST" && zoneInput != "COT" && zoneInput != "EASST" && zoneInput != "ECT" && zoneInput != "PET" && zoneInput != "R" &&
		zoneInput != "EAST" && zoneInput != "GALT" && zoneInput != "MDT" && zoneInput != "S" &&
		zoneInput != "MST" && zoneInput != "PDT" && zoneInput != "T" &&
		zoneInput != "PST" && zoneInput != "AKDT" && zoneInput != "U" &&
		zoneInput != "AKST" && zoneInput != "GAMT" && zoneInput != "HDT" && zoneInput != "V" && zoneInput != "MART" &&
		zoneInput != "HST" && zoneInput != "CKT" && zoneInput != "TAHT" && zoneInput != "W" &&
		zoneInput != "NUT" && zoneInput != "SST" && zoneInput != "X" &&
		zoneInput != "AoE" && zoneInput != "Y" &&
		zoneInput != "BST" && zoneInput != "CST" && zoneInput != "IST" && zoneInput != "WST" && zoneInput != "AMST" && zoneInput != "GST" && zoneInput != "ADT" && zoneInput != "AMT" && zoneInput != "AST" && zoneInput != "CDT")
		)
	{
		cout << endl << "Error: Abbreviation was too long (maximum of 5 characters), blank characters were found, integers were found, or abbreviation does not exist." << endl;
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

int validConvertedMinute(int minuteInput)
{
	if (minuteInput < 0)
	{
		minuteInput = minuteInput * -1;
	}
	if (minuteInput > 60)
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

	while (zoneDesired == "" || zoneDesired.find_first_not_of(' ') || noIntegersInZoneName(zoneDesired) == false || 
			(zoneDesired != "West Samoa Time" && zoneDesired != "Bougainville Standard Time" && zoneDesired != "China Standard Time" && zoneDesired != "Bangladesh Standard Time" && zoneDesired != "India Standard Time" && zoneDesired != "Armenia Summer Time"
			&& zoneDesired != "Gulf Standard Time" && zoneDesired != "Arabia Daylight Time" && zoneDesired != "Armenia Time" && zoneDesired != "Arabia Standard Time" && zoneDesired != "Israel Standard Time" && zoneDesired != "British Summer Time"
			&& zoneDesired != "Irish Standard Time" && zoneDesired != "Western Sahara Summer Time" && zoneDesired != "South Georgia Time" && zoneDesired != "Atlantic Daylight Time" && zoneDesired != "Amazon Summer Time" && zoneDesired != "Amazon Time"
			&& zoneDesired != "Atlantic Standard Time" && zoneDesired != "Cuba Daylight Time" && zoneDesired != "Central Daylight Time" && zoneDesired != "Cuba Standard Time" && zoneDesired != "Central Standard Time")
		  )
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
	else if (hourInput >= 10 && minuteInput >= 10 && hourDesired >= 10 && minuteDesired >= 10)
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

void formatTwelveHourClockOutput(int hourInput, int minuteInput, string meridiemInput, string zoneInput, int hourDesired, int minuteDesired, string meridiemDesired, string zoneDesired)
{
	if (minuteInput < 10 && minuteDesired < 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":0" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
	}
	else if (minuteInput < 10 && minuteDesired > 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
	}
	else if (minuteInput > 10 && minuteDesired < 10)
	{
		cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
	}
	else if (minuteInput >= 10 && minuteDesired >= 10)
	{
		cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " is " << hourDesired << ":" << minuteDesired << " " << meridiemDesired << " " << zoneDesired << endl << endl;
	}
}

string getZoneAbbreviation(string zoneInput)
{
	string zoneAbbreviation = "";
	string temp = "";
	int zoneInputLength = zoneInput.length();

	for (int cnt = 0; cnt < zoneInputLength; cnt++)
	{
		if (cnt == 0)
		{
			zoneInput[cnt] = toupper(zoneInput[cnt]);
			temp = zoneInput.substr(cnt, 1);
			zoneAbbreviation += temp;
		}
		else if (zoneInput[cnt - 1] == ' ')
		{
			zoneInput[cnt] = toupper(zoneInput[cnt]);
			temp = zoneInput.substr(cnt, 1);
			zoneAbbreviation += temp;
		}
	}

	// since above won't make zoneAbbreviation correct for non-duplicate time zone cases, this sets zoneAbbreviation back to zoneInput which is the correct time zone abbreviation
	if (zoneAbbreviation.length() == 1)
	{
		zoneAbbreviation = zoneInput;
	}

	return zoneAbbreviation;
}

string getMeridiemDesired(int tempHourDesired)
{
	string meridiemDesired = "";

	if ((tempHourDesired % 24) > 12)
	{
		meridiemDesired = "PM";
	}
	else
	{
		meridiemDesired = "AM";
	}

	return meridiemDesired;
}