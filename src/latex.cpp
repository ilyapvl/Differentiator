#include <string.h>

#include <assert.h>
#include "latex.h"

static const int MAX_LEN = 1000;

void add_to_tex_file(char* der_str, FILE* tex)
{
    assert(der_str != nullptr);

    fprintf(tex, "\n\\begin {equation}\n");
    fprintf(tex, "%s\n", der_str);
    fprintf(tex,"\\end {equation}\n\n");
}

tex_string get_expr(Node* handled_node)
{
    assert(handled_node != nullptr);

    tex_string str_copy;
    switch (handled_node->type)
    {
        case VALUE_TYPE:
        case VARIABLE_TYPE:
            strcpy(str_copy.str, take_str_from_node(handled_node));
            return str_copy;
        case OPER_TYPE:
            handle_operation(handled_node, str_copy.str);
    }
    return str_copy;
}

void handle_operation(Node* cur_node, char* str)
{
    switch (cur_node->content.token)
    {
        case ADD:
            snprintf(str, MAX_LEN, "%s + %s", get_expr(cur_node->left).str, get_expr(cur_node->right).str);
            break;
        case SUBTRACT:
            snprintf(str, MAX_LEN, "%s - %s", get_expr(cur_node->left).str, get_expr(cur_node->right).str);
            break;
        case MULTIPLY:
            snprintf(str, MAX_LEN, "%s * %s", get_expr(cur_node->left).str, get_expr(cur_node->right).str);
            break;
        case DIVISION:
            snprintf(str, MAX_LEN, "\\frac {%s} {%s}", get_expr(cur_node->left).str, get_expr(cur_node->right).str);
            break;
        case POWER:
            snprintf(str, MAX_LEN, "(%s) ^ {%s}", get_expr(cur_node->left).str, get_expr(cur_node->right).str);
            break;
        case COS:
            snprintf(str, MAX_LEN, "\\cos(%s)", get_expr(cur_node->right).str);
            break;
        case SIN:
            snprintf(str, MAX_LEN, "\\sin(%s)", get_expr(cur_node->right).str);
            break;
        case TAN:
            snprintf(str, MAX_LEN, "\\tan(%s)", get_expr(cur_node->right).str);
            break;
        case CTAN:
            snprintf(str, MAX_LEN, "\\cot(%s)", get_expr(cur_node->right).str);
            break;
        case LN:
            snprintf(str, MAX_LEN, "\\ln(%s)", get_expr(cur_node->right).str);
            break;
        default:
            snprintf(str, MAX_LEN, "%s", get_expr(cur_node).str);
    }
}

FILE* make_tex()
{
    char full_file_name[100] = "./data/";
    strcat(full_file_name, "result.tex");
    FILE* tex = fopen(full_file_name, "w");
    //if (!tex) return nullptr;

    fprintf(tex, "\\documentclass{article}\n\
\\usepackage{graphicx}\n\
\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n\
\\usepackage[fontsize=10pt]{fontsize}\n\
\\usepackage{graphicx}\n\
\\usepackage{float}\n\
\\usepackage{wrapfig}\n\
\\title{Differentiation}\n\
\\author{Ilya Pavlenko}\n\
\\date{May 2025}\n\
\\begin{document}\n\
\\maketitle\n\
\\section{Result}\n");

    return tex;
}

void finish_tex_file(FILE* tex)
{
    fprintf(tex, "\\end{document}\n");
    fclose(tex);
}
