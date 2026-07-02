#include <stdio.h>
#include <stdlib.h>

typedef int data;
typedef int key_type;

struct list
{
    key_type key;
    data information;
    struct list* next;
};

void insert_start(struct list** my_list, key_type key, data information)
{
    struct list* temporary = (struct list*) malloc(sizeof(*temporary));
    if (temporary == NULL)
    {
        printf("Not enough memory for a new element!\n");
        return;
    }

    temporary->next = *my_list;
    (*my_list) = temporary;
    (*my_list)->key = key;
    (*my_list)->information = information;
}

void insert_after(struct list** my_list, key_type key, data information)
{

    if (*my_list == NULL)
    {
        insert_start(my_list, key, information);
        return;
    }

    struct list* temporary = (struct list*) malloc(sizeof(*temporary));
    if (temporary == NULL)
    {
        printf("Not enough memory for a new element!\n");
        return;
    }

    temporary->key = key;
    temporary->information = information;
    temporary->next = (*my_list)->next;
    (*my_list)->next = temporary;
}

void insert_before(struct list** my_list, key_type key, data information)
{
    if (*my_list == NULL)
    {
        insert_start(my_list, key, information);
        return;
    }

    struct list* temporary = (struct list*) malloc(sizeof(*temporary));
    if (temporary == NULL)
    {
        printf("Not enough memory for a new element!\n");
        return;
    }

    temporary->next = *my_list;
    temporary->key = key;
    temporary->information = information;
    *my_list = temporary;
}

void delete_node(struct list** my_list, key_type key)
{
    if (*my_list == NULL)
    {
        printf("Error! Empty list!\n");
        return;
    }

    struct list* current = *my_list;
    struct list* save;
    if((*my_list)-> key == key)
    {
        current = (*my_list)->next;
        free(*my_list);
        *my_list = current;
        return;
    }

    while(current->next != NULL && current->next->key != key) {current = current->next;}

    if (current->next == NULL)
    {
        printf("Error! Element to delete not found!\n");
        return;
    }
    else
    {
        save = current->next;
        current->next = current->next->next;
        free(save);
    }
}

void print(struct list* my_list)
{
    while (my_list != NULL)
    {
        printf("%d(%d) ", my_list->key, my_list->information);
        my_list = my_list->next;
    }
    printf("\n");
}

struct list* search(struct list* my_list, key_type key)
{
    while(my_list != NULL)
    {
        if (my_list->key == key) {return my_list;}
        my_list = my_list->next;
    }
    return NULL;
}

void call_list_functions()
{
    struct list* my_list = NULL;
    int my_data;
    insert_start(&my_list, 0, 42);

    for (int i = 1; i < 6; i++)
    {
        my_data = rand()%100;
        printf("Insertion Before: %d(%d)\n", i, my_data);
        insert_before(&my_list, i, my_data);
    }
    for (int i = 6; i < 10; i++)
    {
        my_data = rand()%100;
        printf("Insertion After: %d(%d)\n", i, my_data);
        insert_after(&my_list, i, my_data);
    }

    print(my_list);
    delete_node(&my_list, 9);
    print(my_list);
    delete_node(&my_list, 0);
    print(my_list);
    delete_node(&my_list, 3);
    print(my_list);
    delete_node(&my_list, 5);
    print(my_list);
    delete_node(&my_list, 5);
}
