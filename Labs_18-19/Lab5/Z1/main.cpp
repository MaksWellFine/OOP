#include <QCoreApplication>
#include <string.h>
#include <iostream>

using namespace std;

class Publication
{
    string name;
    float price;
    public:
        Publication(){}
        virtual void getData(){ cout << "Name: " << name << endl << "Price: " << price << endl;}
        virtual void putData() {cout << "Write name: "; cin >> name;
                        cout << "Write price: "; cin >> price; }
        virtual bool isOversized(){return false;}
};

class Book: public Publication
{
    int pageAmount;
    public:
        Book(){}
        void getData() override{cout << "Book: " << endl; Publication::getData(); cout << "Page amount: " << pageAmount << endl; }
        void putData() override{Publication::putData(); cout << "Write page amount: "; cin >> pageAmount; }
        bool isOversized() override{ if(pageAmount > 800) return true; else return false; }
};

class Tape: public Publication
{
    int writeTime;
    public:
        Tape(){}
        void getData() override{cout << "Tape: " << endl; Publication::getData(); cout << "Write time: " << writeTime << endl; }
        void putData() override{Publication::putData(); cout << "Write writing time: "; cin >> writeTime; }
        bool isOversized() override{ if(writeTime > 90) return true; else return false; }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Publication **pubarr;
    cout << "Write count: ";
    int c;
    cin >> c;
    pubarr = new Publication*[c];

    for(int i = 0; i < c; i++)
    {
        cout << "Choose publication(Book(1), Tape(2)): ";
        int type = 1;
        cin >> type;
        if(type == 2)
            pubarr[i] = new Tape();
        else
            pubarr[i] = new Book();

        pubarr[i]->putData();
    }

    for(int i = 0; i < c; i++)
    {
        pubarr[i]->getData();
        if(pubarr[i]->isOversized()) cout << "Oversized!" << endl;
        cout << endl;
    }

    return a.exec();
}
