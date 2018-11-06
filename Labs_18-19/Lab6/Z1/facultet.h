#include <string>
#include <grupa.h>

#ifndef FACULTET_H
#define FACULTET_H

using namespace std;

class Facultet
{
    string name;
    Grupa *groups;
    int groupsCount;
    void AddGroups(int count);
public:
    Facultet();
    Facultet(string name, int groupsCount);
    ~Facultet();
    friend ostream& operator<<(ostream& outSt, Facultet& facultet);
};

#endif // FACULTET_H
