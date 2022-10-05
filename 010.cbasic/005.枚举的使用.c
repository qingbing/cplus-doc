#include <stdio.h>

int main()
{
    // 针对连续的枚举类型，是可以遍历的，不连续的不可以
    enum WEEKDAY
    {
        MON = 1,
        TUS,
        WED,
        THU,
        FRI,
        SAT,
        SUN
    } weekday;
    for (weekday = MON; weekday <= SUN; weekday++)
    {
        printf("枚举元素: %d\n", weekday);
    }

    // 定义和赋值
    enum WEEKDAY today = THU;
    printf("今天是: %d\n", today);

    // 整数转换为枚举类型
    int a = FRI;
    today = (enum WEEKDAY)a;
    printf("今天是: %d\n", today);
    return 0;
}
