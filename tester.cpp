#include <iostream>
#include <string>
#include "timeMethods.h"

using namespace std;

int menu();
int validHours();
int validMinutes();
string validZone();
bool confirmDelete();

int main()
{
	int response = 0;
	int hours = 0;
	int minutes = 0;
	string zone = "";
	timeMethods time;
	do
	{
		response = menu();
		switch (response)
		{
		case 1:
			hours = validHours();
			minutes = validMinutes();
			zone = validZone();
			time.storeTime(hours, minutes, zone);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			cout << endl << "Displaying the stored times:" << endl;
			time.displayStoredTimes();
			cout << endl;
			break;
		case 5:
			cout << "Exiting program.";
			break;
		case 10:
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
		default:
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

	while (hours < 0)
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

	while (minutes < 0)
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

	while (zoneName == "" || zoneName.find_first_not_of(' ') || zoneName.length() > 4)
	{
		cout << endl << "Error: Time zone name is too long (maximum of 4 characters) or blank characters were found." << endl;
		cout << endl << "Enter time zone abbrevation: ";
		getline(cin, zoneName);
	}
	return zoneName;
}

bool confirmDelete()
{
	int response = 0;
	cout << "Enter any other number to cancel deletion." << endl;
	cout << "Enter 1 to confirm deletion." << endl;
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