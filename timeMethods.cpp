/*
*  Created by: Nicholas Chao
*  Purpose: To convert a time in one time zone to another time zone
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
	nodeCount = 0;
}

void timeMethods::storeTime(int hours, int minutes, string zoneName)
{
	if (hours < 0)
	{
		cout << "Error: The time value for hours, " << hours << " is negative which is not an accepted input (no negative time values)." << "The given time will not be stored." << endl;
		return;
	}
	if (minutes < 0)
	{
		cout << "Error: The time value for minutes, " << minutes << " is negative which is not an accepted input (no negative time values)." << "The given time will not be stored." << endl;
		return;
	}

	Node* newNode = new Node;
	newNode->hour = hours;
	newNode->minute = minutes;
	newNode->zone = zoneName;
	newNode->next = nullptr;

	Node* currentNode = head;

	if (head == nullptr)
	{
		head = newNode;
		nodeCount++;
	}
	else
	{
		while (currentNode->next)
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
		nodeCount++;
	}
	cout << endl << hours << ":" << minutes << " " << zoneName << " has been stored." << endl << endl;
}

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
		cout << hours << ":" << minutes << " has been deleted." << endl << endl;
		nodeCount--;
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

	cout << hours << ":" << minutes << " " << zoneName << " has been deleted." << endl << endl;
	nodeCount--;
	return;
}

void timeMethods::displayStoredTimes() const
{
	Node* currentNode = head;
	int counter = 0;

	while (currentNode)
	{
		cout << "(" << counter << ") " << currentNode->hour << ":" << currentNode->minute << " " << currentNode->zone << endl;
		counter++;
		currentNode = currentNode->next;
	}
}

bool timeMethods::searchTime(int hours, int minutes, string zoneName)
{
	Node* currentNode = head;

	if (head == nullptr)
	{
		cout << "There were no stored times found." << endl;
		return false;
	}

	while (currentNode)
	{
		if (currentNode->hour == hours && currentNode->minute == minutes && currentNode->zone == zoneName)
		{
			cout << "Specified time was found in the list of stored times." << endl;
			return true;
		}
		currentNode = currentNode->next;
	}
	cout << "Specified time was not found in the list of stored times." << endl;
	return false;
}

// add a function in the main that asks user to input the region they are in/their time is in because there are conflicts with
// time zone abbreviations such as CST having two meanings - China Standard Time and Central Standard Time
// this would cause issues with converting the user's time to UTC then to desired time zone

// potential solution could be to split the HourToUTC function into three general regions (Americas, Europe, Asia)

// the time zones checked for inside this function are based on those listed on https://www.timeanddate.com/time/current-number-time-zones.html
int timeMethods::HourToUTC(int hours, string zoneName)
{
	int convertedHours = hours;

	if (zoneName == "LINT" || zoneName == "TOST")
	{
		convertedHours -= 14;
		return convertedHours;
	}

	if (zoneName == "CHADT")
	{
		convertedHours -= 13;
		return convertedHours;
	}

	if (zoneName == "NZDT" || zoneName == "FJST" || zoneName == "PHOT" || zoneName == "TKT" || zoneName == "TOT" || zoneName == "WST")
	{
		convertedHours -= 13;
		return convertedHours;
	}

	if (zoneName == "ANAT" || zoneName == "ANAST" || zoneName == "FJT" || zoneName == "GILT" || zoneName == "M" || zoneName == "MAGST" || zoneName == "MHT" || zoneName == "NFDT" || zoneName == "NRT" || zoneName == "NZST" || zoneName == "PETST" || zoneName == "PETT" || zoneName == "TVT" || zoneName == "WAKT" || zoneName == "WFT")
	{
		convertedHours -= 12;
		return convertedHours;
	}

	if (zoneName == "AEDT" || zoneName == "BST" || zoneName == "KOST" || zoneName == "L" || zoneName == "LHDT" || zoneName == "MAGT" || zoneName == "NCT" || zoneName == "NFT" || zoneName == "PONT" || zoneName == "SAKT" || zoneName == "SBT" || zoneName == "SRET" || zoneName == "VLAST" || zoneName == "VUT")
	{
		convertedHours -= 11;
		return convertedHours;
	}

	if (zoneName == "ACDT" || zoneName == "LHST")
	{
		convertedHours -= 10;
		return convertedHours;
	}

	if (zoneName == "AEST" || zoneName == "CHUT" || zoneName == "CHST" || zoneName == "DDUT" || zoneName == "K" || zoneName == "PGT" || zoneName == "VLAT" || zoneName == "YAKST" || zoneName == "YAPT")
	{
		convertedHours -= 10;
		return convertedHours;
	}

	if (zoneName == "ACST")
	{
		convertedHours -= 9;
		return convertedHours;
	}

	if (zoneName == "JST" || zoneName == "AWDT" || zoneName == "CHOST" || zoneName == "I" || zoneName == "IRKST" || zoneName == "KST" || zoneName == "PWT" || zoneName == "TLT" || zoneName == "ULAST" || zoneName == "WIT" || zoneName == "YAKT")
	{
		convertedHours -= 9;
		return convertedHours;
	}

	if (zoneName == "ACWST")
	{
		convertedHours -= 8;
		return convertedHours;
	}

	if (zoneName == "CST" || zoneName == "AWST" || zoneName == "BNT" || zoneName == "CAST" || zoneName == "CHOT" || zoneName == "H" || zoneName == "HKT" || zoneName == "HOVST" || zoneName == "IRKT" || zoneName == "KRAST" || zoneName == "MYT" || zoneName == "PHT" || zoneName == "SGT" || zoneName == "ULAT" || zoneName == "WITA")
	{
		convertedHours -= 8;
		return convertedHours;
	}

	if (zoneName == "WIB" || zoneName == "CXT" || zoneName == "DAVT" || zoneName == "G" || zoneName == "HOVT" || zoneName == "ICT" || zoneName == "KRAT" || zoneName == "NOVST" || zoneName == "NOVT" || zoneName == "OMSST")
	{
		convertedHours -= 7;
		return convertedHours;
	}

	if (zoneName == "MMT" || zoneName == "CCT")
	{
		convertedHours -= 6;
		return convertedHours;
	}

	if (zoneName == "BST" || zoneName == "ALMT" || zoneName == "BTT" || zoneName == "F" || zoneName == "IOT" || zoneName == "KGT" || zoneName == "OMST" || zoneName == "QYZT" || zoneName == "VOST" || zoneName == "YEKST")
	{
		convertedHours -= 6;
		return convertedHours;
	}

	if (zoneName == "NPT")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (zoneName == "IST")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (zoneName == "UZT" || zoneName == "AMST" || zoneName == "AQTT" || zoneName == "AZST" || zoneName == "E" || zoneName == "MAWT" || zoneName == "MVT" || zoneName == "ORAT" || zoneName == "PKT" || zoneName == "TFT" || zoneName == "TJT" || zoneName == "TMT" || zoneName == "YEKT")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (zoneName == "AFT" || zoneName == "IRDT")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (zoneName == "GST" || zoneName == "ADT" || zoneName == "AMT" || zoneName == "AZT" || zoneName == "D" || zoneName == "GET" || zoneName == "KUYT" || zoneName == "MSD" || zoneName == "MUT" || zoneName == "RET" || zoneName == "SAMT" || zoneName == "SCT")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (zoneName == "IRST")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (zoneName == "MSK" || zoneName == "AST" || zoneName == "C" || zoneName == "EAT" || zoneName == "EEST" || zoneName == "FET" || zoneName == "IDT" || zoneName == "SYOT" || zoneName == "TRT")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (zoneName == "EET" || zoneName == "B" || zoneName == "CAT" || zoneName == "CEST" || zoneName == "IST" || zoneName == "SAST" || zoneName == "WAST")
	{
		convertedHours -= 2;
		return convertedHours;
	}

	if (zoneName == "CET" || zoneName == "A" || zoneName == "BST" || zoneName == "IST" || zoneName == "WAT" || zoneName == "WEST" || zoneName == "WST")
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

	if (zoneName == "GST" || zoneName == "BRST" || zoneName == "FNT" || zoneName == "O" || zoneName == "PMDT" || zoneName == "UYST" || zoneName == "WGST")
	{
		convertedHours += 2;
		return convertedHours;
	}

	if (zoneName == "ART" || zoneName == "ADT" || zoneName == "AMST" || zoneName == "BRT" || zoneName == "CLST" || zoneName == "FKST" || zoneName == "GFT" || zoneName == "P" || zoneName == "PMST" || zoneName == "PYST" || zoneName == "ROTT" || zoneName == "SRT" || zoneName == "UYT" || zoneName == "WARST" || zoneName == "WGT")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (zoneName == "NST")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (zoneName == "VET" || zoneName == "AMT" || zoneName == "AST" || zoneName == "BOT" || zoneName == "CDT" || zoneName == "CIDST" || zoneName == "CLT" || zoneName == "EDT" || zoneName == "FKT" || zoneName == "GYT" || zoneName == "PYT" || zoneName == "Q")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (zoneName == "EST" || zoneName == "ACT" || zoneName == "CDT" || zoneName == "CIST" || zoneName == "COT" || zoneName == "CST" || zoneName == "EASST" || zoneName == "ECT" || zoneName == "PET" || zoneName == "R")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (zoneName == "CST" || zoneName == "EAST" || zoneName == "GALT" || zoneName == "MDT" || zoneName == "S")
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

	if (zoneName == "AKST" || zoneName == "GAMT" || zoneName == "HDT" || zoneName == "V")
	{
		convertedHours += 9;
		return convertedHours;
	}

	if (zoneName == "MART")
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

// time zones checked for in this function are based on those listed on https://www.timeanddate.com/time/current-number-time-zones.html
int timeMethods::MinuteToUTC(int minutes, string zoneName)
{
	int convertedMinutes = minutes;

	if (zoneName == "CHADT")
	{
		convertedMinutes -= 45;
		return convertedMinutes;
	}

	if (zoneName == "ACDT" || zoneName == "LHST")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "ACST")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "ACWST")
	{
		convertedMinutes -= 45;
		return convertedMinutes;
	}

	if (zoneName == "MMT" || zoneName == "CCT")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "NPT")
	{
		convertedMinutes -= 45;
		return convertedMinutes;
	}

	if (zoneName == "IST")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "AFT" || zoneName == "IRDT")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "IRST")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (zoneName == "NST")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (zoneName == "MART")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	return convertedMinutes;
}

// these two functions do not work properly
int timeMethods::convertHourUTCtoZoneHour(int hours, string desiredZone)
{
	int convertedHours = hours;

	if (desiredZone == "LINT" || desiredZone == "TOST")
	{
		convertedHours += 14;
		return convertedHours;
	}

	if (desiredZone == "CHADT")
	{
		convertedHours += 13;
		return convertedHours;
	}

	if (desiredZone == "NZDT" || desiredZone == "FJST" || desiredZone == "PHOT" || desiredZone == "TKT" || desiredZone == "TOT" || desiredZone == "WST")
	{
		convertedHours += 13;
		return convertedHours;
	}

	if (desiredZone == "ANAT" || desiredZone == "ANAST" || desiredZone == "FJT" || desiredZone == "GILT" || desiredZone == "M" || desiredZone == "MAGST" || desiredZone == "MHT" || desiredZone == "NFDT" || desiredZone == "NRT" || desiredZone == "NZST" || desiredZone == "PETST" || desiredZone == "PETT" || desiredZone == "TVT" || desiredZone == "WAKT" || desiredZone == "WFT")
	{
		convertedHours += 12;
		return convertedHours;
	}

	if (desiredZone == "AEDT" || desiredZone == "BST" || desiredZone == "KOST" || desiredZone == "L" || desiredZone == "LHDT" || desiredZone == "MAGT" || desiredZone == "NCT" || desiredZone == "NFT" || desiredZone == "PONT" || desiredZone == "SAKT" || desiredZone == "SBT" || desiredZone == "SRET" || desiredZone == "VLAST" || desiredZone == "VUT")
	{
		convertedHours += 11;
		return convertedHours;
	}

	if (desiredZone == "ACDT" || desiredZone == "LHST")
	{
		convertedHours += 10;
		return convertedHours;
	}

	if (desiredZone == "AEST" || desiredZone == "CHUT" || desiredZone == "CHST" || desiredZone == "DDUT" || desiredZone == "K" || desiredZone == "PGT" || desiredZone == "VLAT" || desiredZone == "YAKST" || desiredZone == "YAPT")
	{
		convertedHours += 10;
		return convertedHours;
	}

	if (desiredZone == "ACST")
	{
		convertedHours += 9;
		return convertedHours;
	}

	if (desiredZone == "JST" || desiredZone == "AWDT" || desiredZone == "CHOST" || desiredZone == "I" || desiredZone == "IRKST" || desiredZone == "KST" || desiredZone == "PWT" || desiredZone == "TLT" || desiredZone == "ULAST" || desiredZone == "WIT" || desiredZone == "YAKT")
	{
		convertedHours += 9;
		return convertedHours;
	}

	if (desiredZone == "ACWST")
	{
		convertedHours += 8;
		return convertedHours;
	}

	if (desiredZone == "CST" || desiredZone == "AWST" || desiredZone == "BNT" || desiredZone == "CAST" || desiredZone == "CHOT" || desiredZone == "H" || desiredZone == "HKT" || desiredZone == "HOVST" || desiredZone == "IRKT" || desiredZone == "KRAST" || desiredZone == "MYT" || desiredZone == "PHT" || desiredZone == "SGT" || desiredZone == "ULAT" || desiredZone == "WITA")
	{
		convertedHours += 8;
		return convertedHours;
	}

	if (desiredZone == "WIB" || desiredZone == "CXT" || desiredZone == "DAVT" || desiredZone == "G" || desiredZone == "HOVT" || desiredZone == "ICT" || desiredZone == "KRAT" || desiredZone == "NOVST" || desiredZone == "NOVT" || desiredZone == "OMSST")
	{
		convertedHours += 7;
		return convertedHours;
	}

	if (desiredZone == "MMT" || desiredZone == "CCT")
	{
		convertedHours += 6;
		return convertedHours;
	}

	if (desiredZone == "BST" || desiredZone == "ALMT" || desiredZone == "BTT" || desiredZone == "F" || desiredZone == "IOT" || desiredZone == "KGT" || desiredZone == "OMST" || desiredZone == "QYZT" || desiredZone == "VOST" || desiredZone == "YEKST")
	{
		convertedHours += 6;
		return convertedHours;
	}

	if (desiredZone == "NPT")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (desiredZone == "IST")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (desiredZone == "UZT" || desiredZone == "AMST" || desiredZone == "AQTT" || desiredZone == "AZST" || desiredZone == "E" || desiredZone == "MAWT" || desiredZone == "MVT" || desiredZone == "ORAT" || desiredZone == "PKT" || desiredZone == "TFT" || desiredZone == "TJT" || desiredZone == "TMT" || desiredZone == "YEKT")
	{
		convertedHours += 5;
		return convertedHours;
	}

	if (desiredZone == "AFT" || desiredZone == "IRDT")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (desiredZone == "GST" || desiredZone == "ADT" || desiredZone == "AMT" || desiredZone == "AZT" || desiredZone == "D" || desiredZone == "GET" || desiredZone == "KUYT" || desiredZone == "MSD" || desiredZone == "MUT" || desiredZone == "RET" || desiredZone == "SAMT" || desiredZone == "SCT")
	{
		convertedHours += 4;
		return convertedHours;
	}

	if (desiredZone == "IRST")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (desiredZone == "MSK" || desiredZone == "AST" || desiredZone == "C" || desiredZone == "EAT" || desiredZone == "EEST" || desiredZone == "FET" || desiredZone == "IDT" || desiredZone == "SYOT" || desiredZone == "TRT")
	{
		convertedHours += 3;
		return convertedHours;
	}

	if (desiredZone == "EET" || desiredZone == "B" || desiredZone == "CAT" || desiredZone == "CEST" || desiredZone == "IST" || desiredZone == "SAST" || desiredZone == "WAST")
	{
		convertedHours += 2;
		return convertedHours;
	}

	if (desiredZone == "CET" || desiredZone == "A" || desiredZone == "BST" || desiredZone == "IST" || desiredZone == "WAT" || desiredZone == "WEST" || desiredZone == "WST")
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

	if (desiredZone == "GST" || desiredZone == "BRST" || desiredZone == "FNT" || desiredZone == "O" || desiredZone == "PMDT" || desiredZone == "UYST" || desiredZone == "WGST")
	{
		convertedHours -= 2;
		return convertedHours;
	}

	if (desiredZone == "ART" || desiredZone == "ADT" || desiredZone == "AMST" || desiredZone == "BRT" || desiredZone == "CLST" || desiredZone == "FKST" || desiredZone == "GFT" || desiredZone == "P" || desiredZone == "PMST" || desiredZone == "PYST" || desiredZone == "ROTT" || desiredZone == "SRT" || desiredZone == "UYT" || desiredZone == "WARST" || desiredZone == "WGT")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (desiredZone == "NST")
	{
		convertedHours -= 3;
		return convertedHours;
	}

	if (desiredZone == "VET" || desiredZone == "AMT" || desiredZone == "AST" || desiredZone == "BOT" || desiredZone == "CDT" || desiredZone == "CIDST" || desiredZone == "CLT" || desiredZone == "EDT" || desiredZone == "FKT" || desiredZone == "GYT" || desiredZone == "PYT" || desiredZone == "Q")
	{
		convertedHours -= 4;
		return convertedHours;
	}

	if (desiredZone == "EST" || desiredZone == "ACT" || desiredZone == "CDT" || desiredZone == "CIST" || desiredZone == "COT" || desiredZone == "CST" || desiredZone == "EASST" || desiredZone == "ECT" || desiredZone == "PET" || desiredZone == "R")
	{
		convertedHours -= 5;
		return convertedHours;
	}

	if (desiredZone == "CST" || desiredZone == "EAST" || desiredZone == "GALT" || desiredZone == "MDT" || desiredZone == "S")
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

	if (desiredZone == "AKST" || desiredZone == "GAMT" || desiredZone == "HDT" || desiredZone == "V")
	{
		convertedHours -= 9;
		return convertedHours;
	}

	if (desiredZone == "MART")
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

int timeMethods::convertMinuteUTCtoZoneMinute(int minutes, string desiredZone)
{
	int convertedMinutes = minutes;

	if (desiredZone == "CHADT")
	{
		convertedMinutes += 45;
		return convertedMinutes;
	}

	if (desiredZone == "ACDT" || desiredZone == "LHST")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "ACST")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "ACWST")
	{
		convertedMinutes += 45;
		return convertedMinutes;
	}

	if (desiredZone == "MMT" || desiredZone == "CCT")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "NPT")
	{
		convertedMinutes += 45;
		return convertedMinutes;
	}

	if (desiredZone == "IST")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "AFT" || desiredZone == "IRDT")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "IRST")
	{
		convertedMinutes += 30;
		return convertedMinutes;
	}

	if (desiredZone == "NST")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	if (desiredZone == "MART")
	{
		convertedMinutes -= 30;
		return convertedMinutes;
	}

	return convertedMinutes;
}
//