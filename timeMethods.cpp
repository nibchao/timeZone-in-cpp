/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
*  Accepted time zones in this program are based on the ones listed on https://www.timeanddate.com/time/current-number-time-zones.html
*/

#include <iostream>
#include <string>
#include "timeMethods.h"

using namespace std;

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
void timeMethods::storeTime(int hours, int minutes, string meridiemAbbreviation, string zoneName)
{
	Node* newNode = new Node;
	newNode->hour = hours;
	newNode->minute = minutes;
	newNode->meridiem = meridiemAbbreviation;
	newNode->zone = zoneName;
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
	if (minutes < 10)
	{
		cout << endl << hours << ":0" << minutes << " " << meridiemAbbreviation << " " << zoneName << " has been stored." << endl << endl;
	}
	else
	{
		cout << endl << hours << ":" << minutes << " " << meridiemAbbreviation << " " << zoneName << " has been stored." << endl << endl;
	}
}

// deleteTime method - 12-Hour Clock Version
void timeMethods::deleteTime(int hours, int minutes, string meridiemAbbreviation, string zoneName)
{
	Node* currentNode = head;

	if (!head)
	{
		cout << "There were no times added so no times were deleted." << endl << endl;
		return;
	}

	if (head->hour == hours && head->minute == minutes && head->meridiem == meridiemAbbreviation && head->zone == zoneName)
	{
		head = currentNode->next;
		delete(currentNode);
		if (minutes < 10)
		{
			cout << hours << ":0" << minutes << " " << meridiemAbbreviation << " " << zoneName << " has been deleted." << endl << endl;
		}
		else
		{
			cout << hours << ":" << minutes << " " << meridiemAbbreviation << " " << zoneName << " has been deleted." << endl << endl;
		}
		return;
	}

	while (currentNode != nullptr && currentNode->next->hour != hours && currentNode->next->minute != minutes && currentNode->next->meridiem != meridiemAbbreviation && currentNode->next->zone != zoneName)
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

	if (minutes < 10)
	{
		cout << hours << ":0" << minutes << " " << meridiemAbbreviation << " " << zoneName << " has been deleted." << endl << endl;
	}
	else
	{
		cout << hours << ":" << minutes << " " << meridiemAbbreviation << " " << zoneName << " has been deleted." << endl << endl;
	}
}

// searchTime method - 12-Hour Clock Version
bool timeMethods::searchTime(int hours, int minutes, string meridiemAbbreviation, string zoneName)
{
	Node* currentNode = head;

	if (head == nullptr)
	{
		cout << "No stored times were found." << endl;
		return false;
	}

	while (currentNode)
	{
		if (currentNode->hour == hours && currentNode->minute == minutes && currentNode->meridiem == meridiemAbbreviation && currentNode->zone == zoneName)
		{
			cout << "Specified time was found in the list of stored times." << endl << endl;
			return true;
		}
		currentNode = currentNode->next;
	}
	cout << endl << "Specified time was not found in the list of stored times." << endl << endl;
	return false;
}

// overloaded storeTime method - 24-Hour Clock Version
void timeMethods::storeTime(int hours, int minutes, string zoneName)
{
	Node* newNode = new Node;
	newNode->hour = hours;
	newNode->minute = minutes;
	newNode->zone = zoneName;
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

	if (hours < 10)
	{
		if (minutes < 10)
		{
			cout << endl << "0" << hours << ":0" << minutes << " " << zoneName << " has been stored." << endl << endl;
		}
		else
		{
			cout << endl << "0" << hours << ":" << minutes << " " << zoneName << " has been stored." << endl << endl;
		}
	}
	else
	{
		cout << endl << hours << ":" << minutes << " " << zoneName << " has been stored." << endl << endl;
	}
}

// overloaded deleteTime method - 24-Hour Clock Version
void timeMethods::deleteTime(int hours, int minutes, string zoneName)
{
	Node* currentNode = head;

	if (!head)
	{
		cout << "There were no times added so no times were deleted." << endl << endl;
		return;
	}

	if (head->hour == hours && head->minute == minutes && head->zone == zoneName)
	{
		head = currentNode->next;
		delete(currentNode);
		if (minutes < 10)
		{
			cout << hours << ":0" << minutes << " " << zoneName << " has been deleted." << endl << endl;
		}
		else
		{
			cout << hours << ":" << minutes << " " << zoneName << " has been deleted." << endl << endl;
		}
		return;
	}

	while (currentNode != nullptr && currentNode->next->hour != hours && currentNode->next->minute != minutes && currentNode->next->zone != zoneName)
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

	if (minutes < 10)
	{
		cout << hours << ":0" << minutes << " " << zoneName << " has been deleted." << endl << endl;
	}
	else
	{
		cout << hours << ":" << minutes << " " << zoneName << " has been deleted." << endl << endl;
	}
}

