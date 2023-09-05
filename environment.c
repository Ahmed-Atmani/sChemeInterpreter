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
    EnvHeader* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_HEADER);
    temp->varCount = 0;
    temp->procCount = 0;
    temp->nestingLevel = (enclosing == NULL) ? 0 : enclosing->nestingLevel + 1;
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
    // Env is empty
    if (env->first == NULL)
        env->first = entry;
    else
        GetLastEnvEntry(env->first)->next = entry;
    
    entry->next = NULL; // Make sure pointers to other environments are impossible
    
    // Increment correct counter
    if (entry->argumentCount == -1)
        env->varCount++;
    else
        env->procCount++;
}

EnvHeader* AddEntryToNewEnvironment(EnvHeader* oldEnv, EnvEntry* entry)
{
    EnvHeader* newEnv = MakeEnvironment(oldEnv);
    AddEntryToEnvironment(newEnv, entry);
    
    return newEnv;
}

void PrintEnvEntry(EnvEntry* entry)
{
    PrintString(entry->identifier);
    printf("\t");
    PrintValue(entry->value);    
}

EnvEntry* LookupValue(EnvHeader* env, String* identifier)
{
    EnvHeader* currentEnv = env;
    EnvEntry* currentEntry;

    // Environment search
    while (currentEnv != NULL){
        // Entry search
        currentEntry = (currentEnv == NULL) ? NULL : currentEnv->first; // Skip loop if env is NULL

        while (currentEntry != NULL){
            if (StringEq(identifier, currentEntry->identifier))
                return currentEntry;

            currentEntry = currentEntry->next;
        }
        currentEnv = currentEnv->enclosingEnv;
    }
    
    return NULL;
}

// Prints stack frames according to superposition (highest nesting level is current stackframe)
void PrintEnvironment(EnvHeader* env)
{
    EnvHeader* currentEnv = env;
    EnvEntry* currentEntry;

    // Environment search
    while (currentEnv != NULL){
        currentEntry = (currentEnv == NULL) ? NULL : currentEnv->first; // Skip loop if env is NULL

        printf("Nesting: %d\n", currentEnv->nestingLevel);

        while (currentEntry != NULL){
            printf("\t");
            PrintEnvEntry(currentEntry);
            printf("\n");
            currentEntry = currentEntry->next;
        }
        currentEnv = currentEnv->enclosingEnv;
    }
}

void FreeEnvEntry(EnvEntry* entry)
{
    // Free identifier
    FreeString(entry->identifier);

    // Free value
    FreeValue(entry->value);

    // Free object
    Deallocate(entry, sizeof(EnvEntry), ALLOC_ENV_ENTRY);
}

// Frees current environment only, not recursively
void FreeEnvironment(EnvHeader* env)
{
    EnvEntry* entry = env->first;

    // Free all entries
    while (entry != NULL){
        FreeEnvEntry(entry);
        entry = entry->next;
    }

    // Free header
    Deallocate(env, sizeof(EnvHeader), ALLOC_ENV_HEADER);

}