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
    if (!HasNothing(*currentNest))
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

    int insideQuote = 0;              // Stack for quote nesting 
    int quoteStack = 0;               // Stack for quote nesting 

    for (int i = 0; i < len; i++){
        switch (string[i]){

            case '(':
                // = Update stack
                stack++; 

                // = Update quoted stack
                if (insideQuote)
                    quoteStack++;

                // = Write word
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

                // = Update quoted stack
                if (insideQuote){
                    quoteStack--;
                    if (!quoteStack){
                        // = Remove quote nesting
                        TokenTree* temp = currentNest;
                        currentNest = currentNest->parent;

                        // = Destroy old current if it's empty (no token)
                        if (HasNothing(temp))
                            RemoveTree(temp);
                    
                        insideQuote = 0;
                    }
                }

                // = Write word
                CopyBuffer(&currentNest, buffer, charCount);
                charCount = 0;

                // = Decrement nesting level
                TokenTree* temp = currentNest;
                currentNest = currentNest->parent;
                
                // = Destroy old current if it's empty (no token)
                if (HasNothing(temp))
                    RemoveTree(temp);
                break;

            case ' ':
                // = Write word
                CopyBuffer(&currentNest, buffer, charCount);
                charCount = 0;
                break;

            case '\'':
                // = Write word
                CopyBuffer(&currentNest, buffer, charCount);

                // = If not already in quote: make quote tree
                if (!insideQuote && charCount == 0){
                    // = Increment nesting level
                    SetSubTree(currentNest, NewTokenTree());
                    currentNest = currentNest->value.subTree;

                    // = Add quote expression
                    CopyBuffer(&currentNest, "quote", 5);

                    if (i == len - 1)
                        CopyBuffer(&currentNest, buffer, charCount);
                    
                    insideQuote = 1;
                    quoteStack = 0;
                    break;
                }
                // = Else: just write quote

                // = Intentional switch fallthrough

            default:
                // === Add character to current word
                buffer[charCount++] = string[i];

                if (i == len - 1)
                    CopyBuffer(&currentNest, buffer, charCount);

                break;
        }

        // printf("\nchar: '%c'\nbuffer: %s\ntree: ", string[i], buffer);
        // PrintTree(tree);
        // printf("\n");
    }

    if (stack > 0)
        printf("\n=====================\nError: %i ')' missing!\n=====================\n", stack);

    return tree;
}
