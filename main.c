#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalhometodos.h"

int main() {
    Hash* tabela = Criar_Hash();
    int opcao;
    char nome[30], senha[30];

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar login\n");
        printf("2 - Login\n"); 
        printf("3 - Imprimir tabela\n");
        printf("4 - Remover login\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                printf("Digite o login: ");
                scanf("%s", nome);

                if (AprovarLogin(tabela, nome)) {
                    CreateLogin(tabela, nome);
                } else {
                    printf("Login %s já existe.\n", nome);
                }
                break;

            case 2: 
                printf("Digite o login: ");
                scanf("%s", nome);
                printf("Digite a senha: ");
                scanf("%s", senha);
                Login(tabela, nome, senha); 
                break;

            case 3:
                Print_Hash(tabela);
                break;

            case 4:
                printf("Digite o login para remover: ");
                scanf("%s", nome);
                Remove_Login(tabela, nome);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
    
    
    return 0;
}