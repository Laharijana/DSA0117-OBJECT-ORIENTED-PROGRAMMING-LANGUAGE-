
#include <iostream>
#include <string>
using namespace std;

class BusTicket
{
private:
    static int issued;
    static const int CAPACITY = 3;

    int seat;
    string name;

public:
    // Constructor
    BusTicket(const string &n)
    {
        name = n;

        if (issued < CAPACITY)
        {
            issued++;
            seat = issued;
        }
        else
        {
            seat = 0;
        }
    }

    // Static member function
    static int count()
    {
        return issued;
    }

    // Display ticket details
    void print() const
    {
        cout << name << ": ";

        if (seat != 0)
        {
            cout << "Seat " << seat;
        }
        else
        {
            cout << "Waiting";
        }

        cout << endl;
    }
};

// Definition of static data member
int BusTicket::issued = 0;

int main()
{
    cout << "===== COLLEGE BUS TICKET SYSTEM =====" << endl;

    // Array of objects
    BusTicket trip[4] =
    {
        BusTicket("Asha"),
        BusTicket("Bala"),
        BusTicket("Chitra"),
        BusTicket("Dev")
    };

    // Display all tickets
    for (int i = 0; i < 4; i++)
    {
        trip[i].print();
    }

    cout << "Issued: " << BusTicket::count() << endl;

    return 0;
}

