#include "environment.h"


// EnvEntry* MakeEnvEntry(String* identifier, Value* val)
// {
//     EnvEntry* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_ENTRY);
//     temp->next = NULL;

//     // Copy identifier
//     temp->identifier = identifier;

//     // Point to value
//     temp->value = val;

//     return temp;
// }

EnvEntry* MakeVariableEntry(String* identifier, Value* val)
{
    EnvEntry* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_ENTRY);

    temp->next = NULL;
    temp->identifier = identifier;
    temp->content.value = val;
    temp->argumentCount = -1;

    return temp;
}

EnvEntry* MakeProcedureEntry(String* identifier, TokenTree* body, int argCount)
{
    EnvEntry* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_ENTRY);

    temp->next = NULL;
    temp->identifier = identifier;
    temp->content.body = body;
    temp->argumentCount = argCount;

    return temp;
}

EnvHeader* MakeEnvironment(EnvHeader* enclosing)
{
    EnvHeader* temp = Allocate(sizeof(EnvEntry), ALLOC_ENV_ENTRY);
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

int IsVariable(EnvEntry* entry)
{
    return entry->argumentCount == -1;
}

int IsProcedure(EnvEntry* entry)
{
    return !IsVariable(entry);
}

void PrintEnvEntry(EnvEntry* entry)
{
    PrintString(entry->identifier);
    printf("\t");

    if (IsVariable(entry))
        PrintValue(entry->content.value);
    
    else
        printf("<proc>");
    
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
