#include <assert.h>
#include "differentiator.h"
#include "optimization.h"
#include "latex.h"
#include <stdio.h>

static double ONE = 1.0;
static double M_ONE = -1.0;
static double ZERO = 0.0;
static double TWO = 2.0;

static Tree* take_tree_of_derivative(Tree* handled_tree);
static Node* take_derivative(Node* handled_node);
static Node* get_derivative_mul(Node* oper_node);
static Node* get_derivative_div(Node* oper_node);
static Node* get_derivative_pow(Node* oper_node);
static Node* get_derivative_cos(Node* oper_node);
static Node* get_derivative_sin(Node* oper_node);
static Node* get_derivative_tan(Node* oper_node);
static Node* get_derivative_ctan(Node* oper_node);
static Node* get_derivative_ln(Node* oper_node);
static Node* evaluate(Node* oper_node);

void take_n_derivatives(Tree* token_tree, int derivative_qty, FILE* tex)
{
    assert(token_tree != nullptr);

    bool changed = 1;
    Tree* token_tree2 = simplify_tree(token_tree, &changed);
    char* start_str = (char*)calloc(1000, sizeof(char));
    handle_operation(token_tree2->root, start_str);
    add_to_tex_file(start_str, tex);

    for (int i = 0; i < derivative_qty; i++)
    {
        changed = true;
        token_tree2 = simplify_tree(token_tree2, &changed);
        token_tree2 = take_tree_of_derivative(token_tree2);

        while (changed)
        {
            changed = false;
            token_tree2 = simplify_tree(token_tree2, &changed);
        }
        
        handle_operation(token_tree2->root, start_str);
        add_to_tex_file(start_str, tex);
    }
}

static Node* evaluate(Node* oper_node)
{
    assert(oper_node != nullptr);

    Node* new_node = copy_node(oper_node);

    switch (oper_node->content.token)
    {
        case ADD:
            new_node->left = take_derivative(oper_node->left);
            new_node->right = take_derivative(oper_node->right);

            break;
        case SUBTRACT:
            new_node->left = take_derivative(oper_node->left);
            new_node->right = take_derivative(oper_node->right);

            break;
        case MULTIPLY:
            new_node = get_derivative_mul(oper_node);

            break;
        case DIVISION:
            new_node = get_derivative_div(oper_node);

            break;
        case POWER:
            new_node = get_derivative_pow(oper_node);

            break;
        case COS:
            new_node = get_derivative_cos(oper_node);

            break;
        case SIN:
            new_node = get_derivative_sin(oper_node);

            break;
        case TAN:
            new_node = get_derivative_tan(oper_node);

            break;
        case CTAN:
            new_node = get_derivative_ctan(oper_node);

            break;
        case LN:
            new_node = get_derivative_ln(oper_node);

            break;
        default:
            assert(0);
    }
    return new_node;
}

static Node* get_derivative_mul(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, add_tok = ADD;
    Node* new_node = make_node(OPER_TYPE, &add_tok);
    new_node->left = make_node(OPER_TYPE, &mul_tok);
    new_node->right = make_node(OPER_TYPE, &mul_tok);
    new_node->left->right = copy_node(oper_node->right);
    new_node->left->left = take_derivative(oper_node->left);
    new_node->right->left = copy_node(oper_node->left);
    new_node->right->right = take_derivative(oper_node->right);
    return new_node;
}

static Node* get_derivative_div(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens div_tok = DIVISION, sub_tok = SUBTRACT, mul_tok = MULTIPLY, pow_tok = POWER;
    Node* new_node = make_node(OPER_TYPE, &div_tok);
    Node* left_node = make_node(OPER_TYPE, &sub_tok);
    left_node->left = make_node(OPER_TYPE, &mul_tok);
    left_node->right = make_node(OPER_TYPE, &mul_tok);
    left_node->left->right = copy_node(oper_node->right);
    left_node->left->left = take_derivative(oper_node->left);
    left_node->right->left = copy_node(oper_node->left);
    left_node->right->right = take_derivative(oper_node->right);
    new_node->left = copy_node(left_node);
    Node* right_node = make_node(OPER_TYPE, &pow_tok);
    right_node->left = copy_node(oper_node->right);
    right_node->right = make_node(VALUE_TYPE, &TWO);
    new_node->right = copy_node(right_node);

    return new_node;
}

