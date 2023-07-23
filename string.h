#ifndef STRING_H
#define STRING_H

#include <string.h>
#include "memproc.h"


typedef struct String{
    int allocatedBytes, length;
    char* content;
} String;

String* NewString(int charCount);
String* CopyString(String* str);
void NewStringContent(String* str, int charCount);
String* NewStringFromLiteral(const char* literal);
void CopyLiteralToString(String* str, const char* literal);
void RewriteString(String* str, const char* literal);

int StringEq(String* str1, String* str2);

void PrintString(String* str);
void FreeStringContent(String* str);
void FreeString(String* str);


#endif
