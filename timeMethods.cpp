/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
*  Accepted time zones in this program are based on the ones listed on https://www.timeanddate.com/time/current-number-time-zones.html
*/

#include <iostream>
#include <string>
#include "timeMethods.h"

using std::cout;
using std::endl;

timeMethods::~timeMethods()
{
	Node* currentNode = head;
	Node* nextNode = nullptr;

	while (currentNode)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
	head = nullptr;
}

// storeTime method - 12-Hour Clock Version
void timeMethods::storeTime(int hourInput, int minuteInput, string meridiemInput, string zoneInputAbbreviation, string fullZoneInput)
{
	Node* newNode = new Node;
	newNode->hour = hourInput;
	newNode->minute = minuteInput;
	newNode->meridiem = meridiemInput;
	newNode->zone = zoneInputAbbreviation;
	newNode->fullZoneName = fullZoneInput;
	newNode->next = nullptr;

	Node* currentNode = head;

	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		while (currentNode->next)
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
	}
	if (minuteInput < 10)
	{
		cout << endl << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInputAbbreviation << " has been stored." << endl << endl;
	}
	else
	{
		cout << endl << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInputAbbreviation << " has been stored." << endl << endl;
	}
}

// deleteTime method - 12-Hour Clock Version
void timeMethods::deleteTime(int hourInput, int minuteInput, string meridiemInput, string zoneInput)
{
	Node* currentNode = head;

	if (!head)
	{
		cout << "There were no times added so no times were deleted." << endl << endl;
		return;
	}

	if (head->hour == hourInput && head->minute == minuteInput && head->meridiem == meridiemInput && head->fullZoneName == zoneInput)
	{
		head = currentNode->next;
		delete(currentNode);
		if (minuteInput < 10)
		{
			cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " has been deleted." << endl << endl;
		}
		else
		{
			cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " has been deleted." << endl << endl;
		}
		return;
	}

	while (currentNode != nullptr && currentNode->next->hour != hourInput && currentNode->next->minute != minuteInput && currentNode->next->meridiem != meridiemInput && currentNode->next->fullZoneName != zoneInput)
	{
		currentNode = currentNode->next;
	}

	if (currentNode == nullptr || currentNode->next == nullptr)
	{
		cout << "The time to be deleted was out of bounds or does not exist." << endl << endl;
		return;
	}

	Node* nextNextNode = currentNode->next->next;
	delete(currentNode->next);
	currentNode->next = nextNextNode;

	if (minuteInput < 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " has been deleted." << endl << endl;
	}
	else
	{
		cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " has been deleted." << endl << endl;
	}
}

// searchTime method - 12-Hour Clock Version
bool timeMethods::searchTime(int hourInput, int minuteInput, string meridiemInput, string zoneInput)
{
	Node* currentNode = head;

	if (head == nullptr)
	{
		cout << "No stored times were found." << endl;
		return false;
	}

	while (currentNode)
	{
		if (currentNode->hour == hourInput && currentNode->minute == minuteInput && currentNode->meridiem == meridiemInput && currentNode->fullZoneName == zoneInput)
		{
			cout << endl;
			if (minuteInput < 10)
			{
				cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << currentNode->zone << " was found in the list of stored times." << endl << endl;
			}
			else
			{
				cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << currentNode->zone << " was found in the list of stored times." << endl << endl;
			}
			return true;
		}
		currentNode = currentNode->next;
	}

	cout << endl;
	if (minuteInput < 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << meridiemInput << " " << zoneInput << " was not found in the list of stored times." << endl << endl;
	}
	else
	{
		cout << hourInput << ":" << minuteInput << " " << meridiemInput << " " << zoneInput << " was not found in the list of stored times." << endl << endl;
	}

	return false;
}

