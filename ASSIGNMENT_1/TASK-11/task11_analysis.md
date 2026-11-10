# Task 11 - Recommend and Defend the Final Design

**Name:** <your name>
**Register No:** <your register number>
**Course:** Object-Oriented Programming using C++ - Assignment 1 [CO1]

> Files in this folder:
> - `task11_analysis.md` - this recommendation
> - `task11_config.cpp` - alternative concept: fare table read from a configuration file at start-up
> - `fares.txt`, `fares4.txt`, `fares_bad.txt` - sample configuration files (3 fares, 4 fares, a corrupt file)
> - `task11_config_output.txt` and the output screenshot - result of running the configuration demo

**Compile and run (alternative concept):**
```
g++ -std=c++17 -Wall -Wextra task11_config.cpp -o task11_config
./task11_config fares.txt
./task11_config fares4.txt
./task11_config fares_bad.txt
./task11_config nofile.txt
```

This task is a recommendation, so the evidence comes from the experiments in Tasks 3, 4, 7, 9, 10 and 12, plus the configuration-file experiment below.

---

## 1. Recommended design

| Area | Recommendation | Evidence from my own experiments |
|---|---|---|
| **Money** | `long long` integer **paise** for fares, balances, recharges and totals | Task 3 and 10: `double` rupees drifted (+0.30 paise at 3,000,000 journeys) while paise were exact; Task 4: `base * (20 / 100)` gave a surcharge of 0 until fixed |
| **Totals** | `long long`, never `int` | Task 10: a 32-bit total overflowed at 3,000,000 journeys (6,030,000,000 > 2,147,483,647) and gave 1,735,032,704 |
| **Constants** | every fare, the surcharge, the discount and the minimum balance as `constexpr` in **one place** | Task 2: one block; Task 12: a new zone needed one array element |
| **Zones** | `enum class Zone`, with a `constexpr std::array` of fares indexed by the zone | Task 2: `int x = Zone::Inner;` is a compile error; Task 12: the old `switch` returned 0 for Airport until the table replaced it |
| **Peak rule** | half-open intervals: `(h >= 8 && h < 10) \|\| (h >= 17 && h < 20)` | Task 9: boundary tests at 7, 8, 10, 17, 19, 20 all pass; 10:00 and 20:00 are always off-peak |
| **Balance rule** | `SmartCard` class with a **private** balance, `canTravel()`, `deduct()` and `recharge()` | Task 7: the procedural version reached -90999 paise; the class refused the same call and stayed at 9000 |
| **Input** | validate every value (range and type); reject, never guess | Task 8: letters and out-of-range values were rejected and the program recovered; Task 9: invalid zone, hour 25 and `abc` all rejected |
| **Testing** | a table-driven test program run before every release | Task 9: 28 of 28 tests pass; Task 12: 18 of 18 tests pass |

**Classes recommended:** `SmartCard` (private balance and the Rs 50 rule), `Pass` (two covered zones, from Task 12) and a fare function or `FareTable` that reads the constants. `Passenger` with `StudentPassenger` and `SeniorPassenger` (virtual `concessionPercent()`) is added when concessions are implemented.

---

## 2. How a fare revision will be carried out

1. Edit the one constant block, for example `FARE_PAISE` (a zone from Rs 20 to Rs 22 means changing 2000 to 2200).
2. Recompile with `g++ -std=c++17 -Wall -Wextra` and check that there are no warnings.
3. Update the expected values in the test table (Task 9 and Task 12 tests) for the changed fare.
4. Run the tests; all rows must pass before deployment.
5. Deploy the new build to the gates.
6. Keep the previous build so the change can be rolled back.

No other source line changes, because no fare value is typed anywhere else.

---

## 3. Limitations of the design

| Limitation | Effect | Possible remedy |
|---|---|---|
| Fares are compiled in | every revision needs a recompile and redeployment | read fares from a validated configuration file (section 5) |
| Concession rates (Student 50%, Senior 30%) are **assumed**, not given in the assignment | the numbers may differ in the real system | confirm the rates and put them in the constants block |
| Invalid input returns `-1` instead of throwing an exception | the caller must remember to check the value | use `std::optional` or exceptions |
| The card balance lives in memory only | nothing is saved between runs | store cards in a database |
| Two gates using the same card at the same moment are not handled | a race could allow two journeys on one balance | locking or a central server |
| Hours are integers 0 to 23 only | minutes are not modelled (8:00 is the same as 8:59) | store the time in minutes and compare against boundaries |
| `long long` has a limit of about 9.2 x 10^18 paise | not a practical limit for a city metro | none needed |

