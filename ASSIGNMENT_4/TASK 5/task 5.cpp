
#include <iostream>
#include <string>
using namespace std;

class Cart {
private:
    int cartId;
    string customerName;
    double total;

public:
    Cart(int id, string name, double amount) {
        cartId = id;
        customerName = name;
        total = amount;
    }

    Cart* addItem(double price) {
        this->total += price;
        return this;
    }

    Cart* applyDiscount(double discount) {
        this->total -= discount;
        return this;
    }

    void display() {
        cout << "Cart ID: " << cartId << endl;
        cout << "Customer: " << customerName << endl;
        cout << "Total: Rs. " << total << endl;
    }

    double getTotal() {
        return total;
    }
};

int main() {
    Cart c1(101, "Ravi", 1000);
    Cart c2(102, "Kavya", 1500);
    Cart c3(103, "Anu", 800);

    cout << "CART DETAILS" << endl;

    c1.addItem(500)->applyDiscount(100);
    c2.addItem(300)->applyDiscount(200);
    c3.addItem(700)->applyDiscount(50);

    cout << "\nCart 1:" << endl;
    c1.display();

    cout << "\nCart 2:" << endl;
    c2.display();

    cout << "\nCart 3:" << endl;
    c3.display();

    Cart* carts[] = {&c1, &c2, &c3};

    Cart* highest = carts[0];

    for (int i = 1; i < 3; i++) {
        if (carts[i]->getTotal() > highest->getTotal()) {
            highest = carts[i];
        }
    }

    cout << "\nHIGHEST CART TOTAL" << endl;
    highest->display();

    return 0;
}

