
#include <iostream>
#include <iomanip>
using namespace std;

enum Zone
{
    Inner,
    Middle,
    Outer
};

const long INNER_FARE = 1000;
const long MIDDLE_FARE = 2000;
const long OUTER_FARE = 3000;
const long MIN_BALANCE = 5000;
const int PEAK_PERCENT = 20;

// TODO 1: Calculate fare using switch
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

        default:
            return -1;
    }

    if(peak)
    {
        fare = fare + (fare * PEAK_PERCENT / 100);
    }

    return fare;
}

// TODO 2: Check minimum balance
bool canTravel(long balance, long fare)
{
    if(fare < 0)
        return false;

    return (balance - fare >= MIN_BALANCE);
}

// Check peak hours
bool isPeakHour(int hour, int minute)
{
    int time = hour * 60 + minute;

    if((time >= 480 && time < 600) ||
       (time >= 1020 && time < 1200))
        return true;

    return false;
}

int main()
{
    long balance = 10000;

    Zone zones[3] = {Inner, Outer, Middle};
    bool peak[3] = {false, true, false};

    cout << "METRO SMART CARD SYSTEM" << endl;
    cout << "-----------------------" << endl;

    // Process journeys
    for(int i = 0; i < 3; i++)
    {
        long fare = calculateFare(zones[i], peak[i]);

        if(canTravel(balance, fare))
        {
            balance = balance - fare;

            cout << "Fare Rs. "
                 << fare / 100 << "."
                 << setw(2) << setfill('0')
                 << fare % 100 << setfill(' ');
        }
        else
        {
            cout << "Denied (low balance)";
        }

        cout << " Balance Rs. "
             << balance / 100 << "."
             << setw(2) << setfill('0')
             << balance % 100 << setfill(' ')
             << endl;
    }

    cout << "\nPEAK HOUR BOUNDARY CHECK" << endl;

    cout << "10:00 AM: "
         << (isPeakHour(10, 0) ? "Peak" : "Off-Peak")
         << endl;

    cout << "8:00 PM: "
         << (isPeakHour(20, 0) ? "Peak" : "Off-Peak")
         << endl;

    return 0;
}

