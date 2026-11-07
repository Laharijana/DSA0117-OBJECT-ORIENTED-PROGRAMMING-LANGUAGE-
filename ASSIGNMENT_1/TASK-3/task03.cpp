
#include <iostream>
#include <iomanip>
#include <climits>
#include <cfloat>
using namespace std;

int main()
{
    cout << "METRO SMART CARD - DATA TYPES ANALYSIS" << endl;
    cout << "--------------------------------------" << endl;

    // Display memory size of data types
    cout << "\n1. DATA TYPE SIZES" << endl;

    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of short: " << sizeof(short) << " bytes" << endl;
    cout << "Size of long: " << sizeof(long) << " bytes" << endl;
    cout << "Size of long long: " << sizeof(long long) << " bytes" << endl;
    cout << "Size of float: " << sizeof(float) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " byte" << endl;
    cout << "Size of bool: " << sizeof(bool) << " byte" << endl;

    // Display integer limits
    cout << "\n2. INTEGER RANGE" << endl;
    cout << "Minimum int: " << INT_MIN << endl;
    cout << "Maximum int: " << INT_MAX << endl;

    // Display floating point limits
    cout << "\n3. FLOATING POINT RANGE" << endl;
    cout << "Float maximum: " << FLT_MAX << endl;
    cout << "Double maximum: " << DBL_MAX << endl;

    // Integer paise calculation
    cout << "\n4. INTEGER PAISE CALCULATION" << endl;

    int farePaise = 3000;
    int surchargePaise = farePaise * 20 / 100;
    int totalPaise = farePaise + surchargePaise;

    cout << "Base fare: Rs. " << farePaise / 100 << ".00" << endl;
    cout << "Peak surcharge: Rs. "
         << surchargePaise / 100 << ".00" << endl;

    cout << "Total fare: Rs. "
         << totalPaise / 100 << ".00" << endl;

    // Double calculation comparison
    cout << "\n5. DOUBLE CALCULATION" << endl;

    double fare = 30.00;
    double totalFare = fare + (fare * 20.0 / 100.0);

    cout << fixed << setprecision(2);
    cout << "Base fare: Rs. " << fare << endl;
    cout << "Total fare: Rs. " << totalFare << endl;

    // Conclusion
    cout << "\n6. CONCLUSION" << endl;
    cout << "Integer paise is preferred for fare calculations." << endl;
    cout << "It avoids floating-point rounding errors." << endl;

    return 0;
}

