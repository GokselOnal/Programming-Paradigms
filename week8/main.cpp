#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

enum Color{Red, Green, Blue};
enum Boolean{False, True};

struct Library
{
    string name;
    string location;
    Boolean is_public;
    int year;
};

//this requires i and j to be present at the call time
//bool less_than(int i, int j){return i < j;}
bool less_than_50(int i){return i < 50;}
bool less_than_2000(int i){return i < 2000;}
//more clever way is lifting a function

bool less_than_(int i, int j){return i < j;}
auto less_than(int j) // lifted function
{
    return [j](int i){return less_than_(i,j);};
}


bool greater_than_(int i, int j){return i > j;}
auto greter_than(int j){return [j](int i){return greater_than_(i, j);};}



auto get_name_(const auto& anything){return anything.name;}
auto get_name(){return [](const auto& anything){return get_name_(anything);};}



auto get_year_(const auto& anything){return anything.year;}
auto get_year(){return [](const auto& anything){return get_year_(anything);};}


auto compose(auto f, auto g){return [=](auto item){return g(f(item));};} // [f=f, g=g] || [f, g] || [=]

auto operator|(auto f, auto g){return compose(f,g);}


template<typename>
struct TypeDisplay;

//ULTRA GENERIC TRANSFORM ALGORITHM!
template<template<typename...> typename ContainerTemplate, typename Item, typename Lambda>
auto transform_(const ContainerTemplate<Item>& container, Lambda func)
{
    auto it = container.begin();
    const auto& item = *it;
    using type_of_item = typename remove_cvref<decltype(item)>::type;

    using type_of_returned_item = decltype(func(type_of_item{}));

    auto new_container = ContainerTemplate<type_of_returned_item>(container.size());

    auto it1 = container.begin();
    auto it2 = new_container.begin();
    while(it1 != container.end())
    {
        *it2 = func(*it1);
        ++it1;
        ++it2;
    }
    return new_container;
}
//lifted verison
auto transform(auto func){return [=](const auto& container){return transform_(container,func);};}


template<typename Container>
auto filter_(const Container& container, auto func)
{
    auto filtered_container = Container{};
    for(const auto& item: container)
        if(func(item))
            filtered_container.push_back(item);
    return filtered_container;
}
auto filter(auto func){return [=](const auto& container){return filter_(container,func);};}


template<typename T>
concept AnyContainer = requires(T container)
{
      container.begin();
      container.end();
      container.size();
};

void print(const AnyContainer auto& container)
{
    for(const auto& item: container)
        cout << item << endl;
}

int main()
{
    auto result1 = less_than_(10,25);
    cout << (result1 ==true ? "True": "False") << endl;

    auto lambda = less_than(25);
    auto result2 = lambda(10);
    cout << (result2 ==true ? "True": "False") << endl;

    auto v = list<Library>{
        {"Özyeğin University", "Çekmeköy", Boolean::True, 2009},
        {"Bogazici University", "Hisar", Boolean::True, 1863},
    };

    auto library1 = *v.begin();
    cout << "Name of the first library is " << get_name_(library1) << endl;

    auto gn = get_name(); //lifted way
    cout << "Name of the first library is " << gn(library1) << endl;


    auto gy = get_year(); //lifted way
    cout << "Year of the first library is " << gy(library1) << endl;


    auto before_2000 = less_than(2010);
    cout << (before_2000(gy(library1)) ? "True": "False") << endl;

    auto composed_by_before2000 = compose(gy, before_2000);
    cout << (composed_by_before2000(library1) ? "True": "False") << endl;

    auto composed_by_before2000_opovl = gy | before_2000;
    cout << (composed_by_before2000_opovl(library1) ? "True": "False") << endl;
    cout << ((gy | before_2000)(library1) ? "True": "False") << endl; //same


    auto new_container = transform_(v, get_year() | less_than(2000));
    print(new_container);


    auto new_container2 = transform_(v, get_year());
    print(new_container2);


    auto new_container3 = transform_(v, get_name());


    auto get_names = transform(get_name());
    auto new_container4 = get_names(v);
    print(new_container4);


    auto filtered = filter(get_year() | less_than(2000));
    cout << filtered(v).size()<< endl;


    return 0;
}
