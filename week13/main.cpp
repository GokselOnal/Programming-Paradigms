#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

void print_(const auto& container)
{
    for(const auto& item: container)
        cout << item << endl;
}

auto print_pair_(const auto& container)
{
    for(const auto& [key, value]: container)
        cout << key << "|" << value << endl;
}

template<typename Container1, typename Container2, typename FUNC>
auto cartesian_product(const Container1& v1, const Container2& v2, FUNC func)
{
    for(const auto& i1: v1)
        for(const auto& i2: v2)
            func(i1,i2);
}

template<typename Container1, typename Container2, typename Container3, typename FUNC>
auto cartesian_product(const Container1& v1, const Container2& v2, const Container3& v3, FUNC func)
{
    for(const auto& i1: v1)
        for(const auto& i2: v2)
            for(const auto& i3: v3)
            func(i1,i2,i3);
}

template<
        template<typename ...> typename CT1,
        template<typename ...> typename CT2,
        typename ITEMTYPE1,
        typename ITEMTYPE2
        >
auto zip(const CT1<ITEMTYPE1>& c1, const CT2<ITEMTYPE2>& c2)
{
    auto sz = c1.size();
    if(sz > c2.size())
        sz = c2.size();

    auto container = CT1<std::pair<ITEMTYPE1, ITEMTYPE2>>(sz);
    auto it1 = c1.begin();
    auto it2 = c2.begin();
    auto it_dest = container.begin();
    for(int i = 0; i < sz; ++i)
    {
        *it_dest = std::pair<ITEMTYPE1, ITEMTYPE2>{*it1, *it2}; // vector<pair<int, string>>
        ++it1;
        ++it2;
        ++it_dest;
    }
    return container;
}




int main()
{
    auto v1 = vector<int>{1,2,3};
    auto v2 = vector<string>{"aaa", "bbb", "ccc", "ddd"};

    //    for(const auto& i1: v1)
    //        for(const auto& i2: v2)
    //            cout << i1 << "/" << i2 << endl;

//    auto sz = v1.size();
//    if(sz > v2.size())
//        sz = v2.size();

//    for(int i =0; i < sz; ++i)
//        cout << v1[i] << "|" << v2[i] << endl;



    cartesian_product(v1,v2,[](int i, const string&s ){cout << i << "/" << s << endl;});


//    auto v_zipped = vector<pair<int, string>>{
//        {1,"aaa"},
//        {2,"bbb"},
//        {3,"ccc"}
//     };

    auto v_zipped = zip(v1,v2);
    print_pair_(v_zipped);


    return 0;
}
