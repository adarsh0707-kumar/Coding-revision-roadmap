# C++ Level 2 — Interview-Ready Handbook

> Reviewed solutions with deep explanations · C++17
> Every program is compiled with `g++ -std=c++17 -Wall -Wextra -Wpedantic` and tested.
> **Status:** all 50 questions reviewed (Modules 1–7).

**Template for each question:** Review of your solution → Problem → Concepts → How to think → Solution → Dry run → Edge cases → Complexity → Pitfalls → Follow-ups.

---

# PART 0 — ARRAY CONCEPTS (read once)

## A1. What an array is

```cpp
int arr[5] = {10, 20, 30, 40, 50};   // 5 ints stored side by side in memory
//             [0] [1] [2] [3] [4]   // zero-based: first index 0, last index n-1
```

- Elements are **contiguous**, so `arr[i]` is computed as "start address + i × sizeof(int)". Access is O(1).
- **No bounds checking.** `arr[5]` or `arr[-1]` is undefined behavior (it may crash, or silently read garbage). *Every* loop bound is your responsibility.
- The size is fixed at compile time for a plain array. For a size known only at run time, use `std::vector<int>` (see the follow-ups).

## A2. Getting the size, and the "array decay" trap

```cpp
int arr[] = {1, 2, 3, 4};
int n = static_cast<int>(std::size(arr));            // 4   (C++17, needs <iterator>)
int n2 = sizeof(arr) / sizeof(arr[0]);               // 4   (works only where `arr` is a real array)
```

When you pass an array to a function it **decays to a pointer**, and all size information is lost:

```cpp
void f(int arr[]) {                 // really: void f(int* arr)
    sizeof(arr);                    // size of a POINTER (8 on 64-bit), NOT the array!
}
```

Therefore: **always pass the size as a separate parameter**: `void f(const int arr[], int n)`. Use `const` when the function only reads the array; the compiler then stops you from modifying it by accident.

## A3. `int` vs `size_t` (the source of most `-Wsign-compare` warnings)

`sizeof` and `std::size` return `size_t`, an **unsigned** type. Comparing it with a signed `int` loop counter triggers a warning, and mixing them is dangerous:

```cpp
size_t n = 0;
for (size_t i = 0; i <= n - 1; i++) { }   // n - 1 wraps to 18446744073709551615 → effectively infinite loop
```

Safe habits: convert once (`int n = static_cast<int>(std::size(arr));`) and keep everything `int`, **or** use a range-for loop (`for (int x : arr)`) when you do not need the index.

## A4. Empty-input rules

Almost every array algorithm needs a decision for `n == 0`:

| Algorithm | What to do for an empty array |
|---|---|
| max / min | there is no answer: return a "found" flag, or report an error |
| sum | `0` (empty sum) |
| average | undefined (division by zero): report an error |
| search | not found |
| reverse / dedupe | nothing to do |

**Never read `arr[0]` before checking `n > 0`.**

## A5. Sentinel values are fragile

Using `INT_MIN` as "not set yet" is a common shortcut, but `INT_MIN` can also be a *real* value in the array. The robust patterns are:

1. **Initialize from the first element** (`largest = arr[0]`), or
2. Keep a separate **`bool found`** flag, or
3. Return `std::optional<int>` (C++17).

## A6. Two-pointer technique (appears in Q4, Q8, and many later problems)

Two indices walk the array, usually to work **in place** in O(n) time and O(1) extra memory:

- **Opposite ends** (`left`, `right` moving toward each other): reverse, palindrome check, two-sum on a sorted array.
- **Reader / writer** (`i` scans, `k` marks where to write): remove duplicates, move zeros, filter.

## A7. Review summary of your first 8 solutions

| Q | Verdict | Main finding |
|---|---|---|
| 1 | ✅ correct | Hard-coded array; make it a function and handle `n == 0` |
| 2 | ✅ correct, 1 warning | `-Wsign-compare` (`int` vs `size_t`) |
| 3 | ✅ correct | `int` sum can overflow; use `long long` + `double`; guard `n == 0` |
| 4 | 🐞 works, but unsafe swap | Arithmetic swap overflows (undefined behavior, caught by UBSan) |
| 5 | 🐞 edge-case bug | `INT_MIN` sentinel fails for `{5, INT_MIN}`; message text wrong; missing `<iterator>` |
| 6 | ✅ correct | Negative numbers handled correctly; could be a function |
| 7 | ✅ correct, 1 warning | `-Wsign-compare`; make it a function that returns the index |
| 8 | 🐞 changes the problem | The question gives a **sorted** array; you sorted an unsorted one with O(n²) bubble sort. Also a sign-compare warning. |

**What you did well:** correct core algorithms; `std::size`, range-for and `static_cast`-style thinking; handling the "all elements equal" case in Q5; the early `break` in Q7; the last-element handling in Q8.

**The pattern to fix:** your programs work for the *one hard-coded array*, but interviews test *functions on many inputs*. Write `solve(arr, n)` and test it with empty, single-element, negative, duplicate and extreme values.

### Round 2 update (you re-sent Q1–Q8 and added Q9–Q11)

| Q | Verdict now | Note |
|---|---|---|
| 1, 3, 6 | ✅ unchanged | still correct (Q3: still `int` sum + `float`) |
| 2, 7 | ✅ unchanged | the `-Wsign-compare` warning is still there |
| 4 | ✅ fixed | temp-variable swap, no overflow |
| 5 | 🐞 **regression** | fixed `{5, INT_MIN}` but now `{7,7,7}` and `{3,3}` wrongly print `-2147483648`. See Q5. |
| 8 | ✅ fixed | now the true O(n) two-pointer solution |
| 9 | ✅ correct algorithm | three-reversal rotation works for left and right; small output and edge-case issues |
| 10 | ✅ correct | stable, O(n), O(1) |
| 11 | ✅ correct | polish: `empty()`, no printing inside the function, UTF-8 note |
| 12 | ⬜ empty | only the comment was sent |

**The most valuable lesson of round 2:** when you fix a bug, **re-run every earlier test case**, not just the one that failed. Fixing `{5, INT_MIN}` broke `{7,7,7}`. Keep a small list of edge-case inputs per problem and run all of them after every change (this is *regression testing*).

### Round 3 update (Q12–Q30)

| Q | Verdict | Main finding |
|---|---|---|
| 12 | ✅ | Empty-string rule inconsistent; decide strict vs relaxed |
| 13 | ✅ | `isalpha` needs `unsigned char`; sign-compare warning |
| 14 | 🐞 | Only `' '` counted as whitespace (`hello<TAB>world` → 1 word) |
| 15 | ✅ | Correct but O(n²); use a count table (O(n)) |
| 16 | ✅ | Algorithm good; strings were hard-coded, rules unstated |
| 17 | ✅ | Correct and clean |
| 18 | ✅ | Correct; hard-coded input |
| 19 | ✅ | Works, but functions print instead of **returning** results |
| 20 | 🐞 **does not compile** | Q19 code pasted in, so two `main` functions. The GCD/LCM part is excellent |
| 21 | ✅ | Correct; move printing into a function |
| 22 | ✅ | Works; show inner values and addresses to make the demo convincing |
| 23 | ✅ | Correct |
| 24 | ✅ | Good tag-dispatch idea; use `enum class` and validate input |
| 25 | 🐞 | Never prints the variable's own value and `&val`; unused variable |
| 26 | ✅ | Correct; show the result in `main` |
| 27 | ✅ | Correct; the idiomatic form is `[first, last)` |
| 28 | ✅ | Correct; return a pointer to the maximum |
| 29 | ✅ | Careful code; silent failure on short input |
| 30 | 🐞 **incomplete** | Missing requirement 2 (pointer to an integer variable) and 5 (dangling pointer demo) |

**What round 3 shows:** your code quality is rising (overflow-safe GCD/LCM, exception handling, `optional`). The remaining misses are about **process**: compile the file before sending it (Q20), and tick off every bullet of the problem statement (Q25, Q30).

### Round 4 update (Q31–Q37, recursion)

| Q | Verdict | Main finding |
|---|---|---|
| 31 | ✅ | Correct; put the overflow guard next to the function, not only in `main` |
| 32 | 🐞 | No overflow guard (`F(94)` silently wraps); huge input → `num + 1` overflow and uncaught `bad_alloc` |
| 33 | ✅ | Correct; the `INT_MIN`-safe absolute value is excellent |
| 34 | ✅ | Correct; hide the internal `left` parameter behind a wrapper |
| 35 | 🐞 | Fast exponentiation is right, but `double` output prints `1.04858e+06`; no integer overflow detection |
| 36 | ✅ | Excellent: half-open `[low, high)`, no overflow or underflow |
| 37 | 🐞 | Base case `n == 1` only: `n = 0` recurses until the stack overflows (segfault) |

**What round 4 shows:** your recursion structure is strong (base cases, shrinking arguments, memoization, fast power, Hanoi). The misses are all at the **boundaries of the input**: the value just past the limit (`F(94)`), the empty case (`n = 0`), and the formatting of big results. Before submitting any recursive function, test `0`, `1`, the largest valid value and one past it.

### Round 5 update (Q38–Q50, searching, sorting, matrices, STL)

| Q | Verdict | Main finding |
|---|---|---|
| 38 | ✅ | Correct; add the sortedness precondition and a first-occurrence variant |
| 39 | ✅ | No early exit: 28 comparisons even on sorted input (7 with a `swapped` flag) |
| 40 | ✅ | Correct; know that it is **not stable** (demonstrated) |
| 41 | 🐞 | Correct sort, but the required tests on sorted / reversed / random input were not written |
| 42 | ✅ | Correct merge; the function prints instead of returning the result |
| 43 | ✅ | Correct; two vectors allocated in every merge, `merge` name vs `std::merge` |
| 44 | ✅ | Excellent (random pivot, smaller-side recursion); O(n²) when elements are equal: 199,990,000 comparisons for n = 20,000 |
| 45 | ✅ | Correct; exceptions never caught, so a mismatch aborts (exit 134) |
| 46 | ✅ | Correct and cache-friendly; ragged input causes a heap-buffer-overflow |
| 47 | ✅ | Correct; `unordered_map` iteration order is unspecified |
| 48 | ✅ | Correct and idiomatic; know the `sort` + `unique` alternative |
| 49 | ✅ | Correct on all 15 cases I tried |
| 50 | 🐞 | Hash version misses pairs when the array has duplicates (`{3,3,3}`: 2 pairs instead of 3); `int` overflow; no "no pair" message |

**What round 5 shows:** your algorithm knowledge is solid: every sort and search is correct. The remaining issues are the ones that separate a working answer from an interview-ready one: **duplicates** (Q44, Q50), **unhandled failure paths** (Q45, Q46), and **completing every requirement** (Q41).

---

# MODULE 1 — ARRAYS

---

## Q1. Find the Largest Element

**Review of your solution:** ✅ Correct and efficient (one pass, no sorting). Starting from `arr[0]` instead of `INT_MIN` is the right choice. To make it interview-ready: wrap it in a function and decide what happens when the array is empty.

**Problem:** Find the largest element of an integer array without sorting.

**Concepts:** running maximum, empty-input handling (A4), array passed with its size (A2).

**How to think**
1. *Brute force:* sort, then take the last element: O(n log n), and it modifies the data.
2. *Better:* scan once, remembering the biggest value seen so far. Every element is looked at exactly once: O(n).
3. Initialize with `arr[0]`, **not** `0` (all-negative arrays would break) and not `INT_MIN` (fragile, see A5).

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

// Returns false if the array is empty; otherwise stores the maximum in `result`.
bool findLargest(const int arr[], int n, int &result) {
    if (n <= 0) return false;
    int largest = arr[0];                    // start from a REAL element
    for (int i = 1; i < n; i++)
        if (arr[i] > largest)
            largest = arr[i];
    result = largest;
    return true;
}

int main() {
    int a[] = {1, 3, 4, 5, 9, 4, 6, 4, 0, 3};
    int b[] = {-8, -3, -20};
    int c[] = {42};

    int result;
    if (findLargest(a, static_cast<int>(size(a)), result)) cout << "Largest: " << result << '\n';
    if (findLargest(b, static_cast<int>(size(b)), result)) cout << "Largest: " << result << '\n';
    if (findLargest(c, static_cast<int>(size(c)), result)) cout << "Largest: " << result << '\n';
    if (!findLargest(a, 0, result)) cout << "Empty array: no largest element\n";
    return 0;
}
```

**Dry run (`{3, 9, 4}`):** `largest = 3` → `9 > 3` → `largest = 9` → `4 > 9`? no → **9**.

| Input | Output |
|---|---|
| `{1,3,4,5,9,4,6,4,0,3}` | `9` |
| `{-8,-3,-20}` | `-3` (a `0` start would wrongly give `0`) |
| `{42}` | `42` |
| `{}` | no largest element |

**Complexity:** O(n) time, O(1) extra space. You must examine every element, so O(n) is optimal.

**Pitfalls:** `largest = 0` fails for negatives; `for (i = 0; ...)` with `largest = arr[0]` is harmless but does one wasted comparison; reading `arr[0]` before checking `n > 0`.

**Follow-ups**
- *Return the index too?* Track `maxIndex` and update it with `largest`.
- *Standard library?* `*max_element(arr, arr + n)` (`<algorithm>`), same O(n).
- *Find max and min in one pass?* Keep both; the optimized pairwise version uses about `3n/2` comparisons.
- *Largest in a sorted array?* The last element: O(1).

---

## Q2. Find the Smallest Element

**Review of your solution:** ✅ Logic correct. One compiler warning under `-Wall -Wextra`: `i < sizeof(arr)/sizeof(arr[0])` compares a signed `int` with an unsigned `size_t` (see A3). Compute the size once into an `int` (as you did in Q1 and Q3).

**Problem:** Find the minimum element of an array.

**Concepts:** mirror of Q1, `size_t` vs `int`.

**How to think:** Identical to Q1 with `<` instead of `>`. Start from `arr[0]`; update when a smaller value appears.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

bool findSmallest(const int arr[], int n, int &result) {
    if (n <= 0) return false;
    int smallest = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < smallest)
            smallest = arr[i];
    result = smallest;
    return true;
}

int main() {
    int a[] = {4, 7, 9, 9, 0, 7, -2, -1, 67, 6};
    int b[] = {5, 5, 5};

    int result;
    if (findSmallest(a, static_cast<int>(size(a)), result)) cout << "Smallest: " << result << '\n';
    if (findSmallest(b, static_cast<int>(size(b)), result)) cout << "Smallest: " << result << '\n';
    if (!findSmallest(a, 0, result)) cout << "Empty array: no smallest element\n";
    return 0;
}
```

| Input | Output |
|---|---|
| `{4,7,9,9,0,7,-2,-1,67,6}` | `-2` |
| `{5,5,5}` | `5` |
| `{}` | no smallest element |

**Why your warning mattered:** with `i < sizeof(...)`, the compiler converts `i` to unsigned. If `i` were ever negative it would become a huge number. That's harmless in this loop, but the habit causes real bugs in `n - 1` expressions (A3).

**Complexity:** O(n) time, O(1) space.

**Follow-ups**
- *Find both min and max?* One loop updating both; do not run two separate passes if the interviewer asks for efficiency.
- *Second smallest?* Same technique as Q5.

---

## Q3. Calculate Array Sum and Average

**Review of your solution:** ✅ Correct (`float(sum) / arrSize` correctly avoids integer division). Improvements: (1) a sum of many `int`s can overflow, so accumulate in `long long`; (2) `double` is more precise than `float` (about 15 vs 7 digits); (3) an empty array makes `sum / 0` undefined.

**Problem:** Calculate the sum and average of all elements.

**Concepts:** accumulator (C7), integer division trap, overflow, `double`.

**How to think**
- Sum: start at 0 (the identity for addition) and add each element.
- Average = `sum / n`. If both operands are integers the division **truncates** (`7 / 2 == 3`), so convert one operand to `double` **before** dividing.
- The sum of `n` values of up to ~2·10⁹ needs 64 bits.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

long long arraySum(const int arr[], int n) {
    long long sum = 0;                         // wide accumulator
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

bool arrayAverage(const int arr[], int n, double &avg) {
    if (n <= 0) return false;                  // would divide by zero
    avg = static_cast<double>(arraySum(arr, n)) / n;
    return true;
}

int main() {
    int a[] = {1, 3, 4, 5, 9, 4, 6, 33, 0, 3, -4};
    int big[] = {2000000000, 2000000000, 2000000000};   // sum 6e9 does not fit in int

    cout << "Sum: " << arraySum(a, static_cast<int>(size(a))) << '\n';

    double avg;
    if (arrayAverage(a, static_cast<int>(size(a)), avg)) cout << "Average: " << avg << '\n';

    cout << "Big sum: " << arraySum(big, static_cast<int>(size(big))) << '\n';
    if (!arrayAverage(a, 0, avg)) cout << "Empty array: average undefined\n";
    return 0;
}
```

**Dry run (`{2, 3, 5}`):** `sum = 0 → 2 → 5 → 10`; `10 / 3.0 = 3.33333`.

| Input | Output |
|---|---|
| `{1,3,4,5,9,4,6,33,0,3,-4}` | sum `64`, average `5.81818` |
| `{2e9, 2e9, 2e9}` | sum `6000000000` (an `int` sum overflows: undefined behavior) |
| `{}` | sum `0`, average undefined |
| `{1,2}` | average `1.5` (integer division would give `1`) |

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** `int avg = sum / n;` loses the fraction; casting **after** dividing (`(double)(sum / n)`) is too late; `float` loses precision on large sums.

**Follow-ups**
- *Print 2 decimals?* `cout << fixed << setprecision(2) << avg;` (`<iomanip>`).
- *Standard library?* `accumulate(arr, arr + n, 0LL)` from `<numeric>` (note the `0LL` so the sum is `long long`; plain `0` would accumulate in `int`).
- *Average without overflow for huge values?* Use `long double` or keep a running mean.

---

## Q4. Reverse an Array

**Review of your solution:** 🐞 The reversal logic (two pointers `left`/`right`) is exactly right. The problem is your custom `swap` using `a = a + b; b = a - b; a = a - b;`. If `a + b` exceeds `INT_MAX` it is **signed overflow, which is undefined behavior** (I confirmed it with UBSan: `INT_MAX` and `1` trigger runtime errors). It also hides the standard `std::swap`. Use a temporary variable or `std::swap`. A tiny style point: the output has no final newline.

**Review of your revised version (round 2):** ✅ Fixed. You replaced the arithmetic swap with a temporary variable, which is correct and safe for all values. Two tiny notes: naming your own function `swap` hides the idea of `std::swap` (it works because you don't use `using namespace std`; calling it `swapInts` or just using `std::swap` is clearer), and the output has no final newline.

**Problem:** Reverse an array in place, without a second array.

**Concepts:** two pointers from opposite ends (A6), in-place algorithms, safe swapping (Q25 of Level 1).

**How to think:** The first element swaps with the last, the second with the second-to-last, and so on. Stop when the pointers meet: only **n/2** swaps are needed. Swapping all the way (until `left > right`) would reverse the array twice and undo the work.

**Solution**
```cpp
#include <iostream>
#include <iterator>
#include <utility>        // std::swap
using namespace std;

void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {                // strict <: the middle element stays put
        swap(arr[left], arr[right]);      // safe for any values, no overflow
        left++;
        right--;
    }
}

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';
}

int main() {
    int a[] = {1, 3, 4, 5, 9, 4, 6, 34, 0, 3};   // even length
    int b[] = {1, 2, 3, 4, 5};                   // odd length
    int c[] = {7};
    int big[] = {2147483647, 1};                 // your arithmetic swap breaks here

    reverseArray(a, static_cast<int>(size(a)));   printArray(a, static_cast<int>(size(a)));
    reverseArray(b, static_cast<int>(size(b)));   printArray(b, static_cast<int>(size(b)));
    reverseArray(c, static_cast<int>(size(c)));   printArray(c, static_cast<int>(size(c)));
    reverseArray(big, static_cast<int>(size(big))); printArray(big, static_cast<int>(size(big)));
    reverseArray(a, 0);                          // empty: nothing happens
    return 0;
}
```

**Dry run (`{1, 2, 3, 4, 5}`):**

| step | left | right | action | array |
|---|---|---|---|---|
| 1 | 0 | 4 | swap 1 ↔ 5 | `5 2 3 4 1` |
| 2 | 1 | 3 | swap 2 ↔ 4 | `5 4 3 2 1` |
| 3 | 2 | 2 | `left < right` false → stop | `5 4 3 2 1` |

| Input | Output |
|---|---|
| `{1,2,3,4,5}` | `5 4 3 2 1` |
| `{1,2,3,4}` | `4 3 2 1` |
| `{7}` | `7` |
| `{2147483647, 1}` | `1 2147483647` (safe) |
| `{}` | unchanged |

**Complexity:** O(n) time (n/2 swaps), O(1) extra space.

**Why the arithmetic swap is a bad idea:** it needs `a + b` to fit in `int`; it breaks if both references name the same variable (`a = a + a; b = a - b` → `a` becomes 0); and modern compilers generate *worse* code for it than for a temp-variable swap.

**Pitfalls:** `left <= right` (harmless but pointless: it swaps the middle element with itself); looping to `n` instead of `n/2` (reverses twice); using `sizeof` inside the function (A2).

**Follow-ups**
- *Standard library?* `reverse(arr, arr + n)` from `<algorithm>`.
- *Reverse only part of an array (indices `l..r`)?* Same loop with `left = l`, `right = r`. This is the building block of **array rotation** (Q9).
- *Why not reverse with a second array?* O(n) extra memory; the question demands in place.

---

## Q5. Find the Second-Largest Element

**Review of your solution:** 🐞 The idea (track `largest` and `secondLargest` in one pass, ignore duplicates with `num != largest`) is right, and your "all elements equal" message shows good edge-case thinking. Problems:

1. **`INT_MIN` sentinel bug.** For `{5, INT_MIN}` the real second-largest *is* `INT_MIN`, but your code reports "no second largest". I ran it: it returns `-2147483648` and treats it as "not found". Same for `{INT_MIN, 5}`.
2. The error message says "must be greater than 2" but the check `arrSize < 2` means "at least 2".
3. `std::size` lives in `<iterator>`, which you did not include. It compiles here only because `<iostream>` happens to pull it in.
4. The `arrSize < 2` check can never trigger on a hard-coded array. It belongs inside a function.

**Review of your revised version (round 2):** 🐞 You fixed the `{5, INT_MIN}` case by adding a `foundSecond` flag, but the new code introduced a **regression**. It now prints a wrong answer when all elements are equal, which your *first* version handled correctly. I ran your exact logic:

| Input | Your revised code | Correct |
|---|---|---|
| `{5, INT_MIN}` | `-2147483648` ✓ | `INT_MIN` |
| `{7, 7, 7}` | `Second largest: -2147483648` ✗ | no second largest |
| `{3, 3}` | `Second largest: -2147483648` ✗ | no second largest |
| `{9, 9, 5}`, `{-3, -7}`, `{0,3,1,9,5,7,4,6,8,9}` | correct | |

**Why:** `largest` starts as the placeholder `INT_MIN`. The very first element is always `> INT_MIN`, so the first branch runs: it copies the *placeholder* into `secondLargest` and sets `foundSecond = true`. The flag now claims "a second value exists" when only a placeholder was copied. (`{5, INT_MIN}` came out right only by coincidence, because INT_MIN really was the answer.)

**The fix:** remove the placeholder entirely. Start `first` from `arr[0]` and loop from index 1, as in the solution below. A flag is then only set when a *real* element becomes the runner-up.


**Problem:** Find the second-largest **distinct** element without sorting.

**Concepts:** two running maxima, strict comparisons for distinctness, `bool found` instead of a sentinel (A5).

**How to think**
- "Distinct" means `{9, 9, 5}` has second-largest `5`, and `{7, 7}` has none.
- Keep `first` (largest) and `second` (largest value strictly smaller than `first`).
- For each element `x`:
  - `x > first` → the old `first` becomes `second`; `x` becomes `first`.
  - `x < first` and (`second` not set yet or `x > second`) → `x` becomes `second`.
  - `x == first` → ignore (not distinct).
- Use a `hasSecond` flag so no value is "reserved" as a marker.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

// Returns false if there is no second-largest DISTINCT value.
bool secondLargest(const int arr[], int n, int &result) {
    if (n < 2) return false;

    int first = arr[0];
    int second = 0;
    bool hasSecond = false;

    for (int i = 1; i < n; i++) {
        int x = arr[i];
        if (x > first) {
            second = first;                 // old maximum is now the runner-up
            hasSecond = true;
            first = x;
        } else if (x < first && (!hasSecond || x > second)) {
            second = x;
            hasSecond = true;
        }                                   // x == first: duplicate, ignore
    }

    if (!hasSecond) return false;
    result = second;
    return true;
}

static void test(const char *label, const int arr[], int n) {
    int r;
    cout << label << " -> ";
    if (secondLargest(arr, n, r)) cout << r << '\n';
    else                          cout << "no second largest\n";
}

int main() {
    int a[] = {0, 3, 1, 9, 5, 7, 4, 6, 8, 9};
    int b[] = {9, 9, 5};
    int c[] = {7, 7, 7};
    int d[] = {5, -2147483647 - 1};         // contains INT_MIN as a real value
    int e[] = {-3, -7};
    int f[] = {1};

    test("{0,3,1,9,5,7,4,6,8,9}", a, static_cast<int>(size(a)));
    test("{9,9,5}", b, static_cast<int>(size(b)));
    test("{7,7,7}", c, static_cast<int>(size(c)));
    test("{5,INT_MIN}", d, static_cast<int>(size(d)));
    test("{-3,-7}", e, static_cast<int>(size(e)));
    test("{1}", f, static_cast<int>(size(f)));
    return 0;
}
```

**Dry run (`{3, 9, 9, 5}`):**

| x | action | first | second |
|---|---|---|---|
| 3 (init) | `first = 3` | 3 | none |
| 9 | `9 > 3`: second = 3, first = 9 | 9 | 3 |
| 9 | equal to first: ignore | 9 | 3 |
| 5 | `5 < 9` and `5 > 3`: second = 5 | 9 | 5 |

Result: **5**.

| Input | Output |
|---|---|
| `{0,3,1,9,5,7,4,6,8,9}` | `8` |
| `{9,9,5}` | `5` |
| `{7,7,7}` | no second largest |
| `{5, INT_MIN}` | `INT_MIN` (your sentinel version said "none") |
| `{-3,-7}` | `-7` |
| `{1}` | no second largest |

**Complexity:** O(n) time, one pass; O(1) space.

**Pitfalls:** using `>=` for the second comparison lets a duplicate of the maximum become the second largest; initializing both to `INT_MIN`; forgetting `n < 2`.

**Follow-ups**
- *k-th largest?* Min-heap of size k (`priority_queue`): O(n log k); or `nth_element` for average O(n).
- *Why not sort?* O(n log n) and mutates the input; a single pass is O(n).
- *Using `std::optional<int>` instead of the `bool` + reference?* Cleaner in modern C++: `optional<int> secondLargest(...)`.

---

## Q6. Count Even and Odd Elements

**Review of your solution:** ✅ Correct, including negative numbers. (`-3 % 2` is `-1`, which is `!= 0`, so it lands in your `else` branch: odd.) Only polish: put it in a function and use `'\n'`.

**Problem:** Count the even and odd values in an array.

**Concepts:** counters, parity (Level 1 Q3), range-based `for`.

**How to think:** One pass, one `if/else` per element. Because every integer is either even or odd, `countEven + countOdd == n` always: a handy self-check.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

void countEvenOdd(const int arr[], int n, int &evenCount, int &oddCount) {
    evenCount = 0;
    oddCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) evenCount++;   // 0 and negative evens included
        else                 oddCount++;    // -3 % 2 == -1, so != 0 -> odd
    }
}

