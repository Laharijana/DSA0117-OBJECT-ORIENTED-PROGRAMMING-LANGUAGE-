#include <iostream>
#include <string>
using namespace std;

class Staff {
protected:
    string name;
    int id;
    double basic;

public:
    Staff(string n, int i, double b) {
        name = n;
        id = i;
        basic = b;
    }

    virtual double pay() const = 0;

    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Salary: " << pay() << endl;
    }

    virtual ~Staff() {}
};

class Professor : public Staff {
    double research;

public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i, b) {
        research = r;
    }

    double pay() const override {
        return basic + basic * 0.42 + research;
    }
};

class LabAssistant : public Staff {
public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i, b) {}

    double pay() const override {
        return basic + basic * 0.42;
    }
};

class GuestFaculty : public Staff {
    double hours, rate;

public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i, 0) {
        hours = h;
        rate = r;
    }

    double pay() const override {
        return hours * rate;
    }
};

int main() {
    Professor p("Ravi", 101, 50000, 5000);
    LabAssistant l("Kiran", 102, 30000);
    GuestFaculty g("Anu", 103, 20, 1000);

    Staff* staff[] = {&p, &l, &g};

    for (int i = 0; i < 3; i++) {
        staff[i]->display();
        cout << endl;
    }

    return 0;
}
