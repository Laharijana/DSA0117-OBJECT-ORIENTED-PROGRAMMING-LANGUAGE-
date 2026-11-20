
#include <iostream>
using namespace std;

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual ~Account() {
        cout << "Account Destructor" << endl;
    }
};

class SeniorAccount : public Account {
private:
    double* history;

public:
    SeniorAccount() {
        history = new double[100];
    }

    double rate() const override {
        return 4.0;
    }

    ~SeniorAccount() {
        delete[] history;
        cout << "SeniorAccount Destructor" << endl;
    }
};

int main() {
    Account* accounts[2];

    accounts[0] = new Account();
    accounts[1] = new SeniorAccount();

    cout << "Interest Rates:" << endl;

    for (int i = 0; i < 2; i++) {
        cout << accounts[i]->rate() << "%" << endl;
    }

    cout << endl << "Destroying Accounts:" << endl;

    delete accounts[0];
    delete accounts[1];

    return 0;
}

