#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

// Função para cadastrar os territórios dinamicamente
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Lista de Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simulação dos dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n%s (%s) atacou %s (%s)!\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        printf(">> %s venceu a batalha!\n", atacante->nome);

        // Transferência de controle: defensor muda de dono
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas invadem

    } else {
        printf(">> Defesa bem sucedida!\n");
        atacante->tropas--; // atacante perde uma tropa
    }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Garante aleatoriedade nos dados

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, n);

    // Exibe territórios cadastrados
    exibirTerritorios(mapa, n);

    // Exemplo de ataque
    int iAtacante, iDefensor;
    printf("\nEscolha o número do território atacante (1-%d): ", n);
    scanf("%d", &iAtacante);
    printf("Escolha o número do território defensor (1-%d): ", n);
    scanf("%d", &iDefensor);

    // Validação: impedir que ataque territórios da mesma cor
    if (strcmp(mapa[iAtacante - 1].cor, mapa[iDefensor - 1].cor) == 0) {
        printf("Um território não pode atacar outro da mesma cor!\n");
    } else {
        atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
    }

    // Exibe novamente os territórios atualizados
    exibirTerritorios(mapa, n);

    // Libera memória
    liberarMemoria(mapa);

    return 0;
}
