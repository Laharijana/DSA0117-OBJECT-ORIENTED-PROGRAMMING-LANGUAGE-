
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    int vehicleId;
    string brand;
    double rentPerDay;
    bool rented;

public:
    Vehicle(int id, string b, double rent) {
        vehicleId = id;
        brand = b;
        rentPerDay = rent;
        rented = false;
    }

    virtual double calculateCharge(int days) = 0;

    virtual void display() {
        cout << "Vehicle ID: " << vehicleId << endl;
        cout << "Brand: " << brand << endl;
        cout << "Rent per day: Rs. " << rentPerDay << endl;
        cout << "Status: " << (rented ? "Rented" : "Available") << endl;
    }

    void rentVehicle() {
        if (!rented) {
            rented = true;
            cout << "Vehicle rented successfully!" << endl;
        } else {
            cout << "Vehicle is already rented." << endl;
        }
    }

    void returnVehicle() {
        rented = false;
        cout << "Vehicle returned successfully!" << endl;
    }

    virtual ~Vehicle() {}
};

class Bicycle : public Vehicle {
public:
    Bicycle(int id, string b, double rent)
        : Vehicle(id, b, rent) {}

    double calculateCharge(int days) {
        return rentPerDay * days;
    }

    void display() {
        cout << "\nBICYCLE DETAILS" << endl;
        Vehicle::display();
    }
};

class TwoWheeler : public Vehicle {
public:
    TwoWheeler(int id, string b, double rent)
        : Vehicle(id, b, rent) {}

    double calculateCharge(int days) {
        return rentPerDay * days;
    }

    void display() {
        cout << "\nTWO-WHEELER DETAILS" << endl;
        Vehicle::display();
    }
};

class Car : public Vehicle {
public:
    Car(int id, string b, double rent)
        : Vehicle(id, b, rent) {}

    double calculateCharge(int days) {
        return rentPerDay * days;
    }

    void display() {
        cout << "\nCAR DETAILS" << endl;
        Vehicle::display();
    }
};

class ElectricCar : public Car {
public:
    ElectricCar(int id, string b, double rent)
        : Car(id, b, rent) {}

    double calculateCharge(int days) {
        return (rentPerDay * days) + 200;
    }

    void display() {
        cout << "\nELECTRIC CAR DETAILS" << endl;
        Vehicle::display();
    }
};

class ElectricBus : public Vehicle {
public:
    ElectricBus(int id, string b, double rent)
        : Vehicle(id, b, rent) {}

    double calculateCharge(int days) {
        return (rentPerDay * days) + 500;
    }

    void display() {
        cout << "\nELECTRIC BUS DETAILS" << endl;
        Vehicle::display();
    }
};

int main() {
    Bicycle bicycle(101, "Hero", 100);
    TwoWheeler bike(102, "Honda", 300);
    Car car(103, "Hyundai", 1000);
    ElectricCar electricCar(104, "Tata", 1500);
    ElectricBus bus(105, "Electric Bus", 3000);

    Vehicle* vehicles[] = {
        &bicycle, &bike, &car, &electricCar, &bus
    };

    int days = 3;

    for (int i = 0; i < 5; i++) {
        vehicles[i]->display();

        vehicles[i]->rentVehicle();

        cout << "Rental charge for " << days
             << " days: Rs. "
             << vehicles[i]->calculateCharge(days)
             << endl;

        vehicles[i]->returnVehicle();
    }

    return 0;
}

