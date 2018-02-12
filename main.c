
/*
 * In this experiment, there is clients whose count can vary and one server. Both clients and server
 * have their own queue and stack structures.
 * This program takes three arguments from command line. Two input files and one output file name.
 * First input file specifies the sizes of queue and stack structures of clients and server. Also it includes
 * total number of clients + server.
 * Second input file includes the commands which will specify the operations on clients and server. Second
 * input file's first line is the number of commands.
 * Third argument is the name of output file. The history of all clients and server will be written to that file.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

/*
 * Definitions of types.
 */
typedef struct{
    char *st;
    int top;
    int stsize;
}Stack;

typedef struct{
    char *qu;
    int front;
    int rear;
    int qusize;
    int count;
}Queue;

/*
 * Definitions of structures.
 */
struct Client{
    Stack stack;
    Queue queue;
    char History[500];
};

struct Command{
    char c[3];
};

/*
 * Definitions of global variables.
 */
int clientSize;


/*
 * The main function does it all. I did not broke it to multiple functions.
 * Main function reads first input file then creates clients and server.
 * After that, it reads second input file and operates the commands in it.
 * Finally it prints the histories of both clients and server to the output file.
 */
int main(int argc, char **argv)
{
    //char *const f1 = argv[1];
    FILE *file1;
    static char line[10];
    char *word;

    /*
     * Giving error message to console if the file could not opened.
     */
    if((file1 = fopen(argv[1], "r")) == NULL)
    {
        printf("Error! Input1 could not opened.\n");
        return 0;
    }

    fgets(line, sizeof(line), file1);
    word = strtok(line, "\n");
    clientSize = atoi(word);
    clientSize--;

    /*
     * Clients hold by an array which type is 'Client'.
     */
    struct Client client[clientSize];
    struct Client server;

    int i = 0;
    while(fgets(line, sizeof(line), file1))     /* Creating the clients and whose stack and queues */
    {
        if(i<clientSize)
        {
            word = strtok(line, " ");
            client[i].queue.qu = (char*) malloc(atoi(word) * sizeof(char));
            client[i].queue.front = -1;
            client[i].queue.rear = -1;
            client[i].queue.qusize = atoi(word);
            client[i].queue.count = 0;
            word = strtok(NULL, "\n");
            client[i].stack.st = (char*) malloc(atoi(word) * sizeof(char));
            client[i].stack.top = -1;
            client[i].stack.stsize = atoi(word);
            client[i].History[0] = '\0';
            i++;
        }
        else
        {
            break;
        }
    }

    /*
     * Creating server's queue and stack structures.
     */
    word = strtok(line, " ");
    server.queue.qu = (char*) malloc(atoi(word) * sizeof(char));
    server.queue.front = -1;
    server.queue.rear = -1;
    server.queue.qusize = atoi(word);
    server.queue.count = 0;
    word = strtok(NULL, " ");
    server.stack.st = (char*) malloc(atoi(word) * sizeof(char));
    server.stack.top = -1;
    server.stack.stsize = atoi(word);
    server.History[0] = '\0';

    fclose(file1);
    /*
     * End of reading first input file.
     */

    FILE *file2;

    /*
     * Giving error message to console if the file could not opened.
     */
    if((file2 = fopen(argv[2], "r")) == NULL)
    {
        printf("Error! Input2 could not opened.\n");
        return 0;
    }

    fgets(line, sizeof(line), file2);
    word = strtok(line, "\n");
    int commandNumber = atoi(word);
    struct Command *commands = (struct Command*) malloc(commandNumber * sizeof(struct Command));

    /*
     * Reading second input file and keeps it in 'commands' which type is pointer of type 'Command'.
     * I did it because i thought this will be much faster than other ways. But it loses from memory while
     * it gains from speed.
     */
    i = 0;
    int j = 0;
    while(fgets(line, sizeof(line), file2))
    {
        word = strtok(line, " ");
        (commands+i)->c[j] = *(word);
        j++;
        word = strtok(NULL, " ");
        (commands+i)->c[j] = *(word);
        j++;
        word = strtok(NULL, "\n");
        (commands+i)->c[j] = *(word);
        j = 0;
        i++;
    }

    fclose(file2);
    /*
     * End of reading second input file.
     */

    int num;
    i = 0;

    /*
     * The loop is continuing until there is no command.
     */
    while(i<commandNumber)
    {
        /* Variable 'num' keeps the client or server number. This mathematical approach is used for converting char
         * to integer by the help of ASCII Table. */
        num = ((int) (commands+i)->c[1] - 49);
        if(((commands+i)->c[0] == 'A'))
        {
            /* It adds the given content to the queue of the client which number is given. */
            if(!Enqueue((commands+i)->c[2], &(client[num].queue.qu), &(client[num].queue.rear), client[num].queue.qusize, &(client[num].queue.front), &(client[num].queue.count)))
            {
                /* If client's queue is full than it adds error message '1' to the client's history. */
                strcat(client[num].History, "1 ");
            }
        }

        else if((commands+i)->c[0] == 'I')
        {
            /* It adds the given content to the stack of a client or server depends on the number given. */
            if(num < clientSize)
            {
                if(!push((commands+i)->c[2], &(client[num].stack.st), &(client[num].stack.top), client[num].stack.stsize))
                {
                    /* If client's stack is full than it adds error message '2' to the client's history. */
                    strcat(client[num].History, "2 ");
                }
            }
            else
            {
                if(!push((commands+i)->c[2], &(server.stack.st), &(server.stack.top), server.stack.stsize))
                {
                    /* If server's stack is full than it adds error message '2' to the server's history. */
                    strcat(server.History, "2 ");
                }
            }
        }

        else if(((commands+i)->c[0] == 'S'))
        {
            /* It sends the content from client's stack or queue to server's queue and adds it to client's history. */
            char data[3];
            data[2] = '\0';
            if(!isempty(client[num].stack.top))
            {
                /* If client's stack is not empty add content to the client's history. */
                data[0] = pop(client[num].stack.st, &(client[num].stack.top));
                data[1] = ' ';
                strcat(client[num].History, data);
                /* It adds the content to the queue of the server. */
                if(!Enqueue(data[0], &(server.queue.qu), &(server.queue.rear), server.queue.qusize, &(server.queue.front), &(server.queue.count)))
                {
                    /* If server's queue is full than it adds error message '1' to the server's history. */
                    strcat(server.History, "1 ");
                }
            }
            else
            {
                /* If client's stack is empty */
                if(!IsEmpty(&(client[num].queue.front), &(client[num].queue.rear), client[num].queue.count))
                {
                    /* If client's queue is not empty add content to the client's history. */
                    data[0] = Dequeue(client[num].queue.qu, &(client[num].queue.front), &(client[num].queue.rear), client[num].queue.qusize, &(client[num].queue.count));
                    data[1] = ' ';
                    strcat(client[num].History, data);
                    /* It adds the content to the queue of the server. */
                    if(!Enqueue(data[0], &(server.queue.qu), &(server.queue.rear), server.queue.qusize, &(server.queue.front), &(server.queue.count)))
                    {
                        /* If server's queue is full than it adds error message '1' to the server's history. */
                        strcat(server.History, "1 ");
                    }
                }
                else
                {
                    /* If both client's stack and queue is empty then prints error message '3' to client's history. */
                    strcat(client[num].History, "3 ");
                }
            }
        }

        else if(((commands+i)->c[0] == 'O'))
        {
            /* It operates the stack and queue of the server. */
            char data[3];
            data[2] = '\0';
            if(!isempty(server.stack.top))
            {
                /* If server's stack is not empty add the content to the server's history. */
                data[0] = pop(server.stack.st, &(server.stack.top));
                data[1] = ' ';
                strcat(server.History, data);
            }
            else
            {
                /* If server's stack is empty */
                if(!IsEmpty(&(server.queue.front), &(server.queue.rear), server.queue.count))
                {
                    /* If server's queue is not empty add the content to the server's history. */
                    data[0] = Dequeue(server.queue.qu, &(server.queue.front), &(server.queue.rear), server.queue.qusize, &(server.queue.count));
                    data[1] = ' ';
                    strcat(server.History, data);
                }
                else
                {
                    /* If both server's stack and queue is empty then prints error message '3' to server's history. */
                    strcat(server.History, "3 ");
                }
            }
        }

        i++;
    }

    i = 0;
    FILE *file3 = fopen(argv[3], "w");

    /*
     * Writing histories of all clients and server to the output file.
     */
    while(i<clientSize)
    {
        fprintf(file3, "%s\n", client[i].History);
        i++;
    }
    fprintf(file3, "%s", server.History);

    fclose(file3);
    /*
     * End of writing output file.
     */


    return 0;
}