#include <string>
#include <student.h>

#ifndef GRUPA_H
#define GRUPA_H

using namespace std;

class Grupa
{
    string name;
    string specialty;
    int studentsCount;
    Student **students;
    void AddStudents(int count);
public:
    Grupa();
    Grupa(string name, string specialty, int studentsCount);
    ~Grupa();
    friend ostream& operator<<(ostream&, Grupa&);
};

#endif // GRUPA_H
