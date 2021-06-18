#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

struct queueItem ;
typedef struct queueItemTag{
    int isPriority;
    int number;
    struct queueItem *nextItem;
} queueItem;

queueItem *firstItem;
queueItem *lastItem;

void generate_ticket();
void call_next_ticket();
void print_ticket_board();

#endif //QUEUE_H_INCLUDED