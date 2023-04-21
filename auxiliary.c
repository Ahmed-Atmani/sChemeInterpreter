#include "auxiliary.h"


String* NewString(int charCount)
{
    String* str = Allocate(sizeof(String), ALLOC_STRING);
    NewStringContent(str, charCount);
    return str;
}

void NewStringContent(String* str, int charCount)
{
    str->allocatedBytes = sizeof(char) * (charCount + 1);
    str->content = Allocate(str->allocatedBytes, ALLOC_STRING_CONTENT);
}

String* NewStringFromLiteral(const char* literal)
{
    String* str = NewString(strlen(literal));
    CopyLiteralToString(str, literal);
    return str;
}

void CopyLiteralToString(String* str, const char* literal)
{
    strcpy(str->content, literal);
}

void RewriteString(String* str, const char* literal)
{
    FreeStringContent(str);
    NewStringContent(str, strlen(literal));
    CopyLiteralToString(str, literal);
}

void PrintString(String* str)
{
    printf("%s", str->content);
}

void FreeStringContent(String* str)
{
    if (str->content == NULL)
        return;
    
    Deallocate(str->content, str->allocatedBytes, ALLOC_STRING_CONTENT);
    str->allocatedBytes = 0;
    str->content = NULL;
}

void FreeString(String* str)
{
    FreeStringContent(str);
    Deallocate(str, sizeof(String), ALLOC_STRING);
}
