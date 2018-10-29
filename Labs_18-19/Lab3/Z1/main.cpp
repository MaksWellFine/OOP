#include <QCoreApplication>
#include <iostream>
#include <string>

using namespace std;

class Int{

    private:
        int value;
    public:
        Int(int defaultVal)
        {
            value = defaultVal;
        }
        Int():Int(0){}
        void Set(int val) { value = val; }
        int Get() { return value; }
        void Show() { cout << value << endl; }
        void ResetInt() { value = 0; }

        void Exception(string str)
        {
            cout << "Exception: " << str << " in class \"Int\"" << endl;
        }
        Int operator+(Int n)
        {
            long double nToCheck = value;
            if(value + n.value != nToCheck + n.value)
            {
                Exception("value overflow");
                return 0;
            }else return value + n.value;

        }

        Int operator-(Int n)
        {
            long double nToCheck = value;
            if(value - n.value != nToCheck - n.value)
            {
                Exception("value overflow");
                return 0;
            }else return value - n.value;

        }

        Int operator*(Int n)
        {
            long double nToCheck = value;
            if(value * n.value != nToCheck * n.value)
            {
                Exception("value overflow");
                return 0;
            }else return value * n.value;

        }

        Int operator/(Int n)
        {
            long nToCheck = value;
            if(value / n.value != nToCheck / n.value)
            {
                Exception("value overflow");
                return 0;
            }else return value / n.value;

        }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Int n1(2);
    Int n2(10);

    (n1+n2).Show();
    n1.Set(2147483647);
    (n1+n2).Show();

    n1.Set(45);
    n1 = n1 - n2;
    n1.Show();

    n2 = n1*n2;
    n2.Show();

    n2 = n2/Int(9);
    n2.Show();

    return a.exec();
}
