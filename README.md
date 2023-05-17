# sCheme
<br>
A Scheme interpreter written in C that is planned to support the usage of pointers, classes and other C-like features (e.g. ++, += etc.). \
This is a project that does not contribute to anything in any way that I decided to make for no reason whatsoever. 

<br>

---

<br>

## Main ideas
- Pointers
- Usage of C-like inline operations: var++,  *var, var += x, ...
- Macro expansion
- Classes

<br>

---

<br>

## To do list

### Features to implement
- Apply
- Eval environment
- Eval environment (with copy function that copies it)
- Copy function for values (be careful which values to copy!)
- Stack trace for error info (return Error Value object with stack trace)

### Changes to add
- Put fraction sign to nominator, and make procedure that "balances" the sign to the nominator (to call before returning new value)
- Make better makefile
- #(x y z) = (vector x y z)
- When value is <#void>, nothing is printed

### Bugs to fix
- Tokentree init type is NONE while it has a token
- Memory leak (when not define!, it counts too many frees for values)
- "()" input gives segfault
    => parser: add "None" as token so that eval can give error (no proc application)
- "" input causes infinite loop
