#include <iostream>
#include <string>
#include <algorithm>
#include "timeMethods.h"

using namespace std;

timeMethods::~timeMethods()
{

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

void timeMethods::convert()
{

}