// overloaded storeTime method - 24-Hour Clock Version
void timeMethods::storeTime(int hourInput, int minuteInput, string zoneInputAbbreviation, string fullZoneInput)
{
	Node* newNode = new Node;
	newNode->hour = hourInput;
	newNode->minute = minuteInput;
	newNode->zone = zoneInputAbbreviation;
	newNode->fullZoneName = fullZoneInput;
	newNode->next = nullptr;

	Node* currentNode = head;

	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		while (currentNode->next)
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
	}

	if (hourInput < 10)
	{
		if (minuteInput < 10)
		{
			cout << endl << "0" << hourInput << ":0" << minuteInput << " " << zoneInputAbbreviation << " has been stored." << endl << endl;
		}
		else
		{
			cout << endl << "0" << hourInput << ":" << minuteInput << " " << zoneInputAbbreviation << " has been stored." << endl << endl;
		}
	}
	else
	{
		if (minuteInput < 10)
		{
			cout << endl << hourInput << ":0" << minuteInput << " " << zoneInputAbbreviation << " has been stored." << endl << endl;
		}
		else
		{
			cout << endl << hourInput << ":" << minuteInput << " " << zoneInputAbbreviation << " has been stored." << endl << endl;
		}
	}
}

// overloaded deleteTime method - 24-Hour Clock Version
void timeMethods::deleteTime(int hourInput, int minuteInput, string zoneInput)
{
	Node* currentNode = head;

	if (!head)
	{
		cout << "There were no times added so no times were deleted." << endl << endl;
		return;
	}

	if (head->hour == hourInput && head->minute == minuteInput && head->fullZoneName == zoneInput)
	{
		head = currentNode->next;
		delete(currentNode);
		if (hourInput < 10)
		{
			if (minuteInput < 10)
			{
				cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
			}
			else
			{
				cout << "0" << hourInput << ":" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
			}
		}
		else
		{
			if (minuteInput < 10)
			{
				cout << hourInput << ":0" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
			}
			else
			{
				cout << hourInput << ":" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
			}
		}
		return;
	}

	while (currentNode != nullptr && currentNode->next->hour != hourInput && currentNode->next->minute != minuteInput && currentNode->next->fullZoneName != zoneInput)
	{
		currentNode = currentNode->next;
	}

	if (currentNode == nullptr || currentNode->next == nullptr)
	{
		cout << "The time to be deleted was out of bounds or does not exist." << endl << endl;
		return;
	}

	Node* nextNextNode = currentNode->next->next;
	delete(currentNode->next);
	currentNode->next = nextNextNode;

	if (hourInput < 10)
	{
		if (minuteInput < 10)
		{
			cout << "0" << hourInput << ":0" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
		}
		else
		{
			cout << "0" << hourInput << ":" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
		}
	}
	else
	{
		if (minuteInput < 10)
		{
			cout << hourInput << ":0" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
		}
		else
		{
			cout << hourInput << ":" << minuteInput << " " << zoneInput << " has been deleted." << endl << endl;
		}
	}
}

// overloaded searchTime method - 24-Hour Clock Version
bool timeMethods::searchTime(int hourInput, int minuteInput, string zoneInput)
{
	Node* currentNode = head;

	if (head == nullptr)
	{
		cout << "No stored times were found." << endl;
		return false;
	}

	while (currentNode)
	{
		if (currentNode->hour == hourInput && currentNode->minute == minuteInput && currentNode->fullZoneName == zoneInput)
		{
			cout << endl;
			if (minuteInput < 10)
			{
				cout << hourInput << ":0" << minuteInput << " " << currentNode->zone << " was found in the list of stored times." << endl << endl;
			}
			else
			{
				cout << hourInput << ":" << minuteInput << " " << currentNode->zone << " was found in the list of stored times." << endl << endl;
			}
			return true;
		}
		currentNode = currentNode->next;
	}

	cout << endl;
	if (minuteInput < 10)
	{
		cout << hourInput << ":0" << minuteInput << " " << zoneInput << " was not found in the list of stored times." << endl << endl;
	}
	else
	{
		cout << hourInput << ":" << minuteInput << " " << zoneInput << " was not found in the list of stored times." << endl << endl;
	}

	return false;
}

