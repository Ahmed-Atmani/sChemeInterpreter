#include <stdio.h>
#include "parser.h"


int main(int argc, char** argv)
{
    printf("string: %s\n", argv[1]);
    TokenTree* parsed = StringToTokenTree(argv[1]);

    printf("tree: ");
    PrintTree(parsed);
    printf("\n");

    return 0;
}
