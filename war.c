#include <stdio.h>
#include <string.h>
//Definição da stuct de Terrotorios
//Informaçãoes relacionadas a um território do jogo
struct Territorio {
    char nome[20];  //Nome Território
    char cor[10];   // cor Território
    int tropas;     // Quantidade de tropas
};
int main() {
    // Vetor de 5 Territórios
    struct Territorio territorios[5];

    //Entrada de Dados dos 5 Territórios
    printf("======  Cadastro de Territórios =====");

    for(int i = 0; i < 5; i++) {
        printf("Territorio %d:\n" , i + 1);

        //Leitura do nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // lê até o Enter

        // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor); //Usado para permitir que o usuário digite frases com espaços

        // Leitura do número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados
    printf("\n=== Territórios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
};



