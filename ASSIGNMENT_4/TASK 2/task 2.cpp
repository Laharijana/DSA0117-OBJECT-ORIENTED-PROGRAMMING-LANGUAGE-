#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int id;
    string phone;

public:
    Person(string n, int i, string p) {
        name = n;
        id = i;
        phone = p;
    }

    void displayPerson() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Phone: " << phone << endl;
    }
};

class Student : virtual public Person {
protected:
    string programme;
    float cgpa;

public:
    Student(string n, int i, string p, string prog, float c)
        : Person(n, i, p) {
        programme = prog;
        cgpa = c;
    }

    void displayStudent() {
        cout << "Programme: " << programme << endl;
        cout << "CGPA: " << cgpa << endl;
    }
};

class Staff : virtual public Person {
protected:
    string department;
    double salary;

public:
    Staff(string n, int i, string p, string d, double s)
        : Person(n, i, p) {
        department = d;
        salary = s;
    }

    void displayStaff() {
        cout << "Department: " << department << endl;
        cout << "Salary: " << salary << endl;
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int i, string p, string prog,
                      float c, string d, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, d, s) {}

    void display() {
        displayPerson();
        displayStudent();
        displayStaff();
    }
};

class ResearchScholar : public Student {
private:
    double fellowship;

public:
    ResearchScholar(string n, int i, string p, string prog,
                    float c, double f)
        : Person(n, i, p),
          Student(n, i, p, prog, c) {
        fellowship = f;
    }

    void display() {
        displayPerson();
        displayStudent();
        cout << "Fellowship: " << fellowship << endl;
    }
};

int main() {
    cout << "TEACHING ASSISTANT DETAILS" << endl;

    TeachingAssistant ta("Ravi", 101, "9876543210",
                         "AI&DS", 8.5, "CSE", 30000);

    ta.display();

    cout << "\nRESEARCH SCHOLAR DETAILS" << endl;

    ResearchScholar rs("Kavya", 102, "9876501234",
                       "AI&DS", 9.0, 15000);

    rs.display();

    return 0;
}
