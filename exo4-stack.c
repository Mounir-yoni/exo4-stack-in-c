#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stack
{
    int data;
    struct stack *next;
};

void addbegin(struct stack **start, int v);
void delbegin(struct stack **start);
void numberoropiration(char inp[], struct stack **head);
void operation(struct stack **head, char op);
void freeStack(struct stack **head);
int isNumber(const char *str);
int main()
{
    bool end_of_program = false;
    char inp[10];
    struct stack *start = NULL;

    do
    {
        printf("Enter a number or '=' to end : ");
        scanf("%s", inp);

        if (strcmp(inp, "=") == 0)
        {
            end_of_program = true;
        }
        else
        {
            numberoropiration(inp, &start);
        }
    } while (!end_of_program);

    if (start != NULL)
    {
        printf("the result = %i \n", start->data);
    }
    else
    {
        printf("the stack is vide\n");
    }
    freeStack(&start);
    return 0;
}

void addbegin(struct stack **start, int v)
{
    struct stack *new_node = (struct stack *)malloc(sizeof(struct stack));
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = v;
    new_node->next = *start;
    *start = new_node;
}

void delbegin(struct stack **start)
{
    if (*start == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
    struct stack *del = *start;
    *start = (*start)->next;
    free(del);
}

void numberoropiration(char inp[], struct stack **head)
{

    switch (inp[0])
    {
    case '+':
        operation(head, '+');
        break;
    case '*':
        operation(head, '*');
        break;
    case '-':
        operation(head, '-');
        break;
    case '/':
        operation(head, '/');
        break;
    default:

        if (isNumber(inp))
        {
            addbegin(head, atoi(inp));
        }
        else
        {
            printf("Error: enter a number or a operation \n");
        }

        break;
    }
}
int isNumber(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (i == 0 && str[i] == '-')
            continue;
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

void operation(struct stack **head, char op)
{
    int result;
    if ((*head) != NULL && (*head)->next != NULL)
    {

        switch (op)
        {
        case '+':
            result = (*head)->data + (*head)->next->data;
            break;
        case '-':
            result = (*head)->data - (*head)->next->data;
            break;
        case '*':
            result = (*head)->data * (*head)->next->data;
            break;
        case '/':
            result = (*head)->data / (*head)->next->data;
            break;
        default:
            break;
        }
        delbegin(head);
        delbegin(head);
        addbegin(head, result);
    }
    else
    {
        printf("enter number first to do operation \n");
    }
}

void freeStack(struct stack **head)
{
    while (*head != NULL)
    {
        delbegin(head);
    }
}