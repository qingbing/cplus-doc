/*
单位采购一批办公桌，共10000元
高桌子一张500元
普通桌子一张300元
椅子3把100元
需求：钱花光，并且所有家具总数为100
*/
#include <iostream>

int main(int argc, char const *argv[])
{
    // 常规代码
    const int totalMoney{10000};
    const int highDeskPrice{500};
    const int commonDeskPrice{300};
    const int total{100};
    int maxHighDesk{(int)(totalMoney / highDeskPrice)};
    int maxCommonDesk{(int)(totalMoney / commonDeskPrice)};
    std::cout << "通用算法" << std::endl;
    for (int hdCount = 0; hdCount < maxHighDesk; hdCount++)
    {
        for (int cdCount = 0; cdCount < maxCommonDesk; cdCount++)
        {
            int cCount{total - hdCount - cdCount};
            if (cCount < 0 || cCount % 3 != 0)
            {
                continue;
            }
            if (hdCount * highDeskPrice + cdCount * commonDeskPrice + cCount * 100 / 3 == totalMoney)
            {
                std::cout << "高桌子:" << hdCount << "; 普通桌子:" << cdCount << "; 椅子: " << cCount << std::endl;
            }
        }
    }

    // 计算后的优化代码
    std::cout << "计算后的优化代码" << std::endl;
    for (int hdCount = 0; hdCount < 100 / 7; hdCount++)
    {
        if ((100 - 7 * hdCount) % 4 != 0)
        {
            continue;
        }
        int cdCount{(100 - 7 * hdCount) / 4};
        int cCount{100 - hdCount - cdCount};
        std::cout << "高桌子:" << hdCount << "; 普通桌子:" << cdCount << "; 椅子: " << cCount << std::endl;
    }
    return 0;
}
