#include <iostream>
#include <cstdio>

using namespace std;

class Base
{
public:
    virtual void a() { cout << "Base a()" << endl; }
    virtual void b() { cout << "Base b()" << endl; }
    virtual void c() { cout << "Base c()" << endl; }
};

class Derive : public Base
{
public:
    virtual void b() { cout << "Derive b()" << endl; }
};

int main()
{
    cout << "-----------Base------------" << endl;
    Base *q = new Base;
    long *tmp1 = (long *)q;
    long *vptr1 = (long *)(*tmp1);
    for (int i = 0; i < 3; i++)
    {
        printf("tmp1[%d] : %p\n", i, tmp1[i]);
    }

    Derive *p = new Derive;
    long *tmp = (long *)p;
    long *vptr = (long *)(*tmp);
    cout << "---------Derive------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        printf("vptr[%d] : %p\n", i, vptr[i]);
    }

    return 0;
}