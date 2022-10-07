#include <iostream>
#include <cstring>
#include <math.h>

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
    virtual string detail() = 0; // 定义纯虚函数
    void info()
    {
        cout << "形状类型: " << this->type << endl;
        cout << "详情: " << this->detail() << endl;
        cout << "面积: " << this->area() << "; ";
        cout << "周长: " << this->perimeter();
        cout << endl;
    }
};

class Triangle : public Shape
{
private:
    int edgeA{0};
    int edgeB{0};
    int edgeC{0};

public:
    Triangle(int a, int b, int c) : edgeA(a), edgeB(b), edgeC(c)
    {
        this->setType("triangle");
    }
    string detail()
    {
        return "三边长分别为(" + to_string(this->edgeA) + ", " + to_string(this->edgeB) + ", " + to_string(this->edgeC) + ")";
    }
    int area()
    {
        int hp = perimeter() / 2;
        return sqrt(hp * (hp - edgeA) * (hp - edgeB) * (hp - edgeC));
    }
    int perimeter()
    {
        return edgeA + edgeB + edgeC;
    }
};

class Square : public Shape
{
private:
    int width{0};
    int height{0};

public:
    /*
    构造函数
    */
    Square(int a, int b) : width(a), height(b)
    {
        cout << "构造函数" << endl;
        this->setType("Square");
    }
    /*
    拷贝构造函数,
    */
    Square(const Square &obj)
    {
        cout << "拷贝构造函数" << endl;
        this->width = obj.width * 2;
        this->height = obj.height * 2;
        this->setType("Square");
    }
    /*
    析构函数
    */
    ~Square()
    {
    }
    /*
    实现基类虚函数
    */
    string detail()
    {
        return "长方形宽和高分别为(" + to_string(this->width) + ", " + to_string(this->height) + ")";
    }
    int area()
    {
        return width * height;
    }
    int perimeter()
    {
        return (width + height) * 2;
    }
    /*
    申明友元函数，传递类实例，在外部实现时，可以访问类中所有成员，包括私有成员
    */
    friend void sayHello(Square s);
};

void sayHello(Square s)
{
    cout << "Type: " << s.getType() << "; Width:" << s.width << "; Height:" << s.height << endl;
}

int main(int argc, char const *argv[])
{
    // 三角形
    cout << "=========" << endl;
    Triangle t1(3, 4, 5);
    t1.info();

    // 长方形
    cout << "=========" << endl;
    Square s1(10, 20);
    s1.info();

    cout << "=========" << endl;
    Square s2 = s1;
    s2.info();
    sayHello(s2);

    cout << "==== 类指针的使用 =====" << endl;
    // 类指针的使用， 用 "->" 访问类指针的成员
    Square *ptr = &s2;
    ptr->info();

    return 0;
}
