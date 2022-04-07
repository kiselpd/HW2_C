#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "search.h"
#include "utils.h"


int compare(const void* first, const void* second)
{
    const file_t* first_file = (const file_t*)first;
    const file_t* second_file = (const file_t*)second;

    return second_file->count_search - first_file->count_search;
}

int found_string(char* string, char* find_string)
{
    if (!(string && find_string))
    {
        return INPUT_ERROR;
    }

    int count_found_string = 0;
    char* ptr_string = string;

    while (ptr_string && ptr_string < (ptr_string + strlen(ptr_string)))
    {
        ptr_string = strstr(ptr_string, find_string);
        if (ptr_string)
        {
            ptr_string += strlen(find_string);
            count_found_string++;
        }
    }
    ptr_string = NULL;

    return count_found_string;
}

int sequential_search(dir_t curr_dir, char* find_string, file_t files[])
{
    if (!(curr_dir.dir_name && find_string && files))
    {
        return INPUT_ERROR;
    }
    if (!curr_dir.dir)
    {
        return DIR_NOT_FOUND;
    }

    struct dirent* ent;
    size_t count_found = 0;
    int count_files = 0;
    int len_curr_dir = strlen(curr_dir.dir_name);

    while ((ent = readdir(curr_dir.dir)) != EXIT)
    {
        if ((strcmp(ent->d_name, ".")) && (strcmp(ent->d_name, "..")))
        {
            strcat(curr_dir.dir_name, "/");
            strcat(curr_dir.dir_name, ent->d_name);
            FILE* file = fopen(curr_dir.dir_name, "r");
            if (!file)
            {
                continue;
            }

            int len = 0;
            size_t count = 0;
            char* str = NULL;
            do
            {
                len = getline(&str, &count, file);
                if (len != INPUT_ERROR)
                {
                    if (str[strlen(str) - 1] == '\n')
                    {
                        str[strlen(str) - 1] = '\0';
                    }
                    else
                    {
                        str[strlen(str)] = '\0';
                    }
                    count_found += found_string(str, find_string);
                }
                count = 0;
                free(str);
            } while (len != INPUT_ERROR);
            if (count_found != 0)
            {
                files[count_files].file_name = ent->d_name;
                files[count_files].count_search = count_found;
                count_files++;
            }
            count_found = 0;
            curr_dir.dir_name[len_curr_dir] = '\0';

            fclose(file);
        }
    }
    return count_files;
}

int search_top(dir_t curr_dir, char* find_str, file_t files[])
{
    if (!(curr_dir.dir_name && find_str && files))
    {
        return INPUT_ERROR;
    }

    if (!curr_dir.dir)
    {
        return DIR_NOT_FOUND;
    }

    int result = EXIT;

    result = sequential_search(curr_dir, find_str, files);

    if (result == 0)
    {
        return STR_NOT_FOUND;
    }

    qsort(files, result, sizeof(file_t), compare);

    return result;
}