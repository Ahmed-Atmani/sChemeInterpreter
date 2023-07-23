# sCheme

sCheme is a Scheme interpreter written in C that is planned to support the usage of pointers, classes and other C-like features (e.g. ++, += etc.). \
This is a project that does not contribute to anything in any way that I decided to make for no reason whatsoever. 

---

## Main ideas
- Use of pointers
- Use of increment syntax (var++, var += x, ...)
- Macro expansion
- Classes
- Previous value assignment
- SDL support

---

## To do
1. **Lambda's:**
    1. Make FreeS_Lambda/CopyS_Lambda functions
    1. Fix () for e.g. lambda's with no args

1. **Definition of variables:**
    1. Define should overwrite definition of existing identifier
        => Only overwrite (set!) if identifier in same scope (not in enclosing scopes)
    1. Syntactic sugar (e.g. (define (f x) (+ x 1)))

1. **Apply:**
    1. Make new variables (arguments) in scope of function 
    1. Call EvalSequence on the body

1. Make 3-demensional array with (predicate, argcount, function) pair for macros/proc application
    1. Move PrintValue/CopyValue/FreeValue into Value object itself (func pointer)

1. **primitive procedures**
    1. Make S_Primitive Value type (that encapsulates function pointer) (?) 
    1. Add primitives to base EnvHeader
        => Primitives can be mutated just like regular variables
    1. Load put all primitives into env on startup

1. **Rewrite Parser:**
    1. Enable excape characters (e.g. #\a becomes token instead of (vector \a))
    1. () should be (\*nothing\*) instead of a copy/reference to next

1. Error Handling:
    1. When error is encountered in any eval/apply proc => return a modified stack (with current scope pushed)
    1. Make way of printing error


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
- Segfault after deleting characters (overwriting) on input
- "()" and "'()" input gives segfault when freeing inputTree
    => "()" has parse tree "( ( ) )"
    => "'()" has parse tree "( ( [quote] ( *nothing* ) ) )"
- "" input causes infinite loop
- '(test) input results in segfault, while '(test ) doesn't
    => problem in parser.c
