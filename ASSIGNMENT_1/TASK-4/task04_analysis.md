# TASK 4 -- Type Conversions in C++

## 1. Aim

To study and demonstrate different type conversions in C++, including
implicit conversion, integer division, signed and unsigned comparison,
narrowing conversion, and explicit conversion using `static_cast`.

## 2. Introduction

Type conversion is the process of changing a value from one data type to
another. C++ supports automatic conversion (implicit conversion) and
programmer-controlled conversion (explicit conversion).

Type conversions must be handled carefully in a metro smart-card system
because incorrect conversions can affect fare calculations.

## 3. Concepts Explained

### 3.1 Implicit Conversion

Implicit conversion happens automatically when a value of one data type
is assigned to a compatible data type.

**Example:**

``` cpp
int farePaise = 3000;
double fare = farePaise;
```

Here, the integer value `3000` is automatically converted into a
`double` value.

### 3.2 Integer Division

When two integer values are divided, the fractional part of the result
is discarded.

**Example:**

``` cpp
int a = 5;
int b = 2;
cout << a / b;       // Output: 2
cout << 5.0 / 2;     // Output: 2.5
```

Integer division produces `2`, while floating-point division produces
`2.5`.

### 3.3 Signed and Unsigned Values

-   A signed integer can represent negative and positive values.
-   An unsigned integer can represent zero and positive values only.

When a signed integer and an unsigned integer of the same rank are
compared, the signed value may be converted to unsigned. Therefore,
comparing `-1` with `1u` can produce an unexpected result.

**Example:**

``` cpp
int signedValue = -1;
unsigned int unsignedValue = 1;

if (signedValue < unsignedValue)
    cout << "Signed value is smaller";
else
    cout << "Signed value is NOT smaller";
```

On the usual C++ implementation where `int` and `unsigned int` have the
same rank, the comparison is false because `-1` is converted to a large
unsigned value.

### 3.4 Narrowing Conversion

Narrowing conversion changes a value into a type that may not preserve
all its information.

**Example:**

``` cpp
double decimalValue = 36.75;
int result = static_cast<int>(decimalValue);
```

The result is `36`. The fractional part `.75` is discarded. This
conversion does not round the value.

### 3.5 Explicit Conversion Using `static_cast`

`static_cast` is used when the programmer wants to request a conversion
explicitly.

**Example:**

``` cpp
int totalPaise = 3600;
double rupees = static_cast<double>(totalPaise) / 100;
```

The result is `36.00` rupees. Converting to `double` before division
ensures that the division is floating-point division.

## 4. Program Code

The source code is saved separately as `task04.cpp`. It demonstrates all
five concepts using simple examples related to the metro smart-card fare
system.

## 5. Expected Output

``` text
METRO SMART CARD - TYPE CONVERSION
----------------------------------

1. IMPLICIT CONVERSION
Integer fare in paise: 3000
Converted double value: 3000

2. INTEGER DIVISION
5 / 2 = 2
5.0 / 2 = 2.5

3. SIGNED AND UNSIGNED
Signed value: -1
Unsigned value: 1
Signed value is NOT smaller.

4. NARROWING CONVERSION
Original decimal value: 36.75
After conversion to int: 36

5. STATIC CAST
Total fare in paise: 3600
Total fare in rupees: Rs. 36.00

Conclusion: Use explicit conversion carefully.
```

**Note:** The displayed memory sizes and some type-conversion behaviour
can depend on the compiler and platform. The signed/unsigned comparison
shown above assumes the usual implementation where `int` and
`unsigned int` have the same rank.

## 6. Application in the Metro Smart-Card System

1.  Fare values can be stored as integer paise to avoid floating-point
    representation errors.
2.  Integer division must be used carefully because it discards the
    fractional part.
3.  Signed and unsigned values should not be mixed carelessly in
    comparisons.
4.  Explicit conversions make the programmer's intention clear.
5.  Narrowing conversions should be checked because they can lose
    information.

## 7. Conclusion

The program demonstrates implicit conversion, integer division, signed
and unsigned comparison, narrowing conversion, and `static_cast`. These
concepts help a programmer avoid unexpected results and perform safer
fare calculations in a metro smart-card system.

## 8. Result

The C++ program successfully demonstrates the different type-conversion
operations and displays their results.
