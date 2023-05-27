#include "eval.h"


void PrintCurrentNode(TokenTree* t)
{
    if (IsNull(t))
        printf("Tree is null");
    else if (HasToken(t)){
        printf("HasToken: ");
        PrintString(t->value.token);
    }
    else if (HasSubTree(t)){
        printf("HasSubTree: ( ");
        TokenTree* curr = t->value.subTree;
        while (curr != NULL){
            if (HasToken(t)){
                PrintString(curr->value.token);
                printf(" ");
            }
            else if (HasSubTree(t))
                printf("*subsubtree* ");
        curr = curr->next; 
        }
        printf(" )");
    }
    printf("\n");
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

Value* Eval(TokenTree* exp, EnvHeader* env)
{
    if (IsNull(exp))
        return NULL;
    
    Value* result = NULL;

    if (IsIntegerLiteral(exp)){
        printf("\n == NUMBER ==\n");
        result = MakeS_IntegerValue(atoi(exp->value.token->content));    
    }

    else if (IsQuoted(exp)){
        printf("\n == QUOTED ==\n");
        result = NULL;
    }

    else if (IsSum(exp)){
        printf("\n == SUM ==\n");
        result = PerformSum(exp->value.subTree, env); // Give list of tokens starting from '+'
    }
    else if (IsExit(exp)){
        printf("\n == EXIT ==\n");
        EvalExit();
    }

    return result;
}

int IsSum(TokenTree* exp)
{
    return HasSubTree(exp) && 
          !IsNull(exp->value.subTree) &&
           HasToken(exp->value.subTree) &&
           IsKeyword(exp->value.subTree->value.token, SUM_KEYWORD);
}

Value* PerformSum(TokenTree* exp, EnvHeader* env) // Exp == list starting with '+'
{
    if (!HasNext(exp))
        return NULL;

    TokenTree* currArg = exp->next;
    Value* tmpVal = NULL;
    int accumulator = 0;

    while (currArg != NULL){
        tmpVal = Eval(currArg, env);
        if (!IsS_Number(tmpVal)) // Also check for error value type
            return NULL;
        if (tmpVal->content.number->content.exact->sign)
            accumulator -= tmpVal->content.number->content.exact->numerator;
        else
            accumulator += tmpVal->content.number->content.exact->numerator;
        
        FreeValue(tmpVal);
        currArg = currArg->next;
    }

    return MakeS_IntegerValue(accumulator);

}

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

int IsIntegerLiteral(TokenTree* exp)
{
    if (!HasToken(exp))
        return 0;
    
    String* token = exp->value.token;
    int len = token->length;

    if (len == 0)
        return 0;

    for (int i = 0; i < len; i++){
        char c = token->content[i]; 
        if (i == 0 && c == '-')
            continue;
        if (!(48 <= c && c <= 57))
            return 0;
    }
    return 1;
}

int IsQuoted(TokenTree* exp)
{
    return  HasSubTree(exp) &&
           !IsNull(exp->value.subTree) &&
            HasToken(exp->value.subTree) &&
            IsKeyword(exp->value.subTree->value.token, QUOTE);
}

int IsExit(TokenTree* exp)
{
    return HasSubTree(exp) &&
          !IsNull(exp->value.subTree) &&
           HasToken(exp->value.subTree) &&
           IsKeyword(exp->value.subTree->value.token, EXIT_KEYWORD);
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
