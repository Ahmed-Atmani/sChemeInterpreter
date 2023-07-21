#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>
// #include <string.h>
#include "string.h"
#include "memproc.h"
#include "token-tree.h"
// #include "environment.h" // Circular inclue



// === Types of content

// == S_Number
typedef enum NumberType {EXACT, INEXACT} NumberType;
typedef enum Sign {POSITIVE, NEGATIVE} Sign;

// Fraction
typedef struct S_Fraction{
    Sign sign;
    int numerator, denominator;
} S_Fraction;

// S_Number
typedef struct S_Number{
    NumberType type;
    union{
        S_Fraction* exact; // Exact
        double inexact; // Inexact
    } content;

} S_Number;

// S_Vector
typedef struct S_Vector{
    int length;
    void** contents; // Pointer to array of Value objects
} S_Vector;

// S_String
typedef struct S_String{
    S_Vector* vector;
} S_String;

// S_Symbol
typedef struct S_Symbol{
    String* str;
} S_Symbol;

// S_Lambda
struct EnvHeader;

typedef struct S_Lambda{
    int argCount;
    TokenTree* body;
    struct EnvHeader* environment;
} S_Lambda;

// Boolean
typedef enum S_Boolean {FALSE, TRUE} S_Boolean;

// === Value type

typedef enum ValueType {EMPTY_LIST, ERROR, VOID, NUMBER, SYMBOL, STRING, CHARACTER, BOOLEAN, MCONS, VECTOR, POINTER, LAMBDA} ValueType; 

typedef struct Value{
    ValueType type;
    union{
        // Add a struct variable foreach type
        S_Number* number;
        char character;
        S_Boolean boolean;
        S_Vector* vector;
        S_String* string;
        S_Symbol* symbol;   
        S_Lambda* lambda;

    } content;
    // void* address;
} Value;


// === Prototypes

Value* NewValue(ValueType type);

Value* MakeS_IntegerValue(int n);
Value* MakeS_FractionValue(int num, int denom);
Value* MakeS_InexactValue(double n);
S_Number* NewS_InexactNumber(double n);
S_Number* NewS_FractionNumber(int num, int denom);
S_Number* NewS_IntegerNumber(int n);
S_Fraction* NewS_Fraction(int num, int denom);
int IsS_Number(Value* val);
int IsInteger(S_Number* num);
void PrintS_Number(S_Number* num);
void FreeS_Number(S_Number* num);
Value* CopyS_NumberValue(S_Number* num);
void FreeFraction(S_Fraction* f);

Value* MakeS_BooleanValue(int true);
void PrintBoolean(S_Boolean bool);

Value* MakeS_VectorValue(int length);
S_Vector* NewS_Vector(int length);
void PrintS_Vector(S_Vector* v);

Value* MakeS_CharacterValue(char character);
void PrintS_Character(char c);

Value* MakeS_StringValue(String* string);
S_String* NewS_String(int length);
char* S_CharVectorToCharArray(S_Vector* v);
void PrintS_String(S_String* s);

Value* MakeS_SymbolValue(char* str);
S_Symbol* NewS_Symbol(char* str);
void PrintS_Symbol(S_Symbol* sym);
void FreeS_Symbol(S_Symbol* sym);
Value* CopyS_SymbolValue(S_Symbol* sym);    

Value* MakeS_Lambda(TokenTree* body, struct EnvHeader* env, int argCount);
S_Lambda* NewS_Lambda(TokenTree* body, struct EnvHeader* env, int argCount);
void PrintS_Lambda(S_Lambda* l);

Value* MakeS_Void();
void PrintVoid();

void PrintValue(Value* val);
int IsFalse(Value* val);
int IsTrue(Value* val);
Value* CopyValue(Value* val);
void FreeValue(Value* val);

#endif
