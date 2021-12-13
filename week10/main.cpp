#include <iostream>

using namespace std;

template<typename>
struct TypeDisplayer{};

//std::integral
template<typename> struct is_integrall         {static const auto value = false;};
template<>         struct is_integrall<int>    {static const auto value = true;};
template<>         struct is_integrall<short>  {static const auto value = true;};
template<>         struct is_integrall<char>   {static const auto value = true;};
template<>         struct is_integrall<long>   {static const auto value = true;};

template<typename T> const bool is_integrall_v = is_integrall<T>::value;

//std::conditional // Class template
template<bool B, typename T1, typename T2> struct conditional_type               {using type = T1;};
template<typename T1, typename T2>         struct conditional_type<false, T1, T2>{using type = T2;};

// type alias template
template<bool B, typename T1, typename T2> using conditional_type_t = conditional_type<B,T1,T2>::type;


//std::is_same
template<typename T1, typename T2> struct is_samee      {static const bool value = false;};
template<typename T>               struct is_samee<T,T> {static const bool value = true;};



template<typename T>
void foo(){}

int main()
{


    const auto a = is_integrall<float>::value;
    cout << a << endl;

    using T = conditional_type<true, int, float>::type;
    auto t = TypeDisplayer<T>{};

    const auto b = is_samee<int,int>::value;
    cout << b << endl;

    using T2 = conditional_type_t<false, int, float>; // there is no ::type(type alias)

    return 0;
}
