

#include <iostream>
#include <string>
#include <cstdio>

class water
{
private:
    /* data */
    std::string m_name1 = "water";
public:
    water(int a);
    ~water();
    virtual void print1() = 0;
    virtual void print2() = 0;
    virtual void print3() = 0;
    void PrintWaterName()
    {
        std::cout << "i am water"<< std::endl;
    }
};

water::water(int a)
{
    printf("water init\n");
}

water::~water()
{
    printf("water destroy\n");
}

class food
{
private:
    /* data */
    std::string m_name2 = "food";
public:
    food(int a);
    ~food();
    virtual void print4()
    {
        std::cout << "print4"<< std::endl;
    }
    virtual void print5()
    {
        std::cout << "print5"<< std::endl;
    }
    virtual void print6()
    {
        std::cout << "print6"<< std::endl;
    }
    void PrintFoodName()
    {
        std::cout << "i am food"<< std::endl;
    }
};

food::food(int a)
{
    
    printf("food init\n");
}

food::~food()
{
    printf("food destroy\n");
}

class market:public water,public food
{
private:
    /* data */
    /* data */
    std::string m_name3 = "market";
    
public:

    market(int a);
    ~market();
    void print1()
    {
         std::cout << "print1"<< std::endl;
    }
    void print2()
    {
        std::cout << "print2"<< std::endl;
    }
    void print3()
    {
        std::cout << "print3"<< std::endl;
    }
    void PrintMarketName()
    {
        std::cout << "i am market"<< std::endl;
    }
};

market::market(int a):water(a),food(a)
{
    printf("market init\n");
}

market::~market()
{

    printf("market destroy\n");
}

int main()
{
    market *mar = new market(4);
    food *foo = (food*)mar;
    foo->PrintFoodName();

    void *voo = mar;
    food *foo1 = (food*)voo;
    foo1->print6();
    
    delete mar;
    printf("mar:%x,foo:%x,voo:%x,foo1:%x\n",mar,foo,voo,foo1);

    market mar1(4);
    return 0;
}

