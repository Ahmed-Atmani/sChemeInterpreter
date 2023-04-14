#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token-tree.h"

#define BUFF_SIZE 100


// Split file into multiple expressions (split by newline): (()()()()) --> () () () ()
// Split each expression into list of tokens (split by sp


TokenTree* StringToTokenTree(char* string);
void CopyCharacters(char* src, char* dest, int count);

#endif
