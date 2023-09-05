#include "value.h"

/*
CONVENTION:
    MakeXYZValue makes and returns value object with content of type XYZ
    NewXYZ makes and returns content object of type XYZ

*/

// === Value

void* AllocateValue(size_t size)
{
    return Allocate(size, ALLOC_VALUE);
}

void DeallocateValue(void* ptr, size_t size)
{
    Deallocate(ptr, size, ALLOC_VALUE);
}

Value* NewValue(ValueType type)
{
    Value* temp = AllocateValue(sizeof(Value));
    temp->type = type;
    return temp;
}

// === ArgList

ArgList* MakeArgList(String* identifier)
{
    ArgList* temp = AllocateValue(sizeof(ArgList));
    temp->identifier = CopyString(identifier);
    temp->next = NULL;

    return temp;
}

ArgList* AddArgToList(ArgList* lst, String* identifier)
{
    if (lst == NULL)
        return MakeArgList(identifier);
    
    lst->next = MakeArgList(identifier);
    return lst->next;
}

void FreeArgList(ArgList* lst)
{
    if (lst == NULL)
        return;
    
    FreeString(lst->identifier);
    FreeArgList(lst->next);
}

// === Number

// = Constructors
Value* MakeS_IntegerValue(int n)
{
   return MakeS_FractionValue(n, 1);
}

Value* MakeS_FractionValue(int num, int denom)
{
    Value* temp = NewValue(NUMBER);
    temp->content.number = NewS_FractionNumber(num, denom);
    return temp;
}

Value* MakeS_InexactValue(double n)
{
    Value* temp = NewValue(NUMBER);
    temp->content.number = NewS_InexactNumber(n);
    return temp;
}

// = Auxiliary constructors
S_Number* NewS_InexactNumber(double n)
{
    S_Number* temp = AllocateValue(sizeof(S_Number));
    temp->type = INEXACT;
    temp->content.inexact = n;
    return temp;
}

S_Number* NewS_FractionNumber(int num, int denom) // Makes exact (fraction)
{
    S_Number* temp = AllocateValue(sizeof(S_Number));
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
    S_Fraction* temp = AllocateValue(sizeof(S_Fraction));
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
            printf("%f", num->content.inexact);
            break;
    }
}

Value* CopyS_NumberValue(S_Number* num)
{    
    switch (num->type){
        case EXACT:
            return MakeS_FractionValue(num->content.exact->numerator, num->content.exact->denominator);
        case INEXACT:
            return MakeS_InexactValue(num->content.inexact);
    }
}

void FreeS_Number(S_Number* num)
{
    if (num->type == EXACT)
        FreeFraction(num->content.exact);

    DeallocateValue(num, sizeof(S_Number));
}

void FreeFraction(S_Fraction* f)
{
    DeallocateValue(f, sizeof(S_Fraction));
}

// === Boolean
// = Constructor
Value* MakeS_BooleanValue(int true)
{
    Value* temp = NewValue(BOOLEAN);
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
    Value* temp = NewValue(VECTOR);
    temp->content.vector = NewS_Vector(length);

    // Initialize values
    for (int i = 0; i < length; i++)
        temp->content.vector->contents[i] = (void*)MakeS_IntegerValue(i);

    return temp;
}

// = Auxiliary constructor
S_Vector* NewS_Vector(int length)
{
    S_Vector* v = AllocateValue(sizeof(S_Vector));
    v->length = length;
    v->contents = (void**)AllocateValue(sizeof(void*) * length);
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
    Value* temp = NewValue(CHARACTER);
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
    Value* temp = NewValue(STRING);
    int length = string->length;
    temp->content.string = NewS_String(length);

    for (int i = 0; i < length; i++)
        temp->content.string->vector->contents[i] = MakeS_CharacterValue(string->content[i]);
    
    return temp;
}

// = Auxiliary constructor
S_String* NewS_String(int length)
{
    S_String* str = AllocateValue(sizeof(S_String));
    str->vector = NewS_Vector(length);
    return str;
}

// = Conversion functions
char* S_CharVectorToCharArray(S_Vector* v)
{
    int len = v->length;
    char* temp = AllocateValue(sizeof(char) * (len + 1));
        
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
    DeallocateValue(temp, sizeof(char) * (s->vector->length + 1));
}