void timeMethods::displayStoredTimes() const
{
	Node* currentNode = head;
	int counter = 0;

	if (head == nullptr)
	{
		cout << "There were no stored times found." << endl << endl;
		return;
	}

	cout << "Displaying stored times ";

	if (clockType == 12)
	{
		cout << "for " << clockType << "-Hour Clock Type:" << endl;
		while (currentNode)
		{
			if (currentNode->minute < 10)
			{
				cout << "(" << counter << ") " << currentNode->hour << ":0" << currentNode->minute << " " << currentNode->meridiem << " " << currentNode->zone << endl;
			}
			else
			{
				cout << "(" << counter << ") " << currentNode->hour << ":" << currentNode->minute << " " << currentNode->meridiem << " " << currentNode->zone << endl;
			}
			counter++;
			currentNode = currentNode->next;
		}
	}
	else
	{
		cout << "for " << clockType << "-Hour Clock Type:" << endl;
		while (currentNode)
		{
			if (currentNode->hour < 10)
			{
				if (currentNode->minute < 10)
				{
					cout << "(" << counter << ") 0" << currentNode->hour << ":0" << currentNode->minute << " " << currentNode->zone << endl;
				}
				else
				{
					cout << "(" << counter << ") 0" << currentNode->hour << ":" << currentNode->minute << " " << currentNode->zone << endl;
				}
			}
			else
			{
				if (currentNode->minute < 10)
				{
					cout << "(" << counter << ") " << currentNode->hour << ":0" << currentNode->minute << " " << currentNode->zone << endl;
				}
				else
				{
					cout << "(" << counter << ") " << currentNode->hour << ":" << currentNode->minute << " " << currentNode->zone << endl;
				}
			}
			counter++;
			currentNode = currentNode->next;
		}
	}
	cout << endl;
}

