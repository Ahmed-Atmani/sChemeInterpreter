#include "value.h"


S_Number* MakeS_IntegerNumber(int value){
    S_Number* temp = Allocate(sizeof(S_Number), ALLOC_VALUE);
    temp->type = INTEGER;
    temp->content.integer = value;
    return temp;
}

Value* NewS_IntegerValue(int value)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = NUMBER;
    temp->content.number = MakeS_IntegerNumber(value);
    return temp;
}

Value* NewS_BooleanValue(int true)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = BOOLEAN;
    temp->content.boolean = true ? TRUE : FALSE;
    return temp;
}

S_Vector* MakeS_Vector(int length)
{
    S_Vector* v = Allocate(sizeof(S_Vector), ALLOC_VALUE);
    v->length = length;
    v->contents = (void**)Allocate(sizeof(void*) * length, ALLOC_VALUE);
    return v;
}

Value* NewS_VectorValue(int length)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = VECTOR;
    temp->content.vector = MakeS_Vector(length);

    // Initialize values
    for (int i = 0; i < length; i++)
        temp->content.vector->contents[i] = (void*)NewS_IntegerValue(i);

    return temp;
}

Value* NewS_CharacterValue(char character)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    temp->type = CHARACTER;
    temp->content.character = character;
    return temp;
}

S_String* MakeS_String(int length)
{
    S_String* str = Allocate(sizeof(S_String), ALLOC_VALUE);
    str->vector = MakeS_Vector(length);
    return str;
}

Value* NewS_StringValue(const char* string)
{
    Value* temp = Allocate(sizeof(Value), ALLOC_VALUE);
    int length = strlen(string);
    temp->type = STRING;
    temp->content.string = MakeS_String(length);

        for (int i = 0; i < length; i++)
        temp->content.string->vector->contents[i] = NewS_CharacterValue(string[i]);
    
    return temp;
}

void PrintValue(Value* val)
{
    int len;
    char* temp;

    ValueType type = val == NULL ? VOID : val->type;

    switch (type){
        case NUMBER:
            switch (val->content.number->type){
                case INTEGER:
                    printf("%i", val->content.number->content.integer);
                    break;
                
                case EXACT:
                    printf("%s%d/%d", (val->content.number->content.exact.sign ? "" : "-"), val->content.number->content.exact.numerator, val->content.number->content.exact.denominator);
                    break;
                
                case INEXACT:
                    printf("%d", val->content.number->content.inexact);
                    break;
            }
            break;
        
        case CHARACTER:
            printf("#\\%c", val->content.character);
            break;

        case BOOLEAN:
            printf("#%c", val->content.boolean == FALSE ? 'f' : 't');
            break;

        case VECTOR:
            len = val->content.vector->length;
            printf("#(");
            for (int i = 0; i < len; i++){
                if (i != 0)
                    printf(" ");
                PrintValue((Value*)val->content.vector->contents[i]);
            }
            printf(")");
            break;

        case STRING:
            temp = S_CharVectorToCharArray(val->content.string->vector);
            printf("\"%s\"", temp);
            Deallocate(temp, sizeof(char) * (val->content.string->vector->length + 1), ALLOC_VALUE);
            break;
        
        case VOID:
            printf("#<void>");
            break;
    }
}

int IsFalse(Value* val)
{
    return (val->type == BOOLEAN && val->content.boolean == FALSE);
}

int IsTrue(Value* val)
{
    return !IsFalse(val);
}

char* S_CharVectorToCharArray(S_Vector* v)
{
    int len = v->length;
    char* temp = Allocate(sizeof(char) * (len + 1), ALLOC_VALUE);
        
    for (int i = 0; i < len; i++)
        temp[i] = ((Value*)(v->contents[i]))->content.character;
    
    temp[len] = '\0';

    return temp;
}
