#include "shell.h"

/**
 * getHistoryFile - Retrieves the history file path.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *getHistoryFile(info_t *info)
{
    char *buf, *dir;

    dir = getEnvironmentVariable(info, "HOME=");
    if (!dir)
        return (NULL);

    buf = malloc(sizeof(char) * (stringLength(dir) + stringLength(HISTORY_FILE) + 2));
    if (!buf)
        return (NULL);

    buf[0] = 0;
    stringCopy(buf, dir);
    stringConcat(buf, "/");
    stringConcat(buf, HISTORY_FILE);

    return (buf);
}

/**
 * writeHistory - Creates or appends to a history file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int writeHistory(info_t *info)
{
    ssize_t fd;
    char *filename = getHistoryFile(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        printToFD(node->str, fd);
        printToFD('\n', fd);
    }

    printToFD(BUF_FLUSH, fd);
    close(fd);

    return (1);
}

/**
 * readHistory - Reads history from a file.
 * @info: Parameter struct.
 *
 * Return: Number of history entries read on success, 0 on failure.
 */
int readHistory(info_t *info)
{
    int i, last = 0, lineCount = 0;
    ssize_t fd, readLen, fileSize = 0;
    struct stat st;
    char *buf = NULL, *filename = getHistoryFile(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fileSize = st.st_size;

    if (fileSize < 2)
        return (0);

    buf = malloc(sizeof(char) * (fileSize + 1));

    if (!buf)
        return (0);

    readLen = read(fd, buf, fileSize);
    buf[fileSize] = 0;

    if (readLen <= 0)
        return (free(buf), 0);

    close(fd);

    for (i = 0; i < fileSize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            buildHistoryList(info, buf + last, lineCount++);
            last = i + 1;
        }
    }

    if (last != i)
        buildHistoryList(info, buf + last, lineCount++);

    free(buf);
    info->histCount = lineCount;

    while (info->histCount-- >= HISTORY_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);
    return (info->histCount);
}

/**
 * buildHistoryList - Adds an entry to a history linked list.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @lineCount: History line count.
 *
 * Return: Always 0.
 */
int buildHistoryList(info_t *info, char *buf, int lineCount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, lineCount);

    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new history count.
 */
int renumberHistory(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histCount = i);
}

