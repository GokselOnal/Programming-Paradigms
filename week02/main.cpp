#include <iostream>

//pass by value makes copy

int n_vector = 0;
/*
struct{ int x; int y; } v1;
v1.x = 10;
v1.y = 20;
struct{ int x; int y; } v2;
v2.x = 1;*/

//typedef struct{ int x; int y; } Vector2d;
struct Vector2d
{
    int x; // member variable, attribute, property
    int y;

    Vector2d(int x_, int y_)
    {
        x = x_;
        y = y_;
    }

    Vector2d addVectors2d(/*const Vector2d& a1*,*/ const Vector2d& a2) const // first param. is redundant(OOP style), last const for first hidden param
    {
        return Vector2d(this->x + a2.x, this->y + a2.y);
    }
};

template<typename T>
struct Vector
{

    int n_dims = 0;
    T* values = nullptr;

    Vector(int n_dims, T* values): n_dims(n_dims), values(new T[n_dims]) // you dont have to use a different name like n_dims_, compiler knows
    {
        ++n_vector;
        //n_dims = n_dims_;
        //values = new int[n_dims];
        if(values != nullptr)
            for(int i=0; i < n_dims; i++)
                this->values[i] = values[i];
    }

    // overloading, default c-tor
    Vector()
    {
        ++n_vector;
    }

    ~Vector()
    {
        delete[] values;
        --n_vector;
    }

    /*
    Vector<T> addVector(const Vector<T>& other) const
    {
        Vector<T> result(n_dims, nullptr);
        if(n_dims != other.n_dims)
        {
            std::cout << "Number of dimensions don't hold" << std::endl;
            return result;
        }

        for(int i=0; i < n_dims; i++){
            result.values[i] = this->values[i] + other.values[i];
        }
        return result;
    }*/
    Vector<T> operator+(const Vector<T>& other) const
    {
        Vector<T> result(n_dims, nullptr);
        if(n_dims != other.n_dims)
        {
            std::cout << "Number of dimensions don't hold" << std::endl;
            return result;
        }

        for(int i=0; i < n_dims; i++){
            result.values[i] = this->values[i] + other.values[i];
        }
        return result;
    }
};


int i = 0; // global scope variable
int j = 1;

void doSomething() // free-function
{
    int i = 0;
    ::i += 1; // global i
    std::cout << i << std::endl;
}

/*
int e1 = 10;
int e2 = 20;

int f1 = 10;
int f2 = 20;

void addVectors()
{
    int k1 = e1 + f1;
    int k2 = e2 + f2;
}
*/


int e[2] = {10, 20};
int f[2] = {1, 2};
/*
void addVectors()
{
    int k[2];

    k[0] = e[0] + f[0];
    k[1] = e[1] + f[1];
}
*/

void addVectors(int* v1, int* v2)
{
    int k[2];

    k[0] = v1[0] + v2[0];
    k[1] = v1[1] + v2[1];
}

/*
Vector2d addVectors2d(Vector2d a1, Vector2d a2)
{

    //Vector2d k;
    //k.x = a1.x + a2.x;
    //k.y = a1.y + a2.y;
    //return k;
    return Vector2d(a1.x + a2.x, a1.y + a2.y);
}*/

/*
Vector2d addVectors2d(const Vector2d& a1, const Vector2d& a2) // instead using it as free func, use it in struct
{
    return Vector2d(a1.x + a2.x, a1.y + a2.y);
}
*/

int m[2] = {10, 20};
int n[2] = {1, 2};

void doSmt()
{
    static int m = 1000;
    m++;
    std::cout << "m = " << m << std::endl;
}

void doSmt1(int value)
{
    int m = 1000;
    m += value;
    std::cout << "m = " << m << std::endl;
}

void doSmt2(int value)
{
    int m = 10;
    m *= value;
    std::cout << "m = " << m << std::endl;
}

void increment_by_one(int& value)
{
    value++;
}

void multiply_by_two(int& value)
{
    value *= 2;
}

using Func_t = void(*)(int&);
void for_each(int* values, int n_items, Func_t func)
{
    for(int i = 0; i < n_items; i++){
        func(values[i]);
    }
}

auto increment(int& val1)
{
    return ++val1;
}

int main(int argc, char* argv[])
{
    using namespace std;

    int k = 0;
    cout <<"K = " << k++ << endl; // use value of k, at the end of the line increment k
    cout <<"K = " << k << endl;

    int l = 0; // directly increment
    cout <<"L = " << ++l << endl;
    cout <<"L = " << l << endl;

    doSmt(); // 1001
    doSmt(); // 1002
    doSmt(); // 1003
    doSmt1(10);
    doSmt2(15);

    //type of the function void(*)(int)
    using FuncPtr = void(*)(int);
    FuncPtr p1 = &doSmt1;
    FuncPtr p2 = &doSmt2;

    //instead of using doSmt1(10) or doSmt2(15) you can use;
    p1(10);
    p2(15);

    p1 = &doSmt2; //dynamically you can change that pointer
    p1(5);




    // Point p = new Point(); only option for Java 'reference semantic'
    // Object* p = new Object(); cpp

    int i = 0; // local variable
    doSomething();

    addVectors(&e[0], &f[0]);
    addVectors(&m[0], &n[0]);


    /*
    Vector2d v1;
    Vector2d v2;
    Vector2d v3, v4;
    v1.x = 10;
    v1.y = 20;
    v2.x = 1;
    v2.y = 2;
    */

    Vector2d v1(10,20), v2(1,2);

    //Vector2d K = addVectors2d(v1,v2);
    //Vector2d K = addVectors2d(v1,v2); // burada değişkenlere &, fonksiyonda parametrelere* yazmak yerine direkt olarak fonksiyondaki parametreye & ver aynı
    Vector2d K2 = v1.addVectors2d(v2); //OOP Style

    cout << K2.x << endl;
    cout << K2.y << endl;

    int Gvalues[3] = {11, 22, 33};

    //Vector D();

    Vector<int> G(3, Gvalues); //Vector G(3, &Gvalues[0]);
    cout << "Number of vector instances after G is " << n_vector << endl;

    //Vector<int> I = G.addVector(G); instead of this
    Vector<int> J = G.operator +(G); // change method name as operator+
    Vector<int> I = G + G; // more understandable
    cout << I.n_dims << endl;
    for(int i=0; i < I.n_dims; i++){
        std::cout << I.values[i] << endl;
    }

    return 0; // 0 means everything is okay
}