// overloaded searchTime method - 24-Hour Clock Version
bool timeMethods::searchTime(int hours, int minutes, string zoneName)
{
	Node* currentNode = head;

	if (head == nullptr)
	{
		cout << "No stored times were found." << endl;
		return false;
	}

	while (currentNode)
	{
		if (currentNode->hour == hours && currentNode->minute == minutes && currentNode->zone == zoneName)
		{
			cout << "Specified time was found in the list of stored times." << endl << endl;
			return true;
		}
		currentNode = currentNode->next;
	}
	cout << endl << "Specified time was not found in the list of stored times." << endl << endl;
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
				cout << "(" << counter << ") " << currentNode->hour << ":" << currentNode->minute << " " << currentNode->zone << endl;
			}
			counter++;
			currentNode = currentNode->next;
		}
	}
	cout << endl;
}

int timeMethods::HourToUTC(int hours, string zoneName)
{
	int convertedHours = hours;

	if (zoneName == "LINT" || zoneName == "TOST")
	{
		convertedHours -= 14;
		return convertedHours;
	}

	if (zoneName == "CHADT" || zoneName == "NZDT" || zoneName == "FJST" || zoneName == "PHOT" || zoneName == "TKT" || zoneName == "TOT")
	{
		convertedHours -= 13;
		return convertedHours;
	}

	if (zoneName == "ANAT" || zoneName == "ANAST" || zoneName == "FJT" || zoneName == "GILT" || zoneName == "M" || zoneName == "MAGST" || zoneName == "MHT" || zoneName == "NFDT" || zoneName == "NRT" || zoneName == "NZST" || zoneName == "PETST" || zoneName == "PETT" || zoneName == "TVT" || zoneName == "WAKT" || zoneName == "WFT")
	{
		convertedHours -= 12;
		return convertedHours;
	}

	if (zoneName == "AEDT" || zoneName == "KOST" || zoneName == "L" || zoneName == "LHDT" || zoneName == "MAGT" || zoneName == "NCT" || zoneName == "NFT" || zoneName == "PONT" || zoneName == "SAKT" || zoneName == "SBT" || zoneName == "SRET" || zoneName == "VLAST" || zoneName == "VUT")
	{
		convertedHours -= 11;
		return convertedHours;
	}

	if (zoneName == "ACDT" || zoneName == "LHST" || zoneName == "AEST" || zoneName == "CHUT" || zoneName == "CHST" || zoneName == "DDUT" || zoneName == "K" || zoneName == "PGT" || zoneName == "VLAT" || zoneName == "YAKST" || zoneName == "YAPT")
	{
		convertedHours -= 10;
		return convertedHours;
	}

	if (zoneName == "ACST" || zoneName == "JST" || zoneName == "AWDT" || zoneName == "CHOST" || zoneName == "I" || zoneName == "IRKST" || zoneName == "KST" || zoneName == "PWT" || zoneName == "TLT" || zoneName == "ULAST" || zoneName == "WIT" || zoneName == "YAKT")
	{
		convertedHours -= 9;
		return convertedHours;
	}

	if (zoneName == "ACWST" || zoneName == "AWST" || zoneName == "BNT" || zoneName == "CAST" || zoneName == "CHOT" || zoneName == "H" || zoneName == "HKT" || zoneName == "HOVST" || zoneName == "IRKT" || zoneName == "KRAST" || zoneName == "MYT" || zoneName == "PHT" || zoneName == "SGT" || zoneName == "ULAT" || zoneName == "WITA")
	{
		convertedHours -= 8;
		return convertedHours;
	}

	if (zoneName == "WIB" || zoneName == "CXT" || zoneName == "DAVT" || zoneName == "G" || zoneName == "HOVT" || zoneName == "ICT" || zoneName == "KRAT" || zoneName == "NOVST" || zoneName == "NOVT" || zoneName == "OMSST")
	{
		convertedHours -= 7;
		return convertedHours;
	}

	if (zoneName == "MMT" || zoneName == "CCT" || zoneName == "ALMT" || zoneName == "BTT" || zoneName == "F" || zoneName == "IOT" || zoneName == "KGT" || zoneName == "OMST" || zoneName == "QYZT" || zoneName == "VOST" || zoneName == "YEKST")
	{
		convertedHours -= 6;
		return convertedHours;
	}

	if (zoneName == "NPT" || zoneName == "UZT" || zoneName == "AQTT" || zoneName == "AZST" || zoneName == "E" || zoneName == "MAWT" || zoneName == "MVT" || zoneName == "ORAT" || zoneName == "PKT" || zoneName == "TFT" || zoneName == "TJT" || zoneName == "TMT" || zoneName == "YEKT")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (zoneName == "AFT" || zoneName == "IRDT" || zoneName == "AZT" || zoneName == "D" || zoneName == "GET" || zoneName == "KUYT" || zoneName == "MSD" || zoneName == "MUT" || zoneName == "RET" || zoneName == "SAMT" || zoneName == "SCT")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (zoneName == "IRST" || zoneName == "MSK" || zoneName == "C" || zoneName == "EAT" || zoneName == "EEST" || zoneName == "FET" || zoneName == "IDT" || zoneName == "SYOT" || zoneName == "TRT")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (zoneName == "EET" || zoneName == "B" || zoneName == "CAT" || zoneName == "CEST" || zoneName == "SAST" || zoneName == "WAST")
	{
		convertedHours -= 2;
		return convertedHours;
	}

	if (zoneName == "CET" || zoneName == "A" || zoneName == "WAT" || zoneName == "WEST")
	{
		convertedHours -= 1;
		return convertedHours;
	}

	if (zoneName == "GMT" || zoneName == "AZOST" || zoneName == "EGST" || zoneName == "WET" || zoneName == "WT" || zoneName == "Z")
	{
		convertedHours -= 0;
		return convertedHours;
	}

	if (zoneName == "CVT" || zoneName == "AZOT" || zoneName == "EGT" || zoneName == "N")
	{
		convertedHours += 1;
		return convertedHours;
	}

	if (zoneName == "BRST" || zoneName == "FNT" || zoneName == "O" || zoneName == "PMDT" || zoneName == "UYST" || zoneName == "WGST")
	{
		convertedHours += 2;
		return convertedHours;
	}

	if (zoneName == "ART" || zoneName == "BRT" || zoneName == "CLST" || zoneName == "FKST" || zoneName == "GFT" || zoneName == "P" || zoneName == "PMST" || zoneName == "PYST" || zoneName == "ROTT" || zoneName == "SRT" || zoneName == "UYT" || zoneName == "WARST" || zoneName == "WGT" || zoneName == "NST")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (zoneName == "VET" || zoneName == "BOT" || zoneName == "CIDST" || zoneName == "CLT" || zoneName == "EDT" || zoneName == "FKT" || zoneName == "GYT" || zoneName == "PYT" || zoneName == "Q")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (zoneName == "EST" || zoneName == "ACT" || zoneName == "CIST" || zoneName == "COT" || zoneName == "EASST" || zoneName == "ECT" || zoneName == "PET" || zoneName == "R")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (zoneName == "EAST" || zoneName == "GALT" || zoneName == "MDT" || zoneName == "S")
	{
		convertedHours += 6;
		return convertedHours;
	}

	if (zoneName == "MST" || zoneName == "PDT" || zoneName == "T")
	{
		convertedHours += 7;
		return convertedHours;
	}

	if (zoneName == "PST" || zoneName == "AKDT" || zoneName == "U")
	{
		convertedHours += 8;
		return convertedHours;
	}

	if (zoneName == "AKST" || zoneName == "GAMT" || zoneName == "HDT" || zoneName == "V" || zoneName == "MART")
	{
		convertedHours += 9;
		return convertedHours;
	}

	if (zoneName == "HST" || zoneName == "CKT" || zoneName == "TAHT" || zoneName == "W")
	{
		convertedHours += 10;
		return convertedHours;
	}

	if (zoneName == "NUT" || zoneName == "SST" || zoneName == "X")
	{
		convertedHours += 11;
		return convertedHours;
	}

	if (zoneName == "AoE" || zoneName == "Y")
	{
		convertedHours += 12;
		return convertedHours;
	}

	return convertedHours;
}