static Node* get_derivative_pow(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, ln_tok = LN;
    Node* new_node = make_node(OPER_TYPE, &mul_tok);
    new_node->left = copy_node(oper_node);
    Node* buffer_node = make_node(OPER_TYPE, &mul_tok);
    buffer_node->left = copy_node(oper_node->right);
    buffer_node->right = make_node(OPER_TYPE, &ln_tok);
    buffer_node->right->left = make_node(VALUE_TYPE, &M_ONE);
    buffer_node->right->right = copy_node(oper_node->left);
    new_node->right = get_derivative_mul(buffer_node);

    return new_node;
}

static Node* get_derivative_cos(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, sin_tok = SIN;
    Node* new_node = make_node(OPER_TYPE, &mul_tok);
    new_node->right = take_derivative(oper_node->right);
    Node* left_node = make_node(OPER_TYPE, &mul_tok);
    left_node->left = make_node(VALUE_TYPE, &M_ONE);
    left_node->right = make_node(OPER_TYPE, &sin_tok);
    left_node->right->left = make_node(VALUE_TYPE, &M_ONE);
    left_node->right->right = copy_node(oper_node->right);
    new_node->left = copy_node(left_node);

    return new_node;
}

static Node* get_derivative_sin(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, cos_tok = COS;
    Node* new_node = make_node(OPER_TYPE, &mul_tok);
    new_node->left = make_node(OPER_TYPE, &cos_tok);
    new_node->left->left = make_node(VALUE_TYPE, &M_ONE);
    new_node->left->right = copy_node(oper_node->right);
    new_node->right = take_derivative(oper_node->right);

    return new_node;
}

static Node* get_derivative_tan(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, cos_tok = SIN, div_tok = DIVISION, pow_tok = POWER;
    Node* new_node = make_node(OPER_TYPE, &mul_tok);
    new_node->right = take_derivative(oper_node->right);
    new_node->left = make_node(OPER_TYPE, &div_tok);
    new_node->left->left = make_node(VALUE_TYPE, &ONE);
    new_node->left->right = make_node(OPER_TYPE, &pow_tok);
    new_node->left->right->right = make_node(VALUE_TYPE, &TWO);
    new_node->left->right->left = make_node(OPER_TYPE, &cos_tok);
    new_node->left->right->left->left = make_node(VALUE_TYPE, &M_ONE);
    new_node->left->right->left->right = copy_node(oper_node->right);

    return new_node;
}

static Node* get_derivative_ctan(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, sin_tok = SIN, div_tok = DIVISION, pow_tok = POWER;
    Node* new_node = make_node(OPER_TYPE, &mul_tok);
    new_node->right = take_derivative(oper_node->right);
    new_node->left = make_node(OPER_TYPE, &mul_tok);
    new_node->left->left = make_node(VALUE_TYPE, &M_ONE);
    Node* buffer_node = make_node(OPER_TYPE, &div_tok);
    buffer_node->left = make_node(VALUE_TYPE, &ONE);
    buffer_node->right = make_node(OPER_TYPE, &pow_tok);
    buffer_node->right->right = make_node(VALUE_TYPE, &TWO);
    buffer_node->right->left = make_node(OPER_TYPE, &sin_tok);
    buffer_node->right->left->left = make_node(VALUE_TYPE, &M_ONE);
    buffer_node->right->left->right = copy_node(oper_node->right);
    new_node = buffer_node;

    return new_node;
}

static Node* get_derivative_ln(Node* oper_node)
{
    assert(oper_node != nullptr);

    Tokens mul_tok = MULTIPLY, div_tok = DIVISION;
    Node* new_node = make_node(OPER_TYPE, &mul_tok);
    new_node->left = make_node(OPER_TYPE, &div_tok);
    new_node->left->left = make_node(VALUE_TYPE, &ONE);
    new_node->left->right = copy_node(oper_node->right);
    new_node->right = take_derivative(oper_node->right);

    return new_node;
}

static Node* take_derivative(Node* handled_node)
{
    assert(handled_node != nullptr);

    if (NODE_IS_VALUE(handled_node))
    {
        return make_node(VALUE_TYPE, &ZERO);
    }
    if (NODE_IS_VARIABLE(handled_node))
    {
        return make_node(VALUE_TYPE, &ONE);
    }

    return evaluate(handled_node);
}

static Tree* take_tree_of_derivative(Tree* handled_tree)
{
    assert(handled_tree != nullptr);

    handled_tree->root = take_derivative(handled_tree->root);
    handled_tree->size = handled_tree->size;
    return handled_tree;
}
