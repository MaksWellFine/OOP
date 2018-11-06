#include "grupa.h"
#include <iostream>

using namespace std;

Grupa::Grupa()
{
    cout << "Write group name: ";
    cin >> name;
    cout << "Write group specialty: ";
    cin >> specialty;
    cout << "Write studens count: ";
    cin >> studentsCount;
    AddStudents(studentsCount);
}

Grupa::Grupa(string name, string specialty, int studentsCount)
{
    this->name = name;
    this->specialty = specialty;
    this->studentsCount = studentsCount;
    AddStudents(studentsCount);
}

Grupa::~Grupa()
{
    delete students;
}

void Grupa::AddStudents(int count)
{
    if(count < 1) studentsCount = 1;
    students = new Student*[studentsCount]();
    for(int i = 0; i < studentsCount; i++)
        students[i] = new Student();
}

ostream& operator<<(ostream& outSt, Grupa& group)
{
    outSt << "Group: " << group.name << endl;
    outSt << "Specialty: " << group.specialty << endl;
    outSt << "Students in group(" << group.studentsCount << "): " << endl << endl;
    for(int i = 0; i < group.studentsCount; i++)
        outSt << *group.students[i];
    return outSt;
}
