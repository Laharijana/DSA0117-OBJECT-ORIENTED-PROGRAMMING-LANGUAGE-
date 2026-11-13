
#include <iostream>
#include <cmath>
using namespace std;

class Complex
{
private:
    double real;
    double imag;

public:
    // Default constructor
    Complex()
    {
        real = 0;
        imag = 0;
    }

    // Constructor with real value
    Complex(double r)
    {
        real = r;
        imag = 0;
    }

    // Constructor with real and imaginary values
    Complex(double r, double i)
    {
        real = r;
        imag = i;
    }

    // Addition operator
    Complex operator+(const Complex &c) const
    {
        return Complex(real + c.real, imag + c.imag);
    }

    // Subtraction operator
    Complex operator-(const Complex &c) const
    {
        return Complex(real - c.real, imag - c.imag);
    }

    // Multiplication operator
    Complex operator*(const Complex &c) const
    {
        double r = real * c.real - imag * c.imag;
        double i = real * c.imag + imag * c.real;

        return Complex(r, i);
    }

    // Division operator
    Complex operator/(const Complex &c) const
    {
        double denominator =
            c.real * c.real + c.imag * c.imag;

        if (denominator == 0)
        {
            cout << "Error: Division by zero is not possible"
                 << endl;
            return Complex();
        }

        double r =
            (real * c.real + imag * c.imag) / denominator;

        double i =
            (imag * c.real - real * c.imag) / denominator;

        return Complex(r, i);
    }

    // Equality operator
    bool operator==(const Complex &c) const
    {
        return real == c.real && imag == c.imag;
    }

    // Magnitude calculation
    double magnitude() const
    {
        return sqrt(real * real + imag * imag);
    }

    // Output stream operator
    friend ostream &operator<<(ostream &out, const Complex &c)
    {
        out << c.real;

        if (c.imag >= 0)
            out << " + " << c.imag << "i";
        else
            out << " - " << -c.imag << "i";

        return out;
    }
};

int main()
{
    Complex z1(4, 3);
    Complex z2(2, 1);

    cout << "First Complex Number: " << z1 << endl;
    cout << "Second Complex Number: " << z2 << endl;

    // Arithmetic operations
    cout << "\nAddition: " << z1 + z2 << endl;

    cout << "Subtraction: " << z1 - z2 << endl;

    cout << "Multiplication: " << z1 * z2 << endl;

    cout << "Division: " << z1 / z2 << endl;

    // Equality comparison
    if (z1 == z2)
        cout << "Both numbers are equal" << endl;
    else
        cout << "Both numbers are not equal" << endl;

    // Magnitude
    cout << "\nMagnitude of first number: "
         << z1.magnitude() << endl;

    // AC circuit impedance
    Complex Z1(4, 3);
    Complex Z2(2, 1);

    // Series impedance: Z = Z1 + Z2
    Complex series = Z1 + Z2;

    cout << "\nSeries Impedance: " << series << endl;

    // Parallel impedance: Z = (Z1 * Z2) / (Z1 + Z2)
    Complex parallel = (Z1 * Z2) / (Z1 + Z2);

    cout << "Parallel Impedance: " << parallel << endl;

    // Division by zero test
    Complex zero(0, 0);

    cout << "\nDivision by Zero Test: "
         << z1 / zero << endl;

    return 0;
}

