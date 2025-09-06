#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// STRUCTS 
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct {
    char* missao; // armazenada dinamicamente
} Jogador;

// FUNÇÕES 

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir o mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d -> Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n %s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado do Atacante: %d | Dado do Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(" O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf(" O defensor resistiu! O atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

// Função para atribuir uma missão
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    *destino = (char*)malloc(strlen(missoes[sorteio]) + 1);
    strcpy(*destino, missoes[sorteio]);
}

// Exibir missão do jogador
void exibirMissao(char* missao) {
    printf("\n Sua missão: %s\n", missao);
}

// Verificar missão (lógica simples de exemplo)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de condição fictícia:
    if (strstr(missao, "3 territórios")) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) contador++;
        }
        if (contador >= 3) return 1;
    }
    return 0;
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int qtdJogadores) {
    free(mapa);
    for (int i = 0; i < qtdJogadores; i++) {
        free(jogadores[i].missao);
    }
    free(jogadores);
}

// Main
int main() {
    srand(time(NULL));

    int qtdTerritorios, qtdJogadores;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);

    Territorio* mapa = (Territorio*)calloc(qtdTerritorios, sizeof(Territorio));
    cadastrarTerritorios(mapa, qtdTerritorios);

    printf("\nQuantos jogadores participarão? ");
    scanf("%d", &qtdJogadores);

    Jogador* jogadores = (Jogador*)malloc(qtdJogadores * sizeof(Jogador));

    // Missoes pré-definidas
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 2 territórios com 5 ou mais tropas",
        "Conquistar qualquer território azul",
        "Manter pelo menos 1 território até o final do turno"
    };
    int totalMissoes = 5;

    // Atribui missões a cada jogador
    for (int i = 0; i < qtdJogadores; i++) {
        atribuirMissao(&jogadores[i].missao, missoes, totalMissoes);
        printf("\nJogador %d recebeu sua missão!\n", i + 1);
        exibirMissao(jogadores[i].missao);
    }

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar\n");
        printf("3 - Verificar missões\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirMapa(mapa, qtdTerritorios);
        } else if (opcao == 2) {
            int idAtacante, idDefensor;
            exibirMapa(mapa, qtdTerritorios);
            printf("\nEscolha o território atacante: ");
            scanf("%d", &idAtacante);
            printf("Escolha o território defensor: ");
            scanf("%d", &idDefensor);

            if (idAtacante > 0 && idAtacante <= qtdTerritorios &&
                idDefensor > 0 && idDefensor <= qtdTerritorios &&
                strcmp(mapa[idAtacante - 1].cor, mapa[idDefensor - 1].cor) != 0) {
                atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
            } else {
                printf("Ataque inválido!\n");
            }
        } else if (opcao == 3) {
            for (int i = 0; i < qtdJogadores; i++) {
                if (verificarMissao(jogadores[i].missao, mapa, qtdTerritorios)) {
                    printf("\n Jogador %d venceu cumprindo a missão: %s\n", i + 1, jogadores[i].missao);
                    liberarMemoria(mapa, jogadores, qtdJogadores);
                    return 0;
                }
            }
            printf("\nNenhum jogador venceu ainda.\n");
        }
    } while (opcao != 0);

    liberarMemoria(mapa, jogadores, qtdJogadores);
    return 0;
}
