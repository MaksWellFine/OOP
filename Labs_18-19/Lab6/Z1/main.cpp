#include <QCoreApplication>
#include <iostream>
#include <student.h>
#include <grupa.h>
#include <facultet.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ------------1------------

    /*Student st1;
    Student st2("Qwert", "Asdfg", "Zxcv", 597394, true);
    Student *st3 = new Student();

    cout << st1;
    cout << st2;
    cout << *st3;*/

    //------------2-------------

    /*Grupa gr;
    cout << gr;*/

    //-------------3------------

    Facultet facultet;
    cout << facultet;

    return a.exec();
}
