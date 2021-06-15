#include "queue.h"
#include "stdlib.h"
#include "stdio.h"

time_t t;

void generate_ticket(){
    int ticketNumber = generate_ticket_number(Queue.items);
}

int generate_ticket_number(queueItem *items){
    int ticket_number = generate_random_number(1, 999);
    if (ticket_number_already_exists_in_queue(ticket_number, items) == 1){
        ticket_number = generate_ticket_number(1, 999);
    }
    return ticket_number;
}

int ticket_number_already_exists_in_queue(int ticketNumber, queueItem *items){
    int exists = 0;
    for(int i=0; i<len(*items); i++){
        if (items[i].number == ticketNumber){
            exists = 1;
            break;
        }
    }
    return exists;
}


int generate_random_number(int indexOf, int indexTo){
    srand((unsigned) time(&t));
    return rand() % indexTo + indexOf;
}