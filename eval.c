#include "eval.h"


int IsKeyword(char* src, const char* keyWord)
{
    int len1 = strlen(src), len2 = strlen(keyWord);
    if (len1 != len2)
        return 0;
    
    for (int i = 0; i < len1; i++)
        if (src[i] != keyWord[i])
            return 0;
    
    return 1;
}

Value* EvalSequence(TokenTree* tree, EnvHeader* env)
{
    // Evaluates trees with following structure:
    // ((proc1 arg1 ...) val1 (proc2 arg1 ...) ...) 

    TokenTree* currentExpr = tree;
    Value* lastValue = NewS_IntegerValue(0);

    while (currentExpr != NULL){
        //free value
        lastValue = Eval(tree, env);
        currentExpr = tree->next;
    }

    return lastValue;
}

Value* Eval(TokenTree* tree, EnvHeader* env)
{
    if (IsEmpty(tree))
        return NULL;

    char* token = (HasSubTree(tree)) ? tree->value.subTree->value.token : tree->value.token;

    if (IsKeyword(token, CONDITIONAL))
        return EvalConditional(env);
    else if (IsKeyword(token, IF))
        return EvalIf(env);
    else if (IsKeyword(token, DEFINITION))
        return EvalDefinition(env);
    else if (IsKeyword(token, ASSIGNMENT))
        return EvalAssignment(env);
    else if (IsKeyword(token, EXIT_KEYWORD))
        EvalExit();
    
    // Temp
    else if (IsKeyword(token, SUM_KEYWOARD))
        return EvalSum(tree, env);
}

Value* EvalSum(TokenTree* tree, EnvHeader* env){

    // Do not forget to evaluate the rest
    Value* num1 = NewS_IntegerValue(atoi(NewStringFromLiteral(tree->value.subTree->next->value.token)->content));
    Value* num2= NewS_IntegerValue(atoi(NewStringFromLiteral(tree->value.subTree->next->next->value.token)->content));

    // Better to use other function that calculates result (and returns value* of correct s-type)
    Value* result = NewS_IntegerValue(num1->content.number->content.integer + num2->content.number->content.integer);

    // Free num1, num2

    return result;
}

Value* EvalConditional(EnvHeader* env){
    printf("Cond!\n");
    return NULL;
}

Value* EvalIf(EnvHeader* env){
    printf("If!\n");
    return NULL;
}

Value* EvalDefinition(EnvHeader* env){
    printf("Define!\n");
    return NULL;
}

Value* EvalAssignment(EnvHeader* env){
    printf("Set!!\n");
    return NULL;
}

void EvalExit()
{
    exit(0);
}