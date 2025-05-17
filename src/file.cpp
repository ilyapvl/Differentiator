#include <stdlib.h>
#include <string.h>
#include "differentiator.h"
#include "file.h"
#include "str_functions.h"

static const int DIR_MAX_NAME_LEN = 100;
static const char* DIRECTORY_NAME = "./data/";

char* read_file(const char* file_name, size_t* symbols_num)
{
    char dirf[DIR_MAX_NAME_LEN] = {};
    strcpy(dirf, DIRECTORY_NAME);
    strncat (dirf, file_name, DIR_MAX_NAME_LEN);
    FILE *fp = fopen(dirf, "rb");

    *(symbols_num) = find_file_size(fp);

    char* text_from_file = (char*) calloc(*symbols_num + 1, sizeof(char));
    fread(text_from_file, sizeof(char), *symbols_num, fp);

    fclose(fp);

    return text_from_file;
}

void file_validation(const char* file_name)
{
    char dirf[DIR_MAX_NAME_LEN] = {};
    strcpy(dirf, DIRECTORY_NAME);
    strncat (dirf, file_name, DIR_MAX_NAME_LEN);
    FILE* fp = fopen(dirf, "r");
    if (!fp)
    {
        fprintf(stderr, red(File doesn`t exist!)"\n");
        fclose(fp);
        exit(1);
    }
    if (find_file_size(fp) < 2)
    {
        fprintf(stderr, red(File is empty!)"\n");
        fclose(fp);
        exit(1);
    }
    fclose(fp);
}

size_t find_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    size_t n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return n;
}

char* handle_file(const char* file_name)
{
    size_t num_of_symbols = 0;
    char* str = read_file(file_name, &num_of_symbols);
    num_of_symbols -= len_without_slash_n(str);
    str = replace_spaces(str, num_of_symbols);
    return str;
}
