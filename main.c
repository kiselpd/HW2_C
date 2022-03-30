#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "search.h"
#include "show.h"



int main()
{
    int result = EXIT;
    file_t files[500];
    int len_dir = 0;
    size_t count_dir = 0;
    char* str_dir = NULL;
    int len_find_str = 0;
    size_t count_find_str = 0;
    char* find_str = NULL;

    printf("Enter the name of directory: ");
    len_dir = getline(&str_dir, &count_dir, stdin);
    if (len_dir == INPUT_ERROR)
    {
        result = INPUT_ERROR;
    }
    if (str_dir[strlen(str_dir) - 1] == '\n')
    {
        str_dir[strlen(str_dir) - 1] = '\0';
    }

    printf("Enter the string: ");
    len_find_str = getline(&find_str, &count_find_str, stdin);
    if (len_find_str == INPUT_ERROR)
    {
        result = INPUT_ERROR;
    }
    if (find_str[strlen(find_str) - 1] == '\n')
    {
        find_str[strlen(find_str) - 1] = '\0';
    }
        
    if (result != INPUT_ERROR)
    {
        result = sequential_search_top(str_dir, find_str, files);
    }

    free(str_dir);
    str_dir = NULL;
    free(find_str);
    find_str = NULL;

    if ((result == INPUT_ERROR) || (result == DIR_NOT_FOUND) || (result == STR_NOT_FOUND))
    {
        show_error(result);
    }
    else
    {
        show_top(files, result);
    }
	return 0;
}
