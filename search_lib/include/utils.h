#ifndef UTILS_H
#define UTILS_H

enum Error
{
    STR_NOT_FOUND = -3,
    DIR_NOT_FOUND = -2,
    INPUT_ERROR = -1
};

enum Value
{
    EXIT = 0,
    TOP5 = 5
};

typedef struct File_t
{
    char* file_name;
    size_t count_search;
}file_t;

#endif