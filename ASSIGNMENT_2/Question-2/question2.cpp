
#include <iostream>
using namespace std;

// Function returning reference to the highest mark
int& highestMark(int marks[], int size)
{
    int maxIndex = 0;

    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }

    return marks[maxIndex];
}

// Function returning a copy of the highest mark
int highestMarkCopy(int marks[], int size)
{
    int maxMark = marks[0];

    for (int i = 1; i < size; i++)
    {
        if (marks[i] > maxMark)
        {
            maxMark = marks[i];
        }
    }

    return maxMark;
}

// Safe alternative: return the index of highest mark
int highestMarkIndex(int marks[], int size)
{
    int maxIndex = 0;

    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }

    return maxIndex;
}

int main()
{
    int marks[5] = {75, 88, 92, 81, 85};

    cout << "Original examination marks:" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << marks[i] << " ";
    }

    cout << endl;

    // Return by reference
    highestMark(marks, 5) += 2;

    cout << "\nAfter increasing highest mark by 2:" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << marks[i] << " ";
    }

    cout << endl;

    cout << "\nHighest mark using copy: "
         << highestMarkCopy(marks, 5) << endl;

    // Using index as an alternative
    int index = highestMarkIndex(marks, 5);

    cout << "Highest mark index: " << index << endl;

    cout << "Highest mark using index: "
         << marks[index] << endl;

    return 0;
}

