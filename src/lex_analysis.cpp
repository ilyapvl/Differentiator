#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>

#include "lex_analysis.h"

List* lexical_analysis(char* str)
{

    List* token_list = make_list(LIST_LEN);

    int idx = 0;
    while (str[idx] != '\0')
    {

        Node* new_node = encode(str, &idx);
        append_to_list(token_list, new_node);
        idx++;
    }
    return token_list;
}

Node* encode(char* str, int* idx)
{
    double value = 0;

    if (isnumber(str[*idx]))
    {
        value = get_value(str, idx);
        return make_node(VALUE_TYPE, &value);
    }

    Node* func = check_func(str, idx);
    if (func)
        return func;

    if (isalpha(str[*idx]))
    {
        return make_node(VARIABLE_TYPE, &str[*idx]);
    }
    Tokens token = UNKNOWN;

    switch(str[*idx])
    {
        case '+':
            token = ADD;
            return make_node(OPER_TYPE, &token);
        case '-':
            token = SUBTRACT;
            return make_node(OPER_TYPE, &token);
        case '*':
            token = MULTIPLY;
            return make_node(OPER_TYPE, &token);
        case '/':
            token = DIVISION;
            return make_node(OPER_TYPE, &token);
        case '^':
            token = POWER;
            return make_node(OPER_TYPE, &token);
        case '(':
            token = LEFT_BR;
            return make_node(OPER_TYPE, &token);
        case ')':
            token = RIGHT_BR;
            return make_node(OPER_TYPE, &token);
        default:
            return NULL;
    }
}

double get_value(char* str, int* idx)
{
    assert(str != nullptr);

    double value = 0;
    double non_int = 0.0;
    while (str[*idx] >= '0' && str[*idx] <= '9')
    {
        value = value * 10 + str[*idx] - '0';
        (*idx)++;
    }

    if (str[*idx] == '.')
    {
        (*idx)++;
        double divider = 10;
        while (str[*idx] >= '0' && str[*idx] <= '9')
        {
            non_int = non_int + (str[*idx] - '0') / divider;
            divider *= 10;
            idx++;
        }

    }
    (*idx)--;
    return value + non_int;
}

Node* check_func(char* str, int* idx)
{
    enum Tokens token = UNKNOWN;
    if (strncmp(&str[*idx], "cos", 3) == 0)
    {
        *idx += 2;
        token = COS;

    }
    if (strncmp(&str[*idx], "sin", 3) == 0)
    {
        *idx += 2;
        token = SIN;

    }
    if (strncmp(&str[*idx], "tg", 2) == 0)
    {
        (*idx)++;
        token = TAN;

    }
    if (strncmp(&str[*idx], "ctg", 3) == 0)
    {
        *idx += 2;
        token = CTAN;

    }
    if (strncmp(&str[*idx], "ln", 2) == 0)
    {
        (*idx)++;
        token = LN;
    }

    if (token != UNKNOWN) return make_node(OPER_TYPE, &token);
    return NULL;
}
