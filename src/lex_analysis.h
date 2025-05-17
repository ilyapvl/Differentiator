#ifndef LEX_ANALYSIS_H
#define LEX_ANALYSIS_H
#include "tree.h"
#include "list.h"
List* lexical_analysis(char* str);
Node* encode(char* str, int* idx);
double get_value(char* str, int* idx);
Node* check_func(char* str, int* idx);


#endif // LEX_ANALYSIS_H
