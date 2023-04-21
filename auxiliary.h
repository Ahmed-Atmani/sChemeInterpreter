#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string.h>
#include "memproc.h"


typedef struct String{
    int allocatedBytes;
    char* content;
} String;

String* NewString(int charCount);
void NewStringContent(String* str, int charCount);
String* NewStringFromLiteral(const char* literal);
void CopyLiteralToString(String* str, const char* literal);
void RewriteString(String* str, const char* literal);
void PrintString(String* str);
void FreeStringContent(String* str);
void FreeString(String* str);


#endif
