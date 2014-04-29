#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// void myadd(const int &x) // this case makes x not possible to be changed.
void myadd(int &x); // function declaration

int mydivide(int x, int y = 2)
{
    return x/y;
}

template <class A> A sum (A a, A b) // you can have multiple template class not only A
{
    return a+b;
}

namespace mynamespace
{
    int x = 3;
    int tambahx(int y)
    {
        return y + x;
    }
}

int main()
{
//  string input;
//  cout << "What is your name? ";
//  getline(cin,input);
//  cout << "Hello " << input << ", what is your favorite football team? ";
//  getline(cin,input);
//  cout << "What a coincidence! I also like " << input;

//    string input;
//    int price,discount,semitotal,total;
//    bool answer = false;
//    char theanswer;
//    getline(cin,input);
//    stringstream(input) >> price;
//    while((price == 0 && !answer) || price < 0)
//    {
//        if(price < 0)
//        {
//            cout << "Price can not be minus." << endl;
//            getline(cin,input);
//            stringstream(input) >> price;
//        }
//        else if (price == 0)
//        {
//            cout << "Are you sure the price is " << price << "?(Y\\N) \n";
//            getline(cin,input); stringstream(input) >> theanswer;
//            if(theanswer == 'Y') answer = true; else answer = false;
//            if(!answer)
//            {
//                getline(cin,input);
//                stringstream(input) >> price;
//            }
//        }
//    }
//    getline(cin,input);
//    stringstream(input) >> discount;
//    total = (semitotal=price-discount,semitotal*1.1);
//    cout << "The total price is " << total;

// array and listing inside array.
//    int data [5] = {1,2,3,4,5};
//    for(auto a:data)
//        cout << a << " ";

// for, switch and goto
//    for(int b = 0; b < 11; b++)
//    {
//        switch(b){
//            case 5: goto test;
//            default: cout << b;
//        }
//
//    }
//    test: cout << "Keluar!";

//    int x;
//    string input;
//    getline(cin,input); stringstream(input) >> x;
//    myadd(x);
//    cout << x << endl;
//    cout << mydivide(x);

//    int x = 5, z = 10;
//    int *y = &x;
//    cout << *y << endl;
//    y = &z;
//    cout << *y << endl;
//    z++;
//    cout << *y << " " << x;

//    int x = 5, z = 10;
//    int &y = x;
//    cout << y << endl;
//    y = z;
//    cout << y << endl;
//    z++;
//    cout << y << " " << x;

    int a = 5, b = 7;
    cout << sum(a,b) << endl; // or you can write sum <int> (a,b)

    int x = 4;
    cout << x << " " << mynamespace::x << " " << mynamespace::tambahx(x);
}

void myadd(int &x)
{
    x++;
}
