#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "my_string.h"

#define SUCCESS 0
#define ARG_ERROR -2

#define COUNT_ARG 7

FILE *file_in = NULL;
FILE *file_out = NULL;

char *source = NULL;
char *result = NULL;

/*
 * comment
 */

int all_fopen(char **argv)
{
    file_in = NULL;
    file_out = NULL;

    file_in = fopen(argv[1], "r");
    file_out = fopen(argv[2], "w");

    if (file_in == NULL || file_out == NULL)
        return errno;

    return SUCCESS;
}

int all_fclose(void)
{
    if (file_in != NULL)
        fclose(file_in);
    
    if (file_out != NULL)
        fclose(file_out);

    if (errno != SUCCESS)
        return errno;

    return SUCCESS;
}

void all_free(void)
{
    free_string(source);
    free_string(result);
}

int return_error(int error)
{
    all_fclose();
    all_free();

    switch (error)
    {
        case SUCCESS:
            return SUCCESS;
        case ARG_ERROR:
            fprintf(stderr, "%s\n", "Incorrect arguments");
            return ARG_ERROR;
        case GETLINE_ERROR:
            fprintf(stderr, "%s\n", "Getline error");
            return GETLINE_ERROR;
        default:
            fprintf(stderr, "%s\n", strerror(errno));
            return errno;
    }
}

int replace_in_file(char **argv)
{
    size_t n = 0;

    char *search = argv[4];
    char *replace = argv[6];

    while (my_getline(&source, &n, file_in) != GETLINE_ERROR)
    {
        result = str_replace(source, search, replace);
        fprintf(file_out, "%s\n", result);
        free_string(result);
        free_string(source);
    }

    if (result == NULL)
        return GETLINE_ERROR;

    return SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc != COUNT_ARG)
        return return_error(ARG_ERROR);

    int code_error = SUCCESS;

    if ((code_error = all_fopen(argv)) != SUCCESS)
        return return_error(code_error);

    if ((code_error = replace_in_file(argv)) != SUCCESS)
        return return_error(code_error);

    return return_error(SUCCESS);
}