int timeMethods::HourToUTC(int hourInput, string zoneInput)
{
	int convertedHours = hourInput;

	if (zoneInput == "LINT" || zoneInput == "TOST")
	{
		convertedHours -= 14;
	}

	if (zoneInput == "CHADT" || zoneInput == "NZDT" || zoneInput == "FJST" || zoneInput == "PHOT" || zoneInput == "TKT" || zoneInput == "TOT")
	{
		convertedHours -= 13;
	}

	if (zoneInput == "ANAT" || zoneInput == "ANAST" || zoneInput == "FJT" || zoneInput == "GILT" || zoneInput == "M" || zoneInput == "MAGST" || zoneInput == "MHT" || zoneInput == "NFDT" || zoneInput == "NRT" || zoneInput == "NZST" || zoneInput == "PETST" || zoneInput == "PETT" || zoneInput == "TVT" || zoneInput == "WAKT" || zoneInput == "WFT")
	{
		convertedHours -= 12;
	}

	if (zoneInput == "AEDT" || zoneInput == "KOST" || zoneInput == "L" || zoneInput == "LHDT" || zoneInput == "MAGT" || zoneInput == "NCT" || zoneInput == "NFT" || zoneInput == "PONT" || zoneInput == "SAKT" || zoneInput == "SBT" || zoneInput == "SRET" || zoneInput == "VLAST" || zoneInput == "VUT")
	{
		convertedHours -= 11;
	}

	if (zoneInput == "ACDT" || zoneInput == "LHST" || zoneInput == "AEST" || zoneInput == "CHUT" || zoneInput == "CHST" || zoneInput == "DDUT" || zoneInput == "K" || zoneInput == "PGT" || zoneInput == "VLAT" || zoneInput == "YAKST" || zoneInput == "YAPT")
	{
		convertedHours -= 10;
	}

	if (zoneInput == "ACST" || zoneInput == "JST" || zoneInput == "AWDT" || zoneInput == "CHOST" || zoneInput == "I" || zoneInput == "IRKST" || zoneInput == "KST" || zoneInput == "PWT" || zoneInput == "TLT" || zoneInput == "ULAST" || zoneInput == "WIT" || zoneInput == "YAKT")
	{
		convertedHours -= 9;
	}

	if (zoneInput == "ACWST" || zoneInput == "AWST" || zoneInput == "BNT" || zoneInput == "CAST" || zoneInput == "CHOT" || zoneInput == "H" || zoneInput == "HKT" || zoneInput == "HOVST" || zoneInput == "IRKT" || zoneInput == "KRAST" || zoneInput == "MYT" || zoneInput == "PHT" || zoneInput == "SGT" || zoneInput == "ULAT" || zoneInput == "WITA")
	{
		convertedHours -= 8;
	}

	if (zoneInput == "WIB" || zoneInput == "CXT" || zoneInput == "DAVT" || zoneInput == "G" || zoneInput == "HOVT" || zoneInput == "ICT" || zoneInput == "KRAT" || zoneInput == "NOVST" || zoneInput == "NOVT" || zoneInput == "OMSST")
	{
		convertedHours -= 7;
	}

	if (zoneInput == "MMT" || zoneInput == "CCT" || zoneInput == "ALMT" || zoneInput == "BTT" || zoneInput == "F" || zoneInput == "IOT" || zoneInput == "KGT" || zoneInput == "OMST" || zoneInput == "QYZT" || zoneInput == "VOST" || zoneInput == "YEKST")
	{
		convertedHours -= 6;
	}

	if (zoneInput == "NPT" || zoneInput == "UZT" || zoneInput == "AQTT" || zoneInput == "AZST" || zoneInput == "E" || zoneInput == "MAWT" || zoneInput == "MVT" || zoneInput == "ORAT" || zoneInput == "PKT" || zoneInput == "TFT" || zoneInput == "TJT" || zoneInput == "TMT" || zoneInput == "YEKT")
	{
		convertedHours -= 5;
	}

	if (zoneInput == "AFT" || zoneInput == "IRDT" || zoneInput == "AZT" || zoneInput == "D" || zoneInput == "GET" || zoneInput == "KUYT" || zoneInput == "MSD" || zoneInput == "MUT" || zoneInput == "RET" || zoneInput == "SAMT" || zoneInput == "SCT")
	{
		convertedHours -= 4;
	}

	if (zoneInput == "IRST" || zoneInput == "MSK" || zoneInput == "C" || zoneInput == "EAT" || zoneInput == "EEST" || zoneInput == "FET" || zoneInput == "IDT" || zoneInput == "SYOT" || zoneInput == "TRT")
	{
		convertedHours -= 3;
	}

	if (zoneInput == "EET" || zoneInput == "B" || zoneInput == "CAT" || zoneInput == "CEST" || zoneInput == "SAST" || zoneInput == "WAST")
	{
		convertedHours -= 2;
	}

	if (zoneInput == "CET" || zoneInput == "A" || zoneInput == "WAT" || zoneInput == "WEST")
	{
		convertedHours -= 1;
	}

	if (zoneInput == "GMT" || zoneInput == "AZOST" || zoneInput == "EGST" || zoneInput == "WET" || zoneInput == "WT" || zoneInput == "Z")
	{
		convertedHours -= 0;
	}

	if (zoneInput == "CVT" || zoneInput == "AZOT" || zoneInput == "EGT" || zoneInput == "N")
	{
		convertedHours += 1;
	}

	if (zoneInput == "BRST" || zoneInput == "FNT" || zoneInput == "O" || zoneInput == "PMDT" || zoneInput == "UYST" || zoneInput == "WGST")
	{
		convertedHours += 2;
	}

	if (zoneInput == "ART" || zoneInput == "BRT" || zoneInput == "CLST" || zoneInput == "FKST" || zoneInput == "GFT" || zoneInput == "P" || zoneInput == "PMST" || zoneInput == "PYST" || zoneInput == "ROTT" || zoneInput == "SRT" || zoneInput == "UYT" || zoneInput == "WARST" || zoneInput == "WGT" || zoneInput == "NST")
	{
		convertedHours += 3;
	}

	if (zoneInput == "VET" || zoneInput == "BOT" || zoneInput == "CIDST" || zoneInput == "CLT" || zoneInput == "EDT" || zoneInput == "FKT" || zoneInput == "GYT" || zoneInput == "PYT" || zoneInput == "Q")
	{
		convertedHours += 4;
	}

	if (zoneInput == "EST" || zoneInput == "ACT" || zoneInput == "CIST" || zoneInput == "COT" || zoneInput == "EASST" || zoneInput == "ECT" || zoneInput == "PET" || zoneInput == "R")
	{
		convertedHours += 5;
	}

	if (zoneInput == "EAST" || zoneInput == "GALT" || zoneInput == "MDT" || zoneInput == "S")
	{
		convertedHours += 6;
	}

	if (zoneInput == "MST" || zoneInput == "PDT" || zoneInput == "T")
	{
		convertedHours += 7;
	}

	if (zoneInput == "PST" || zoneInput == "AKDT" || zoneInput == "U")
	{
		convertedHours += 8;
	}

	if (zoneInput == "AKST" || zoneInput == "GAMT" || zoneInput == "HDT" || zoneInput == "V" || zoneInput == "MART")
	{
		convertedHours += 9;
	}

	if (zoneInput == "HST" || zoneInput == "CKT" || zoneInput == "TAHT" || zoneInput == "W")
	{
		convertedHours += 10;
	}

	if (zoneInput == "NUT" || zoneInput == "SST" || zoneInput == "X")
	{
		convertedHours += 11;
	}

	if (zoneInput == "AoE" || zoneInput == "Y")
	{
		convertedHours += 12;
	}

	return convertedHours;
}

