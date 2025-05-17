#ifndef TREE_H
#define TREE_H

enum Tokens
{
    LEFT_BR,
    RIGHT_BR,
    POWER,
    MULTIPLY,
    DIVISION,
    ADD,
    SUBTRACT,
    COS,
    SIN,
    TAN,
    CTAN,
    LN,
    UNKNOWN
};

union node_data {
    double value;
    enum Tokens token;
    char variable;
};

enum Brackets_status
{
    NOT_IN_BRACKETS,
    IN_BRACKETS
};

typedef struct node {
    union node_data content;
    int type;
    int status = NOT_IN_BRACKETS;
    node* left;
    node* right;
    node* prev;
} Node;

typedef struct tree {
    Node* root;
    int size;
} Tree;

Node* make_node(int type, void* content);
Tree* make_tree();
Node* append_to_tree(Tree* tree, Node* new_node, Node* current_node, int indicator);
void delete_node(Node* deleted_node);
void destruct_tree(Tree* deleted_tree);
char* decode_operation(Node* cur_node);
char* take_str_from_node(Node* cur_node);
Node* copy_node(Node* copied_node);

enum Node_type
{
    OPER_TYPE,
    VALUE_TYPE,
    VARIABLE_TYPE
};

enum Tree_indicators
{
    LEFT  = -1,
    PREV  =  0,
    RIGHT =  1
};

#define IS_OPEN_BRACKETS    (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == RIGHT_BR)
#define IS_CLOSE_BRACKETS   (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == LEFT_BR)
#define IS_PLUS             (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == ADD)
#define IS_MINUS            (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == SUBTRACT)
#define IS_MULTIPLY         (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == MULTIPLY)
#define IS_DIVISION         (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == DIVISION)
#define IS_POWER            (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == POWER)
#define IS_COS              (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == COS)
#define IS_SIN              (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == SIN)
#define IS_TAN              (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == TAN)
#define IS_CTAN             (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == CTAN)
#define IS_LN               (token_list->data[*idx]->type == OPER_TYPE && token_list->data[*idx]->content.token == LN)
#define IS_VALUE            (token_list->data[*idx]->type == VALUE_TYPE)
#define IS_VARIABLE         (token_list->data[*idx]->type == VARIABLE_TYPE)
#define IS_FUNCTION         (IS_COS || IS_SIN || IS_TAN || IS_CTAN || IS_LN)

#define NOT_FOUND -1

#define NODE_IS_PLUS(NODE)             (NODE->type == OPER_TYPE && NODE->content.token == ADD)
#define NODE_IS_MINUS(NODE)            (NODE->type == OPER_TYPE && NODE->content.token == SUBTRACT)
#define NODE_IS_MULTIPLY(NODE)         (NODE->type == OPER_TYPE && NODE->content.token == MULTIPLY)
#define NODE_IS_DIVISION(NODE)         (NODE->type == OPER_TYPE && NODE->content.token == DIVISION)
#define NODE_IS_POWER(NODE)            (NODE->type == OPER_TYPE && NODE->content.token == POWER)
#define NODE_IS_COS(NODE)              (NODE->type == OPER_TYPE && NODE->content.token == COS)
#define NODE_IS_SIN(NODE)              (NODE->type == OPER_TYPE && NODE->content.token == SIN)
#define NODE_IS_TAN(NODE)              (NODE->type == OPER_TYPE && NODE->content.token == TAN)
#define NODE_IS_CTAN(NODE)             (NODE->type == OPER_TYPE && NODE->content.token == CTAN)
#define NODE_IS_LN(NODE)               (NODE->type == OPER_TYPE && NODE->content.token == LN)
#define NODE_IS_VALUE(NODE)            (NODE->type == VALUE_TYPE)
#define NODE_IS_VARIABLE(NODE)         (NODE->type == VARIABLE_TYPE)
#define NODE_IS_ZERO(NODE)             (NODE->type == VALUE_TYPE && cmp_with_number(NODE->content.value, (double)0))
#define NODE_IS_ONE(NODE)             (NODE->type == VALUE_TYPE && cmp_with_number(NODE->content.value, (double)1))

#endif // TREE_H
