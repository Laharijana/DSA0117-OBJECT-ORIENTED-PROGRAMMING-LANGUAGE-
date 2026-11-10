# Task 8 - Read and Print Data Safely

**Name:** <your name>
**Register No:** <your register number>
**Course:** Object-Oriented Programming using C++ - Assignment 1 [CO1]

> Files in this folder:
> - `task08_analysis.md` - this analysis
> - `task08.cpp` - safe input with `cin`, error recovery and a formatted journey report
> - `input.txt` - test input containing letters, out-of-range values and valid values
> - `task08_output.txt` and the output screenshot - result of `./task08 < input.txt`
> - `task08_getline.cpp`, `getline_input.txt`, `task08_getline_output.txt` - alternative concept (`getline` + `stoi` in `try/catch`)

**Compile and run:**
```
g++ -std=c++17 -Wall -Wextra task08.cpp -o task08
./task08 < input.txt          # or run ./task08 and type the values yourself
g++ -std=c++17 -Wall -Wextra task08_getline.cpp -o task08_getline
./task08_getline < getline_input.txt
```

---

## 1. Reading values with `cin` and checking `cin.fail()`

When the operator types letters where a number is expected, `cin >> v` cannot convert the text. It then:
1. leaves `v` unchanged (or sets it to 0),
2. sets the **fail bit** in the stream, so `std::cin` evaluates to `false` and `cin.fail()` is `true`,
3. leaves the bad characters in the input buffer.

From this moment **every later `cin >>` also fails**, until the program repairs the stream. A program that does not check this will loop forever or use garbage values.

```cpp
if (std::cin >> v) {
    // success: v holds a valid number
} else {
    // failure: letters were typed (or input ended)
}
```

---

## 2. Clearing the error state and discarding the bad input

Recovery needs two steps, in this order:

```cpp
std::cin.clear();                                                    // 1. reset the fail bit
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 2. throw away the bad text up to the end of the line
```

- `clear()` alone is **not** enough: the letters are still in the buffer, so the next read fails again and the loop never ends.
- `ignore(...)` removes the rest of the bad line so the next read starts fresh.
- The program also stops cleanly at end of input (`cin.eof()`), so it cannot loop forever when the input file ends early.

The full function used in `task08.cpp`, with a range check for zones (0 to 2), hours (0 to 23) and the journey count (1 to 3):

```cpp
int readIntInRange(const char* prompt, int lo, int hi) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) {
            if (v >= lo && v <= hi) return v;
            std::cout << "  Out of range (" << lo << " to " << hi << "), try again.\n";
        } else {
            if (std::cin.eof()) return lo;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Not a number, try again.\n";
        }
    }
}
```

---

## 3. Formatting money with `<iomanip>`

Money is stored as integer paise and printed by splitting it into rupees and paise:

```cpp
void printMoney(long long paise) {
    std::cout << "Rs " << paise / 100 << '.' << std::setw(2) << std::setfill('0')
              << paise % 100 << std::setfill(' ');
}
```

| Manipulator | Purpose | Example |
|---|---|---|
| `setw(n)` | minimum field width for the next value | `setw(2)` makes 5 print as ` 5` |
| `setfill(c)` | padding character | `setfill('0')` makes 5 print as `05`, so 3605 paise prints as `Rs 36.05` |
| `fixed` | print floating-point numbers in fixed notation | `fixed` + `setprecision(2)` prints `36.05` |
| `setprecision(n)` | number of decimals (with `fixed`) | `setprecision(2)` |
| `left` / `right` | alignment inside a field | table columns |

Because the money is an integer, `f / 100` and `f % 100` are exact, and no rounding can occur on output.

---

## 4. Printing a neat journey report

The report is printed with `std::left`, `std::right` and `setw` so that the columns line up.

Test input used (`input.txt`, one value per line):

```
abc      <- number of journeys: letters (rejected)
5        <- number of journeys: out of range (rejected)
3        <- number of journeys: valid
two      <- journey 1 zone: letters (rejected)
2        <- journey 1 zone: Outer
9        <- journey 1 hour: 9 (peak)
1        <- journey 2 zone: Middle
25       <- journey 2 hour: out of range (rejected)
14       <- journey 2 hour: 14 (off-peak)
0        <- journey 3 zone: Inner
18       <- journey 3 hour: 18 (peak)
```

**Actual output** of `./task08 < input.txt` (the values come from a file, so the typed values are not echoed on the screen):

