#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_node
{
    int data;
    struct s_node *link;
    
}t_node;


t_node  *add_last(t_node *ptr, int data)
{
    t_node *tmp;
    tmp = (t_node *)malloc(sizeof(t_node));
    tmp->data = data;
    tmp->link = NULL;

    ptr->link = tmp;
    return (tmp); 
}
int main()
{
    t_node *head, *ptr;
    head = (t_node *)malloc(sizeof(t_node));
    
    head->data = 1994;
    head->link = NULL;
    
    ptr = head;
    
    ptr = add_last(ptr, 1337);
    ptr = add_last(ptr, 42);
    ptr = add_last(ptr, 1996);

    ptr = head;

    while (ptr->link != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }
    printf("%d ", ptr->data);
    return (0);
}