int timeMethods::HourToUTCDuplicateAbbreviation(int hourInput, string fullZoneName)
{
	int convertedHours = hourInput;

	if (fullZoneName == "West Samoa Time")
	{
		convertedHours -= 13;
	}

	if (fullZoneName == "Bougainville Standard Time")
	{
		convertedHours -= 11;
	}

	if (fullZoneName == "China Standard Time")
	{
		convertedHours -= 8;
	}

	if (fullZoneName == "Bangladesh Standard Time")
	{
		convertedHours -= 6;
	}

	if (fullZoneName == "India Standard Time" || fullZoneName == "Armenia Summer Time")
	{
		convertedHours -= 5;
	}

	if (fullZoneName == "Gulf Standard Time" || fullZoneName == "Arabia Daylight Time" || fullZoneName == "Armenia Time")
	{
		convertedHours -= 4;
	}

	if (fullZoneName == "Arabia Standard Time")
	{
		convertedHours -= 3;
	}

	if (fullZoneName == "Israel Standard Time")
	{
		convertedHours -= 2;
	}

	if (fullZoneName == "British Summer Time" || fullZoneName == "Irish Standard Time" || fullZoneName == "Western Sahara Summer Time")
	{
		convertedHours -= 1;
	}

	if (fullZoneName == "South Georgia Time")
	{
		convertedHours += 2;
	}

	if (fullZoneName == "Atlantic Daylight Time" || fullZoneName == "Amazon Summer Time")
	{
		convertedHours += 3;
	}

	if (fullZoneName == "Amazon Time" || fullZoneName == "Atlantic Standard Time" || fullZoneName == "Cuba Daylight Time")
	{
		convertedHours += 4;
	}

	if (fullZoneName == "Central Daylight Time" || fullZoneName == "Cuba Standard Time")
	{
		convertedHours += 5;
	}

	if (fullZoneName == "Central Standard Time")
	{
		convertedHours += 6;
	}

	return convertedHours;
}

