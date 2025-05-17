#include "differentiator.h"
#include "file.h"
#include "list.h"
#include "parser.h"
#include "lex_analysis.h"
#include "graph.h"
#include "latex.h"

const char* graph_file_name = "tree_graph.dot";
int main(const int argc, const char *argv[])
{
    int derivative_order = 0;
    const char* file_name = argv[1];
    file_validation(file_name);
    char* str = handle_file(file_name);
    if (argc == 3) sscanf(argv[2], "%d", &derivative_order);
    else
    {
        fprintf(stderr, "Number of derivative: ");
        scanf("%d", &derivative_order);
    }

    FILE* tex = make_tex();

    if (tex == nullptr)
    {
        fprintf(stderr, "Error while opening tex file\n");
        return -1;
    }

    List* token_list = lexical_analysis(str);

    token_list = reverse_list(token_list);

    Tree* token_tree = parse(token_list);

    draw_graph(token_tree, graph_file_name);

    take_n_derivatives(token_tree, derivative_order, tex);

    finish_tex_file(tex);
    fprintf(stderr, "SUCCESS\n");

    return 0;
}