int main() {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
    int b[] = {-4, -3, 0};
    int c[] = {2, 4, 6};

    int even, odd;
    countEvenOdd(a, static_cast<int>(size(a)), even, odd);
    cout << "Even: " << even << ", Odd: " << odd << '\n';
    countEvenOdd(b, static_cast<int>(size(b)), even, odd);
    cout << "Even: " << even << ", Odd: " << odd << '\n';
    countEvenOdd(c, static_cast<int>(size(c)), even, odd);
    cout << "Even: " << even << ", Odd: " << odd << '\n';
    countEvenOdd(a, 0, even, odd);
    cout << "Empty -> Even: " << even << ", Odd: " << odd << '\n';
    return 0;
}
```

| Input | Even | Odd |
|---|---|---|
| `{0,1,2,3,4,5,6,7,8,9,11}` | 5 | 6 |
| `{-4,-3,0}` | 2 | 1 |
| `{2,4,6}` | 3 | 0 |
| `{}` | 0 | 0 |

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** testing odd with `arr[i] % 2 == 1` (fails for negative odds: `-3 % 2 == -1`); forgetting to reset counters to 0 (here the function does it for you).

**Follow-ups**
- *Bitwise parity?* `arr[i] & 1` is 1 for odd, including negatives in two's complement.
- *Standard library?* `count_if(arr, arr + n, [](int x){ return x % 2 == 0; })`.
- *Count positives, negatives and zeros?* Same pattern with three counters.

---

## Q7. Linear Search

**Review of your solution:** ✅ Correct: first-occurrence semantics, `-1` as the "not found" marker, early `break`. Improvements: (1) `i < std::size(arr)` gives a `-Wsign-compare` warning; (2) a function `int linearSearch(arr, n, target)` is what the question literally asks for ("return its index"); (3) the interactive prompt makes it impossible to test automatically.

**Problem:** Find a target element and return its index, or indicate that it is absent.

**Concepts:** sequential search, sentinel return value (`-1` is a safe "not found" because valid indices are ≥ 0), early exit.

**How to think:** Check elements from left to right; the moment one equals the target, return its index. If the loop finishes, nothing matched. Returning *inside* the loop is the cleanest way to stop early.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

// Returns the index of the FIRST occurrence of target, or -1 if absent.
int linearSearch(const int arr[], int n, int target) {
    for (int i = 0; i < n; i++)
        if (arr[i] == target)
            return i;                // stop at the first match
    return -1;
}

int main() {
    int arr[] = {0, 1, 2, 5, 4, 3, 9, 7, 6, 8};
    int n = static_cast<int>(size(arr));

    int targets[] = {9, 99, 0, 8};   // middle, absent, first, last
    for (int t : targets) {
        int idx = linearSearch(arr, n, t);
        if (idx != -1) cout << t << " found at index " << idx << '\n';
        else           cout << t << " not found\n";
    }

    int dup[] = {4, 2, 4};
    cout << "First 4 in {4,2,4}: index " << linearSearch(dup, 3, 4) << '\n';
    cout << "Search in empty array: " << linearSearch(arr, 0, 1) << '\n';
    return 0;
}
```

**Dry run (target 9 in `{0,1,2,5,4,3,9,...}`):** compare index 0..5 (no match) → index 6 equals 9 → return **6**.

| Input | Output |
|---|---|
| target `9` | `6` |
| target `99` | `-1` (not found) |
| target `0` (first element) | `0` |
| target `8` (last element) | `9` |
| duplicates `{4,2,4}`, target `4` | `0` (first occurrence) |
| empty array | `-1` |

**Complexity:** best O(1) (first element), worst and average O(n), O(1) space. It is the only option on **unsorted** data.

**Pitfalls:** returning `0` for "not found" (index 0 is valid!); looping `i <= n` (reads one past the end); not breaking after finding (wasted work and returns the *last* index if you keep overwriting).

**Follow-ups**
- *Find all occurrences / the last occurrence?* Keep scanning and record indices (or loop backwards for the last).
- *Faster on sorted data?* Binary search, O(log n) (Q38).
- *Many searches on the same data?* Build a `unordered_map` or sort once, then search (Q47, Q50).
- *Standard library?* `find(arr, arr + n, target)` returns an iterator; `it - arr` gives the index.
- *Sentinel trick:* place the target at the end to avoid checking `i < n` each iteration (a micro-optimization worth knowing).

---

## Q8. Remove Duplicates from a Sorted Array

**Review of your solution:** 🐞 Your deduplication loop is correct. It keeps the last copy of each run and appends the final element. But:

1. **You changed the problem.** The question says "a sorted array". You started with an *unsorted* array and sorted it with bubble sort first. Bubble sort is O(n²), so the whole program is O(n²), while the intended solution is **O(n)** because sorted input makes duplicates adjacent.
2. `i < std::size(arr) - 1` mixes `int` with `size_t` (a warning), and `size() - 1` would wrap around to a huge number for an empty array (A3). It cannot happen with your fixed array, but it would in a function.
3. The result should be the **new length** returned by a function, as in the classic interview version.

**Review of your revised version (round 2):** ✅ Correct, and exactly the intended solution: you now work on a sorted array and use the reader/writer pattern with `arr[j-1]` as the last kept value, in O(n) time and O(1) space. Tested on your array (`0 2 3 4 6 8`). Remaining polish: put it in a function that **returns the new length** (so it can be tested), and avoid the trailing space when printing. The `n == 0` check is correct for a function, but cannot trigger for a C array (arrays cannot have size 0).

**Problem:** Modify a sorted array in place so each distinct value appears once.

**Concepts:** reader/writer two-pointer technique (A6), in-place modification, returning the new logical length.

**How to think**
- In a sorted array equal values are neighbors, so a value is a duplicate exactly when it equals the **last value written**.
- `k` = number of unique values written so far (also the next write position). Element `arr[0]` is always kept.
- For each `i` from 1: if `arr[i] != arr[k - 1]`, it is new: write `arr[k++] = arr[i]`.
- The array is not shrunk (a C array cannot be). Return `k`; only the first `k` elements are meaningful.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

// Input MUST be sorted. Returns the number of distinct values (new length).
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    int k = 1;                              // arr[0] is always unique
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[k - 1]) {         // different from the last kept value
            arr[k] = arr[i];
            k++;
        }
    }
    return k;
}

void printFirst(const int arr[], int k) {
    for (int i = 0; i < k; i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';
}

int main() {
    int a[] = {0, 0, 2, 3, 3, 4, 4, 6, 22, 22, 33, 84, 84, 204};
    int b[] = {1, 1, 1, 1};
    int c[] = {1, 2, 3};
    int d[] = {5};

    int k = removeDuplicates(a, static_cast<int>(size(a))); printFirst(a, k);
    k = removeDuplicates(b, static_cast<int>(size(b)));     printFirst(b, k);
    k = removeDuplicates(c, static_cast<int>(size(c)));     printFirst(c, k);
    k = removeDuplicates(d, static_cast<int>(size(d)));     printFirst(d, k);
    cout << "Empty -> new length " << removeDuplicates(a, 0) << '\n';
    return 0;
}
```

**Dry run (`{1, 1, 2, 2, 3}`):**

| i | arr[i] | compare with arr[k-1] | action | k | array (first k) |
|---|---|---|---|---|---|
| start | | | arr[0] kept | 1 | `1` |
| 1 | 1 | 1 == 1 | skip | 1 | `1` |
| 2 | 2 | 2 != 1 | `arr[1] = 2` | 2 | `1 2` |
| 3 | 2 | 2 == 2 | skip | 2 | `1 2` |
| 4 | 3 | 3 != 2 | `arr[2] = 3` | 3 | `1 2 3` |

New length **3**.

| Input (sorted) | Output |
|---|---|
| `{0,0,2,3,3,4,4,6,22,22,33,84,84,204}` | `0 2 3 4 6 22 33 84 204` |
| `{1,1,1,1}` | `1` |
| `{1,2,3}` | `1 2 3` (no duplicates) |
| `{5}` | `5` |
| `{}` | length `0` |

**Complexity:** O(n) time, O(1) extra space. Your version: O(n²) because of bubble sort.

**If the input is not sorted:** sort first with `std::sort` (O(n log n), `<algorithm>`) and then run the same function. Do not hand-write bubble sort for this. Alternatively use a `std::set` (Q48) or `std::unordered_set`, trading memory for not needing to sort.

**Pitfalls:** running it on unsorted input silently gives wrong results (`{1,2,1}` keeps all three: the second `1` differs from the last kept `2`); comparing `arr[i]` with `arr[i-1]` instead of `arr[k-1]` also works for removal in place only if you are careful about overwriting; forgetting that elements after index `k - 1` are leftovers.

**Follow-ups**
- *Allow each value at most twice (LeetCode 80)?* Compare with `arr[k - 2]` instead of `arr[k - 1]`.
- *Standard library?* `unique(arr, arr + n) - arr` (returns the new end) after sorting.
- *Remove a specific value in place?* Same reader/writer pattern with `if (arr[i] != val) arr[k++] = arr[i];`.
- *Why in place?* Constant extra memory, which interviewers care about.

---

---

## Q9. Rotate an Array

**Review of your solution:** ✅ The algorithm is correct and is the classic optimal one: **three reversals**, O(n) time, O(1) space. I verified left and right rotation for `k = 3, 13, 10, 0, 1` on `0..9`. Your comment block explaining the steps is excellent. What to improve:

1. **`k % n == 0` prints "No rotation need" but not the array.** After a full rotation the array is unchanged, but the caller still expects to see it. The special case should simply do nothing and let the normal printing happen.
2. **Negative `k` is silently ignored** (no output at all). A left rotation by `-1` is the same as a right rotation by `1`, so normalize with `((k % n) + n) % n` instead of rejecting it.
3. **Printing inside the rotate functions** mixes two jobs. Rotation functions should only rotate; printing belongs in `main` (or a helper). This also makes them testable.
4. **`int arr2[10]` hard-codes the size** while `arr` is sized automatically. If you later add elements to `arr`, the copy loop writes past the end of `arr2`. Derive the size from the data (`const int n = size(base);` then `int b[n];`, as below) or copy into a `std::vector`.
5. Conventional parameter order is `(arr, n, k)`.

**Problem:** Rotate an array to the right (and left) by `k` positions.

**Concepts:** array reversal (Q4), modular arithmetic for `k ≥ n`, in-place algorithms.

**How to think**
- *Right rotation by 2 of `{1,2,3,4,5}` → `{4,5,1,2,3}`:* the **last k elements move to the front**, keeping their order.
- *Brute force:* rotate by one position `k` times: O(n·k). *With a copy:* write `arr[i]` to `tmp[(i + k) % n]`: O(n) time but O(n) extra memory.
- *Three reversals (optimal):* reversing the whole array puts the last `k` elements at the front but **backwards**. Reversing the first `k` and then the remaining `n - k` elements puts each block back in its original order.
- *Normalize `k` first:* rotating by `n` returns the original array, so only `k mod n` matters.

**Solution**
```cpp
#include <iostream>
#include <iterator>
#include <utility>
using namespace std;

void reverseRange(int arr[], int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// Maps ANY k (negative, or >= n) into the range [0, n-1].
int normalize(int k, int n) {
    return ((k % n) + n) % n;
}

void rotateRight(int arr[], int n, int k) {
    if (n <= 0) return;
    k = normalize(k, n);
    if (k == 0) return;               // nothing to do; the array stays as it is
    reverseRange(arr, 0, n - 1);      // 1. reverse everything
    reverseRange(arr, 0, k - 1);      // 2. fix the first k elements
    reverseRange(arr, k, n - 1);      // 3. fix the remaining n-k elements
}

void rotateLeft(int arr[], int n, int k) {
    if (n <= 0) return;
    k = normalize(k, n);
    if (k == 0) return;
    reverseRange(arr, 0, k - 1);      // 1. reverse the first k
    reverseRange(arr, k, n - 1);      // 2. reverse the rest
    reverseRange(arr, 0, n - 1);      // 3. reverse everything
}

void printArray(const char *label, const int arr[], int n) {
    cout << label;
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';
}

int main() {
    const int base[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int n = static_cast<int>(size(base));
    const int ks[] = {3, 13, 10, 0, 1, -1};

    for (int k : ks) {
        int a[n];
        int b[n];
        for (int i = 0; i < n; i++) { a[i] = base[i]; b[i] = base[i]; }

        rotateLeft(a, n, k);
        rotateRight(b, n, k);

        cout << "k = " << k << '\n';
        printArray("  left : ", a, n);
        printArray("  right: ", b, n);
    }

    int one[] = {42};
    rotateRight(one, 1, 5);
    printArray("single element: ", one, 1);
    rotateLeft(one, 0, 5);              // empty array: nothing happens
    return 0;
}
```

**Dry run — right rotation of `{1, 2, 3, 4, 5}` by `k = 2`:**

| step | action | array |
|---|---|---|
| start | | `1 2 3 4 5` |
| 1 | reverse all | `5 4 3 2 1` |
| 2 | reverse first 2 | `4 5 3 2 1` |
| 3 | reverse last 3 | `4 5 1 2 3` ✓ |

**Dry run — left rotation of `{1, 2, 3, 4, 5}` by `k = 2`:**

| step | action | array |
|---|---|---|
| 1 | reverse first 2 | `2 1 3 4 5` |
| 2 | reverse last 3 | `2 1 5 4 3` |
| 3 | reverse all | `3 4 5 1 2` ✓ |

| Input (`0..9`) | Left | Right |
|---|---|---|
| `k = 3` | `3 4 5 6 7 8 9 0 1 2` | `7 8 9 0 1 2 3 4 5 6` |
| `k = 13` (same as 3) | same as `k = 3` | same as `k = 3` |
| `k = 10` or `0` | unchanged | unchanged |
| `k = 1` | `1 2 … 9 0` | `9 0 1 … 8` |
| `k = -1` | `9 0 1 … 8` (a left rotation by -1 is a right rotation by 1) | `1 2 … 9 0` |
| single element | unchanged | unchanged |
| empty | unchanged | unchanged |

**Why `((k % n) + n) % n`:** in C++ `-1 % 10 == -1`, which is not a valid index offset. Adding `n` makes it positive and the final `% n` brings it back into `[0, n-1]`.

**Complexity:** O(n) time (every element is moved at most twice), O(1) extra space.

| Approach | Time | Space |
|---|---|---|
| Rotate by 1, `k` times | O(n·k) | O(1) |
| Temporary array | O(n) | O(n) |
| **Three reversals** | **O(n)** | **O(1)** |
| Juggling (cycle) algorithm | O(n) | O(1) |

**Pitfalls:** forgetting `k % n` (reading past the end for `k > n`); `k % 0` when `n == 0` (division by zero: guard `n <= 0` first); reversing in the wrong order (left and right use different step orders: your code had them right).

**Follow-ups**
- *Standard library?* `rotate(arr, arr + k, arr + n)` rotates **left** by `k` (`<algorithm>`); for a right rotation by `k` use `rotate(arr, arr + n - k, arr + n)`.
- *Why do three reversals work?* Write the array as two blocks `AB`. Then `(AB)ᴿ = BᴿAᴿ`, and reversing each block gives `BA`. That is exactly a rotation.
- *Check if one array is a rotation of another?* Search for it inside the doubled array `A + A`.
- *Rotate a matrix?* Transpose and reverse each row (Module 7).

---

## Q10. Move All Zeros to the End

**Review of your solution:** ✅ Correct, and it is the standard optimal answer: one pass, in place, **stable** (nonzero elements keep their relative order). I tested `{0,0,0}`, `{1,2,3}`, `{0,1}`, `{4}` and `{0,0,1,0,2,0,0,3}`. Minor polish: when `i == insertPos` your code swaps an element with itself (harmless, but it is a wasted write; it happens for every nonzero element before the first zero). Use `std::swap` and skip the self-swap.

**Problem:** Move all zeros to the end while keeping the order of the nonzero elements.

**Concepts:** reader/writer two pointers (A6), stability, in-place partitioning.

**How to think**
- Maintain `insertPos`, the position where the next nonzero value belongs. Everything before it is already final: nonzeros in their original order.
- Scan with `i`. Whenever `arr[i]` is nonzero, swap it to `insertPos` and advance `insertPos`. Zeros are never touched explicitly: the swaps push them to the right.
- *Why stable?* Nonzero elements are placed in the order they are encountered.
- *Alternative (two passes):* copy the nonzeros forward, then fill the rest with zeros. Fewer writes, but two loops.

**Solution**
```cpp
#include <iostream>
#include <utility>
using namespace std;

void moveZerosToEnd(int arr[], int n) {
    int insertPos = 0;                           // next slot for a nonzero value
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            if (i != insertPos)                  // skip pointless self-swaps
                swap(arr[i], arr[insertPos]);
            insertPos++;
        }
    }
}

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';
}

int main() {
    int a[] = {0, 1, 0, 3, 13, 0, 8, 9};
    int b[] = {0, 0, 0};
    int c[] = {1, 2, 3};
    int d[] = {0, 1};
    int e[] = {0, 0, 1, 0, 2, 0, 0, 3};

    moveZerosToEnd(a, 8); printArray(a, 8);
    moveZerosToEnd(b, 3); printArray(b, 3);
    moveZerosToEnd(c, 3); printArray(c, 3);
    moveZerosToEnd(d, 2); printArray(d, 2);
    moveZerosToEnd(e, 8); printArray(e, 8);
    moveZerosToEnd(a, 0);                        // empty: nothing happens
    return 0;
}
```

**Dry run (`{0, 1, 0, 3}`):**

| i | arr[i] | action | insertPos | array |
|---|---|---|---|---|
| 0 | 0 | zero: skip | 0 | `0 1 0 3` |
| 1 | 1 | swap with index 0 | 1 | `1 0 0 3` |
| 2 | 0 | zero: skip | 1 | `1 0 0 3` |
| 3 | 3 | swap with index 1 | 2 | `1 3 0 0` ✓ |

| Input | Output |
|---|---|
| `{0,1,0,3,13,0,8,9}` | `1 3 13 8 9 0 0 0` |
| `{0,0,0}` | `0 0 0` |
| `{1,2,3}` | `1 2 3` (no swaps at all) |
| `{0,1}` | `1 0` |
| `{4}` | `4` |
| `{}` | unchanged |

**Complexity:** O(n) time, O(1) space, at most `n` swaps.

**Pitfalls:** using `arr[i] == 0` as the trigger and swapping with the "last nonzero" (breaks stability); sorting (O(n log n) and may reorder nonzeros); building a second array when the question says in place.

**Follow-ups**
- *Move zeros to the front instead?* Run the same idea from right to left.
- *Move all negative numbers first, keeping order?* Replace `!= 0` with `< 0`. In general this is a **stable partition**: `stable_partition(arr, arr + n, [](int x){ return x != 0; })`.
- *Relation to sorting?* This is exactly the *partition* step of quicksort (Q44), except quicksort does not need stability.
- *Remove all zeros (shrink the array)?* Same loop, but return `insertPos` as the new length (compare Q8).

---

# PART 0 (continued) — STRING CONCEPTS (read once)

## S1. `std::string` basics

```cpp
#include <string>
std::string s = "Mahakal";
s.size();        // 7  (same as s.length())   -- returns size_t (unsigned)!
s[0];            // 'M'  (no bounds check)     s.at(0) checks and throws on a bad index
s.empty();       // true only for ""
s += "!";        // append
```

- A `std::string` is a **mutable** sequence of `char`s that manages its own memory. Copying it copies the characters.
- `s[i]` for `i >= s.size()` is undefined behavior (except `s[s.size()]`, which is `'\0'`).
- To avoid copies, pass big strings as `const string &s` (read only) or `string &s` (modify).

## S2. `char` is a small integer

- `'a' == 97`, `'A' == 65`, `'0' == 48`. Letters are consecutive, so `'d' - 'a' == 3`.
- Digit character → number: `c - '0'`. Number → digit: `char('0' + d)`.
- Use `<cctype>`: `isalpha`, `isdigit`, `isspace`, `tolower`, `toupper`. Cast to `unsigned char` first for safe use with arbitrary data: `isalpha(static_cast<unsigned char>(c))`.

## S3. Reading strings

```cpp
string w;  cin >> w;            // reads ONE word (stops at whitespace)
string line;  getline(cin, line);   // reads the WHOLE line, spaces included
```

If you mix `cin >> x` and `getline`, the leftover newline makes `getline` return an empty string; call `cin.ignore()` in between.

## S4. The `size_t` loop trap (again)

`s.size() - 1` on an **empty** string is `18446744073709551615`. Safe habits: use `i < n / 2` style loops, check `empty()` first, or cast to `int` once.

## S5. Bytes vs characters

`std::string` stores **bytes**. For plain ASCII text one byte = one character. In UTF-8 text (accents, emoji, Devanagari, ...) a character can take 2 to 4 bytes, so byte-by-byte algorithms (reverse, count, index) can break the text. Interview problems assume ASCII unless stated otherwise.

---

# MODULE 2 — STRINGS

---

## Q11. Reverse a String

**Review of your solution:** ✅ Correct (`"Mahakal"` → `"lakahaM"`; empty, one-character, even, odd and spaces all work). Polish:

1. `s.length() <= 0` is a roundabout way to say `s.empty()`; `length()` is unsigned, so "less than 0" can never be true.
2. **Printing inside the function** ("String is Empty.") mixes work and output. An empty string is a perfectly valid input whose reverse is the empty string: just return.
3. `int end = s.length() - 1;` converts an unsigned value to `int`. It is safe here only because you checked for empty first. Looping `i < n / 2` avoids the subtraction entirely.
4. The string is hard-coded. Read it from the user with `getline` so spaces work (done below).
5. **Byte reversal breaks non-ASCII text** (see S5): `"café"` reversed byte-wise produces invalid UTF-8. I tested this. Mention it in an interview as a known limitation.

**Problem:** Reverse a string without a built-in reverse function.

**Concepts:** two pointers (A6) on a string, `size_t` care (S4), in place.

**How to think:** Identical to reversing an array (Q4): swap the first character with the last, the second with the second-to-last, and so on, stopping at the middle. With `n = s.size()`, character `i` swaps with character `n - 1 - i`, for `i` from `0` to `n/2 - 1`. The middle character of an odd-length string stays in place.

**Solution**
```cpp
#include <iostream>
#include <string>
using namespace std;

void reverseString(string &s) {
    size_t n = s.size();
    for (size_t i = 0; i < n / 2; i++) {       // n == 0 -> loop never runs
        char temp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = temp;
    }
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {                    // end of input or read error
        cout << "No input\n";
        return 0;
    }

    reverseString(s);
    cout << "Reversed: " << s << '\n';
    return 0;
}
```

**Reading the input as a string (used from now on in the strings module):** `getline(cin, s)` reads the **whole line**, spaces included. `cin >> s` would stop at the first space.

| Reading method | Input line `Hello World` | `s` becomes |
|---|---|---|
| `cin >> s` | `Hello World` | `Hello` (stops at the space; the rest stays in the buffer) |
| `getline(cin, s)` | `Hello World` | `Hello World` |

If the program has already read a number with `cin >> n`, a newline is still waiting in the buffer, and the next `getline` would return an empty string. Call `cin.ignore(numeric_limits<streamsize>::max(), '\n');` (needs `<limits>`) in between. For an online judge, remove the `"Enter a string: "` prompt, because judges compare the output exactly.

**Sample runs** (everything after `Enter a string: ` is what you type):

| You type | Output |
|---|---|
| `Mahakal` | `Reversed: lakahaM` |
| `Hello World` | `Reversed: dlroW olleH` |
| `racecar` | `Reversed: racecar` |
| `a` | `Reversed: a` |
| *(just Enter, an empty line)* | `Reversed: ` |
| `  hi  ` (leading and trailing spaces) | `Reversed:   ih  ` (spaces are characters too and are kept) |
| *(Ctrl+D / end of input)* | `No input` |

**Dry run (`"abcd"`, n = 4, loop `i = 0..1`):**

| i | swap | string |
|---|---|---|
| 0 | `s[0] ↔ s[3]` | `dbca` |
| 1 | `s[1] ↔ s[2]` | `dcba` ✓ |

**Complexity:** O(n) time (n/2 swaps), O(1) extra space. Building a new string by appending from the back is also O(n) but uses O(n) extra memory.

**Pitfalls:** `for (int i = 0; i < s.size() ...)` sign-compare warning; looping to `n` instead of `n/2` reverses twice; using `s.size() - 1` on an empty string.

**Follow-ups**
- *Standard library?* `reverse(s.begin(), s.end());` from `<algorithm>`, or `string(s.rbegin(), s.rend())`.
- *Reverse the order of the words but not the letters?* Reverse the whole string, then reverse each word.
- *Reverse each word in place?* Find word boundaries with `' '` and reverse each range.
- *Recursive version?* See Q34 (swap the ends, recurse on the middle).
- *Why is a palindrome check (Q12) almost the same loop?* Compare `s[i]` with `s[n-1-i]` instead of swapping.

---

## Q12. Check a String Palindrome

**Review of your solution:** ✅ The two-pointer logic is correct (`racecar`, `abba`, `a`, `ab` all verified) and you read the line with `getline`. Things to tighten:

1. **Inconsistent empty-string rule.** `isPalindrome("")` returns `true`, but `main` prints "String is empty." and never calls it. Pick one rule. By convention the empty string **is** a palindrome.
2. The parameter should be `const std::string &s` (the function only reads it).
3. `int end = s.length() - 1;` converts an unsigned value to `int`. The `i < n / 2` loop form avoids the subtraction (S4).
4. **State your decisions.** Your version is case-sensitive and counts spaces/punctuation, so `Racecar` and `A man, a plan, a canal: Panama` are "not palindromes" (I tested both). That is a valid reading, but say it out loud, and know the relaxed version (below).
5. The output ends with a trailing space (`" is Palindrome "`).

**Problem:** Decide whether a string reads the same forwards and backwards.

**Concepts:** two pointers (A6), `<cctype>` (S2), deciding the rules before coding.

**How to think**
- Compare the first and last characters, then the second and second-to-last, and so on. One mismatch → not a palindrome. Stop at the middle: `n / 2` comparisons.
- **Strict version:** every character counts, case-sensitive.
- **Relaxed version (the famous interview variant):** ignore case and skip everything that is not a letter or digit. Move `left` forward and `right` backward past non-alphanumerics, then compare lower-cased characters.

**Solution**
```cpp
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

// Strict: case-sensitive, every character (spaces included) counts.
bool isPalindrome(const string &s) {
    size_t n = s.size();
    for (size_t i = 0; i < n / 2; i++)
        if (s[i] != s[n - 1 - i]) return false;
    return true;                                  // "" and 1 character are palindromes
}

