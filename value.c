#include "value.h"

/*
CONVENTION:
    MakeXYZValue makes and returns value object with content of type XYZ
    NewXYZ makes and returns content object of type XYZ

*/

Value* NewValue(ValueType type)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = type;
    return temp;
}

// === Number

// = Constructors
Value* MakeS_IntegerValue(int n)
{
   return MakeS_FractionValue(n, 1);
}

Value* MakeS_FractionValue(int num, int denom)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = NUMBER;
    temp->content.number = NewS_FractionNumber(num, denom);
    return temp;
}

Value* MakeS_InexactValue(double n)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = NUMBER;
    temp->content.number = NewS_InexactNumber(n);
    return temp;
}

// = Auxiliary constructors
S_Number* NewS_InexactNumber(double n)
{
    S_Number* temp = Allocate(sizeof(S_Number), ALLOC_VALUE);
    temp->type = INEXACT;
    temp->content.inexact = n;
    return temp;
}

S_Number* NewS_FractionNumber(int num, int denom) // Makes exact (fraction)
{
    S_Number* temp = Allocate(sizeof(S_Number), ALLOC_VALUE);
    temp->type = EXACT;
    temp->content.exact = NewS_Fraction(num, denom);
    return temp;
}

S_Number* NewS_IntegerNumber(int n) // Makes exact (integer)
{
    return NewS_FractionNumber(n, 1);
}

S_Fraction* NewS_Fraction(int num, int denom)
{
    S_Fraction* temp = Allocate(sizeof(S_Fraction), ALLOC_VALUE);
    temp->numerator = abs(num);
    temp->denominator = abs(denom);
    temp->sign = ((num < 0 && denom < 0) || (num >= 0 && denom >= 0)) ? 0 : 1;
    return temp;
}

// = Predicates
int IsS_Number(Value* val)
{
    return val->type == NUMBER;
}

int IsInteger(S_Number* num)
{
    return (num->type == EXACT && num->content.exact->denominator == 1);
}

// = Other functions
void PrintS_Number(S_Number* num)
{
    switch (num->type){
        case EXACT:
            if (IsInteger(num))
                printf("%s%i", num->content.exact->sign ? "-" : "", num->content.exact->numerator);
            else
                printf("%s%i/%i", num->content.exact->sign ? "-" : "", num->content.exact->numerator, num->content.exact->denominator);
            break;
        
        case INEXACT:
            printf("%d", num->content.inexact);
            break;
    }
}

void FreeS_Number(S_Number* num)
{
    if (num->type == EXACT)
        FreeFraction(num->content.exact);

    Deallocate(num, sizeof(S_Number), ALLOC_VALUE);
}

void FreeFraction(S_Fraction* f)
{
    Deallocate(f, sizeof(S_Fraction), ALLOC_VALUE);
}

// === Boolean
// = Constructor
Value* MakeS_BooleanValue(int true)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = BOOLEAN;
    temp->content.boolean = true ? TRUE : FALSE;
    return temp;
}

// = Other functions
void PrintS_Boolean(S_Boolean bool)
{
    printf("#%c", bool == FALSE ? 'f' : 't');
}

// === Vector
// = Constructor
Value* MakeS_VectorValue(int length)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = VECTOR;
    temp->content.vector = NewS_Vector(length);

    // Initialize values
    for (int i = 0; i < length; i++)
        temp->content.vector->contents[i] = (void*)MakeS_IntegerValue(i);

    return temp;
}

// = Auxiliary constructor
S_Vector* NewS_Vector(int length)
{
    S_Vector* v = Allocate(sizeof(S_Vector), ALLOC_VALUE);
    v->length = length;
    v->contents = (void**)Allocate(sizeof(void*) * length, ALLOC_VALUE);
    return v;
}

// = Other functions
void PrintS_Vector(S_Vector* v)
{
    int len = v->length;
    printf("#(");
    for (int i = 0; i < len; i++){
        if (i != 0)
            printf(" ");
        PrintValue((Value*)v->contents[i]);
    }
    printf(")");
}

