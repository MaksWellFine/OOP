#include<string>
using namespace std;

#ifndef STUDENT_H
#define STUDENT_H


class Student
{
    string familyName, name, fatherName;
    int numberMarkbook;
    bool studyType;
public:
    Student();
    Student(string familyName, string name, string fatherName, int numberMarkbook, bool studyType);
    friend ostream& operator<<(ostream &, Student &);
};

#endif // STUDENT_H