int timeMethods::MinuteToUTC(int minuteInput, string zoneInput)
{
	int convertedMinutes = minuteInput;

	if (zoneInput == "CHADT" || zoneInput == "ACWST" || zoneInput == "NPT")
	{
		convertedMinutes -= 45;
	}

	if (zoneInput == "ACDT" || zoneInput == "LHST" || zoneInput == "ACST" || zoneInput == "MMT" || zoneInput == "CCT" || zoneInput == "IST" || zoneInput == "AFT" || zoneInput == "IRDT" || zoneInput == "IRST")
	{
		convertedMinutes -= 30;
	}

	if (zoneInput == "NST" || zoneInput == "MART")
	{
		convertedMinutes += 30;
	}

	return convertedMinutes;
}

// need to go through this function and remove duplicate abbreviation cases because convertHourUTCtoZoneHourDuplicateAbbreviation should be used instead for those cases
int timeMethods::convertHourUTCtoZoneHour(int hourUTC, string desiredZone)
{
	int convertedHours = hourUTC;

	if (desiredZone == "LINT" || desiredZone == "TOST")
	{
		convertedHours += 14;
	}

	if (desiredZone == "CHADT" || desiredZone == "NZDT" || desiredZone == "FJST" || desiredZone == "PHOT" || desiredZone == "TKT" || desiredZone == "TOT")
	{
		convertedHours += 13;
	}

	if (desiredZone == "ANAT" || desiredZone == "ANAST" || desiredZone == "FJT" || desiredZone == "GILT" || desiredZone == "M" || desiredZone == "MAGST" || desiredZone == "MHT" || desiredZone == "NFDT" || desiredZone == "NRT" || desiredZone == "NZST" || desiredZone == "PETST" || desiredZone == "PETT" || desiredZone == "TVT" || desiredZone == "WAKT" || desiredZone == "WFT")
	{
		convertedHours += 12;
	}

	if (desiredZone == "AEDT" || desiredZone == "KOST" || desiredZone == "L" || desiredZone == "LHDT" || desiredZone == "MAGT" || desiredZone == "NCT" || desiredZone == "NFT" || desiredZone == "PONT" || desiredZone == "SAKT" || desiredZone == "SBT" || desiredZone == "SRET" || desiredZone == "VLAST" || desiredZone == "VUT")
	{
		convertedHours += 11;
	}

	if (desiredZone == "ACDT" || desiredZone == "LHST" || desiredZone == "AEST" || desiredZone == "CHUT" || desiredZone == "CHST" || desiredZone == "DDUT" || desiredZone == "K" || desiredZone == "PGT" || desiredZone == "VLAT" || desiredZone == "YAKST" || desiredZone == "YAPT")
	{
		convertedHours += 10;
	}

	if (desiredZone == "ACST" || desiredZone == "JST" || desiredZone == "AWDT" || desiredZone == "CHOST" || desiredZone == "I" || desiredZone == "IRKST" || desiredZone == "KST" || desiredZone == "PWT" || desiredZone == "TLT" || desiredZone == "ULAST" || desiredZone == "WIT" || desiredZone == "YAKT")
	{
		convertedHours += 9;
	}

	if (desiredZone == "ACWST" || desiredZone == "AWST" || desiredZone == "BNT" || desiredZone == "CAST" || desiredZone == "CHOT" || desiredZone == "H" || desiredZone == "HKT" || desiredZone == "HOVST" || desiredZone == "IRKT" || desiredZone == "KRAST" || desiredZone == "MYT" || desiredZone == "PHT" || desiredZone == "SGT" || desiredZone == "ULAT" || desiredZone == "WITA")
	{
		convertedHours += 8;
	}

	if (desiredZone == "WIB" || desiredZone == "CXT" || desiredZone == "DAVT" || desiredZone == "G" || desiredZone == "HOVT" || desiredZone == "ICT" || desiredZone == "KRAT" || desiredZone == "NOVST" || desiredZone == "NOVT" || desiredZone == "OMSST")
	{
		convertedHours += 7;
	}

	if (desiredZone == "MMT" || desiredZone == "CCT" || desiredZone == "ALMT" || desiredZone == "BTT" || desiredZone == "F" || desiredZone == "IOT" || desiredZone == "KGT" || desiredZone == "OMST" || desiredZone == "QYZT" || desiredZone == "VOST" || desiredZone == "YEKST")
	{
		convertedHours += 6;
	}

	if (desiredZone == "NPT" || desiredZone == "UZT" || desiredZone == "AQTT" || desiredZone == "AZST" || desiredZone == "E" || desiredZone == "MAWT" || desiredZone == "MVT" || desiredZone == "ORAT" || desiredZone == "PKT" || desiredZone == "TFT" || desiredZone == "TJT" || desiredZone == "TMT" || desiredZone == "YEKT")
	{
		convertedHours += 5;
	}

	if (desiredZone == "AFT" || desiredZone == "IRDT" || desiredZone == "AZT" || desiredZone == "D" || desiredZone == "GET" || desiredZone == "KUYT" || desiredZone == "MSD" || desiredZone == "MUT" || desiredZone == "RET" || desiredZone == "SAMT" || desiredZone == "SCT")
	{
		convertedHours += 4;
	}

	if (desiredZone == "IRST" || desiredZone == "MSK" || desiredZone == "C" || desiredZone == "EAT" || desiredZone == "EEST" || desiredZone == "FET" || desiredZone == "IDT" || desiredZone == "SYOT" || desiredZone == "TRT")
	{
		convertedHours += 3;
	}

	if (desiredZone == "EET" || desiredZone == "B" || desiredZone == "CAT" || desiredZone == "CEST" || desiredZone == "SAST" || desiredZone == "WAST")
	{
		convertedHours += 2;
	}

	if (desiredZone == "CET" || desiredZone == "A" || desiredZone == "WAT" || desiredZone == "WEST")
	{
		convertedHours += 1;
	}

	if (desiredZone == "GMT" || desiredZone == "AZOST" || desiredZone == "EGST" || desiredZone == "WET" || desiredZone == "WT" || desiredZone == "Z")
	{
		convertedHours += 0;
	}

	if (desiredZone == "CVT" || desiredZone == "AZOT" || desiredZone == "EGT" || desiredZone == "N")
	{
		convertedHours -= 1;
	}

	if (desiredZone == "BRST" || desiredZone == "FNT" || desiredZone == "O" || desiredZone == "PMDT" || desiredZone == "UYST" || desiredZone == "WGST")
	{
		convertedHours -= 2;
	}

	if (desiredZone == "ART" || desiredZone == "BRT" || desiredZone == "CLST" || desiredZone == "FKST" || desiredZone == "GFT" || desiredZone == "P" || desiredZone == "PMST" || desiredZone == "PYST" || desiredZone == "ROTT" || desiredZone == "SRT" || desiredZone == "UYT" || desiredZone == "WARST" || desiredZone == "WGT" || desiredZone == "NST")
	{
		convertedHours -= 3;
	}

	if (desiredZone == "VET" || desiredZone == "BOT" || desiredZone == "CIDST" || desiredZone == "CLT" || desiredZone == "EDT" || desiredZone == "FKT" || desiredZone == "GYT" || desiredZone == "PYT" || desiredZone == "Q")
	{
		convertedHours -= 4;
	}

	if (desiredZone == "EST" || desiredZone == "ACT" || desiredZone == "CIST" || desiredZone == "COT" || desiredZone == "CST" || desiredZone == "EASST" || desiredZone == "ECT" || desiredZone == "PET" || desiredZone == "R")
	{
		convertedHours -= 5;
	}

	if (desiredZone == "EAST" || desiredZone == "GALT" || desiredZone == "MDT" || desiredZone == "S")
	{
		convertedHours -= 6;
	}

	if (desiredZone == "MST" || desiredZone == "PDT" || desiredZone == "T")
	{
		convertedHours -= 7;
	}

	if (desiredZone == "PST" || desiredZone == "AKDT" || desiredZone == "U")
	{
		convertedHours -= 8;
	}

	if (desiredZone == "AKST" || desiredZone == "GAMT" || desiredZone == "HDT" || desiredZone == "V" || desiredZone == "MART")
	{
		convertedHours -= 9;
	}

	if (desiredZone == "HST" || desiredZone == "CKT" || desiredZone == "TAHT" || desiredZone == "W")
	{
		convertedHours -= 10;
	}

	if (desiredZone == "NUT" || desiredZone == "SST" || desiredZone == "X")
	{
		convertedHours -= 11;
	}

	if (desiredZone == "AoE" || desiredZone == "Y")
	{
		convertedHours -= 12;
	}

	return convertedHours;
}

