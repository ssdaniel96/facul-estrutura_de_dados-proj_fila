#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

queueItem *__newQueueItem(int ticketNumber, int isPriority){
    queueItem *newQueueItem = (queueItem*)malloc(sizeof(queueItem));
    newQueueItem->number = ticketNumber;
    newQueueItem->isPriority = isPriority;
    newQueueItem->nextItem = NULL;
    return newQueueItem;
}

int __getTrueOrFalse(char message[255]){
    int value;
    printf("%s", message);
    fflush(stdin);
    scanf("%d", &value);
    printf("\n");
    if (value > 1 || value < 0){
        printf("Os valores devem ser 0 ou 1! Tente Novamente!\n");
        value = __getTrueOrFalse(message);
    }
    return value;
}

int __getIsPriority(){
    return __getTrueOrFalse("Digite o tipo de atendimento.\n\t0 - Normal\n\t1 - Prioritario\nAtendimento: ");
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

queueItem *__getFirstNoPriority(queueItem *firstItem, queueItem **previousItem){
    if (firstItem->isPriority == 1){
        if (firstItem->nextItem == NULL){
            return NULL;
        }
        *previousItem = firstItem;
        return __getFirstNoPriority((queueItem *)firstItem->nextItem, previousItem);
    }
    return firstItem;
}

void __add_after_all_priority(queueItem *firstItem, queueItem *newItem){
    if (newItem->isPriority == 0){
        printf("Esse item sem prioridade deveria ser adicionado no final da fila!\nEncerrando o programa por erro!\n");
        exit(1);
    }

    queueItem *previousItem;
    queueItem *actualItem = __getFirstNoPriority(firstItem, &previousItem);
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

void generate(void){
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
        __add_after_all_priority(firstItem, newQueueItem);
    }
}

int __get_giche(){
    int value;
    printf("Por favor digite o giche: ");
    fflush(stdin);
    scanf("%d", &value);
    printf("\n");
    if (value < 1){
        printf("O valor deve ser maior ou igual a 1.\n");
        value = __get_giche();
    }    
    return value;
}

int __check_empty_queue(){
    if (firstItem == NULL){
        return 1;
    }
    else{
        return 0;
    }
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

void call_next(void){
    if(__check_empty_queue()){
        printf("Fila vazia! Gere uma senha!\n");
        return;
    }
    __print_ticket(lastItem);
    __pop();
}

void __print_board_header(){
    printf("Posicao\tSenha\tTipo\n");
}

char *__get_type_attendance_description(int isPriority){
    if (isPriority == 1){
        return "Prioritario";
    }
    else{
        return "Normal";
    }
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

void __find_ticket(queueItem *findItem){
    char *modalidade = __get_type_attendance_description(findItem->isPriority);
    printf("Senha: %d\tAtendimento: %s\n", findItem->number, modalidade);
}

void print_new_item(){
    printf("Senha Cadastrada!\n");
    printf("Confira sua senha!\n");
    __find_ticket(lastItem);

}