
#include <iostream>
#include <iomanip>
using namespace std;

class SmartCard
{
private:
    long balance;
    int passZone1;
    int passZone2;

public:
    SmartCard(long amount, int zone1, int zone2)
    {
        balance = amount;
        passZone1 = zone1;
        passZone2 = zone2;
    }

    long calculateFare(int zone, bool peak, bool weekend)
    {
        long fare = 0;

        // Monthly pass check
        if(zone == passZone1 || zone == passZone2)
            return 0;

        // Base fare for four zones
        if(zone == 1)
            fare = 1000;
        else if(zone == 2)
            fare = 2000;
        else if(zone == 3)
            fare = 3000;
        else if(zone == 4)
            fare = 6000;
        else
            return -1;

        // Weekend discount takes priority
        if(weekend)
        {
            fare = fare - (fare * 10 / 100);
        }
        else if(peak)
        {
            fare = fare + (fare * 20 / 100);
        }

        return fare;
    }

    bool makePayment(long fare)
    {
        if(fare >= 0 && balance - fare >= 5000)
        {
            balance = balance - fare;
            return true;
        }

        return false;
    }

    long getBalance()
    {
        return balance;
    }
};

int main()
{
    int zone;
    int pass1, pass2;
    int peakChoice, weekendChoice;

    long initialBalance = 20000;

    cout << "IMPROVED METRO SMART CARD SYSTEM" << endl;
    cout << "================================" << endl;

    cout << "Initial Balance: Rs. 200.00" << endl;

    cout << "\nMONTHLY PASS" << endl;
    cout << "Select first pass zone (1-4): ";
    cin >> pass1;

    cout << "Select second pass zone (1-4): ";
    cin >> pass2;

    if(cin.fail() || pass1 < 1 || pass1 > 4 ||
       pass2 < 1 || pass2 > 4 || pass1 == pass2)
    {
        cout << "Invalid monthly pass zones!" << endl;
        return 0;
    }

    SmartCard card(initialBalance, pass1, pass2);

    cout << "\nEnter travel zone:" << endl;
    cout << "1. Inner - Rs. 10" << endl;
    cout << "2. Middle - Rs. 20" << endl;
    cout << "3. Outer - Rs. 30" << endl;
    cout << "4. Airport - Rs. 60" << endl;

    cout << "Enter zone: ";
    cin >> zone;

    cout << "Is it peak hour? (1-Yes, 0-No): ";
    cin >> peakChoice;

    cout << "Is it weekend? (1-Yes, 0-No): ";
    cin >> weekendChoice;

    if(cin.fail() || zone < 1 || zone > 4 ||
       (peakChoice != 0 && peakChoice != 1) ||
       (weekendChoice != 0 && weekendChoice != 1))
    {
        cout << "Invalid input!" << endl;
        return 0;
    }

    long fare = card.calculateFare(
        zone, peakChoice == 1, weekendChoice == 1
    );

    cout << "\nFARE DETAILS" << endl;
    cout << "------------" << endl;

    if(fare == 0)
        cout << "Monthly Pass Applied!" << endl;
    else
        cout << "Calculated Fare: Rs. "
             << fixed << setprecision(2)
             << fare / 100.0 << endl;

    if(card.makePayment(fare))
        cout << "Journey Status: APPROVED" << endl;
    else
        cout << "Journey Status: DENIED - Low Balance" << endl;

    cout << "Remaining Balance: Rs. "
         << card.getBalance() / 100.0 << endl;

    return 0;
}

