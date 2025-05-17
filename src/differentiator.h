#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <stdio.h>

#include "text_color.h"
#include "list.h"
#include "tree.h"

void take_n_derivatives(Tree* token_tree, int derivative_qty, FILE* tex);

#endif // DIFFERENTIATOR_H
