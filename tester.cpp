#include <iostream>
#include <string>

using namespace std;

int menu();
void storeTime();
string storeZone();
void convert();

int main()
{
	int response = 0;
	string zoneName = "";
	do
	{
		response = menu();
		switch (response)
		{
		case 1:
			storeTime();
			zoneName = storeZone();
			cout << "The time zone for your inputted time is: " << zoneName << endl;
			break;
		case 2:
			convert();
			break;
		case 3:
			cout << "Quitting.";
			break;
		default:
			cout << endl << "Input out of bounds. Enter any key to return." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}	
	} while (response != 3);
	return 0;
}

int menu()
{
	int response = 0;

	cout << "1. Input a time to convert" << endl;
	cout << "2. Convert a time to a specific time zone" << endl;
	cout << "3. Quit" << endl;

	cout << endl << "Enter your input: ";
	cin >> response;
	cin.clear();
	cin.ignore(10000, '\n');
	return response;
}

void storeTime()
{
	int hours = 0;
	int minutes = 0;
	char c = ' ';
	cout << "Enter time: ";
	cin >> hours >> c >> minutes;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << endl << hours << ":" << minutes << endl;
}

string storeZone()
{
	string zoneName = "";
	cout << "Enter time zone: ";
	getline(cin, zoneName);
	return zoneName;
}

void convert()
{

}
