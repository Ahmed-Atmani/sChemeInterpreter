# sCheme

<br>

sCheme is a Scheme interpreter written in C that is planned to support the usage of pointers, classes and other C-like features (e.g. ++, += etc.). \
This is a project that does not contribute to anything in any way that I decided to make for no reason whatsoever. 

<br>

---
<br>

## Main ideas
- Pointers
- Usage of C-like inline operations: var++,  *var, var += x, 'a' instead of #\a, ...
- Macro expansion
- Classes

<br>

---
<br>

## To do list

### Features to implement
- Eval should return a value and a new (modified) environment !!!!
- Eval environment (with copy function that copies it)
- Apply
- Copy function for values (be careful which values to copy!)
- Stack trace for error info (return Error Value object with stack trace)

### Changes to add
- Add IsNull to HasAtom, ...
- Put fraction sign to nominator, and make procedure that "balances" the sign to the nominator (to call before returning new value)
- Make better makefile
- #(x y z) = (vector x y z)
- When value is <#void>, nothing is printed
- Check parenthesis balance and empty input before parsing (or while parsing pass error to main to skip eval) 

### Bugs to fix
- "()" and "'()" input gives segfault when freeing inputTree
    => "()" has parse tree "( ( ) )"
    => "'()" has parse tree "( ( [quote] ( *nothing* ) ) )"
- "" input causes infinite loop
- '(test) input results in segfault, while '(test ) doesn't
    => problem in parser.c
