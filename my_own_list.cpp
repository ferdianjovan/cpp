#include <iostream>

using namespace std;

class list_element
{
  public:
        list_element(int n = 0, list_element* ptr = 0): d(n), next(ptr){}

        int d;
        list_element* next;
};

class my_list
{
    public:
        my_list(): head(0), cursor(0){}
        my_list(const int* arr, int n);

        ~my_list(); // destructor

        void prepend(int n)
        {
            if(head == 0)
                cursor = head = new list_element(n,head);
            else
                head = new list_element(n, head);
        }

        int get_element()
        {
            return cursor->d;
        }

        void advance(){cursor =  cursor->next;}

        void print()
        {
            list_element* h = head;
            innard_print(h); // recursive function
        }

    private:
        list_element* head;
        list_element* cursor;

        void innard_print(list_element *h)
        {
            if(h == 0)
                cout << "###" << endl;
            else
            {
                cout << h->d ;
                h = h->next;
                innard_print(h);
            }
        }
};

int main()
{
    my_list test;
    test.prepend(3);
    test.prepend(7);
    test.print();

    return 0;
}