---

## 4. Does the design remain correct for the whole network?

**Yes**, for these reasons, each supported by my measurements:

1. **Range:** the network total for 3,000,000 journeys at Rs 20.10 is 6,030,000,000 paise, which is far below the `long long` limit of 9,223,372,036,854,775,807, and my experiment showed the `long long` total was exact (Task 10).
2. **Exactness:** integer paise have no rounding error at any size, unlike `double` (Task 10).
3. **Speed:** each journey is a few comparisons and one subtraction, **O(1)**, so n journeys cost **O(n)**; 3,000,000 additions took about 8.5 ms in my test.
4. **Rules:** the balance rule and the peak boundaries are covered by passing tests (Task 9: 28 of 28; Task 12: 18 of 18).

The `int` version would **not** be correct for the whole network, which is why `int` is not recommended for any total.

---

## 5. Alternative Concept and Complexity Analysis: fare table read from a configuration file

If the fare table were read from a configuration file when the gate starts, instead of being compiled into the program, the solution would be (`task11_config.cpp`):

```cpp
bool loadFares(const char* path, std::vector<long long>& fares) {
    std::ifstream in(path);
    if (!in) return false;                       // missing file
    long long v;
    while (in >> v) {
        if (v <= 0) return false;                // validate: fares must be positive
        fares.push_back(v);
    }
    return in.eof() && !fares.empty();           // stopped at end of file, not at bad text
}
```

**Measured results (my computer):**

```
./task11_config fares.txt
Loaded 3 fares from fares.txt: 1000 2000 3000
Start-up read time: 45 us
Memory for the fares: 24 bytes

./task11_config fares4.txt
Loaded 4 fares from fares4.txt: 1000 2000 3000 6000
Start-up read time: 26 us
Memory for the fares: 32 bytes

./task11_config fares_bad.txt          (contains the text "abc" in place of a fare)
Could not load fare table from fares_bad.txt - gate refuses to start

./task11_config nofile.txt
Could not load fare table from nofile.txt - gate refuses to start
```

I also loaded a file of 100,000 fares: the read took about 6.5 milliseconds and the values used 800,000 bytes (8 bytes each), which shows the cost grows in proportion to the number of values.

**Extra start-up time.** Reading z fare values takes **O(z)** time. For the real network (z = 3 or 4 zones) that is a few tens of microseconds, once per gate start. The timings vary from run to run (the first read was 31 to 46 us, the second 26 to 33 us), so the exact figure is not important: it is negligible.

**Space.** The values need **O(z)** memory: 24 bytes for 3 fares and 32 bytes for 4 fares.

**Against the cost of recompiling and redeploying after every revision:**

| Point | Compiled-in `constexpr` table | Configuration file |
|---|---|---|
| Fare revision | edit source, recompile, retest, redeploy the program | edit the text file and restart the gate |
| Start-up cost | none | a few tens of microseconds for 3 or 4 fares |
| Memory | no extra (the compiler places the values in the code) | 8 bytes per fare |
| Type checking | by the compiler | none: values are text, so the program must validate them |
| Usable as `constexpr` / `switch` label / array size | yes | **no** (values are known only at run time) |
| Risk | a wrong value is caught by the tests before release | a missing, corrupt or wrongly edited file can reach a gate, so the program must validate and refuse to start (as shown above) |
| Audit trail | the version control history of the source | needs a separate record of file changes |

**Conclusion.** The start-up cost of a configuration file is negligible, so the decision is about safety and how often fares change. For a small table that changes rarely, the **compiled-in `constexpr` table is safer** because the compiler and the tests check it before release. If revisions become frequent, a **validated configuration file** is worth its small cost, but only if the program refuses to start on a bad file, as the demonstration does.

---

## 6. Final recommendation (summary)

Use **`long long` paise, `constexpr` constants in one place, `enum class Zone` with a table of fares, a `SmartCard` class with a private balance, half-open peak intervals, validated input and a table-driven test suite.** This design was tested in Tasks 3 to 10 and 12 and remained correct for the whole network (3,000,000 journeys), and a fare revision touches one block of constants.

---

## 7. Evidence summary

- Recommendation table linked to my own experiments (section 1)
- Fare-revision procedure (section 2)
- Limitations (section 3)
- Correctness for the whole network, supported by measurements (section 4)
- Configuration-file alternative with measured start-up time, memory and failure handling (section 5)
