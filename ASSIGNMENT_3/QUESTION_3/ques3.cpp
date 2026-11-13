#include <iostream>
using namespace std;

class Auditorium
{
private:
    int rows;
    int seatsPerRow;
    char **seatMap;

public:
    Auditorium(int r, int s)
        : rows(r), seatsPerRow(s), seatMap(NULL)
    {
        if (rows > 0 && seatsPerRow > 0)
        {
            seatMap = new char*[rows];

            for (int i = 0; i < rows; i++)
            {
                seatMap[i] = new char[seatsPerRow];

                for (int j = 0; j < seatsPerRow; j++)
                {
                    seatMap[i][j] = 'O';
                }
            }
        }

        cout << "Auditorium created" << endl;
    }

    void bookSeat(int r, int s)
    {
        if (r >= 0 && r < rows &&
            s >= 0 && s < seatsPerRow)
        {
            if (seatMap[r][s] == 'O')
            {
                seatMap[r][s] = 'X';
                cout << "Seat booked successfully" << endl;
            }
            else
            {
                cout << "Seat already booked" << endl;
            }
        }
        else
        {
            cout << "Invalid seat number" << endl;
        }
    }

    void cancelSeat(int r, int s)
    {
        if (r >= 0 && r < rows &&
            s >= 0 && s < seatsPerRow)
        {
            if (seatMap[r][s] == 'X')
            {
                seatMap[r][s] = 'O';
                cout << "Booking cancelled" << endl;
            }
            else
            {
                cout << "Seat is not booked" << endl;
            }
        }
        else
        {
            cout << "Invalid seat number" << endl;
        }
    }

    void display()
    {
        cout << "\nSeat Map:\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < seatsPerRow; j++)
            {
                cout << seatMap[i][j] << " ";
            }

            cout << endl;
        }
    }

    ~Auditorium()
    {
        if (seatMap != NULL)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] seatMap[i];
            }

            delete[] seatMap;
        }

        cout << "Auditorium memory released" << endl;
    }
};

int main()
{
    Auditorium a(3, 4);

    a.display();

    a.bookSeat(1, 2);
    a.bookSeat(2, 1);

    a.display();

    a.cancelSeat(1, 2);

    a.display();

    return 0;
}
