#include <QCoreApplication>
#include <iostream>
#include <math.h>

using namespace std;

class Point
{
    float x,y;

public:
    Point(float _x, float _y){x = _x; y = _y;}
    Point():Point(0,0){}
    float GetX(){return x;}
    float GetY(){return y;}
    void SetX(float _x){ x = _x;}
    void SetY(float _y){ x = _y;}
    string Get(){return "(" + to_string(x) + ";" + to_string(y) + ")";}
    float GetLength(){return (float)sqrt(pow(x,2)+pow(y,2));}
    float GetAngle(){return atan2(y,x);}
    float DistanceBetween(Point p)
    {
        return (float)sqrt(pow(x-p.x,2)+pow(y-p.y,2));
    }
    Point& operator-(Point& p)
    {
        return *new Point(x-p.x, y-p.y);
    }
};

class Fourangle
{
    Point verticles[4];

public:
    Fourangle():Fourangle(*new Point(0,0), *new Point(0,0), *new Point(0,0), *new Point(0,0)){}
    Fourangle(Point &v1, Point &v2, Point &v3, Point &v4)
    {
        verticles[0] = v1;
        verticles[1] = v2;
        verticles[2] = v3;
        verticles[3] = v4;
    }
    ~Fourangle()
    {

    }
    void SetVerticle(int pos, Point &p)
    {
        verticles[pos] = p;
    }
    Point& GetVerticle(int pos)
    {
        return verticles[pos];
    }
    void Show()
    {
        cout << "Rectangle with verticles: ";
        for(int i = 0; i < 4; i++)
            cout << verticles[i].Get() << " ";
        cout << endl;
    }
    void Input()
    {
        int x,y;
        for(int i = 0; i < 4; i++)
        {
            cout << "Corner " << i+1 << ": ";
            cin >> x >> y;
            verticles[i].SetX(x);
            verticles[i].SetY(y);
        }
    }
    static float Dobutok(float a, float b)
    {
        return a*b;
    }
};

class Paralelogram : Fourangle
{
private:
    float GetCornerAngle()
    {
        return abs((GetVerticle(1) - GetVerticle(0)).GetAngle() - (GetVerticle(3) - GetVerticle(0)).GetAngle());
    }
public:
    Paralelogram():Fourangle(){}
    Paralelogram(Point &v1, Point &v2, Point &v3, Point &v4):Fourangle(v1, v2, v3, v4){}
    ~Paralelogram(){}
    float Square()
    {
        return Dobutok(GetVerticle(0).DistanceBetween(GetVerticle(1)), GetVerticle(1).DistanceBetween(GetVerticle(2)))*sin(GetCornerAngle());
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
