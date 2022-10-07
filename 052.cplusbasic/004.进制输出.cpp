#include <iostream>
#include <bitset>

int main(int argc, char const *argv[])
{
    // 进制数据表示
    int binaryNum{0b11}; // 二进制: 3
    int octallNum{011};  // 八进制: 9
    int decimalNum{11};  // 十进制: 11
    int hexNum{0x11};    // 十六进制: 17
    std::cout << "二进制: " << binaryNum << std::endl;
    std::cout << "八进制: " << octallNum << std::endl;
    std::cout << "十进制: " << decimalNum << std::endl;
    std::cout << "十六进制: " << hexNum << std::endl;
    int decimalNum1{11'111}; // 11111
    std::cout << "十进制单引号分位表示: " << decimalNum1 << std::endl;
    // 类型字面量
    std::cout << "八进制" << 0111 << std::endl;
    std::cout << "八进制无符号" << 0111U << std::endl;
    std::cout << "八进制long" << 0111L << std::endl;

    /* 值得注意的是：使用 std::oct,dec,hex 后面的输出 std::cout 及 std::cin 就会一直生效，除非手动修改 */
    // 有符号正整数
    int num_01{100};
    std::cout << "有符号正整数二进制: " << std::bitset<32>(num_01) << std::endl;
    std::cout << "有符号正整数八进制数: " << std::oct << num_01 << std::endl;
    std::cout << "有符号正整数十进制数: " << std::dec << num_01 << std::endl;
    std::cout << "有符号正整数十六进制数: " << std::hex << num_01 << std::endl;

    // 有符号负整数
    int num_02{-100};
    std::cout << "有符号负整数二进制: " << std::bitset<32>(num_02) << std::endl;
    std::cout << "有符号负整数八进制数: " << std::oct << num_02 << std::endl;
    std::cout << "有符号负整数十进制数: " << std::dec << num_02 << std::endl;
    std::cout << "有符号负整数十六进制数: " << std::hex << num_02 << std::endl;

    // 无符号整数
    unsigned int num_11{100};
    std::cout << "无符号整数二进制: " << std::bitset<32>(num_11) << std::endl;
    std::cout << "无符号整数八进制数: " << std::oct << num_11 << std::endl;
    std::cout << "无符号整数十进制数: " << std::dec << num_11 << std::endl;
    std::cout << "无符号整数十六进制数: " << std::hex << num_11 << std::endl;
    return 0;
}
