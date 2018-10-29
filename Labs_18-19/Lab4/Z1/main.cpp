#include <QCoreApplication>
#include <string.h>
#include <iostream>

using namespace std;

class Publication
{
    string name;
    float price;
    public:
        void getData(){ cout << "Name: " << name << endl << "Price: " << price << endl;}
        void putData() {cout << "Write name: "; cin >> name;
                        cout << "Write price: "; cin >> price; }
};

class Book: Publication
{
    int pageAmount;
    public:
        void getData(){ Publication::getData(); cout << "Page amount: " << pageAmount << endl; }
        void putData() {Publication::putData(); cout << "Write page amount: "; cin >> pageAmount; }
};

class Type: Publication
{
    float writeTime;
    public:
        void getData(){ Publication::getData(); cout << "Write time: " << writeTime << endl; }
        void putData() {Publication::putData(); cout << "Write writing time: "; cin >> writeTime; }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Book b;
    Type t;

    b.putData();
    t.putData();

    b.getData();
    t.getData();

    return a.exec();
}
