# Task 9 - Implement and Test the Fare Logic

**Name:** <your name>
**Register No:** <your register number>
**Course:** Object-Oriented Programming using C++ - Assignment 1 [CO1]

> Files in this folder:
> - `task09_analysis.md` - this analysis
> - `task09.cpp` - the complete fare logic with a table-driven test program
> - `task09_output.txt` and the output screenshot - result of running `task09.cpp` (28 of 28 tests pass)

**Compile and run:**
```
g++ -std=c++17 -Wall -Wextra task09.cpp -o task09
./task09
```

---

## 1. Implementation

```cpp
enum class Zone { Inner, Middle, Outer };

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int       PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

// returns the fare in paise, or -1 for an invalid zone number or hour
long long fare(int zoneIndex, int hour) {
    if (zoneIndex < 0 || zoneIndex > 2 || hour < 0 || hour > 23) return -1;
    long long f = BASE_PAISE[zoneIndex];
    if (isPeak(hour)) f += f * PEAK_SURCHARGE_PERCENT / 100;     // multiply first, then divide
    return f;
}

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long b) : balance_{b} {}
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    bool recharge(long long p) { if (p <= 0) return false; balance_ += p; return true; }
    long long balance() const { return balance_; }
};

// reads an hour typed as text; returns -1 for letters or anything that is not a whole number
int parseHour(const std::string& s) { /* stoi inside try/catch, rejects "9x" */ }
```

All money is exact `long long` paise, all constants are in one place, the peak rule uses half-open intervals, and invalid input is rejected before it can reach the balance.

---

## 2. Test plan

| Group | What is tested | Why |
|---|---|---|
| A. Normal journeys | each zone, peak and off-peak | basic correctness |
| A. Boundary hours | 7, 8, 9, 10, 17, 19, 20 | the peak intervals are half-open; 10:00 and 20:00 must be off-peak |
| B. Invalid inputs | unknown zone (5, -1), hour 25, letters typed for the hour (`abc`, `9x`) | invalid input must be rejected, not priced |
| C. Balance rules | a balance that leaves exactly Rs 50, one that leaves Rs 49.99, negative and zero recharge | the Rs 50 rule and a protected balance |
| D. Hand-calculated total | five journeys whose total is worked out by hand | an independent check of the whole calculation |

---

## 3. Test table with expected and actual results

The program calls `check(name, expected, actual)` for every row and prints PASS or FAIL. **Every row passed.**

### A. Fare tests

| # | Case | Zone | Hour | Expected (paise) | Actual | Result |
|---|---|---|---|---|---|---|
| 1 | Off-peak Inner | Inner | 12 | 1000 | 1000 | PASS |
| 2 | Off-peak Middle | Middle | 12 | 2000 | 2000 | PASS |
| 3 | Off-peak Outer | Outer | 12 | 3000 | 3000 | PASS |
| 4 | Peak Inner | Inner | 9 | 1200 | 1200 | PASS |
| 5 | Peak Middle | Middle | 18 | 2400 | 2400 | PASS |
| 6 | Peak Outer | Outer | 8 | 3600 | 3600 | PASS |
| 7 | Just before peak | Inner | 7 | 1000 | 1000 | PASS |
| 8 | Peak starts (8:00) | Inner | 8 | 1200 | 1200 | PASS |
| 9 | Hour 9 still peak | Inner | 9 | 1200 | 1200 | PASS |
| 10 | **10:00 is off-peak (boundary)** | Inner | 10 | 1000 | 1000 | PASS |
| 11 | **17:00 is peak (boundary)** | Inner | 17 | 1200 | 1200 | PASS |
| 12 | Hour 19 still peak | Inner | 19 | 1200 | 1200 | PASS |
| 13 | **20:00 is off-peak (boundary)** | Inner | 20 | 1000 | 1000 | PASS |

### B. Invalid inputs

