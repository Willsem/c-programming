#include "list.h"

int comparator(const void *data1, const void *data2)
{
    return *(int*)data1 - *(int*)data2;
}

void free_data(void *data)
{
    return;
}

int main(void)
{
    int arr[] = { 1, 3 ,5, 1, 3, 4, 2, 0, 3, 2, 3 };

    node_t *head = malloc(sizeof(node_t));

    node_t *temp = head;

    for (int i = 0; i < 10; i++)
    {
        temp->data = arr + i;

        if (i != 9)
        {
            temp->next = malloc(sizeof(node_t));
            temp = temp->next;
        }
    }

    temp->next = NULL;

    temp = head;
    while (temp != NULL)
    {
        printf("%d ", *(int*)temp->data);
        temp = temp->next;
    }
    printf("\n");

    head = sort(head, comparator);

    temp = head;
    while (temp != NULL)
    {
        printf("%d ", *(int*)temp->data);
        temp = temp->next;
    }
    printf("\n");

    remove_duplicates(&head, comparator);

    temp = head;
    while (temp != NULL)
    {
        printf("%d ", *(int*)temp->data);
        temp = temp->next;
    }

    free_list(head, free_data);
}
