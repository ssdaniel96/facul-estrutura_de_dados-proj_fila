#include <stdio.h>
#include "queue.h"

int main() {
    printf("Hello world");
    generate_ticket();
    call_next_ticket();
}

void chosen_menu(int option){
    switch (option)
    {
    case 1:
        generate_ticket();
        break;
    case 2:
        call_next_ticket();
        break;
    case 3:
        printf("Board aqui");
        break;
    default:
        printf("Escolha uma opcao valida! (1 a 3)\n");
        chosen_menu(option);
        break;
    }
}