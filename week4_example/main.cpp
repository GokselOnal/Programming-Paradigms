#include <iostream>
using namespace std;

struct Fahrenheit; // promise to the compiler that there is a structure called Fahrenheit to be decleared
struct Celsius
{
    static char suffix;
    double value;
    //Celsius(): value(0) {}
    Celsius(double value = 0.0): value(value){}
    // forward decleration of a method
    explicit Celsius(const Fahrenheit& f); //: value((f.value - 32.0) / 180.0 * 100.0){}

    void operator=(const Fahrenheit& f);

    operator double(){ return value;}
};

struct Fahrenheit
{
    static char suffix;
    double value;
    Fahrenheit(double value = 0.0): value(value){}
    Fahrenheit(const Celsius& c): value(c.value / 100.0 * 180.0 + 32.0){}
    operator double(){ return value;}
};

Celsius::Celsius(const Fahrenheit& f) : value((f.value - 32.0) / 180.0 * 100.0){}

void Celsius::operator=(const Fahrenheit& f)
{
    value = (f.value - 32.0) / 180.0 * 100.0;
}

char Celsius::suffix = 'C';
char Fahrenheit::suffix = 'F';

template<typename T>
void print(const T& c){ cout << c.value << " " << T::suffix << endl;}

//void print(const Celsius& c){ cout << c.value << " C"<< endl;}
//void print(const Fahrenheit& f){ cout << f.value << " F"<< endl;}



bool operator ==(const Celsius& left, const Fahrenheit& right)
{
    return left.value == Celsius(right).value;
}

bool operator ==(const Fahrenheit& left, const Celsius& right)
{
    return left.value == Fahrenheit(right).value;
}

int operator +(const Celsius& left, const Fahrenheit& right)
{

    return left.value + Celsius(right).value;
}

int operator +(const Fahrenheit& left, const Celsius& right)
{
    return left.value + Fahrenheit(right).value;
}


int main(int argc, char* argv[])
{
    auto temp1 = Celsius(100.0);
    print(temp1);
    cout << (double)temp1 << endl;

    auto temp2 = Fahrenheit(30.0);
    print(temp2);

    auto temp3 = Fahrenheit(temp1);
    print(temp3);

    auto temp4 = Celsius(temp3);
    print(temp4);

    if(operator==(temp3, temp4))
    {
        cout << "Both temperatures are the same" << endl;
    }

    if(temp3 == temp4)
    {
        cout << "Both temperatures are the same" << endl;
    }

    cout << (double)temp1 << endl;
    cout.operator <<((double)temp1).operator<<(endl);

    //temp4 = Celsius(Fahrenheit(40.0));
    temp4 = Fahrenheit(40.0); // blocked because of explicit ctor but uncloked by operator=

    cout << temp1 + temp2 << endl;


    return 0;
}
