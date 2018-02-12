#include "stack.h"

/*
 * isempty()
 * parameter int
 * returns 1 if stack is empty
 * returns 0 if stack is not empty
 */
int isempty(int top)
{
    if(top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * isfull()
 * parameter int, int
 * returns 1 if stack is full
 * returns 0 if stack is not full
 */
int isfull(int top, int size)
{
    if(top == (size - 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * pop()
 * parameter char*, int*
 * returns character at the top of stack
 */
char pop(char *stack, int *top)
{
    char data;
    if(!isempty(*(top)))
    {
        data = *(stack + *(top));
        *(top) = *(top) - 1;
        return data;
    }
    else
    {
        return '$';
    }
}

/*
 * push()
 * parameter char, char**, int*, int
 * returns 1 if it can add the stack
 * returns 0 if it can not add the stack
 */
int push(char data, char **stack, int *top, int size)
{
    if(!isfull(*(top), size))
    {
        *(top) = *(top) + 1;
        *(*(stack) + *(top)) = data;
        return 1;
    }
    else
    {
        return 0;
    }
}