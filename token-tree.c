#include "token-tree.h"


TokenTree* NewTokenTree(void)
{
    TokenTree* temp = (TokenTree*) Allocate(sizeof(TokenTree), ALLOC_TOKEN_TREE);
    temp->type = NONE;
    temp->next = NULL;
    temp->prev = NULL;
    temp->parent = NULL;
    temp->value.subTree = NULL;
    temp->value.token = NULL;
    return temp;
}

void SetToken(TokenTree* t, String* new)
{
    // Free old token
    if (HasToken(t))
        FreeString(t->value.token);

    // Set new token
    t->value.token = new;

    // Update type
    t->type = ATOM;
}

void SetTokenCounted(TokenTree* t, char* buffer, int charCount)
{
    if (!charCount)
        return;

    // Free current string content
    if (!HasToken(t))
        t->value.token = NewString(charCount);

    // Free current token content
    FreeStringContent(t->value.token);

    // Allocate and copy token
    NewStringContent(t->value.token, charCount);
    CopyCharacters(buffer, t->value.token->content, charCount);

    // Update type
    t->type = ATOM;
}

void CopyCharacters(char* src, char* dest, int count)
{
    while (count-- > 0){
        *dest = *(src++);
        dest++;
    }
    *dest = '\0';
}

void SetSubTree(TokenTree* t1, TokenTree* t2)
{
    // First free token (new trees contain "EMPTY" token)
    if (HasToken(t1))
        FreeString(t1->value.token);

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
    if (IsNull(t))
        return NewTokenTree();
        
    SetNext(t, NewTokenTree());
    return t->next;
}

void RemoveTree(TokenTree* t)
{
    // No tree
    if (IsNull(t))
        return;
    
    // Update prev's next 
    if (!IsNull(t->prev))
        t->prev->next = t->next;

    // Deallocate next 
    if (HasNext(t))
        RemoveTree(t->next);

    // Deallocate subtree recursively
    if (HasSubTree(t))
        RemoveTree(t->value.subTree);
    
    // Deallocate token
    if (HasToken(t))
        FreeString(t->value.token);
    
    // Deallocate current
    Deallocate(t, sizeof(TokenTree), ALLOC_TOKEN_TREE); 
}

int IsNull(TokenTree* t)
{
    return t == NULL;
}

int HasSubTree(TokenTree* t)
{
    return t->type == SUBLIST;
}

int HasToken(TokenTree* t)
{
    return t->type == ATOM;
}

int HasNothing(TokenTree* t)
{
    return t->type == NONE;
}

int HasNext(TokenTree* t)
{
    return !IsNull(t->next);
}

int HasPrevious(TokenTree* t)
{
    return !IsNull(t->prev);
}

int HasParent(TokenTree* t)
{
    return !IsNull(t->parent);
}

TokenTree* GetLastNode(TokenTree* t)
{
    if (IsNull(t))
        return NULL;

    TokenTree *prev = t, *curr = t;

    while (!IsNull(curr)){
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

TokenTree* AppendList(TokenTree* t1, TokenTree* t2)
{
    if (IsNull(t1))
        return t2;

    TokenTree* last = GetLastNode(t1);
    SetNext(last, t2);
    return t1;
}

TokenTree* AppendValue(TokenTree* t, String* new)
{
    TokenTree* temp = NewTokenTree();
    SetToken(temp, new);
    AppendList(t, temp);
    return t;
}

void Foreach(TokenTree* t, void (*f)(String*))
{
    if (IsNull(t))
        return;
    
    if (HasSubTree(t))
        Foreach(t->value.subTree, f);
    else if (HasToken(t))
        f(t->value.token);

    Foreach(t->next, f);
}

TokenTree* CopyTokenTree(TokenTree* tree)
{
    if (IsNull(tree)) 
        return NULL;

    TokenTree* result = NewTokenTree();
    TokenTree* curr = result;

    while (!IsNull(tree)){
        if (HasToken(tree))
            SetToken(curr, CopyString(tree->value.token));
        else if (HasSubTree(tree))
            SetSubTree(curr, CopyTokenTree(tree->value.subTree));
        
        tree = tree->next;
        if (!IsNull(tree))
            curr = AddNewNext(curr);
    }

    return result;
}

TokenTree* CopySubtree(TokenTree* tree)
{
    return NULL;
}

void PrintTree(TokenTree* t)
{
    printf("( ");

    while (!IsNull(t)){
        if (HasToken(t)){
            printf("[");
            PrintString(t->value.token);
            printf("] ");
        }
        else if (HasNothing(t))
            printf("*nothing* ");
        else if (HasSubTree(t))
            PrintTree(t->value.subTree);
        t = t->next;
    }
        printf(") ");
}