// Relaxed: ignore case, spaces and punctuation.
bool isPalindromeRelaxed(const string &s) {
    int left = 0, right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        while (left < right && !isalnum(static_cast<unsigned char>(s[left])))  left++;
        while (left < right && !isalnum(static_cast<unsigned char>(s[right]))) right--;
        if (tolower(static_cast<unsigned char>(s[left])) !=
            tolower(static_cast<unsigned char>(s[right])))
            return false;
        left++;
        right--;
    }
    return true;
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }

    cout << "Strict:  " << (isPalindrome(s) ? "palindrome" : "not a palindrome") << '\n';
    cout << "Relaxed: " << (isPalindromeRelaxed(s) ? "palindrome" : "not a palindrome") << '\n';
    return 0;
}
```

**Dry run (`"abca"`):** `i = 0`: `a` vs `a` ✓; `i = 1`: `b` vs `c` ✗ → **not a palindrome**.

| You type | Strict | Relaxed |
|---|---|---|
| `racecar` | palindrome | palindrome |
| `Racecar` | not | palindrome |
| `A man, a plan, a canal: Panama` | not | palindrome |
| `ab` | not | not |
| `a` | palindrome | palindrome |
| *(empty line)* | palindrome | palindrome |
| `!!` | palindrome | palindrome (nothing alphanumeric is left, so nothing can mismatch) |

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** comparing `s[i]` with `s[n - i]` (off by one); using `s.size() - 1` on an empty string; `isalnum(s[i])` with a negative `char` (undefined behavior: cast to `unsigned char`).

**Follow-ups**
- *Without writing a loop?* `equal(s.begin(), s.begin() + s.size() / 2, s.rbegin())` or `s == string(s.rbegin(), s.rend())` (this one copies).
- *Palindrome number?* Level 1, Q17.
- *Longest palindromic substring?* Expand around each center: O(n²).
- *Valid palindrome after deleting at most one character?* Two pointers; on a mismatch try skipping either side.

---

## Q13. Count Vowels and Consonants

**Review of your solution:** ✅ Correct: only letters are counted (digits, spaces and punctuation are ignored: `"123 !!"` → 0 and 0), both cases are handled. Improvements:

1. `i < str.length()` compares `int` with `size_t` (compiler warning).
2. `isalpha(str[i])` with a plain `char`: a negative value (any non-ASCII byte) is **undefined behavior**; cast to `unsigned char` (S2).
3. The ten-way `||` chain is hard to read and easy to mistype. Lower-case the character once and test five letters, or put the test in a helper `isVowel`.
4. For an empty string you print a message. The natural answer is simply "Vowels: 0, Consonants: 0": no special case needed.

**Problem:** Count vowels and consonants, handling upper and lower case.

**Concepts:** `<cctype>` (`isalpha`, `tolower`), helper functions, definitions (a *consonant* is a letter that is not a vowel).

**How to think:** For every character: is it a letter? If not, skip it. If yes, convert to lower case and check `a e i o u`. Everything else among letters is a consonant. Note that `y` counts as a consonant here (state this assumption).

**Solution**
```cpp
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

bool isVowel(char c) {
    char lower = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

void countVowelsAndConsonants(const string &s, int &vowels, int &consonants) {
    vowels = 0;
    consonants = 0;
    for (char c : s) {
        if (!isalpha(static_cast<unsigned char>(c))) continue;   // ignore non-letters
        if (isVowel(c)) vowels++;
        else            consonants++;
    }
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }

    int vowels, consonants;
    countVowelsAndConsonants(s, vowels, consonants);
    cout << "Vowels: " << vowels << '\n';
    cout << "Consonants: " << consonants << '\n';
    return 0;
}
```

| You type | Vowels | Consonants |
|---|---|---|
| `Hello World` | 3 | 7 |
| `AEIOU` | 5 | 0 |
| `123 !!` | 0 | 0 |
| `Rhythm` | 0 | 6 |
| *(empty line)* | 0 | 0 |

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** counting spaces or digits as consonants (`!vowel` is **not** the same as consonant); forgetting uppercase vowels; assuming only ASCII letters exist.

**Follow-ups**
- *Count digits, spaces and special characters too?* Add `isdigit`, `isspace`, and an `else` branch.
- *A vowel test with a lookup?* `string("aeiou").find(lower) != string::npos`, or a `switch` with fall-through cases.

---

## Q14. Count Words in a Sentence

**Review of your solution:** ✅ The `inWord` state flag is exactly the right technique, and it correctly handles repeated spaces and leading/trailing spaces (`"  hello   world  "` → 2, `"   "` → 0). Bugs and polish:

1. 🐞 **Only `' '` counts as a separator.** A tab or newline between words is treated as part of a word: `"hello<TAB>world"` gives **1** (I tested this). Use `isspace`, which covers space, tab, newline, carriage return and so on.
2. The empty string prints "String is empty." instead of the correct answer, `0` words.
3. The output sentence is hard to read (`'...' :2`).

**Problem:** Count words, handling repeated spaces and leading or trailing whitespace.

**Concepts:** state machine (`inWord`), `isspace`, `istringstream`.

**How to think:** A word **starts** where a non-space character follows a space (or the start of the string). So count the *transitions* from "outside a word" to "inside a word". One pass, one flag.

**Solution**
```cpp
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int countWords(const string &s) {
    int count = 0;
    bool inWord = false;
    for (char c : s) {
        if (isspace(static_cast<unsigned char>(c))) {
            inWord = false;                    // whitespace ends any current word
        } else if (!inWord) {
            inWord = true;                     // a new word begins here
            count++;
        }
    }
    return count;
}

// Same result with the standard library: `>>` skips whitespace automatically.
int countWordsStream(const string &s) {
    istringstream in(s);
    string word;
    int count = 0;
    while (in >> word) count++;
    return count;
}

int main() {
    string s;
    cout << "Enter a sentence: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }

    cout << "Words: " << countWords(s) << '\n';
    cout << "Words (stream check): " << countWordsStream(s) << '\n';
    return 0;
}
```

**Dry run (`"  hi  you"`):**

| char | action | inWord | count |
|---|---|---|---|
| space, space | whitespace | false | 0 |
| `h` | new word | true | 1 |
| `i` | still in word | true | 1 |
| space, space | whitespace | false | 1 |
| `y` | new word | true | 2 |
| `o`, `u` | in word | true | 2 |

| You type | Words |
|---|---|
| `  hello   world  ` | 2 |
| `one` | 1 |
| `   ` (only spaces) | 0 |
| *(empty line)* | 0 |
| `hello<TAB>world` | 2 (your version: 1) |

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** counting spaces and adding 1 (`"a  b"` and `" a"` break it); treating only `' '` as whitespace; hyphenated words or punctuation (decide what a "word" is, e.g. `don't`, `well-known`).

**Follow-ups**
- *Print each word?* Use the `istringstream` loop and print `word`.
- *Longest word? Reverse the word order?* Same loop with extra state.
- *Count words separated by commas?* Replace `isspace` with a custom delimiter test.

---

## Q15. Character Frequency

**Review of your solution:** ✅ Correct output in first-occurrence order (`hello world` → `h 1, e 1, l 3, o 2, ...`). But:

1. 🐞 **O(n²)**: for each character you scan before it (`seen`) and after it (count). Counting every character in one pass with a table is O(n).
2. The output ends with a dangling `", "`, and a space character prints as a blank (`"  1"`), which is confusing.
3. `std::string &s` should be `const std::string &s`; `int strSize = s.size()` is an unsigned-to-int conversion.

**Problem:** Count how many times each character occurs.

**Concepts:** counting with a lookup table indexed by character code (`unsigned char` → 0..255), preserving first-occurrence order, `std::map` alternative.

**How to think**
1. **Brute force (yours):** for each position, check if the character was seen, count the rest: O(n²).
2. **Table:** `int count[256]`; for each character do `count[c]++`. Reading the table afterwards gives sorted-by-character order; to get **first-occurrence order**, walk the string again and print each character the first time you meet it, then zero its count so it is not printed twice.

**Solution**
```cpp
#include <iostream>
#include <string>
using namespace std;

void printFrequency(const string &s) {
    int count[256] = {};                                  // one counter per possible byte
    for (char ch : s)
        count[static_cast<unsigned char>(ch)]++;

    bool first = true;
    for (char ch : s) {
        unsigned char u = static_cast<unsigned char>(ch);
        int c = count[u];
        if (c == 0) continue;                             // already printed

        if (!first) cout << ", ";
        if (ch == ' ') cout << "' '";                     // make spaces visible
        else           cout << ch;
        cout << ": " << c;

        count[u] = 0;                                     // never print this character again
        first = false;
    }
    cout << '\n';
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }
    printFrequency(s);
    return 0;
}
```

**Dry run (`"aba"`):** table after pass 1: `a = 2`, `b = 1`. Pass 2: `a` → print `a: 2`, zero it; `b` → print `b: 1`; `a` → count 0, skip. Output `a: 2, b: 1`.

| You type | Output |
|---|---|
| `hello world` | `h: 1, e: 1, l: 3, o: 2, ' ': 1, w: 1, r: 1, d: 1` |
| `aAa` | `a: 2, A: 1` (case-sensitive) |
| `mississippi` | `m: 1, i: 4, s: 4, p: 2` |
| *(empty line)* | *(empty line)* |

**Complexity:** O(n) time, O(1) space (a fixed 256-entry table, independent of `n`).

**Alphabetical order or any Unicode text?** Use `std::map<char,int>` (sorted by key, O(n log k)) or `unordered_map` (Q47). For lower-case-only input a table of 26 (`c - 'a'`) is enough.

**Pitfalls:** indexing the table with a plain `char` (negative index for non-ASCII bytes → out-of-bounds); forgetting that `'A'` and `'a'` are different; not initializing the table (`= {}` zeroes it).

**Follow-ups**
- *Most frequent character?* Track the maximum while scanning the table.
- *Frequency ignoring case?* `tolower` before indexing.
- *This "count with a table" idea powers anagrams (Q16), first unique character (Q18) and the frequency counter (Q47).*

---

## Q16. Check Anagrams

**Review of your solution:** ✅ The algorithm is correct and well written: length check first, then **increment for one string and decrement for the other**, then verify every counter is zero. Using `unsigned char` for the index is exactly right. Improvements:

1. 🐞 **The strings are hard-coded** (`"asdf09876"`, `"67890fdas"`). Read both with `getline` so you can test it (as you said you wanted: input as string).
2. Parameters should be `const std::string &`.
3. **Decide the rules:** your version is case-sensitive and counts spaces, so `Listen` / `Silent` is **not** an anagram pair. The classic interview version ignores case and spaces (`"Dormitory"` / `"dirty room"`); a relaxed function is below.
4. Output formatting: `" Anagrams. "` / `" Not Anagrams."` have inconsistent spaces.

**Problem:** Decide whether two strings contain the same characters with the same frequencies.

**Concepts:** frequency table (Q15), early exit on different lengths, normalization.

**How to think**
1. **Sort both strings and compare:** O(n log n), easy to write.
2. **Counting (yours):** one table, `+1` for each character of `a`, `-1` for each of `b`. If they are anagrams, every entry returns to zero: O(n), O(1) space.
3. If the lengths differ they cannot be anagrams (strict version): return immediately.

**Solution**
```cpp
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

// Strict: case-sensitive, spaces count.
bool isAnagram(const string &a, const string &b) {
    if (a.size() != b.size()) return false;

    int count[256] = {};
    for (size_t i = 0; i < a.size(); i++) {
        count[static_cast<unsigned char>(a[i])]++;
        count[static_cast<unsigned char>(b[i])]--;
    }
    for (int c : count)
        if (c != 0) return false;
    return true;
}

// Relaxed: ignore case and anything that is not a letter or digit.
bool isAnagramRelaxed(const string &a, const string &b) {
    int count[256] = {};
    for (char ch : a)
        if (isalnum(static_cast<unsigned char>(ch)))
            count[tolower(static_cast<unsigned char>(ch))]++;
    for (char ch : b)
        if (isalnum(static_cast<unsigned char>(ch)))
            count[tolower(static_cast<unsigned char>(ch))]--;
    for (int c : count)
        if (c != 0) return false;
    return true;
}

int main() {
    string a, b;
    cout << "Enter the first string: ";
    getline(cin, a);
    cout << "Enter the second string: ";
    if (!getline(cin, b)) {
        cout << "Need two lines of input\n";
        return 0;
    }

    cout << "Strict:  " << (isAnagram(a, b) ? "anagrams" : "not anagrams") << '\n';
    cout << "Relaxed: " << (isAnagramRelaxed(a, b) ? "anagrams" : "not anagrams") << '\n';
    return 0;
}
```

**Dry run (`"cab"` vs `"abc"`):** `c+1, a-1` → `a+1, b-1` → `b+1, c-1`... every counter ends at 0 → anagrams.

| First | Second | Strict | Relaxed |
|---|---|---|---|
| `asdf09876` | `67890fdas` | anagrams | anagrams |
| `listen` | `silent` | anagrams | anagrams |
| `Listen` | `Silent` | not | anagrams |
| `dormitory` | `dirty room` | not (lengths differ) | anagrams |
| `abc` | `abd` | not | not |
| `a` | `aa` | not | not |
| *(both empty)* | | anagrams | anagrams |

**Complexity:** O(n) time, O(1) space (fixed table).

**Pitfalls:** comparing only the sorted-ness of lengths; using a 26-entry table when the input has digits or capitals (out-of-bounds); forgetting the early length check.

**Follow-ups**
- *Sorting version?* `sort(a.begin(), a.end()); sort(b.begin(), b.end()); return a == b;` (O(n log n), modifies copies).
- *Group a list of words by anagram class?* Use the sorted word as a map key.
- *Unicode?* Counting bytes is wrong for multi-byte characters (S5).

---

## Q17. Remove Duplicate Characters

**Review of your solution:** ✅ Correct and clean: a `seen` table, the `unsigned char` cast with an explanatory comment, and a new string built in first-occurrence order (`programming` → `progamin`, `aabbcc` → `abc`, empty → empty). Notes:

1. Case-sensitive: `AaA` → `Aa`. State it, or `tolower` for the check only.
2. `vector<bool>` works; a plain `bool seen[256] = {}` is simpler and faster for a fixed table.
3. `std::string newString = "";` can simply be `std::string newString;`.

**Problem:** Remove repeated characters, keeping the first occurrence of each.

**Concepts:** "seen" table, building a result string, O(n) vs O(n²).

**How to think:** Walk the string once. If a character was not seen, append it and mark it. Otherwise skip it. The result is naturally in first-occurrence order.

**Solution**
```cpp
#include <iostream>
#include <string>
using namespace std;

string removeDuplicates(const string &s) {
    bool seen[256] = {};
    string result;
    for (char ch : s) {
        unsigned char u = static_cast<unsigned char>(ch);   // avoid negative indices
        if (!seen[u]) {
            seen[u] = true;
            result += ch;
        }
    }
    return result;
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }
    cout << "Result: " << removeDuplicates(s) << '\n';
    return 0;
}
```

| You type | Output |
|---|---|
| `programming` | `progamin` |
| `aabbcc` | `abc` |
| `AaA` | `Aa` |
| `hello world` | `helo wrd` |
| *(empty line)* | *(empty line)* |

**Complexity:** O(n) time, O(1) space for the table plus O(n) for the result.

**Without an extra table or a second string?** In place with the reader/writer pattern: `k` marks the write position and, for each `s[i]`, a loop over `s[0..k-1]` checks "seen": O(n²) time, O(1) space.

**Pitfalls:** removing *all* occurrences of repeated characters instead of keeping the first (`aab` → `b` is a different problem); sorting first (loses the original order).

**Follow-ups**
- *Remove only adjacent duplicates (`aabbca` → `abca`)?* Compare with the last appended character.
- *Standard library?* A `set<char>` for the "seen" test.

---

## Q18. First Non-Repeating Character

**Review of your solution:** ✅ Correct (checked: `afdaeaasfed3` → `s`, the first character that appears exactly once). The two-pass design (count, then scan in original order) is the standard answer, and returning `std::optional<char>` is a good modern way to say "maybe nothing". Improvements:

1. **Hard-coded string**: read it with `getline`.
2. For characters, `int freq[256]` is simpler and faster than `unordered_map<char,int>` (no hashing, no heap allocation, same O(n)).
3. Be careful with `map[key]`: `operator[]` **inserts** a missing key. It is safe in your loop because every key exists, but use `find`/`at` for pure lookups.

**Problem:** Find the first character that appears exactly once.

**Concepts:** two-pass counting, `std::optional`, order matters (so you must scan the **string**, not the table).

**How to think:** First pass: count all characters. Second pass: walk the string from the left and return the first character whose count is 1. A table alone cannot answer "first" (it has no order), which is why the second pass reads the string.

**Solution**
```cpp
#include <iostream>
#include <optional>
#include <string>
using namespace std;

optional<char> firstNonRepeating(const string &s) {
    int freq[256] = {};
    for (char ch : s)
        freq[static_cast<unsigned char>(ch)]++;

    for (char ch : s)
        if (freq[static_cast<unsigned char>(ch)] == 1)
            return ch;                      // implicitly wraps the char in an optional

    return nullopt;                         // "no value"
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }

    auto result = firstNonRepeating(s);
    if (result)
        cout << "First non-repeating character: " << *result << '\n';
    else
        cout << "No non-repeating character\n";
    return 0;
}
```

**Dry run (`"swiss"`):** counts `s: 3, w: 1, i: 1`. Scan: `s` (3) skip → `w` (1) **found**.

| You type | Output |
|---|---|
| `swiss` | `w` |
| `afdaeaasfed3` | `s` |
| `aabb` | no non-repeating character |
| `a` | `a` |
| *(empty line)* | no non-repeating character |
| `abcabcd` | `d` |

**Complexity:** O(n) time, O(1) space (fixed table).

**Pitfalls:** returning the character with the *smallest count* or the first in the table (wrong order); using a sentinel like `'\0'` for "none" (a string may contain it); a single pass cannot decide "first unique" until the whole string has been read.

**Follow-ups**
- *Streaming input (characters arrive one by one)?* Keep a queue of candidates and pop repeated ones from the front.
- *Return the index instead of the character?* Same loop, return `i`.
- *First repeating character?* Mark characters as seen in one pass and return the first already seen.

---

# PART 0 (continued) — FUNCTION CONCEPTS (read once)

## F1. Declaration, definition, and prototypes

```cpp
int add(int a, int b);            // declaration (prototype): tells the compiler the signature
int add(int a, int b) {           // definition: the actual body
    return a + b;
}
```

A function must be **declared before it is used**. For small programs, define helpers above `main`; for bigger ones put prototypes at the top.

## F2. Compute in functions, print in `main`

A function that both calculates and prints cannot be reused or tested. The professional split:

| Function | Responsibility |
|---|---|
| `long long add(int a, int b)` | **return** a result |
| `bool divide(int a, int b, double &out)` | return success/failure, give the result through a reference |
| `main` | read input, call functions, print |

Functions that return values compose (`add(add(1, 2), 3)`), can be unit-tested, and can be reused with a different front end.

## F3. How arguments are passed

| Style | Syntax | Effect | Use for |
|---|---|---|---|
| By value | `void f(int x)` | `x` is a **copy**; the caller's variable is unchanged | small types you only read |
| By reference | `void f(int &x)` | `x` **is** the caller's variable | functions that must modify the argument |
| By const reference | `void f(const string &s)` | no copy, read-only | big objects (strings, vectors) you only read |
| By pointer | `void f(int *p)` | `p` holds the caller's **address**; may be `nullptr` | optional arguments, arrays, C-style APIs |

A reference **cannot be null and cannot be re-seated**; a pointer can be both. Prefer references when "no object" is not a valid input.

## F4. Function overloading

Several functions may share a name if their **parameter lists differ** (number or types):

```cpp
double area(double radius);                    // 1 parameter
double area(double length, double breadth);    // 2 parameters
```

- The **return type alone cannot distinguish** overloads.
- Resolution order: exact match → promotion (`char` → `int`) → conversion (`int` → `double`) → ambiguous (compile error).
- Two overloads with the *same* parameter types (circle radius vs square side, both `double`) are impossible, so you need a tag type or different names (see Q24).

## F5. Return-value conventions

- **Return `bool` + out-parameter** (or `std::optional<T>`) when the operation can fail, as for division by zero.
- **Do not return references or pointers to local variables**: they die when the function returns (dangling, see Q30).

---

# MODULE 3 — FUNCTIONS AND MODULAR PROGRAMMING

---

## Q19. Build a Calculator Using Functions

**Review of your solution:** ✅ Works (checked `+ - * /`, division by zero, an invalid operator, and the 64-bit widening so `2000000000 * 2000000000` is exact). The design issue is the one this question is really testing:

1. 🐞 **Your functions print instead of returning.** "Implement addition, subtraction, multiplication and division in separate functions" means each function should compute and **return** a value. Printing belongs in `main`. As written, you cannot reuse `addition` to add three numbers or test it without reading the console.
2. The prompts are confusing: `"Enter the number for calculation(+,-,*,/) : "` mentions operators while asking for numbers. Reading `a op b` in one line (`3 + 4`) is the natural format.
3. Check that input reading succeeded (`cin >> a >> op >> b`).

**Problem:** Implement `+ - * /` in separate functions and use them.

**Concepts:** functions that return values (F2), `switch`, error signalling (`bool` + reference), widening to avoid overflow.

**How to think:** One tiny function per operation. Operations that cannot fail return the result. Division can fail (`b == 0`) and may produce a fraction, so it returns a `bool` and writes the result through a reference parameter. `main` parses the input and chooses the function.

**Solution**
```cpp
#include <iostream>
using namespace std;

long long add(int a, int b)      { return static_cast<long long>(a) + b; }
long long subtract(int a, int b) { return static_cast<long long>(a) - b; }
long long multiply(int a, int b) { return static_cast<long long>(a) * b; }

// Returns false when the division is impossible.
bool divide(int a, int b, double &result) {
    if (b == 0) return false;
    result = static_cast<double>(a) / b;
    return true;
}

int main() {
    int a, b;
    char op;
    cout << "Enter an expression (e.g. 3 + 4): ";
    if (!(cin >> a >> op >> b)) {
        cout << "Invalid input\n";
        return 1;
    }

    switch (op) {
    case '+': cout << a << " + " << b << " = " << add(a, b) << '\n'; break;
    case '-': cout << a << " - " << b << " = " << subtract(a, b) << '\n'; break;
    case '*': cout << a << " * " << b << " = " << multiply(a, b) << '\n'; break;
    case '/': {
        double result;
        if (divide(a, b, result)) cout << a << " / " << b << " = " << result << '\n';
        else                      cout << "Error: division by zero\n";
        break;
    }
    default:
        cout << "Error: invalid operator '" << op << "'\n";
    }
    return 0;
}
```

| You type | Output |
|---|---|
| `3 + 4` | `3 + 4 = 7` |
| `3 - 10` | `3 - 10 = -7` |
| `2000000000 * 2000000000` | `2000000000 * 2000000000 = 4000000000000000000` |
| `7 / 2` | `7 / 2 = 3.5` |
| `5 / 0` | `Error: division by zero` |
| `1 % 2` | `Error: invalid operator '%'` |

**Complexity:** O(1).

**Pitfalls:** integer division (`7 / 2 == 3`) when you expected `3.5`; printing inside the operation functions; forgetting `break` in the `switch`; declaring a variable inside a `case` without braces (the `{ }` around `case '/'` above are required).

**Follow-ups**
- *Make it a loop until the user quits?* Wrap the body in `while (true)`.
- *Use `double` operands?* Change the parameter and return types to `double`.
- *Table of function pointers instead of `switch`?* `double (*ops[])(double, double)`: a nice extension in the pointers module.

---

## Q20. GCD and LCM Functions

**Review of your solution:** 🐞 **The file does not compile.** It contains the entire Q19 calculator program (including its own `main`) pasted in the middle, followed by your GCD/LCM code with a second `main`: `error: redefinition of 'int main()'`. The GCD/LCM part itself is **excellent**, and I tested it separately:

- `magnitude()` converts to unsigned without overflow, even for `LLONG_MIN` (`-(n + 1)` first, then `+ 1`). That is a corner most people miss.
- `gcdValue` on unsigned types, `lcmValue` returning `std::optional` to signal overflow, and the overflow test `reduced > maxValue / y` are all correct.
- Results: `12 18` → GCD 6, LCM 36; `-4 6` → 2, 12; `0 5` → 5, 0; `0 0` → 0, 0; `7 13` → 1, 91; a pair near 9·10¹⁸ → "LCM exceeds the long long range"; `LLONG_MIN 0` → GCD `9223372036854775808`.

Lesson: **one file, one problem, one `main`.** Copy/paste mistakes like this are caught instantly by compiling before submitting. Also remove the unused `<cstdint>`.

**Problem:** Implement separate GCD and LCM functions for two integers.

**Concepts:** Euclid (Level 1, Q18–Q19), `unsigned long long`, `std::optional`, overflow-safe LCM.

**How to think:** `gcd(a, b) = gcd(b, a % b)` until `b == 0`. `lcm(a, b) = a / gcd(a, b) * b`, dividing **first** to keep the intermediate value small, and checking that the product fits. Work with magnitudes so negative inputs behave (`gcd` and `lcm` are defined as non-negative).

**Solution (your design, cleaned up)**
```cpp
#include <iostream>
#include <limits>
#include <optional>
using namespace std;

using ULL = unsigned long long;

// |n| as an unsigned value. Safe even for LLONG_MIN.
ULL magnitude(long long n) {
    return n < 0 ? static_cast<ULL>(-(n + 1)) + 1 : static_cast<ULL>(n);
}

ULL gcdValue(ULL a, ULL b) {
    while (b != 0) {
        ULL r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// nullopt when the LCM does not fit in a long long.
optional<long long> lcmValue(long long a, long long b) {
    ULL x = magnitude(a);
    ULL y = magnitude(b);
    if (x == 0 || y == 0) return 0LL;

    ULL g = gcdValue(x, y);
    ULL reduced = x / g;                                   // divide first

    const ULL maxValue = static_cast<ULL>(numeric_limits<long long>::max());
    if (reduced > maxValue / y) return nullopt;            // reduced * y would not fit

    return static_cast<long long>(reduced * y);
}

int main() {
    long long a, b;
    cout << "Enter two integers: ";
    if (!(cin >> a >> b)) {
        cout << "Invalid input\n";
        return 1;
    }

    cout << "GCD(" << a << ", " << b << ") = " << gcdValue(magnitude(a), magnitude(b)) << '\n';

    auto l = lcmValue(a, b);
    if (l) cout << "LCM(" << a << ", " << b << ") = " << *l << '\n';
    else   cout << "LCM exceeds the long long range\n";
    return 0;
}
```

**Dry run (12, 18):** `gcd`: `(12, 18) → (18, 12) → (12, 6) → (6, 0)` = **6**. `lcm`: `reduced = 12 / 6 = 2`, `2 * 18 = 36`.

| You type | Output |
|---|---|
| `12 18` | GCD 6, LCM 36 |
| `-4 6` | GCD 2, LCM 12 |
| `0 5` | GCD 5, LCM 0 |
| `0 0` | GCD 0, LCM 0 |
| `7 13` | GCD 1, LCM 91 |
| `9000000000000000000 8999999999999999999` | GCD 1, LCM exceeds the long long range |

**Simpler version for an interview whiteboard** (non-negative `int`s):
```cpp
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(int a, int b) { return a == 0 || b == 0 ? 0 : static_cast<long long>(a / gcd(a, b)) * b; }
```

**Complexity:** O(log min(a, b)) time, O(1) space.

**Pitfalls:** `a * b / gcd` (overflows before dividing); `lcm(a, 0)` dividing by a zero gcd; naming your function `gcd` while also writing `using namespace std;` and including `<numeric>` (ambiguous with `std::gcd`).

**Follow-ups**
- *GCD of an array?* Fold with `g = gcd(g, x)`.
- *Standard library?* `std::gcd` and `std::lcm` in `<numeric>` (C++17).
- *Reduce a fraction?* Divide numerator and denominator by their GCD.

---

## Q21. Prime Numbers Using Functions

**Review of your solution:** ✅ Correct and well structured: `isPrime` is a separate function (6k ± 1, `i <= n / i`), input errors and `start > end` are reported, and the loop `for (n = start;; ++n) { ...; if (n == end) break; }` correctly avoids overflow when `end == INT_MAX`. I verified `10 30`, `1 10`, `2147483600 2147483647`, `30 10` and non-numeric input. Small improvements:

1. Move the range printing into a function too (`printPrimes(start, end)`), as the question suggests using the function "to print primes in a range".
2. The output has a trailing space.
3. `<limits>` is unused.

**Problem:** Write a primality function and use it to print primes in a range.

**Concepts:** modular programming (F2), √n primality (Level 1, Q12/Q26), safe loop bounds near `INT_MAX`.

**How to think:** The primality test is the reusable piece. The range function loops through the numbers and calls it. For large ranges prefer the sieve (follow-ups).

