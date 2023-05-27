#include "main.h"


int main(int argc, char** argv)
{
    // == REPL
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
 