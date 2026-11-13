
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Time
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0)
    {
        hours = h;
        minutes = m;
        seconds = s;

        normalize();
    }

    void normalize()
    {
        int total = hours * 3600 + minutes * 60 + seconds;

        if (total < 0)
            total = 0;

        hours = total / 3600;
        minutes = (total % 3600) / 60;
        seconds = total % 60;
    }

    // Prefix increment
    Time &operator++()
    {
        seconds++;
        normalize();
        return *this;
    }

    // Postfix increment
    Time operator++(int)
    {
        Time old = *this;
        seconds++;
        normalize();
        return old;
    }

    // Equality operator
    bool operator==(const Time &t) const
    {
        return hours == t.hours &&
               minutes == t.minutes &&
               seconds == t.seconds;
    }

    // Less than operator
    bool operator<(const Time &t) const
    {
        int first = hours * 3600 + minutes * 60 + seconds;
        int second = t.hours * 3600 + t.minutes * 60 + t.seconds;

        return first < second;
    }

    void display() const
    {
        cout << hours << ":"
             << (minutes < 10 ? "0" : "") << minutes << ":"
             << (seconds < 10 ? "0" : "") << seconds << endl;
    }
};

class Playlist
{
private:
    string songs[5];
    int size;

public:
    Playlist()
    {
        size = 0;
    }

    void addSong(const string &song)
    {
        if (size < 5)
        {
            songs[size] = song;
            size++;
        }
        else
        {
            cout << "Playlist is full" << endl;
        }
    }

    // Non-constant subscript operator
    string &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Invalid playlist index");
        }

        return songs[index];
    }

    // Constant subscript operator
    const string &operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Invalid playlist index");
        }

        return songs[index];
    }

    int getSize() const
    {
        return size;
    }
};

int main()
{
    cout << "TIME OPERATIONS" << endl;

    Time t1(1, 59, 59);

    cout << "Original Time: ";
    t1.display();

    Time a = t1++;

    cout << "After Postfix Increment: ";
    t1.display();

    cout << "Old Time: ";
    a.display();

    Time b = ++t1;

    cout << "After Prefix Increment: ";
    t1.display();

    cout << "Prefix Result: ";
    b.display();

    Time t2(2, 0, 1);

    cout << "Are times equal? "
         << (t1 == t2 ? "true" : "false") << endl;

    cout << "Is first time less? "
         << (t1 < t2 ? "true" : "false") << endl;

    cout << "\nPLAYLIST OPERATIONS" << endl;

    Playlist p;

    p.addSong("Song One");
    p.addSong("Song Two");
    p.addSong("Song Three");

    cout << "Playlist Songs:" << endl;

    for (int i = 0; i < p.getSize(); i++)
    {
        cout << p[i] << endl;
    }

    p[1] = "Updated Song";

    cout << "\nAfter Updating:" << endl;

    for (int i = 0; i < p.getSize(); i++)
    {
        cout << p[i] << endl;
    }

    try
    {
        cout << p[5] << endl;
    }
    catch (const out_of_range &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

