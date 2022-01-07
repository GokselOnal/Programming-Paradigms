#include <iostream>
#include <vector>

using namespace std;

struct Date
{
    int year =-1, month =-1, day=-1;
    Date(int year): year(year){}
    Date(int year, int month): year(year), month(month){}
    Date(int year, int month, int day): year(year), month(month), day(day){}
    Date(){} // for vector initialization
};


//directly sendable to console
auto& operator <<(ostream& out, const Date& date)
{
    if(date.year == -1 && date.month == -1 && date.day == -1)
        cout << "<Uninitialized>" << endl;
    else if(date.month == -1 && date.day == -1)
        cout << "(" << date.year << ")" << endl;
    else if(date.day == -1)
        cout << "[" << date.year << "-" << date.month << "]" << endl;
    else
        cout << date.year << "-" << date.month << "-" << date.day << endl;
    return out;
}

template<typename Container> auto print(const Container& container)
{
    for(const auto& item: container)
        cout << item << endl;
}


int main()
{
    auto d1 = Date(2012);
    auto d2 = Date(2020, 7);
    auto d3 = Date(2020, 10, 30);

    auto v = vector<Date>(3);
    print(v);
    auto vec = vector<Date>{d1,d2,d3};
    print(vec);

    auto v_int = vector<int>{1,2,3};
    print(v_int);

    return 0;
}
