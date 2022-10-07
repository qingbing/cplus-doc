/*
CURD： 增删改查
*/
#include <iostream>
using namespace std;

typedef struct
{
    int id;
    string name;
    string info()
    {
        return to_string(id) + " " + name;
    }
} Book;

class BookManager
{
private:
public:
    BookManager()
    {
    }

    bool create()
    {
    }

    bool del() {}

    bool update()
    {
    }
    
    Book view(int id)
    {
    }
};

int main(int argc, char const *argv[])
{
    return 0;
}