**Solution**
```cpp
#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i <= n / i; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

void printPrimes(int start, int end) {
    bool first = true;
    for (int n = start;; ++n) {                 // safe even when end == INT_MAX
        if (isPrime(n)) {
            if (!first) cout << ' ';
            cout << n;
            first = false;
        }
        if (n == end) break;
    }
    cout << '\n';
}

int main() {
    int start, end;
    cout << "Enter the start and end of the range: ";
    if (!(cin >> start >> end)) {
        cout << "Error: invalid input\n";
        return 1;
    }
    if (start > end) {
        cout << "Error: start cannot exceed end\n";
        return 1;
    }

    cout << "Primes between " << start << " and " << end << ": ";
    printPrimes(start, end);
    return 0;
}
```

| You type | Output |
|---|---|
| `10 30` | `11 13 17 19 23 29` |
| `1 10` | `2 3 5 7` |
| `24 28` | *(empty line, no primes)* |
| `2147483600 2147483647` | `2147483629 2147483647` |
| `30 10` | error: start cannot exceed end |
| `abc` | error: invalid input |

**Complexity:** O((end − start) · √end) time, O(1) space.

**Pitfalls:** `for (n = start; n <= end; n++)` loops forever when `end == INT_MAX`; testing `n % i` up to `n - 1` (too slow); printing primes below 2.

**Follow-ups**
- *Many primes quickly?* Sieve of Eratosthenes (Level 2 handbook Q27, Level 1 handbook).
- *Count primes instead of printing them?* Return a counter.
- *Twin primes in the range?* Compare consecutive primes with a difference of 2.

---

## Q22. Pass by Value vs. Pass by Reference

**Review of your solution:** ✅ Correct, and the demonstration works: after `swapByValue(x, y)` the values in `main` are unchanged, after `swapByReference(x, y)` they are swapped (checked with `3 7`). To make the demonstration **convincing** in an interview:

1. Print the values **inside** the by-value function too: the local copies *were* swapped there, but the effect disappears when the function returns. Otherwise it looks like the function did nothing.
2. Print the **addresses**: the by-value parameter has a *different* address than `x`; the by-reference parameter has the *same* address.
3. Add a second, simpler example (`increment`) and a `const` reference example for the "big object" case.

**Problem:** Demonstrate the difference between passing arguments by value and by reference.

**Concepts:** copy vs alias (F3), address-of (`&`), `const &`.

**How to think:** By value → the function receives its own copy; by reference → the parameter is another name for the caller's variable. Printing both the values and `&` addresses makes this visible.

**Solution**
```cpp
#include <iostream>
#include <string>
using namespace std;

void incrementByValue(int n) {
    n++;
    cout << "  inside by value:     n = " << n << ", &n = " << &n << '\n';
}

void incrementByReference(int &n) {
    n++;
    cout << "  inside by reference: n = " << n << ", &n = " << &n << '\n';
}

void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "  inside swapByValue:     a = " << a << ", b = " << b << " (swapped, but only the copies)\n";
}

void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "  inside swapByReference: a = " << a << ", b = " << b << '\n';
}

// A const reference avoids copying a big object and forbids modifying it.
size_t countChars(const string &s) { return s.size(); }

int main() {
    int x, y;
    cout << "Enter two integers: ";
    if (!(cin >> x >> y)) {
        cout << "Invalid input\n";
        return 1;
    }

    cout << "\n--- increment ---\n";
    cout << "main:  x = " << x << ", &x = " << &x << '\n';
    incrementByValue(x);
    cout << "main after by value:     x = " << x << "  (unchanged)\n";
    incrementByReference(x);
    cout << "main after by reference: x = " << x << "  (changed)\n";

    cout << "\n--- swap ---\n";
    cout << "main before: x = " << x << ", y = " << y << '\n';
    swapByValue(x, y);
    cout << "main after swapByValue:     x = " << x << ", y = " << y << "  (unchanged)\n";
    swapByReference(x, y);
    cout << "main after swapByReference: x = " << x << ", y = " << y << "  (swapped)\n";

    string big = "a very long string we do not want to copy";
    cout << "\nconst reference, no copy: " << countChars(big) << " characters\n";
    return 0;
}
```

**Output for `3 7`** (addresses will differ on your machine; the pattern is what matters):

```
--- increment ---
main:  x = 3, &x = 0x7ffd...a4
  inside by value:     n = 4, &n = 0x7ffd...6c      <- a DIFFERENT address (a copy)
main after by value:     x = 3  (unchanged)
  inside by reference: n = 4, &n = 0x7ffd...a4      <- the SAME address as x
main after by reference: x = 4  (changed)

--- swap ---
main before: x = 4, y = 7
  inside swapByValue:     a = 7, b = 4 (swapped, but only the copies)
main after swapByValue:     x = 4, y = 7  (unchanged)
  inside swapByReference: a = 7, b = 4
main after swapByReference: x = 7, y = 4  (swapped)
```

| Style | Copy made? | Caller's variable changes? | Typical use |
|---|---|---|---|
| value | yes | no | small read-only values |
| reference | no | **yes** | functions that must modify |
| const reference | no | no (compiler enforces) | large objects, read-only |

**Complexity:** O(1).

**Pitfalls:** forgetting `&` and wondering why nothing changes; passing a huge `vector` by value (an O(n) copy per call); returning a reference to a local variable.

**Follow-ups**
- *What about pointers?* Passing the address also lets a function modify the original (Q26): the pointer itself is passed *by value*.
- *Arrays?* They always "decay" to pointers, so the callee works on the original elements (A2).
- *Why can't I pass a temporary (`f(5)`) to `int &`?* A non-const reference needs an lvalue; `const int &` accepts temporaries.

---

## Q23. Swap Using References

**Review of your solution:** ✅ Correct and safe: the temporary-variable swap with reference parameters (tested `3 7` → `7 3`). Because it uses a temp, it is also correct if both references name the *same* variable (`swapByReference(x, x)` leaves `x` unchanged), unlike the XOR trick. Extras worth showing in an interview: swapping array elements, and `std::swap`.

**Problem:** Write a function that swaps two integers using reference parameters.

**Concepts:** reference parameters (F3), temp swap, `std::swap`.

**How to think:** You need to change the caller's variables, so use references. Three assignments with one temporary: save `a`, copy `b` into `a`, copy the saved value into `b`.

**Solution**
```cpp
#include <iostream>
#include <utility>
using namespace std;

void swapInts(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x, y;
    cout << "Enter two integers: ";
    if (!(cin >> x >> y)) {
        cout << "Invalid input\n";
        return 1;
    }

    cout << "Before: x = " << x << ", y = " << y << '\n';
    swapInts(x, y);
    cout << "After:  x = " << x << ", y = " << y << '\n';

    int arr[] = {10, 20, 30};
    swapInts(arr[0], arr[2]);                 // works on any int lvalue
    cout << "Array after swapping the ends: " << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

    swapInts(x, x);                           // same variable twice: still safe
    cout << "After swapInts(x, x): x = " << x << '\n';

    swap(x, y);                               // the standard library version (<utility>)
    cout << "After std::swap: x = " << x << ", y = " << y << '\n';
    return 0;
}
```

**Output for `3 7`:**
```
Before: x = 3, y = 7
After:  x = 7, y = 3
Array after swapping the ends: 30 20 10
After swapInts(x, x): x = 7
After std::swap: x = 3, y = 7
```

**Dry run (`a = 3`, `b = 7`):** `temp = 3` → `a = 7` → `b = 3`.

**Complexity:** O(1).

**Pitfalls:** parameters by value (no effect); `swapInts(5, 6)` does not compile (a literal is not an lvalue: that is the compiler protecting you).

**Follow-ups**
- *Swap without a temp?* Arithmetic/XOR tricks (Level 1, Q25), with their overflow and aliasing problems.
- *Swap two strings or vectors?* Make it a template: `template <class T> void mySwap(T &a, T &b)`.
- *Pointer version?* `void swapPtr(int *a, int *b)`.

---

## Q24. Function Overloading

**Review of your solution:** ✅ Correct, and you spotted the real difficulty: the circle (`double radius`) and the square (`double side`) would have the **same signature** `area(double)`, which C++ does not allow. Your fix, a tag parameter (`Shape`), is a recognized technique (*tag dispatch*), and overload resolution picks the right function (`area(r)`, `area(side, SQUARE)`, `area(length, breadth)` gave `12.5664`, `9`, `20`). Improvements:

1. **Use `enum class`** (`Shape::Square`). An unscoped `enum` leaks the name `SQUARE` into the global namespace and converts implicitly to numbers.
2. **Validate input:** a negative radius or side makes no geometric sense (`-2` radius still printed `12.5664`).
3. `<cmath>` is unused. (`M_PI` is not standard C++; your explicit `PI` constant is the portable choice.)

**Problem:** Create overloaded functions that compute the area of a circle, a rectangle and a square.

**Concepts:** overloading rules (F4), tag dispatch, `enum class`, input validation.

**How to think:** Rectangle has two `double` parameters, so it is naturally distinct. Circle and square both take a single `double`: you must make one of them different. Options: (a) a tag parameter, (b) different parameter *types* (e.g. `int side` vs `double radius`: fragile, because `area(5)` and `area(5.0)` silently mean different shapes), or (c) distinct struct types (`Circle`, `Square`). The tag is simple and explicit.

**Solution**
```cpp
#include <iostream>
using namespace std;

enum class Shape { Square };                       // a tag type, no implicit conversions

const double PI = 3.14159265358979323846;

double area(double radius) {                       // circle
    return PI * radius * radius;
}

double area(double length, double breadth) {       // rectangle
    return length * breadth;
}

double area(double side, Shape) {                  // square (the tag disambiguates)
    return side * side;
}

int main() {
    double r, side, length, breadth;

    cout << "Enter radius of the circle: ";
    cin >> r;
    cout << "Enter side of the square: ";
    cin >> side;
    cout << "Enter length and breadth of the rectangle: ";
    cin >> length >> breadth;

    if (!cin || r < 0 || side < 0 || length < 0 || breadth < 0) {
        cout << "Error: enter non-negative numbers only\n";
        return 1;
    }

    cout << "Circle:    " << area(r) << '\n';
    cout << "Square:    " << area(side, Shape::Square) << '\n';
    cout << "Rectangle: " << area(length, breadth) << '\n';
    return 0;
}
```

**Overload resolution in this program:**

| Call | Candidates | Chosen |
|---|---|---|
| `area(r)` | `area(double)` | circle |
| `area(length, breadth)` | `area(double, double)` | rectangle |
| `area(side, Shape::Square)` | `area(double, Shape)` | square (`Shape` does not convert to `double`) |

| You type | Output |
|---|---|
| radius `2`, side `3`, `4 5` | circle `12.5664`, square `9`, rectangle `20` |
| radius `0`, side `0`, `0 0` | all `0` |
| any negative number | error message |

**Complexity:** O(1).

**Alternative: distinct types (strongest and easiest to read)**
```cpp
struct Circle    { double radius; };
struct Rectangle { double length, breadth; };
struct Square    { double side; };

double area(Circle c)    { return PI * c.radius * c.radius; }
double area(Rectangle r) { return r.length * r.breadth; }
double area(Square s)    { return s.side * s.side; }
// usage: area(Circle{2.0}), area(Square{3.0})
```

**Pitfalls:** two overloads differing only in return type (compile error); ambiguous calls such as `f(5)` with overloads `f(long)` and `f(double)`; relying on `int` vs `double` to select a shape.

**Follow-ups**
- *Is overloading resolved at compile time or run time?* Compile time (static polymorphism); virtual functions are run-time.
- *Default arguments vs overloads?* `area(double l, double b = 1)` is shorter but different semantics.
- *Name mangling:* the compiler encodes parameter types into the symbol name, which is how overloads coexist.

---

# PART 0 (continued) — POINTER AND MEMORY CONCEPTS (read once)

## P1. What a pointer is

A pointer is a **variable that stores a memory address**.

```cpp
int val = 100;
int *ptr = &val;       // ptr holds the ADDRESS of val

//   val:  [ 100 ]     at address 0x1000
//   ptr:  [0x1000]    at address 0x2000   (the pointer is itself a variable with its own address)
```

| Expression | Meaning |
|---|---|
| `&val` | **address of** `val` (`0x1000`) |
| `ptr` | the address stored in the pointer (`0x1000`) |
| `*ptr` | **dereference**: the value at that address (`100`); assigning `*ptr = 5` changes `val` |
| `&ptr` | the address of the pointer variable itself (`0x2000`) |

The `*` in a declaration (`int *ptr`) means "pointer to int". In an expression (`*ptr`) it means "go to the address". Same symbol, two roles.

## P2. `nullptr` and always-initialized pointers

- A pointer that points nowhere must hold **`nullptr`** (C++11), not `NULL` or `0`.
- An **uninitialized** pointer holds garbage (a *wild* pointer): dereferencing it is undefined behavior. Always write `int *p = nullptr;` or initialize with a valid address.
- Dereferencing `nullptr` is undefined behavior (usually a crash), so check `if (p != nullptr)` before using a pointer you did not create yourself.

## P3. Arrays and pointer arithmetic

- The name of an array decays to a pointer to its first element: `arr == &arr[0]`.
- **`arr[i]` is defined as `*(arr + i)`.** Adding `i` to a pointer moves it by `i * sizeof(element)` bytes, not by `i` bytes.
- Pointers into the same array can be compared and subtracted: `p - arr` is the index.
- The idiomatic traversal is a half-open range `[first, last)`: `for (const int *p = first; p != last; ++p)`. `last` may point **one past** the end but must never be dereferenced.

## P4. `const` and pointers

```cpp
const int *p;        // pointer to const int : cannot change *p, can re-point p
int *const p = &x;   // const pointer to int : can change *p, cannot re-point p
const int *const p;  // neither
```

Read the declaration right-to-left. Use `const int *` for parameters that only read.

## P5. Stack vs heap

| | Stack (automatic) | Heap (dynamic) |
|---|---|---|
| Created by | ordinary declarations (`int x;`) | `new`, `new[]` |
| Lifetime | until the enclosing `{ }` ends | until you `delete` it |
| Size | small, fixed at compile time | large, chosen at run time |
| Cleanup | automatic | **your job** |

```cpp
int *p  = new int(5);        // one int, initialised to 5      -> delete p;
int *a  = new int[10];       // 10 ints, uninitialised         -> delete[] a;
int *z  = new int[10]();     // 10 ints, all zero
```

**Rule: `new` ↔ `delete`, `new[]` ↔ `delete[]`.** Mixing them is undefined behavior.

## P6. The four classic pointer bugs

| Bug | What happens | Prevention |
|---|---|---|
| **Memory leak** | `new` without `delete`: memory is never returned | pair every `new` with a `delete`; prefer RAII |
| **Dangling pointer** | pointer to memory that was freed or went out of scope | set to `nullptr` after `delete`; never return the address of a local |
| **Double delete** | `delete` twice on the same address | set to `nullptr` after the first `delete` (`delete nullptr` is safe) |
| **Wild / null dereference** | `*p` with an uninitialised or null pointer | initialise pointers; check for `nullptr` |

## P7. Modern C++: let objects clean up after themselves (RAII)

```cpp
#include <memory>
auto p = make_unique<int>(100);         // freed automatically at the end of the scope
auto a = make_unique<int[]>(10);        // array version
vector<int> v(10);                      // even simpler: a resizable array that manages its own memory
```

Raw `new`/`delete` is still asked in interviews (and in this module), but in real code prefer `unique_ptr`, `shared_ptr` or containers.

## P8. Tools that find memory bugs

```bash
g++ -std=c++17 -g -fsanitize=address,undefined file.cpp -o program   # AddressSanitizer + UBSan
valgrind ./program                                                    # leak and invalid-access checker (Linux)
```

---

# MODULE 4 — POINTERS AND MEMORY

---

## Q25. Pointer Basics

**Review of your solution:** ✅ The core is right (pointer to `val`, dereference, modification through the pointer). Against the question's wording, **something is missing**: it asks to print *the value, the address, and the dereferenced value*. Your program prints the address (through `ptr`), `*ptr`, and the updated `val`, but never prints the original `val` itself or `&val`, so it does not show that `ptr` and `&val` are the same address. Also:

1. 🐞 `empty_ptr` is declared and never used (compiler warning: `unused variable`).
2. The comment "Always reset unused raw pointers to nullptr" is misleading: the rule is **initialize** a pointer to `nullptr` when you have no valid target yet, and **reset** it after you free what it points to.
3. The hard-coded address in the comment (`0x7ff7bfe0`) will differ on every run: fine as an illustration, but say so.

**Problem:** Declare an integer and a pointer to it. Print the value, address, and dereferenced value.

**Concepts:** `&`, `*`, pointer declaration (P1), `nullptr` (P2).

**How to think:** Print all four relevant things side by side so the relationship is obvious: the variable's value, its address (`&val`), the address stored in the pointer (`ptr`), and `*ptr`. The first two address lines must match. Then write through the pointer and show the variable changed.

**Solution**
```cpp
#include <iostream>
using namespace std;

int main() {
    int val = 100;
    int *ptr = &val;                                  // ptr stores the address of val

    cout << "Value of val                : " << val << '\n';
    cout << "Address of val (&val)       : " << &val << '\n';
    cout << "Value stored in ptr (address): " << ptr << '\n';
    cout << "Dereferenced value (*ptr)   : " << *ptr << '\n';
    cout << "Address of ptr itself (&ptr): " << &ptr << '\n';
    cout << "Size of a pointer           : " << sizeof(ptr) << " bytes\n";

    *ptr = 250;                                       // changes val through the pointer
    cout << "\nAfter *ptr = 250, val     : " << val << '\n';

    int *noTarget = nullptr;                          // a pointer with no target yet
    cout << "A null pointer holds        : " << noTarget << '\n';
    if (noTarget == nullptr)
        cout << "so it must not be dereferenced\n";
    return 0;
}
```

**Output** (addresses differ on every run; what matters is that lines 2 and 3 are equal):
```
Value of val                : 100
Address of val (&val)       : 0x7ffd5c1e3a44
Value stored in ptr (address): 0x7ffd5c1e3a44
Dereferenced value (*ptr)   : 100
Address of ptr itself (&ptr): 0x7ffd5c1e3a48
Size of a pointer           : 8 bytes

After *ptr = 250, val     : 250
A null pointer holds        : 0
so it must not be dereferenced
```

**Memory picture:**
```
 address  0x...a44          0x...a48
         +-------+         +------------+
   val   |  250  |  <----  | ptr = 0x...a44 |
         +-------+         +------------+
```

**Complexity:** O(1).

**Pitfalls:** `int *p = 5;` (an integer is not an address: compile error); `int *a, b;` declares `a` as a pointer but `b` as a plain `int`; printing a `char *` with `cout` prints the **string** it points to, not the address (cast to `const void *` to see the address).

**Follow-ups**
- *Pointer size?* 8 bytes on a 64-bit system regardless of the pointed-to type.
- *What is a `void *`?* A pointer to unknown type: cannot be dereferenced without a cast.
- *Pointer to pointer?* `int **pp = &ptr;` and `**pp` is the original value.

---

## Q26. Modify a Variable Through a Pointer

**Review of your solution:** ✅ Correct: the pointer is checked for `nullptr` before dereferencing, and the caller's variable really changes. Improvements:

1. `main` never prints `value` after the call: show it, because "the caller's variable changed" is the whole point.
2. Demonstrate the null check by actually calling the function with `nullptr`.
3. Name the new value clearly (`230043` is a magic number; use a parameter `newValue`).

**Problem:** Write a function that changes a variable's value using a pointer parameter.

**Concepts:** passing an address, dereferencing, null checks (P2), pointer vs reference (F3).

**How to think:** The function receives the **address** of the variable. By writing through it (`*ptr = ...`) it changes the caller's original. The pointer itself is a copy, but both copies hold the same address.

**Solution**
```cpp
#include <iostream>
using namespace std;

// Returns false if the pointer is null (nothing was changed).
bool setValue(int *ptr, int newValue) {
    if (ptr == nullptr) return false;
    *ptr = newValue;
    return true;
}

int main() {
    int value = 100;
    cout << "Before: value = " << value << '\n';

    if (setValue(&value, 230043))
        cout << "After:  value = " << value << '\n';

    if (!setValue(nullptr, 5))
        cout << "Null pointer rejected, nothing modified\n";
    return 0;
}
```

**Output:**
```
Before: value = 100
After:  value = 230043
Null pointer rejected, nothing modified
```

**Dry run:** `&value` is copied into `ptr` → `*ptr = 230043` writes into `value`'s memory → `main` sees the new value.

**Complexity:** O(1).

**Pitfalls:** assigning `ptr = &other` inside the function changes only the local copy of the pointer, not the caller's variable; forgetting the `nullptr` check; calling with an uninitialized pointer.

**Follow-ups**
- *Pointer vs reference version?* `void setValue(int &x, int v) { x = v; }`: shorter, cannot be null.
- *Change the pointer itself from a function?* Pass a pointer to a pointer (`int **`) or a reference to a pointer (`int *&`).
- *Use `const int *` when?* When the function only reads the value.

---

## Q27. Traverse an Array Using Pointers

**Review of your solution:** ✅ Correct (`*(ptr + i)` prints all elements). It is a legitimate use of pointer arithmetic: `arr[i]` is defined as `*(arr + i)`. To show the more idiomatic forms:

1. Move the pointer itself (`++p`) up to an **end pointer** (`arr + n`) instead of indexing with `i`: that is how C++ iterators work.
2. Put the loop in a function taking `(first, last)`, which also matches the standard library convention.
3. Print without a trailing space.

**Problem:** Print all elements using pointer arithmetic instead of array indexing.

**Concepts:** pointer arithmetic (P3), half-open ranges `[first, last)`, `const int *`.

**How to think:** Start a pointer at the first element. While it has not reached "one past the last element", print `*p` and advance with `++p`. Advancing by 1 moves `sizeof(int)` bytes.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

void printWithPointers(const int *first, const int *last) {
    for (const int *p = first; p != last; ++p) {
        if (p != first) cout << ' ';
        cout << *p;
    }
    cout << '\n';
}

int main() {
    int arr[] = {0, 2, 1, 3, 5, 4, 6, 9, 8, 7};
    int n = static_cast<int>(size(arr));

    printWithPointers(arr, arr + n);                 // idiomatic: pointer to pointer range

    for (int i = 0; i < n; i++)                      // your version: base + offset
        cout << *(arr + i) << ' ';
    cout << '\n';

    for (const int *p = arr + n; p != arr;) {        // backwards: step first, then read
        --p;
        cout << *p << ' ';
    }
    cout << '\n';

    cout << "Index of the element holding 9: " << (arr + 7) - arr << '\n';   // pointer difference
    printWithPointers(arr, arr);                     // empty range prints just a newline
    return 0;
}
```

**Output:**
```
0 2 1 3 5 4 6 9 8 7
0 2 1 3 5 4 6 9 8 7 
7 8 9 6 4 5 3 1 2 0 
Index of the element holding 9: 7
(empty line)
```

**Dry run:** `p = arr` → prints `0`; `++p` moves 4 bytes (for `int`) to `arr[1]` → prints `2`; ... stops when `p == arr + 10`.

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** dereferencing `arr + n` (one past the end may be *compared* but never *read*); looping backwards with `for (p = last; p >= arr; --p)`, which forms the pointer `arr - 1`, **before** the array (not allowed): step first and read afterwards as above, or use `reverse_iterator`; mixing pointer types in arithmetic (`int *` moves 4 bytes per step, `char *` moves 1).

**Follow-ups**
- *Why does `p + 1` move 4 bytes?* The compiler scales by `sizeof(*p)`.
- *Relationship to iterators?* `vector::begin()` / `end()` are pointer-like objects with the same `[begin, end)` contract.
- *`arr[i]` vs `i[arr]`?* Both are `*(arr + i)` and `*(i + arr)`: legal (and silly).

---

## Q28. Find the Largest Element Using Pointers

**Review of your solution:** ✅ Correct (`44` for your array). You start from `arr[0]` (good: not `0` or `INT_MIN`) and read through `*(ptr + i)`. Improvements:

1. The loop starts at `i = 0`, comparing `arr[0]` with itself (harmless, one wasted comparison). Start at `first + 1`.
2. Return a **pointer to the maximum** (or `nullptr` for an empty range) instead of printing: then the caller gets both the value (`*p`) and the position (`p - arr`), and the function handles the empty case.

**Problem:** Find the maximum array element using pointers.

**Concepts:** pointer arithmetic, returning a pointer, `[first, last)` ranges, `nullptr` as "not found".

**How to think:** Same running-maximum idea as Level 2 Q1, but the running "best" is a **pointer to the best element**. If the range is empty there is no maximum: return `nullptr`.

**Solution**
```cpp
#include <iostream>
#include <iterator>
using namespace std;

// Pointer to the largest element in [first, last), or nullptr if the range is empty.
const int *maxElement(const int *first, const int *last) {
    if (first == last) return nullptr;
    const int *best = first;
    for (const int *p = first + 1; p != last; ++p)
        if (*p > *best)
            best = p;
    return best;
}

int main() {
    int arr[] = {10, 30, 20, 43, 34, 32, 3, 42, 0, 44, 1};
    int n = static_cast<int>(size(arr));

    const int *best = maxElement(arr, arr + n);
    if (best)
        cout << "Largest: " << *best << " at index " << (best - arr) << '\n';

    int negatives[] = {-8, -3, -20};
    best = maxElement(negatives, negatives + 3);
    cout << "Largest of negatives: " << *best << '\n';

    if (maxElement(arr, arr) == nullptr)
        cout << "Empty range: no maximum\n";
    return 0;
}
```

**Output:**
```
Largest: 44 at index 9
Largest of negatives: -3
Empty range: no maximum
```

**Dry run (`{3, 9, 4}`):** `best → 3`; `p → 9`: `9 > 3` → `best → 9`; `p → 4`: `4 > 9`? no → `*best = 9`.

**Complexity:** O(n) time, O(1) space.

**Pitfalls:** dereferencing the returned pointer without checking for `nullptr` (empty input); returning a pointer to a **local** variable (dangling); `int *` returned from a `const int *` input (const-correctness: the return type must be `const int *`).

**Follow-ups**
- *Standard library?* `max_element(arr, arr + n)` returns exactly this kind of pointer/iterator.
- *Pointer to the minimum? Both min and max in one pass?* Same pattern.
- *Why return a pointer rather than a value?* It carries the position and can represent "not found" (`nullptr`).

---

## Q29. Dynamic Memory Allocation

**Review of your solution:** ✅ Good, careful code: validates the size, catches `std::bad_alloc` (also covers huge sizes that throw `bad_array_new_length`), checks every `cin >> arr[i]`, frees with `delete[]` on the failure path, and resets the pointer to `nullptr`. I tested `5 1 2 3 4 5` (prints the values) and sizes `0`, `-3`, `abc` (rejected). Small improvements:

1. 🐞 **Silent failure:** with too few values (`3 1 2`) the program exits with code 1 and **prints nothing**. Tell the user what went wrong.
2. The array is never *initialized* before use. Allocate with `new int[n]()` (zero-initialized) or fill it explicitly, then show both stages.
3. Mention the modern alternatives (`vector`, `unique_ptr<int[]>`) and test with AddressSanitizer.

**Problem:** Allocate an array with `new[]`, initialize it, print it, and release it correctly.

**Concepts:** heap allocation (P5), `new[]`/`delete[]` pairing, exceptions from `new`, `nothrow`, RAII (P7).

**How to think:** `new int[n]` returns the address of `n` contiguous ints on the heap. Its elements are **indeterminate** unless you initialize them (`new int[n]()` zeroes them). Every successful `new[]` needs exactly one `delete[]` on **every** path out of the function (including error returns).

**Solution**
```cpp
#include <iostream>
#include <new>
using namespace std;