int timeMethods::HourToUTCDuplicateAbbreviation(int hours, string fullZoneName)
{
	int convertedHours = hours;

	if (fullZoneName == "West Samoa Time")
	{
		convertedHours -= 13;
		return convertedHours;
	}

	if (fullZoneName == "Bougainville Standard Time")
	{
		convertedHours -= 11;
		return convertedHours;
	}

	if (fullZoneName == "China Standard Time")
	{
		convertedHours -= 8;
		return convertedHours;
	}

	if (fullZoneName == "Bangladesh Standard Time")
	{
		convertedHours -= 6;
		return convertedHours;
	}

	if (fullZoneName == "India Standard Time" || fullZoneName == "Armenia Summer Time")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (fullZoneName == "Gulf Standard Time" || fullZoneName == "Arabia Daylight Time" || fullZoneName == "Armenia Time")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (fullZoneName == "Arabia Standard Time")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (fullZoneName == "Israel Standard Time")
	{
		convertedHours -= 2;
		return convertedHours;
	}

	if (fullZoneName == "British Summer Time" || fullZoneName == "Irish Standard Time" || fullZoneName == "Western Sahara Summer Time")
	{
		convertedHours -= 1;
		return convertedHours;
	}

	if (fullZoneName == "South Georgia Time")
	{
		convertedHours += 2;
		return convertedHours;
	}

	if (fullZoneName == "Atlantic Daylight Time" || fullZoneName == "Amazon Summer Time")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (fullZoneName == "Amazon Time" || fullZoneName == "Atlantic Standard Time" || fullZoneName == "Cuba Daylight Time")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (fullZoneName == "Central Daylight Time" || fullZoneName == "Cuba Standard Time")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (fullZoneName == "Central Standard Time")
	{
		convertedHours += 6;
		return convertedHours;
	}

	return convertedHours;
}

