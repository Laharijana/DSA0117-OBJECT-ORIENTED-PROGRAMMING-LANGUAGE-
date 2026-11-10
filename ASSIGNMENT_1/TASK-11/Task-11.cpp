
#include <iostream>
using namespace std;

class SmartCard
{
private:
    long balance;

public:
    SmartCard(long amount)
    {
        balance = amount;
    }

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
    SmartCard card(10000);

    int zone = 3;
    bool peak = true;

    cout << "METRO SMART CARD - FINAL DESIGN" << endl;
    cout << "================================" << endl;

    cout << "Initial Balance: Rs. "
         << card.getBalance() / 100 << endl;

    long fare = card.calculateFare(zone, peak);

    if(fare >= 0)
    {
        cout << "Calculated Fare: Rs. "
             << fare / 100 << endl;

        if(card.makePayment(fare))
            cout << "Journey Status: APPROVED" << endl;
        else
            cout << "Journey Status: DENIED" << endl;
    }
    else
    {
        cout << "Invalid Zone!" << endl;
    }

    cout << "Remaining Balance: Rs. "
         << card.getBalance() / 100 << endl;

    cout << "\nDesign Features:" << endl;
    cout << "1. Private card balance" << endl;
    cout << "2. Fare calculation using a class" << endl;
    cout << "3. Minimum Rs. 50 balance protection" << endl;
    cout << "4. Integer paise calculation" << endl;

    return 0;
}

