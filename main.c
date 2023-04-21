#include "main.h"


int main(int argc, char** argv)
{
    // == PrintValue test

    // Value* test = NewIntegerValue(5);
    // Value* test = NewBooleanValue(0);
    // Value* test = NewCharacterValue('c');
    // Value* test = NewVectorValue(10);
    // char string[] = "test123";
    // Value* test = NewStringValue(string);
    // PrintValue(test);


    // == Tree memory leak test

    // PrintMemory();
    // TokenTree* tree = StringToTokenTree(argv[1]);
    // PrintMemory();
    // RemoveTree(tree);
    // PrintMemory();


    // == String and PrintMemory test

    // PrintMemory();
    // String* str = NewStringFromLiteral("test123");
    // PrintString(str);
    // printf("\n");
    // PrintMemory();
    // RewriteString(str, "This is a quick test");
    // PrintString(str);
    // printf("\n");
    // PrintMemory();
    // FreeStringContent(str);
    // PrintMemory();
    // FreeString(str);
    // PrintMemory();


    // == REPL

    PromptLoop();

    return 0;
}

void PromptLoop()
{
    char* string;
    TokenTree* tree;

    for (;;){
        string = Allocate(sizeof(char) * INPUT_SIZE, ALLOC_OTHER);
        // == Prompt
        printf("> "); gets(string);

        // printf("string: %s\n", string);
        tree = StringToTokenTree(string);
        PrintTree(tree);
        printf("\n");
        
        Deallocate(string, sizeof(char) * INPUT_SIZE, ALLOC_OTHER);

        Value* result = Eval(tree, NULL);
        PrintValue(result);
        // FreeValue()
        printf("\n");
        
        // == Free tree
        RemoveTree(tree);

        // PrintMemory();

    }
}