int timeMethods::convertHourUTCtoZoneHourDuplicateAbbreviation(int hourUTC, string desiredZone)
{
	int convertedHours = hourUTC;

	if (desiredZone == "West Samoa Time")
	{
		convertedHours += 13;
	}

	if (desiredZone == "Bougainville Standard Time")
	{
		convertedHours += 11;
	}

	if (desiredZone == "China Standard Time")
	{
		convertedHours += 8;
	}

	if (desiredZone == "Bangladesh Standard Time")
	{
		convertedHours += 6;
	}

	if (desiredZone == "India Standard Time" || desiredZone == "Armenia Summer Time")
	{
		convertedHours += 5;
	}

	if (desiredZone == "Gulf Standard Time" || desiredZone == "Arabia Daylight Time" || desiredZone == "Armenia Time")
	{
		convertedHours += 4;
	}

	if (desiredZone == "Arabia Standard Time")
	{
		convertedHours += 3;
	}

	if (desiredZone == "Israel Standard Time")
	{
		convertedHours += 2;
	}

	if (desiredZone == "British Summer Time" || desiredZone == "Irish Standard Time" || desiredZone == "Western Sahara Summer Time")
	{
		convertedHours += 1;
	}

	if (desiredZone == "South Georgia Time")
	{
		convertedHours -= 2;
	}

	if (desiredZone == "Atlantic Daylight Time" || desiredZone == "Amazon Summer Time")
	{
		convertedHours -= 3;
	}

	if (desiredZone == "Amazon Time" || desiredZone == "Atlantic Standard Time" || desiredZone == "Cuba Daylight Time")
	{
		convertedHours -= 4;
	}

	if (desiredZone == "Central Daylight Time" || desiredZone == "Cuba Standard Time")
	{
		convertedHours -= 5;
	}

	if (desiredZone == "Central Standard Time")
	{
		convertedHours -= 6;
	}

	return convertedHours;
}