int main() {
    int n;
    cout << "Enter array size: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid array size\n";
        return 1;
    }

    int *arr = nullptr;
    try {
        arr = new int[n]();                          // () zero-initialises every element
    } catch (const bad_alloc &) {
        cout << "Memory allocation failed\n";
        return 1;
    }

    cout << "Freshly allocated (zero-initialised): ";
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << '\n';

    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> arr[i])) {
            cout << "Invalid or missing input\n";
            delete[] arr;                            // free on the error path too
            return 1;
        }
    }

    cout << "Values: ";
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << '\n';

    delete[] arr;                                    // new[] -> delete[]
    arr = nullptr;                                   // no dangling pointer left behind
    return 0;
}
```

| You type | Output |
|---|---|
| `5` then `1 2 3 4 5` | zeros, then `Values: 1 2 3 4 5` |
| `0` or `-3` or `abc` | `Invalid array size` |
| `3` then `1 2` (too few) | `Invalid or missing input` (and the memory is freed) |

**Dry run (n = 3):** `new int[3]()` → heap block `[0][0][0]` → user fills `[7][8][9]` → print → `delete[]` returns the block → `arr = nullptr`.

**Complexity:** O(n) time and O(n) heap memory.

**Mistakes to avoid**
| Mistake | Result |
|---|---|
| `delete arr;` for memory from `new[]` | undefined behavior (use `delete[]`) |
| forgetting `delete[]` on an early `return` | memory leak |
| using `arr[i]` after `delete[]` | use-after-free (dangling pointer) |
| reading `arr[i]` of `new int[n]` before writing | garbage values |

**Modern equivalents (preferred in real code)**
```cpp
#include <memory>
#include <vector>
auto up = make_unique<int[]>(n);   // freed automatically
vector<int> v(n);                  // freed automatically, can also grow
```

**Check for leaks:** `g++ -g -fsanitize=address file.cpp && ./a.out`: AddressSanitizer reports leaks and invalid accesses.

**Follow-ups**
- *`new` vs `malloc`?* `new` calls constructors and throws on failure; `malloc` returns `nullptr` and knows nothing about objects. Never mix `new` with `free`.
- *2D dynamic arrays?* An array of row pointers, each from its own `new[]`, or one flat block indexed `a[i * cols + j]`.
- *What does `new (nothrow) int[n]` do?* Returns `nullptr` instead of throwing.

---

## Q30. Pointer Safety

**Review of your solution:** 🐞 The code you wrote is correct and safe: a `safePrint` helper that checks for `nullptr`, allocation with `new`, `delete`, and reset to `nullptr`. But it **does not cover the whole problem statement**. Compared with the six required parts:

| Requirement | Your code |
|---|---|
| 1. Null pointer + check before access | ✅ |
| 2. Pointer to an **integer variable** (its address), validated and printed | ❌ missing (you only used heap memory) |
| 3. `new`, assign, print | ✅ |
| 4. `delete` and reset to `nullptr` | ✅ |
| 5. **Demonstrate and explain a dangling pointer** (without dereferencing it) | ❌ missing: resetting one pointer does not show what a dangling pointer is |
| 6. Never dereference null/dangling | ✅ |

In an interview, answering a question with only some of the listed items is the most common way to lose points, so tick every bullet before submitting.

**Problem:** Demonstrate null pointers, pointer validation, dynamic memory, deallocation, and dangling pointers, safely.

**Concepts:** `nullptr`, validation (P2), heap lifetime (P5), the four pointer bugs (P6), RAII (P7).

**How to think:** A **dangling pointer** is a pointer that still holds an address whose memory has been freed. The classic way to *create* one is to have **two** pointers to the same heap block and free through one of them: the other becomes dangling. Resetting the pointer you freed through does not fix the other one. We create the situation, explain it, **never dereference it**, and then cure it by resetting that pointer as well. We do not even print the dangling pointer's value: reading an invalid pointer value is implementation-defined.

**Solution**
```cpp
#include <iostream>
using namespace std;

// Prints *ptr only when it is safe to do so.
void safePrint(const char *label, const int *ptr) {
    if (ptr != nullptr)
        cout << label << ": value = " << *ptr << '\n';
    else
        cout << label << ": pointer is null, NOT dereferencing\n";
}

int main() {
    // 1. Null pointer: initialised to "points nowhere", checked before use.
    int *nullPtr = nullptr;
    safePrint("1. null pointer", nullPtr);

    // 2. Valid pointer to an ordinary (stack) variable, validated before use.
    int local = 42;
    int *validPtr = &local;
    safePrint("2. pointer to a local variable", validPtr);

    // 3. Dynamic allocation: allocate, assign, print.
    int *heapPtr = new int(100);
    safePrint("3. heap pointer", heapPtr);
    *heapPtr = 200;
    safePrint("3. after assignment", heapPtr);

    // 5. (set-up) A second pointer to the SAME heap block.
    int *alias = heapPtr;

    // 4. Deallocate and reset the pointer we freed through.
    delete heapPtr;
    heapPtr = nullptr;
    safePrint("4. after delete + reset", heapPtr);

    // 5. 'alias' still holds the old address, but that memory has been released.
    //    It is now a DANGLING pointer: dereferencing it is undefined behavior
    //    (the memory may be reused, unmapped, or still hold stale data), so we
    //    do not touch it. The cure is to reset it too.
    cout << "5. 'alias' is now dangling (not dereferenced)\n";
    alias = nullptr;
    safePrint("5. alias after reset", alias);

    return 0;
}
```

**Output:**
```
1. null pointer: pointer is null, NOT dereferencing
2. pointer to a local variable: value = 42
3. heap pointer: value = 100
3. after assignment: value = 200
4. after delete + reset: pointer is null, NOT dereferencing
5. 'alias' is now dangling (not dereferenced)
5. alias after reset: pointer is null, NOT dereferencing
```

**Why dereferencing a dangling pointer is undefined behavior:** after `delete`, the allocator owns that memory again. It may hand it to a later `new`, so you would read or corrupt someone else's data; it may be returned to the operating system, causing a crash; or it may still contain the old bytes, so the bug appears to "work" in testing and fails in production. The language gives no guarantee, which is exactly what "undefined" means.

**Pointer problems at a glance (all avoided above):**

| Problem | Example | How this program avoids it |
|---|---|---|
| Null dereference | `*nullPtr` | `safePrint` checks first |
| Wild pointer | `int *p; *p = 1;` | every pointer is initialised |
| Dangling pointer | use `alias` after `delete heapPtr` | `alias` is never used, then reset |
| Double delete | `delete heapPtr; delete heapPtr;` | `heapPtr = nullptr` (and `delete nullptr` is harmless) |
| Leak | missing `delete` | exactly one `delete` for the one `new` |
| Dangling from a local | `return &local;` | never returns addresses of locals |

**Another classic dangling pointer (do not run): returning the address of a local**
```cpp
int *bad() {
    int x = 5;
    return &x;      // x dies when the function returns -> dangling pointer
}
```

**The modern fix: smart pointers**
```cpp
#include <memory>
auto p = make_unique<int>(100);   // single owner, deleted automatically, cannot dangle by mistake
// auto q = p;                    // does not compile: ownership cannot be copied
shared_ptr<int> a = make_shared<int>(7);
shared_ptr<int> b = a;            // shared ownership: freed when the LAST owner goes away
```

**Complexity:** O(1).

**Follow-ups**
- *What is the difference between a null, a wild and a dangling pointer?* Null = points to nothing on purpose. Wild = never initialized. Dangling = was valid, now points to freed memory.
- *Does `delete ptr;` change `ptr`?* No. It frees the memory but leaves the pointer value alone: that is why you assign `nullptr` yourself.
- *Is `delete nullptr;` safe?* Yes, it does nothing.
- *How do you catch these bugs automatically?* AddressSanitizer (`-fsanitize=address`) reports use-after-free and double free; Valgrind reports leaks.

---

---

# PART 0 (continued) — RECURSION CONCEPTS (read once)

## R1. What recursion is

A function is **recursive** if it calls itself. Every correct recursive solution has three parts:

1. **Base case:** an input so small that the answer is known directly (`factorial(0) = 1`). Without it the function never stops.
2. **Recursive case:** reduce the problem to a **strictly smaller** version of itself (`n! = n × (n − 1)!`).
3. **Trust:** assume the recursive call returns the right answer for the smaller input, and only worry about how to combine it with the current step. Do not mentally unroll every call.

```cpp
unsigned long long factorial(int n) {
    if (n <= 1) return 1;                 // 1. base case
    return n * factorial(n - 1);          // 2. smaller problem: n-1,  3. combine with n
}
```

## R2. The call stack

Every call gets its own **stack frame** holding its parameters and local variables. Calls pile up on the way down and return on the way back up:

```
factorial(3)
  -> 3 * factorial(2)
        -> 2 * factorial(1)
              -> returns 1
        -> returns 2 * 1 = 2
  -> returns 3 * 2 = 6
```

The stack is limited (typically about 1 MB on Windows and 8 MB on Linux, enough for roughly 10,000 to 100,000 frames). **Too many nested calls = stack overflow = crash** (a segmentation fault). That is what happens with a missing base case or with very deep recursion (for example, recursing once per character of a 10-million-character string).

## R3. Recursion vs iteration

| | Recursion | Iteration (loop) |
|---|---|---|
| Memory | O(depth) stack space | usually O(1) |
| Speed | function-call overhead | faster |
| Best for | trees, divide and conquer, backtracking, naturally recursive definitions | simple counting and scanning |

A call is a **tail call** when it is the very last thing the function does (nothing left to compute afterwards). Compilers *may* turn tail calls into loops, but C++ does not guarantee it, so never rely on it to avoid deep stacks.

```cpp
unsigned long long factorialAcc(int n, unsigned long long acc = 1) {   // accumulator style
    if (n <= 1) return acc;
    return factorialAcc(n - 1, acc * n);                                // the call is the last action
}
```

## R4. Complexity of recursive functions (recurrences)

| Problem | Recurrence | Time | Stack depth |
|---|---|---|---|
| factorial, sum of digits | `T(n) = T(n−1) + O(1)` | O(n) (digits: O(log n)) | O(n) |
| reverse string (ends) | `T(n) = T(n−2) + O(1)` | O(n) | O(n) |
| **naive** Fibonacci | `T(n) = T(n−1) + T(n−2)` | **O(2ⁿ)** | O(n) |
| memoized Fibonacci | each `F(i)` computed once | O(n) | O(n) |
| fast power | `T(n) = T(n/2) + O(1)` | O(log n) | O(log n) |
| binary search | `T(n) = T(n/2) + O(1)` | O(log n) | O(log n) |
| Tower of Hanoi | `T(n) = 2T(n−1) + 1` | **O(2ⁿ)** (exactly 2ⁿ − 1 moves) | O(n) |

Rule of thumb: **one recursive call** per step gives a linear (or logarithmic) chain; **two calls on nearly the same size** gives an exponential tree.

## R5. Memoization

If the same sub-problem is solved again and again, **store its answer** the first time and reuse it. This turns exponential time into polynomial time (top-down dynamic programming). See Q32: 2,692,537 calls become 59.

## R6. How to write and debug a recursive function

1. Write the **base case first**. Ask: what are the smallest inputs (0, 1, empty)? What if the caller passes something even smaller (negative, `nullptr`, empty string)?
2. Check that every recursive call moves **toward** the base case (`n - 1`, `left + 1`), never away or sideways.
3. Trace `n = 0`, `1`, `2` on paper before running.
4. Watch for overflow in the return values (factorials, Fibonacci, powers).
5. If the function has an "internal" parameter (an index, an accumulator), hide it behind a public wrapper so callers cannot misuse it.

---

# MODULE 5 — RECURSION

---

## Q31. Factorial Using Recursion

**Review of your solution:** ✅ Correct. `n <= 1` is the right base case (it covers both `0! = 1` and `1! = 1`), the multiplication is done in `unsigned long long`, and `main` rejects negatives and anything above 20 before calling. I verified `0, 1, 5, 20` (`2432902008176640000`), `21` (overflow message), `-3` and non-numeric input. Improvements:

1. **The overflow guard lives in `main`**, so the function itself is unsafe if called with 21 or more (it silently wraps). Put the validation next to the function (a wrapper), so any caller is protected.
2. `<limits>` is included but unused.
3. Know the accumulator (tail-recursive) form and the iterative form: interviewers often ask for them as a follow-up (see R3).

**Problem:** Calculate the factorial of a non-negative integer recursively.

**Concepts:** base case, recursive case, call stack (R1, R2), overflow (Level 1, Q13).

**How to think:** `n! = n × (n − 1)!`, and `0! = 1! = 1`. Each call asks for the factorial of a number one smaller, until it reaches 1. The answer is then built on the way **back up** by multiplying.

**Solution**
```cpp
#include <iostream>
using namespace std;

// Precondition: 0 <= n <= 20 (checked by factorial() below).
unsigned long long factorialRec(int n) {
    if (n <= 1) return 1;                                      // base case: 0! = 1! = 1
    return static_cast<unsigned long long>(n) * factorialRec(n - 1);
}

// Safe entry point: returns false when the result would not exist or not fit.
bool factorial(int n, unsigned long long &result) {
    if (n < 0 || n > 20) return false;                         // 21! > ULLONG_MAX
    result = factorialRec(n);
    return true;
}

int main() {
    int n;
    cout << "Enter a non-negative integer: ";
    if (!(cin >> n)) {
        cout << "Invalid input\n";
        return 1;
    }

    unsigned long long result;
    if (factorial(n, result))
        cout << n << "! = " << result << '\n';
    else if (n < 0)
        cout << "Factorial is not defined for negative numbers\n";
    else
        cout << "Overflow: " << n << "! does not fit in unsigned long long (maximum n is 20)\n";
    return 0;
}
```

**Dry run (`factorialRec(4)`):**

| call | goes down | comes back up |
|---|---|---|
| `factorialRec(4)` | needs `factorialRec(3)` | `4 * 6 = 24` |
| `factorialRec(3)` | needs `factorialRec(2)` | `3 * 2 = 6` |
| `factorialRec(2)` | needs `factorialRec(1)` | `2 * 1 = 2` |
| `factorialRec(1)` | **base case** | `1` |

| You type | Output |
|---|---|
| `0` | `0! = 1` |
| `1` | `1! = 1` |
| `5` | `5! = 120` |
| `20` | `20! = 2432902008176640000` |
| `21` | overflow message |
| `-3` | not defined for negative numbers |
| `abc` | `Invalid input` |

**Complexity:** O(n) time, O(n) stack space (n frames). With the limit of 20, the depth is tiny.

**Pitfalls:** a base case of `n == 0` only (then `factorial(1)` still works, but a negative `n` recurses forever); `int` for the result (overflows at 13!); forgetting the cast so the multiplication happens in `int` before widening.

**Follow-ups**
- *Iterative version?* A loop with `result *= i`: O(n) time, O(1) space (Level 1, Q13).
- *Tail-recursive version?* `factorialAcc(n - 1, acc * n)` from R3.
- *Factorial of 100?* Needs big-integer arithmetic (an array of digits) or modular arithmetic.
- *What happens with `factorial(1000000)`?* Stack overflow long before the multiplication matters.

---

## Q32. Fibonacci Using Recursion

**Review of your solution:** ✅ Memoization is correct and fast: `fibonacci(i, memo)` is O(n) and each `F(i)` is computed once. The check `memo[n] != 0` works as a "not computed yet" marker because `F(n)` is never zero for `n ≥ 2` (a neat subtlety worth saying out loud). Problems I found by testing:

1. 🐞 **No overflow guard.** `F(93) = 12200160415121876738` is the last Fibonacci number that fits in `unsigned long long`. For `n = 94` your program prints `1293530146158671551`, which is the true value **mod 2⁶⁴**, with no warning. Anything from 94 upward is silently wrong.
2. 🐞 **Huge input crashes.** `std::vector<unsigned long long> memo(num + 1, 0)` computes `num + 1` in `int`, which overflows (undefined behavior) when `num == INT_MAX`; and a large `num` asks for gigabytes: `2147483647` requests about 16 GB and throws an uncaught `std::bad_alloc`. Validating `0 ≤ n ≤ 93` fixes both.
3. The question asks to *generate Fibonacci numbers using a recursive function*. You went straight to the optimized version. In an interview, write the **plain recursive** definition first and show *why* it is slow, then memoize (below).
4. Small things: a trailing space in the output and the message "not define" (typo).

**Problem:** Generate Fibonacci numbers with a recursive function.

**Concepts:** two recursive calls (exponential tree), memoization (R5), overflow limits.

**How to think**
- Definition: `F(0) = 0`, `F(1) = 1`, `F(n) = F(n − 1) + F(n − 2)`. That is already a recursive function.
- *Plain version:* `fib(n)` calls `fib(n−1)` and `fib(n−2)`, and both of those recompute the same values again and again. The number of calls is `2·F(n+1) − 1`: exponential.
- *Memoized version:* remember each `F(i)` in a table. Every value is computed once, so about `2n − 1` calls in total.

**Solution**
```cpp
#include <iostream>
#include <vector>
using namespace std;

long long calls = 0;                       // counts function calls, to compare the two versions

unsigned long long fibSlow(int n) {        // plain recursion: O(2^n) time
    calls++;
    if (n <= 1) return static_cast<unsigned long long>(n);
    return fibSlow(n - 1) + fibSlow(n - 2);
}

unsigned long long fibMemo(int n, vector<unsigned long long> &memo) {   // memoized: O(n) time
    calls++;
    if (n <= 1) return static_cast<unsigned long long>(n);
    if (memo[n] != 0) return memo[n];      // 0 means "not computed yet" (safe: F(n) > 0 for n >= 2)
    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
}

int main() {
    const int MAX_N = 93;                  // F(93) is the largest value that fits in unsigned long long
    int n;
    cout << "Enter n (0 to " << MAX_N << "): ";
    if (!(cin >> n) || n < 0 || n > MAX_N) {
        cout << "Invalid input: n must be between 0 and " << MAX_N << '\n';
        return 1;
    }

    vector<unsigned long long> memo(n + 1, 0);
    cout << "Fibonacci numbers F(0)..F(" << n << "): ";
    for (int i = 0; i <= n; i++) {
        if (i > 0) cout << ' ';
        cout << fibMemo(i, memo);
    }
    cout << '\n';

    if (n <= 35) {                         // plain recursion is too slow beyond this
        calls = 0;
        fibSlow(n);
        long long slowCalls = calls;

        vector<unsigned long long> fresh(n + 1, 0);
        calls = 0;
        fibMemo(n, fresh);
        cout << "Calls to compute F(" << n << "): plain = " << slowCalls
             << ", memoized = " << calls << '\n';
    }
    return 0;
}
```

**Call tree of plain `fib(4)`** (the repeated work is visible):
```
fib(4)
├── fib(3)
│   ├── fib(2)
│   │   ├── fib(1)
│   │   └── fib(0)
│   └── fib(1)
└── fib(2)            <- computed again
    ├── fib(1)
    └── fib(0)
```

| You type | Output |
|---|---|
| `0` | `F(0)..F(0): 0`, calls: plain 1, memoized 1 |
| `1` | `0 1` |
| `10` | `0 1 1 2 3 5 8 13 21 34 55`, calls: plain **177**, memoized **19** |
| `30` | ends in `832040`, calls: plain **2,692,537**, memoized **59** |
| `35` | calls: plain **29,860,703**, memoized **69** |
| `93` | works (the last value is `12200160415121876738`) |
| `94` or `-1` | `Invalid input: n must be between 0 and 93` |

**Complexity:** plain O(2ⁿ) time; memoized O(n) time and O(n) space (table plus recursion depth).

**Pitfalls:** unguarded overflow; using `memo[n] == 0` as the marker when `0` can be a real answer (it is only safe here because `F(0)` and `F(1)` are handled before the lookup); sizing the table with `n + 1` in `int` without a range check.

**Follow-ups**
- *Iterative version?* Two variables, O(n) time, O(1) space (Level 1, Q14).
- *Faster than O(n)?* Matrix exponentiation or the fast-doubling method gives O(log n).
- *Why is the plain version exponential?* `T(n) = T(n−1) + T(n−2) + 1`, which grows like the golden ratio to the power `n` (about `1.618ⁿ`).
- *Bottom-up vs top-down?* Filling the table in a loop from 0 upwards (bottom-up) avoids recursion entirely.

---

## Q33. Sum of Digits Using Recursion

**Review of your solution:** ✅ Correct, and the sign handling is excellent. `0u - static_cast<unsigned int>(num)` computes the absolute value in **unsigned arithmetic**, which is well defined (it wraps modulo 2³²) and, unlike `-num`, also works for `INT_MIN`. I verified `0` → 0, `583` → 16, `-123` → 6, `2147483647` → 46 and `-2147483648` → 47. Small notes: the output wording ("Sum of digit"), and the return type `unsigned long long` is more than needed (the maximum sum for 10 digits is 90): `int` would do.

**Problem:** Calculate the sum of an integer's digits recursively.

**Concepts:** `n % 10` and `n / 10` (Level 1 digit toolkit), base case `n == 0`, absolute value without overflow.

**How to think:** The sum of the digits of `n` is *the last digit* plus *the sum of the digits of everything before it*: `sum(583) = 3 + sum(58) = 3 + 8 + sum(5) = 3 + 8 + 5 + sum(0)`, and `sum(0) = 0` is the base case.

**Solution**
```cpp
#include <iostream>
using namespace std;

int sumOfDigits(unsigned int n) {
    if (n == 0) return 0;                       // base case: no digits left
    return static_cast<int>(n % 10) + sumOfDigits(n / 10);
}

int main() {
    int num;
    cout << "Enter an integer: ";
    if (!(cin >> num)) {
        cout << "Invalid input\n";
        return 1;
    }

    // |num| in unsigned arithmetic: well defined, and correct even for INT_MIN.
    unsigned int magnitude = (num < 0) ? 0u - static_cast<unsigned int>(num)
                                       : static_cast<unsigned int>(num);

    cout << "Sum of the digits of " << num << " is " << sumOfDigits(magnitude) << '\n';
    return 0;
}
```

**Dry run (`583`):**

| call | n % 10 | returns |
|---|---|---|
| `sumOfDigits(583)` | 3 | `3 + sumOfDigits(58)` |
| `sumOfDigits(58)` | 8 | `8 + sumOfDigits(5)` |
| `sumOfDigits(5)` | 5 | `5 + sumOfDigits(0)` |
| `sumOfDigits(0)` | | **0** (base case) |

Unwinding: `5 + 0 = 5` → `8 + 5 = 13` → `3 + 13 = 16`.

| You type | Output |
|---|---|
| `583` | `16` |
| `0` | `0` |
| `-123` | `6` |
| `2147483647` | `46` |
| `-2147483648` | `47` (the `INT_MIN` case) |

**Complexity:** O(log₁₀ n) time and stack depth (one call per digit, at most 10).

**Pitfalls:** `-num` for `INT_MIN` (overflow, undefined behavior); using base case `n < 10` and forgetting that `n = 0` must still give `0`; negative `%` results (`-123 % 10 == -3`) if you skip the absolute value.

**Follow-ups**
- *Digital root recursively?* `while`/recursion: `digitalRoot(n) = n < 10 ? n : digitalRoot(sumOfDigits(n))`.
- *Count the digits, reverse a number, or check a palindrome recursively?* Same `% 10` / `/ 10` pattern.
- *Iterative version?* Level 1, Q15.

---

## Q34. Reverse a String Recursively

**Review of your solution:** ✅ Correct: swap the character at `left` with its mirror and recurse on `left + 1`; the base case `left >= size / 2` stops exactly at the middle (tested: empty, one character, even, odd, spaces). Using `std::swap` is fine, since the question only forbids a built-in *reverse*. Improvements:

1. The default argument `left = 0` exposes an **internal bookkeeping parameter** to every caller (`reverseString(text, 5)` compiles and gives nonsense). Hide it behind a wrapper (R6).
2. The recursion depth is `n / 2`. For a very long string (millions of characters) this overflows the stack, while a loop would not. Mention the trade-off.
3. Prefer explicit `left` and `right` indices: the base case `left >= right` is easier to read than `left >= size / 2`.

**Problem:** Reverse a string using recursion, without a built-in reverse function.

**Concepts:** recursion on indices, shrinking the problem from both ends, helper + wrapper pattern.

**How to think:** To reverse a string, swap its first and last characters, then reverse **what is in between**, a shorter string of the same kind. The problem is solved when the two indices meet or cross (0 or 1 characters left).

**Solution**
```cpp
#include <iostream>
#include <string>
#include <utility>
using namespace std;

// Reverses s[left..right] in place.
void reverseHelper(string &s, int left, int right) {
    if (left >= right) return;                 // base case: 0 or 1 characters left
    swap(s[left], s[right]);                   // swap the two ends
    reverseHelper(s, left + 1, right - 1);     // reverse the middle part
}

void reverseString(string &s) {                // public entry point
    reverseHelper(s, 0, static_cast<int>(s.size()) - 1);
}

int main() {
    string s;
    cout << "Enter a string: ";
    if (!getline(cin, s)) {
        cout << "No input\n";
        return 0;
    }

    reverseString(s);
    cout << "Reversed: " << s << '\n';
    return 0;
}
```

**Dry run (`"abcd"`):**

| call | left, right | action | string |
|---|---|---|---|
| 1 | 0, 3 | swap `a` ↔ `d` | `dbca` |
| 2 | 1, 2 | swap `b` ↔ `c` | `dcba` |
| 3 | 2, 1 | `left >= right`: **base case** | `dcba` |

| You type | Output |
|---|---|
| `hello` | `olleh` |
| `Hello World` | `dlroW olleH` |
| `a` | `a` |
| `ab` | `ba` |
| *(empty line)* | *(empty)* (`right = -1`, so the base case triggers at once) |

**Complexity:** O(n) time (n/2 swaps), O(n) stack space (n/2 frames).

**Another way of thinking (elegant, but O(n²))**
```cpp
string reverseCopy(const string &s) {
    if (s.size() <= 1) return s;
    return reverseCopy(s.substr(1)) + s[0];     // reverse(rest) followed by the first character
}
```
It is easy to explain, but every `substr` and `+` copies the string, so it costs O(n²) time. Know it, then prefer the in-place version.

**Pitfalls:** a base case of `left == right` only (even-length strings skip past each other and recurse forever); using `size() - 1` with unsigned values on an empty string; deep recursion on huge strings.

**Follow-ups**
- *Iterative version?* Level 2, Q11 (two pointers, O(1) space, no stack risk).
- *Palindrome check recursively?* Compare `s[left]` and `s[right]`, then recurse inward.
- *Reverse the words of a sentence?* Reverse the whole string, then each word.

---

## Q35. Calculate Power Recursively

**Review of your solution:** ✅ The algorithm is excellent: **fast exponentiation** (`x^n = (x^(n/2))²`, times `x` when `n` is odd) gives O(log n) calls instead of O(n), the base case returns `1.0` (so `0^0 = 1`, the standard convention) and the exponent is validated. One problem, which I tested:

1. 🐞 **The output format hides the answer.** `cout` prints a `double` with 6 significant digits, so `2^20` prints as `1.04858e+06` and `2^62` as `4.61169e+18` instead of `1048576` and `4611686018427387904`. It is the same trap as Level 1, Q22. Either print with `setprecision` or, for integer bases, compute in `long long` and **detect overflow** (the first version below).
2. With integers, a result that does not fit should be reported, not rounded.

**Problem:** Calculate `a^b` recursively for a non-negative exponent.

**Concepts:** divide and conquer (R4), fast exponentiation, overflow-checked multiplication, `0^0`.

**How to think**
- *Simple recursion:* `a^b = a × a^(b−1)`, base case `a^0 = 1`. It works but needs `b` calls: with `b = 10⁹` the stack overflows.
- *Halving:* `a^b = (a^(b/2))²` for even `b`, and `a × (a^(b/2))²` for odd `b`. The exponent halves each time, so there are only about `log₂ b` calls.
- Compute the half **once** and reuse it (do not call the recursive function twice, or you lose the speed-up).
- For integers, each multiplication needs an overflow check.

**Solution**
```cpp
#include <climits>
#include <iomanip>
#include <iostream>
using namespace std;

