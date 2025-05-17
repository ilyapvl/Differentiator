#include <math.h>
#include <assert.h>
#include "optimization.h"
#include "comparator.h"
#include <stdio.h>

static double ONE = 1.0;
static double ZERO = 0.0;

static Node* simplify(Node* handled_node, bool* changed, int* new_tree_size);
static Node* do_operation(Node* oper_node, Node* left_node, Node* right_node);
static Node* optimizate_if_right_zero(Node* oper_node, Node* left_node);
static Node* optimizate_if_left_zero(Node* oper_node, Node* right_node);
static Node* optimizate_if_right_one(Node* oper_node, Node* left_node);
static Node* optimizate_if_left_one(Node* oper_node, Node* right_node);

Tree* simplify_tree(Tree* handled_tree, bool* changed)
{
    assert(handled_tree != nullptr);
    int new_tree_size = 0;
    handled_tree->root = simplify(handled_tree->root, changed, &new_tree_size);
    handled_tree->size = new_tree_size;
    return handled_tree;
}

static Node* simplify(Node* handled_node, bool* changed, int* new_tree_size)
{
    assert(handled_node != nullptr);

    Node* new_node = NULL;

    if (NODE_IS_VALUE(handled_node) || NODE_IS_VARIABLE(handled_node))
    {
        (*new_tree_size)++;
        return copy_node(handled_node);
    }

    Node* left_node = simplify(handled_node->left, changed, new_tree_size);
    Node* right_node = simplify(handled_node->right, changed, new_tree_size);

    if NODE_IS_ZERO(left_node)
    {
        new_node = optimizate_if_left_zero(handled_node, right_node);
        if (new_node)
        {
            *changed = true;
            return new_node;
        }
    }
    if NODE_IS_ZERO(right_node)
    {
        new_node = optimizate_if_right_zero(handled_node, left_node);
        if (new_node)
        {
            *changed = true;
            return new_node;
        }
    }

    if NODE_IS_ONE(left_node)
    {
        new_node = optimizate_if_left_one(handled_node, right_node);
        if (new_node)
        {
            *changed = true;
            return new_node;
        }
    }
    if NODE_IS_ONE(right_node)
    {
        new_node = optimizate_if_right_one(handled_node, left_node);
        if (new_node)
        {
            *changed = true;
            return new_node;
        }
    }

    if (NODE_IS_VALUE(left_node) && NODE_IS_VALUE(right_node))
    {
        new_tree_size--;
        *changed = true;
        return do_operation(handled_node, left_node, right_node);
    }

    new_node = copy_node(handled_node);
    new_node->left = left_node;
    new_node->right = right_node;
    new_tree_size++;
    return new_node;
}

static Node* do_operation(Node* oper_node, Node* left_node, Node* right_node)
{
    assert(oper_node != nullptr);
    assert(left_node != nullptr);
    assert(right_node != nullptr);

    Node* new_node = copy_node(left_node);
    switch (oper_node->content.token)
    {
        case ADD:
            new_node->content.value += right_node->content.value;
            break;
        case SUBTRACT:
            new_node->content.value -= right_node->content.value;
            break;
        case MULTIPLY:
            new_node->content.value *= right_node->content.value;
            break;
        case DIVISION:
            new_node->content.value /= right_node->content.value;
            break;
        case POWER:
            new_node->content.value = pow(new_node->content.value, right_node->content.value);
            break;
        case COS:
            new_node->content.value = cos(right_node->content.value);
            break;
        case SIN:
            new_node->content.value = sin(right_node->content.value);
            break;
        case TAN:
            new_node->content.value = tan(right_node->content.value);
            break;
        case CTAN:
            new_node->content.value = 1/tan(right_node->content.value);
            break;
        case LN:
            new_node->content.value = log(right_node->content.value);
            break;
        default:
            assert(NULL);
    }

    return new_node;
}

static Node* optimizate_if_left_zero(Node* oper_node, Node* right_node)
{
    assert(oper_node != nullptr);
    assert(right_node != nullptr);

    switch (oper_node->content.token)
    {
        case ADD:
            return right_node;
        case MULTIPLY:
        case DIVISION:
        case POWER:
            return make_node(VALUE_TYPE, &ZERO);

        default:
            return NULL;
    }
}

static Node* optimizate_if_right_zero(Node* oper_node, Node* left_node)
{
    assert(oper_node != nullptr);
    assert(left_node != nullptr);

    switch (oper_node->content.token)
    {
        case ADD:
            return left_node;
        case SUBTRACT:
            return left_node;
        case MULTIPLY:
            return make_node(VALUE_TYPE, &ZERO);
        case DIVISION:
            assert(NULL);
        case POWER:
            return make_node(VALUE_TYPE, &ONE);
        default:
            return NULL;
    }
}

static Node* optimizate_if_left_one(Node* oper_node, Node* right_node)
{
    assert(oper_node != nullptr);
    assert(right_node != nullptr);

    switch (oper_node->content.token)
    {
        case ADD:
        case SUBTRACT:
            break;
        case MULTIPLY:
            return right_node;
        case DIVISION:
            break;
        case POWER:
            return right_node;
        default:
            return NULL;
    }

    return NULL;
}

static Node* optimizate_if_right_one(Node* oper_node, Node* left_node)
{
    assert(oper_node != nullptr);
    assert(left_node != nullptr);

    switch (oper_node->content.token)
    {
        case ADD:
        case SUBTRACT:
            break;
        case MULTIPLY:
            return left_node;
        case DIVISION:
            return left_node;
        case POWER:
            return left_node;
        default:
            return NULL;
    }

    return NULL;
}
