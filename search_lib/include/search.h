#ifndef SEARCH_H
#define SEARCH_H

#include <dirent.h>
#include "utils.h"

int compare(const void* first, const void* second);

int found_string(char* string, char* find_string);

int sequential_search(dir_t curr_dir, char* find_string, file_t files[]);

int parallel_search(dir_t curr_dir, char* find_string, file_t files[]);

int search_top(dir_t curr_dir, char* find_str, file_t files[], int mode);



#endif