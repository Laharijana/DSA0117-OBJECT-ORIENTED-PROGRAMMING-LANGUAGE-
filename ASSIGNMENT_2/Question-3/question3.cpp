
#include <iostream>
using namespace std;

// Function to calculate courier charge
// Default arguments are used for express and insurance
double charge(double weight, bool express = false,
              bool insured = false)
{
    double amount = weight * 50;

    if (express)
    {
        amount += 100;
    }

    if (insured)
    {
        amount += 50;
    }

    return amount;
}

// Overloaded function for weight in grams
double charge(int grams)
{
    double weight = grams / 1000.0;
    return charge(weight);
}

// Parcel class
class Parcel
{
public:
    double weight;
    bool express;
    bool insured;

    Parcel(double w, bool e, bool i)
    {
        weight = w;
        express = e;
        insured = i;
    }
};

// Overloaded function for Parcel object
double charge(Parcel p)
{
    return charge(p.weight, p.express, p.insured);
}

int main()
{
    cout << "===== COURIER CHARGE CALCULATOR =====" << endl;

    // Different function calls
    cout << "Charge for 2 kg: "
         << charge(2.0) << endl;

    cout << "Charge for 2 kg express: "
         << charge(2.0, true) << endl;

    cout << "Charge for 2 kg express with insurance: "
         << charge(2.0, true, true) << endl;

    cout << "Charge for 2000 grams: "
         << charge(2000) << endl;

    cout << "Charge for 2.0f: "
         << charge(2.0f) << endl;

    // Creating Parcel object
    Parcel p(3.0, true, true);

    cout << "Charge for Parcel object: "
         << charge(p) << endl;

    return 0;
}

