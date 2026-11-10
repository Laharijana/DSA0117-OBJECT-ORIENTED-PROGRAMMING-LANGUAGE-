
#include <iostream>
using namespace std;

// PROCEDURAL PROGRAMMING

long proceduralBalance = 10000;

long calculateProceduralFare(int zone, bool peak)
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

bool proceduralTravel(long fare)
{
    if(fare < 0)
        return false;

    if(proceduralBalance - fare >= 5000)
    {
        proceduralBalance = proceduralBalance - fare;
        return true;
    }

    return false;
}

// OBJECT-ORIENTED PROGRAMMING

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

    bool canTravel(long fare)
    {
        return (fare >= 0 && balance - fare >= 5000);
    }

    void deductFare(long fare)
    {
        if(canTravel(fare))
            balance = balance - fare;
    }

    long getBalance()
    {
        return balance;
    }
};

int main()
{
    int zones[3] = {1, 3, 2};
    bool peak[3] = {false, true, false};

    cout << "METRO SMART CARD SYSTEM" << endl;
    cout << "=======================" << endl;

    // Procedural method
    cout << "\nPROCEDURAL PROGRAMMING" << endl;

    for(int i = 0; i < 3; i++)
    {
        long fare = calculateProceduralFare(zones[i], peak[i]);

        if(proceduralTravel(fare))
            cout << "Journey " << i + 1 << ": Approved";
        else
            cout << "Journey " << i + 1 << ": Denied";

        cout << " | Balance: Rs. "
             << proceduralBalance / 100 << endl;
    }

    // OOP method
    cout << "\nOBJECT-ORIENTED PROGRAMMING" << endl;

    SmartCard card(10000);

    for(int i = 0; i < 3; i++)
    {
        long fare = card.calculateFare(zones[i], peak[i]);

        if(card.canTravel(fare))
        {
            card.deductFare(fare);
            cout << "Journey " << i + 1 << ": Approved";
        }
        else
        {
            cout << "Journey " << i + 1 << ": Denied";
        }

        cout << " | Balance: Rs. "
             << card.getBalance() / 100 << endl;
    }

    return 0;
}

