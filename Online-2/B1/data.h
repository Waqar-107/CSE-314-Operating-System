#define SZ 2048

#include<string>
#include<stdlib.h>

struct writer
{
    std :: string name;
    int current, borrow;

    writer(){}
    writer(std :: string name, int current, int borrow)
    {
        this->name = name;
        this->current = current;
        this->borrow = borrow;
    }
};

struct catalog
{
    int id;
    struct writer a, b, c;
    std :: string text;
};

