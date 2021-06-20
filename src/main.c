#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <locale.h>

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
    printf("SUPER FILA SX 3.000\n");
    printf("1 - Gerar nova senha\n");
    printf("2 - Chamar próxima senha\n");
    printf("3 - Imprimir senhas\n");
    printf("4 - Encerrar\n");
}

int get_menu_option(){
    int value;
    fflush(stdin);
    printf("Digite a opcao (1 a 4): ");
    scanf("%d", &value);
    printf("\n");
    if (value < 1 || value > 4){
        printf("Opção inválida! Só serão aceitos valores de 1 a 4.\n");
        system("pause");
        value = get_menu_option();
    }
    return value;
}


int chosen_menu(){
    int option = get_menu_option();
    int run = 1;
    switch (option)
    {
    case 1:
        generate();
        break;
    case 2:
        call_next();
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
    setlocale(LC_ALL, "Portuguese");
    execute_menu();
}