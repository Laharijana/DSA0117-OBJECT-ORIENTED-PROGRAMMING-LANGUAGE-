
#include <iostream>
#include <iomanip>
using namespace std;

long calculateFare(int zone, bool peak)
{
    long fare = 0;

    if(zone == 1)
        fare = 1000;
    else if(zone == 2)
        fare = 2000;
    else if(zone == 3)
        fare = 3000;
    else
        return -1;

    if(peak)
        fare = fare + (fare * 20 / 100);

    return fare;
}

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
    int zone, hour, minute;
    long balance, fare;

    cout << "METRO SMART CARD FARE SYSTEM" << endl;
    cout << "============================" << endl;

    cout << "Enter card balance in rupees: ";
    cin >> balance;

    if(cin.fail() || balance < 0)
    {
        cout << "Invalid balance input!" << endl;
        return 0;
    }

    balance = balance * 100;

    cout << "Enter zone (1-Inner, 2-Middle, 3-Outer): ";
    cin >> zone;

    if(cin.fail())
    {
        cout << "Invalid zone input!" << endl;
        return 0;
    }

    cout << "Enter hour (0-23): ";
    cin >> hour;

    if(cin.fail())
    {
        cout << "Invalid hour input!" << endl;
        return 0;
    }

    cout << "Enter minute (0-59): ";
    cin >> minute;

    if(cin.fail())
    {
        cout << "Invalid minute input!" << endl;
        return 0;
    }

    if(hour < 0 || hour > 23 || minute < 0 || minute > 59)
    {
        cout << "Invalid time!" << endl;
        return 0;
    }

    fare = calculateFare(zone, isPeakHour(hour, minute));

    if(fare < 0)
    {
        cout << "Invalid zone!" << endl;
        return 0;
    }

    cout << "\nBase fare and peak calculation completed." << endl;

    cout << "Calculated Fare: Rs. "
         << fixed << setprecision(2) << fare / 100.0 << endl;

    cout << "Available Balance: Rs. "
         << balance / 100.0 << endl;

    if(balance - fare >= 5000)
    {
        balance = balance - fare;

        cout << "Journey Status: APPROVED" << endl;
    }
    else
    {
        cout << "Journey Status: DENIED - Minimum balance rule" << endl;
    }

    cout << "Remaining Balance: Rs. "
         << balance / 100.0 << endl;

    return 0;
}

