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

// char* my_gets(char* buffer)
// {
//     fgets(buffer, INPUT_SIZE, stdin);

//     char* temp = buffer;
//     while (*temp++ != '\n')
// }

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
        result = Eval(tree, NULL);

        // // == Print
        printf("string: %s\ntree: ", string);
        PrintTree(tree);
        printf("\nresult: ");
        PrintValue(result);
        printf("\n");
        
        // // == Free memory
        RemoveTree(tree);
        FreeValue(result);
        PrintMemory();
    }
}
 