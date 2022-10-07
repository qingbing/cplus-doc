#include <iostream>
using namespace std;

struct Book
{
    int id;
    string name;
    void print()
    {
        cout << __func__ << ". bookId: " << id << "; bookName: " << name << endl;
    }
    void print2(); // 申明，在外部使用 "::" 符号进行实现
};
// 使用范围解析运算符 "::" 对内部声明的成员方法进行实现
void Book::print2()
{
    cout << __func__ << ". bookId: " << id << "; bookName: " << name << endl;
}

// 使用 typedef 创建新的类型
typedef struct
{
    int id;
    string name;
    void print()
    {
        cout << __func__ << ". deskkId: " << id << "; deskName: " << name << endl;
    }
} Desk;

int main(int argc, char const *argv[])
{
    // 普通使用， 用 “.” 访问成员
    struct Book b1;
    b1.id = 11;
    b1.name = "hello";
    b1.print();
    b1.print2();

    // 结构体指针使用 "->" 进行访问
    struct Book *ptr_b1 = &b1;
    ptr_b1->print();
    ptr_b1->print2();

    // typedef 创建的类型
    Desk d1;
    d1.id = 11;
    d1.name = "name string";
    d1.print();
    return 0;
}
