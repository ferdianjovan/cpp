#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class point
{
    public:
        point(double x): x(x), y(0.0){}
        operator double()
        {
            return sqrt(x*x + y*y);
        }

    private:
        double x, y;
};

int main()
{
    double x =3.5;
    point p = x; // implicit conversion
    p = static_cast<point>(x); // explicit conversion

    // because of point::operator double()
    // you can convert point to double
    x = p;

    // example using vector
    vector<int> v(100);
    for(auto p = v.begin(); p != v.end(); ++p)
    //for(vector<int>::iterator p = v.begin(); p != v.end(); ++p)
        cout << *p << '\t';
    cout << endl;
    // v.begin() stores value whereas v.end() does not

    return 0;
}

// ternary operator ?:
// example (a < b)? a : b;
