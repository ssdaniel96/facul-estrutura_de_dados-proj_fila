#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queueItem queueItem;
struct queueItem{
    int isPriority;
    int number;
    struct queueItem *nextItem;
};


queueItem *firstItem;
queueItem *lastItem;

void generate_ticket(void);
void call_next_ticket(void);
void print_ticket_board(void);

#endif //QUEUE_H_INCLUDED
