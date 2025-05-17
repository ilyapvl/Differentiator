#ifndef FILE_H
#define FILE_H
#include <stdio.h>

char* handle_file(const char* file_name);
char* read_file(const char* file_name, size_t* symbols_num);
void file_validation(const char* file_name);
size_t find_file_size(FILE* fp);

#endif // FILE_H
