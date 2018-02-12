#ifndef EXP2_STACK_H
#define EXP2_STACK_H

/*
 * Declerations of stack functions.
 */
int isempty(int top);
int isfull(int top, int size);
char pop(char *stack, int *top);
int push(char data, char **stack, int *top, int size);

#endif
