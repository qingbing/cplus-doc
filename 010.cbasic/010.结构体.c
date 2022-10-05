#include <stdio.h>
#include <string.h>

void print(char c[])
{
    printf("%s\n", c);
}

/**
 * 定义一个结构体的新类型
 */
typedef struct
{
    int id;
    char name[50];
    char author[50];
    void (*print)(char c[]); // 定义一个函数
} Book;

/**
 * 结构体作为参数进行传递
 */
void printBook(Book book)
{
    printf("bookID: %-10d; bookName: %-20s; bookAuthor: %-20s\n", book.id, book.name, book.author);
}

struct person
{
    char name[100];
    int age;
    void (*printPerson)(struct person *p);
};
void printPerson(struct person *p)
{
    printf("Name: %20s; Age: %10d\n", p->name, p->age);
}

int main(int argc, char const *argv[])
{
    // 初始化
    Book b1 = {10, "Chinese", "qingbing", print};
    Book b2;
    b2.id = 11;
    strcpy(b2.name, "Math");
    strcpy(b2.author, "who");
    // b2.print= print;

    printBook(b1);
    printBook(b2);

    // 对于结构体指针使用 "->" 访问成员
    Book *ptrBook;
    ptrBook = &b2;
    ptrBook->print = &print;
    printf("id: %d\n", ptrBook->id);
    ptrBook->print("hello");

    struct person p = {"姓名", 18, printPerson};
    p.printPerson(&p);
    return 0;
}
