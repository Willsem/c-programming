#include "trie.h"

my_trie *trie_create()
{
    my_trie *trie = malloc(sizeof(my_trie));
    trie->data = NULL;
    trie->key = '\0';
    trie->is_real = FALSE;
    trie->leavs = NULL;

    return trie;
}

void *trie_get(my_trie *trie, char *str_key)
{
    for (int i = 0; ; i++)
    {
        if (str_key[i] == '\0')
        {
            if (trie->is_real)
                return trie->data;
            else
                return NULL;
        }

        node_t *temp;
        if (trie != NULL)
            temp = trie->leavs;
        else
            return NULL;

        for (;temp != NULL; temp = temp->next)
        {
            my_trie *root = temp->data;

            if (root->key == str_key[i])
            {
                trie = root;
                break;
            }
        }

        if (temp == NULL)
            return NULL;
    }
}

void trie_set(my_trie *trie, char *str_key, void *data)
{
    for (int i = 0; ; i++)
    {
        if (str_key[i] == '\0')
        {
            trie->data = data;
            trie->is_real = TRUE;
            return;
        }

        node_t *temp = NULL;
        if (trie != NULL)
            temp = trie->leavs;
        else
        {
            my_trie *tmp = malloc(sizeof(my_trie));
            tmp->is_real = FALSE;
            tmp->key = str_key[i];
            tmp->data = NULL;
            tmp->leavs = NULL;
            node_t *node = malloc(sizeof(node_t));
            node->data = tmp;
            insert(&(trie->leavs), node, trie->leavs);
            trie = tmp;
        }

        for (;temp != NULL; temp = temp->next)
        {
            my_trie *root = temp->data;

            if (root->key == str_key[i])
            {
                trie = root;
                break;
            }
        }

        if (temp == NULL)
        {
            my_trie *tmp = malloc(sizeof(my_trie));
            tmp->is_real = FALSE;
            tmp->key = str_key[i];
            tmp->data = NULL;
            tmp->leavs = NULL;
            node_t *node = malloc(sizeof(node_t));
            node->data = tmp;
            insert(&(trie->leavs), node, trie->leavs);
            trie = tmp;
        }
    }
}

void trie_remove(my_trie *trie, char *str_key)
{
    for (int i = 0; ; i++)
    {
        if (str_key[i] == '\0')
        {
            if (trie->is_real)
            {
                trie->is_real = FALSE;
                return;
            }
            else
                return;
        }

        node_t *temp;
        if (trie != NULL)
            temp = trie->leavs;
        else
            return;

        for (;temp != NULL; temp = temp->next)
        {
            my_trie *root = temp->data;

            if (root->key == str_key[i])
            {
                trie = root;
                break;
            }
        }

        if (temp == NULL)
            return;
    }
}

void trie_search_keys_recursive(my_trie *trie, char *str, int index, char *now, int found, int len);

void trie_search_keys(my_trie *trie, char *str)
{
    char now[SIZE];
    trie_search_keys_recursive(trie, str, 0, now, 0, 0);
}

void trie_search_keys_recursive(my_trie *trie, char *str, int index, char now[SIZE], int found, int len)
{
    if (trie == NULL)
        return;

    if (!found && str[index] == trie->key)
        index++;
    else
        index = 0;

    if (str[index] == '\0')
        found = TRUE;

    if (trie->key != '\0')
        now[len++] = trie->key;

    now[len] = '\0';

    if (found && trie->is_real)
        printf("%s\n", now);

    for (node_t *temp = trie->leavs; temp != NULL; temp = temp->next)
        trie_search_keys_recursive((my_trie*)temp->data, str, index, now, found, len);
}

void trie_print_recursive(my_trie *trie, int level, int end, int probels[SIZE]);

void trie_print(my_trie *trie)
{
    int probels[SIZE];
    trie_print_recursive(trie, 0, 0, probels);
}

void trie_print_recursive(my_trie *trie, int level, int end, int probels[SIZE])
{
    if (trie == NULL)
        return;

    for (int i = 0; i < level - 1; i++)
    {
        if (probels[i])
            printf("  ");
        else
            printf("│ ");
    }

    if (trie->key == '\0')
        printf("head\n");
    else if (trie->is_real)
    {
        if (end)
            printf("└▶" GREEN "%c\n", trie->key);
        else
            printf("├▶" GREEN "%c\n", trie->key);
    }
    else
    {
        if (end)
            printf(WHITE "└▶%c\n", trie->key);
        else
            printf(WHITE "├▶%c\n", trie->key);
    }

    printf(WHITE "");

    for (node_t *temp = trie->leavs; temp != NULL; temp = temp->next)
    {
        if (temp->next != NULL)
        {
            probels[level] = 0;
            trie_print_recursive((my_trie*)temp->data, level + 1, FALSE, probels);
        }
        else
        {
            probels[level] = 1;
            trie_print_recursive((my_trie*)temp->data, level + 1, TRUE, probels);
        }
    }
}

