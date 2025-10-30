#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void DFS(int** G, int numG, int* visited, int s) {
    visited[s] = 1;
    printf("%3d", s);
    for (int i = 0; i < numG; i++) {
        if (G[s][i] == 1 && visited[i] == 0) {
            DFS(G, numG, visited, i);
        }
    }
}

int main() {
    int** G;
    int* visited;
    int numG;
    int current;

    setlocale(LC_ALL, "Russian");

    srand(time(NULL));

    printf("Введите кол-во вершин: ");
    scanf("%d", &numG);

    G = (int**)malloc(numG * sizeof(int*));
    visited = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    
    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
        for (int j = i; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0; 
            }
            else {
                G[i][j] = G[j][i] = rand() % 2; 
            }
        }
    }

    
    printf("\nМатрица смежности:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", G[i][j]); 
        }
        printf("\n");
    }

    printf("\nВведите номер вершины: ");
    scanf("%d", &current);

    printf("\nПорядок обхода в глубину: ");
    DFS(G, numG, visited, current);
    printf("\n");

    return 0;
}