| # | Case | Expected | Actual | Result |
|---|---|---|---|---|
| 14 | Unknown zone 5 | -1 (rejected) | -1 | PASS |
| 15 | Negative zone -1 | -1 (rejected) | -1 | PASS |
| 16 | Hour 25 | -1 (rejected) | -1 | PASS |
| 17 | Hour typed as `abc` | -1 (rejected) | -1 | PASS |
| 18 | Hour typed as `9x` | -1 (rejected) | -1 | PASS |
| 19 | Hour typed as `9` | 9 (accepted) | 9 | PASS |

### C. Balance rules

| # | Case | Expected | Actual | Result |
|---|---|---|---|---|
| 20 | 6000 - 1000 leaves exactly 5000: allowed | true | true | PASS |
| 21 | balance after that journey | 5000 | 5000 | PASS |
| 22 | 5999 - 1000 would leave 4999: refused | false | false | PASS |
| 23 | balance unchanged after the refusal | 5999 | 5999 | PASS |
| 24 | negative recharge -500 refused | false | false | PASS |
| 25 | zero recharge refused | false | false | PASS |
| 26 | positive recharge 2000 accepted | true | true | PASS |
| 27 | balance after recharge (10000 + 2000) | 12000 | 12000 | PASS |

### D. Five journeys whose total is calculated by hand

| Journey | Zone | Hour | Peak? | Calculation | Fare (paise) |
|---|---|---|---|---|---|
| 1 | Inner | 12 | No | 1000 | 1000 |
| 2 | Middle | 9 | Yes | 2000 + 400 | 2400 |
| 3 | Outer | 15 | No | 3000 | 3000 |
| 4 | Inner | 18 | Yes | 1000 + 200 | 1200 |
| 5 | Outer | 10 | No (10:00 is off-peak) | 3000 | 3000 |
| **Total** | | | | 1000 + 2400 + 3000 + 1200 + 3000 | **10600 paise = Rs 106.00** |

| # | Case | Expected | Actual | Result |
|---|---|---|---|---|
| 28 | Total of the five journeys | 10600 | 10600 | PASS |

**Program result:** `28/28 tests passed`

---

## 4. Alternative Concept and Complexity Analysis: separate hand-written checks instead of a table

If each journey were tested with separate hand-written checks instead of a table of test cases in a loop, the solution would be:

```cpp
if (fare(0, 12) != 1000) std::cout << "FAIL Inner 12\n";
if (fare(1, 12) != 2000) std::cout << "FAIL Middle 12\n";
if (fare(2, 12) != 3000) std::cout << "FAIL Outer 12\n";
// ... one separate if-statement for every case ...
```

The table version used in `task09.cpp` keeps the cases as data (`{zone, hour, expected}`) and one loop runs them all.

**Time.** For t test cases, both methods call the function once per case, so the time is **O(t)**.

**Space.** The table stores t entries, so the space is **O(t)** (for example 13 entries of three `int`/`long long` values, a few hundred bytes). The hand-written version stores no table, but its source code grows by one statement per case.

**Adding a new boundary case:**

| Point | Table of test cases | Separate hand-written checks |
|---|---|---|
| Adding a case | add **one row of data** | write a new `if` statement |
| Risk of copy-and-paste errors | low | higher |
| Reading the cases | all cases visible together as a table | cases spread across many lines |
| Reporting | the loop prints PASS or FAIL and the totals automatically | each check needs its own message |

**Conclusion.** Both take O(t) time, so speed is not the difference. The table is easier to extend and to review, so it is the better design for this test suite.

---

## 5. Evidence summary

- Complete fare logic with a protected `SmartCard` (section 1)
- Test plan covering normal, boundary, invalid and balance cases (section 2)
- Test table with expected and actual results for every case, all PASS, and the hand-calculated five-journey total of Rs 106.00 (section 3)
- Table-driven testing alternative with Big-O analysis (section 4)
