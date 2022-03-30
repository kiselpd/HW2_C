#ifndef SEARCH_H
#define SEARCH_H

#include <dirent.h>
#include "utils.h"

int compare(const void* first, const void* second);

int found_string(char* string, char* find_string);

int start_search(char* directory, DIR* dir, char* find_string, file_t files[]);

int sequential_search_top(char* str_dir, char* find_str, file_t files[]);



#endif