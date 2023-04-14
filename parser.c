#include "parser.h"


int NothingToCopy(char* buffer, int charCount)
{
    for (int i = 0; i < charCount; i++)
        if (buffer[i] != ' ')
            return 0;
    return 1;
}

void CopyBuffer(TokenTree** currentNest, char* buffer, int charCount)
{
    // Create next if needed
    if (!HasNoToken(*currentNest))
        *currentNest = AddNewNext(*currentNest);
    
    if (NothingToCopy(buffer, charCount))
        return;

    // Write word
    SetTokenCounted(*currentNest, buffer, charCount);
}

TokenTree* StringToTokenTree(char* string)
{
    int len = strlen(string);         // String length
    int stack = 0;                    // For counting parenthesis

    TokenTree* tree = NewTokenTree(); // Stores parse tree
    TokenTree* currentNest = tree;    // Stores current nesting level

    char buffer[BUFF_SIZE] = "";      // Holds current word
    int charCount = 0;                // Stores how long the current word is

    for (int i = 0; i < len; i++){
        switch (string[i]){

            case '(':
                // = Update stack
                stack++; 
                
                CopyBuffer(&currentNest, buffer, charCount);
                charCount = 0;

                // = Increment nesting level
                SetSubTree(currentNest, NewTokenTree());
                currentNest = currentNest->value.subTree;
                break;

            case ')':
                // = Update stack
                stack--;
                if (stack < 0)
                    printf("\n======================\nError: Unexpected ')'!\n======================\n");

                CopyBuffer(&currentNest, buffer, charCount);
                charCount = 0;

                // = Decrement nesting level
                TokenTree* temp = currentNest;
                currentNest = currentNest->parent;
                
                // Destroy old current if it's empty (no token)
                if (HasNoToken(temp))
                    RemoveTree(temp);
                break;

            case ' ':
                CopyBuffer(&currentNest, buffer, charCount);
                charCount = 0;
                break;

            default:
                // === Add character to current word
                buffer[charCount++] = string[i];
                break;
        }
    }

    if (stack > 0)
        printf("\n=====================\nError: %i ')' missing!\n=====================\n", stack);

    return tree;
}
