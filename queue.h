#ifndef EXP2_QUEUE_H
#define EXP2_QUEUE_H

/*
 * Declerations of queue functions.
 */
int IsEmpty(int *front, int *rear, int count);
int Enqueue(char data, char **queue, int *rear, int size, int *front, int *count);
char Dequeue(char *queue, int *front, int *rear, int size, int *count);

#endif