// === Symbol
// = Constructor
Value* MakeS_SymbolValue(char* str)
{
    Value* val = NewValue(SYMBOL);
    val->content.symbol = NewS_Symbol(str);
    return val;
}

// = Auxiliary constructor
S_Symbol* NewS_Symbol(char* str)
{
    S_Symbol* temp = AllocateValue(sizeof(S_Symbol));
    temp->str = NewStringFromLiteral(str);
    return temp;
}

// = Other functions
void PrintS_Symbol(S_Symbol* sym)
{
    printf("'");
    PrintString(sym->str);
}

void FreeS_Symbol(S_Symbol* sym)
{
    FreeString(sym->str);
    DeallocateValue(sym, sizeof(S_Symbol));
}

Value* CopyS_SymbolValue(S_Symbol* sym)
{
    return MakeS_SymbolValue(sym->str->content);
}

// === Lambda       
// = Constructor
Value* MakeS_LambdaValue(TokenTree* body, struct EnvHeader* env, int argCount, ArgList* argList)
{
    Value* temp = NewValue(LAMBDA);
    temp->type = LAMBDA;
    temp->content.lambda = NewS_Lambda(body, env, argCount, argList);
    return temp;
}

// = Auxiliary constructor
S_Lambda* NewS_Lambda(TokenTree* body, struct EnvHeader* env, int argCount, ArgList* argList)
{
    S_Lambda* temp = AllocateValue(sizeof(S_Lambda));
    temp->body = body;
    temp->environment = env;
    temp->argCount = argCount;
    temp->args = argList;
    return temp;
}

// = Other functions

Value* CopyS_LambdaValue(S_Lambda* l)
{
    // ENV AND ARGS SHOULD ALSO BE COPIED (AS THEY MIGHT BE FREED LATER)
    return MakeS_LambdaValue(CopyTokenTree(l->body), l->environment, l->argCount, l->args);
}

void FreeS_Lambda(S_Lambda* l)
{
    // Free body
    RemoveTree(l->body);

    // Free env
    // FreeEnvironment(l->environment); // Not possible (circular include DAG if env.h is included)
 
    // Free argList
    FreeArgList(l->args);

    // Free object
    DeallocateValue(l, sizeof(S_Lambda));
}

void PrintS_Lambda(S_Lambda* l)
{
    printf("<lambda: %i args>", l->argCount);
}

// === Void
// = Constructor
Value* MakeS_Void()
{
    return NewValue(VOID);
}

// = Other functions
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

        case SYMBOL:
            PrintS_Symbol(val->content.symbol);
            break;

        case LAMBDA:
            PrintS_Lambda(val->content.lambda);
            break;
        
        case VOID:
            PrintVoid();
            break;
        
        case -1:
            printf("ERROR: value.c:PrintValue: Given value is NULL\n");
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

Value* CopyValue(Value* val)
{
    ValueType type = (val == NULL) ? -1 : val->type;

    switch (type){
        case NUMBER:
            return CopyS_NumberValue(val->content.number);
            break;
        
        case CHARACTER:
            // return CopyS_Character(val->content.character);
            break;

        case BOOLEAN:
            // return CopyS_Boolean(val->content.boolean);
            break;

        case VECTOR:
            // return CopyS_Vector(val->content.vector);
            break;

        case STRING:
            // return CopyS_String(val->content.string);
            break;

        case SYMBOL:
            return CopyS_SymbolValue(val->content.symbol);
            break;
            
        case LAMBDA:
            return CopyS_LambdaValue(val->content.lambda);
            break;
        
        case VOID:
            // return CopyVoid();
            break;
        
        case -1:
            printf("value.c:PrintValue: Given value is NULL\n");
    }
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

        case SYMBOL:
            FreeS_Symbol(val->content.symbol);
            break;
                
        case CHARACTER:
        case BOOLEAN:
        case LAMBDA:
            FreeS_Lambda(val->content.lambda);
        case VOID:
        case -1:
            printf("value.c:FreeValue: given value is NULL\n");
    }

    DeallocateValue(val, sizeof(Value));
}
