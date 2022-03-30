#include <stdio.h>
#include "show.h"

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

void show_top(file_t files[], int count)
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