// result = a * b, or false if the product does not fit in a long long.
bool safeMultiply(long long a, long long b, long long &result) {
    if (a > 0) {
        if (b > 0) { if (a > LLONG_MAX / b) return false; }
        else       { if (b < LLONG_MIN / a) return false; }
    } else if (a < 0) {
        if (b > 0) { if (a < LLONG_MIN / b) return false; }
        else       { if (b < LLONG_MAX / a) return false; }
    }
    result = a * b;
    return true;
}

// Integer power by repeated halving. Returns false on overflow.
bool powerInt(long long base, unsigned long long exp, long long &result) {
    if (exp == 0) {                                  // base case: a^0 = 1 (including 0^0)
        result = 1;
        return true;
    }
    long long half;
    if (!powerInt(base, exp / 2, half)) return false;    // computed ONCE and reused

    long long square;
    if (!safeMultiply(half, half, square)) return false;

    if (exp % 2 == 0) {
        result = square;
        return true;
    }
    return safeMultiply(square, base, result);           // odd exponent: one extra factor
}

// Real-number version (your original idea).
double powerDouble(double x, unsigned long long n) {
    if (n == 0) return 1.0;
    double half = powerDouble(x, n / 2);
    return (n % 2 == 0) ? half * half : x * half * half;
}

int main() {
    long long base, exponent;
    cout << "Enter an integer base and a non-negative exponent: ";
    if (!(cin >> base >> exponent)) {
        cout << "Invalid input\n";
        return 1;
    }
    if (exponent < 0) {
        cout << "Negative exponent is not allowed\n";
        return 1;
    }

    long long result;
    if (powerInt(base, static_cast<unsigned long long>(exponent), result))
        cout << base << "^" << exponent << " = " << result << '\n';
    else
        cout << base << "^" << exponent << " does not fit in a long long (overflow)\n";

    cout << setprecision(10)
         << "Real-number examples: 2.5^3 = " << powerDouble(2.5, 3)
         << ", 2^20 = " << powerDouble(2, 20) << '\n';
    return 0;
}
```

**Dry run (`power(3, 5)`):**

| call | exp | half | computed |
|---|---|---|---|
| `power(3, 5)` | 5 (odd) | `power(3, 2)` = 9 | `3 * 9 * 9 = 243` |
| `power(3, 2)` | 2 (even) | `power(3, 1)` = 3 | `3 * 3 = 9` |
| `power(3, 1)` | 1 (odd) | `power(3, 0)` = 1 | `3 * 1 * 1 = 3` |
| `power(3, 0)` | 0 | | **1** (base case) |

Only 4 calls for `exp = 5` (exponents 5, 2, 1, 0); in general `⌊log₂ exp⌋ + 2`.

| You type (base exponent) | Output |
|---|---|
| `2 10` | `2^10 = 1024` |
| `2 20` | `2^20 = 1048576` (your `double` version printed `1.04858e+06`) |
| `2 62` | `2^62 = 4611686018427387904` |
| `2 63` | overflow message |
| `-2 3` | `-2^3 = -8` |
| `0 0` | `0^0 = 1` |
| `3 39` / `3 40` | `4052555153018976267` / overflow |
| `1 1000000000` | `1` (31 calls, no loop of a billion steps) |
| `5 -1` | negative exponent rejected |

**Complexity:** O(log b) time and O(log b) stack space. The naive `a × a^(b−1)` is O(b) and overflows the stack for large `b`.

**Pitfalls:** calling `power(x, n/2)` twice (`power(x,n/2) * power(x,n/2)`) turns O(log n) back into O(n); not handling the odd exponent; printing a `double` without `setprecision`; assuming `0^0` is undefined (it is `1` by convention here).

**Follow-ups**
- *Negative exponent?* `1 / a^|b|` with `double`.
- *Modular power (`a^b mod m`)?* Take `% m` after every multiplication: the foundation of RSA-style cryptography.
- *Iterative form?* Loop over the bits of the exponent (Level 1, Q22 bonus).

---

## Q36. Binary Search Recursively

**Review of your solution:** ✅ Very good, and it avoids three classic traps:

1. **Half-open interval `[low, high)`** with `size_t`. The usual version (`high = mid - 1`) underflows when `mid == 0` and `low`/`high` are unsigned; your `high = mid` never does.
2. **`mid = low + (high - low) / 2`** instead of `(low + high) / 2` (which can overflow for huge indices).
3. The base case `low >= high` correctly means "empty range, not found", and the return type `ptrdiff_t` can hold `-1`.

I tested: first element, last element, a middle element, absent values on both ends and in the middle, an empty vector, a single element, and duplicates. All correct. Notes: the array and target were hard-coded, so the program tests only one case; and with **duplicates** it returns *some* matching index (for `{1,2,2,2,3}` and target `2` it returns index 2), not necessarily the first. The precondition (the array must be sorted) is not checked.

**Problem:** Implement binary search recursively on a sorted array.

**Concepts:** divide and conquer, halving the search range, half-open intervals, preconditions.

**How to think:** Compare the target with the **middle** element. If equal, done. If the middle is bigger than the target, the answer can only be in the left half; otherwise only in the right half. Each call discards half of the remaining elements. An empty range means the target is not there.

**Solution** (your function, with input from the user)
```cpp
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

// Searches arr[low, high). Returns the index of a match, or -1.
ptrdiff_t binarySearch(const vector<int> &arr, int target, size_t low, size_t high) {
    if (low >= high) return -1;                          // empty range: not found

    size_t mid = low + (high - low) / 2;                 // no overflow, no underflow

    if (arr[mid] == target) return static_cast<ptrdiff_t>(mid);
    if (arr[mid] > target)  return binarySearch(arr, target, low, mid);       // left half
    return binarySearch(arr, target, mid + 1, high);                          // right half
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }

    vector<int> arr(n);
    cout << "Enter " << n << " integers in ascending order: ";
    for (int &x : arr) {
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
    }
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            cout << "The array must be sorted in ascending order\n";
            return 1;
        }
    }

    int target;
    cout << "Enter the target: ";
    if (!(cin >> target)) {
        cout << "Invalid input\n";
        return 1;
    }

    ptrdiff_t index = binarySearch(arr, target, 0, arr.size());
    if (index != -1) cout << "Found at index " << index << '\n';
    else             cout << "Not found\n";
    return 0;
}
```

**Dry run (your array, target `455`):**

| call | [low, high) | mid | arr[mid] | decision |
|---|---|---|---|---|
| 1 | [0, 12) | 6 | 87 | `87 < 455` → right: `[7, 12)` |
| 2 | [7, 12) | 9 | 92 | `92 < 455` → right: `[10, 12)` |
| 3 | [10, 12) | 11 | 6345 | `6345 > 455` → left: `[10, 11)` |
| 4 | [10, 11) | 10 | 455 | **found, index 10** |

4 calls for 12 elements (`⌈log₂ 13⌉ = 4`).

| Input | Result |
|---|---|
| target `2` (first) | index `0` |
| target `6345` (last) | index `11` |
| target `455` | index `10` |
| target `1` / `100` (absent) | not found |
| empty array | not found |
| `{7}`, target `7` / `8` | index `0` / not found |
| `{1,2,2,2,3}`, target `2` | index `2` (one of the matches) |

**Complexity:** O(log n) time and O(log n) stack. The recursive call is a **tail call**, so an iterative loop (Q38) uses O(1) space.

**Pitfalls:** running it on an unsorted array (wrong answers, no error); `(low + high) / 2` overflow for `int` indices near 2³⁰; `high = mid - 1` with unsigned types; infinite recursion when the range does not shrink (`low = mid` instead of `mid + 1`).

**Follow-ups**
- *Find the **first** occurrence (lower bound)?* When `arr[mid] == target`, keep searching the left half and remember `mid`.
- *Standard library?* `binary_search`, `lower_bound`, `upper_bound` in `<algorithm>`.
- *Search in a rotated sorted array? Find the square root of a number?* Same halving idea on a different predicate.

---

## Q37. Tower of Hanoi

**Review of your solution:** ✅ The structure is the textbook solution: move `n − 1` disks to the helper rod, move the largest disk, then move the `n − 1` disks onto it. I traced and verified the output for 3 disks: 7 legal moves (`A→C, A→B, C→B, A→C, B→A, B→C, A→C`). One bug and two weaknesses:

1. 🐞 **The base case is `n == 1` only, so `TOH(0, ...)` never stops.** `n = 0` calls `TOH(-1)`, then `TOH(-2)`, ... until the stack overflows. I tested this base-case pattern with `n = 0`: **segmentation fault (exit code 139)**. Your `main` hard-codes 3, so you never hit it, but any user input of `0` or a negative number would. Use `n == 0` as the base case ("nothing to move"): it is simpler and safe, and `n <= 0` is safer still.
2. `numDisks = 3` is hard-coded; read it from the user.
3. The number of moves is `2ⁿ − 1`, so large `n` prints an enormous amount of output. Validate the input and report the move count.

**Problem:** Print the steps to move `n` disks from one rod to another using a third rod, following the rules (move one disk at a time; never place a larger disk on a smaller one).

**Concepts:** recursion with two calls on a smaller problem (R4), role-swapping parameters, exponential growth.

**How to think (trust the recursion)**
To move `n` disks from `from` to `to` using `via`:
1. Move the top `n − 1` disks from `from` to `via` (using `to` as the helper).
2. Move the biggest disk (disk `n`) from `from` to `to`. This is the only direct move.
3. Move the `n − 1` disks from `via` onto `to` (using `from` as the helper).

You never need to figure out *how* the `n − 1` disks move: the recursive call does it. Only the roles of the three rods change between calls.

**Solution**
```cpp
#include <iostream>
using namespace std;

// Prints the moves and returns how many there were.
unsigned long long hanoi(int n, char from, char to, char via) {
    if (n == 0) return 0;                                           // base case: nothing to move

    unsigned long long moves = hanoi(n - 1, from, via, to);         // 1. n-1 disks: from -> via
    cout << "Move disk " << n << " from " << from << " to " << to << '\n';   // 2. the largest disk
    moves++;
    moves += hanoi(n - 1, via, to, from);                           // 3. n-1 disks: via -> to
    return moves;
}

int main() {
    int n;
    cout << "Enter the number of disks (1 to 20): ";
    if (!(cin >> n) || n < 1 || n > 20) {
        cout << "Invalid input: enter a number from 1 to 20 (2^n - 1 moves are printed)\n";
        return 1;
    }

    unsigned long long moves = hanoi(n, 'A', 'C', 'B');
    cout << "Total moves: " << moves << '\n';
    return 0;
}
```

**Dry run (`n = 3`, rods A → C via B):**

```
hanoi(3, A, C, B)
├─ hanoi(2, A, B, C)               move 2 disks A -> B
│  ├─ hanoi(1, A, C, B)            Move disk 1 from A to C
│  │                               Move disk 2 from A to B
│  └─ hanoi(1, C, B, A)            Move disk 1 from C to B
│                                  Move disk 3 from A to C      <- the largest disk
└─ hanoi(2, B, C, A)               move 2 disks B -> C
   ├─ hanoi(1, B, A, C)            Move disk 1 from B to A
   │                               Move disk 2 from B to C
   └─ hanoi(1, A, C, B)            Move disk 1 from A to C
```

Output: `1 A→C`, `2 A→B`, `1 C→B`, `3 A→C`, `1 B→A`, `2 B→C`, `1 A→C` (**7 moves**).

**Moves needed: `T(n) = 2·T(n−1) + 1`, with `T(0) = 0`, which solves to `2ⁿ − 1`.**

| Disks | Moves |
|---|---|
| 1 | 1 |
| 2 | 3 |
| 3 | 7 |
| 4 | 15 |
| 10 | 1,023 |
| 20 | 1,048,575 |
| 64 | 18,446,744,073,709,551,615 (at one move per second, about 585 billion years) |

**Why it is the minimum:** the largest disk must move at least once, and while it moves all `n − 1` smaller disks have to sit on the third rod. So you need `T(n−1)` moves before it, one for it, and `T(n−1)` after: `T(n) ≥ 2T(n−1) + 1`.

**Complexity:** O(2ⁿ) time, O(n) stack space (the depth is `n`, and rods are only labels).

**Pitfalls:** mixing up the order of `from`, `to` and `via` in the two recursive calls (swap the roles carefully: step 1 uses `(from, via, to)`, step 3 uses `(via, to, from)`); a base case that does not cover `n = 0` or negative values; printing for large `n`.

**Follow-ups**
- *Iterative solution?* For odd `n` the smallest disk cycles A→C→B, for even `n` A→B→C; between those moves make the only legal move that does not involve the smallest disk.
- *How would you verify the answer?* Simulate three stacks and assert that every move is legal.
- *Four rods (Frame–Stewart)?* Fewer moves, but the optimal solution is harder.

---

---

# PART 0 (continued) — SEARCHING AND SORTING CONCEPTS (read once)

## B1. Binary search

Binary search finds a value in a **sorted** array by repeatedly discarding half of the remaining range: O(log n) instead of O(n). One million elements need at most 20 comparisons.

**Invariant (say it out loud):** *if the target is in the array, its index is inside `[low, high]`.* Each step compares with `arr[mid]` and keeps only the half that can still contain the target. When the range is empty (`low > high`), the target is absent.

Bugs to avoid:

| Bug | Why it happens | Prevention |
|---|---|---|
| Overflow in `(low + high) / 2` | the sum exceeds `INT_MAX` for huge arrays | `mid = low + (high - low) / 2` |
| Infinite loop | `low = mid` or `high = mid` with a closed range `[low, high]` | use `mid + 1` / `mid - 1` (closed range) or a half-open range `[low, high)` with `high = mid` |
| `size_t` underflow | `high = mid - 1` when `mid == 0` and `high` is unsigned | use `int`, or a half-open range |
| Wrong answers | the array is not sorted | state and check the precondition |
| Duplicates | any matching index may be returned | search again on the left side for the *first* occurrence |

## B2. Sorting vocabulary

- **Comparison sort:** decides order only by comparing elements. No comparison sort can beat **O(n log n)** in the worst case.
- **In place:** uses O(1) (or O(log n)) extra memory.
- **Stable:** elements that compare equal keep their original relative order. It matters when you sort records by one field and want an earlier ordering by another field to survive (for example, sort by name, then stable-sort by age).
- **Adaptive:** gets faster when the input is already (nearly) sorted.

## B3. The five sorts at a glance

| Sort | Best | Average | Worst | Extra space | Stable | Notes |
|---|---|---|---|---|---|---|
| Bubble | O(n) with early exit, else O(n²) | O(n²) | O(n²) | O(1) | yes | easy; almost never used in practice |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | **no** | exactly n(n−1)/2 comparisons; at most n−1 swaps |
| Insertion | **O(n)** | O(n²) | O(n²) | O(1) | yes | excellent for small or nearly sorted data |
| Merge | O(n log n) | O(n log n) | O(n log n) | **O(n)** | yes | predictable; used for linked lists and stable sorting |
| Quick | O(n log n) | O(n log n) | **O(n²)** | O(log n) stack | no | fastest in practice; worst case depends on the pivot |

`std::sort` is an *introsort* (quicksort + heapsort fallback + insertion sort for small ranges): O(n log n) worst case, not stable. `std::stable_sort` is merge-based and stable.

## B4. Divide-and-conquer recurrences

| Algorithm | Recurrence | Result |
|---|---|---|
| Merge sort | `T(n) = 2T(n/2) + O(n)` | O(n log n): `log₂ n` levels, O(n) merging work on each level |
| Quicksort, balanced split | `T(n) = 2T(n/2) + O(n)` | O(n log n) |
| Quicksort, worst split | `T(n) = T(n−1) + O(n)` | O(n²) |
| Binary search | `T(n) = T(n/2) + O(1)` | O(log n) |

---

# MODULE 6 — SEARCHING AND SORTING

---

## Q38. Binary Search Iteratively

**Review of your solution:** ✅ Correct and clean. The closed range `[low, high]`, `mid = low + (high - low) / 2`, and the updates `low = mid + 1` / `high = mid - 1` (both always shrink the range, so the loop must end) are exactly right. I verified: first element, last element, a middle element, absent values below / between / above the data, an empty vector, a single element, and duplicates. Small improvements:

1. `int high = arr.size() - 1;` converts a `size_t` to `int` implicitly. It works (even for an empty vector, where it gives `-1`), but write `static_cast<int>(arr.size()) - 1`.
2. The array and the target are hard-coded, and the precondition (**sorted ascending**) is not checked.
3. With **duplicates** it returns *some* matching index (for `{1,2,2,2,3}` and target `2` it returns index 2). The "first occurrence" version is a common follow-up.

**Problem:** Find a target in a sorted array using binary search (iteratively).

**Concepts:** B1, loop invariant, O(log n).

**How to think:** Keep a range `[low, high]` that must contain the target if it exists. Look at the middle element. If it is the target, done. If it is smaller than the target, everything at or left of it is too small: `low = mid + 1`. If larger, `high = mid - 1`. Stop when the range is empty.

**Solution**
```cpp
#include <iostream>
#include <vector>
using namespace std;

// Returns the index of a match, or -1. Precondition: arr is sorted in ascending order.
int binarySearch(const vector<int> &arr, int target) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;      // search the closed range [low, high]
    while (low <= high) {
        int mid = low + (high - low) / 2;             // never overflows
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;         // the target can only be in the right half
        else                   high = mid - 1;        // ... or in the left half
    }
    return -1;                                        // the range became empty: not present
}

// Bonus: index of the FIRST occurrence (useful with duplicates), or -1.
int firstOccurrence(const vector<int> &arr, int target) {
    int low = 0, high = static_cast<int>(arr.size()) - 1, answer = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            answer = mid;                             // remember it, then look further left
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return answer;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }

    vector<int> arr(n);
    cout << "Enter " << n << " integers in ascending order: ";
    for (int &x : arr) {
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
    }
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            cout << "The array must be sorted in ascending order\n";
            return 1;
        }
    }

    int target;
    cout << "Enter the target: ";
    if (!(cin >> target)) {
        cout << "Invalid input\n";
        return 1;
    }

    int index = binarySearch(arr, target);
    if (index == -1) {
        cout << "Not found\n";
    } else {
        cout << "Found at index " << index << '\n';
        cout << "First occurrence: index " << firstOccurrence(arr, target) << '\n';
    }
    return 0;
}
```

**Dry run (target `12` in `{1,3,4,5,6,7,8,12,45,66,87,99,123}`):**

| iteration | low | high | mid | arr[mid] | decision |
|---|---|---|---|---|---|
| 1 | 0 | 12 | 6 | 8 | `8 < 12` → `low = 7` |
| 2 | 7 | 12 | 9 | 66 | `66 > 12` → `high = 8` |
| 3 | 7 | 8 | 7 | 12 | **found, index 7** |

| Input | Output |
|---|---|
| your array, target `12` | `Found at index 7` |
| your array, target `1` / `123` | index `0` / `12` |
| your array, target `100` (absent) | `Not found` |
| `{1,2,2,2,3}`, target `2` | found at index 2; first occurrence: index **1** |
| empty array, `{7}` with target `7` | `Not found` / index `0` |
| unsorted input | `The array must be sorted in ascending order` |

**Complexity:** O(log n) time, O(1) space. Searching 1,000,000 elements takes at most 20 iterations.

**Pitfalls:** `(low + high) / 2` overflow; `low <= high` replaced by `low < high` (misses the one-element range); `high = mid` in a closed range (infinite loop); running it on unsorted data (no error, wrong answer).

**Follow-ups**
- *Recursive version?* Q36. The recursive call is a tail call, so the loop version is the same algorithm using O(1) space.
- *Last occurrence, insertion point, count of a value?* Variations of `firstOccurrence`; the standard library has `lower_bound`, `upper_bound` and `binary_search` (`<algorithm>`).
- *Search on the answer?* The same halving works on any monotonic condition (square root, minimum capacity, ...).

---

## Q39. Bubble Sort

**Review of your solution:** ✅ Correct: I tested sorted, reversed, random, duplicate-containing and empty input. The inner bound `arrSize - i - 1` (the last `i` elements are already in place) is the right optimization, and the strict `>` comparison makes the sort **stable**. One missing piece:

1. **No early exit.** Even on an already-sorted array your version does every pass: **28 comparisons for 8 elements, whether the input is sorted, reversed or random**. Adding a `swapped` flag stops as soon as a full pass makes no swap, which makes the best case O(n) (7 comparisons for a sorted array of 8).
2. The array is hard-coded.

**Problem:** Sort an array in ascending order using bubble sort.

**Concepts:** adjacent swaps, invariant "after pass `i`, the `i` largest elements are in their final place", early termination, stability.

**How to think:** Walk through the array comparing neighbours; swap any pair that is out of order. After the first pass the largest element has "bubbled" to the end; after the second pass the second largest is in place, and so on. If a whole pass makes **no swap**, the array is sorted and you can stop.

**Solution**
```cpp
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// Returns the number of comparisons made.
long long bubbleSort(vector<int> &arr) {
    long long comparisons = 0;
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;                      // did this pass change anything?
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {             // strict >: equal elements never swap (stable)
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;                       // already sorted: stop early
    }
    return comparisons;
}

void printArray(const char *label, const vector<int> &a) {
    cout << label;
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }
    vector<int> arr(n);
    cout << "Enter " << n << " integers: ";
    for (int &x : arr) {
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
    }

    printArray("Original: ", arr);
    long long comparisons = bubbleSort(arr);
    printArray("Sorted:   ", arr);
    cout << "Comparisons: " << comparisons << '\n';
    return 0;
}
```

**Dry run (`{5, 1, 4, 2}`):**

| pass | array during the pass | result |
|---|---|---|
| 1 | `5 1 4 2` → `1 5 4 2` → `1 4 5 2` → `1 4 2 5` | 5 is in place |
| 2 | `1 4 2 5` → `1 4 2 5` → `1 2 4 5` | 4 is in place |
| 3 | `1 2 4 5`: no swaps → **stop** | sorted |

| Input (n = 8) | Comparisons, no early exit | With the `swapped` flag |
|---|---|---|
| sorted `1 2 3 4 5 6 7 8` | 28 | **7** |
| reversed `8 7 … 1` | 28 | 28 |
| `23 42 24 63 334 53 0 43` | 28 | 28 (the `0` needs 7 passes to travel to the front) |
| `3 1 2 3 1 2` (duplicates) | | 14 |
| empty / one element | 0 | 0 |

**Complexity:** best O(n) (sorted, with the flag), average and worst O(n²) time; O(1) space; **stable**, in place.

**Pitfalls:** running the inner loop to `n - 1` every time (wasted comparisons and an out-of-bounds read of `arr[j + 1]` if you also forget `- 1`); using `>=` (swaps equal elements: loses stability and does extra work).

**Follow-ups**
- *Why do small elements move so slowly?* An element can only move **one position left per pass** (the "turtle" problem); large elements move to the end in one pass ("rabbits"). Cocktail shaker sort alternates directions to fix this.
- *Why is it rarely used?* O(n²) with many swaps; insertion sort does less work on the same inputs.
- *How many swaps does bubble sort perform?* Exactly the number of **inversions** (pairs out of order) in the input.

---

## Q40. Selection Sort

**Review of your solution:** ✅ Correct (verified on your array and edge cases). The structure is textbook: find the minimum of the unsorted part, swap it to the front. Notes:

1. When `minIndex == i` you still swap the element with itself: harmless, but skipping it is cleaner.
2. Be ready to state its properties, because they are the interview question: **it always does n(n−1)/2 comparisons** (it cannot exit early), it does **at most n−1 swaps** (the fewest of the simple sorts), and it is **not stable**.
3. Hard-coded data; no final newline.

**Problem:** Sort an array using selection sort.

**Concepts:** invariant "`arr[0..i-1]` already holds the `i` smallest elements, in order", minimum search, stability.

**How to think:** Pass `i` selects the smallest element of the remaining part `arr[i..n-1]` and swaps it into position `i`. After `n − 1` passes the array is sorted (the last element is automatically the largest).

**Solution**
```cpp
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// Generic selection sort; `less(x, y)` says whether x must come before y. Returns the number of swaps.
template <typename T, typename Less>
int selectionSort(vector<T> &a, Less less) {
    int swaps = 0;
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;                              // find the smallest element of a[i..n-1]
        for (int j = i + 1; j < n; j++)
            if (less(a[j], a[minIndex]))
                minIndex = j;
        if (minIndex != i) {                           // at most one swap per pass
            swap(a[i], a[minIndex]);
            swaps++;
        }
    }
    return swaps;
}

struct Item {
    int key;
    char tag;
};

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }
    vector<int> arr(n);
    cout << "Enter " << n << " integers: ";
    for (int &x : arr) {
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
    }

    int swaps = selectionSort(arr, [](int x, int y) { return x < y; });
    cout << "Sorted:";
    for (int x : arr) cout << ' ' << x;
    cout << "\nSwaps: " << swaps << '\n';

    // Selection sort is NOT stable: equal keys can change their relative order.
    vector<Item> items = {{2, 'a'}, {2, 'b'}, {1, 'c'}};
    selectionSort(items, [](const Item &x, const Item &y) { return x.key < y.key; });
    cout << "Stability demo, input (2,a) (2,b) (1,c) ->";
    for (const Item &it : items) cout << " (" << it.key << ',' << it.tag << ')';
    cout << "   <- (2,a) and (2,b) swapped order\n";
    return 0;
}
```

**Dry run (`{29, 10, 14, 37, 13}`):**

| pass | minimum found | array after the swap |
|---|---|---|
| 1 | 10 (index 1) | `10 29 14 37 13` |
| 2 | 13 (index 4) | `10 13 14 37 29` |
| 3 | 14 (index 2, already there) | `10 13 14 37 29` |
| 4 | 29 (index 4) | `10 13 14 29 37` |

**Why it is not stable:** in `(2,a) (2,b) (1,c)` the first pass swaps `(1,c)` with `(2,a)`, producing `(1,c) (2,b) (2,a)`: the two equal keys are now in the opposite order (shown by the program).

| Input | Output |
|---|---|
| `62 13 65 0 34 76 2 6 98 9` | `0 2 6 9 13 34 62 65 76 98`, 8 swaps |
| empty | empty, 0 swaps |

**Complexity:** O(n²) comparisons in **every** case; O(n) swaps at most; O(1) space; in place; not stable.

**Pitfalls:** searching for the minimum from `0` instead of `i`; looping `i` up to `n` (a harmless extra pass); assuming it is stable.

**Follow-ups**
- *When is selection sort a good choice?* When writes are expensive (flash memory), because it does the minimum number of swaps.
- *Make it stable?* Shift elements instead of swapping (insert the minimum at position `i`), at the cost of more moves.
- *Heap sort?* Selection sort where "find the minimum" is done by a heap: O(n log n).

---

## Q41. Insertion Sort

**Review of your solution:** 🐞 The sort itself is correct and **stable** (`arr[j] > key` shifts only strictly larger elements): the invariant "the prefix `arr[0..i-1]` is sorted" is maintained, the shifting loop is right, and `j >= 0` is checked **before** `arr[j]`. But **the question asks to test it on sorted, reversed and randomly ordered input**, and your `main` tests only one (random) array. Completing every requirement is part of the answer. The program below tests all three and counts the work, which also shows *why* the best case is O(n) and the worst case O(n²).

**Problem:** Implement insertion sort and test it on sorted, reversed and random input.

**Concepts:** growing a sorted prefix, shifting, adaptive behaviour, stability.

**How to think:** Take the next element (`key`) and slide it left into the already-sorted prefix: shift every larger element one place right, then drop `key` into the gap. It works like sorting playing cards in your hand.

**Solution**
```cpp
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct Stats {
    long long comparisons = 0;
    long long shifts = 0;
};

Stats insertionSort(vector<int> &arr) {
    Stats st;
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; i++) {
        int key = arr[i];                          // the element to insert into arr[0..i-1]
        int j = i - 1;
        while (j >= 0) {
            st.comparisons++;
            if (arr[j] <= key) break;              // found its place (<= keeps equal elements stable)
            arr[j + 1] = arr[j];                   // shift the bigger element right
            st.shifts++;
            j--;
        }
        arr[j + 1] = key;
    }
    return st;
}

