#include "main.h"

EnvHeader* env;


int main(int argc, char** argv)
{
    EnvEntry* temp = NULL;

    // == Make environment
    env = MakeEnvironment(NULL);

    AddEntryToEnvironment(env, MakeEnvEntry(NewStringFromLiteral("test"), MakeS_IntegerValue(123)));

    // // == REPL
    PromptLoop();

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
        result = EvalSequence(tree, env);

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
 