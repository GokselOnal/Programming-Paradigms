// S011827 GÖKSEL CAN ÖNAL
// GCC 11

#include <iostream>
#include <vector>
#include <list>
#include <array>

using namespace std;
template<typename T>
concept IsContainer = requires(T t) {
 t.begin();
 t.end();
 t.size();
};


auto accumulate_(const IsContainer auto& container, auto initval, auto lambda)
{
     auto a = initval;
     for(const auto& item : container)
         a = lambda(a, item);
     return a;
}


template<typename Container>
requires(IsContainer<Container>)
auto filter_(const Container& container, auto lambda)
{
     auto new_container = Container{};
     for(const auto& item : container)
        if(lambda(item))
            new_container.push_back(item);
     return new_container;
}
// YOU CAN WRITE YOUR CODE HERE - BEGIN 1


//Q1)
string initval1 = "START";
auto lambda1 = [](auto val1, auto val2){return val1 + "_" + val2;};
//auto print_(const auto& item){cout << item << endl;}
template<typename Container>
auto print_(const Container& var) // result_filtered[0] (Q4)
{
    using type = typename remove_cvref<decltype(var)>::type;
    if constexpr(is_same_v<type,vector<string>>){
        auto it = var.begin();
        for(const auto& item : var){
            cout << "   " << item << endl;
        }
        cout << endl;
    }
    else{cout << var << endl;}
}


auto print_(const vector<vector<string>>& var)
{
    cout << "level 0: current item is a container with " << var.size() << " items which are: " << endl;
    for(auto i = 0; i < var.size(); ++i){
        cout << "   level 1: current item is a container with " << var[i].size() << " items which are:" << endl;
        cout << "";
        print_(var[i]);
    }
}

template<IsContainer Container, IsContainer Container_str, IsContainer Container_one_shot>
auto print_(const Container& p1, Container_str& p2, Container_one_shot& p3)
{
    auto item_count = 0;
    cout << "Printing item " << ++item_count << endl;
    print_(p1);
    cout << "Printing item " << ++item_count << endl;
    print_(p2);
    cout << "Printing item "<< ++item_count << endl;
    print_(p3);
}



static int k = 1;

// YOU CAN WRITE YOUR CODE HERE - END 1


int main(int, char* [])
{
     // accumulate_ and filter_ free-functions, and IsContainer concept are already given to you.
     // Q1: Accumulate an array of any number of strings in a single string by concatenating all of them.
     // Q1a (5pts): Write initval1 correctly to match with the console output given.
     // Q1b (5pts): Write lambda1 correctly to match with the console output given.
     // Q2: Accumulate a vector of strings in such a way that strings are clustered according to their length.
     // This means that strings with a lendth of L will be accumulated in Lth container in the returned container of containers.
     // Check the console output for more informative understanding.
     // Hint: std::vector has a resize(int) method that dynamically allocates different number of item slots at run-time.
     // Q2a (5pts): Write initval2 correctly.
     // Q2b (20pts): Write lambda2 correctly.
     // Q3: Filter the container such that only the clusters of strings that are non-empty stays.
     // Q3a (5pts): Write lambda_filter correctly.
     // Q4: Write a print_ overload-set that matches the supplied console output.
     // Q4a (10pts) print_(result_filtered[0]); matches with the console output given.
     // Q4b (5pts) print_(result_filtered[0][0]); matches with the console output given.
     // Q4c (15pts) print_(result_filtered); matches with the console output given. Be careful about the indentations depending on the level.
     // Q4d (10pts) print_(result_filtered[0], result_filtered[0][0], result_filtered); matches with the console output given.
     // In this question, variable input version of print_ free-function writes "Printing item 1", "Printing item 2", ...
     // kind of extra lines when compared with the above print_ that prints single thing at a time. Do not miss that.
     // Hint: Be careful, std::string is also a container! std::string is implemented as a container of "char"s in std library.
     // So, IsContainer concept returns true for std::string type as well.
     // Q5 (10pts): Snapshot 1
     // Q6 (10pts): Snapshot 2
     // YOU CAN WRITE YOUR CODE HERE - BEGIN 2


     //Q2)

     auto initval2 = vector<vector<string>>(6);//k
     auto lambda2 = [](auto container, auto val1)
     {
         if(container[val1.size()].empty()){
            container[val1.size()].push_back(val1);
            //container.resize(++::k); :(
         }
         else{
             container[val1.size()].push_back(val1);
         }
         return container;
     };


     //Q3)
     auto lambda_filter = [](const auto& container){return !container.empty();};





     // YOU CAN WRITE YOUR CODE HERE - END 2

    {
     auto container = array<string, 10>{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
     auto result = accumulate_(container, initval1, lambda1);
     cout << "Printing concatenation of all strings in the container:" << endl;
     print_(result);
     cout << endl;
     }


     {
     auto container = vector<string>{"quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
     auto result = accumulate_(container, initval2, lambda2);
     cout << "Grouped the strings according to their length. Size of the result container is " << result.size() << endl;
     for(int i=0; i<result.size(); ++i)
     cout << result[i].size() << " strings with length " << i << endl;

     auto result_filtered = filter_(result, lambda_filter);
     cout << "Size of result_filtered container that contains only non-empty strings is " <<
     result_filtered.size() << endl;
     for(int i=0; i<result_filtered.size(); ++i)
     cout << result_filtered[i].size() << " strings with length " << result_filtered[i][0].size() << endl;

     cout << "Printing index 0 of the container, which is another container by the way" << endl;
     print_(result_filtered[0]);
     cout << "Printing the first element of the container in result_filtered[0]" << endl;
     print_(result_filtered[0][0]);
     cout << "Printing the whole container" << endl;
     print_(result_filtered);
     cout << "This time, printing all the above in one shot:" << endl;
     print_(result_filtered[0], result_filtered[0][0], result_filtered);
     }
      return 0;
}
