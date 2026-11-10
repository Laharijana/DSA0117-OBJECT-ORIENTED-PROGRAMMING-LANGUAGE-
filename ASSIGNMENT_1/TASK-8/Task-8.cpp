
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main()
{
    int zone;
    int hour;
    int minute;

    long balance = 10000;
    long fare = 0;

    cout << "METRO SMART CARD SYSTEM" << endl;
    cout << "=======================" << endl;

    // Safe zone input
    cout << "\nEnter Zone (1-Inner, 2-Middle, 3-Outer): ";
    cin >> zone;

    if(cin.fail())
    {
        cout << "Invalid input! Please enter a number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }

    if(zone == 1)
        fare = 1000;
    else if(zone == 2)
        fare = 2000;
    else if(zone == 3)
        fare = 3000;
    else
    {
        cout << "Invalid zone!" << endl;
        return 0;
    }

    // Safe time input
    cout << "Enter hour (0-23): ";
    cin >> hour;

    if(cin.fail())
    {
        cout << "Invalid hour input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }

    cout << "Enter minute (0-59): ";
    cin >> minute;

    if(cin.fail())
    {
        cout << "Invalid minute input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }

    if(hour < 0 || hour > 23 || minute < 0 || minute > 59)
    {
        cout << "Invalid time!" << endl;
        return 0;
    }

    // Check peak hour
    int totalMinutes = hour * 60 + minute;

    bool peak = ((totalMinutes >= 480 && totalMinutes < 600) ||
                 (totalMinutes >= 1020 && totalMinutes < 1200));

    if(peak)
        fare = fare + (fare * 20 / 100);

    // Check minimum balance
    cout << "\nCard Balance: Rs. "
         << fixed << setprecision(2) << balance / 100.0 << endl;

    cout << "Calculated Fare: Rs. "
         << fare / 100.0 << endl;

    if(balance - fare >= 5000)
    {
        balance = balance - fare;

        cout << "Journey Status: APPROVED" << endl;
    }
    else
    {
        cout << "Journey Status: DENIED - Low Balance" << endl;
    }

    cout << "Remaining Balance: Rs. "
         << balance / 100.0 << endl;

    return 0;
}

