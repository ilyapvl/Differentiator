#ifndef LIST_H
#define LIST_H
#include "tree.h"

#define TYPE_LIST Node*

const int LIST_LEN = 10;

typedef struct {
    TYPE_LIST* data;
    int capacity;
    int size;
} List;

List* make_list(int length);
void list_realloc(List* list, int new_capacity);
void append_to_list(List* list, TYPE_LIST value);
void insert_into_list(List* list, TYPE_LIST value, int index);
void destruct_list(List* list);
void print_list(List* list);

List* cut_from_list(List* copied_list, int start_i, int finish_i);
void remove_from_list(List* list, int index);
List* reverse_list(List* list);


#endif
