#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>
#include <string.h>
#include "memproc.h"



// === Types of content

// == S_Number
typedef enum NumberType {INTEGER, EXACT, INEXACT} NumberType;
typedef enum Sign {POSITIVE, NEGATIVE} Sign;

// Fraction
typedef struct Fraction{
    Sign sign;
    int numerator, denominator;
} Fraction;

// S_Number
typedef struct S_Number{
    NumberType type;
    union{
        int integer;
        Fraction exact;
        double inexact;
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

// Boolean
typedef enum S_Boolean {FALSE, TRUE} S_Boolean;

// === Value type

typedef enum ValueType {EMPTY_LIST, ERROR, VOID, NUMBER, SYMBOL, STRING, CHARACTER, BOOLEAN, MCONS, VECTOR, POINTER, PROCEDURE} ValueType; 

typedef struct Value{
    ValueType type;
    union{
        // Add a struct variable foreach type
        S_Number* number;
        char character;
        S_Boolean boolean;
        S_Vector* vector;
        S_String* string;

    } content;
    // void* address;
} Value;


// === Prototypes

// == Constructors
S_Number* MakeS_IntegerNumber(int value);
Value* NewS_IntegerValue(int value);
Value* NewS_BooleanValue(int t);
// Value* NewVectorValue(int length, Value* content); // For make-vector
Value* NewS_VectorValue(int length);
Value* NewS_CharacterValue(char character);
Value* NewS_StringValue(const char* S_String);

// == Boolean 
int IsFalse(Value* val);
int IsTrue(Value* val);

// == S_String
char* S_CharVectorToCharArray(S_Vector* v);

// == General
void PrintValue(Value* val);

#endif
