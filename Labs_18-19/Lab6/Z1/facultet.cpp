#include "facultet.h"
#include <iostream>

Facultet::Facultet()
{
    cout << "Write facultet name: ";
    cin >> name;
    cout << "Write groups count: ";
    cin >> groupsCount;
    AddGroups(groupsCount);
}

Facultet::Facultet(string name, int groupsCount)
{
    this->name = name;
    this->groupsCount = groupsCount;
    AddGroups(groupsCount);
}

Facultet::~Facultet()
{
    delete groups;
}

void Facultet::AddGroups(int count)
{
    if(count < 1) groupsCount = 1;
    groups = new Grupa[groupsCount]();
}

ostream& operator<<(ostream& outSt, Facultet& facultet)
{
    outSt << "Facultet: " << facultet.name << endl;
    outSt << "Groups in facultet(" << facultet.groupsCount << "): " << endl << endl;
    for(int i = 0; i < facultet.groupsCount; i++)
        outSt << facultet.groups[i] << endl;
    return outSt;
}