int timeMethods::convertMinuteUTCtoZoneMinute(int minuteUTC, string desiredZone)
{
	int convertedMinutes = minuteUTC;

	if (desiredZone == "CHADT" || desiredZone == "ACWST" || desiredZone == "NPT")
	{
		convertedMinutes += 45;
	}

	if (desiredZone == "ACDT" || desiredZone == "LHST" || desiredZone == "ACST" || desiredZone == "MMT" || desiredZone == "CCT" || desiredZone == "IST" || desiredZone == "AFT" || desiredZone == "IRDT" || desiredZone == "IRST")
	{
		convertedMinutes += 30;
	}

	if (desiredZone == "NST" || desiredZone == "MART")
	{
		convertedMinutes -= 30;
	}

	return convertedMinutes;
}

int timeMethods::setClockTypeTo12()
{
	if (clockType == 12)
	{
		cout << endl << "Clock type is already set to " << clockType << "." << endl;
	}
	else
	{
		clockType = 12;
		cout << endl << "Clock type has been set to " << clockType << "." << endl;
	}

	return clockType;
}

int timeMethods::setClockTypeTo24()
{
	if (clockType == 24)
	{
		cout << endl << "Clock type is already set to " << clockType << "." << endl;
	}
	else
	{
		clockType = 24;
		cout << endl << "Clock type has been set to " << clockType << "." << endl;
	}

	return clockType;
}

int timeMethods::getClockType()
{
	return clockType;
}

bool timeMethods::isEmpty()
{
	if (head == nullptr)
	{
		return true;
	}

	return false;
}