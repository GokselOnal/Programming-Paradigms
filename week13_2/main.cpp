#include <iostream>
#include <tuple>
#include <string>

using namespace std;

template<typename ...>
struct TypeDisplayer;

struct Custom
{
    int i;
    float f;
    string s;
};
auto obj = std::tuple<int, float, string>{};


using TUPLE = std::tuple<int, float, string, Custom, float>;

// if something is tuple or not
template<typename T>      struct is_tuple                    {static const bool val = false;};
template<typename ... Ts> struct is_tuple<std::tuple<Ts...>> {static const bool val = true;};

template<typename T>
const bool is_tuple_v = is_tuple<T>::val;


int main()
{
    auto pair = std::pair<int, float>{10, 3.14f};
    auto tuple = TUPLE{10, 3.14f, "Hi there", Custom{}, 2.2f};

    cout << is_tuple<TUPLE>::val << endl;
    cout << is_tuple<std::pair<int, float>>::val << endl;

    cout << is_tuple_v<TUPLE> << endl;

    cout << std::get<float>(tuple) << endl;
    cout << std::get<4>(tuple) << endl;


    using type_index_3 = std::tuple_element_t<3, TUPLE>; //returns type
    //auto td = TypeDisplayer<type_index_3>{};

    cout << std::tuple_size_v<TUPLE> << endl;

    return 0;
}
