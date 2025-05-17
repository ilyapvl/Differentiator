#include <string.h>
#include <assert.h>
#include "graph.h"
#include "tree.h"

static const int MAX_DIR_LEN = 100;
static const char* FILE_REPOSITORY = "./data/";

void draw_graph(Tree* cur_tree, const char* file_name)
{
    char full_file_name[MAX_DIR_LEN] = {};
    strcpy(full_file_name, FILE_REPOSITORY);
    strcat(full_file_name, file_name);
    FILE* fp = fopen(full_file_name, "w");
    assert(fp != NULL);

    fprintf(fp, "digraph G {\
                \n  tree [shape=box ; stryle=rounded ; label=\"size : %d\"];\
                \n  edge [color=black];\
                \n  node [shape=record ; style=rounded ; color=green];\n", cur_tree->size);

    print_node_in_graph(fp, cur_tree->root);
    print_edge_in_graph(fp, cur_tree->root);

    fprintf(fp, "}");
    fclose(fp);
}

void print_node_in_graph(FILE* fp, Node* cur_node)
{
    if (!cur_node->left && !cur_node->right)
    {
        fprintf(fp, "%lld [label=\"{%s}\"];\n", (long long int)cur_node, take_str_from_node(cur_node));
        return;
    }
    fprintf(fp, "%lld [label=\"{%s|{<LEFT>LEFT|<RIGHT>RIGHT}}\"];\n", (long long int)cur_node, take_str_from_node(cur_node));
    if (cur_node->left)
        print_node_in_graph(fp, cur_node->left);
    if (cur_node->right)
        print_node_in_graph(fp, cur_node->right);
}

void print_edge_in_graph(FILE* fp, Node* cur_node)
{
    if (cur_node->left)
    {
        fprintf(fp, "%lld:<LEFT> -> %lld [color=green];\n", (long long int)cur_node, (long long int)cur_node->left);
        print_edge_in_graph(fp, cur_node->left);
    }
    if (cur_node->right)
    {
        fprintf(fp, "%lld:<RIGHT> -> %lld [color=red];\n", (long long int)cur_node, (long long int)cur_node->right);
        print_edge_in_graph(fp, cur_node->right);
    }
}
