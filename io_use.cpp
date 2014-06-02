#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void getw(string& t, ifstream& in)
{
    in >> t;
}

int read_string(vector<string> &words, ifstream& in)
{
    int i = 0;
    while(!in.eof())
        getw(words[i++], in);

    return (i-1);
}

int main()
{
    vector<int> v(10);

    // Another way to iterate inside vector
    for(auto p = v.begin(); p != v.end(); ++p)
        cout << *p << '\t';
    cout << endl;

    // Yet another way to iterate inside vector
    for(auto &data: v)
        data += 2;

    for(auto data: v)
        cout << data << '\t';
    cout << endl;

    ifstream in("data");
    vector<string> w(1000);

    int howmany = read_string(w,in);
    w.resize(howmany);

    sort(w.begin(),w.end());

    for(auto str: w)
        cout << str << endl;

    ifstream myin("data");
    istream_iterator<int> another_in(myin); // iterate file and interpreted as integer
    istream_iterator<int> eos; // default is end of file

    cout << accumulate(another_in, eos, 0);

    return 0;
}
