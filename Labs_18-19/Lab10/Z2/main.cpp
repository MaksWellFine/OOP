#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string fileName = "myfile.txt";

class Person
{
    string surname, name, fatherName, birthday, educationPlace;
    int age, phoneNumber;

public:
    void Read()
    {
        cout << "Write PIB: ";
        cin >> surname >> name >> fatherName;
        cout << "Write age: ";
        cin >> age;
        cout << "Write phoneNumber: ";
        cin >> phoneNumber;
        cout << "Write birthday: ";
        cin >> birthday;
        cout << "Write education place: ";
        cin >> educationPlace;
    }
    void Show()
    {
        cout << "Person - " << surname << " " << name << " " << fatherName << endl;
        cout << "Age - " << age << ", birthday - " << birthday << endl;
        cout << "Phone number - " << phoneNumber << endl;
        cout << "Education place - " << educationPlace << endl;
    }
    friend ofstream& operator<<(ofstream&, Person&);
    friend ifstream& operator>>(ifstream&, Person&);
};

ofstream& operator<<(ofstream& outFile, Person& person)
{
    outFile << person.surname << " " << person.name << " " << person.fatherName << " " << person.age << " "
            << person.phoneNumber << " " << person.birthday << " " << person.educationPlace;
}

ifstream& operator>>(ifstream& inFile, Person& person)
{
    inFile >> person.surname >> person.name >> person.fatherName >> person.age >>
            person.phoneNumber >> person.birthday >> person.educationPlace;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //--------------3-----------------
    Person person;
    person.Read();
    ofstream outFile(fileName);
    outFile << person;
    outFile.close();
    cout << endl;

    //--------------4-----------------
    Person person2;
    ifstream inFile(fileName);
    inFile >> person2;
    person2.Show();
    inFile.close();

    return a.exec();
}
