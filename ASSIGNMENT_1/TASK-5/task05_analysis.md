# TASK 5 -- Operators, Precedence and Expressions in C++

## 1. Aim

To understand C++ operators, operator precedence, increment and
decrement operators, integer division, the modulus operator, and logical
expressions used to identify metro peak hours.

## 2. Introduction

Operators are symbols that perform operations on values and variables.
C++ provides arithmetic, relational, logical, assignment, and
increment/decrement operators.

Operator precedence determines which operation is performed first in an
expression. Parentheses can be used to make the intended order clear.

## 3. Concepts Explained

### 3.1 Arithmetic Operators

  Operator   Meaning               Example
  ---------- --------------------- ---------------
  `+`        Addition              `10 + 5 = 15`
  `-`        Subtraction           `10 - 5 = 5`
  `*`        Multiplication        `10 * 5 = 50`
  `/`        Division              `10 / 5 = 2`
  `%`        Remainder (modulus)   `10 % 3 = 1`

### 3.2 Operator Precedence

Multiplication and division have higher precedence than addition and
subtraction.

Example:

``` cpp
int result1 = 10 + 5 * 2;      // 20
int result2 = (10 + 5) * 2;    // 30
```

Parentheses change the order of evaluation and make expressions easier
to understand.

### 3.3 Increment and Decrement Operators

-   `++x` is pre-increment: it increases `x` first, then uses the new
    value.
-   `x++` is post-increment: it uses the current value first, then
    increases `x`.
-   `--x` and `x--` work similarly for decrement.

Example:

``` cpp
int x = 5;
int y = x++;   // y becomes 5, then x becomes 6
int z = ++x;   // x becomes 7, then z becomes 7
```

### 3.4 Negative Division and Modulus

In C++, integer division discards the fractional part by truncating
toward zero.

``` cpp
-7 / 3   // -2
-7 % 3   // -1
 7 / -3  // -2
 7 % -3  // 1
```

The remainder has the sign of the left-hand operand (the dividend), or
is zero.

### 3.5 Peak-Hour Logical Expression

The metro system applies a peak surcharge during these time periods:

-   8:00 AM to before 10:00 AM
-   5:00 PM to before 8:00 PM

Represent time as minutes after midnight. The peak-hour condition is:

``` cpp
(time >= 8 * 60 && time < 10 * 60) ||
(time >= 17 * 60 && time < 20 * 60)
```

The start time is included and the end time is excluded. Therefore, 8:00
AM and 5:00 PM are peak times, while 10:00 AM and 8:00 PM are not.

## 4. Program Code

The source code is saved separately as `task05.cpp`. It demonstrates
arithmetic precedence, pre-increment, post-increment, negative division
and modulus, and the metro peak-hour condition.

## 5. Predicted Output

Before running the program, predict the output of each expression:

  Expression                     Predicted result
  -------------------- --------------------------
  `10 + 5 * 2`                                 20
  `(10 + 5) * 2`                               30
  `x++` when `x = 5`     Uses 5, then x becomes 6
  `++x` when `x = 6`          x becomes 7, uses 7
  `-7 / 3`                                     -2
  `-7 % 3`                                     -1
  `7 / -3`                                     -2
  `7 % -3`                                      1

Expected peak-hour results:

  Time    Peak hour?
  ------- ------------
  07:59   No
  08:00   Yes
  09:59   Yes
  10:00   No
  16:59   No
  17:00   Yes
  19:59   Yes
  20:00   No

## 6. Application in the Metro Smart-Card System

1.  Arithmetic operators calculate the base fare and peak surcharge.
2.  Operator precedence affects the order of fare calculations.
3.  Parentheses help ensure that the surcharge is calculated correctly.
4.  Logical operators `&&` and `||` identify whether a journey starts
    during peak hours.
5.  Correct boundary checks prevent peak charges from being applied
    outside the specified time periods.

For example, an Outer Zone fare of 3000 paise with a 20% peak surcharge
is:

``` cpp
totalFare = 3000 + (3000 * 20 / 100);
```

The result is 3600 paise, which is ₹36.00.

## 7. Conclusion

This task demonstrates how operators and expressions work in C++.
Understanding precedence, increment operators, integer division,
modulus, and logical conditions helps prevent errors in metro fare
calculations and peak-hour detection.

## 8. Result

The C++ program successfully demonstrates operator precedence, increment
operations, negative division and modulus, and peak-hour checking at the
required time boundaries.
