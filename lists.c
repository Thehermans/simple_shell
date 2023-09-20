#include "shell.h"

/**
 * addNode - Adds a node to the beginning of the list.
 * @head: Pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used for history.
 *
 * Return: Pointer to the new head node.
 */
list_t *addNode(list_t **head, const char *str, int num)
{
    list_t *newHead;

    if (!head)
        return (NULL);

    newHead = malloc(sizeof(list_t));
    if (!newHead)
        return (NULL);

    memset((void *)newHead, 0, sizeof(list_t));
    newHead->num = num;

    if (str)
    {
        newHead->str = strdup(str);
        if (!newHead->str)
        {
            free(newHead);
            return (NULL);
        }
    }

    newHead->next = *head;
    *head = newHead;

    return (newHead);
}

/**
 * addNodeEnd - Adds a node to the end of the list.
 * @head: Pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used for history.
 *
 * Return: Pointer to the new node.
 */
list_t *addNodeEnd(list_t **head, const char *str, int num)
{
    list_t *newNode, *node;

    if (!head)
        return (NULL);

    node = *head;
    newNode = malloc(sizeof(list_t));
    if (!newNode)
        return (NULL);

    memset((void *)newNode, 0, sizeof(list_t));
    newNode->num = num;

    if (str)
    {
        newNode->str = strdup(str);
        if (!newNode->str)
        {
            free(newNode);
            return (NULL);
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    return (newNode);
}

/**
 * printListStrings - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t printListStrings(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * deleteNodeAtIndex - Deletes a node at the given index.
 * @head: Pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *node, *prevNode;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }

    node = *head;
    while (node)
    {
        if (i == index)
        {
            prevNode->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }

        i++;
        prevNode = node;
        node = node->next;
    }

    return (0);
}

/**
 * freeList - Frees all nodes of a list.
 * @headPtr: Pointer to the pointer to the head node.
 *
 * Return: Void.
 */
void freeList(list_t **headPtr)
{
    list_t *node, *nextNode, *head;

    if (!headPtr || !*headPtr)
        return;

    head = *headPtr;
    node = head;

    while (node)
    {
        nextNode = node->next;
        free(node->str);
        free(node);
        node = nextNode;
    }

    *headPtr = NULL;
}

