#include <iostream>

using namespace std;

// 1, 1, 2, 3, 5, 8, 13, ...

struct FibonacciGenerator
{
    int& a;
    int& b;

    FibonacciGenerator(int& a, int& b) : a{a}, b{b}
    {
    }

    auto operator() ()
    {
        auto ret_value = a + b;
        a = b;
        b = ret_value;
        return a;
    }
};


int main(int argc, char* argv[])
{
    auto a=0;
    auto b=1;

    auto fibo_gen = FibonacciGenerator{a, b};
    for(auto i=0; i<10; ++i)
        cout << fibo_gen() << endl;

    auto fibo_gen_lambda = [&a, &b]() mutable {
        auto ret_value = a + b;
        a = b;
        b = ret_value;
        return a;
    };

    for(auto i=0; i<10; ++i)
        cout << fibo_gen_lambda() << endl;

    cout << "local a = " << a << endl;
    cout << "local b = " << b << endl;

    return 0;
}
