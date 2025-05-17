#include <assert.h>
#include "parser.h"

static Node* handle_start(List* token_list, int* idx);
static Node* handle_plus_minus(List* token_list, int* idx);
static Node* handle_mul_div(List* token_list, int* idx);
static Node* handle_power(List* token_list, int* idx);
static Node* handle_func(List* token_list, int* idx);
static Node* handle_value(List* token_list, int* idx);

#define WRONG_LAST_SYMB fprintf(stderr, red(ERROR)": Wrong character at the end of file: %s\n", take_str_from_node(token_list->data[*idx]))
#define WRONG_COMB      fprintf(stderr, red(ERROR)": Wrong combination of characters at the end of file: %s %s\n", take_str_from_node(token_list->data[*idx]), take_str_from_node(token_list->data[*idx - 1]))

Tree* parse(List* token_list)
{
    assert(token_list != nullptr);

    int idx = 0;
    Tree* token_tree = make_tree();
    token_tree->root = handle_start(token_list, &idx);
    token_tree->size = token_list->size;
    return token_tree;
}

static Node* handle_start(List* token_list, int* idx)
{
    assert(token_list != nullptr);

    if (IS_VARIABLE || IS_VALUE || IS_OPEN_BRACKETS)
    {
        Node* result = handle_plus_minus(token_list, idx);
        return result;
    }

    else
    {
        WRONG_LAST_SYMB;
        return NULL;
    }

    return NULL;
}

static Node* handle_plus_minus(List* token_list, int* idx)
{
    assert(token_list != nullptr);

    Node* cur_node = token_list->data[*idx];
    if (IS_VARIABLE || IS_VALUE || IS_OPEN_BRACKETS || IS_FUNCTION)
    {
        Node* result = handle_mul_div(token_list, idx);

        if (*idx >= token_list->size - 1)
            return result;

        (*idx)++;
        if (IS_PLUS || IS_MINUS)
        {
            cur_node = token_list->data[*idx];
            cur_node->right = result;
            (*idx)++;
            cur_node->left = handle_plus_minus(token_list, idx);
        }
        else if IS_CLOSE_BRACKETS
        {
            cur_node = result;
            (*idx)--;
        }
        else
        {
            WRONG_COMB;
            return NULL;
        }
    }
    else
    {
        WRONG_COMB;
            return NULL;
    }
    return cur_node;
}

static Node* handle_mul_div(List* token_list, int* idx)
{
    assert(token_list != nullptr);

    Node* cur_node = token_list->data[*idx];
    if (IS_VARIABLE || IS_VALUE || IS_OPEN_BRACKETS || IS_FUNCTION)
    {
        Node* result = handle_power(token_list, idx);

        if (*idx >= token_list->size - 1)
            return result;
        (*idx)++;
        if (IS_MULTIPLY || IS_DIVISION)
        {
            cur_node = token_list->data[*idx];
            cur_node->right = result;
            (*idx)++;
            cur_node->left = handle_mul_div(token_list, idx);
        }
        else if (IS_CLOSE_BRACKETS || IS_PLUS || IS_MINUS)
        {
            cur_node = result;
            (*idx)--;
        }
        else
        {
            WRONG_COMB;
            return NULL;
        }
    }
    else
    {
        WRONG_COMB;
        return NULL;
    }
    return cur_node;
}

static Node* handle_power(List* token_list, int* idx)
{
    assert(token_list != nullptr);

    Node* ret_node = token_list->data[*idx];
    if (IS_VARIABLE || IS_VALUE || IS_OPEN_BRACKETS || IS_FUNCTION)
    {
        Node* result = handle_func(token_list, idx);
        if (*idx >= token_list->size - 1)
            return result;
        (*idx)++;
        if IS_POWER
        {
            ret_node = token_list->data[*idx];
            ret_node->right = result;
            (*idx)++;
            ret_node->left = handle_power(token_list, idx);
        }
        else if (IS_CLOSE_BRACKETS || IS_PLUS || IS_MINUS || IS_MULTIPLY || IS_DIVISION)
        {
            ret_node = result;
            (*idx)--;
        }
        else
        {
            WRONG_COMB;
            return NULL;
        }
    }
    else
    {
        WRONG_COMB;
        return NULL;
    }
    return ret_node;
}

static Node* handle_func(List* token_list, int* idx)
{
    assert(token_list != nullptr);

    Node* ret_node = token_list->data[*idx];
    if (IS_VARIABLE || IS_VALUE || IS_OPEN_BRACKETS)
    {
        Node* result = handle_value(token_list, idx);
        if (*idx >= token_list->size - 1)
            return result;
        (*idx)++;
        if IS_FUNCTION
        {
            ret_node = token_list->data[*idx];
            ret_node->right = result;
            double buf_value = -1;
            ret_node->left = make_node(VALUE_TYPE, &buf_value);
        }
        else if (IS_CLOSE_BRACKETS || IS_PLUS || IS_MINUS || IS_MULTIPLY || IS_DIVISION || IS_POWER)
        {
            ret_node = result;
            (*idx)--;
        }
        else
        {
            WRONG_COMB;
            return NULL;
        }
    }
    else
    {
        WRONG_COMB;
        return NULL;
    }
    return ret_node;
}

static Node* handle_value(List* token_list, int* idx)
{
    assert(token_list != nullptr);

    Node* buffer = NULL;
    if (IS_VALUE || IS_VARIABLE)
    {
        return token_list->data[*idx];
    }
    if (IS_OPEN_BRACKETS)
    {
        (*idx)++;
        buffer = handle_plus_minus(token_list, idx);
        (*idx)++;
        if IS_FUNCTION
        {
            token_list->data[*idx]->right = buffer;
            double buf_value = -1;
            token_list->data[*idx]->left = make_node(VALUE_TYPE, &buf_value);
            return token_list->data[*idx];
        }
    }
    else
    {
        WRONG_COMB;
        return NULL;
    }

    return buffer;
}
