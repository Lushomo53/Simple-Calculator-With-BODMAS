
---

# Simple Calculator

A **C++ command-line calculator** capable of evaluating arithmetic expressions with support for addition, subtraction, multiplication, division, parentheses, and factorial operations.

This project was developed using **CLion** and demonstrates basic tokenization, parsing, and recursive descent evaluation of mathematical expressions.

---

## Features

* Supports **basic arithmetic operations**: `+`, `-`, `*`, `/`
* Supports **parentheses** for expression grouping: `( … )`
* Supports **factorial** operator: `!` (e.g., `5! = 120`)
* Handles **decimal numbers** (floating-point arithmetic)
* Detects **division by zero** and invalid syntax
* Interactive command-line interface

---

## Installation / Setup

1. **Clone the repository**:

   ```bash
   git clone <repository-url>
   ```
2. **Open in CLion**:

   * Open CLion → File → Open → Select project folder
3. **Build the project**:

   * Use `Build` → `Build Project` in CLion
4. **Run the executable**:

   * Use `Run` → `Run 'main'` or the green play button in CLion

---

## Usage

1. Launch the program. You will see:

   ```
   ***Simple Calculator***
   Enter expression(enter 'e' to exit):
   ```
2. Enter any valid arithmetic expression:

   ```text
   2 + 3 * (4 - 1)
   5!
   3.5 + 2.1
   ```
3. To exit the calculator, enter:

   ```
   e
   ```

---

## How It Works

1. **Tokenization (`tokenise`)**:
   Converts a string expression into a vector of tokens (numbers, operators, parentheses, factorials).

2. **Parsing and Evaluation**:

   * Uses **recursive descent parsing** with the following grammar:

     * `expression = term { (+ | -) term }`
     * `term = primary { (* | /) primary }`
     * `primary = number [!]| '(' expression ')'`
   * `number()` handles numerical values and advances the token stream.
   * Factorials are calculated for non-negative integers only.

3. **Error Handling**:

   * Division by zero
   * Unexpected characters
   * Missing parentheses
   * Invalid factorial input

---

## Example Session

```text
***Simple Calculator***
Enter expression(enter 'e' to exit):
2 + 3 * 4
Result: 14
Enter expression(enter 'e' to exit):
5!
Result: 120
Enter expression(enter 'e' to exit):
(2 + 3) * 4
Result: 20
Enter expression(enter 'e' to exit):
e
```

---

## Dependencies

* **C++17 or higher** (for `std::stod` and modern C++ features)
* **CLion IDE** (optional, but project is configured for CLion)

---

## Notes

* Factorials only work for **non-negative integers**.
* Spaces in expressions are ignored.
* Floating-point numbers are supported, e.g., `3.14 + 2.71`.

---

## Author

**Lushomo Lungo** – Created as a learning project in C++ using CLion.

