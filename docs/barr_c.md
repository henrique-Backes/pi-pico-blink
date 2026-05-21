# Barr Group's Embedded C Coding Standard (2018)

## 1. General Rules

### 1.1 Which C?
**Rules:**
* **a.** All programs shall be written to comply with the C99 version of the ISO C Programming Language Standard.
* **b.** Whenever a C++ compiler is used, appropriate compiler options shall be set to restrict the language to the selected version of ISO C.
* **c.** The use of proprietary compiler language keyword extensions, `#pragma`, and inline assembly shall be kept to the minimum necessary and localized.
* **d.** Preprocessor directive `#define` shall not be used to alter or rename any keyword.

### 1.2 Line Widths
**Rules:**
* **a.** The width of all lines in a program shall be limited to a maximum of 80 characters.

### 1.3 Braces
**Rules:**
* **a.** Braces shall always surround the blocks of code following `if`, `else`, `switch`, `while`, `do`, and `for` statements.
* **b.** Each left brace (`{`) shall appear by itself on the line below the start of the block it opens. The corresponding right brace (`}`) shall appear by itself.

### 1.4 Parentheses
**Rules:**
* **a.** Do not rely on C's operator precedence rules. Use parentheses to ensure proper execution order.
* **b.** Unless it is a single identifier or constant, each operand of the logical AND (`&&`) and logical OR (`||`) operators shall be surrounded by parentheses.

### 1.6 Casts
**Rules:**
* **a.** Each cast shall feature an associated comment describing how the code ensures proper behavior.

### 1.8 Keywords to Frequent
**Rules:**
* **a.** The `static` keyword shall be used for all functions and variables that do not need to be visible outside their module.
* **b.** The `const` keyword shall be used whenever appropriate.
* **c.** The `volatile` keyword shall be used for variables accessible by ISRs, multiple threads, or memory-mapped registers.

## 2. Comment Rules

### 2.2 Locations and Content
**Rules:**
* **c.** **Avoid explaining the obvious.** Assume the reader knows C. Avoid unhelpful and redundant comments.
* **h.** Each module and function shall be commented in a manner suitable for automatic documentation generation (e.g., Doxygen).

## 3. White Space Rules

### 3.1 Spaces
**Rules:**
* **a.** Keywords like `if`, `while`, `for`, `switch` shall be followed by one space.
* **b/c.** Binary operators (`=`, `+`, `==`, etc.) shall be preceded and followed by one space.
* **d.** Unary operators (`!`, `++`, etc.) shall be written without a space on the operand side.
* **j.** Function calls: no space between name and `(`. Function declarations: one space between name and `(`.

### 3.4 Indentation
**Rules:**
* **a.** Each indentation level should be a multiple of 4 spaces.
* **b.** Within a `switch`, `case` labels shall be aligned; code blocks indented once.

### 3.5 Tabs
**Rules:**
* **a.** The tab character shall never appear within any source code file.

## 5. Data Type Rules

### 5.2 Fixed-Width Integers
**Rules:**
* **a.** Use fixed-width types from `stdint.h` (`int8_t`, `uint32_t`, etc.) instead of standard types when width matters.
* **b.** The keywords `short` and `long` shall not be used.

## 8. Statement Rules

### 8.4 Loops
**Rules:**
* **c.** Infinite loops shall be implemented via controlling expression `for (;;)`.

### 8.6 Equivalence Tests
**Rules:**
* **a.** When evaluating equality against a constant, the constant shall be placed to the left of the `==` operator (e.g., `if (NULL == p_obj)`).

## Appendix B: Header File Template
```c
/** @file module.h
*
* @brief A description of the module’s purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
*/
#ifndef MODULE_H
#define MODULE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int8_t max8(int8_t num1, int8_t num2);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_H */
/*** end of file ***/
```

## Appendix C: Source File Template
```c
/** @file module.c
*
* @brief A description of the module’s purpose.
*
* @par
* COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
*/
#include <stdint.h>
#include <stdbool.h>
#include "module.h"

/*!
* @brief Identify the larger of two 8-bit integers.
*
* @param[in] num1  The first number to be compared.
* @param[in] num2  The second number to be compared.
*
* @return The value of the larger number.
*/
int8_t
max8 (int8_t num1, int8_t num2)
{
    return ((num1 > num2) ? num1 : num2);
}
/*** end of file ***/
```
