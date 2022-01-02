#include <iostream>
#include <vector>

using namespace std;


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
auto transform(auto func){return [=](const auto& container){return transform_(container,func);};}

auto operator|(const auto& left, const auto& right){return right(left);}

template<typename Container> auto print_(const Container& container)
{
    auto it = container.begin();
    for(const auto& item : container){
        cout << item;
        if(it != container.end()-1)
            cout << ", ";
        ++it;
    }
    cout << endl;
    return container;
}
auto print(){return [](const auto& var) {return print_(var);};}

int main()
{

    return 0;
}
