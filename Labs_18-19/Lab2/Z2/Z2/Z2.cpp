// Z2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class ListPIP
{
	string* mas = new string[3];
	ListPIP *next = NULL;
	bool isInited = false;

	public:
		ListPIP() {}
		ListPIP(string name1, string name2, string name3)
		{
			Add(name1, name2, name3);
		}
		void Add(string name1, string name2, string name3)
		{
			if (next == NULL)
			{
				if (isInited)
					next = new ListPIP(name1, name2, name3);
				else
				{
					mas[0] = name1;
					mas[1] = name2;
					mas[2] = name3;
					isInited = true;
				}
			}
			else next->Add(name1, name2, name3);
		}
		void ShowPIP()
		{
			if (isInited)
			{
				cout << mas[0] << " " << mas[1] << " " << mas[2] << endl;
				if (next != NULL)
					next->ShowPIP();
			}			
		}
		void ShowShortPIP()
		{
			if (isInited)
			{
				cout << mas[0] << " " << mas[1][0] << ". " << mas[2][0] << "." << endl;
				if (next != NULL)
					next->ShowShortPIP();
			}
		}
};

int main()
{
	int amount = 0;
	cin >> amount;
	ListPIP list;
	for (int i = 0; i < amount; i++)
	{
		string name1, name2, name3;
		cin >> name1;
		cin >> name2;
		cin >> name3;
		list.Add(name1, name2, name3);
	}

	cout << endl;
	list.ShowPIP();
	cout << endl;
	list.ShowShortPIP();

	system("pause");
    return 0;
}

