#include <iostream>

#define NUM_3 3

int main(int argc, char const *argv[])
{
    // 输出
    printf("printf: Hello World\n");
    std::cout << "std::cout: Hello World" << std::endl;
    // 定义变量
    int num1 = 3.11; // 会被转换为 3
    int num2{3};     // 建议使用的格式，类型和格式不匹配会编译不通过
    std::cout << "变量1: " << num1 << std::endl;
    std::cout << "变量2: " << num2 << std::endl;
    // 定义常量
    const int NUM_1{3};
    const int NUM_2{3};
    std::cout << "常量1: " << NUM_1 << std::endl;
    std::cout << "常量2: " << NUM_2 << std::endl;
    std::cout << "常量3: " << NUM_3 << std::endl;
    // 自增运算
    int a{10};
    std::cout << "先运算后增加: a++ + 5 + a = " << a++ + 5 + a << std::endl; // a:10, res=26
    std::cout << "先增加后运算: ++a + 5 + a = " << ++a + 5 + a << std::endl; // a:11, res=29
    // 多余精度演示
    std::cout << "float 演示 200.0F: " << 200.0F << std::endl;
    std::cout << "double 演示 200.0: " << 200.0 << std::endl;
    std::cout << "long double 演示 200.0L: " << 200.0L << std::endl;
    std::cout << "float 精度演示" << 3.1234546F << std::endl;       // 3.12345
    std::cout << "double 精度演示" << 3.1234546 << std::endl;       // 3.12345
    std::cout << "long double 精度演示" << 3.1234546L << std::endl; // 3.12345
    // 类型转换
    float fnum{3.1415f};
    int inum_1 = fnum; // 隐式转换
    std::cout << "3.1415f 赋值给int: " << inum_1 << std::endl;
    int inum_2 = int(fnum);
    int inum_3 = (int)(fnum);
    int inum_4 = static_cast<int>(fnum);
    std::cout << "c: int(fnum): " << inum_2 << std::endl;
    std::cout << "c: (int)(fnum): " << inum_3 << std::endl;
    std::cout << "c: static_cast<int>(fnum): " << inum_4 << std::endl;
    // 类型内存占用 sizeof
    std::cout << "char 占用字节 sizeof(char):" << sizeof(char) << std::endl;
    std::cout << "int 占用字节 sizeof(int):" << sizeof(int) << std::endl;
    std::cout << "float 占用字节 sizeof(float):" << sizeof(float) << std::endl;
    std::cout << "long 占用字节 sizeof(long):" << sizeof(long) << std::endl;
    return 0;
}
