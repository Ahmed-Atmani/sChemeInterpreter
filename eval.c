#include "eval.h"


int IsKeyword(String* src, char* keyWord)
{
    int len1 = src->length, len2 = strlen(keyWord);
    if (len1 != len2)
        return 0;
    
    for (int i = 0; i < len1; i++)
        if (src->content[i] != keyWord[i])
            return 0;
    
    return 1;
}

Value* EvalSequence(TokenTree* tree, EnvHeader* env)
{
    TokenTree* currentExpr = tree;
    Value* lastValue = NULL;

    while (currentExpr != NULL){
        // Free temporary value
        if (lastValue != NULL)
            FreeValue(lastValue);
        
        // Evaluate expression
        lastValue = Eval(currentExpr, env);
        currentExpr = currentExpr->next;
    }

    return lastValue;
}

Value* Eval(TokenTree* tree, EnvHeader* env)
{
    if (IsNull(tree))
        return NULL;

    String* token;
    if (HasSubTree(tree))
        token = NewStringFromLiteral(tree->value.subTree->value.token->content);
    else if (HasToken(tree))
        token = NewStringFromLiteral(tree->value.token->content);
    
    Value* result;

    if (IsKeyword(token, CONDITIONAL))
        result = EvalConditional(env);
    else if (IsKeyword(token, IF))
        result = EvalIf(env);
    else if (IsKeyword(token, DEFINITION))
        result = EvalDefinition(env);
    else if (IsKeyword(token, ASSIGNMENT))
        result = EvalAssignment(env);
    else if (IsKeyword(token, EXIT_KEYWORD))
        EvalExit();
    // Temp
    else if (IsKeyword(token, SUM_KEYWORD))
        result = EvalSum(tree, env);

    FreeString(token);

    return result;
}

Value* EvalSum(TokenTree* tree, EnvHeader* env){

    // Do not forget to evaluate the rest
    // Value* num1 = MakeS_IntegerValue(atoi(tree->value.subTree->next->value.token->content));
    // Value* num2 = MakeS_IntegerValue(atoi(tree->value.subTree->next->next->value.token->content));
    // // Better to use other function that calculates result (and returns value* of correct s-type)
    // Value* result = MakeS_IntegerValue(num1->content.number->content.exact->numerator + num2->content.number->content.exact->numerator);
    int x = atoi(tree->value.subTree->next->value.token->content);
    int y = atoi(tree->value.subTree->next->next->value.token->content);
    Value* result = MakeS_IntegerValue(x + y);

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
    return MakeS_FractionValue(-2, 3);
    // return NULL;
}

Value* EvalAssignment(EnvHeader* env){
    printf("Set!!\n");
    return NULL;
}

void EvalExit()
{
    exit(0);
}