#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

enum Error
{
    STR_NOT_FOUND = -3,
    DIR_NOT_FOUND,
    INPUT_ERROR,
    EXIT,
    TOP5 = 5
};

typedef struct File_t
{
    char* file_name;
    size_t count_search;
}file_t;

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

int compare(const void* first, const void* second)
{
    const file_t* first_file = (const file_t*)first;
    const file_t* second_file = (const file_t*)second;

    return second_file->count_search - first_file->count_search;
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

    return EXIT;
}

void show_error(int error)
{
    switch (error)
    {
    case STR_NOT_FOUND:
        printf("This string was not found in the files!\n");
        break;
    case DIR_NOT_FOUND:
        printf("Directory not found!\n");
        break;
    case INPUT_ERROR:
        printf("\nInput error!\n");
        break;
    case EXIT:
        break;
    default:
        printf("\nUnknown error!\n");
        break;
    }
}

void show_top(file_t files, int count)
{
    if (count < TOP5)
    {
        printf("\n");
        for (size_t i = 0; i < count; i++)
        {
            printf("%ld.%s -> %ld\n", i + 1, files[i].file_name, files[i].count_search);
        }
    }
    else
    {
        printf("\n");
        for (size_t i = 0; i < TOP5; i++)
        {
            printf("%ld.%s -> %ld\n", i + 1, files[i].file_name, files[i].count_search);
        }
    }
}


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
