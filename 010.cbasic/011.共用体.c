#include <stdio.h>
#include <string.h>

union Data
{
    int i;
    float f;
    char s[10];
};

int main(int argc, char const *argv[])
{
    union Data data;
    // 这样整体赋值再使用是无效的， 它们地址相同
    data.i = 10;
    data.f = 3.14;
    strcpy(data.s, "name");
    printf("address: %p; i: %d;\n", &data.i, data.i); // address: 0xffffdf6be378; i: 1701667182;
    printf("address: %p; f: %f;\n", &data.f, data.f); // address: 0xffffdf6be378; f: 70062382309412494639104.000000;
    printf("address: %p; s: %s;\n", &data.s, data.s); // address: 0xffffdf6be378; s: name;

    // 正确使用共用体的方式
    data.i = 10;
    printf("address: %p; i: %d;\n", &data.i, data.i); // address: 0xffffdf6be378; i: 10;
    data.f = 3.14;
    printf("address: %p; f: %f;\n", &data.f, data.f); // address: 0xffffdf6be378; f: 3.140000;
    strcpy(data.s, "name");
    printf("address: %p; s: %s;\n", &data.s, data.s); // address: 0xffffdf6be378; s: name;
    return 0;
}
