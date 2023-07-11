#include "main.h"

EnvHeader* env;


int main(int argc, char** argv)
{
    EnvEntry* temp = NULL;

    // == Make environment
    env = MakeEnvironment(NULL);

    
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("test"), MakeS_IntegerValue(5)));
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("ANOTHER"), MakeS_IntegerValue(6)));
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("one"), MakeS_IntegerValue(7)));

    PrintEnvironment(env);

    printf("\n\n");

    // == Make environment
    env = MakeEnvironment(env);

    
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("the"), MakeS_IntegerValue(10)));
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("quick"), MakeS_IntegerValue(11)));
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("brown"), MakeS_IntegerValue(12)));
    AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("fox"), MakeS_IntegerValue(13)));

    PrintEnvironment(env);  

    // // temp: add variable to env
    // AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("test"), MakeS_IntegerValue(5)));

    // temp = LookupValue(env, NewStringFromLiteral("test"));
    // if (temp == NULL)
    //     printf("null");
    // else
    //     PrintValue(temp->content.value);
    // printf("\n");
    
    // env = MakeEnvironment(env);

    // temp = LookupValue(env, NewStringFromLiteral("test"));

    // if (temp == NULL)
    //     printf("null");
    // else
    //     PrintValue(temp->content.value);
    // printf("\n");


    // // == Make environment
    // env = MakeEnvironment(NULL);

    // // temp: add variable to env
    // AddEntryToEnvironment(env, MakeVariableEntry(NewStringFromLiteral("test"), MakeS_IntegerValue(5)));

    // // == REPL
    // PromptLoop();

    return 0;
}

void PromptLoop()
{
    char string[INPUT_SIZE];
    TokenTree* tree;
    Value* result;

    // == Loop
    for (;;){
        // == Read
        printf("> "); 
        scanf("%[^\n]%*c", string);

        // // == Eval
        tree = StringToTokenTree(string);
        result = EvalSequence(tree, NULL);

        // // == Print
        printf("string: %s\ntree: ", string);
        PrintTree(tree);
        printf("\nresult: ");
        PrintValue(result);
        printf("\n");
        
        // // == Free memory
        RemoveTree(tree);
        if (result != NULL) // temporary (some functions temporarily return NULL as Value* object)
            FreeValue(result);
        // PrintMemory();
    }
}
 