
#include <iostream>
using namespace std;

// Function to check peak hours
bool isPeakHour(int hour, int minute)
{
    int time = hour * 60 + minute;

    return ((time >= 8 * 60 && time < 10 * 60) ||
            (time >= 17 * 60 && time < 20 * 60));
}

int main()
{
    cout << "METRO SMART CARD - OPERATORS AND EXPRESSIONS" << endl;
    cout << "--------------------------------------------" << endl;

    // 1. Operator precedence
    cout << "\n1. OPERATOR PRECEDENCE" << endl;

    cout << "10 + 5 * 2 = " << 10 + 5 * 2 << endl;
    cout << "(10 + 5) * 2 = " << (10 + 5) * 2 << endl;

    // 2. Increment operators
    cout << "\n2. INCREMENT OPERATORS" << endl;

    int x = 5;
    int y = x++;

    cout << "Post-increment value: " << y << endl;
    cout << "Value of x after post-increment: " << x << endl;

    int z = ++x;

    cout << "Pre-increment value: " << z << endl;
    cout << "Final value of x: " << x << endl;

    // 3. Negative division and modulus
    cout << "\n3. NEGATIVE DIVISION AND MODULUS" << endl;

    cout << "-7 / 3 = " << -7 / 3 << endl;
    cout << "-7 % 3 = " << -7 % 3 << endl;
    cout << "7 / -3 = " << 7 / -3 << endl;
    cout << "7 % -3 = " << 7 % -3 << endl;

    // 4. Peak hour checking
    cout << "\n4. PEAK HOUR CHECKING" << endl;

    cout << "08:00 - "
         << (isPeakHour(8, 0) ? "Peak Hour" : "Off-Peak") << endl;

    cout << "10:00 - "
         << (isPeakHour(10, 0) ? "Peak Hour" : "Off-Peak") << endl;

    cout << "17:00 - "
         << (isPeakHour(17, 0) ? "Peak Hour" : "Off-Peak") << endl;

    cout << "20:00 - "
         << (isPeakHour(20, 0) ? "Peak Hour" : "Off-Peak") << endl;

    // 5. Metro fare calculation
    cout << "\n5. METRO FARE CALCULATION" << endl;

    int fare = 3000;
    int surcharge = fare * 20 / 100;
    int totalFare = fare + surcharge;

    cout << "Base Fare: " << fare << " paise" << endl;
    cout << "Peak Surcharge: " << surcharge << " paise" << endl;
    cout << "Total Fare: " << totalFare << " paise" << endl;

    cout << "\nConclusion: Operators work correctly." << endl;

    return 0;
}