void printArray(const char *label, const vector<int> &a) {
    cout << label;
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    mt19937 gen(2024);                             // fixed seed: the same "random" data every run

    // 1. Small inputs: see the actual arrays.
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> reversed = {8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> randomSmall = {23, 42, 24, 63, 334, 53, 0, 43};
    for (auto *v : {&sorted, &reversed, &randomSmall}) {
        printArray("before: ", *v);
        insertionSort(*v);
        printArray("after:  ", *v);
    }

    // 2. Larger inputs: count the work.
    const int N = 1000;
    vector<int> s(N), r(N), rnd(N);
    for (int i = 0; i < N; i++) {
        s[i] = i;
        r[i] = N - i;
        rnd[i] = static_cast<int>(gen() % 100000);
    }
    cout << "\nn = " << N << '\n';
    for (auto &entry : {make_pair("sorted  ", &s), make_pair("reversed", &r), make_pair("random  ", &rnd)}) {
        Stats st = insertionSort(*entry.second);
        cout << entry.first << "  comparisons = " << st.comparisons << ", shifts = " << st.shifts
             << ", sorted correctly: " << (is_sorted(entry.second->begin(), entry.second->end()) ? "yes" : "NO") << '\n';
    }
    return 0;
}
```

**Dry run (`{4, 3, 1}`):**

| i | key | shifting | array |
|---|---|---|---|
| 1 | 3 | `4 > 3`: shift 4 | `3 4 1` |
| 2 | 1 | `4 > 1`, `3 > 1`: shift both | `1 3 4` |

**Measured work for n = 1000** (seeded data, so the numbers repeat):

| Input | Comparisons | Shifts | Why |
|---|---|---|---|
| sorted | **999** | **0** | each key is compared once and stays: O(n) |
| reversed | **499,500** | **499,500** | every key moves all the way to the front: n(n−1)/2 |
| random | 252,163 | 251,167 | about n²/4 on average |

The number of shifts equals the number of **inversions** (pairs in the wrong order) in the input.

**Complexity:** best O(n), average and worst O(n²) time; O(1) space; **stable**, in place, **adaptive**, and an **online** algorithm (can sort items as they arrive).

**Pitfalls:** testing `arr[j] > key` before `j >= 0` (reads `arr[-1]`); writing `arr[j] = key` instead of `arr[j + 1] = key` after the loop; using `>=` (loses stability).

**Follow-ups**
- *Why do real libraries use it?* For small ranges (about 16 elements) and nearly sorted data it beats the O(n log n) sorts because of its low overhead; introsort and Timsort finish with insertion sort.
- *Faster search for the insertion point?* Binary insertion sort reduces comparisons to O(n log n), but the shifting is still O(n²).
- *Sorting a linked list?* Insertion needs no shifting there (only pointer changes).

---

## Q42. Merge Two Sorted Arrays

**Review of your solution:** ✅ The merge logic is correct and stable: two indices walk the two inputs, the smaller front element is taken (`<=` takes from the first array on ties), and the two leftover loops copy the remaining tail. Improvements:

1. 🐞 **The function prints instead of returning** the merged array, so it cannot be reused (this is the same design lesson as Q19: *compute in functions, print in `main`*). Return a `vector<int>`.
2. The parameters are non-const references (`std::vector<int> &`) although the function only reads them: use `const std::vector<int> &`.
3. Hard-coded data; sizes stored in `int`.

**Problem:** Merge two sorted arrays into one sorted array.

**Concepts:** the two-pointer merge (the core of merge sort, Q43), O(n + m), stability.

**How to think:** Both inputs are sorted, so the smallest unused element is always at the front of one of them. Compare the two front elements, take the smaller, advance that pointer. When one array runs out, append the rest of the other one unchanged.

**Solution**
```cpp
#include <iostream>
#include <vector>
using namespace std;

// Merges two ascending vectors into a new ascending vector. O(n + m) time.
vector<int> mergeSorted(const vector<int> &a, const vector<int> &b) {
    vector<int> result;
    result.reserve(a.size() + b.size());              // avoid re-allocations

    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) result.push_back(a[i++]);   // <= : on ties take from `a` first (stable)
        else              result.push_back(b[j++]);
    }
    while (i < a.size()) result.push_back(a[i++]);    // one of these two loops does nothing
    while (j < b.size()) result.push_back(b[j++]);
    return result;
}

bool readSortedArray(const char *name, vector<int> &out) {
    int n;
    cout << "Enter the size of " << name << ": ";
    if (!(cin >> n) || n < 0) return false;
    out.assign(n, 0);
    cout << "Enter " << n << " integers in ascending order: ";
    for (int &x : out)
        if (!(cin >> x)) return false;
    for (int i = 1; i < n; i++)
        if (out[i - 1] > out[i]) {
            cout << name << " is not sorted\n";
            return false;
        }
    return true;
}

int main() {
    vector<int> a, b;
    if (!readSortedArray("the first array", a) || !readSortedArray("the second array", b)) {
        cout << "Invalid input\n";
        return 1;
    }

    vector<int> merged = mergeSorted(a, b);
    cout << "Merged:";
    for (int x : merged) cout << ' ' << x;
    cout << '\n';
    return 0;
}
```

**Dry run (`{1, 3, 5}` and `{2, 4}`):**

| i | j | compare | taken | result |
|---|---|---|---|---|
| 0 | 0 | 1 vs 2 | 1 | `1` |
| 1 | 0 | 3 vs 2 | 2 | `1 2` |
| 1 | 1 | 3 vs 4 | 3 | `1 2 3` |
| 2 | 1 | 5 vs 4 | 4 | `1 2 3 4` |
| 2 | 2 | second array exhausted: copy the rest | 5 | `1 2 3 4 5` |

| Input | Merged |
|---|---|
| `0 2 4 6 7 9` and `1 3 5 8 10 11` | `0 1 2 3 4 5 6 7 8 9 10 11` |
| `{}` and `1 2 3` | `1 2 3` |
| `1 1 2` and `1 2 2` | `1 1 1 2 2 2` |
| an unsorted input | `... is not sorted` and `Invalid input` |

**Complexity:** O(n + m) time, O(n + m) space for the result.

**Pitfalls:** forgetting the leftover loops (the tail of the longer array is lost); `<` instead of `<=` (still sorted, but no longer stable); calling `result[k++] = ...` without sizing the result first.

**Follow-ups**
- *Standard library?* `merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result))` or `inplace_merge`.
- *Merge into the first array in place* (when it has enough spare room at the end, a classic interview problem)? Fill from the **back**, comparing the largest elements, so nothing unread is overwritten.
- *Merge k sorted arrays?* A min-heap of the k front elements: O(N log k).

---

## Q43. Merge Sort

**Review of your solution:** ✅ Correct, clean top-down merge sort: the base case `left >= right`, `mid = left + (right - left) / 2`, recursion on both halves, then merge, and `<=` in the merge, which makes it **stable**. I verified it against `std::sort` on 2,000 random arrays (0 to 40 elements, with duplicates and negatives): no mismatch. Improvements:

1. **Two new vectors are allocated in every `merge` call** (`leftArr`, `rightArr`): that is O(n) separate allocations over the whole sort. Use **one** auxiliary buffer allocated once.
2. **Name clash risk:** your function is called `merge`, like `std::merge`. It compiles because yours takes 4 arguments, but `std::vector` is a `std` type, so argument-dependent lookup also considers `std::merge`. A different name (`mergeHalves`) avoids any surprise.
3. `mergeSort(arr, 0, arr.size() - 1)` on an **empty** vector computes `size_t(0) - 1` (a huge number) and converts it to `int`. It happens to give `-1` and work, but a wrapper with an explicit check is safer.

**Problem:** Implement merge sort using divide and conquer.

**Concepts:** divide, conquer, combine; the merge from Q42; recurrence `T(n) = 2T(n/2) + O(n)`.

**How to think:** A one-element (or empty) range is already sorted. Otherwise split in the middle, sort each half recursively (trust it), and merge the two sorted halves (Q42). The real work happens in the merge, on the way back up.

**Solution**
```cpp
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

// Merges the sorted halves a[left..mid] and a[mid+1..right] using the shared buffer.
void mergeHalves(vector<int> &a, vector<int> &buffer, int left, int mid, int right) {
    copy(a.begin() + left, a.begin() + right + 1, buffer.begin() + left);

    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (buffer[i] <= buffer[j]) a[k++] = buffer[i++];   // <= keeps the sort stable
        else                        a[k++] = buffer[j++];
    }
    while (i <= mid) a[k++] = buffer[i++];
    // Any remaining right-half elements are already in their final place.
}

void mergeSortRange(vector<int> &a, vector<int> &buffer, int left, int right) {
    if (left >= right) return;                      // base case: 0 or 1 element is sorted
    int mid = left + (right - left) / 2;
    mergeSortRange(a, buffer, left, mid);           // divide ...
    mergeSortRange(a, buffer, mid + 1, right);
    mergeHalves(a, buffer, left, mid, right);       // ... and conquer (combine)
}

void mergeSort(vector<int> &a) {
    if (a.size() < 2) return;
    vector<int> buffer(a.size());                   // ONE auxiliary array for the whole sort
    mergeSortRange(a, buffer, 0, static_cast<int>(a.size()) - 1);
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    cout << "Original:";
    for (int x : arr) cout << ' ' << x;
    mergeSort(arr);
    cout << "\nSorted:  ";
    for (int x : arr) cout << ' ' << x;
    cout << '\n';

    mt19937 gen(5);
    int failures = 0;
    for (int t = 0; t < 2000; t++) {
        vector<int> v(gen() % 80);
        for (int &x : v) x = static_cast<int>(gen() % 41) - 20;
        vector<int> expected = v;
        sort(expected.begin(), expected.end());
        mergeSort(v);
        if (v != expected) failures++;
    }
    cout << "Self-test against std::sort (2000 random arrays): " << (failures == 0 ? "passed" : "FAILED") << '\n';

    vector<int> big(1000000);
    for (int &x : big) x = static_cast<int>(gen());
    mergeSort(big);
    cout << "1,000,000 random integers sorted: " << (is_sorted(big.begin(), big.end()) ? "ok" : "NO") << '\n';
    return 0;
}
```

**Recursion on `{38, 27, 43, 3, 9, 82, 10}`:**
```
[38 27 43 3 9 82 10]
├── [38 27 43 3]
│   ├── [38 27]  → [38] [27]  → merge → [27 38]
│   └── [43 3]   → [43] [3]   → merge → [3 43]
│   merge → [3 27 38 43]
└── [9 82 10]
    ├── [9 82]   → [9] [82]   → merge → [9 82]
    └── [10]
    merge → [9 10 82]
merge → [3 9 10 27 38 43 82]
```

**Complexity:** `log₂ n` levels, each doing O(n) merging work: **O(n log n) in the best, average and worst case.** O(n) extra space for the buffer plus O(log n) recursion depth. **Stable.**

| Property | Merge sort |
|---|---|
| time (all cases) | O(n log n) |
| extra space | O(n) |
| stable | yes |
| in place | no |
| adaptive | no (always does the full work) |

**Pitfalls:** an off-by-one in `mid` (`mid + 1` vs `mid`) that makes the recursion not shrink (infinite loop); forgetting the leftover loops in the merge; allocating inside the merge (slow).

**Follow-ups**
- *Why is merge sort preferred for linked lists and for stable sorting?* Merging needs no random access, and equal elements keep their order.
- *Bottom-up version?* Merge runs of size 1, 2, 4, ... in a loop: no recursion.
- *Count inversions?* Count, while merging, how many left-half elements are bigger than a right-half element: O(n log n).
- *External sorting (data bigger than memory)?* Merge sorted chunks from disk.

---

## Q44. Quick Sort

**Review of your solution:** ✅ This is a strong answer, and the written explanation of how pivot selection affects performance is clear and correct (balanced vs lopsided splits, the sorted-array trap, first/last vs random vs median-of-three). The implementation has two excellent details:

- a **random pivot**, which defeats the "already sorted input" trap, and
- **recursing into the smaller partition and looping on the larger one**, which keeps the stack depth at O(log n) *always* (I measured a maximum depth of 9 for 20,000 elements, even for sorted input).

I verified it against `std::sort` on 2,000 random arrays. One real weakness, found by testing:

1. 🐞 **Many equal elements make it O(n²).** Your partition sends every element `<= pivot` to the left. If all elements are equal, *every* element goes left, the split is `n − 1 : 0`, and a random pivot cannot help because all choices are identical. For **20,000 equal elements it performed 199,990,000 comparisons (449 ms)**, versus about 340,000 for sorted, reversed or random data of the same size. The fix is a **three-way partition** (`< pivot`, `== pivot`, `> pivot`): elements equal to the pivot are grouped in the middle and never touched again.
2. The explanation promises behaviour for sorted/reversed inputs, but the program never demonstrates it. The experiment below does.

**Problem:** Implement quicksort and explain how pivot selection affects performance.

**Concepts:** partitioning, recursion on subranges, worst-case analysis, randomization, stack depth.

**How to think**
1. Pick a **pivot**. Rearrange the range so smaller elements are on its left and larger ones on its right. The pivot is then in its final position.
2. Recursively sort the left and right parts.
3. *Performance depends on how balanced the split is.* Even splits give `T(n) = 2T(n/2) + O(n) = O(n log n)`; the worst split gives `T(n) = T(n−1) + O(n) = O(n²)`.

**Solution (production version: random pivot, three-way partition, smaller-side recursion)**
```cpp
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

mt19937 rng(random_device{}());

// Random pivot + three-way partition. After partitioning:
//   a[low .. lt-1] < pivot,   a[lt .. gt] == pivot,   a[gt+1 .. high] > pivot
// Elements equal to the pivot are never touched again, so many duplicates are cheap.
void quickSort(vector<int> &a, int low, int high) {
    while (low < high) {
        int pivot = a[uniform_int_distribution<int>(low, high)(rng)];
        int lt = low, i = low, gt = high;
        while (i <= gt) {
            if (a[i] < pivot)      swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else                   i++;
        }
        // Recurse into the SMALLER side, loop on the larger one: stack depth stays O(log n).
        if (lt - low < high - gt) {
            quickSort(a, low, lt - 1);
            low = gt + 1;
        } else {
            quickSort(a, gt + 1, high);
            high = lt - 1;
        }
    }
}

void quickSort(vector<int> &a) {
    if (!a.empty()) quickSort(a, 0, static_cast<int>(a.size()) - 1);
}

void printArray(const char *label, const vector<int> &a) {
    cout << label;
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5, 7, 10, 1};
    printArray("Original: ", arr);
    quickSort(arr);
    printArray("Sorted:   ", arr);

    // Self-test against std::sort on random arrays full of duplicates and negatives.
    mt19937 gen(99);
    int failures = 0;
    for (int t = 0; t < 2000; t++) {
        vector<int> v(gen() % 60);
        for (int &x : v) x = static_cast<int>(gen() % 15) - 7;
        vector<int> expected = v;
        sort(expected.begin(), expected.end());
        quickSort(v);
        if (v != expected) failures++;
    }
    cout << "Self-test against std::sort (2000 random arrays): " << (failures == 0 ? "passed" : "FAILED") << '\n';

    vector<int> allEqual(200000, 5);                  // the input that breaks the classic Lomuto version
    quickSort(allEqual);
    cout << "200000 equal elements sorted in one linear pass: " << (is_sorted(allEqual.begin(), allEqual.end()) ? "ok" : "NO") << '\n';
    return 0;
}
```

**Experiment: how the pivot strategy and the partition scheme change the work** (n = 5000, the same seeded data for every column; the numbers are elements compared against the pivot):

```cpp
// Experiment: how the pivot strategy and the partition scheme change the amount of work.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

enum class Pivot { First, Random, MedianOfThree };
long long work = 0;                                // elements compared with the pivot
mt19937 rng(12345);                                // fixed seed: reproducible numbers

int choosePivot(const vector<int> &a, int low, int high, Pivot p) {
    if (p == Pivot::First) return low;
    if (p == Pivot::Random) return uniform_int_distribution<int>(low, high)(rng);
    int mid = low + (high - low) / 2;              // median of a[low], a[mid], a[high]
    int x = a[low], y = a[mid], z = a[high];
    if ((x <= y && y <= z) || (z <= y && y <= x)) return mid;
    if ((y <= x && x <= z) || (z <= x && x <= y)) return low;
    return high;
}

// Classic Lomuto partition (the one in most textbooks): "<= pivot" goes left.
void quickLomuto(vector<int> &a, int low, int high, Pivot p) {
    while (low < high) {
        swap(a[choosePivot(a, low, high, p)], a[high]);
        int pivot = a[high], i = low - 1;
        for (int j = low; j < high; j++) {
            work++;
            if (a[j] <= pivot) swap(a[++i], a[j]);
        }
        swap(a[i + 1], a[high]);
        int pi = i + 1;
        if (pi - low < high - pi) { quickLomuto(a, low, pi - 1, p); low = pi + 1; }
        else                      { quickLomuto(a, pi + 1, high, p); high = pi - 1; }
    }
}

// Three-way partition: elements equal to the pivot are grouped in the middle and skipped.
void quick3Way(vector<int> &a, int low, int high, Pivot p) {
    while (low < high) {
        int pivot = a[choosePivot(a, low, high, p)];
        int lt = low, i = low, gt = high;
        while (i <= gt) {
            work++;
            if (a[i] < pivot)      swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else                   i++;
        }
        if (lt - low < high - gt) { quick3Way(a, low, lt - 1, p); low = gt + 1; }
        else                      { quick3Way(a, gt + 1, high, p); high = lt - 1; }
    }
}

int main() {
    const int N = 5000;
    mt19937 gen(1);
    vector<int> randomData(N), sorted(N), reversed(N), allEqual(N, 7), fewDistinct(N);
    for (int i = 0; i < N; i++) {
        randomData[i] = static_cast<int>(gen() % 1000000);
        sorted[i] = i;
        reversed[i] = N - i;
        fewDistinct[i] = static_cast<int>(gen() % 5);
    }
    struct Case { const char *name; vector<int> *data; };
    Case cases[] = {{"random", &randomData}, {"sorted", &sorted}, {"reversed", &reversed},
                    {"all equal", &allEqual}, {"5 distinct values", &fewDistinct}};

    cout << "n = " << N << "   (n^2 / 2 = " << static_cast<long long>(N) * N / 2 << ",  n * log2(n) = "
         << static_cast<long long>(N * 12.3) << ")\n\n";
    cout << left << setw(20) << "input" << right << setw(14) << "Lomuto/first" << setw(15) << "Lomuto/random"
         << setw(16) << "Lomuto/median3" << setw(16) << "3-way/random" << '\n';

    for (auto &c : cases) {
        cout << left << setw(20) << c.name << right;
        for (int mode = 0; mode < 4; mode++) {
            vector<int> v = *c.data;
            work = 0;
            if (mode == 0)      quickLomuto(v, 0, N - 1, Pivot::First);
            else if (mode == 1) quickLomuto(v, 0, N - 1, Pivot::Random);
            else if (mode == 2) quickLomuto(v, 0, N - 1, Pivot::MedianOfThree);
            else                quick3Way(v, 0, N - 1, Pivot::Random);
            if (!is_sorted(v.begin(), v.end())) cout << " NOT SORTED";
            cout << setw(mode == 0 ? 14 : mode == 1 ? 15 : 16) << work;
        }
        cout << '\n';
    }
    return 0;
}
```

**Measured results:**

```
n = 5000   (n^2 / 2 = 12500000,  n * log2(n) = 61500)

input                 Lomuto/first  Lomuto/random  Lomuto/median3    3-way/random
random                       71050          73354           64460           71838
sorted                    12497500          69119           51822           74474
reversed                  12497500          67705          100346           73590
all equal                 12497500       12497500        12497500            5000
5 distinct values          2512213        2508206         2506276           11973
```

**What the table teaches**
- **First-element pivot on sorted or reversed data: 12,497,500 comparisons** (exactly n(n−1)/2). That is the "sorted array trap".
- **A random pivot** (or **median-of-three**) turns those inputs into ordinary O(n log n) work (about 52,000 to 100,000 comparisons).
- **Duplicates are a separate problem.** With the classic partition, *every* pivot strategy needs 12.5 million comparisons on all-equal data, and about 2.5 million on only five distinct values. A **three-way partition** needs just 5,000 and about 12,000, respectively.
- Median-of-three is deterministic and cheap, but an adversary can still build a bad input for it; a random pivot has no bad input, only unlucky coin flips (probability negligible).

| Pivot strategy | Bad input | Typical use |
|---|---|---|
| first / last element | sorted, reversed | teaching examples only |
| random element | none in practice (expected O(n log n)) | general purpose |
| median of three (first, middle, last) | specially crafted inputs | library implementations |
| true median (median of medians) | none (guaranteed O(n log n)) | theoretical; large constant factor |

**Complexity:** expected O(n log n); worst O(n²), made astronomically unlikely by the random pivot; O(log n) stack space thanks to recursing on the smaller side. **Not stable**, in place.

| Input | Result |
|---|---|
| `10 7 8 9 1 5 7 10 1` | `1 1 5 7 7 8 9 10 10` |
| 2,000 random arrays with duplicates | identical to `std::sort` |
| 200,000 equal elements | sorted in one linear pass |

**Pitfalls:** recursing on both partitions without the smaller-side trick (stack overflow on bad splits); a partition that does not make progress (infinite recursion); assuming a random pivot fixes duplicates; using quicksort when stability is required.

**Follow-ups**
- *Why is quicksort usually faster than merge sort in practice?* It works in place with good cache behaviour and a small constant factor, even though merge sort has the better worst case.
- *What does `std::sort` do?* Introsort: quicksort that switches to heapsort when the recursion gets too deep (guaranteeing O(n log n)) and to insertion sort for small ranges.
- *Find the k-th smallest element in O(n) average time?* **Quickselect**: partition, then recurse into only one side.
- *Hoare vs Lomuto partition?* Hoare's scheme does fewer swaps and handles duplicates better; Lomuto is simpler to write.

---

# PART 0 (continued) — MATRICES AND STL CONCEPTS (read once)

## M1. Two-dimensional data

```cpp
vector<vector<long long>> m(rows, vector<long long>(cols, 0));   // rows x cols, all zeros
m[i][j];                // row i, column j   (0-based)
m.size();               // number of rows
m[0].size();            // number of columns (if the matrix is not empty!)
```

- **Rectangular check:** every row must have the same length. A "ragged" `vector<vector<T>>` is legal C++ but breaks matrix algorithms (out-of-bounds reads, see Q46).
- **Memory layout:** each row is its own array, but walking **row by row** (`i` outer, `j` inner) is cache-friendly; column-by-column is not.
- **Operations and cost** (for `r × c` matrices):

| Operation | Rule | Time |
|---|---|---|
| addition | same dimensions; `sum[i][j] = a[i][j] + b[i][j]` | O(r·c) |
| transpose | `r × c` becomes `c × r`; `t[j][i] = m[i][j]` | O(r·c) |
| multiplication | `(r1 × c1)(c1 × c2) = (r1 × c2)`; **columns of A must equal rows of B** | O(r1·c1·c2), O(n³) for square |

- **Overflow:** a product entry is a *sum of products*; accumulate in `long long`.

## M2. Choosing an STL container

| Container | Order | Lookup / insert (average) | Typical use |
|---|---|---|---|
| `vector` | insertion order, contiguous | index O(1), push_back O(1) amortized | default sequence |
| `unordered_map` / `unordered_set` | **none (unspecified)** | O(1) average, O(n) worst | counting, "have I seen this?", complement lookup |
| `map` / `set` | **sorted by key** | O(log n) | sorted output, range queries, unique sorted values |
| `stack` | LIFO (`push`, `pop`, `top`, `empty`) | O(1) | matching brackets, undo, DFS |
| `queue` | FIFO | O(1) | BFS, scheduling |

Rules of thumb: need **order**? → `map`/`set`. Need **speed** and don't care about order? → `unordered_*`. Calling `top()` or `pop()` on an empty stack is undefined behavior: check `empty()` first.

## M3. The hash-map patterns

1. **Frequency counting:** `freq[x]++` (a missing key is created with value 0). Q47.
2. **"Seen before?":** keep a set of what you have processed. Q48.
3. **Complement lookup:** to find a pair that sums to `T`, look up `T − x` among the elements already seen. Q50.

Hash maps trade **O(n) extra memory** for turning an O(n²) double loop into an O(n) single pass.

## M4. Exceptions in one minute

```cpp
try {
    risky();                              // may `throw invalid_argument("message")`
} catch (const invalid_argument &e) {
    cout << e.what() << '\n';             // handled: the program continues
}
```

An exception that nobody catches calls `std::terminate`, and the program **aborts** (exit code 134 on Linux). Use exceptions for exceptional failures (bad dimensions); for *expected* "not found" outcomes prefer `bool`, `optional` or an empty result.

---

# MODULE 7 — MATRICES, STL, AND PROBLEM-SOLVING

---

## Q45. Matrix Addition and Transposition

**Review of your solution:** ✅ Well engineered: validated dimensions, an `isRectangular` check, `size_t` indexing, `long long` sums so `int` addition cannot overflow, and exceptions for incompatible shapes. I verified the 3×3 example, the transpose of a **non-square** 2×3 matrix (correctly 3×2), an empty matrix, and both mismatch cases (3×2 vs 2×3, and equal row counts with different columns). Two findings:

1. 🐞 **The exceptions are never caught.** `addMatrix` throws `invalid_argument`, but `main` has no `try/catch`, so a mismatch ends the program with `terminate called after throwing an instance of 'std::invalid_argument'` and **exit code 134** (I forced it). Catch it in `main` and print a friendly message.
2. The demo uses only 3×3 matrices generated by `createMatrix`. The interesting cases are **non-square** matrices (transposing changes the shape) and **mismatched** shapes. Read the matrices from the user so you can test both.

(Mixing `Matrix` of `int` for the inputs and `long long` for the sum works, but a single element type is simpler to read. The solution below uses `long long` throughout.)

**Problem:** Add two compatible matrices and compute the transpose of a matrix.

**Concepts:** 2D vectors (M1), dimension rules, exceptions (M4).

**How to think**
- **Addition:** defined only for matrices with the **same** number of rows and columns; add element by element.
- **Transpose:** an `r × c` matrix becomes `c × r`; the element at row `i`, column `j` moves to row `j`, column `i`.

**Solution**
```cpp
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

using Matrix = vector<vector<long long>>;           // long long: sums cannot overflow int

bool readMatrix(const char *name, Matrix &m) {
    int rows, cols;
    cout << "Enter the number of rows and columns of " << name << ": ";
    if (!(cin >> rows >> cols) || rows < 1 || cols < 1) return false;
    m.assign(rows, vector<long long>(cols));
    cout << "Enter " << rows << " x " << cols << " values, row by row: ";
    for (auto &row : m)
        for (long long &x : row)
            if (!(cin >> x)) return false;
    return true;
}

void printMatrix(const Matrix &m) {
    for (const auto &row : m) {
        for (size_t j = 0; j < row.size(); j++) {
            if (j > 0) cout << ' ';
            cout << row[j];
        }
        cout << '\n';
    }
}

// Element-wise sum. Throws if the shapes differ.
Matrix addMatrices(const Matrix &a, const Matrix &b) {
    if (a.size() != b.size() || a[0].size() != b[0].size())
        throw invalid_argument("matrices must have the same dimensions");
    Matrix sum(a.size(), vector<long long>(a[0].size()));
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a[0].size(); j++)
            sum[i][j] = a[i][j] + b[i][j];
    return sum;
}

// An r x c matrix becomes c x r, with transposed[j][i] = m[i][j].
Matrix transpose(const Matrix &m) {
    Matrix t(m[0].size(), vector<long long>(m.size()));
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m[0].size(); j++)
            t[j][i] = m[i][j];
    return t;
}

