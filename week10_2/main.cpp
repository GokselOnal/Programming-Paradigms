#include <iostream>
#include <vector>
#include <list>
#include <numeric>

using namespace std;


template<typename Container>
auto sum(const Container& v)
{
    auto result = 0;
    for(const auto& item: v)
        result += item;
    return result;
}

template<typename Container, typename T, typename Lambda>
auto accumulate_(const Container& v, T initial_value, Lambda lambda)
{
    auto result = initial_value;
    for(const auto& item: v){
        result = lambda(result, item);
        //result += item;
    }
    return result;
}

template<typename T, typename Lambda>
auto accumulate(T initial_value, Lambda lambda){return [=](const auto v){accumulate_(v, initial_value, lambda);};}

auto bar()
{
    cout << "Hi There" << endl;
    return 100;
}

auto foo(){
    bar(), bar(), bar();
                 //only last one returns the value, but cout part is executed
    bar(); bar(); bar(); // if you use with ; operator all of them returns

//    for(int i = 0, j = 0; i < 10; i += 2; j++)
//    {

//    }

    return 10,20,30;
}

//template<typename ... Ts>
void print(const auto& ... ts)
{
    ((cout << ts << endl), ...); //fold expression
}

// fold exp sum
auto sums(const auto& ... values){return (values + ...);}


int main()
{
    print<int, float, char>(10, 1.1, 'a');
    print(10, 1.1, 'a');

    cout << sums(10, 3.14, 100.1f) << endl;


    auto v = list<int>{1,2,3,4,5};
    auto v_f = vector<float>{1.1,2.2,3.3,4.4,5.5};
    cout << sum(v) << endl;

    auto adder = [](auto a, auto b){return a + b;};
    auto multiplier = [](auto a, auto b){return a * b;};

    cout << accumulate_(v, 1.1, adder) << endl;
    cout << accumulate_(v, 1, multiplier) << endl;
    cout << accumulate_(v_f, 2.4f, multiplier) << endl;

    //std version
    cout << std::accumulate(v_f.begin(), v_f.end(), 2.4f, multiplier) << endl;
    cout << std::accumulate(v_f.begin()+1, v_f.end()-1, 2.4f, multiplier) << endl;

    return 0;
}
