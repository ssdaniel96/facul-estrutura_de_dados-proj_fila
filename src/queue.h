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

void generate(void);
void call_next(void);
void print_board(void);

#endif //QUEUE_H_INCLUDED
