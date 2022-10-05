
#include <stdio.h>
int main(int argc, char const *argv[])
{
    // if 判断
    unsigned short age = 18;
    if (age < 18)
    {
        printf("age: %d, 未成年", age);
    }
    else if (age == 18)
    {
        printf("age: %d, 刚成年", age);
    }
    else
    {
        printf("age: %d, 成年人", age);
    }

    printf("\n");
    // switch 判断
    unsigned short sex = 0;
    switch (sex)
    {
    case 1:
        printf("sex: %d, 性别: 男", sex);
        break;
    case 2:
        printf("sex: %d, 性别: 女", sex);
        break;
    default:
        printf("sex: %d, 性别: 未知", sex);
        break;
    }

    printf("\n");
    // :? 三元操作符判断
    unsigned short score = 99;
    printf("score:%d, %s", score, score > 60 ? "及格了" : "未及格");
    printf("\n");

    return 0;
}
