#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string fileName = "myfile.txt";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //---------------------1-----------------------
    ofstream outFile(fileName);
    if(outFile.is_open())
    {
        string strToWrite = "Pelishko Maksym Ruslanovych 17 0689479273 08.01.2001 TK_TNTU";
        outFile.write(strToWrite.c_str(), strToWrite.size());
        outFile.close();
    }else cout << "Can't create or open file!";

    //---------------------2-----------------------
    ifstream inFile(fileName);
    if(inFile.is_open())
    {
        string surname, name, fatherName, birthday, educationPlace;
        int age, phoneNumber;

        inFile >> surname >> name >> fatherName >> age >> phoneNumber >> birthday >> educationPlace;
        inFile.close();

        cout << "Person - " << surname << " " << name << " " << fatherName << endl;
        cout << "Age - " << age << ", birthday - " << birthday << endl;
        cout << "Phone number - " << phoneNumber << endl;
        cout << "Education place - " << educationPlace << endl;
    }else cout << "Can't open file!";

    return a.exec();
}
