#ifndef TIMEMETHODS_H
#define TIMEMETHODS_H

#include <string>

using namespace std;

class timeMethods
{
private:
	struct Node
	{
		int hour;
		int minute;
		string zone;
		Node* next;
	};

	int nodeCount = 0;
	Node* head;

public:
	timeMethods()
	{
		nodeCount = 0;
		head = nullptr;
	}

	~timeMethods();

	void storeTime(int, int, string);
	void deleteTime(int, int);
	void displayStoredTimes() const;
	void convertToUTC(int, int, string);
	void convertUTCtoOther(int, int, string);
};
#endif