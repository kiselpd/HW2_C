#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "search.h"
#include "show.h"

int main()
{
    int result = EXIT;
    int mode = 0;
    file_t files[500]; 
    dir_t curr_dir;
    char* find_str = NULL;
    result = get_dir_t(&curr_dir);
    if (result != EXIT)
    {
        show_error(result);
        return 0;
    }
        
    find_str = get_find_str(find_str);
    if (find_str == NULL)
    {
        result = INPUT_ERROR;
        show_error(result);
        closedir(curr_dir.dir);
        free(curr_dir.dir_name);
        return 0;
    }

    printf("Input mode 0/1:");         //0-
    scanf("%d", &mode);


    result = search_top(curr_dir, find_str, files, mode);
    

    if ((result == INPUT_ERROR) || (result == DIR_NOT_FOUND) || (result == STR_NOT_FOUND) || (result == MAP_ERROR) || (result == MALLOC_ERROR))
    {
        show_error(result);
    }
    else
    {
        show_top(files, result);
    }

    free(find_str);
    find_str = NULL;
    closedir(curr_dir.dir);
    free(curr_dir.dir_name);
	return 0;
}