int timeMethods::MinuteToUTC(int minutes, string zoneName)
{
	int convertedMinutes = minutes;

	if (zoneName == "CHADT" || zoneName == "ACWST" || zoneName == "NPT")
	{
		convertedMinutes -= 45;
		return convertedMinutes;
	}

	if (zoneName == "ACDT" || zoneName == "LHST" || zoneName == "ACST" || zoneName == "MMT" || zoneName == "CCT" || zoneName == "IST" || zoneName == "AFT" || zoneName == "IRDT" || zoneName == "IRST")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "NST" || zoneName == "MART")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	return convertedMinutes;
}

int timeMethods::convertHourUTCtoZoneHour(int hours, string desiredZone)
{
	int convertedHours = hours;

	if (desiredZone == "LINT" || desiredZone == "TOST")
	{
		convertedHours += 14;
		return convertedHours;
	}

	if (desiredZone == "CHADT" || desiredZone == "NZDT" || desiredZone == "FJST" || desiredZone == "PHOT" || desiredZone == "TKT" || desiredZone == "TOT")
	{
		convertedHours += 13;
		return convertedHours;
	}

	if (desiredZone == "ANAT" || desiredZone == "ANAST" || desiredZone == "FJT" || desiredZone == "GILT" || desiredZone == "M" || desiredZone == "MAGST" || desiredZone == "MHT" || desiredZone == "NFDT" || desiredZone == "NRT" || desiredZone == "NZST" || desiredZone == "PETST" || desiredZone == "PETT" || desiredZone == "TVT" || desiredZone == "WAKT" || desiredZone == "WFT")
	{
		convertedHours += 12;
		return convertedHours;
	}

	if (desiredZone == "AEDT" || desiredZone == "KOST" || desiredZone == "L" || desiredZone == "LHDT" || desiredZone == "MAGT" || desiredZone == "NCT" || desiredZone == "NFT" || desiredZone == "PONT" || desiredZone == "SAKT" || desiredZone == "SBT" || desiredZone == "SRET" || desiredZone == "VLAST" || desiredZone == "VUT")
	{
		convertedHours += 11;
		return convertedHours;
	}

	if (desiredZone == "ACDT" || desiredZone == "LHST" || desiredZone == "AEST" || desiredZone == "CHUT" || desiredZone == "CHST" || desiredZone == "DDUT" || desiredZone == "K" || desiredZone == "PGT" || desiredZone == "VLAT" || desiredZone == "YAKST" || desiredZone == "YAPT")
	{
		convertedHours += 10;
		return convertedHours;
	}

	if (desiredZone == "ACST" || desiredZone == "JST" || desiredZone == "AWDT" || desiredZone == "CHOST" || desiredZone == "I" || desiredZone == "IRKST" || desiredZone == "KST" || desiredZone == "PWT" || desiredZone == "TLT" || desiredZone == "ULAST" || desiredZone == "WIT" || desiredZone == "YAKT")
	{
		convertedHours += 9;
		return convertedHours;
	}

	if (desiredZone == "ACWST" || desiredZone == "AWST" || desiredZone == "BNT" || desiredZone == "CAST" || desiredZone == "CHOT" || desiredZone == "H" || desiredZone == "HKT" || desiredZone == "HOVST" || desiredZone == "IRKT" || desiredZone == "KRAST" || desiredZone == "MYT" || desiredZone == "PHT" || desiredZone == "SGT" || desiredZone == "ULAT" || desiredZone == "WITA")
	{
		convertedHours += 8;
		return convertedHours;
	}

	if (desiredZone == "WIB" || desiredZone == "CXT" || desiredZone == "DAVT" || desiredZone == "G" || desiredZone == "HOVT" || desiredZone == "ICT" || desiredZone == "KRAT" || desiredZone == "NOVST" || desiredZone == "NOVT" || desiredZone == "OMSST")
	{
		convertedHours += 7;
		return convertedHours;
	}

	if (desiredZone == "MMT" || desiredZone == "CCT" || desiredZone == "ALMT" || desiredZone == "BTT" || desiredZone == "F" || desiredZone == "IOT" || desiredZone == "KGT" || desiredZone == "OMST" || desiredZone == "QYZT" || desiredZone == "VOST" || desiredZone == "YEKST")
	{
		convertedHours += 6;
		return convertedHours;
	}

	if (desiredZone == "NPT" || desiredZone == "UZT" || desiredZone == "AQTT" || desiredZone == "AZST" || desiredZone == "E" || desiredZone == "MAWT" || desiredZone == "MVT" || desiredZone == "ORAT" || desiredZone == "PKT" || desiredZone == "TFT" || desiredZone == "TJT" || desiredZone == "TMT" || desiredZone == "YEKT")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (desiredZone == "AFT" || desiredZone == "IRDT" || desiredZone == "AZT" || desiredZone == "D" || desiredZone == "GET" || desiredZone == "KUYT" || desiredZone == "MSD" || desiredZone == "MUT" || desiredZone == "RET" || desiredZone == "SAMT" || desiredZone == "SCT")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (desiredZone == "IRST" || desiredZone == "MSK" || desiredZone == "C" || desiredZone == "EAT" || desiredZone == "EEST" || desiredZone == "FET" || desiredZone == "IDT" || desiredZone == "SYOT" || desiredZone == "TRT")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (desiredZone == "EET" || desiredZone == "B" || desiredZone == "CAT" || desiredZone == "CEST" || desiredZone == "SAST" || desiredZone == "WAST")
	{
		convertedHours += 2;
		return convertedHours;
	}

	if (desiredZone == "CET" || desiredZone == "A" || desiredZone == "WAT" || desiredZone == "WEST")
	{
		convertedHours += 1;
		return convertedHours;
	}

	if (desiredZone == "GMT" || desiredZone == "AZOST" || desiredZone == "EGST" || desiredZone == "WET" || desiredZone == "WT" || desiredZone == "Z")
	{
		convertedHours += 0;
		return convertedHours;
	}

	if (desiredZone == "CVT" || desiredZone == "AZOT" || desiredZone == "EGT" || desiredZone == "N")
	{
		convertedHours -= 1;
		return convertedHours;
	}

	if (desiredZone == "BRST" || desiredZone == "FNT" || desiredZone == "O" || desiredZone == "PMDT" || desiredZone == "UYST" || desiredZone == "WGST")
	{
		convertedHours -= 2;
		return convertedHours;
	}

	if (desiredZone == "ART" || desiredZone == "BRT" || desiredZone == "CLST" || desiredZone == "FKST" || desiredZone == "GFT" || desiredZone == "P" || desiredZone == "PMST" || desiredZone == "PYST" || desiredZone == "ROTT" || desiredZone == "SRT" || desiredZone == "UYT" || desiredZone == "WARST" || desiredZone == "WGT" || desiredZone == "NST")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (desiredZone == "VET" || desiredZone == "BOT" || desiredZone == "CIDST" || desiredZone == "CLT" || desiredZone == "EDT" || desiredZone == "FKT" || desiredZone == "GYT" || desiredZone == "PYT" || desiredZone == "Q")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (desiredZone == "EST" || desiredZone == "ACT" || desiredZone == "CIST" || desiredZone == "COT" || desiredZone == "CST" || desiredZone == "EASST" || desiredZone == "ECT" || desiredZone == "PET" || desiredZone == "R")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (desiredZone == "EAST" || desiredZone == "GALT" || desiredZone == "MDT" || desiredZone == "S")
	{
		convertedHours -= 6;
		return convertedHours;
	}

	if (desiredZone == "MST" || desiredZone == "PDT" || desiredZone == "T")
	{
		convertedHours -= 7;
		return convertedHours;
	}

	if (desiredZone == "PST" || desiredZone == "AKDT" || desiredZone == "U")
	{
		convertedHours -= 8;
		return convertedHours;
	}

	if (desiredZone == "AKST" || desiredZone == "GAMT" || desiredZone == "HDT" || desiredZone == "V" || desiredZone == "MART")
	{
		convertedHours -= 9;
		return convertedHours;
	}

	if (desiredZone == "HST" || desiredZone == "CKT" || desiredZone == "TAHT" || desiredZone == "W")
	{
		convertedHours -= 10;
		return convertedHours;
	}

	if (desiredZone == "NUT" || desiredZone == "SST" || desiredZone == "X")
	{
		convertedHours -= 11;
		return convertedHours;
	}

	if (desiredZone == "AoE" || desiredZone == "Y")
	{
		convertedHours -= 12;
		return convertedHours;
	}

	return convertedHours;
}

