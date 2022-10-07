#include <iostream>
using namespace std;

/*
给定第二维的长度来作为形参
*/
void printTwoArr1(int arr[][3], int row)
{
    cout << "给定第二维的长度来作为形参:" << __func__ << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

/*
给定二维长度的指针作为形参
*/
void printTwoArr2(int (*arr)[3], int row)
{
    cout << "给定二维长度的指针作为形参:" << __func__ << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

/*
使用指针数组作为形参
*/
void printTwoArr3(int (*arr)[], int row, int col)
{
    cout << "使用指针数组作为形参:" << __func__ << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << (*arr + i * col)[j] << " ";
        }
        cout << endl;
    }
}

/*
将二维数组指针转换成一维数组指针作为形参
*/
void printTwoArr4(int *arr, int row, int col)
{
    cout << "将二维数组指针转换成一维数组指针作为形参:" << __func__ << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int pos = i * col + j; // 计算偏移

            // cout << arr[pos] << " "; // 和下一句等效
            cout << *((int *)arr + pos) << " ";
        }
        cout << endl;
    }
}

/*
使用二级指针作为形参
*/
void printTwoArr5(int **arr, int row, int col)
{
    cout << "使用二级指针作为形参:" << __func__ << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int pos = i * col + j; // 计算偏移
            cout << *((int *)arr + pos) << " ";
        }
        cout << endl;
    }
}
/*
使用二级指针作为形参，打印一位效果
*/
void printTwoArr6(int **arr, int size)
{
    cout << "使用二级指针作为形参，打印一位效果:" << __func__ << endl;
    // cout << arr << endl;
    // cout << *(arr) << endl;
    // cout << *((int *)arr) << endl;
    // cout << *((int *)arr + 1) << endl;
    // cout << *((int *)arr + 5) << endl;
    for (int i = 0; i < size; i++)
    {
        cout << *((int *)arr + i) << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // 二维数组初始化, 下面两种方式
    int arr_02[2][3]{
        {1, 2, 3},
        {4, 5, 6},
    };
    int arr_03[2][3]{1, 2, 3, 4, 5, 6};

    printTwoArr1(arr_03, 2);
    printTwoArr2(arr_03, 2);
    printTwoArr3(arr_03, 2, 3);
    printTwoArr4((int *)arr_03, 2, 3);
    printTwoArr5((int **)arr_03, 2, 3);
    printTwoArr6((int **)arr_03, 6);
    return 0;
}
