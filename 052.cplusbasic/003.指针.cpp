#include <iostream>

int main(int argc, char const *argv[])
{
    // 变量及其地址
    int num_10{100};
    std::cout << "num_10 地址: " << &num_10 << "; 值为: " << num_10 << std::endl;
    // 指针变量, 改变指针内容或原变量内容效果一致，指针内容和变量都一起改变
    int *ptrNum_10{&num_10};
    std::cout << "ptrNum_10 地址: " << ptrNum_10 << "; 值为: " << *ptrNum_10 << std::endl;
    *ptrNum_10 = 200;
    std::cout << "ptrNum_10 " << *ptrNum_10 << "; num_10值为: " << num_10 << std::endl;
    num_10 = 300;
    std::cout << "ptrNum_10 " << *ptrNum_10 << "; num_10值为: " << num_10 << std::endl;

    // 常量指针: const 变量类型 * 变量名；指针指向的一个常量的内存地址，不能地址内的数据，但可以改变指向的地址
    const int num_21{100};
    const int num_22{101};
    const int *ptrNum_20{&num_21};
    std::cout << "指针内容: " << *ptrNum_20 << std::endl;
    // *ptrNum_20 = 102; // 编译不通过
    ptrNum_20 = &num_22;
    std::cout << "常量指针修改地址后内容: " << *ptrNum_20 << std::endl;

    // 指针常量: 变量类型 *const 变量名；指针变量是一个常量，一旦初始化，不能修改指向，但可以修改指向地址的内容
    int num_31{100};
    int num_32{101};
    int *const ptrNum_30{&num_31};
    std::cout << "指针内容: " << *ptrNum_30 << std::endl;
    *ptrNum_30 = 300;
    // ptrNum_30 = &num_32; // 编译不通过
    std::cout << "常量指针内容: " << *ptrNum_30 << std::endl;

    // 指向常量的常量指针: const 变量类型 * const 变量名；该指针变量是一个常量，一旦初始化后，指向地址和地址的内容都不能改变
    const int num_41{100};
    const int num_42{101};
    const int *ptrNum_40{&num_41};
    // *ptrNum_40 = 10;     // 编译不通过
    // ptrNum_40 = &num_42; // 编译不通过
    std::cout << "指针内容: " << *ptrNum_40 << std::endl;
    return 0;
}
