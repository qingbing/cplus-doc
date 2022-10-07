#include <iostream>

typedef struct
{
    int id;
    char name[100];
    void print()
    {
        std::cout << "BookId: " << id << "; BookName: " << name << std::endl;
    }
} Book;

int main(int argc, char const *argv[])
{
    Book b1 = {11, "Chinese"};
    b1.print();
    return 0;
}
