#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string.h>
#include "value.h"


typedef struct EnvEntry{
    char* identifier;
    Value* value;
    struct EnvEntry* next;
} EnvEntry;

typedef struct EnvHeader{
    int varCount, procCount;
    EnvEntry* first;
    struct EnvHeader* enclosingEnv;
} EnvHeader;


EnvEntry* MakeEnvEntry(const char* name, Value* val);
EnvHeader* MakeEnvironment(EnvHeader* enclosing);
EnvEntry* GetLastEnvEntry(EnvEntry* entry);
void AddEntryToEnvironment(EnvHeader* env, EnvEntry* entry);
EnvHeader* AddEntryToNewEnvironment(EnvHeader* oldEnv, EnvEntry* entry);
Value* LookupValue(EnvHeader* env, const char* identifier);

#endif
