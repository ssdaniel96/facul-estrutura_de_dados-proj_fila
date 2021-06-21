#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "ascii_art.c";

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}

void get_menu(){
    clear_screen();
    print_welcome_art();
    printf("\t\t\t\t\t\tESCOLHA SEU SERVICO:\n");
    printf("\n1 - Gerar nova senha\n");
    printf("\n2 - Chamar senha\n");
    printf("\n3 - Imprimir senhas\n");
    printf("\n4 - Encerrar\n");
}

int get_menu_option(){
    int value;
    fflush(stdin);
    printf("\nDigite a escolha (1 a 4): ");
    scanf("%d", &value);
    printf("\n");
    if (value < 1 || value > 4){
        printf("Escolha invalida! Os valoes devem ser de 1 a 4.\n");
        system("pause");
        value = get_menu_option();
    }
    return value;
}

int __get_priority(){
    char *message = "Digite o tipo de atendimento.\n\t0 - Normal\n\t1 - Prioritario\nAtendimento: ";
    int value;
    printf("%s", message);
    fflush(stdin);
    scanf("%d", &value);
    printf("\n");
    if (value > 1 || value < 0){
        printf("Os valores devem ser 0 ou 1! Tente Novamente!\n");
        value = __get_priority();
    }
    return value;
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



int chosen_menu(){
    int option = get_menu_option();
    int run = 1;
    switch (option)
    {
    case 1:
        generate(__get_priority());
        print_new_item();
        break;
    case 2:
        call_next(__get_giche());
        break;
    case 3:
        print_board();
        break;
    case 4:
        run = 0;
    }
    system("pause");
    return run;
}

void execute_menu(){
    int run = 1;
    while(run == 1){
        get_menu();
        run = chosen_menu();
    }
}

int main() {
    execute_menu();
}

