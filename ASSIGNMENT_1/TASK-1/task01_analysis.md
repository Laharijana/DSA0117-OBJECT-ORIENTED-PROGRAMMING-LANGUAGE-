# Task 1 - Understand the Problem and Identify the Objects

**Name:** <your name>
**Register No:** <your register number>
**Course:** Object-Oriented Programming using C++ - Assignment 1 [CO1]
**Scenario:** Namma Metro Smart-Card Fare System

> Files in this folder:
> - `task01_analysis.md` - this analysis (the main answer for Task 1)
> - `uml_diagram.png` - UML class diagram
> - the C++ file - the procedural example used for the "Alternative Concept" part (section 7)
> - the output screenshot - output of that procedural example

---

## 1. Objects, their data and behaviour

| Object | Data | Behaviour | Why it is an object |
|---|---|---|---|
| SmartCard | balance (in paise), card id | canTravel(), deduct(), recharge(), balance() | It owns the money and must protect the rule that the balance never falls below Rs 50 after a journey. |
| Passenger | name, category (Regular, Student, Senior) | concessionPercent() | The concession depends on who the person is, not on the trip. |
| Journey | entry zone, exit zone, hour, weekend flag | farthestZone(), isPeak(), fare() | It groups all the facts needed to price one trip. |
| Zone | Inner, Middle, Outer | none (an enum class) | A fixed set of named values; a separate type stops a zone being mixed up with an ordinary number. |
| FareTable | base fare per zone, surcharge %, minimum balance | baseFare(zone) | Keeps every fare number in one place, so a fare revision is made in one place only. |

---

## 2. UML class diagram

![UML class diagram](uml_diagram.png)

Relationships shown in the diagram:
- A **Passenger** owns one **SmartCard** (association).
- A **SmartCard** pays for a **Journey**.
- A **Journey** uses a **Zone** and reads fares from the **FareTable**.
- **StudentPassenger** and **SeniorPassenger** inherit from **Passenger** (generalisation) and override `concessionPercent()`.
- In the Day-4 change (Task 12), a SmartCard may hold one **Pass**, and a Pass covers two zones.

---

## 3. Procedural style versus object-oriented style

**Procedural style.** The program would use global variables such as `balance` and `fares[]`, and free functions such as `computeFare()` and `deduct()`. Because the data is global, any function can change `balance`, so the negative-balance bug could come from anywhere in the program. The fare values are also likely to be typed in several places, which is exactly the problem described in the scenario.

**Object-oriented style.** The data and the functions that protect it are packaged together in a class. The balance is private and only `deduct()` changes it, after checking the rule. The rule lives in one place, so a bug can only come from one class. The program also reads like the real system: a card pays for a journey.

**What changes:**

| Point | Procedural | Object-oriented |
|---|---|---|
| Where the balance lives | global variable | private member of SmartCard |
| Who can change it | any function | only deduct() and recharge() |
| Where the Rs 50 rule is checked | wherever the programmer remembers | once, inside deduct() |
| Where fare numbers live | possibly several places | one FareTable / constexpr block |
| Cost of changing a rule | search the whole program | edit one class or constant |

---

## 4. OOP principles and where each appears in this system

- **Encapsulation:** SmartCard keeps `balance_` private. Only `deduct()` and `recharge()` can change it, so the rule "balance never below Rs 50 after a journey" cannot be bypassed.
- **Abstraction:** gate code calls `card.deduct(fare)` without knowing how the Rs 50 rule is checked or how the balance is stored.
- **Inheritance:** StudentPassenger and SeniorPassenger derive from Passenger and reuse its name and category data. A monthly pass could also derive from a common travel-authority base class.
- **Polymorphism:** a virtual `concessionPercent()` returns 0, 50 or 30 depending on the passenger type, so the fare code does not need an if-else chain on the category.

---

## 5. Rules every correct journey must satisfy

1. **The balance after payment is at least 5000 paise (Rs 50).** This also makes a negative balance impossible.
   *Justification:* it is the central business rule and the cause of the reported negative-balance bug.
2. **Fare = base fare of the farthest zone, plus 20% only in peak hours.**
   *Justification:* this is the pricing rule given in the scenario.
3. **Peak hours are 08:00 up to but not including 10:00, and 17:00 up to but not including 20:00.**
   *Justification:* half-open intervals remove the inconsistency where 10 AM and 8 PM were sometimes treated as peak and sometimes not.
4. **All money is stored and calculated as exact integer paise.**
   *Justification:* this removes the "fare off by a paisa" errors that come from floating-point rounding.
5. **The zone and hour must be valid, and a recharge amount must be positive.**
   *Justification:* invalid input must be rejected before it can corrupt the balance.

---

## 6. Assumptions

- Money is held in integer paise (Rs 1 = 100 paise).
- The concession percentages are not given in the assignment, so I assume Student 50% and Senior citizen 30%, applied after the peak surcharge. They can be changed in one constant.
- Peak intervals are half-open, as in rule 3.

---

## 7. Alternative Concept and Complexity Analysis: purely procedural solution

If the fare system were written in a purely procedural style (global variables and free functions) instead of SmartCard, Journey and FareTable classes, the solution would look like this:

```cpp
long long balance = 10000;                       // global variable
const long long fares[] = {1000, 2000, 3000};

long long computeFare(int zone, bool peak) {
    long long f = fares[zone];
    if (peak) f += f * 20 / 100;
    return f;
}

void deduct(long long f) { balance -= f; }       // no check: balance can go negative
```

(The full runnable version of this example is the C++ file in this folder, with its output screenshot.)

**Time complexity.** One journey needs a table lookup, a few comparisons and one subtraction, so the time per journey is **O(1)** in both the procedural and the object-oriented style. Processing n journeys is O(n) in both.

**Space complexity.** Each card needs one stored balance, so the memory per card is **O(1)** in both styles. Class member functions add no per-card memory.

**Comparison of code to change when one fare rule changes.**

| Change | Procedural | Object-oriented |
|---|---|---|
| Minimum balance changes | every place that touches `balance` must be found and edited: O(c) places, where c is the number of call sites | one constant or the single `canTravel()` function: O(1) places |
| A fare changes | fares may be typed in many places | one entry in the FareTable / constexpr block |

**Conclusion.** Speed and memory are the same in both styles, so the choice is made on correctness and maintainability. The object-oriented design is better because it protects the balance with a private member and keeps each rule in one place.

---

## 8. Evidence

- Objects, data and behaviour table (section 1)
- UML class diagram (`uml_diagram.png`)
- Rules and assumptions (sections 5 and 6)
- Procedural example code and its output screenshot (section 7)
