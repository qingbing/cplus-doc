#include <iostream>
using namespace std;

// 数组形参为指针
void printArr(int *ptr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "第 " << i << " 个元素是: " << *(ptr++) << endl;
    }
}
/*
返回一个数组
*/
int *createArr()
{
    static int res[3];
    res[0] = 1;
    res[1] = 2;
    res[2] = 3;
    return res;
}

int main(int argc, char const *argv[])
{
    // 一维数组初始化
    int arr_01[5]{2, 3, 4, 5};
    printArr(arr_01, 5);

    /*
    指向数组的指针
    */
    int *ptr_01 = arr_01;
    // 指针 + 偏移 的方式访问指针
    cout << "指针 + 偏移 的方式访问指针" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << *(ptr_01 + i) << " ";
    }
    cout << endl;
    // 移动指针的方式访问数组
    cout << "移动指针的方式访问数组" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << *ptr_01 << " ";
        ptr_01++;
    }
    cout << endl;

    int *ptr_02 = createArr();
    for (int i = 0; i < 3; i++)
    {
        cout << *ptr_02 << " ";
        ptr_02++;
    }
    cout << endl;

    return 0;
}
