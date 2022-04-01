#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int get_dir_t(dir_t* ptr_dir)
{
    int len_dir = 0;
    size_t count_dir = 0;
    char* str_dir = NULL;
    printf("Enter the name of directory: ");
    len_dir = getline(&str_dir, &count_dir, stdin);
    if (len_dir == INPUT_ERROR)
    {
        free(str_dir);
        str_dir = NULL;
        return INPUT_ERROR;
    }
    if (str_dir[strlen(str_dir) - 1] == '\n')
    {
        str_dir[strlen(str_dir) - 1] = '\0';
    }

    ptr_dir->dir_name = str_dir;
    ptr_dir->dir = opendir(str_dir);
    if (ptr_dir->dir == NULL)
    {
        free(str_dir);
        str_dir = NULL;
        return DIR_NOT_FOUND;
    }

    return EXIT;
}

char* get_find_str(char* find_str)
{
    int len_find_str = 0;
    size_t count_find_str = 0;
    printf("Enter the string: ");
    len_find_str = getline(&find_str, &count_find_str, stdin);
    if (len_find_str == INPUT_ERROR)
    {
        free(find_str);
        find_str = NULL;
        return NULL;
    }
    if (find_str[strlen(find_str) - 1] == '\n')
    {
        find_str[strlen(find_str) - 1] = '\0';
    }

    return find_str;
}