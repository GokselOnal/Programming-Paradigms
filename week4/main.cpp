#include <iostream>
using namespace std;

struct Fraction{
    int n; // numerator
    int d; // denominator

    // default ctor
    Fraction() : n(0), d(1){ }
    Fraction(int n) : n(n), d(1){ }
    Fraction(int n, int d) : n(n), d(d){ }

    Fraction(const Fraction& other) : n(other.n), d(other.d) // copy constructor
    {
        cout << "Copy constructed" << endl;
    }

    void operator=(const Fraction& right) //copy assignment
    {
        cout << "Copy assignment" << endl;
        n = right.n;
        d = right.d;
    }

    void print() const // pass by constant reference
    {
        cout << n << " / " << d << endl;
    }

    operator double() const // conversion operator for double type request
    {
        return double(n) / d;
    }

    operator int() const
    {
        return int(double(n) / d);
    }

    double get_value() const
    {
        return double(n) / d;
    }
};

Fraction operator"" _frac(long double value)
{
    return Fraction((int)value,1);
}


/*free function form of overloading assignment operator is forbiden
void operator=(Fraction& left, const Fraction& right)
{
    left.n = right.n;
    left.d = right.d;
}*/

//free function
void print(const Fraction& f) // pass by constant reference
{
    cout << f.n << " / " << f.d << endl;
}

Fraction func_name(); // forward declaration


int main(int argc, char* argv[])
{
    auto i = 5;

    Fraction a;
    print(a);  // free func
    a.print(); // this pointer becomes equal to &a
    a = Fraction(20, 7); // copy assignment
    print(a);

    Fraction b(10);
    print(b);
    b.print();

    Fraction c(10,3);
    print(c);
    c.print();


    //modern way
    auto d = Fraction(10, 3);

    auto e = Fraction(d); //copy
    print(e);
    cout << e.get_value() << endl;

    cout << double(e) << endl;
    cout << (double)e << endl; //same

    auto f = 11.567_frac;
    print(f);
    return 0;
}
