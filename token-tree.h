#ifndef LINKED_TREE_H
#define LINKED_TREE_H

#include <stdio.h>
#include <string.h>
#include "memproc.h"

#define EMPTY_TOKEN "EMPTY"


typedef enum ContentType {NONE, ATOM, SUBLIST} ContentType;

typedef struct TokenTree {
    ContentType type;
    union{
        char* token;
        struct TokenTree* subTree;
    } value;
    struct TokenTree *next, *prev, *parent;
} TokenTree;


TokenTree* NewTokenTree(void);

void SetNext(TokenTree* t1, TokenTree* t2);
TokenTree* AddNewNext(TokenTree* t);
void SetToken(TokenTree* t, char* val);
void SetTokenCounted(TokenTree* t, char* buffer, int charCount);
void SetSubTree(TokenTree* t1, TokenTree* t2);
void RemoveTree(TokenTree* t);

int IsEmpty(TokenTree* t);
int HasNext(TokenTree* t);
int HasSubTree(TokenTree* t);
int HasAtom(TokenTree* t);
int HasParent(TokenTree* t);
int HasNoToken(TokenTree* t);

TokenTree* AppendList(TokenTree* t1, TokenTree* t2);
TokenTree* AppendValue(TokenTree* t, char* val);
TokenTree* GetLastNode(TokenTree* t);

void Foreach(TokenTree* t, void (*f)(char*));
void PrintTree(TokenTree* t);
void CopyCharacters(char* src, char* dest, int count);

#endif
