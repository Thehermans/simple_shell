#include "shell.h"

/**
 * initializeInfo - Initializes an info_t struct.
 * @info: Pointer to the struct to be initialized.
 */
void initializeInfo(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * populateInfo - Populates an info_t struct with values.
 * @info: Pointer to the struct to be populated.
 * @av: Argument vector.
 */
void populateInfo(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];

    if (info->arg)
    {
        info->argv = splitString(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = duplicateString(info->arg);
                info->argv[1] = NULL;
            }
        }

        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replaceAliases(info);
        replaceVariables(info);
    }
}

/**
 * deallocateInfo - Deallocates memory associated with an info_t struct.
 * @info: Pointer to the struct to be deallocated.
 * @all: True if all fields should be deallocated.
 */
void deallocateInfo(info_t *info, int all)
{
    freeStringArray(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);

        if (info->env)
            freeLinkedList(&(info->env));

        if (info->history)
            freeLinkedList(&(info->history));

        if (info->alias)
            freeLinkedList(&(info->alias));

        freeStringArray(info->environ);
        info->environ = NULL;

        deallocateBuffer((void **)info->cmd_buf);

        if (info->readfd > 2)
            close(info->readfd);

        flushBuffer();
    }
}

