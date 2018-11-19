#include <QCoreApplication>
#include <iostream>
using namespace std;
#include <process.h> //for exit()
const int LIMIT = 10; //array size

class IndexException
{
    string msg;
    int index;
public:
    IndexException(string str, int errorIndx){msg = str; index = errorIndx;}
    void Show(){ cout << msg + ", wrong index: " + to_string(index) + "\n"; }
};

class safearay
{
private:
    int arr[LIMIT];
public:
    int& operator [](int n)
    {
        if( n< 0 || n>=LIMIT ) { throw IndexException("\nIndex out of bounds", n);}
        return arr[n];
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    safearay sa1;
    for(int j=0; j<=LIMIT; j++)
        try{
            sa1[j] = j*10; //*left* side of equal sign
        }catch(IndexException e){e.Show();}
    for(int j=0; j<=LIMIT; j++) //display elements
    {
        try{
            int temp = sa1[j]; //*right* side of equal sign
            cout << "Element " << j << " is " << temp << endl;
        }catch(IndexException e){e.Show();}
    }

    return a.exec();
}
