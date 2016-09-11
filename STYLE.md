ModbusMaster Style Guide
========================

The following references provide sound guidance for writing C/C++ code for the Arduino platform.

- [Arduino API Style Guide (AASG)](http://www.arduino.cc/en/Reference/APIStyleGuide)
- [Bjarne Stroustrup's C++ Style Guide](http://www.stroustrup.com/bs_faq2.html)
- [JSF Air Vehicle C++ Coding Standards (JSFAV)](http://www.stroustrup.com/JSF-AV-rules.pdf)

Opinions about style and generally accepted usage patterns may vary widely. I've carefully chosen a few key items to emphasize and enforce for this library in order to promote readability, usability, and safe coding practices. **Pull requests will follow these guidelines in order to be considered**.


General \[AASG\]
-------

Use the established Arduino core libraries and styles.

- Use `read()` to read inputs, and `write()` to write to outputs, e.g. `digitalRead()`, `analogWrite()`, etc.
- Use the `Stream.h` and `Print.h` libraries when dealing with byte streams. If it’s not appropriate, at least try to use its API as a model. For more on this, see below.
- For network applications, use the Client and Server libraries as the basis.
- Use `begin()` to initialize a library instance, usually with some settings. Use `end()` to stop it.
- Use camelCase function names, not underscore. For example, `analogRead`, not `analog_read`. Or `myNewFunction`, not `my_new_function`. We've adopted this from Processing.org for readability's sake. Refer to AV Rule 45 and AV Rule 51.
- When using serial communication, allow the user to specify any `Stream` object, rather than hard-coding `Serial`. This will make the library compatible with all serial ports on Mega and the Due, and can also use alternate interfaces like `SoftwareSerial`. The `Stream` object can be passed to the library's constructor or to a `begin()` function (as a reference, not a pointer). See Firmata 2.3 or XBee 0.4 for examples of each approach.


Rules \[JSFAV 4.2\]
-----

#### Should, Will, and Shall Rules

There are three types of rules: **should**, **will**, and **shall** rules. Each rule contains either a **"should"**, **"will"** or a **"shall"** in bold letters indicating its type.

- **Should** rules are advisory rules. They strongly suggest the recommended way of doing things.
- **Will** rules are intended to be mandatory requirements. It is expected that they will be followed, but they do not require verification. They are limited to non-safety-critical requirements that cannot be easily verified (e.g., naming conventions).
- **Shall** rules are mandatory requirements. They must be followed and they require verification (either automatic or manual).


Pre-Processing Directives  \[JSFAV 4.6\]
-------------------------
Since the pre-processor knows nothing about C++, it should not be used to do what can otherwise be done in C++.

- AV Rule 26

  Only the following pre-processor directives shall be used:

  1. `#ifndef`
  1. `#define`
  1. `#endif`
  1. `#include`

  **Rationale**: Limit the use of the pre-processor to those cases where it is necessary.

#### \#ifndef and \#endif Pre-Processing Directives

- AV Rule 27

  `#ifndef`, `#define` and `#endif` **will** be used to prevent multiple inclusions of the same header file. Other techniques to prevent the multiple inclusions of header files **will not** be used.

  **Rationale**: Eliminate multiple inclusions of the same header file in a standard way.

- AV Rule 28

  The `#ifndef` and `#endif` pre-processor directives **will** only be used as defined in AV Rule 27 to prevent multiple inclusions of the same header file.

  **Rationale**: Conditional code compilation should be kept to a minimum as it can significantly obscure testing and maintenance efforts.

#### \#define Pre-Processing Directive

- AV Rule 29

  The `#define` pre-processor directive **shall not** be used to create inline macros. Inline functions **shall** be used instead.

  **Rationale**: Inline functions do not require text substitutions and behave well when called with arguments (e.g. type checking is performed).

- AV Rule 30

  The `#define` pre-processor directive **shall not** be used to define constant values. Instead, the `const` qualifier shall be applied to variable declarations to specify constant values.

  **Rationale**: `const` variables follow scope rules, are subject to type checking and do not require text substitutions (which can be confusing or misleading).

- AV Rule 31

  The `#define` pre-processor directive **will** only be used as part of the technique to prevent multiple inclusions of the same header file.

  **Rationale**: `#define` can be used to specify conditional compilation (AV Rule 27 and AV Rule 28), inline macros (AV Rule 29) and constants (AV Rule 30). This rule specifies that the only allowable use of `#define` is to prevent multiple includes of the same header file (AV Rule 27).

#### \#include Pre-Processing Directive

- AV Rule 32

  The `#include` pre-processor directive **will** only be used to include header (\*.h) files.

  **Rationale**: Clarity. The only files included in a .cpp file should be the relevant header (\*.h) files.


Header Files \[JSFAV 4.7\]
------------

- AV Rule 33

  The `#include` directive **shall** use the `<filename.h>` notation to include header files.

  **Rationale**: The include form `"filename.h"` is typically used to include local header files. However, due to the unfortunate divergence in vendor implementations, only the `<filename.h>` form will be used.

- AV Rule 35

  A header file **will** contain a mechanism that prevents multiple inclusions of itself.

  **Rationale**: Avoid accidental header file recursion. Note AV Rule 27 specifies the mechanism by which multiple inclusions are to be eliminated whereas this rule (AV Rule 35) specifies that each header file must use that mechanism.

- AV Rule 37

  Header (include) files **should** include only those header files that are required for them to successfully compile. Files that are only used by the associated .cpp file should be placed in the .cpp file—not the .h file.

  **Rationale**: The `#include` statements in a header file define the dependencies of the file. Fewer dependencies imply looser couplings and hence a smaller ripple-effect when the header file is required to change.


Style \[JSFAV 4.9\]
-----
Imposing constraints on the format of syntactic elements makes source code easier to read due to consistency in form and appearance.

- AV Rule 41 (modified)

  Source lines **will** be kept to a length of 78 characters or less.

  **Rationale**: Readability and style. Very long source lines can be difficult to read and understand.

- AV Rule 42

  Each expression-statement **will** be on a separate line.

  **Rationale**: Simplicity, readability, and style.

- AV Rule 43 (modified)

  Tabs **will** be avoided.

  **Rationale**: Tabs are interpreted differently across various editors and printers.

- AV Rule 44

  All indentations **will** be at least two spaces and be consistent within the same source file.

  **Rationale**: Readability and style.

#### Naming Identifiers

The choice of identifier names should:

- Suggest the usage of the identifier.
- Consist of a descriptive name that is short yet meaningful.
- Be long enough to avoid name conflicts, but not excessive in length.
- Include abbreviations that are generally accepted.

Note: In general, the above guidelines should be followed. However, conventional usage of simple identifiers (i, x, y, p, etc.) in small scopes can lead to cleaner code and will therefore be permitted.

Additionally, the term ‘word’ in the following naming convention rules may be used to refer to a word, an acronym, an abbreviation, or a number.

- AV Rule 45

  All words in an identifier **will** be separated by the '\_' character.

  **Exception**: Function names follow the camelCase convention according to the Arduino API Style Guide. Refer to AV Rule 51.

  **Rationale**: Readability and Style.

- AV Rule 47 (modified)

  Identifiers **should not** begin with the underscore character '\_'.

  **Exception**: Currently, private members of the `ModbusMaster` class begin with '\_'.

  **Rationale**: '\_' is often used as the first character in the name of library functions (e.g. `_main`, `_exit`, etc.) In order to avoid name collisions, identifiers should not begin with '\_'.

- AV Rule 49

  All acronyms in an identifier **will** be composed of uppercase letters.

  Note: An acronym will always be in uppercase, even if the acronym is located in a portion of an identifier that is specified to be lowercase by other rules.

  **Rationale**: Readability.

- AV Rule 50

  The first word of the name of a class, structure, namespace, enumeration, or type created with typedef **will** begin with an uppercase letter. All others letters will be lowercase.

  **Rationale**: Style.

  **Exception**: The first letter of a typedef name may be in lowercase in order to conform to a standard library interface or when used as a replacement for fundamental types.

- AV Rule 51 (modified)

  All letters contained in *function* names **will** be composed of a mix of lowercase and uppercase letters in camelCase format (e.g. first letter of first word is lowercase and first letter of each subsequent word is uppercase). This is to maintain consistency with the Arduion API Style Guide. Refer to AV Rule 45.

  All letters contained in *variable* names **will** be composed entirely of lowercase letters.

  **Rationale**: Style.

- AV Rule 52

  Identifiers for constant and enumerator values **shall** be lowercase.

  **Rationale**: Although it is an accepted convention to use uppercase letters for constants and enumerators, it is possible for third party libraries to replace constant/enumerator names as part of the macro substitution process (macros are also typically represented with uppercase letters).

#### Classes

- AV Rule 57

  The public, protected, and private sections of a class **will** be declared in that order (the public section is declared before the protected section which is declared before the private section).

  **Rationale**: By placing the public section first, everything that is of interest to a user is gathered in the beginning of the class definition. The protected section may be of interest to designers when considering inheriting from the class. The private section contains details that should be of the least general interest.

#### Functions

- AV Rule 58

  When declaring and defining functions with more than two parameters, the leading parenthesis and the first argument **will** be written on the same line as the function name. Each additional argument will be written on a separate line (with the closing parenthesis directly after the last argument).

  **Rationale**: Readability and style.

#### Blocks

- AV Rule 59

  The statements forming the body of an `if`, `else if`, `else`, `while`, `do...while` or `for` statement **shall** always be enclosed in braces, even if the braces form an empty block.

  **Rationale**: Readability. It can be difficult to see ';' when it appears by itself.

- AV Rule 60

  Braces ('{}') which enclose a block will be placed in the same column, on separate lines directly before and after the block.

  **Example**:
    ```
    if (var_name == true)
    {
    }
    else
    {
    }
    ```

- AV Rule 61

  Braces ('{}') which enclose a block **will** have nothing else on the line except comments (if necessary).

#### Pointers and References

- AV Rule 62

  The dereference operator '\*' and the address-of operator '&' **will** be directly connected with the type-specifier.

  **Rationale**: The `int32* p;` form emphasizes type over syntax while the `int32 *p;` form emphasizes syntax over type. Although both forms are equally valid C++, the heavy emphasis on types in C++ suggests that `int32* p;` is the preferable form.

  **Examples**:
    ```
    int32* p;     // correct
    int32 *p;     // incorrect
    int32* p, q;  // probable error
    ```

#### Miscellaneous

- AV Rule 63

  Spaces **will not** be used around '.' or '->', nor between unary operators and operands.

  **Rationale**: Readability and style.


Classes \[JSFAV 4.10\]
-------

#### const Member Functions

- AV Rule 69

  A member function that does not affect the state of an object (its instance variables) **will** be declared `const`.

  Member functions should be `const` by default. Only when there is a clear, explicit reason should the `const` modifier on member functions be omitted.

  **Rationale**: Declaring a member function `const` is a means of ensuring that objects will not be modified when they should not. Furthermore, C++ allows member functions to be overloaded on their `const`-ness.


Initialization \[JSFAV 4.16\]
--------------

- AV Rule 142

  All variables **shall** be initialized before use.

  **Rationale**: Prevent the use of variables before they have been properly initialized.

- AV Rule 143

  Variables **will not** be introduced until they can be initialized with meaningful values.

  **Rationale**: Prevent clients from accessing variables without meaningful values.


Constants \[JSFAV 4.18\]
---------

- AV Rule 149

  Octal constants (other than zero) **shall not** be used.

  **Rationale**: Any integer constant beginning with a zero ('0') is defined by the C++ standard to be an octal constant. Due to the confusion this causes, octal constants should be avoided.

  Note: Hexadecimal numbers and zero (which is also an octal constant) are allowed.

- AV Rule 150

  Hexadecimal constants **will** be represented using all uppercase letters.


Variables \[JSFAV 4.19\]
---------

- AV Rule 152

  Multiple variable declarations **shall not** be allowed on the same line.

  **Rationale**: Increases readability and prevents confusion (see also AV Rule 62).

  **Examples**:
    ```
    int32 p;                                // correct
    int32 q;                                // correct
    int32 p, q;                             // probable error
    int32 first_button_on_the_left_box, i;  // incorrect; easy to overlook i
    ```


Flow Control Structures \[JSFAV 4.24\]
-----------------------

- AV Rule 188

  Labels **will** not be used, except in switch statements.

  **Rationale**: Labels are typically either used in switch statements or are as the targets for goto statements. See exception given in AV Rule 189.

- AV Rule 189

  The `goto` statement **shall not** be used.

  **Rationale**: Frequent use of the `goto` statement tends to lead to code that is both difficult to read and maintain.

- AV Rule 190

  The `continue` statement **shall not** be used.

- AV Rule 191

  The `break` statement **shall not** be used (except to terminate the cases of a switch statement).

  **Exception**: The `break` statement may be used to "break" out of a single loop provided the alternative would obscure or otherwise significantly complicate the control logic.

- AV Rule 192

  All `if`, `else if` constructs **will** contain either a final `else` clause or a comment indicating why a final `else` clause is not necessary.

  **Rationale**: Provide a defensive strategy to ensure that all cases are handled by an `else if` series.

  Note: This rule only applies when an `if` statement is followed by one or more `else if`’s.

- AV Rule 193

  Every non-empty `case` clause in a `switch` statement **shall** be terminated with a `break` statement.

  **Rationale**: Eliminates potentially confusing behavior since execution will fall through to the code of the next `case` clause if a `break` statement does not terminate the previous `case` clause.
