
#include <iostream>
#include <string>
using namespace std;

// Zone details
enum Zone {
    Inner,
    Middle,
    Outer
};

// SmartCard class
class SmartCard {
private:
    long long balance;

public:
    SmartCard(long long amount) {
        balance = amount;
    }

    bool canTravel(long long fare) {
        return balance - fare >= 5000;
    }

    void deduct(long long fare) {
        if (canTravel(fare)) {
            balance = balance - fare;
            cout << "Journey Allowed" << endl;
        }
        else {
            cout << "Journey Denied" << endl;
        }
    }

    long long getBalance() {
        return balance;
    }
};

// Passenger class
class Passenger {
public:
    string name;

    Passenger(string n) {
        name = n;
    }
};

// FareTable class
class FareTable {
public:
    static long long calculateFare(Zone z, bool peak) {
        long long fare = 0;

        switch (z) {
            case Inner:
                fare = 1000;
                break;

            case Middle:
                fare = 2000;
                break;

            case Outer:
                fare = 3000;
                break;
        }

        if (peak) {
            fare = fare + fare * 20 / 100;
        }

        return fare;
    }
};

// Journey class
class Journey {
public:
    Zone destination;
    bool peak;

    Journey(Zone z, bool p) {
        destination = z;
        peak = p;
    }
};

int main() {

    Passenger p("Student");
    SmartCard card(10000);

    Journey trip(Outer, true);

    long long fare = FareTable::calculateFare(
        trip.destination, trip.peak
    );

    cout << "Metro Smart Card System" << endl;
    cout << "Passenger: " << p.name << endl;
    cout << "Initial Balance: Rs. 100.00" << endl;

    cout << "Journey Fare: Rs. "
         << fare / 100 << ".";

    if (fare % 100 < 10)
        cout << "0";

    cout << fare % 100 << endl;

    card.deduct(fare);

    cout << "Remaining Balance: Rs. "
         << card.getBalance() / 100 << "."
         << card.getBalance() % 100 << endl;

    return 0;
}


