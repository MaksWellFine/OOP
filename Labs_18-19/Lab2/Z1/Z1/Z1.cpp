// Z1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Furniture
{
	char *Room = new char;
	int Weight;

public:
	Furniture(char* room, int weight)
	{
		SetRoom(room);
		Weight = weight;
	}
	Furniture():Furniture("Unknown", 0) {}
	Furniture(const Furniture& furn)
	{
		//cout << "copy" << endl;
		Weight = furn.Weight;
		SetRoom(furn.Room);
	}
	~Furniture() {/*delete Room;*/ cout << "Deleted" << endl; }

	void SetRoom(const char* room)
	{
		delete Room;
		Room = new char[40];
		for(int i = 0; i < 40; i++)
			Room[i] = room[i];
	}
	char* GetRoom(){return Room;}
	void SetWeight(int val) { Weight = val; }
	int GetWeight() { return Weight; }
	void Print() { cout << "Mass: " << Weight << ", room: " << Room << endl; }
	void Input() { 
		cout << "Write mass: ";
		cin >> Weight;
		cout << "Room: ";
		cin >> Room;
	}
};

int main()
{
	Furniture f1;
	Furniture f2("qw", 10);

	Furniture *f3 = new Furniture;
	Furniture *f4 = new Furniture("qw", 10);

	Furniture mas[3];

	mas[0].Input();

    f1 = Furniture(f2);
	f1.SetRoom("as");
	cout << f1.GetRoom() << endl;
	f2.Print();

	f3->SetWeight(32);
	cout << f3->GetWeight() << endl;
	f3->Print();

	delete f3;
	delete f4;

	system("pause");

    return 0;
}

