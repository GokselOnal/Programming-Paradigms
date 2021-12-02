#include <iostream>
#include <initializer_list>
using namespace std;

struct Vector3d;

struct Vector3d_iterator
{
    Vector3d* obj;
    int index;
    auto get() const;
    auto operator*() const;
    auto operator++() // as a prefix overload
    {
        ++index;
    }

    //auto operator++() // as a suffix overload
    //{
        //index++;
    //}

    bool operator ==( const Vector3d_iterator& other) const
    {
        return obj == other.obj && index == other.index;
    }

    // compiler automatically does this one when you create operator== overload, we don't need that func
    bool operator !=( const Vector3d_iterator& other) const
    {
        //return obj != other.obj || index != other.index;
        return !(*this == other);
    }
};


struct Vector3d
{
    int size;
    int x;
    int y;
    int z;
    Vector3d(std::initializer_list<int> il)
    {
        size = il.size();
        if(size > 3) size = 3;
        cout << "size of IL=" << size << endl;
        auto ptr = il.begin();
        if(size >= 1) x = ptr[0];
        if(size >= 2) y = ptr[1];
        if(size >= 3) z = ptr[2];
    }
    Vector3d(int, int){cout << "2 integers passed to me" << endl;}
    //Vector3d(int, int, int){cout << "3 integers passed to me" << endl;}

    auto begin(){return Vector3d_iterator{this, 0};}

    auto end()
    {
        return Vector3d_iterator{this, size};
    }
};

auto Vector3d_iterator::get() const
{
    if(index == 0) return obj->x;
    if(index == 1) return obj->y;
    if(index == 2) return obj->z;
    return -1;
}

auto Vector3d_iterator::operator*() const
{
    if(index == 0) return obj->x;
    if(index == 1) return obj->y;
    if(index == 2) return obj->z;
    return -1;
}


int main(int argc, char* argv)
{
    /*

    int i = 100;
    int* ptr = &i;

    cout << ptr[0] << endl; // *(ptr + 0)
    cout << *ptr << endl;

    //same
    cout << *(ptr + 1) << endl;
    cout << *(1 + ptr) << endl;
    cout << 1[ptr] << endl;
   */

    auto v = Vector3d{1,6,3,4}; // v = Vector3d(); does not works without ctor, {} works
    cout << "x=" << v.x << endl;
    cout << "y=" << v.y << endl;
    cout << "z=" << v.z << endl;


    //initializer list is not avaliable on Vector3d()
    // we have both ctor and il-ctor when we use {} il-ctor has priority, when () it used ctor is called


   auto it = v.begin();
    //cout << "x with iterator access is " << endl it.obj ->x << endl// it.obj->  ==  (*(it.obj)).

   cout << "x with iterator access is " << it.get() << endl;
   it.index++;
   cout << "y with iterator access is " << it.get() << endl;




   cout << "x with iterator access is " << it.operator*() << endl;
   it.index++;
   cout << "y with iterator access is " << it.operator*() << endl;
   it.index++;
   cout << "z with iterator access is " << it.operator*() << endl;


  //cout << "x with iterator access is " << endl it.obj ->x << endl// it.obj->  ==  (*(it.obj)).

   cout << "x with iterator access is " << *it << endl;
   ++it;
   cout << "y with iterator access is " << *it << endl;
   ++it;
   cout << "z with iterator access is " << *it << endl;


   cout << "for loop for iterator access" << endl;
   for(auto it = v.begin(); it != v.end(); ++it)
       cout << *it << endl;



   cout << "for range-for-loop for iterator access" << endl;
   for(auto item : v)
       cout << item << endl;



    return 0;
}
