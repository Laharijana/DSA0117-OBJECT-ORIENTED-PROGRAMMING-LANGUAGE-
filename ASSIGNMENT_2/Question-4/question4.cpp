
#include <iostream>
using namespace std;

class SavingsAccount
{
private:
    int accountNumber;
    double balance;
    double transactions[10];
    int count;

public:
    // Constructor
    SavingsAccount(int accNo, double initialBalance)
    {
        accountNumber = accNo;
        balance = initialBalance;
        count = 0;
    }

    // Deposit function
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            addTransaction(amount);
            cout << "Deposited: " << amount << endl;
        }
        else
        {
            cout << "Invalid deposit amount" << endl;
        }
    }

    // Withdraw function
    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            addTransaction(-amount);
            cout << "Withdrawn: " << amount << endl;
        }
        else
        {
            cout << "Invalid withdrawal" << endl;
        }
    }

    // Store transaction in array
    void addTransaction(double amount)
    {
        if (count < 10)
        {
            transactions[count] = amount;
            count++;
        }
        else
        {
            // Remove oldest transaction
            for (int i = 0; i < 9; i++)
            {
                transactions[i] = transactions[i + 1];
            }

            transactions[9] = amount;
        }
    }

    // Mini statement function
    void miniStatement()
    {
        cout << "\n===== MINI STATEMENT =====" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: " << balance << endl;

        cout << "Last " << count << " Transactions:" << endl;

        for (int i = 0; i < count; i++)
        {
            if (transactions[i] >= 0)
            {
                cout << "Deposit: " << transactions[i] << endl;
            }
            else
            {
                cout << "Withdrawal: " << -transactions[i] << endl;
            }
        }
    }
};

int main()
{
    SavingsAccount account(1001, 5000);

    cout << "===== SAVINGS ACCOUNT =====" << endl;

    account.deposit(1000);
    account.withdraw(500);
    account.deposit(2000);
    account.withdraw(300);
    account.deposit(1500);
    account.withdraw(200);
    account.deposit(700);
    account.withdraw(100);
    account.deposit(800);
    account.withdraw(400);
    account.deposit(1200);

    account.miniStatement();

    return 0;
}

