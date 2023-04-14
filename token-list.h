#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct TokenList {
    char* value;
    struct TokenList* next;
} TokenList;

TokenList* Cons(char* val, TokenList* next);
TokenList* NewTokenList(char* val);
TokenList* GetLastNode(TokenList* lst);
TokenList* AppendList(TokenList* lst1, TokenList* lst2);
TokenList* AppendValue(TokenList* lst, char* val);
void Foreach(TokenList* lst, void (*f)(char*));

#endif