#include <QCoreApplication>
#include <string.h>
#include <iostream>

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

    virtual float Perimeter()
    {
        return verticles[0].DistanceBetween(verticles[1]) + verticles[1].DistanceBetween(verticles[2])+
                verticles[2].DistanceBetween(verticles[3]) + verticles[3].DistanceBetween(verticles[0]);
    }
};

class Paralelogram : public Fourangle
{
public:
    Paralelogram():Fourangle(){}
    Paralelogram(Point &v1, Point &v2, Point &v3, Point &v4):Fourangle(v1, v2, v3, v4){}
    float Perimeter() override { return Fourangle::Perimeter();}
};

class Romb: public Fourangle
{
public:
    Romb():Fourangle(){}
    Romb(Point &v1, Point &v2, Point &v3, Point &v4):Fourangle(v1, v2, v3, v4){}
    float Perimeter() override { return Fourangle::Perimeter();}
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Fourangle **pubarr;
    cout << "Write count: ";
    int c;
    cin >> c;
    pubarr = new Fourangle*[c];

    for(int i = 0; i < c; i++)
    {
        cout << "Choose figure(Paralelogram(1), Romb(2)): ";
        int type = 1;
        cin >> type;
        if(type == 2)
            pubarr[i] = new Paralelogram();
        else
            pubarr[i] = new Romb();

        pubarr[i]->Input();
    }

    for(int i = 0; i < c; i++)
        cout << "Figure " << i << " perimeter: " << pubarr[i]->Perimeter() << endl;

    return a.exec();
}
