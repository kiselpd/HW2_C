#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "search.h"

int main()
{
    int result = EXIT;
    file_t files[500];
    dir_t curr_dir;
    char* find_str = NULL;

    result = get_dir_t(&curr_dir);
    if (result == INPUT_ERROR)
    {
        show_error(result);
        return 0;
    }
    if (result == DIR_NOT_FOUND)
    {
        free(curr_dir.dir_name);
        show_error(result);
        return 0;
    }
        
    find_str = get_find_str(find_str);
    if (find_str == NULL)
    {
        result = INPUT_ERROR;
        free(curr_dir.dir_name);
        closedir(curr_dir.dir);
        show_error(result);
        return 0;
    }

    result = search_top(curr_dir, find_str, files);

    if ((result == INPUT_ERROR) || (result == DIR_NOT_FOUND) || (result == STR_NOT_FOUND) || (result == MODE_ERROR) || (result == PID_ERROR) || (result == MALLOC_ERROR) || (result == MAP_ERROR))
    {
        show_error(result);
    }
    else
    {
        show_top(files, result);
    }

    free(find_str);
    find_str = NULL;
    free(curr_dir.dir_name);
    closedir(curr_dir.dir);
	return 0;
}
