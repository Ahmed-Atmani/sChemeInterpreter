#include "eval.h"


// void PrintCurrentNode(TokenTree* t)
// {
//     if (IsNull(t))
//         printf("Tree is null");
//     else if (HasToken(t)){
//         printf("HasToken: ");
//         PrintString(t->value.token);
//     }
//     else if (HasSubTree(t)){
//         printf("HasSubTree: ( ");
//         TokenTree* curr = t->value.subTree;
//         while (curr != NULL){
//             if (HasToken(t)){
//                 PrintString(curr->value.token);
//                 printf(" ");
//             }
//             else if (HasSubTree(t))
//                 printf("*subsubtree* ");
//         curr = curr->next; 
//         }
//         printf(" )");
//     }
//     printf("\n");
// }

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
    
    Value* result;

    // = Number
    if (IsIntegerLiteral(exp)){
        // printf("\n == NUMBER ==\n");
        return MakeS_IntegerValue(atoi(exp->value.token->content));    
    }

    // = Symbol
    if (IsQuoted(exp)){
        // printf("\n == QUOTED ==\n");
        return GetSymbol(exp->value.subTree); // Should return symbol value
    }

    if (IsLambda(exp)){
        // printf("\n == LAMBDA ==\n");
        return GetLambda(exp->value.subTree, env);
    }

    // = Definition
    if (IsDefine(exp)){
        // printf("\n == DEFINE ==\n");
        EvalDefinition(exp->value.subTree, env);
        return MakeS_Void();
    }

    // = DEBUG: Print Environment
    if (IsPrintEnv(exp)){
        PrintEnvironment(env);
        printf("\n");
        return MakeS_Void();
    }

    // = DEBUG: Print Memory allocation
    if (IsPrintMem(exp)){
        PrintMemory(env);
        return MakeS_Void();;
    }

    // = DEBUG: Print Lambda Body
    if (IsPrintLambdaBody(exp)){
        // printf("\n == PRINT-BODY ==\n");
        return EvalPrintLambdaBody(exp->value.subTree, env);
    }

    // = TEMP: Sum
    if (IsSum(exp)){
        // printf("\n == SUM ==\n");
        return PerformSum(exp->value.subTree, env); // Give list of tokens starting from '+'
    }

    // = Variable
    if (IsIdentifier(exp)){
        // printf("\n == IDENTIFIER ==\n");
        EnvEntry* temp = LookupValue(env, exp->value.token);

        result = (temp == NULL) ? NULL : CopyValue(temp->value);
        
        if (result == NULL){
            printf("ERROR: Unbound identifier: ");
            PrintString(exp->value.token);
            printf("\n==========================\n");
        }

        return result;
    }

    // = Exit
    if (IsExit(exp)){
        // printf("\n == EXIT ==\n");
        EvalExit();
    }

    return NULL; // Should return error: unknown expression
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

int IsTagged(TokenTree* exp, char* tag)
{
    return HasSubTree(exp) &&
          !IsNull(exp->value.subTree) &&
           HasToken(exp->value.subTree) &&
           IsKeyword(exp->value.subTree->value.token, tag);
}

int IsPrintLambdaBody(TokenTree* exp)
{
    return IsTagged(exp, PRINT_BODY);
}

Value* EvalPrintLambdaBody(TokenTree* exp, EnvHeader* env)
{
    printf("BODY: ");
    PrintTree(Eval(exp->next, env)->content.lambda->body);
    printf("\n");
    return MakeS_Void();
}

Value* GetLambda(TokenTree* exp, EnvHeader* env)
{
    // // = Identifier // This is for procedure definitions
    // String* identifier = NewStringFromLiteral(exp->next->value.subTree->value.token->content);

    // = ArgList and ArgCount
    int argCount = 0;
    TokenTree* args = exp->next->value.subTree;
    ArgList* argLst = NULL;

    ArgList* curr = argLst;

    while (args != NULL){
        argCount++;
        curr = AddArgToList(curr, args->value.token);
        args = args->next;
    }
    
    // = Body
    TokenTree* body = CopyTokenTree(exp->next->next->value.subTree);

    // = Environment
    EnvHeader* newEnv = MakeEnvironment(env);

    return MakeS_LambdaValue(body, newEnv, argCount, argLst);
}

int IsLambda(TokenTree* exp)
{
    return IsTagged(exp, FUNCTION);
}

Value* GetSymbol(TokenTree* exp)
{
    return MakeS_SymbolValue(exp->next->value.token->content);
}

int IsPrintEnv(TokenTree* exp)
{
    return IsTagged(exp, PRINT_ENV);
}

int IsPrintMem(TokenTree* exp)
{
    return IsTagged(exp, PRINT_MEM);
}

int IsDefine(TokenTree* exp)
{
    return IsTagged(exp, DEFINITION);
}

Value* EvalDefinition(TokenTree* exp, EnvHeader* env)
{
    if (!HasNext(exp))
        return NULL;

    switch (HasSubTree(exp->next)){
        case 0: // Variable definition
            String* identifier = NewStringFromLiteral(exp->next->value.token->content);
            
            if (!HasNext(exp->next)){
                printf("ERROR: EvalDefinition: Two args given!\n");
                return NULL;
            }

            Value* val = Eval(exp->next->next, env);
            AddEntryToEnvironment(env, MakeEnvEntry(identifier, val));

            break;
        
        default: // Procedure definition
            break;
    }

    return NULL;
}

int IsIdentifier(TokenTree* exp)
{
    return HasToken(exp);
}

int IsSum(TokenTree* exp)
{
    return IsTagged(exp, SUM_KEYWORD);
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
    return IsTagged(exp, QUOTE);
}

int IsExit(TokenTree* exp)
{
    return IsTagged(exp, EXIT_KEYWORD);
}

Value* EvalConditional(EnvHeader* env){
    printf("Cond!\n");
    return NULL;
}

Value* EvalIf(EnvHeader* env){
    printf("If!\n");
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
