#include <iostream>
#include <vector> // an array dynamically allocated contiguously in heap memory
#include <list>   // this is a linked-list implementation
#include <string>

using namespace std;

void incrementBy(int& i, int value){ i += value;}
void decrementBy(int& i, int value){ i -= value;}

using FunctionPtr = void(*)(int&, int);


// very generic algorithm
// it doesn't care what to do with the content
// all it cares is to transform the contents of the vector according to what func does
template<typename Container>
void transform(Container& a, FunctionPtr func, int by_what)
{
    for(auto& item : a)
        func(item,by_what);
}

/*
template<typename T>
void transform(std::list<T>& a, FunctionPtr func)
{
    for(auto& item : a)
        func(item);
}
*/

template<typename Container>
void print(const Container& container, std::string title)
{
    cout << title << endl;
    for(auto& item : container)
        cout << item << endl;
}

int main(int argc, char* argv [])
{
    auto v = std::vector<int>(10); // initialize a vector instance storing 10 integers which are default cıbstructed

    auto v2 = std::vector<int>{10, 20, 30, 40, 50};
    auto v3 = std::list<int>{10, 20, 30, 40, 50};
    cout << v[0] << endl;

    cout <<"v2" << endl;
    for(int i=0; i < v2.size(); ++i)
    {
        //cout << v2[i] << endl;
    }

    cout <<"v2 with iterators" << endl;
    for(auto it = v2.begin(); it != v2.end(); ++it)
    {
        cout << *it << endl;
    }

    cout <<"v2 with iterators (range-for version)" << endl;
    for(auto item : v)
    {
        cout << item << endl;
    }

    //auto p = new int[10];
    //delete[] p;
    //auto v = vector<int>(10); //dynamic memory allocation of 10 integers

    for(auto& item : v2)
        item++;

    for(auto& item : v2)
        cout << item << endl;

    for(auto& item : v2)
        incrementBy(item,1);

    for(auto& item : v2)
        cout << item << endl;


    //transform<int>(v2, &increment);
    //transform<int>(v2, &increment);
    for(auto& item : v2)
        cout << item << endl;

    transform(v2, &incrementBy, 1);
    for(auto& item : v2)
        cout << item << endl;


    print(v3,"v2 with iterators (range-for version)");
    return 0;
}
