#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

queueItem *__newQueueItem(int ticketNumber, int isPriority){
    queueItem *newQueueItem = (queueItem*)malloc(sizeof(queueItem));
    newQueueItem->number = ticketNumber;
    newQueueItem->isPriority = isPriority;
    return newQueueItem;
}

int __getTrueOrFalse(char message[255]){
    int value;
    printf("%s", message);
    fflush(stdin);
    scanf("%d", &value);
    printf("\n");
    if (value > 1 || value < 0){
        printf("Erro, digite o valor corretamente!\n");
        value = __getTrueOrFalse(message);
    }
    return value;
}

int __getIsPriority(){
    return __getTrueOrFalse("Digite o tipo de atendimento.\n\t0 - Atendimento Normal\n\t1 - Atendimento prioritário\nAtendimento: ");
}

int __generate_random_number(int indexOf, int indexTo){
    time_t t;
    srand((unsigned) time(&t));
    return rand() % indexTo + indexOf;
}

int __ticket_number_already_exists_in_queue(int ticketNumber, queueItem *item){
    if (item == NULL){
        return 0;
    }
    else if (item->number == ticketNumber){
        return 1;
    }
    else if (item->nextItem == NULL){
        return 0;
    }
    else{
        return __ticket_number_already_exists_in_queue(ticketNumber, (queueItem *)item->nextItem);
    }
}

int __generate_ticket_number(){
    int ticket_number = __generate_random_number(1, 999);
    if (__ticket_number_already_exists_in_queue(ticket_number, firstItem) == 1){
        ticket_number = __generate_ticket_number();
    }
    return ticket_number;
}

queueItem *__getFirstNoPriority(queueItem *firstItem, queueItem *previousItem){
    if (firstItem->isPriority == 1){
        if (firstItem->nextItem == NULL){
            return NULL;
        }
        return __getFirstNoPriority((queueItem *)firstItem->nextItem, firstItem);
    }
    return firstItem;
}

void __add_after_all_priorities(queueItem *firstItem, queueItem *newItem){
    if (newItem->isPriority == 0){
        exit(1);
    }

    queueItem *previousItem = NULL;
    queueItem *actualItem = __getFirstNoPriority(firstItem, previousItem);
    if (actualItem == NULL){
        lastItem->nextItem = newItem;
        lastItem = newItem;
    }
    else{
        newItem->nextItem = actualItem;
        previousItem->nextItem = newItem;
    }
}

queueItem *__create_ticket(){
    int ticketNumber = __generate_ticket_number();
    int isPriority = __getIsPriority();
    return __newQueueItem(ticketNumber, isPriority);
}

void generate_ticket(){
    queueItem *newQueueItem = __create_ticket();

    if (firstItem == NULL){
        firstItem = newQueueItem;
        lastItem = newQueueItem;
    }
    else if (newQueueItem->isPriority == 0){
        lastItem->nextItem = newQueueItem;
        lastItem = newQueueItem;
    }
    else if (firstItem->isPriority == 0){
        newQueueItem->nextItem = firstItem;
        firstItem = newQueueItem;
    }
    else{
        __add_after_all_priorities(firstItem, newQueueItem);
    }
}

int __get_giche(){
    int value;
    printf("Por favor digite o gichê: ");
    fflush(stdin);
    scanf("%d", &value);
    printf("\n");
    return value;
}

void __print_ticket(queueItem *queueItem){
    int giche_number = __get_giche();
    printf("NOVA CHAMADA\n");
    printf("Senha: %d\tGiche: %d\n", queueItem->number, giche_number);
}

void __pop(){
    queueItem *oldFirstITem = firstItem;
    firstItem = firstItem->nextItem;
    if (firstItem == NULL){
        lastItem = NULL;
    }
    free(oldFirstITem);
}

void call_next_ticket(){
    __print_ticket(firstItem);
    __pop();
}