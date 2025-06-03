#include <stdio.h>
#include <limits.h>
#include <string.h>

#define V 6  // Número de estações

// Nomes das estações
const char* estacoes[V] = {
    "Centro", "Estacao Norte", "Estacao Leste", "Estacao Sul", "Estacao Oeste", "Terminal Rodoviario"
};

// Função para encontrar o vértice com a menor distância ainda não visitado
int minDistancia(int dist[], int visitado[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Imprime o caminho recursivamente
void imprimirCaminho(int anterior[], int destino) {
    if (anterior[destino] == -1) {
        printf("%s", estacoes[destino]);
        return;
    }
    imprimirCaminho(anterior, anterior[destino]);
    printf(" -> %s", estacoes[destino]);
}

// Função que implementa o algoritmo de Dijkstra com exibição do caminho
void dijkstra(int grafo[V][V], int origem, int destino) {
    int dist[V];         // dist[i] armazena a menor distância de origem até i
    int visitado[V];     // visitado[i] é verdadeiro se o vértice já foi incluído
    int anterior[V];     // anterior[i] armazena o vértice anterior no caminho até i

    // Inicializa todas as distâncias como infinito e os vértices como não visitados
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(dist, visitado);
        if (u == -1) break;

        visitado[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[u][v] && dist[u] != INT_MAX &&
                dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    printf("\n== Resultado ==\n");
    if (dist[destino] == INT_MAX) {
        printf("Nao ha caminho entre %s e %s.\n", estacoes[origem], estacoes[destino]);
    } else {
        printf("Tempo minimo de viagem: %d minutos\n", dist[destino]);
        printf("Rota: ");
        imprimirCaminho(anterior, destino);
        printf("\n");
    }
}

void mostrarMenuEstacoes() {
    printf("Estacoes disponiveis:\n");
    for (int i = 0; i < V; i++) {
        printf("%d - %s\n", i, estacoes[i]);
    }
}

int main() {
    // Grafo representando os tempos médios entre estações
    int grafo[V][V] = {
        // C  N  L  S  O  T
        { 0, 7, 9, 0, 0,14}, // Centro
        { 0, 0,10,15, 0, 0}, // Est. Norte
        { 0, 0, 0,11, 0, 2}, // Est. Leste
        { 0, 0, 0, 0, 6, 0}, // Est. Sul
        { 0, 0, 0, 0, 0, 9}, // Est. Oeste
        { 0, 0, 0, 0, 0, 0}  // Terminal Rodoviário
    };

    int origem, destino;

    printf("=== Sistema Inteligente de Rotas para Transporte Publico ===\n");
    mostrarMenuEstacoes();

    printf("\nEscolha a estacao de origem (0 a %d): ", V - 1);
    scanf("%d", &origem);
    printf("Escolha a estacao de destino (0 a %d): ", V - 1);
    scanf("%d", &destino);

    if (origem < 0 || origem >= V || destino < 0 || destino >= V) {
        printf("Entrada invalida.\n");
        return 1;
    }

    dijkstra(grafo, origem, destino);

    return 0;
}