int timeMethods::convertHourUTCtoZoneHourDuplicateAbbreviation(int hours, string desiredZone)
{
	int convertedHours = hours;

	if (desiredZone == "West Samoa Time")
	{
		convertedHours += 13;
		return convertedHours;
	}

	if (desiredZone == "Bougainville Standard Time")
	{
		convertedHours += 11;
		return convertedHours;
	}

	if (desiredZone == "China Standard Time")
	{
		convertedHours += 8;
		return convertedHours;
	}

	if (desiredZone == "Bangladesh Standard Time")
	{
		convertedHours += 6;
		return convertedHours;
	}

	if (desiredZone == "India Standard Time" || desiredZone == "Armenia Summer Time")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (desiredZone == "Gulf Standard Time" || desiredZone == "Arabia Daylight Time" || desiredZone == "Armenia Time")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (desiredZone == "Arabia Standard Time")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (desiredZone == "Israel Standard Time")
	{
		convertedHours += 2;
		return convertedHours;
	}

	if (desiredZone == "British Summer Time" || desiredZone == "Irish Standard Time" || desiredZone == "Western Sahara Summer Time")
	{
		convertedHours += 1;
		return convertedHours;
	}

	if (desiredZone == "South Georgia Time")
	{
		convertedHours -= 2;
		return convertedHours;
	}

	if (desiredZone == "Atlantic Daylight Time" || desiredZone == "Amazon Summer Time")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (desiredZone == "Amazon Time" || desiredZone == "Atlantic Standard Time" || desiredZone == "Cuba Daylight Time")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (desiredZone == "Central Daylight Time" || desiredZone == "Cuba Standard Time")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (desiredZone == "Central Standard Time")
	{
		convertedHours -= 6;
		return convertedHours;
	}

	return convertedHours;
}

int timeMethods::convertMinuteUTCtoZoneMinute(int minutes, string desiredZone)
{
	int convertedMinutes = minutes;

	if (desiredZone == "CHADT" || desiredZone == "ACWST" || desiredZone == "NPT")
	{
		convertedMinutes += 45;
		return convertedMinutes;
	}

	if (desiredZone == "ACDT" || desiredZone == "LHST" || desiredZone == "ACST" || desiredZone == "MMT" || desiredZone == "CCT" || desiredZone == "IST" || desiredZone == "AFT" || desiredZone == "IRDT" || desiredZone == "IRST")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "NST" || desiredZone == "MART")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
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
		cout << endl << "Clock type is set to " << clockType << "." << endl;
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
		cout << endl << "Clock type is set to " << clockType << "." << endl;
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