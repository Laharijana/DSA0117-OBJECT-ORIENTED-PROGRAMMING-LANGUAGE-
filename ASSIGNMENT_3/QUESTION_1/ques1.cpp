#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    string title;
    int copies;

    static int validateCopies(int c)
    {
        if (c < 0)
            return 0;
        return c;
    }

public:
    Book() : Book("", 0)
    {
        cout << "Default constructor called" << endl;
    }

    explicit Book(const string &t) : Book(t, 1)
    {
        cout << "Title-only constructor called" << endl;
    }

    Book(const string &t, int c)
        : title(t), copies(validateCopies(c))
    {
        cout << "Parameterized constructor called" << endl;
    }

    void display() const
    {
        cout << "Book Title: "
             << (title.empty() ? "Empty Record" : title)
             << endl;

        cout << "Number of Copies: " << copies << endl;
        cout << "------------------------" << endl;
    }
};

int main()
{
    Book b1;
    Book b2("C++ Programming");
    Book b3("Data Structures", 5);
    Book b4("Computer Networks", -3);

    b1.display();
    b2.display();
    b3.display();
    b4.display();

    return 0;
}
