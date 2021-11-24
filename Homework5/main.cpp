#include <iostream>
#include <typeinfo>

using namespace std;

auto print_typed = [](const auto& item)
{
    using type = typename remove_cvref<decltype(item)>::type;
    if constexpr(std::is_same<type, int>::value)
            cout << item << " <" << "int" << ">";
    else if constexpr(std::is_same<type, double>::value)
            cout << item << " <" << "double" << ">";
    else if constexpr(std::is_same<type, float>::value)
            cout << item << " <" << "float" << ">";
    else if constexpr(std::is_same<type, long>::value)
            cout << item << " <" << "long" << ">";
    else if constexpr(std::is_same<type, short>::value)
            cout << item << " <" << "short" << ">";
    else if constexpr(std::is_same<type, char>::value)
            cout << item << " <" << "char" << ">";
    cout << endl;
};

auto print_typed_(const int& item){cout << item << " <" << "int" << ">" << endl;}
auto print_typed_(const double& item){cout << item << " <" << "double" << ">" << endl;}
auto print_typed_(const float& item){cout << item << " <" << "float" << ">" << endl;}
auto print_typed_(const long& item){cout << item << " <" << "long" << ">" << endl;}
auto print_typed_(const short& item){cout << item << " <" << "short" << ">" << endl;}
auto print_typed_(const char& item){cout << item << " <" << "char" << ">" << endl;}

int main()
{
    print_typed(5);
    print_typed(5.1);
    print_typed(3.14f);
    print_typed(50L);
    print_typed('a');

    print_typed(5);
    print_typed_(5.1);
    print_typed_(3.14f);
    print_typed_(50L);
    print_typed_('a');

    return 0;
}
