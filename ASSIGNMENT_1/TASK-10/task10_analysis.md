# Task 10 - Compare Expectations with Execution

**Name:** <your name>
**Register No:** <your register number>
**Course:** Object-Oriented Programming using C++ - Assignment 1 [CO1]

> Files in this folder:
> - `task10_analysis.md` - this analysis
> - `task10.cpp` - experiment: the same totals in `double` rupees, exact `long long` paise and a 32-bit integer
> - `task10_output.txt` and the output screenshot - result of running `task10.cpp`
> - `overflow_int.cpp` and `overflow_int_output.txt` - proof that a signed `int` accumulator overflows (checked with `-fsanitize=undefined`)
> - `warnings_demo.cpp` and `warnings.txt` - the warnings produced by `-Wall -Wextra -Wconversion`

**Compile and run:**
```
g++ -std=c++17 -Wall -Wextra task10.cpp -o task10
./task10

g++ -std=c++17 -Wall -Wextra -fsanitize=undefined overflow_int.cpp -o overflow_int
./overflow_int

g++ -std=c++17 -Wall -Wextra -Wconversion warnings_demo.cpp -o warnings_demo 2> warnings.txt
```

---

## 1. Expectation (written before running)

Each journey costs Rs 20.10 (2010 paise). The total for n journeys, calculated by hand, is n x 2010 paise.

| n (journeys per day) | Expected total (paise) | Expected total (Rs) | Fits in 32-bit `int`? (max 2,147,483,647) |
|---|---|---|---|
| 20,000 (1 station) | 40,200,000 | 402,000.00 | yes |
| 500,000 (1 line) | 1,005,000,000 | 10,050,000.00 | yes |
| 3,000,000 (whole network) | 6,030,000,000 | 60,300,000.00 | **no** (about 2.8 times too large) |

My expectation: `long long` paise will be exact, `double` rupees will be close but not exact, and the 32-bit `int` will fail at 3,000,000 journeys.

---

## 2. Experiment and measured results

```cpp
for (long long k = 0; k < n; ++k) {
    d    += fareRs;                                      // double rupees: 20.10
    p    += farePaise;                                   // long long paise: 2010
    wrap += static_cast<std::uint32_t>(farePaise);       // 32-bit counter (wraps without undefined behaviour)
}
```

**Actual output (g++ 13.3.0, `-std=c++17 -Wall -Wextra`):**

```
n = 20000 journeys
  expected (n x 2010)      = 40200000 paise
  long long paise          = 40200000 paise   (exact)
  double rupees x 100      = 40199999.999989 paise   (difference -0.000011 paise)
  32-bit int would keep    = 40200000 paise   (correct)
  loop time                = 61 us

n = 500000 journeys
  expected (n x 2010)      = 1005000000 paise
  long long paise          = 1005000000 paise   (exact)
  double rupees x 100      = 1004999999.990519 paise   (difference -0.009481 paise)
  32-bit int would keep    = 1005000000 paise   (correct)
  loop time                = 1415 us

n = 3000000 journeys
  expected (n x 2010)      = 6030000000 paise
  long long paise          = 6030000000 paise   (exact)
  double rupees x 100      = 6030000000.300708 paise   (difference 0.300708 paise)
  32-bit int would keep    = 1735032704 paise   (OVERFLOW)
  loop time                = 8529 us
```

(The loop times depend on the computer and will differ on yours.)

**Summary of the three representations:**

| n | long long paise | double rupees (difference from exact) | 32-bit int |
|---|---|---|---|
| 20,000 | exact | -0.000011 paise | correct |
| 500,000 | exact | -0.009481 paise | correct |
| 3,000,000 | exact | +0.300708 paise | **WRONG: 1,735,032,704** |

---

## 3. Do the double and integer-paise totals agree, and by how much do they differ?

They **do not agree exactly**. The integer-paise totals match the hand calculation exactly at all three sizes. The `double` totals are very close but differ, and the difference grows with n:

- 20,000 journeys: about 0.000011 paise (invisible when printed to the paisa)
- 500,000 journeys: about 0.009 paise (still under a hundredth of a paisa)
- 3,000,000 journeys: about 0.30 paise (a third of a paisa)

For a single total the difference is small, but a metro that settles accounts every day and compares totals to the paisa cannot accept a total that is not exactly right, and the error is not predictable in sign (it was negative at 500,000 and positive at 3,000,000).

## 4. Does `int` overflow for the network total?

**Yes.** The expected total at 3,000,000 journeys is 6,030,000,000 paise, which is larger than `INT_MAX` (2,147,483,647). The 32-bit counter wrapped around to 1,735,032,704, which is wrong by more than 4 billion paise.

