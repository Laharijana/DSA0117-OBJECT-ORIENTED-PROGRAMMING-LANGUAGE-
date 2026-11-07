
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "METRO SMART CARD - TYPE CONVERSION" << endl;
    cout << "----------------------------------" << endl;

    // 1. Implicit conversion
    cout << "\n1. IMPLICIT CONVERSION" << endl;

    int farePaise = 3000;
    double fare = farePaise;

    cout << "Integer fare in paise: " << farePaise << endl;
    cout << "Converted double value: " << fare << endl;

    // 2. Integer division
    cout << "\n2. INTEGER DIVISION" << endl;

    int a = 5;
    int b = 2;

    cout << "5 / 2 = " << a / b << endl;
    cout << "5.0 / 2 = " << 5.0 / 2 << endl;

    // 3. Signed and unsigned comparison
    cout << "\n3. SIGNED AND UNSIGNED" << endl;

    int signedValue = -1;
    unsigned int unsignedValue = 1;

    cout << "Signed value: " << signedValue << endl;
    cout << "Unsigned value: " << unsignedValue << endl;

    if (signedValue < unsignedValue)
        cout << "Signed value is smaller." << endl;
    else
        cout << "Signed value is NOT smaller." << endl;

    // 4. Narrowing conversion
    cout << "\n4. NARROWING CONVERSION" << endl;

    double decimalValue = 36.75;
    int narrowedValue = static_cast<int>(decimalValue);

    cout << "Original decimal value: " << decimalValue << endl;
    cout << "After conversion to int: " << narrowedValue << endl;

    // 5. Explicit conversion using static_cast
    cout << "\n5. STATIC CAST" << endl;

    int totalPaise = 3600;
    double rupees = static_cast<double>(totalPaise) / 100;

    cout << fixed << setprecision(2);
    cout << "Total fare in paise: " << totalPaise << endl;
    cout << "Total fare in rupees: Rs. " << rupees << endl;

    cout << "\nConclusion: Use explicit conversion carefully." << endl;

    return 0;
}

