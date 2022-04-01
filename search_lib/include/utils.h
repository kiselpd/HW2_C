#ifndef UTILS_H
#define UTILS_H

#include <dirent.h>

typedef enum error_t
{
    PID_ERROR = -6,
    MALLOC_ERROR = -5,
    MAP_ERROR = -4,
    STR_NOT_FOUND = -3,
    DIR_NOT_FOUND = -2,
    INPUT_ERROR = -1
}error_t;

typedef enum value_t
{
    EXIT = 0,
    TOP5 = 5
}value_t;

typedef enum mode_t
{
    SEQUENTIAL = 0,
    PARALLEL = 1
}value_t;

typedef struct directory_t
{
    char* dir_name;
    DIR* dir;
}dir_t;

typedef struct file_t
{
    char* file_name;
    size_t count_search;
}file_t;

int get_dir_t(dir_t* ptr_dir);

char* get_find_str(char* find_str);

#endif