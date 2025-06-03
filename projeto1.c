#include <stdio.h>
#include <stdlib.h>

#define LINHAS 3
#define COLUNAS 4
#define MAX_NODOS (LINHAS * COLUNAS)

typedef struct {
    int x, y;
} Ponto;

// Fila para BFS
typedef struct {
    Ponto itens[MAX_NODOS];
    int frente, tras;
} Fila;

// Labirinto: 1 = caminho, 0 = parede
int labirinto[LINHAS][COLUNAS] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1}
};

// Visitados e antecessores
int visitado[LINHAS][COLUNAS];
Ponto antecessor[LINHAS][COLUNAS];

// Direções: cima, baixo, esquerda, direita
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Funções para fila (BFS)
void inicializarFila(Fila* f) {
    f->frente = -1;
    f->tras = -1;
}

int estaVazia(Fila* f) {
    return f->frente == -1;
}

void enfileirar(Fila* f, Ponto p) {
    if (f->tras == MAX_NODOS - 1) return;
    if (f->frente == -1) f->frente = 0;
    f->itens[++f->tras] = p;
}

Ponto desenfileirar(Fila* f) {
    Ponto p = {-1, -1};
    if (estaVazia(f)) return p;
    p = f->itens[f->frente++];
    if (f->frente > f->tras) f->frente = f->tras = -1;
    return p;
}

// Verifica se posição é válida
int valido(int x, int y) {
    return x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS &&
           labirinto[x][y] == 1 && !visitado[x][y];
}

// Exibe o caminho visualmente
void mostrarCaminho(Ponto inicio, Ponto fim) {
    char visual[LINHAS][COLUNAS];

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] == 0)
                visual[i][j] = '#';
            else
                visual[i][j] = ' ';
        }
    }

    // Reconstrói o caminho
    Ponto atual = fim;
    while (!(atual.x == inicio.x && atual.y == inicio.y)) {
        visual[atual.x][atual.y] = '*';
        atual = antecessor[atual.x][atual.y];
    }

    visual[inicio.x][inicio.y] = 'S';
    visual[fim.x][fim.y] = 'E';

    printf("\nLabirinto com caminho:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%c ", visual[i][j]);
        }
        printf("\n");
    }
}

// ================= BFS =================
void BFS(Ponto inicio, Ponto fim) {
    Fila f;
    inicializarFila(&f);

    enfileirar(&f, inicio);
    visitado[inicio.x][inicio.y] = 1;

    while (!estaVazia(&f)) {
        Ponto atual = desenfileirar(&f);
        if (atual.x == fim.x && atual.y == fim.y) {
            mostrarCaminho(inicio, fim);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            if (valido(nx, ny)) {
                visitado[nx][ny] = 1;
                antecessor[nx][ny] = atual;
                enfileirar(&f, (Ponto){nx, ny});
            }
        }
    }

    printf("Caminho não encontrado.\n");
}

// ================= DFS =================
int encontrouDFS = 0;

void DFS(Ponto atual, Ponto fim) {
    if (encontrouDFS) return;

    visitado[atual.x][atual.y] = 1;

    if (atual.x == fim.x && atual.y == fim.y) {
        encontrouDFS = 1;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = atual.x + dx[i];
        int ny = atual.y + dy[i];

        if (valido(nx, ny)) {
            antecessor[nx][ny] = atual;
            DFS((Ponto){nx, ny}, fim);
        }
    }
}

// ================= Menu Principal =================
void limparVisitados() {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            visitado[i][j] = 0;
}

int main() {
    Ponto inicio = {0, 0};  // 'S'
    Ponto fim = {2, 3};     // 'E'

    int escolha;
    printf("=== Navegação em Labirintos ===\n");
    printf("1 - Busca em Largura (BFS)\n");
    printf("2 - Busca em Profundidade (DFS)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    limparVisitados();

    if (escolha == 1) {
        printf("\n== Caminho usando BFS ==\n");
        BFS(inicio, fim);
    } else if (escolha == 2) {
        printf("\n== Caminho usando DFS ==\n");
        encontrouDFS = 0;
        DFS(inicio, fim);

        if (encontrouDFS)
            mostrarCaminho(inicio, fim);
        else
            printf("Caminho não encontrado.\n");
    } else {
        printf("Opção inválida.\n");
    }

    return 0;
}
