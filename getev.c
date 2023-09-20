#include "shell.h"

/**
 * getEnvironment - Retrieve a copy of the environment variables as a string array.
 * @info: Structure containing potential arguments. Maintains a constant function prototype.
 *
 * Return: Always 0
 */
char **getEnvironment(info_t *info)
{
    if (!info->environ || info->envChanged)
    {
        info->environ = convertListToStrings(info->env);
        info->envChanged = 0;
    }

    return info->environ;
}

/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @info: Structure containing potential arguments. Maintains a constant function prototype.
 * @variable: The name of the environment variable to delete.
 *
 * Return: 1 if deleted, 0 otherwise
 */
int unsetEnvironmentVariable(info_t *info, char *variable)
{
    list_t *node = info->env;
    size_t index = 0;
    char *property;

    if (!node || !variable)
        return 0;

    while (node)
    {
        property = startsWith(node->str, variable);
        if (property && *property == '=')
        {
            info->envChanged = deleteNodeAtIndex(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }
    return info->envChanged;
}

/**
 * setEnvironmentVariable - Initialize or modify an environment variable.
 * @info: Structure containing potential arguments. Maintains a constant function prototype.
 * @variable: The name of the environment variable.
 * @value: The value of the environment variable.
 *
 * Return: Always 0
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
    char *envString = NULL;
    list_t *node;
    char *property;

    if (!variable || !value)
        return 0;

    envString = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!envString)
        return 1;

    _strcpy(envString, variable);
    _strcat(envString, "=");
    _strcat(envString, value);

    node = info->env;
    while (node)
    {
        property = startsWith(node->str, variable);
        if (property && *property == '=')
        {
            free(node->str);
            node->str = envString;
            info->envChanged = 1;
            return 0;
        }
        node = node->next;
    }

    addNodeEnd(&(info->env), envString, 0);
    free(envString);
    info->envChanged = 1;

    return 0;
}

