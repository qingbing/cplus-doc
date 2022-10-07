#include <iostream>
using namespace std;

class Shape
{
private:
    string type;

public:
    void setType(string type)
    {
        this->type = type;
    }
    string getType()
    {
        return type;
    }
    virtual int area() = 0;      // 定义纯虚函数
    virtual int perimeter() = 0; // 定义纯虚函数
    virtual void info()          // 虚函数
    {
        cout << "Shape Info" << endl;
    }
};

class Square : public Shape
{
private:
    int width{0};

public:
    Square(int a) : width(a){};
    int area()
    {
        return this->width * this->width;
    }
    int perimeter()
    {
        return this->width * 4;
    }
    void info()
    {
        cout << "Square Info" << endl;
    }
};

class Rectangle : public Shape
{
private:
    int width{0};
    int height{0};

public:
    Rectangle(int w, int h) : width(w), height(h){};
    int area()
    {
        return this->width * this->height;
    }
    int perimeter()
    {
        return this->width * 2 + this->height * 2;
    }
    void info()
    {
        cout << "Rectangle Info" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Square s1(10);
    // s1.info();
    Shape *shape_01{&s1};
    shape_01->info();

    Rectangle r1(10, 20);
    // r1.info();
    Shape *shape_02{&r1};
    shape_02->info();

    // 多态
    // Shape *shape;
    // shape = &r1;
    // shape->info();

    return 0;
}
