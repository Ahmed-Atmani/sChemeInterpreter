#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include "parser.h"
#include "eval.h"
#include "value.h"
#include "memproc.h"  
#include "auxiliary.h"  

#define INPUT_SIZE 500


int main(int argc, char** argv);
void PromptLoop();

#endif