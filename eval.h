#ifndef EVAL_H
#define EVAL_H

#include "token-tree.h"
#include "value.h"
#include "environment.h"
#include "string.h"


#define QUOTE "quote"
#define DEFINITION "define"
#define ASSIGNMENT "set!"
#define IF "if"
#define CONDITIONAL "cond"
#define EXIT_KEYWORD "exit"
#define SUM_KEYWORD "+"

#define PRINT_ENV "print-env"
#define PRINT_MEM "print-mem"


Value* Eval(TokenTree* exp, EnvHeader* env);
Value* EvalSequence(TokenTree* tree, EnvHeader* env);

int IsKeyword(String* src, char* keyWord);
int IsIntegerLiteral(TokenTree* exp);
int IsQuoted(TokenTree* exp);

int IsSum(TokenTree* exp);
Value* PerformSum(TokenTree* operands, EnvHeader* env);

int IsPrintEnv(TokenTree* exp);
int IsPrintMem(TokenTree* exp);
int IsIdentifier(TokenTree* exp);   

int IsDefine(TokenTree* exp);
Value* EvalDefinition(TokenTree* exp, EnvHeader* env);

int IsExit(TokenTree* exp);

Value* EvalSum(TokenTree* tree, EnvHeader* env);
Value* EvalConditional(EnvHeader* env);
Value* EvalIf(EnvHeader* env);
Value* EvalAssignment(EnvHeader* env);
void EvalExit();

#endif