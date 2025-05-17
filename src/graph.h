#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include "tree.h"

void print_node_in_graph(FILE* fp, Node* cur_node);
void print_edge_in_graph(FILE* fp, Node* cur_node);
void draw_graph(Tree* cur_tree, const char* file_name);

#endif // GRAPH_H