```
Number of journeys (1-3):   Not a number, try again.
Number of journeys (1-3):   Out of range (1 to 3), try again.
Number of journeys (1-3): 
Journey  Zone    Hour  Fare                Balance
  Zone (0=Inner 1=Middle 2=Outer):   Not a number, try again.
  Zone (0=Inner 1=Middle 2=Outer):   Hour (0-23): 1        Outer   9     Rs 36.00            Rs 64.00
  Zone (0=Inner 1=Middle 2=Outer):   Hour (0-23):   Out of range (0 to 23), try again.
  Hour (0-23): 2        Middle  14    DENIED (low balance) Rs 64.00
  Zone (0=Inner 1=Middle 2=Outer):   Hour (0-23): 3        Inner   18    Rs 12.00            Rs 52.00

Final balance: Rs 52.00  (as fixed 2 decimals: 52.00)
```

**Check by hand:**
- Journey 1: Outer 3000 + 20% (hour 9 is peak) = 3600. Balance 10000 - 3600 = 6400 = Rs 64.00. Correct.
- Journey 2: Middle 2000 (hour 14 is off-peak). 6400 - 2000 = 4400, which is below 5000, so the journey is **denied** and the balance stays Rs 64.00. Correct.
- Journey 3: Inner 1000 + 20% (hour 18 is peak) = 1200. 6400 - 1200 = 5200 = Rs 52.00, which is at least Rs 50, so it is allowed. Correct.

When you run the program by typing in a terminal, you will see your own typed values on the screen; the redirected file is used only so the test is repeatable.

**A surprise worth knowing:** `cin >> v` reads the leading digits of `12abc` and accepts 12, leaving `abc` in the buffer for the *next* read. I tested this with the input `12abc`: the journey count 12 was refused as out of range, and the leftover `abc` was then rejected by the next read. So `cin >>` can accept a prefix of a bad value (section 5 shows how the `getline` method avoids this).

---

## 5. Alternative Concept and Complexity Analysis: `getline()` with `stoi()` inside `try/catch`

If each input line were read with `std::getline()` and converted with `std::stoi()` inside `try/catch`, instead of reading numbers directly with `cin >>`, the solution would be (from `task08_getline.cpp`):

```cpp
bool parseInt(const std::string& line, int& out) {
    try {
        std::size_t used = 0;
        int v = std::stoi(line, &used);
        if (used != line.size()) return false;        // reject trailing junk such as "12abc"
        out = v;
        return true;
    } catch (const std::exception&) {                 // invalid_argument or out_of_range
        return false;
    }
}
```

**Actual output** for the input lines `12`, `abc`, `12abc`, `99999999999`, `-4`, `7`:

```
"12" -> OK 12
"abc" -> invalid, skipped
"12abc" -> invalid, skipped
"99999999999" -> invalid, skipped
"-4" -> OK -4
"7" -> OK 7
```

**Time.** Processing a line of length L takes **O(L)** in both methods, because every character must be examined once.

**Space.** `cin >> v` needs only O(1) extra space. `getline` stores the whole line in a `std::string`, so it needs a buffer of **O(L)** extra space (for a line of a few characters this is tiny).

**How each recovers from invalid input:**

| Point | `cin >> v` | `getline` + `stoi` + `try/catch` |
|---|---|---|
| Error signal | stream fail bit | exception (`invalid_argument`, `out_of_range`) |
| Recovery | `clear()` then `ignore()` (two steps, easy to forget one) | nothing to repair: the line is already consumed |
| `12abc` | accepts 12, leaves `abc` in the buffer | rejected, because the parsed length is checked |
| Out-of-range number such as 99999999999 | fail bit set | `out_of_range` exception |
| Code size | shorter | longer (parse function and `try/catch`) |

**Conclusion.** The speed is the same, **O(L)**. The `getline` method is more robust because it works one whole line at a time and can reject trailing junk, while the `cin >>` method is shorter but needs the `clear()` and `ignore()` recovery steps. For a gate program that must never accept a half-valid value, the `getline` method is the safer choice.

---

## 6. Evidence summary

- Explanation of `cin.fail()`, `clear()` and `ignore()` (sections 1 and 2)
- `<iomanip>` formatting of money (section 3)
- Program, test input, actual output and hand check showing recovery from letters, out-of-range values and a low-balance denial (section 4)
- `getline` alternative with measured output and a comparison table (section 5)
