#ifndef LATEX_H
#define LATEX_H

#include <stdio.h>
#include "tree.h"

struct tex_string {
    char str[1000]; // FIXME calloc(1000, sizeof(char)); понять, почему при использовании calloc переполнение стека
};

void add_to_tex_file(char* der_str, FILE* tex);
void handle_operation(Node* cur_node, char* str);
tex_string get_expr(Node* handled_node);
void finish_tex_file(FILE* tex);
FILE* make_tex();

#endif // LATEX_H
