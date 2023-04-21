#include "token-tree.h"


TokenTree* NewTokenTree(void)
{
    TokenTree* temp = (TokenTree*) Allocate(sizeof(TokenTree), ALLOC_TOKEN_TREE);
    temp->type = NONE;
    temp->next = NULL;
    temp->prev = NULL;
    temp->parent = NULL;
    temp->value.subTree = NULL;
    temp->value.token = Allocate((strlen(EMPTY_TOKEN) + 1) * sizeof(char), ALLOC_TOKEN_CONTENT);
    strcpy(temp->value.token, EMPTY_TOKEN);
    return temp;
}

void SetToken(TokenTree* t, char* val)
{
    Deallocate(t->value.token, sizeof(char) * (strlen(t->value.token) + 1), ALLOC_TOKEN_CONTENT); // Deallocate old token

    // Allocate and copy token
    t->value.token = Allocate((strlen(val) + 1) * sizeof(char), ALLOC_TOKEN_CONTENT);
    strcpy(t->value.token, val);

    // Update type
    t->type = ATOM;
}

void SetTokenCounted(TokenTree* t, char* buffer, int charCount)
{
    if (!charCount)
        return;

    Deallocate(t->value.token, sizeof(char) * (strlen(t->value.token) + 1), ALLOC_TOKEN_CONTENT); // Deallocate old token

    // Allocate and copy token
    t->value.token = Allocate((charCount + 1) * sizeof(char), ALLOC_TOKEN_CONTENT);
    CopyCharacters(buffer, t->value.token, charCount);

    // Update type
    t->type = ATOM;
}

void SetSubTree(TokenTree* t1, TokenTree* t2)
{
    t1->type = SUBLIST;
    t1->value.subTree = t2;
    t2->parent = t1;
}

void SetNext(TokenTree* t1, TokenTree* t2)
{
    t1->next = t2;
    t2->prev = t1;
    t2->parent = t1->parent;
}

// Adds new next to tree and returns the added tree 
TokenTree* AddNewNext(TokenTree* t)
{
    if (IsEmpty(t))
        return NewTokenTree();
        
    SetNext(t, NewTokenTree());
    return t->next;
}

void RemoveTree(TokenTree* t)
{
    if (IsEmpty(t))
        return;
    
    // Update prev's next
    if (!IsEmpty(t->prev))
        t->prev->next = t->next; // Set previous' next to next

    // Deallocate next
    if (HasNext(t))
        RemoveTree(t->next);

    // Deallocate subtrees recursively
    if (HasSubTree(t))
        RemoveTree(t->value.subTree); // Deallocate subtrees recursively

    Deallocate(t->value.token, sizeof(char) * (strlen(t->value.token) + 1), ALLOC_TOKEN_CONTENT); // Deallocate token
    Deallocate(t, sizeof(TokenTree), ALLOC_TOKEN_TREE); // Deallocate tree itself
}

int IsEmpty(TokenTree* t)
{
    return t == NULL;
}

int HasNext(TokenTree* t)
{
    return t->next != NULL;
}

int HasSubTree(TokenTree* t)
{
    return t->type == SUBLIST;
}

int HasAtom(TokenTree* t)
{
    return !HasSubTree(t);
}

int HasParent(TokenTree* t)
{
    return t->parent != NULL;
}

int HasNoToken(TokenTree* t)
{
    return t->type == NONE;
}

TokenTree* GetLastNode(TokenTree* t)
{
    if (t == NULL)
        return NULL;

    TokenTree *prev = t, *curr = t;

    while (curr != NULL){
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

TokenTree* AppendList(TokenTree* t1, TokenTree* t2)
{
    if (t1 == NULL)
        return t2;

    TokenTree* last = GetLastNode(t1);
    SetNext(last, t2);
    return t1;
}

TokenTree* AppendValue(TokenTree* t, char* val)
{
    TokenTree* temp = NewTokenTree();
    SetToken(temp, val);
    AppendList(t, temp);
    return t;
}

void Foreach(TokenTree* t, void (*f)(char*))
{
    if (t == NULL)
        return;
    
    if (HasSubTree(t))
        Foreach(t->value.subTree, f);
    else
        f(t->value.token);

    Foreach(t->next, f);
}

void PrintTree(TokenTree* t)
{
    printf("( ");

    while (!IsEmpty(t)){
        if (HasAtom(t))
            printf("[%s] ", t->value.token);
        else
            PrintTree(t->value.subTree);
        t = t->next;
    }
        printf(") ");
}

void CopyCharacters(char* src, char* dest, int count)
{
    while (count-- > 0){
        *dest = *(src++);
        dest++;
    }
    *dest = '\0';
}
