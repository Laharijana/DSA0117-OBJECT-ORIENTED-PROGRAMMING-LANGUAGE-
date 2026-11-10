
#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    long baseFare = 3000;
    int surchargePercent = 20;

    // Integer paise calculation
    long surchargePaise =
        baseFare * surchargePercent / 100;

    long totalPaise = baseFare + surchargePaise;

    // Double calculation
    double baseRupees = 30.00;
    double surchargeRupees =
        baseRupees * surchargePercent / 100.0;

    double totalRupees =
        baseRupees + surchargeRupees;

    cout << "METRO SMART CARD - RESULT ANALYSIS" << endl;
    cout << "==================================" << endl;

    cout << "\n1. INTEGER PAISE CALCULATION" << endl;

    cout << "Base Fare: " << baseFare << " paise" << endl;
    cout << "Surcharge: " << surchargePaise << " paise" << endl;
    cout << "Total Fare: " << totalPaise << " paise" << endl;

    cout << "\n2. DOUBLE CALCULATION" << endl;

    cout << fixed << setprecision(2);

    cout << "Base Fare: Rs. " << baseRupees << endl;
    cout << "Surcharge: Rs. " << surchargeRupees << endl;
    cout << "Total Fare: Rs. " << totalRupees << endl;

    cout << "\n3. EXPECTED VS ACTUAL RESULT" << endl;

    cout << "Expected Fare: Rs. 36.00" << endl;
    cout << "Integer Result: Rs. "
         << totalPaise / 100.0 << endl;

    cout << "Double Result: Rs. "
         << totalRupees << endl;

    if(totalPaise == 3600 && totalRupees == 36.0)
        cout << "Result: Both calculations match." << endl;
    else
        cout << "Result: Difference found." << endl;

    cout << "\n4. INTEGER LIMIT CHECK" << endl;

    cout << "Maximum int value: " << INT_MAX << endl;
    cout << "Minimum int value: " << INT_MIN << endl;

    cout << "\n5. CONCLUSION" << endl;

    cout << "Integer paise is preferred for money." << endl;
    cout << "It avoids floating-point rounding errors." << endl;
    cout << "Use long long for large accumulated totals." << endl;

    return 0;
}

