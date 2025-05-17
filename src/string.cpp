#include <stdlib.h>
#include <string.h>
#include "differentiator.h"

char* replace_spaces(char *orig, int size)
{
    char* result;
    char* new_str = result = (char*) calloc(size + 1, sizeof(char));
    char* insert_point;
    int n = 0;

    while ((insert_point = strchr(orig, ' ')))
    {
        n = insert_point - orig;
        new_str = strncpy(new_str, orig, n) + n;
        orig = orig + n + 1;
    }

    strcpy(new_str, orig);
    return result;
}

int len_without_slash_n(char* str)
{
    int char_difference = 0;
    char* slash_n = strchr(str, '\n');
    if (slash_n != NULL)
    {
        *(slash_n) = '\0';
        char_difference += 1;
    }
    return char_difference;
}


