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
        my_list(const int* arr, int n) //: head(0), cursor(0)
        {
            head = 0;
            for(int i = n - 1; i > -1; --i)
                head = new list_element(arr[i],head);
            cursor = head;
        };

        ~my_list()
        {
            cout << "We destruct everything.";
            for(cursor = head; cursor != 0;)
            {
                cursor = head -> next;
                delete head;
                head = cursor;
            } // check memory leaks from valgrind
        }; // destructor

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
    int data[5] = {1,2,3};
    my_list test(data,5);
    test.print();
    test.prepend(3);
    test.prepend(7);

    return 0;
}
