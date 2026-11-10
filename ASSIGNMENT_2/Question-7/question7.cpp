
#include <iostream>
using namespace std;

class SavingsAccount
{
private:
    int accountNumber;
    double balance;

    static const int SIZE = 50;

    double transactions[SIZE];

    int count;
    int nextIndex;

public:

    // Constructor
    SavingsAccount(int accNo, double initialBalance)
    {
        accountNumber = accNo;
        balance = initialBalance;
        count = 0;
        nextIndex = 0;
    }

    // Add transaction using circular buffer
    void addTransaction(double amount)
    {
        transactions[nextIndex] = amount;

        nextIndex = (nextIndex + 1) % SIZE;

        if (count < SIZE)
        {
            count++;
        }
    }

    // Deposit function
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            addTransaction(amount);
        }
    }

    // Withdraw function
    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            addTransaction(-amount);
        }
    }

    // Display mini statement
    void miniStatement()
    {
        cout << "\n===== REDESIGNED MINI STATEMENT =====" << endl;

        cout << "Account Number: "
             << accountNumber << endl;

        cout << "Current Balance: "
             << balance << endl;

        cout << "Transactions Stored: "
             << count << endl;

        cout << "Latest Transactions:" << endl;

        int startIndex;

        if (count == SIZE)
        {
            startIndex = nextIndex;
        }
        else
        {
            startIndex = 0;
        }

        for (int i = 0; i < count; i++)
        {
            int index = (startIndex + i) % SIZE;

            if (transactions[index] >= 0)
            {
                cout << "Deposit: "
                     << transactions[index] << endl;
            }
            else
            {
                cout << "Withdrawal: "
                     << -transactions[index] << endl;
            }
        }
    }
};

int main()
{
    cout << "===== SAVINGS ACCOUNT REDESIGN =====" << endl;

    SavingsAccount account(1001, 5000);

    // Add 52 transactions
    for (int i = 1; i <= 52; i++)
    {
        account.deposit(i);
    }

    account.miniStatement();

    return 0;
}

