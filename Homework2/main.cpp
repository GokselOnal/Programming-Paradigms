#include <iostream>

using namespace std;

struct IntVector
{
    int n_dims;
    int* vector = nullptr;
    IntVector(int n_dims): n_dims(n_dims)
    {
        vector = new int[n_dims];
        for(auto i = 0; i < n_dims; ++i)
            vector[i] = 0;
    }
    IntVector(const IntVector& other_vec) // copy ctor
    {
        cout << "Constructor is copied." << endl;
        n_dims = other_vec.n_dims;
        vector = new int[n_dims];
        for(auto i = 0; i < n_dims; ++i)
            vector[i] = other_vec.vector[i];
    }
    auto set(int index, int value){vector[index] = value;}
    auto print()
    {
        for(auto i = 0; i < n_dims; ++i)
            cout << vector[i] << " ";
        cout << endl;
    }
    ~IntVector(){delete[] vector;}
};

auto set(int index, int value, IntVector& vector) //free-func for set
{
    vector.vector[index] = value;
}

auto print(const IntVector& vector) //free-func for print
{
    for(auto i = 0; i < vector.n_dims; ++i)
        cout << vector.vector[i] << " ";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter dimension of vector: ";
    cin >> n;
    IntVector ivec (n);
    ivec.print();
    for(auto i = 0; i < ivec.n_dims; ++i)
        ivec.set(i, i*10);
    auto v2 = IntVector(ivec);
    ivec.print();
    v2.print();
    set(2,99,v2);
    print(v2);

    return 0;
}
