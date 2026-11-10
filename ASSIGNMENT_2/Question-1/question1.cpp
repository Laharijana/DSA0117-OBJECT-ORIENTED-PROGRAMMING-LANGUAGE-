
#include <iostream>
using namespace std;

// 1. Call by Value
void applyByValue(long long fee, int percent)
{
    fee = fee - (fee * percent / 100);
    cout << "Fee inside call by value: " << fee << endl;
}

// 2. Call by Reference
void applyByReference(long long &fee, int percent)
{
    fee = fee - (fee * percent / 100);
}

// 3. Call by Pointer
void applyByPointer(long long *fee, int percent)
{
    if (fee != 0)
    {
        *fee = *fee - (*fee * percent / 100);
    }
}

// Function to demonstrate call by value, reference and pointer
void change(int a, int &b, int *c)
{
    a += 10;
    b += 10;
    *c += 10;
}

// Return by Reference
int& bigger(int &p, int &q)
{
    return (p > q) ? p : q;
}

// Default Arguments
void show(int x, int y = 5, int z = 10)
{
    cout << x + y + z << " ";
}

// Const Reference
void displayFee(const long long &fee)
{
    cout << "Fee using const reference: " << fee << endl;
}

int main()
{
    cout << "===== HOSTEL FEE CONCESSION =====" << endl;

    long long fee1 = 45000;
    long long fee2 = 45000;
    long long fee3 = 45000;

    // Call by Value
    applyByValue(fee1, 10);
    cout << "Original fee after call by value: " << fee1 << endl;

    // Call by Reference
    applyByReference(fee2, 10);
    cout << "Fee after call by reference: " << fee2 << endl;

    // Call by Pointer
    applyByPointer(&fee3, 10);
    cout << "Fee after call by pointer: " << fee3 << endl;

    // Const Reference
    displayFee(fee2);

    cout << endl;

    cout << "===== PREDICT THE OUTPUT =====" << endl;

    int a = 1, b = 2, c = 3;

    change(a, b, &c);

    cout << a << " " << b << " " << c << endl;

    bigger(a, c) = 100;

    cout << a << " " << c << endl;

    show(1);
    show(1, 2);
    show(1, 2, 3);

    cout << endl << endl;

    cout << "===== COMPLETE THE CODE =====" << endl;

    long long hostelFee = 45000;

    applyByValue(hostelFee, 10);

    cout << "after call by value : "
         << hostelFee << endl;

    applyByReference(hostelFee, 10);

    cout << "after call by reference: "
         << hostelFee << endl;

    return 0;
}

