// Z1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

using namespace std;

class Int{

	private:
		int value;
	public:
		Int(int defaultVal)
		{
			value = defaultVal;
		}
		Int():Int(0){}
		void Set(int val) { value = val; }
		int Get() { return value; }
		void Show() { cout << value << endl; }
		void ResetInt() { value = 0; }
		static int Add(Int n1, Int n2) { return n1.Get() + n2.Get(); }
};

class Kasa
{
	unsigned int carsAmount;
	double suma;

	public:
	const Kasa() { carsAmount = 0; suma = 0; }

	const void payingCar() { carsAmount++; suma += 0.5; }
	const void nopayCar() { carsAmount++; }
	const void display() { cout << "Cars amount = " << carsAmount << ", suma = " << suma << endl; }
};

class Time
{
	int hours;
	int minutes;
	int seconds;

	void SetHours(int val) { hours = val % 12; }
	void SetMinutes(int val) { minutes = val % 60; if(val > 59) SetHours(hours + val/60); }
	void SetSeconds(int val) { seconds = val % 60; if (val > 59) SetMinutes(minutes + val / 60); }

	public:
		const Time(int _hours, int _minutes, int _seconds)
		{
			SetHours(_hours);
			SetMinutes(_minutes);
			SetSeconds(_seconds);
		}
		const Time() :Time(0, 0, 0) {}

		const void Print() { cout << hours << ":" << minutes << ":" << seconds << endl; }
		const void Add(Time t1, Time t2) 
		{
			SetHours(t1.hours + t2.hours);
			SetMinutes(t1.minutes + t2.minutes);
			SetSeconds(t1.seconds + t2.seconds);
		}
};

class NewTime
{
	int hours;
	int minutes;

	public:
		NewTime(int hours, int minutes) { InitHours(hours); InitMinutes(minutes); }
		NewTime():NewTime(0,0) {}
		void InitHours(int val) { if (val >= 0 && val < 24) hours = val; else hours = 0; }
		void InitMinutes(int val) { if (val >= 0 && val < 60) minutes = val; else minutes = 0; }
		void Display() { cout << "Time = " << hours << ":" << minutes << endl; }
		void Read()
		{
			cout << "Write hours: ";
			int val = 0;
			cin >> val;
			InitHours(val);
			cout << "Write minutes: ";
			val = 0;
			cin >> val;
			InitMinutes(val);
		}
		int Minutes() { return hours * 60 + minutes; }
};

int main()
{
	//------------------Z1----------------
	Int n1(5), n2(7), n3;
	n3.Set(Int::Add(n1, n2));

	n3.Show();

	//------------------Z2----------------
	char symb;
	cout << endl << "Try kasa: " << endl;
	Kasa kasa;
	while ((symb = getch()) != 27)
	{		
		if (symb == 'p') kasa.payingCar();
		else if (symb == 'n') kasa.nopayCar();		
	}
	kasa.display();

	//-------------------Z3----------------
	cout << endl;
	Time t1(2, 8, 64);
	Time t2(22, 61, 2);
	t1.Print();
	t2.Print();
	Time t3;
	t3.Add(t1, t2);
	t3.Print();

	//--------------------Z4---------------

	cout << endl;
	NewTime nt1;
	NewTime *nt2 = new NewTime(3, 34);
	NewTime mas1[2];
	NewTime mas2[] = {NewTime(4,5), NewTime(15,20) };

	nt1.Read();
	mas1[0].InitHours(8);
	mas1[1].InitMinutes(20);
	mas2[1].Display();
	cout << nt2->Minutes() << endl;

	system("pause");
    return 0;
}



