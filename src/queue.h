#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

struct queueItem ;
typedef struct queueItemTag{
    int isPriority;
    int number;
} queueItem;

struct queue ;
typedef struct queueTag{
    struct queueItem *items;
} queue;

queue Queue;

void generate_ticket();
void call_next_ticket();
void print_ticket_board();

#endif //QUEUE_H_INCLUDED