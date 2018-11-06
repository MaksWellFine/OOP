#include "student.h"
#include <iostream>


Student::Student()
{
    cout << "Write student PIB: ";
    cin >> familyName >> name >> fatherName;
    cout << "Write markbook number: ";
    cin >> numberMarkbook;
    cout << "Choose study type (1-dergavne,2-platne): ";
    int type;
    cin >> type;
    if(type == 1) studyType = true;
    else studyType = false;
}

Student::Student(string familyName, string name, string fatherName, int numberMarkbook, bool studyType)
{
    this->familyName = familyName;
    this->name = name;
    this->fatherName = fatherName;
    this->numberMarkbook = numberMarkbook;
    this->studyType = studyType;
}

ostream& operator<<(ostream &outSt, Student &student)
{
    outSt << "Student: " << student.familyName << " " << student.name << " " << student.fatherName << endl;
    outSt << "Markbook: " << student.numberMarkbook << endl;
    outSt << "Studing type: ";
    if(student.studyType) outSt << "statesman";
    else outSt << "payer";
    outSt << endl;
}
