#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct IntGreaterThanX
{
    int value;
    IntGreaterThanX(int value): value(value){}
    auto operator ()(int value_){return value_ > value;}
};

template<typename T>
struct GreaterThanX
{
    T value;
    GreaterThanX(T value): value(value){}
    auto operator ()(T value_){return value_ > value;}
};

template<typename T> auto greater_than_x(T value){return GreaterThanX<T>(value);}

struct Everything // dummy class
{
    auto operator ()(auto item){return 1;}
};

template<typename Container> auto print(const Container& container, auto class_obj)
{
    for(auto i = 0; i < container.size(); ++i)
        if(class_obj(container[i]))
            cout << container[i] << " ";
    cout << endl;
}

int main()
{
    auto gt_10 = IntGreaterThanX{10};
    cout << gt_10(5) << endl;
    cout << gt_10(11) << endl;

    auto gt_pi = GreaterThanX<float>{3.14f};
    cout << gt_pi(3.0f) << endl;
    cout << gt_pi(11.0f) << endl;

    auto gt_pi2 = greater_than_x(3.14f);
    cout << gt_pi2(3.0f) << endl;
    cout << gt_pi2(11.0f) << endl;

    auto a = array<float, 2>{2.2f, 6.6f};
    print(a, Everything());
    print(a, gt_pi);
    auto v = vector<int>{5, 10, 20};
    print(v, Everything());
    print(v, gt_10);

    return 0;
}
