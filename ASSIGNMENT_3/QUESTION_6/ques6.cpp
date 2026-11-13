
#include <iostream>
#include <cstring>
using namespace std;

class Text
{
private:
    char *data;

public:
    // Parameterized constructor
    Text(const char *str = "")
    {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Copy constructor
    Text(const Text &other)
    {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Copy assignment operator
    Text &operator=(const Text &other)
    {
        if (this != &other)
        {
            char *newData = new char[strlen(other.data) + 1];
            strcpy(newData, other.data);

            delete[] data;
            data = newData;
        }

        return *this;
    }

    // Addition operator
    Text operator+(const Text &other) const
    {
        int length = strlen(data) + strlen(other.data);

        char *temp = new char[length + 1];

        strcpy(temp, data);
        strcat(temp, other.data);

        Text result(temp);

        delete[] temp;

        return result;
    }

    // Equality operator
    bool operator==(const Text &other) const
    {
        return strcmp(data, other.data) == 0;
    }

    // Inequality operator
    bool operator!=(const Text &other) const
    {
        return !(*this == other);
    }

    // Output stream operator
    friend ostream &operator<<(ostream &out, const Text &t)
    {
        out << t.data;
        return out;
    }

    // Destructor
    ~Text()
    {
        delete[] data;
    }
};

int main()
{
    Text t1("Hello ");
    Text t2("World");

    cout << "First Text: " << t1 << endl;
    cout << "Second Text: " << t2 << endl;

    // Addition
    Text t3 = t1 + t2;

    cout << "Combined Text: " << t3 << endl;

    // Copy constructor
    Text t4 = t3;

    cout << "Copied Text: " << t4 << endl;

    // Assignment operator
    Text t5;
    t5 = t1;

    cout << "Assigned Text: " << t5 << endl;

    // Equality comparison
    if (t1 == t5)
    {
        cout << "Both texts are equal" << endl;
    }
    else
    {
        cout << "Texts are not equal" << endl;
    }

    // Inequality comparison
    if (t1 != t2)
    {
        cout << "Texts are different" << endl;
    }
    else
    {
        cout << "Texts are equal" << endl;
    }

    // Self-assignment
    t1 = t1;

    cout << "After Self Assignment: " << t1 << endl;

    return 0;
}

