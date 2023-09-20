#include "shell.h"

/**
 * isExecutable - Checks if a file is an executable command
 * @info: Pointer to the info struct
 * @path: Path to the file
 *
 * Return: 1 if it's an executable, 0 otherwise
 */
int isExecutable(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st) != 0)
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicateChars - Duplicates characters from a string
 * @pathstr: The input PATH string
 * @start: The starting index
 * @stop: The stopping index
 *
 * Return: Pointer to a new buffer
 */
char *duplicateChars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
    {
        if (pathstr[i] != ':')
        {
            buf[k++] = pathstr[i];
        }
    }
    buf[k] = 0;
    return buf;
}

/**
 * findCommandPath - Finds the full path of a command in the PATH string
 * @info: Pointer to the info struct
 * @pathstr: The PATH string
 * @cmd: The command to find
 *
 * Return: The full path of cmd if found, otherwise NULL
 */
char *findCommandPath(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
    {
        return NULL;
    }
    if ((_strlen(cmd) > 2) && startsWith(cmd, "./"))
    {
        if (isExecutable(info, cmd))
        {
            return cmd;
        }
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = duplicateChars(pathstr, curr_pos, i);
            if (!*path)
            {
                _strcat(path, cmd);
            }
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (isExecutable(info, path))
            {
                return path;
            }
            if (!pathstr[i])
            {
                break;
            }
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}

