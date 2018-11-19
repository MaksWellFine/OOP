#include <QCoreApplication>
#include <string.h>
#include <typeinfo.h>
#include <iostream>

using namespace std;

class Exception
{
    string typeName;
    string errorMsg;
public:
    template<class T>
    Exception(T type, string codeError)
    {
        typeName = typeid (type).name();
        errorMsg = codeError;
    }
    friend ostream& operator<<(ostream&, Exception&);
};

ostream& operator<<(ostream& outStr, Exception& exc)
{
    outStr << "Exception in " << exc.typeName << ", error code: " << exc.errorMsg;
}

class Rectangle
{
    double x, y;
    public:
        Rectangle():Rectangle(0,0){}
        Rectangle(double _x, double _y)
        {
            if(_x <= 0 || _y <= 0) throw Exception(this, "Not correct size, must be grater than 0, now: x=" + to_string(_x) + "; y=" + to_string(_y));
            SetCornerDigonal(_x,_y);
        }
        ~Rectangle(){}
        double GetX() {return x;}
        double GetY() {return y;}
        void SetCornerDigonal(double _x, double _y){ x = _x; y = _y;}
        string GetRectangle(){ return ("Rectangle diagonal is (" + to_string(x) + "; " + to_string(y) + ")"); }
        double GetPerymetr(){ return 2*x+2*y; }

        Rectangle& operator+(Rectangle& r)
        {
            Rectangle newR(x+r.x, y+r.y);
            return newR;
        }
        Rectangle& operator-(Rectangle& r)
        {
            Rectangle newR(x-r.x, y-r.y);
            return newR;
        }
        bool operator>(Rectangle& r)
        {
            return GetPerymetr() > r.GetPerymetr();
        }
        bool operator<(Rectangle& r)
        {
            return GetPerymetr() < r.GetPerymetr();
        }
        bool operator==(Rectangle& r)
        {
            return GetPerymetr() == r.GetPerymetr();
        }

        friend istream& operator<<(istream& stream, Rectangle& r);
        friend ostream& operator>>(ostream& stream, Rectangle& r);
};

istream& operator>>(istream& stream, Rectangle& r)
{
    double x, y;
    stream >> x >> y;
    r.SetCornerDigonal(x,y);
    return stream;
}

ostream& operator<<(ostream& stream, Rectangle& r)
{
    stream << r.GetRectangle();
    return stream;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try {
        Rectangle r1(2,3);
        Rectangle r2;
    } catch (Exception e) {
        cout << e;
    }

    return a.exec();

}
