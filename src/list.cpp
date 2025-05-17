#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

List* make_list(int length)
{
    
    List* new_list = (List*) calloc(1, sizeof(List));
    new_list->capacity = length;
    new_list->size = 0;
    new_list->data = (TYPE_LIST*) calloc(length, sizeof(TYPE_LIST));

    return new_list;
}

void list_realloc(List* list, int new_capacity)
{
    list->data = (TYPE_LIST*) realloc(list->data, new_capacity * sizeof(TYPE_LIST));

    memset(list->data + list->capacity, 0, (new_capacity - list->capacity) * sizeof (TYPE_LIST));

    list->capacity = new_capacity;
}

void append_to_list(List* list, TYPE_LIST value)
{
    if (list->size == list->capacity)
    {
        list_realloc(list, list->capacity * 2);
    }
    list->data[list->size] = value;
    list->size++;
}

void insert_into_list(List* list, TYPE_LIST value, int index)
{
    list->size++;
    if (list->size == list->capacity)
    {
        list_realloc(list, list->capacity * 2);
    }

    TYPE_LIST buffer = 0;
    for (int i = index + 1; i < list->size; i++)
    {
        buffer = list->data[i];
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
}

void remove_from_list(List* list, int index)
{
    list->size--;
    for (int i = index; i < list->size; i++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->data[list->size] = NULL;

    if (list->size < list->capacity / 3)
    {
        list_realloc(list, list->capacity / 3);
    }
}

void destruct_list(List* list)
{
    for (int i = 0; i < list->size; i++)
        delete_node(list->data[i]);

    free(list->data);
    free(list);
}

void print_list(List* list)
{
    for (int i = 0; i < list->size; i++)
    {
        fprintf(stdout, "%.2lf ", list->data[i]->content.value);
    }
    fprintf(stdout, "\n");
}

List* cut_from_list(List* copied_list, int start_i, int finish_i)
{
    List* new_list = make_list((finish_i - start_i) * 2);
    for (int i = start_i; i <= finish_i; i++)
    {
        append_to_list(new_list, copied_list->data[start_i]);
        remove_from_list(copied_list, start_i);
    }
    return new_list;
}

List* reverse_list(List* list)
{
    List* new_list = make_list(list->capacity);
    for (int i = 0; i< list->size; i++)
    {
        append_to_list(new_list, list->data[list->size - 1 - i]);
    }

    return new_list;
}
