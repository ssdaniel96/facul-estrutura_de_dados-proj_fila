#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

queueItem *__new_queue_item(int ticketNumber, int isPriority){
    queueItem *newQueueItem = (queueItem*)malloc(sizeof(queueItem));
    newQueueItem->number = ticketNumber;
    newQueueItem->isPriority = isPriority;
    newQueueItem->nextItem = NULL;
    return newQueueItem;
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

queueItem *__get_first_unpriority(queueItem *firstItem, queueItem **previousItem){
    if (firstItem->isPriority == 1){
        if (firstItem->nextItem == NULL){
            return NULL;
        }
        *previousItem = firstItem;
        return __get_first_unpriority((queueItem *)firstItem->nextItem, previousItem);
    }
    return firstItem;
}

void __add_after_all_priority(queueItem *firstItem, queueItem *newItem){
    if (newItem->isPriority == 0){
        printf("Esse item sem prioridade deveria ser adicionado no final da fila!\nEncerrando o programa por erro!\n");
        exit(1);
    }

    queueItem *previousItem;
    queueItem *actualItem = __get_first_unpriority(firstItem, &previousItem);
    if (actualItem == NULL){
        lastItem->nextItem = newItem;
        lastItem = newItem;
    }
    else{
        newItem->nextItem = actualItem;
        previousItem->nextItem = newItem;
    }
}

queueItem *__create_ticket(int isPriority){
    int ticketNumber = __generate_ticket_number();
    return __new_queue_item(ticketNumber, isPriority);
}

char *__get_type_attendance_description(int isPriority){
    if (isPriority == 1){
        return "Prioritario";
    }
    else{
        return "Normal";
    }
}

void __print_ticket(queueItem *item){
    char *priority_description = __get_type_attendance_description(item->isPriority);
    printf("Senha: %d\tAtendimento: %s\n", item->number, priority_description);
}

void __print_registered_ticket(queueItem *item){
    printf("Senha Cadastrada!\n");
    printf("Confira sua senha!\n");
    __print_ticket(item);
}

void generate(int isPriority){
    queueItem *newQueueItem = __create_ticket(isPriority);

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
        __add_after_all_priority(firstItem, newQueueItem);
    }
    __print_registered_ticket(newQueueItem);
}

int __check_empty_queue(){
    if (firstItem == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void __print_call_ticket(queueItem *queueItem, int giche_number){
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

void call_next(int giche_number){
    if(__check_empty_queue()){
        printf("Fila vazia! Gere uma senha!\n");
        return;
    }
    __print_call_ticket(firstItem, giche_number);
    __pop();
}

void __print_board_header(){
    printf("Posicao\tSenha\tTipo\n");
}

void __print_board_tickets(queueItem *item, int position){
    char *tipo_atendimento = __get_type_attendance_description(item->isPriority);
    printf("%d\t%d\t%s\n", position+1, item->number, tipo_atendimento);
    if (item->nextItem != NULL){
        __print_board_tickets(item->nextItem, position+1);
    }
}

void print_board(){
    if (__check_empty_queue()){
        printf("Fila vazia!\n");
        return;
    }
    __print_board_header();
    __print_board_tickets(firstItem, 0);
}