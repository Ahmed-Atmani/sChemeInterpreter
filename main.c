#include <stdio.h>
// #include "parser.c"
// #include "linked-list.h"
// #include "token-list.h"
#include "token-tree.h"
#include "parser.h"

// 1. Parse file (to token list)
// 2. Evaluate token lists (definition?, if?, variable?, ...)

int main(int argc, char** argv){

    // char testString[] = "(define x 10)";
    // TokenList* lst = StringToTokenList(testString);
    // Foreach(lst, PrintToken);

    // char buff[10];
    // char str[] = "this test is working";
    // CopyCharacters(str, buff, 7);
    // printf("%s", buff);



    // TokenTree* t = NewTokenTree();
    // SetToken(t, "This");
    
    // SetNext(t, NewTokenTree());
    // SetToken(t->next, "is");
    
    // SetNext(t->next, NewTokenTree());
    // SetToken(t->next->next, "a");

    // SetNext(t->next->next, NewTokenTree());
    // SetSubTree(t->next->next->next, NewTokenTree());
    // SetToken(t->next->next->next->value.subTree, "test");
    // //
    // SetNext(t->next->next->next->value.subTree, NewTokenTree());
    // SetToken(t->next->next->next->value.subTree->next, "sublist");
    
    // SetNext(t->next->next->next, NewTokenTree());
    // SetToken(t->next->next->next->next, "123");
    // PrintTree(t);
    // printf("\n");
    // printf("\n");

    // RemoveTree(t->next->next->next->value.subTree->next);
    // PrintTree(t);
    // printf("\n");



    printf("string: %s\n", argv[1]);
    TokenTree* parsed = StringToTokenTree(argv[1]);

    printf("tree: ");
    PrintTree(parsed);
    printf("\n");


    return 0;
}


