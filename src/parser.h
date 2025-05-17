#ifndef PARSER_H
#define PARSER_H

#include "stdio.h"
#include "list.h"
#include "tree.h"
#include "text_color.h"

Tree* parse(List* token_list);

#endif // PARSER_H
