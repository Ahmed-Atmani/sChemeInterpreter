#include "environment.h"


EnvEntry* MakeEnvEntry(String* identifier, Value* val)
{
    EnvEntry* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_ENTRY);
    temp->next = NULL;

    // Copy identifier
    temp->identifier = identifier;

    // Point to value
    temp->value = val;

    return temp;
}

EnvHeader* MakeEnvironment(EnvHeader* enclosing)
{
    EnvHeader* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_ENTRY);
    temp->varCount = 0;
    temp->procCount = 0;
    temp->enclosingEnv = enclosing;
    temp->first = NULL;

    return temp;
}

EnvEntry* GetLastEnvEntry(EnvEntry* entry)
{
    // Entry itself is NULL
    if (entry == NULL)
        return entry;

    // Entry is last
    if (entry->next == NULL)
        return entry;
    
    // Recursively check if next entry is last
    return GetLastEnvEntry(entry->next);
}

void AddEntryToEnvironment(EnvHeader* env, EnvEntry* entry)
{
    if (env->first == NULL)
        env->first = entry;
    else
        GetLastEnvEntry(env->first)->next = entry;
    
    entry->next = NULL; // Make sure pointers to other environments are impossible
}

EnvHeader* AddEntryToNewEnvironment(EnvHeader* oldEnv, EnvEntry* entry)
{
    EnvHeader* newEnv = MakeEnvironment(oldEnv);
    AddEntryToEnvironment(newEnv, entry);
    
    return newEnv;
}

Value* LookupValue(EnvHeader* env, String* identifier)
{
    EnvHeader* currentEnv = env;
    EnvEntry* currentEntry = (env == NULL) ? NULL : env->first; // Skip loop if env is NULL

    while (currentEntry != NULL && currentEnv != NULL){

        // No more entries in current environment
        if (currentEntry == NULL){
            currentEnv = currentEnv->enclosingEnv;
            currentEntry = currentEnv->first;
            continue;
        }

        // Compare identifiers
        if (StringEq(identifier, currentEntry->identifier))
            return currentEntry->value;
    }
    
    return NULL;
}
