# sCheme

sCheme is a Scheme interpreter written in C that is planned to support the usage of pointers, classes and other C-like features (e.g. ++, += etc.). \
This is a project that does not contribute to anything in any way that I decided to make for no reason whatsoever. 

---

## Main ideas
- Use of pointers
- Use of increment syntax (var++, var += x, ...)
- Macro expansion
- Classes

---

## To do now
1. Return singleton/new void type after definition/printmem/...
1. Make it possible to define procedures:
    1. Make CheckArgCount function that is called on each macro/proc application
    1. Make Lambda type with constructor
    1. Manually add lambda to env to test
    1. Complete EvalDefinition
1. Make Apply procedure that will:
    1. Make a new environment
    1. Make new variables (arguments) 
    1. Call EvalSequence on the body
1. Make 3-demensional array with predicate-argcount-function for macros/proc application
1. Make primitive procedures
    1. Make S_Primitive Value type (that encapsulates function pointer) (?) 
    1. Add primitives to base EnvHeader
        => Primitives can be mutated just like regular variables
    1. Load put all primitives into env on startup

## To do later
- Add Error type with Error type handling
- Make procedures to copy Environment in various ways (e.g. copy-while-adding-entry)

- Make ValEnv type (Value-Environment-pair) for return type of Eval
- Modify Eval to return Value-Environment pair

- Modify Parser to be able to parse characters (e.g. #\a becomes token instead of (vector \a))

## Features and fixes
### Features to implement
- SubEnvironments should be a copy of the previous one (mutations should not affect the )
- Eval should return a value and a new (modified) environment !!!!
- Eval environment (with copy function that copies it)
- Apply
- Copy function for values (be careful which values to copy!)
- Stack trace for error info (return Error Value object with stack trace)
    => Or just check on all procs if value is of type Error, then AppendTrace(errorValue, currentProcName)
- Find a way to make the pointer system better (e.g. keep track of all pointers with its size to make freeing easier (= without specifying size)) 

### Changes to add
- Put fraction sign to nominator, and make procedure that "balances" the sign to the nominator (to call before returning new value)
- Make better makefile
- When value is <#void>, nothing is printed
- Check parenthesis balance and empty input before parsing (or while parsing pass error to main to skip eval) 
- Make new Read implementation (with getchar (while char != '\n')) 

### Bugs to fix
- "()" and "'()" input gives segfault when freeing inputTree
    => "()" has parse tree "( ( ) )"
    => "'()" has parse tree "( ( [quote] ( *nothing* ) ) )"
- "" input causes infinite loop
- '(test) input results in segfault, while '(test ) doesn't
    => problem in parser.c
