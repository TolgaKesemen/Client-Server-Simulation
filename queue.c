#include "queue.h"

/*
 * IsEmpty()
 * parameter int*, int*, int
 * returns 1 if queue is empty
 * returns 0 if queue is not empty
 */
int IsEmpty(int *front, int *rear, int count)
{
    if((*(rear) == -1) && (*(front) == -1))
    {
        return 1;
    }
    else if(count == 0)
    {
        *(front) = -1;
        *(rear) = -1;
        return  1;
    }
    else
    {
        return 0;
    }
}

/*
 * Enqueue()
 * parameter char, char**, int*, int, int*, int*
 * returns 1 if it can add the queue
 * returns 0 if it can not add the queue
 */
int Enqueue(char data, char **queue, int *rear, int size, int *front, int *count)
{
    if((*(front) == -1) && (*(rear) == -1)) {
        *(front) = 0;
        *(rear) = 0;
        *(*(queue) + *(rear)) = data;
        *(rear) = (*(rear) + 1) % size;
        *(count) = *(count) + 1;
    }
    else if( *(count) == size )
    {
        return 0;
    }
    else
    {
        *(*(queue) + *(rear)) = data;
        *(rear) = (*(rear) + 1) % size;
        *(count) = *(count) + 1;
    }
    return 1;
}

/*
 * Dequeue()
 * parameter char*, int*, int*, int, int*
 * returns character at the front of queue
 */
char Dequeue(char *queue, int *front, int *rear, int size, int *count)
{
    char data;
    if(IsEmpty(front, rear, *(count)))
    {
        return '$';
    }
    else
    {
        data = *(queue + *(front));
        *(front) = (*(front) + 1) % size;
        *(count) = *(count) - 1;
        return data;
    }
}