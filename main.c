#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "search.h"
#include "show.h"

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
        
    find_str = get_find_str(find_str);
    if (find_str == NULL)
    {
        result = INPUT_ERROR;
        show_error(result);
        return 0;
    }

    result = sequential_search_top(curr_dir, find_str, files);

    if ((result == INPUT_ERROR) || (result == DIR_NOT_FOUND) || (result == STR_NOT_FOUND))
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
