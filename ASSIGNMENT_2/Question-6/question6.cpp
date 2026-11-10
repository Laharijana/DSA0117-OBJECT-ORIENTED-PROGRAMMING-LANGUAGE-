
#include <iostream>
using namespace std;

class Time
{
private:
    int h;
    int m;

public:
    Time(int hh, int mm)
    {
        h = hh;
        m = mm;
    }

    // Friend functions
    friend int minutesBetween(const Time &a, const Time &b);
    friend bool earlier(const Time &a, const Time &b);
};

// Inline function
inline int convertToMinutes(int h, int m)
{
    return h * 60 + m;
}

// Calculate absolute difference between two times
int minutesBetween(const Time &a, const Time &b)
{
    int time1 = convertToMinutes(a.h, a.m);
    int time2 = convertToMinutes(b.h, b.m);

    int difference = time1 - time2;

    if (difference < 0)
    {
        difference = -difference;
    }

    return difference;
}

// Check whether first time is earlier than second time
bool earlier(const Time &a, const Time &b)
{
    int time1 = convertToMinutes(a.h, a.m);
    int time2 = convertToMinutes(b.h, b.m);

    return time1 < time2;
}

int main()
{
    cout << "===== TRAIN TIME PLANNER =====" << endl;

    Time departure(9, 45);
    Time arrival(13, 10);

    cout << "Minutes between departure and arrival: "
         << minutesBetween(departure, arrival) << endl;

    cout << "Is arrival earlier than departure? "
         << boolalpha << earlier(arrival, departure) << endl;

    // Additional test
    Time train1(8, 30);
    Time train2(10, 15);

    cout << "Minutes between train1 and train2: "
         << minutesBetween(train1, train2) << endl;

    cout << "Is train1 earlier than train2? "
         << boolalpha << earlier(train1, train2) << endl;

    // Same time test
    Time same1(12, 0);
    Time same2(12, 0);

    cout << "Minutes between same times: "
         << minutesBetween(same1, same2) << endl;

    cout << "Is first same time earlier? "
         << boolalpha << earlier(same1, same2) << endl;

    return 0;
}

