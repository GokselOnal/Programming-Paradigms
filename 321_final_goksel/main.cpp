// S011827 GÖKSEL CAN ÖNAL
// GCC11

#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::map;
using std::pair;
using std::string;
using std::cout;
using std::endl;
using std::get;
using Date = string;
using Count = int;



using ProductCount = pair<string, Count>;
struct StockRecord
{
    string date;
    ProductCount product_count;
};

// makes ProductCount directly sendable to the console
auto& operator<<(std::ostream& os, const ProductCount& pc)
{
    const auto& [name, count] = pc;
    cout << "(" << name << ";" << count << ")";
    return os;
}

// makes StockRecord directly sendable to the console
auto& operator<<(std::ostream& os, const StockRecord& sr)
{
 cout << "(" << sr.date << ";" << sr.product_count << ")";
 return os;
}


#include <range/v3/all.hpp>
namespace views = ranges::views; // instead of ranges::views::*, directly use views::*
namespace actions = ranges::actions; // instead of ranges::views::*, directly use views::*
using namespace ranges; // instead of ranges::*, directly use *

int main(int argc, char* argv[])
{
    auto stock_data = vector<StockRecord>{
    {"2021-11-11", {"Motherboard", 2}},
    {"2021-12-02", {"SSD", 21}},
    {"2021-11-05", {"CPU", 12}},
    {"2021-11-21", {"GPU", 35}},
    {"2021-11-23", {"Keyboard", 3}},
    {"2021-11-11", {"Mouse", 20}},
    {"2021-12-02", {"Monitor", 10}},
    {"2021-12-11", {"CPU", 5}},
    };
    auto price_data = map<string, int>{
    {"Motherboard", 100},
    {"SSD", 60},
    {"CPU", 85},
    {"GPU", 120},
    {"Keyboard", 5},
    {"Mouse", 8},
    {"Monitor", 45},
    };

    // Q1 (15pts) - Write unique dates in ascending order when at least one stock delivery happened
    // Q2 (15pts) - Write all stock data sorted by ascending date
    // Q3 (25pts) - Write total stock of products acquired after all stock arrivals
    // Q4 (20pts) - Write product stocks owned at a specific date (2021-11-11)
    // Q5 (15pts) - Write the price of product stocks owned at a specific date (2021-11-11)
    // Q6 (10pts) - Snapshot at 10:00 that compiles successfully.

    // WRITE YOUR SOLUTIONS HERE - BEGIN //

    //Q1
    cout << "Unique Dates in Ascending Order:" << endl;
    auto dates = stock_data | views::transform([](const StockRecord& item){return item.date;})
                            | to<vector<string>>;
    dates |=  actions::sort | actions::unique;
    cout << (dates | views::all) << endl << endl;


    //Q2
    cout << "Stock Data Sorted by Date in Ascending Order:" << endl;
    sort(stock_data, std::less{}, &StockRecord::date);
    cout << (stock_data | views::all) << endl << endl;


    //Q3
    cout << "Total Stock:" << endl;
    auto stocks = stock_data | views::transform([](const StockRecord& item){return item.product_count;})
                             | to<vector<ProductCount>>;
    auto stocks_vec = stocks | to<vector<pair<string,int>>>;
    stocks |= actions::sort;

    auto chunked_rng = stocks | views::chunk_by([](const ProductCount& item1, const ProductCount& item2){return item1.first == item2.first;});
    auto total = chunked_rng  | views::transform([](const auto& item){
                                                 auto vec = item | to<vector<pair<string,int>>>;
                                                 return accumulate(vec | views::values,0);
                                                 });
    stocks_vec | views::keys | to<vector<string>>;
    cout << (stocks | views::all) << endl << endl;


    //Q4
    cout << "Stock on 2021-11-11:" << endl;
    auto d = "2021-11-11";
    sort(stock_data, std::less{}, &StockRecord::date);
    auto stock_date = stock_data | views::transform([](const StockRecord& item){return item;})
                                 | views::filter([&d](const StockRecord& item){return item.date <= d;})
                                 | to<vector<StockRecord>>;

    auto stock_date_name = stock_date | views::transform([](const StockRecord& item){return item.product_count;})
                                      | to<vector<ProductCount>>;;

    stock_date_name |= actions::sort;
    cout << (stock_date_name | views::all) << endl << endl;


    //Q5
    cout << "Stock Values on 2021-11-11:" << endl;
    auto stock_date_product = stock_date | views::transform([](const StockRecord& item){return item.product_count;});
    auto stock_date_product_vec = stock_date_product | to<vector<pair<string,int>>>;

    auto res = price_data | views::transform([&stock_date_product_vec](const pair<string, int>& item)
                                             {
                                                 auto it = find(stock_date_product_vec | views::keys, item.first);
                                                 auto indx_it = it - begin(stock_date_product_vec | views::keys);
                                                 auto vec = stock_date_product_vec | views::values | to<vector<int>>;
                                                 auto amount = vec[indx_it];
                                                 return amount * item.second;
                                             })
                          | views::filter([](auto val){return val != 0;});
    cout << res << endl << endl;



    // Using any imperative paradigm loop construct is FORBIDDEN!
    // (such as "for", "do-while", "while", "goto". you CANNOT use them!)
    // Using for_each algorithm either from std, or from ranges is FORBIDDEN!
    // Using any imperative paradigm conditional branching is FORBIDDEN!(such as "if", "switch")
    // Any forbidden keyword usage will cause you to lose all the points from related questions
    // Use ranges-v3 library for easier solutions. But all solutions that obey the above rules are accepted)
    // Hint: actions::sort function has two optional parameters
    // 1st one is a lambda that describes how to sort two similar items by returning a boolean
    // true means that two items are already sorted, false means that they need to be swapped
    // 2nd one is a lambda that returns the necessary portion of the whole item on which the sorting will be handled

    // WRITE YOUR SOLUTIONS HERE - END //
    return 0;
}