// === Character
// = Constructor
Value* MakeS_CharacterValue(char character)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = CHARACTER;
    temp->content.character = character;
    return temp;
}

// = Other functions
void PrintS_Character(char c)
{
    printf("#\\%c", c);
}

// === String
// = Constructor
Value* MakeS_StringValue(String* string)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    int length = string->length;
    temp->type = STRING;
    temp->content.string = NewS_String(length);

    for (int i = 0; i < length; i++)
        temp->content.string->vector->contents[i] = MakeS_CharacterValue(string->content[i]);
    
    return temp;
}

// = Auxiliary constructor
S_String* NewS_String(int length)
{
    S_String* str = Allocate(sizeof(S_String), ALLOC_VALUE);
    str->vector = NewS_Vector(length);
    return str;
}

// = Conversion functions
char* S_CharVectorToCharArray(S_Vector* v)
{
    int len = v->length;
    char* temp = Allocate(sizeof(char) * (len + 1), ALLOC_VALUE);
        
    for (int i = 0; i < len; i++)
        temp[i] = ((Value*)(v->contents[i]))->content.character;
    
    temp[len] = '\0';

    return temp;
}

// = Other functions
void PrintS_String(S_String* s)
{
    char* temp = S_CharVectorToCharArray(s->vector);
    printf("\"%s\"", S_CharVectorToCharArray(s->vector));
    Deallocate(temp, sizeof(char) * (s->vector->length + 1), ALLOC_VALUE);
}

// === Lambda
// = Constructor
Value* MakeS_LambdaValue(TokenTree* body, struct EnvHeader* env, int argCount)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = LAMBDA;
    temp->content.lambda = NewS_Lambda(body, env, argCount);
    return temp;
}

// = Auxiliary constructor
S_Lambda* NewS_Lambda(TokenTree* body, struct EnvHeader* env, int argCount)
{
    S_Lambda* temp = Allocate(sizeof(S_Lambda), ALLOC_VALUE);
    temp->body = body;
    temp->environment = env;
    temp->argCount = argCount;
    return temp;
}

// = Other functions
void PrintS_Lambda(S_Lambda* l)
{
    printf("<lambda: %d args>", l->argCount);
}

// === Void
void PrintVoid()
{
    printf("#<void>");
}

// === Other functions
void PrintValue(Value* val)
{
    ValueType type = (val == NULL) ? -1 : val->type;

    switch (type){
        case NUMBER:
            PrintS_Number(val->content.number);
            break;
        
        case CHARACTER:
            PrintS_Character(val->content.character);
            break;

        case BOOLEAN:
            PrintS_Boolean(val->content.boolean);
            break;

        case VECTOR:
            PrintS_Vector(val->content.vector);
            break;

        case STRING:
            PrintS_String(val->content.string);
            break;
        
        case VOID:
            PrintVoid();
            break;
        case LAMBDA:
            PrintS_Lambda(val->content.lambda);
            break;
        
        case -1:
            printf("value.c:PrintValue: Given value is NULL\n");
    }
}

int IsFalse(Value* val) // Only ever returns false if it is #f
{
    return (val->type == BOOLEAN && val->content.boolean == FALSE);
}

int IsTrue(Value* val)
{
    return !IsFalse(val);
}

void FreeValue(Value* val)
{
    ValueType type = (val == NULL) ? -1 : val->type;

    switch (type){
        case NUMBER:
            FreeS_Number(val->content.number);
            break;

        case VECTOR:
            // FreeS_Vector(val->content.vector);
            break;

        case STRING:
            // FreeS_String(val->content.string);
            break;
                
        case CHARACTER:
        case BOOLEAN:
        case VOID:
        case -1:
            printf("value.c:FreeValue: given value is NULL\n");
    }

    Deallocate(val, sizeof(Value), ALLOC_VALUE);
}
