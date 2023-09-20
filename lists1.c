#include "shell.h"

/**
 * getLinkedListLength - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t getLinkedListLength(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * convertListToStrings - Returns an array of strings containing list->str values.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **convertListToStrings(list_t *head)
{
    list_t *node = head;
    size_t i = getLinkedListLength(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        strcpy(str, node->str);
        strs[i] = str;
    }

    strs[i] = NULL;
    return (strs);
}

/**
 * printLinkedList - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t printLinkedList(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(convertNumber(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * findNodeWithPrefix - Returns the node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *findNodeWithPrefix(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = startsWith(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }

    return (NULL);
}

/**
 * getNodeIndex - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1.
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }

    return (-1);
}

