#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "string.h"
#include "value.h"

typedef struct EnvEntry{
    String* identifier;
    int argumentCount; // -1: variable   non-negative: procedure
    Value* value;
    struct EnvEntry* next;
} EnvEntry;

typedef struct EnvHeader{
    int varCount, procCount, nestingLevel;
    EnvEntry* first;
    struct EnvHeader* enclosingEnv;
} EnvHeader;

EnvEntry* MakeEnvEntry(String* identifier, Value* val);
EnvHeader* MakeEnvironment(EnvHeader* enclosing);
EnvEntry* GetLastEnvEntry(EnvEntry* entry);
void AddEntryToEnvironment(EnvHeader* env, EnvEntry* entry);
EnvHeader* AddEntryToNewEnvironment(EnvHeader* oldEnv, EnvEntry* entry);
EnvEntry* LookupValue(EnvHeader* env, String* identifier);
void PrintEnvironment(EnvHeader* env);
void PrintEnvEntry(EnvEntry* entry);

#endif
