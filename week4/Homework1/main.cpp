#include <iostream>

using namespace std;

template<typename T>
struct Vector3D
{
    T x, y, z;
    Vector3D(T x, T y, T z): x(x), y(y), z(z){}
    auto add(const Vector3D<T>& other_vec) // member-func
    {
        cout << "Inside member-func" << endl;
        x += other_vec.x;
        y += other_vec.y;
        z += other_vec.z;
    }
};


template<typename T> auto add(Vector3D<T>& first, const Vector3D<T>& second) // free-func
{
    cout << "Inside free-func" << endl;
    first.x += second.x;
    first.y += second.y;
    first.z += second.z;
}

template<typename T> auto print(const Vector3D<T>& vector)
{
    cout << vector;
}

//directly sendable to console
template<typename T> auto& operator<<(ostream& out, const Vector3D<T> vector)
{
    cout << vector.x << " " << vector.y << " " << vector.z << endl;
    return out;
}



int main()
{
    auto v1 = Vector3D<int>{10,20,30};
    auto v2 = Vector3D<int>{20,30,40};
    Vector3D<int> v3(30,40,50);
    Vector3D<float> v4(30.1f,40.2f,50.3f);

    print(v1);
    print(v2);
    print(v3);
    print(v4);

    add(v1, v2);
    print(v1);
    v1.add(v3);
    print(v1);

    return 0;
}
