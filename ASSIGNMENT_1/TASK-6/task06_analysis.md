# TASK 6 -- Design the Control Structures

## 1. Aim

To design and understand decision-making and looping structures in C++
for calculating metro fares and processing a day's journeys. The task
also demonstrates a `switch` statement, integer-paise arithmetic, fare
validation, and the minimum-balance rule.

## 2. Introduction

Control structures decide the order in which statements execute in a
program.

The main control structures used in this task are:

-   `if–else` for checking conditions such as whether a passenger has
    enough balance.
-   `switch` for selecting the fare based on the travel zone.
-   `for` or range-based `for` loops for processing a known collection
    of journeys.
-   `while` loops when the number of journeys is not known in advance.
-   `break` to exit a switch or loop.
-   `continue` to skip the current invalid journey and move to the next
    one.

## 3. Control Structures and Their Uses

### 3.1 If--Else Statement

An `if–else` statement is suitable for checking conditions.

In this system, it checks whether the card has enough balance remaining
after fare deduction.

``` cpp
if (canTravel(balance, fareAmount)) {
    balance -= fareAmount;
} else {
    cout << "Denied (low balance)";
}
```

### 3.2 Switch Statement

A `switch` statement is suitable when one variable is compared against
several fixed choices.

Here, the zone determines the base fare:

-   Inner Zone -- 1000 paise
-   Middle Zone -- 2000 paise
-   Outer Zone -- 3000 paise

Each `case` selects the corresponding fare. The `break` statement
prevents execution from continuing into the next case.

If no case matches and there is no `default` case, no case body
executes. A `default` case can be used to handle an invalid zone safely.

### 3.3 Conditional Operator

The conditional operator `?:` is a short form of `if–else`.

``` cpp
string result = peak ? "Peak" : "Off-Peak";
```

It is useful for choosing between two simple values, but a normal
`if–else` is clearer for multiple statements or complex logic.

### 3.4 Looping Structures

  -----------------------------------------------------------------------
  Loop                    Use                     Suitability
  ----------------------- ----------------------- -----------------------
  Traditional `for`       Repeats a known number  Suitable for a fixed
                          of times using an index number of journeys

  Range-based `for`       Visits every item in an Best for the supplied
                          array or collection     trip array because no
                                                  index is needed

  `while`                 Repeats while a         Suitable when journeys
                          condition remains true  arrive until input ends
  -----------------------------------------------------------------------

A range-based `for` loop is selected in this program because the
journeys are already stored in an array.

### 3.5 Break and Continue

-   `break` exits the current `switch` or loop.
-   `continue` skips the remaining statements in the current loop
    iteration and moves to the next journey.

For example, `continue` can skip an invalid journey without stopping the
processing of all other journeys.

## 4. Pseudocode

### 4.1 Fare Computation

``` text
ALGORITHM CalculateFare(zone, peak)

    SET baseFare TO 0

    SWITCH zone
        CASE Inner:
            SET baseFare TO 1000
            BREAK

        CASE Middle:
            SET baseFare TO 2000
            BREAK

        CASE Outer:
            SET baseFare TO 3000
            BREAK

        DEFAULT:
            RETURN -1
    END SWITCH

    IF peak IS TRUE THEN
        SET surcharge TO baseFare * 20 / 100
        SET baseFare TO baseFare + surcharge
    END IF

    RETURN baseFare

END ALGORITHM
```

### 4.2 Balance Validation

``` text
ALGORITHM CanTravel(balance, fareAmount)

    IF balance - fareAmount >= 5000 THEN
        RETURN TRUE
    ELSE
        RETURN FALSE
    END IF

END ALGORITHM
```

### 4.3 Processing Journeys

``` text
ALGORITHM ProcessJourneys

    SET balance TO 10000

    FOR EACH trip IN trips
        CALCULATE fareAmount

        IF trip is invalid THEN
            CONTINUE
        END IF

        IF CanTravel(balance, fareAmount) THEN
            DEDUCT fareAmount FROM balance
            DISPLAY fare and remaining balance
        ELSE
            DISPLAY "Denied (low balance)"
        END IF
    END FOR

END ALGORITHM
```

## 5. Complete Code

The complete C++ source code is saved separately as `task06.cpp`. It
completes both TODO sections using a `switch` statement and integer
paise, processes the supplied journeys, and checks the 10:00 AM and 8:00
PM peak-hour boundaries.

## 6. Expected Output

``` text
Fare Rs 10.00 balance Rs 90
Fare Rs 36.00 balance Rs 54
Denied (low balance) balance Rs 54

Peak boundary checks:
10:00 AM - Off-Peak
8:00 PM - Off-Peak
```

The fare results are:

1.  Inner Zone, off-peak: ₹10.00. Balance becomes ₹90.00.
2.  Outer Zone, peak: ₹36.00. Balance becomes ₹54.00.
3.  Middle Zone, off-peak: ₹20.00. The journey is denied because the
    remaining balance would be ₹34.00, below the required ₹50.00.

At exactly 10:00 AM and exactly 8:00 PM, the journey is off-peak because
the peak periods use an inclusive start and exclusive end.

## 7. Alternative Concept: Array Lookup Instead of Switch

The base fare can also be stored in an array:

``` cpp
constexpr long long FARE[] = {1000, 2000, 3000};
```

The fare can be selected using the zone's numeric index:

``` cpp
long long baseFare = FARE[static_cast<int>(zone)];
```

Both the `switch` and array lookup take O(1) time for a fixed number of
zones.

-   **Switch:** clearly names each zone and can handle invalid values
    with a `default` case.
-   **Array:** provides direct indexed lookup, but the index must be
    validated to prevent out-of-range access.
-   **Space:** the array uses O(1) space for three fixed fares (three
    `long long` values).
-   **Fourth zone:** a switch requires a new case; an array requires
    another fare entry and an updated zone value. Both designs need
    updating.

The switch-based design is used in the required program because the task
specifically asks for a switch statement and it makes each zone choice
easy to read.

## 8. Time and Space Complexity

Let `n` be the number of journeys processed.

  Operation                  Time Complexity
  -------------------------- ------------------
  Select fare using switch   O(1)
  Calculate surcharge        O(1)
  Check remaining balance    O(1)
  Process all journeys       O(n)
  Array fare lookup          O(1) per journey

The program stores a fixed-size trip array and a few variables, so its
auxiliary space is O(1) for a fixed number of trips. If the trip
collection grows with `n`, the storage for that collection is O(n).

## 9. Application in the Metro Smart-Card System

1.  The `switch` statement selects the correct zone fare.
2.  Integer paise keeps fare calculations exact.
3.  The peak surcharge is calculated using integer arithmetic.
4.  The `if–else` statement prevents the balance from falling below ₹50.
5.  The range-based `for` loop processes each journey in the collection.
6.  Boundary checks ensure that 10:00 AM and 8:00 PM are off-peak.

## 10. Conclusion

The task demonstrates how selection and looping control structures can
be combined to calculate fares and process multiple metro journeys. The
switch statement selects the zone fare, integer arithmetic calculates
the surcharge, and the balance condition prevents an invalid deduction.

## 11. Result

The program successfully completes the fare and balance functions,
processes the sample journeys, and confirms that the exact 10:00 AM and
8:00 PM boundaries are treated as off-peak.
