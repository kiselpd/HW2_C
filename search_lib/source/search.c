#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

int compare(const void* first, const void* second)
{
    const file_t* first_file = (const file_t*)first;
    const file_t* second_file = (const file_t*)second;

    return second_file->count_search - first_file->count_search;
}

int found_string(char* string, char* find_string)
{
    int count_found_string = 0;
    char* ptr_string = string;

    if (!(string && find_string))
    {
        ptr_string = NULL;
        return INPUT_ERROR;
    }

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

int start_search(char* directory, DIR* dir, char* find_string, file_t files[])
{
    struct dirent* ent;
    size_t count_found = 0;
    int len_directory = strlen(directory);
    int count_files = 0;

    if (!(directory && find_string && files))
    {
        return INPUT_ERROR;
    }
    if (!dir)
    {
        return DIR_NOT_FOUND;
    }

    while ((ent = readdir(dir)) != EXIT)
    {
        if ((strcmp(ent->d_name, ".")) && (strcmp(ent->d_name, "..")))
        {
            strcat(directory, "/");
            strcat(directory, ent->d_name);
            FILE* file = fopen(directory, "r");
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
            } while (len != INPUT_ERROR);
            if (count_found != 0)
            {
                files[count_files].file_name = ent->d_name;
                files[count_files].count_search = count_found;
                count_files++;
            }
            count_found = 0;
            directory[len_directory] = '\0';

            free(str);
            fclose(file);
        }
    }
    return count_files;
}

int sequential_search_top(char* str_dir, char* find_str, file_t files[])
{
    int result = EXIT;
    DIR* dir = opendir(str_dir);

    if (!(str_dir && find_str && files))
    {
        closedir(dir);
        return INPUT_ERROR;
    }

    if (!dir)
    {
        closedir(dir);
        return DIR_NOT_FOUND;
    }

    result = start_search(str_dir, dir, find_str, files);


    if (result == 0)
    {
        closedir(dir);
        return STR_NOT_FOUND;
    }

    qsort(files, result, sizeof(file_t), compare);

    closedir(dir);

    return result;
}