#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "string.h"
#include "value.h"
#include "token-tree.h"
#include "value.h"


typedef struct EnvEntry{
    String* identifier;
    int argumentCount; // -1: variable   non-negative: procedure
    union {
        Value* value;
        TokenTree* body;
    } content;      
    struct EnvEntry* next;
} EnvEntry;

typedef struct EnvHeader{
    int varCount, procCount, nestingLevel;
    EnvEntry* first;
    struct EnvHeader* enclosingEnv;
} EnvHeader;

EnvEntry* MakeVariableEntry(String* identifier, Value* val);
EnvEntry* MakeProcedureEntry(String* identifier, TokenTree* body, int argCount);
EnvHeader* MakeEnvironment(EnvHeader* enclosing);
EnvEntry* GetLastEnvEntry(EnvEntry* entry);
void AddEntryToEnvironment(EnvHeader* env, EnvEntry* entry);
EnvHeader* AddEntryToNewEnvironment(EnvHeader* oldEnv, EnvEntry* entry);
EnvEntry* LookupValue(EnvHeader* env, String* identifier);
void PrintEnvironment(EnvHeader* env);
int IsVariable(EnvEntry* entry);
int IsProcedure(EnvEntry* entry);
void PrintEnvEntry(EnvEntry* entry);

#endif
