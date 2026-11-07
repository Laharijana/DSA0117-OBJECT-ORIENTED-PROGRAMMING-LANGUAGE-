#include <iostream>
using namespace std;

// Fare constants stored in paise
const int INNER_FARE = 1000;
const int MIDDLE_FARE = 2000;
const int OUTER_FARE = 3000;

const int PEAK_SURCHARGE_PERCENT = 20;
const long MIN_BALANCE = 5000;

// Normal enum for older Dev-C++ compilers
enum Zone
{
    Inner,
    Middle,
    Outer
};

// Function to calculate fare
long calculateFare(Zone zone, bool peak)
{
    long fare = 0;

    switch(zone)
    {
        case Inner:
            fare = INNER_FARE;
            break;

        case Middle:
            fare = MIDDLE_FARE;
            break;

        case Outer:
            fare = OUTER_FARE;
            break;
    }

    if(peak)
    {
        fare = fare + (fare * PEAK_SURCHARGE_PERCENT / 100);
    }

    return fare;
}

int main()
{
    cout << "METRO SMART CARD FARE SYSTEM" << endl;
    cout << "----------------------------" << endl;

    cout << "Inner Zone Fare: Rs. " << INNER_FARE / 100 << ".00" << endl;
    cout << "Middle Zone Fare: Rs. " << MIDDLE_FARE / 100 << ".00" << endl;
    cout << "Outer Zone Fare: Rs. " << OUTER_FARE / 100 << ".00" << endl;

    cout << "Peak Surcharge: "
         << PEAK_SURCHARGE_PERCENT << "%" << endl;

    cout << "Minimum Balance: Rs. "
         << MIN_BALANCE / 100 << ".00" << endl;

    long fare = calculateFare(Outer, true);

    cout << "----------------------------" << endl;

    cout << "Outer Zone Peak Fare: Rs. "
         << fare / 100 << "."
         << (fare % 100 < 10 ? "0" : "")
         << fare % 100 << endl;

    return 0;
}
