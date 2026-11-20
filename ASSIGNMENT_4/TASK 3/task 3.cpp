class Address {
    string city;
    int pin;

public:
    Address(string c, int p) {
        city = c;
        pin = p;
        cout << "Address Constructor" << endl;
    }

    string getAddress() {
        stringstream ss;
        ss << city << "-" << pin;
        return ss.str();
    }

    ~Address() {
        cout << "Address Destructor" << endl;
    }
};