int main() {
    Matrix a, b;
    if (!readMatrix("matrix A", a) || !readMatrix("matrix B", b)) {
        cout << "Invalid input\n";
        return 1;
    }

    cout << "\nTranspose of A:\n";
    printMatrix(transpose(a));
    cout << "Transpose of B:\n";
    printMatrix(transpose(b));

    try {
        cout << "\nA + B:\n";
        printMatrix(addMatrices(a, b));
    } catch (const invalid_argument &e) {
        cout << "Cannot add: " << e.what() << '\n';          // handled: no crash
    }
    return 0;
}
```

| Input | Output |
|---|---|
| A = `1 2 3 / 4 5 6`, B = `7 8 9 / 10 11 12` | `Aᵀ` = `1 4 / 2 5 / 3 6`; `Bᵀ` = `7 10 / 8 11 / 9 12`; `A + B` = `8 10 12 / 14 16 18` |
| A is 2×3, B is 3×2 | transposes printed, then `Cannot add: matrices must have the same dimensions` (no crash) |

**Dry run (transpose of `1 2 3 / 4 5 6`):** `t[0][0] = m[0][0] = 1`, `t[1][0] = m[0][1] = 2`, `t[2][0] = m[0][2] = 3`, `t[0][1] = m[1][0] = 4`, ... giving the 3×2 matrix `1 4 / 2 5 / 3 6`.

**Complexity:** O(r·c) time for each operation, O(r·c) space for the result.

**Pitfalls:** allocating the transpose as `r × c` instead of `c × r` (wrong for non-square matrices); transposing "in place" a non-square matrix (impossible in a simple loop); assuming `m[0]` exists for an empty matrix.

**Follow-ups**
- *In-place transpose of a square matrix?* Swap `m[i][j]` with `m[j][i]` for `j > i`.
- *Rotate a matrix by 90°?* Transpose, then reverse each row.
- *Why is the sum `long long`?* Two `int` entries near 2·10⁹ overflow `int`.

---

## Q46. Matrix Multiplication

**Review of your solution:** ✅ The mathematics is correct and the performance choice is good. The loop order **i–k–j** reads both matrices row by row (cache-friendly), and the `long long` accumulator avoids overflow. Verified: the 3×3 example and a **non-square** product `(2×3) × (3×2) = 2×2` (`22 28 / 49 64`), and an incompatible pair throws correctly. Findings:

1. 🐞 **Ragged input causes an out-of-bounds read.** The function takes the dimensions from `matrixA[0]` and `matrixB[0]` only. For a non-rectangular matrix such as `{{1,2,3},{4,5}}`, `matrixA[1][2]` reads past the end of the row. AddressSanitizer reported **heap-buffer-overflow** when I tried it. Q45 had an `isRectangular` check; Q46 needs the same.
2. The exception for incompatible dimensions is not caught in `main` (same as Q45): the program aborts.
3. An empty matrix silently returns an empty result, even when the other matrix is not empty. Decide on one rule (an error is clearer).
4. Only the 3×3 case is demonstrated; test non-square and incompatible shapes.

**Problem:** Multiply two matrices when their dimensions are compatible.

**Concepts:** triple loop, dimension compatibility rule, accumulation, O(n³).

**How to think:** `C = A × B` is defined when the **number of columns of A equals the number of rows of B**. If `A` is `r1 × c1` and `B` is `c1 × c2`, then `C` is `r1 × c2` and `C[i][j] = Σₖ A[i][k] × B[k][j]`: the dot product of row `i` of A and column `j` of B.

**Solution**
```cpp
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

using Matrix = vector<vector<long long>>;

bool readMatrix(const char *name, Matrix &m) {
    int rows, cols;
    cout << "Enter the number of rows and columns of " << name << ": ";
    if (!(cin >> rows >> cols) || rows < 1 || cols < 1) return false;
    m.assign(rows, vector<long long>(cols));
    cout << "Enter " << rows << " x " << cols << " values, row by row: ";
    for (auto &row : m)
        for (long long &x : row)
            if (!(cin >> x)) return false;
    return true;
}

void printMatrix(const Matrix &m) {
    for (const auto &row : m) {
        for (size_t j = 0; j < row.size(); j++) {
            if (j > 0) cout << ' ';
            cout << row[j];
        }
        cout << '\n';
    }
}

// (r1 x c1) times (r2 x c2) is defined only when c1 == r2; the result is r1 x c2.
Matrix multiply(const Matrix &a, const Matrix &b) {
    size_t r1 = a.size(), c1 = a[0].size(), r2 = b.size(), c2 = b[0].size();
    if (c1 != r2)
        throw invalid_argument("columns of A (" + to_string(c1) + ") must equal rows of B (" + to_string(r2) + ")");

    Matrix product(r1, vector<long long>(c2, 0));
    for (size_t i = 0; i < r1; i++)
        for (size_t k = 0; k < c1; k++)                 // i-k-j order walks both matrices row by row
            for (size_t j = 0; j < c2; j++)
                product[i][j] += a[i][k] * b[k][j];
    return product;
}

int main() {
    Matrix a, b;
    if (!readMatrix("matrix A", a) || !readMatrix("matrix B", b)) {
        cout << "Invalid input\n";
        return 1;
    }

    try {
        cout << "\nA x B:\n";
        printMatrix(multiply(a, b));
    } catch (const invalid_argument &e) {
        cout << "Cannot multiply: " << e.what() << '\n';
    }
    return 0;
}
```

**Dry run (`C[0][0]` for A = `1 2 3 / 4 5 6`, B = `1 2 / 3 4 / 5 6`):** `1·1 + 2·3 + 3·5 = 22`. The other entries: `C[0][1] = 1·2 + 2·4 + 3·6 = 28`, `C[1][0] = 4·1 + 5·3 + 6·5 = 49`, `C[1][1] = 4·2 + 5·4 + 6·6 = 64`.

| Input | Output |
|---|---|
| A is 2×3 `1 2 3 / 4 5 6`, B is 3×2 `1 2 / 3 4 / 5 6` | `22 28 / 49 64` |
| A = `1 2 3 / 4 5 6 / 7 8 9`, B = `-5 -4 -3 / -2 -1 0 / 1 2 3` | `-6 0 6 / -24 -9 6 / -42 -18 6` |
| A is 2×3, B is 2×3 | `Cannot multiply: columns of A (3) must equal rows of B (2)` |
| A = `1 2 / 3 4`, B = identity | `1 2 / 3 4` (multiplying by the identity changes nothing) |

**Complexity:** O(r1 · c1 · c2) time, which is O(n³) for square matrices; O(r1 · c2) space for the result.

**Pitfalls:** swapping the compatibility rule (it is columns of **A** against rows of **B**); allocating the result as `r1 × c1`; forgetting that matrix multiplication is **not commutative** (`A × B ≠ B × A` in general); starting the accumulator uninitialized.

**Follow-ups**
- *Faster than O(n³)?* Strassen's algorithm is about O(n^2.81); practical code uses blocking and libraries (BLAS).
- *Matrix power (for example Fibonacci via `[[1,1],[1,0]]ⁿ`)?* Use fast exponentiation (Q35) with matrix multiplication: O(log n) multiplications.
- *Why `i-k-j` rather than `i-j-k`?* The inner loop then walks `b[k][*]` and `product[i][*]` sequentially in memory.

---

## Q47. Frequency Counter Using std::unordered_map

**Review of your solution:** ✅ Correct: `freq[num]++` (a missing key is created with value 0 and then incremented) counts every element in O(n) average time, and the structured binding `const auto &[num, count]` is a nice C++17 touch. Findings:

1. **The output order is unspecified.** An `unordered_map` iterates in an order decided by its hash table. On my machine your program printed the keys as `3, 1, 2, 4`; another compiler or library version can print them differently. If the order matters (it does for tests and for users), copy the entries into a `vector` and sort, or use `std::map`.
2. The text says "1 times"; use a neutral format such as `value: count`.
3. Hard-coded data. Reading `n` values lets you test empty input and larger inputs.

**Problem:** Count how many times each integer occurs, using the standard library.

**Concepts:** hash map (M2, M3), `operator[]` semantics, deterministic output.

**How to think:** For each element increment `freq[x]`. The map stores one counter per distinct value, so the work is one hash lookup per element.

**Solution**
```cpp
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }

    unordered_map<int, int> freq;
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        int x;
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
        freq[x]++;                                    // missing key is created with 0, then incremented
    }

    // An unordered_map has NO defined iteration order, so copy to a vector and sort for stable output.
    vector<pair<int, int>> entries(freq.begin(), freq.end());
    sort(entries.begin(), entries.end());             // by value, then count

    cout << "Frequencies (sorted by value):\n";
    for (const auto &[value, count] : entries)
        cout << "  " << value << ": " << count << '\n';

    if (!entries.empty()) {
        auto best = entries.front();
        for (const auto &e : entries)
            if (e.second > best.second) best = e;     // first maximum wins ties (smallest value)
        cout << "Most frequent: " << best.first << " (" << best.second << " times)\n";
    }
    return 0;
}
```

**Dry run (`4 2 4 1 2 4 3`):** `freq`: `4 → 1 → 2 → 3`, `2 → 1 → 2`, `1 → 1`, `3 → 1`. Sorted by value: `1:1, 2:2, 3:1, 4:3`.

| Input | Output |
|---|---|
| `4 2 4 1 2 4 3` | `1: 1`, `2: 2`, `3: 1`, `4: 3`, `Most frequent: 4 (3 times)` |
| empty | only the heading |

**Complexity:** O(n) average (O(n²) worst case with adversarial hash collisions) time; O(k) space for k distinct values.

**`unordered_map` vs `map`:** `map` keeps the keys sorted and costs O(log n) per operation; `unordered_map` is faster on average but has no order.

**Pitfalls:** relying on iteration order; using `freq[x]` just to *check* membership (it **inserts** the key: use `find` or `count`); using `vector<int> counts(1000000)` when the values are unbounded or negative.

**Follow-ups**
- *Count characters or words?* The same code with `char` or `string` keys (Level 2, Q15).
- *Top-k frequent elements?* Sort the entries by count, or use a heap: O(n log k).
- *Why not an array of counters?* Only when the value range is small and known (for example letters).

---

## Q48. Remove Duplicates Using std::set

**Review of your solution:** ✅ Correct and idiomatic: constructing a `std::set<int>` from an iterator range removes duplicates and sorts in one step. It runs in O(n log n) time and uses O(n) extra memory. Notes:

1. A `set` allocates one node per element (poor cache behaviour); `sort` + `unique` on a vector is often faster for plain data. Know all three approaches (below).
2. The data is hard-coded; read it from the user to test the empty case.
3. The question says "unique values in sorted order": a `set` gives exactly that, which is why it is the intended tool. If the **original order** had to be preserved, you would need a "seen" set and a vector (see Level 2, Q17 for the string version).

**Problem:** Remove duplicate values from a collection and print the unique values in sorted order.

**Concepts:** `std::set` (ordered, unique keys, M2), `std::unique`, `unordered_set`.

**How to think:** A `set` rejects a value that is already present and keeps its elements sorted, so inserting everything leaves exactly the unique values in order.

**Solution**
```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

void printValues(const char *label, const vector<int> &v) {
    cout << label;
    for (int x : v) cout << ' ' << x;
    cout << '\n';
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }
    vector<int> numbers(n);
    cout << "Enter " << n << " integers: ";
    for (int &x : numbers) {
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
    }

    // 1. std::set: unique AND sorted automatically. O(n log n).
    set<int> unique(numbers.begin(), numbers.end());
    cout << "std::set:             ";
    for (int x : unique) cout << x << ' ';
    cout << '\n';

    // 2. sort + std::unique on a copy: same result, contiguous memory (usually faster). O(n log n).
    vector<int> sorted = numbers;
    sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
    printValues("sort + unique:        ", sorted);

    // 3. unordered_set to drop duplicates in O(n), then sort the survivors.
    unordered_set<int> seen(numbers.begin(), numbers.end());
    vector<int> viaHash(seen.begin(), seen.end());
    sort(viaHash.begin(), viaHash.end());
    printValues("unordered_set + sort: ", viaHash);

    cout << "Unique values: " << unique.size() << " of " << numbers.size() << '\n';
    return 0;
}
```

| Input | Output |
|---|---|
| `7 2 5 2 9 1 7 5 3` | `1 2 3 5 7 9` (all three methods), `Unique values: 6 of 9` |
| empty | empty lines, `Unique values: 0 of 0` |

| Method | Time | Extra space | Notes |
|---|---|---|---|
| `std::set` | O(n log n) | O(n) | simplest, sorted result |
| `sort` + `unique` + `erase` | O(n log n) | O(1) in place | contiguous memory, usually fastest |
| `unordered_set` + `sort` | O(n) + O(k log k) | O(n) | best when there are very few distinct values |

**Pitfalls:** forgetting `erase` after `std::unique` (it only moves the duplicates to the end and returns the new logical end; the container size does not change); calling `unique` on an unsorted vector (it removes only *adjacent* duplicates); expecting `unordered_set` to be sorted.

**Follow-ups**
- *`multiset`?* Like a set but keeps duplicates.
- *Descending order?* `set<int, greater<int>>`.
- *Count how many duplicates were removed?* `numbers.size() - unique.size()`.

---

## Q49. Balanced Parentheses

**Review of your solution:** ✅ Correct. The stack logic is exactly right: push every opening bracket; on a closing bracket, **check `empty()` first** (so `top()` is never called on an empty stack, which would be undefined behavior), compare with the matching opener, then pop; finally the string is balanced only if the stack is empty. I verified your six test strings plus nine more: `a(b[c]d)e` (other characters are ignored), `(((`, `)))`, `([{}])`, `{[(])}`, `(a`, a string with no brackets, `()[]{}`, `(]`. All correct. Suggestions:

1. State your assumption: characters other than brackets are **ignored** (so `"no brackets"` is balanced).
2. Reading the string from the user (instead of a fixed list) lets you test anything.
3. Interviewers often ask for **where** the first error is: the version below returns the index.

**Problem:** Determine whether the brackets `()`, `{}`, `[]` in a string are correctly balanced, using `std::stack`.

**Concepts:** stack (LIFO), matching, M2.

**How to think:** The most recently opened bracket must be the first one closed: that is exactly a stack. Scan left to right. An opening bracket is pushed. A closing bracket must match the bracket on top of the stack: otherwise the string is invalid. At the end, leftover opening brackets mean unclosed brackets.

**Solution**
```cpp
#include <iostream>
#include <stack>
#include <string>
#include <utility>
using namespace std;

bool isOpening(char c) { return c == '(' || c == '{' || c == '['; }
bool isClosing(char c) { return c == ')' || c == '}' || c == ']'; }
char matchingOpen(char close) { return close == ')' ? '(' : close == '}' ? '{' : '['; }

// Returns -1 if the brackets are balanced; otherwise the index where the problem is found:
// a closing bracket with no (or the wrong) partner, or the innermost unclosed opening bracket.
int findFirstError(const string &s) {
    stack<pair<char, int>> open;                       // (bracket, its index)
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        char c = s[i];
        if (isOpening(c)) {
            open.push({c, i});
        } else if (isClosing(c)) {
            if (open.empty() || open.top().first != matchingOpen(c))
                return i;                              // nothing to close, or closes the wrong kind
            open.pop();
        }                                              // every other character is ignored
    }
    return open.empty() ? -1 : open.top().second;
}

bool isBalanced(const string &s) { return findFirstError(s) == -1; }

int main() {
    cout << "Enter strings, one per line (Ctrl+D to stop):\n";
    string line;
    while (getline(cin, line)) {
        int err = findFirstError(line);
        cout << '"' << line << "\" -> ";
        if (err == -1) cout << "Balanced\n";
        else           cout << "Not balanced (problem at index " << err << ")\n";
    }
    return 0;
}
```

**Dry run (`{[(])}`):**

| char | action | stack (bottom → top) |
|---|---|---|
| `{` | push | `{` |
| `[` | push | `{ [` |
| `(` | push | `{ [ (` |
| `]` | top is `(`, not `[` | **mismatch → not balanced, index 3** |

| Input line | Output |
|---|---|
| `{[()]}` | Balanced |
| `([)]` | Not balanced (problem at index 2) |
| `((()))` | Balanced |
| `(()` | Not balanced (problem at index 0: the unclosed `(`) |
| `}{` | Not balanced (problem at index 0) |
| *(empty line)* | Balanced |
| `a(b[c]d)e` | Balanced |

**Complexity:** O(n) time; O(n) space in the worst case (a string of only opening brackets).

**Pitfalls:** calling `top()` or `pop()` on an empty stack; checking only that the **counts** of each bracket type match (`([)]` has equal counts but is invalid); forgetting the final `empty()` check (`(()`).

**Follow-ups**
- *Only one bracket type?* A single counter is enough (never negative, zero at the end), with O(1) space.
- *Minimum insertions or deletions to balance it?* Variations using a counter or stack.
- *Where else are stacks used?* Expression evaluation, undo/redo, function calls, depth-first search.

---

## Q50. Two Sum

**Review of your solution:** 🐞 The structure is exactly what the question asks for: a brute-force version first, then a one-pass `unordered_map` version that stores `{value, index}`, checks the complement **before** inserting the current element (which guarantees two *distinct* indices), and uses the C++17 `if` with an initializer. On your sample array both versions find the same three pairs. Findings:

1. 🐞 **The hash-map version misses pairs when the array contains duplicates**, so the two versions disagree. For `{3, 3, 3}` with target `6`, brute force finds **3 pairs** (indices (0,1), (0,2), (1,2)) but the hash version finds **2**, because `seen[arr[i]] = i` overwrites the earlier index of the value `3`. Keep a *list* of indices per value (the third function below), or, if only one answer is needed, return as soon as the first pair is found.
2. **Possible `int` overflow:** `arr[i] + arr[j]` and `target - arr[i]` overflow when the values are large (for example `INT_MAX + INT_MAX`). Compute in `long long`.
3. **No message when nothing is found:** with no pair, the program prints nothing, so the user cannot tell "no answer" from "forgot to print".
4. Classic Two Sum returns **one** pair (as indices); printing every pair is a different problem. The solution below does both.

**Problem:** Given an integer array and a target, find two distinct elements whose sum equals the target. Try brute force first, then improve with `std::unordered_map`.

**Concepts:** complement lookup (M3), time/space trade-off, duplicates, overflow.

**How to think**
1. **Brute force:** try every pair `(i, j)` with `i < j`: O(n²) time, O(1) space.
2. **Observation:** for each element `x` you only need to know whether `target − x` appeared **earlier**. A hash map answers that in O(1) on average.
3. **One pass:** for each element, look up its complement, **then** store the element. Storing after the check prevents using the same element twice.

**Solution**
```cpp
#include <iostream>
#include <optional>
#include <unordered_map>
#include <vector>
using namespace std;

struct IndexPair {
    size_t first, second;
};

// 1. Brute force: try every pair. O(n^2) time, O(1) space.
optional<IndexPair> twoSumBrute(const vector<int> &a, long long target) {
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++)
            if (static_cast<long long>(a[i]) + a[j] == target)   // long long: no int overflow
                return IndexPair{i, j};
    return nullopt;
}

// 2. One pass with a hash map: O(n) time, O(n) space.
optional<IndexPair> twoSumHash(const vector<int> &a, long long target) {
    unordered_map<long long, size_t> seen;                       // value -> index of an earlier element
    for (size_t i = 0; i < a.size(); i++) {
        long long complement = target - a[i];
        auto it = seen.find(complement);
        if (it != seen.end()) return IndexPair{it->second, i};   // partner was seen before i
        seen[a[i]] = i;                                          // store AFTER checking: distinct indices
    }
    return nullopt;
}

// 3. EVERY pair, duplicates handled correctly: keep all earlier indices of each value.
vector<IndexPair> allPairs(const vector<int> &a, long long target) {
    unordered_map<long long, vector<size_t>> seen;
    vector<IndexPair> pairs;
    for (size_t i = 0; i < a.size(); i++) {
        auto it = seen.find(target - a[i]);
        if (it != seen.end())
            for (size_t j : it->second) pairs.push_back({j, i});
        seen[a[i]].push_back(i);
    }
    return pairs;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n < 0) {
        cout << "Invalid size\n";
        return 1;
    }
    vector<int> a(n);
    cout << "Enter " << n << " integers: ";
    for (int &x : a) {
        if (!(cin >> x)) {
            cout << "Invalid input\n";
            return 1;
        }
    }
    long long target;
    cout << "Enter the target: ";
    if (!(cin >> target)) {
        cout << "Invalid input\n";
        return 1;
    }

    auto describe = [&](const char *label, optional<IndexPair> p) {
        cout << label;
        if (p) cout << a[p->first] << " + " << a[p->second] << " = " << target
                    << " (indices " << p->first << " and " << p->second << ")\n";
        else   cout << "no pair\n";
    };
    describe("Brute force, first pair: ", twoSumBrute(a, target));
    describe("Hash map, first pair:    ", twoSumHash(a, target));

    auto pairs = allPairs(a, target);
    cout << "All pairs: " << pairs.size() << '\n';
    for (const auto &p : pairs)
        cout << "  " << a[p.first] << " + " << a[p.second] << " (indices " << p.first << ", " << p.second << ")\n";
    return 0;
}
```

**Dry run (hash version, your array `{0, -90, 30, 4, 5, 25, -10, 45, -5, 10}`, target `35`):**

| i | value | complement | in map? | map after |
|---|---|---|---|---|
| 0 | 0 | 35 | no | `{0}` |
| 1 | -90 | 125 | no | `{0, -90}` |
| 2 | 30 | 5 | no | adds 30 |
| 3 | 4 | 31 | no | adds 4 |
| 4 | 5 | 30 | **yes (index 2)** → pair `30 + 5` | |

| Input | Output |
|---|---|
| your array, target `35` | first pair `30 + 5` (indices 2, 4); all pairs: `30 + 5`, `-10 + 45`, `25 + 10` (3 pairs) |
| `3 3 3`, target `6` | 3 pairs: (0,1), (0,2), (1,2) |
| `1 2 4`, target `100` | `no pair`, `All pairs: 0` |
| `2147483647 2147483647`, target `4294967294` | found (needs `long long`) |
| one element | `no pair` |

**Complexity**

| Approach | Time | Space |
|---|---|---|
| brute force | O(n²) | O(1) |
| hash map (first pair) | O(n) average | O(n) |
| all pairs | O(n + number of pairs) | O(n) |

**Pitfalls:** inserting the element **before** the lookup (an element pairs with itself: `target = 6`, `x = 3`); overwriting indices of duplicate values; `int` arithmetic on large values; assuming the answer is unique.

**Follow-ups**
- *Array is sorted?* Two pointers from both ends: O(n) time, O(1) space.
- *Three Sum?* Sort, then fix one element and run two pointers: O(n²).
- *Return values instead of indices?* Simpler: a `set` is enough.
- *Count the number of pairs?* Keep `count[value]` and add `count[target - x]` for each `x`.

---

# LEVEL 2 WRAP-UP

## Complexity of every problem

| Q | Time | Space | | Q | Time | Space |
|---|---|---|---|---|---|---|
| 1, 2, 3, 6 | O(n) | O(1) | | 28 | O(n) | O(1) |
| 4, 8, 10 | O(n) | O(1) | | 29 | O(n) | O(n) heap |
| 5 | O(n) | O(1) | | 31 | O(n) | O(n) stack |
| 7 | O(n) | O(1) | | 32 | O(2ⁿ) plain, O(n) memo | O(n) |
| 9 | O(n) | O(1) | | 33 | O(log n) | O(log n) stack |
| 11, 12 | O(n) | O(1) | | 34 | O(n) | O(n) stack |
| 13, 14 | O(n) | O(1) | | 35 | O(log b) | O(log b) stack |
| 15, 16, 17, 18 | O(n) | O(1) (table of 256) | | 36 | O(log n) | O(log n) stack |
| 19, 22, 23, 24 | O(1) | O(1) | | 37 | O(2ⁿ) | O(n) stack |
| 20 | O(log min(a, b)) | O(1) | | 38 | O(log n) | O(1) |
| 21 | O(range · √N) | O(1) | | 39, 40, 41 | O(n²) (41 best O(n)) | O(1) |
| 25, 26, 27 | O(1) / O(n) | O(1) | | 42 | O(n + m) | O(n + m) |
| 43 | O(n log n) | O(n) | | 44 | O(n log n) expected | O(log n) |
| 45 | O(r·c) | O(r·c) | | 46 | O(r1·c1·c2) | O(r1·c2) |
| 47 | O(n) avg | O(k) | | 48 | O(n log n) | O(n) |
| 49 | O(n) | O(n) | | 50 | O(n²) → O(n) | O(1) → O(n) |

## The patterns behind all 50 problems

| Pattern | Problems |
|---|---|
| Running best (max, min, second max) | 1, 2, 5, 28 |
| Two pointers (ends or reader/writer) | 4, 8, 10, 11, 12, 34, 42 |
| Reverse / rotate by reversals | 4, 9, 11, 34 |
| Counting table or hash map | 15, 16, 17, 18, 47, 50 |
| State flag (`inWord`, `seen`, `swapped`) | 14, 17, 39 |
| Recursion: base case + smaller problem | 31–37, 43, 44 |
| Memoization | 32 |
| Divide and conquer | 35, 36, 43, 44 |
| Halving a search range | 36, 38 |
| Stack (LIFO) | 49, and the call stack behind 31–37 |
| Compute in functions, print in `main` | 19, 20, 21, 42 |
| Pointers: `&`, `*`, arithmetic, `new`/`delete` | 25–30 |
| Edge cases: empty, one element, extremes, duplicates | every problem |

## The recurring mistakes (found in your own submissions)

1. **Boundary inputs:** `0`, empty, `INT_MAX`, one past the limit (Q5, Q32, Q37, Q41).
2. **Incomplete requirements:** the question lists steps you skipped (Q25, Q30, Q41).
3. **Uncaught failure paths:** exceptions never caught, silent exits, no message for "not found" (Q29, Q45, Q50).
4. **Output that does not match** (formatting, order) (Q35, Q47).
5. **Quadratic hidden inside "fast" code:** duplicates in quicksort, `substr` in recursion (Q44).
6. **A fix that breaks an old case:** always re-run *all* previous tests (Q5).

## Final interview checklist

- [ ] Restate the problem and ask about sizes, negatives, duplicates, and empty input.
- [ ] Say the brute force and its complexity, then the improvement and why it is correct.
- [ ] Name the invariant or the base case aloud.
- [ ] Write small functions that **return** results; print in `main`.
- [ ] Use safe types (`long long`, `size_t` care) and check overflow before it happens.
- [ ] Dry-run one normal case and two edge cases before declaring victory.
- [ ] State time **and** space complexity, and whether a sort is stable or in place.
- [ ] Compile with `-Wall -Wextra -Wpedantic` and (when you have it) `-fsanitize=address,undefined`.

## What to do next

1. **Re-implement from memory** the ones that took you longest: Q5 (second largest), Q32 (memoized Fibonacci), Q37 (Hanoi), Q44 (quicksort), Q50 (Two Sum).
2. **Explain each aloud** in 60 seconds: idea, complexity, one edge case.
3. **Time yourself:** 20 minutes per problem, no notes.
4. Move to **Level 3**: linked lists, stacks and queues from scratch, trees, hashing, graphs (BFS/DFS), and dynamic programming. The recursion and hash-map habits from this level are exactly what those topics build on.

---

## Module status

| Module | Done | Remaining |
|---|---|---|
| 1 — Arrays | Q1–Q10 ✅ | none |
| 2 — Strings | Q11–Q18 ✅ | none |
| 3 — Functions | Q19–Q24 ✅ | none |
| 4 — Pointers and memory | Q25–Q30 ✅ | none |
| 5 — Recursion | Q31–Q37 ✅ | none |
| 6 — Searching and sorting | Q38–Q44 ✅ | none |
| 7 — Matrices, STL, problem solving | Q45–Q50 ✅ | none |

**All 50 questions of Level 2 are reviewed.**
