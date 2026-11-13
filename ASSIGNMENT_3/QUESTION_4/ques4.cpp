
#include <iostream>
#include <iomanip>
using namespace std;

class Money
{
private:
    long long paise;

public:
    Money(long long p = 0)
    {
        paise = p;
    }

    // Addition operator
    Money operator+(const Money &m) const
    {
        return Money(paise + m.paise);
    }

    // Subtraction operator
    Money operator-(const Money &m) const
    {
        return Money(paise - m.paise);
    }

    // Addition assignment operator
    Money &operator+=(const Money &m)
    {
        paise += m.paise;
        return *this;
    }

    // Equality operator
    bool operator==(const Money &m) const
    {
        return paise == m.paise;
    }

    // Less than operator
    bool operator<(const Money &m) const
    {
        return paise < m.paise;
    }

    // Output stream operator
    friend ostream &operator<<(ostream &out, const Money &m)
    {
        out << "Rs " << fixed << setprecision(2)
            << (double)m.paise / 100;
        return out;
    }

    // Input stream operator
    friend istream &operator>>(istream &in, Money &m)
    {
        double amount;
        in >> amount;
        m.paise = (long long)(amount * 100 + 0.5);
        return in;
    }
};

int main()
{
    Money m1(15000);
    Money m2(5000);

    Money total = m1 + m2;
    Money difference = m1 - m2;

    cout << "First Amount: " << m1 << endl;
    cout << "Second Amount: " << m2 << endl;

    cout << "Total Amount: " << total << endl;
    cout << "Difference: " << difference << endl;

    m1 += m2;

    cout << "After += : " << m1 << endl;

    cout << "Are amounts equal? "
         << (m1 == m2 ? "true" : "false") << endl;

    cout << "Is first amount less? "
         << (m1 < m2 ? "true" : "false") << endl;

    Money m3;

    cout << "Enter an amount: ";
    cin >> m3;

    cout << "Entered Amount: " << m3 << endl;

    return 0;
}

