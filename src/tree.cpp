#include <stdlib.h>
#include <string.h>
#include "differentiator.h"
#include "tree.h"
#include "comparator.h"
#include <stdio.h>

node* make_node(int type, void* content)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    new_node->type = type;
    if (type == VALUE_TYPE)
        new_node->content.value = *(double*)(content);
    else if (type == VARIABLE_TYPE)
        new_node->content.variable = *(char*)(content);
    else if (type == OPER_TYPE)
        new_node->content.token = *(enum Tokens*)(content);

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->prev = NULL;

    return new_node;
}

node* copy_node(node* copied_node)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    new_node->type = copied_node->type;
    if (copied_node->type == VALUE_TYPE)
        new_node->content.value = copied_node->content.value;
    else if (copied_node->type == VARIABLE_TYPE)
        new_node->content.variable = copied_node->content.variable;
    else if (copied_node->type == OPER_TYPE)
        new_node->content.token = copied_node->content.token;
    if (copied_node->left)
    {
        new_node->left = copy_node(copied_node->left);
    }
    if (copied_node->right)
    {
        new_node->right = copy_node(copied_node->right);
    }
    return new_node;
}

Tree* make_tree()
{
    Tree* new_tree = (Tree*) calloc(1, sizeof(Tree));
    new_tree->root = NULL;
    new_tree->size = 0;

    return new_tree;
}

Node* append_to_tree(Tree* tree, Node* new_node, Node* current_node, int indicator)
{
    tree->size++;

    if (tree->size == 1)
    {
        tree->root = new_node;
        return new_node;
    }

    new_node->prev = current_node;

    if (indicator == RIGHT)
    {
        current_node->right = new_node;
    }
    else if (indicator == LEFT)
    {
        current_node->left = new_node;
    }

    return new_node;
}

void delete_node(Node* deleted_node)
{
    if (!deleted_node)
        return;

    if (deleted_node->left)
        delete_node(deleted_node->left);

    if (deleted_node->right)
        delete_node(deleted_node->right);

    free(deleted_node);
}

void destruct_tree(Tree* deleted_tree)
{
    if (!deleted_tree)
        return

    delete_node(deleted_tree->root);
}

char str2[20];

char* take_str_from_node(Node* cur_node)
{
    switch (cur_node->type)
    {
        case OPER_TYPE:
            return decode_operation(cur_node);
        case VALUE_TYPE:
            if (cmp_with_number(cur_node->content.value, (double)(int)(cur_node->content.value)))
                snprintf(str2, 20, "%d", (int)cur_node->content.value);
            else
                snprintf(str2, 20, "%.2lf", cur_node->content.value);
            return str2;
        case VARIABLE_TYPE:
            return &cur_node->content.variable;
    }

    return NULL;
}

char* decode_operation(Node* cur_node)
{
    switch (cur_node->content.token)
    {
        case ADD:
            return (char*)"+";
        case SUBTRACT:
            return (char*)"-";
        case MULTIPLY:
            return (char*)"*";
        case DIVISION:
            return (char*)"/";
        case POWER:
            return (char*)"^";
        case COS:
            return (char*)"cos";
        case SIN:
            return (char*)"sin";
        case TAN:
            return (char*)"tg";
        case CTAN:
            return (char*)"ctg";
        case LN:
            return (char*)"ln";
        case LEFT_BR:
            return (char*)"(";
        case RIGHT_BR:
            return (char*)")";
        default:
            return (char*)"none";
    }
}
