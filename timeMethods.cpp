#include <iostream>
#include <string>
#include <algorithm>
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

void timeMethods::deleteTime(int hours, int minutes)
{
	Node* currentNode = head;

	if (!head)
	{
		cout << "There were no times added so no times were deleted." << endl << endl;
		return;
	}

	if (head->hour == hours && head->minute == minutes)
	{
		head = currentNode->next;
		delete(currentNode);
		cout << hours << ":" << minutes << " has been deleted." << endl << endl;
		nodeCount--;
		return;
	}

	while (currentNode != nullptr && currentNode->next->hour != hours && currentNode->next->minute != minutes)
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

	cout << hours << ":" << minutes << " has been deleted." << endl << endl;
	nodeCount--;
	return;
}

void timeMethods::displayStoredTimes() const
{
	Node* currentNode = head;
	int counter = 0;

	while (currentNode)
	{
		transform(currentNode->zone.begin(), currentNode->zone.end(), currentNode->zone.begin(), ::toupper);
		cout << "(" << counter << ") " << currentNode->hour << ":" << currentNode->minute << " " << currentNode->zone << endl;
		counter++;
		currentNode = currentNode->next;
	}
}

// or maybe split up into three separate methods - hours, minutes, and zone name (maybe don't even need to bother with zone name?)
// based off time zones listed on https://earthsky.org/astronomy-essentials/universal-time
void timeMethods::convertToUTC(int hours, int minutes, string zone)
{
	int convertHour = hours;
	int convertMinute = minutes;
	transform(zone.begin(), zone.end(), zone.begin(), ::toupper);
	// United States
	if (zone == "ADT")
	{
		convertHour = convertHour + 3;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "AST")
	{
		convertHour = convertHour + 4;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "EDT")
	{
		convertHour = convertHour + 4;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "EST")
	{
		convertHour = convertHour + 5;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "CDT")
	{
		convertHour = convertHour + 5;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "CST")
	{
		convertHour = convertHour + 6;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "MDT")
	{
		convertHour = convertHour + 6;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "MST")
	{
		convertHour = convertHour + 7;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "PDT")
	{
		convertHour = convertHour + 7;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "PST")
	{
		convertHour = convertHour + 8;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "AKDT")
	{
		convertHour = convertHour + 8;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "AKST")
	{
		convertHour = convertHour + 9;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "HAST")
	{
		convertHour = convertHour + 10;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "SST")
	{
		convertHour = convertHour + 11;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	// Europe/Middle East
	if (zone == "GMT")
	{
		convertHour = convertHour + 0;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "BST")
	{
		convertHour = convertHour - 1;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "CET")
	{
		convertHour = convertHour - 1;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "CEST")
	{
		convertHour = convertHour - 2;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "EET")
	{
		convertHour = convertHour - 2;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "EEST")
	{
		convertHour = convertHour - 3;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "C")
	{
		convertHour = convertHour - 3;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "D")
	{
		convertHour = convertHour - 4;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	// Australia
	if (zone == "AWST")
	{
		convertHour = convertHour - 8;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "ACST")
	{
		convertHour = convertHour - 9;
		convertMinute = convertMinute - 30;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << convertMinute << " UTC" << endl << endl;
		return;
	}

	if (zone == "ACDT")
	{
		convertHour = convertHour - 10;
		convertMinute = convertMinute - 30;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << convertMinute << " UTC" << endl << endl;
		return;
	}

	if (zone == "AEST")
	{
		convertHour = convertHour - 10;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

	if (zone == "AEDT")
	{
		convertHour = convertHour - 11;
		cout << hours << ":" << minutes << " " << zone << " in UTC is " << convertHour << ":" << minutes << " UTC" << endl << endl;
		return;
	}

}

// if above function is split into three (maybe two if time zone is not needed) separate functions, uses what they each return as arguments; make a
// function in the main that asks user to input what they want the time that is now in UTC to be, then do the appropriate calculations
void timeMethods::convertUTCtoOther(int hours, int minutes, string desiredZone)
{

}