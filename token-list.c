#include "token-list.h"


TokenList* Cons(char* val, TokenList* next){
    TokenList* temp = (TokenList*) malloc(sizeof(TokenList));
    temp->value = val;
    temp->next = next;
    return temp;
}

TokenList* NewTokenList(char* val){
    TokenList* temp = (TokenList*) malloc(sizeof(TokenList));
    temp->value = val;
    temp->next = NULL;
    return temp;
}

TokenList* GetLastNode(TokenList* lst){
    if (lst == NULL)
        return NULL;

    TokenList *prev = lst, *curr = lst;

    while (curr != NULL){
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

TokenList* AppendList(TokenList* lst1, TokenList* lst2){
    if (lst1 == NULL)
        return lst2;

    GetLastNode(lst1)->next = lst2;
    return lst1;
}

TokenList* AppendValue(TokenList* lst, char* val){
    GetLastNode(lst)->next = NewTokenList(val);
    return lst;
}

void Foreach(TokenList* lst, void (*f)(char*)){
    if (lst == NULL)
        return;
    
    f(lst->value);
    Foreach(lst->next, f);
}