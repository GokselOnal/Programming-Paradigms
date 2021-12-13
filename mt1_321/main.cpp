//S011827 Göksel Can Önal
//GCC11
#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <string>


struct Course
{
 int code;
 std::string name;
 void print() const { std::cout << "'CS" << code << " " << name << "'"; }
};




using namespace std;

//Q1
template<typename Container> auto print(const Container& container, const string& title)
{
    auto iter = container.begin();
    auto sz = container.size();
    auto k = 0;
    cout << title << endl;
    for(const auto& item : container)
    {
        cout << *iter;
        if(k != sz-1)
            cout <<", ";
        k++;
        iter++;
    }
    cout << endl << endl;
}

//Q2
template<typename T> auto my_swap(T& first, T& second)
{
    auto temp = first;
    first = second;
    second = temp;
}

//Q3
template<typename Container> auto transform(Container& container, auto func_obj)
{
    for (auto i = container.begin(); i != container.end(); ++i)
        for (auto j = i; j != container.end(); ++j)
            if(func_obj(*j, *i))
                my_swap(*i,*j);
    return container;
}

template<typename Container> auto my_sort(Container& container, auto func_obj){ return transform(container, func_obj);}


//Q4
//directly printable to console
ostream& operator<<(std::ostream& s, const Course& c)
{
    c.print();
    return s;
}

auto ascending_by_name = [](const Course& c1, const Course& c2 ){ return c1.name < c2.name;};
auto descending_by_code = [](const Course& c1, const Course& c2 ){ return c1.code > c2.code;};





int main(int argc, char* argv[])
{
    
    auto ascending = []<typename T>(const T& a, const T& b) { return a < b; };
    auto descending = []<typename T>(const T& a, const T& b) { return a > b; };
    auto v = std::vector<int>{10, 5, 8, -3, 1, 101};
    // Q1a (10 pts)
    print(v, "vector<int> original");

    // Q2 (5 pts)
    my_swap(v[1], v[5]);
    print(v, "vector<int> after swap");

    // Q3a (10pts)
    my_sort(v, ascending);
    print(v, "vector<int> ascending sorted");

    // Q3b (10pts)
    my_sort(v, descending);
    print(v, "vector<int> descending sorted");
    auto a = std::array<float, 6>{10.10f, 5.5f, 8.8f, -3.3f, 1.1f, 101.101f};
    // Q3c (10 pts)
    my_sort(a, ascending);

    // Q1b (10 pts)
    print(a, "array<float, 6> ascending sorted");
    my_sort(a, descending);
    print(a, "array<float, 6> descending sorted");

    auto l = std::list<Course>{
    {321, "Programming Paradigms"},
    {409, "Advanced C++ Programming"},
    {423, "Computer Vision"}
    };

    // Q2c (5 pts) - my_sort works on list<T>
    // Q4a (10 pts) - write ascending_by_name lambda
    // < and > operators that does alphabetical comparison are already overloaded for std::string in the std library
    my_sort(l, ascending_by_name);
    print(l, "list<Course> ascending sorted by name");

    // Q1c (5 pts) - print works on list<T>
    // Q3d (5 pts) - my_sort returns correctly for print to work (no extra copies of the container shall be made)
    // Q4b (5 pts) - write descending_by_code lambda
    print(my_sort(l, descending_by_code), "list<Course> descending sorted by code");

    return 0;
}