For a **signed** `int`, overflow is undefined behaviour in C++. I confirmed it with the undefined-behaviour sanitizer (`overflow_int.cpp`, a plain `int total` adding 2010 three million times):

```
overflow_int.cpp:4:45: runtime error: signed integer overflow: 2147481990 + 2010 cannot be represented in type 'int'
1735032704
```

So an `int` total is correct for one station and one line but **fails for the whole network**, and the failure is silent unless a tool such as the sanitizer is used.

---

## 5. Compiler warnings with `-Wall -Wextra` and what each meant

My final programs for Tasks 2, 3, 6, 7, 8, 9, 10 and 12 (and the corrected Task 4 program) compiled with **no warnings** under `-Wall -Wextra`. Warnings appeared in two places only: the original Task 4 program (`-Wsign-compare`) and the deliberately incomplete Task 12 `switch` demo (`-Wswitch`). I also added a small file to show the other common warnings (`warnings_demo.cpp`, compiled with `-Wall -Wextra -Wconversion`):

```
warnings_demo.cpp:5:11: warning: comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]
warnings_demo.cpp:6:29: warning: conversion from 'double' to 'int' may change value [-Wfloat-conversion]
warnings_demo.cpp:3:9: warning: unused variable 'unused' [-Wunused-variable]
warnings_demo.cpp:2:14: warning: unused parameter 'argc' [-Wunused-parameter]
warnings_demo.cpp:2:27: warning: unused parameter 'argv' [-Wunused-parameter]
```

| Warning | What it meant | How it is fixed |
|---|---|---|
| `-Wsign-compare` | a signed value is compared with an unsigned one, so the signed value is converted to unsigned and -1 becomes 4294967295 (Task 4) | check `s < 0` first, or compare as `long long` |
| `-Wfloat-conversion` | a `double` is stored in an `int`, so the fractional part is dropped | use `static_cast<int>(...)` on purpose, or brace initialisation, or keep the type `double` |
| `-Wunused-variable` | a variable is declared but never used (dead code or a typo) | remove it |
| `-Wunused-parameter` | a function parameter is never used | remove the name or the parameter |
| `-Wswitch` (Task 12) | a value of an enum (`Airport`) is not handled in a `switch` | add the missing `case` or a `default` |

---

## 6. Reasons for the differences between expectation and execution

| Observation | Reason |
|---|---|
| `long long` paise matches exactly | whole numbers are stored exactly in binary; no rounding occurs |
| `double` totals differ slightly | 20.10 has no exact binary representation, so each addition rounds, and the rounding errors accumulate as n grows |
| `int` fails at 3,000,000 | a 32-bit signed integer holds at most 2,147,483,647 and the true total is 6,030,000,000 |
| `int` correct at 20,000 and 500,000 | both totals are below the 32-bit limit |

My expectation from section 1 was therefore confirmed on all three points.

---

## 7. Alternative Concept and Complexity Analysis: accumulating in `int`, `long long` or `double`

If the network total were accumulated in an `int`, a `long long` or a `double`, the result at 3,000,000 journeys would be:

| Accumulator | Result at 3,000,000 journeys | How it fails | Time per addition | Space per variable |
|---|---|---|---|---|
| `int` (32-bit) | wrong (wrapped to 1,735,032,704 paise) | **overflow** (value exceeds 2,147,483,647) | O(1) | 4 bytes |
| `long long` | exact 6,030,000,000 paise | none; overflow only above about 9.22 x 10^18 paise | O(1) | 8 bytes |
| `double` (rupees) | 60300000.003007 Rs, about 0.30 paise too high | **loss of precision** (rounding error accumulates) | O(1) | 8 bytes |

**Two different kinds of failure:**
- **Overflow** (`int`): the number is too large for the type, so the stored value is completely wrong. It is a *range* problem.
- **Loss of precision** (`double`): the number is in range but cannot be stored exactly, so the error is small and grows slowly. It is an *exactness* problem.

**Time and space.** Each addition is one instruction, so the time per addition is **O(1)** for all three, and n additions cost **O(n)**. The measured loop time for 3,000,000 additions was about 8.5 milliseconds (one loop that does all three additions at once). The space per variable is 4 bytes for `int` and 8 bytes for `long long` and `double`, so the extra 4 bytes of `long long` are negligible. Speed and memory therefore do not decide the question; **correctness does**, and only `long long` paise is both in range and exact.

---

## 8. Evidence summary

- Expectation table written before running (section 1)
- Measured totals for 20,000, 500,000 and 3,000,000 journeys in three types (section 2)
- Size of the `double` difference and the `int` overflow, confirmed with the sanitizer (sections 3 and 4)
- Compiler warnings received and their meaning (section 5)
- Reasons for the differences (section 6)
- Overflow versus loss-of-precision comparison with time and space (section 7)
