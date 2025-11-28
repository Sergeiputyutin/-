/* Задание 1
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

typedefstructNode{
int data;
structNode* next;
} Node;

typedefstructQueue{
Node * front;
Node* rear;
} Queue;

typedefstructAdjListNode{
int dest;
structAdjListNode* next;
} AdjListNode;

typedefstructAdjList{
AdjListNode * head;
} AdjList;

typedefstructGraph{
int numVertices;
AdjList* array;
} Graph;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

bool isEmpty(Queue* q) {
    returnq->front == NULL;
}

void enqueue(Queue* q, intdata) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }

    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

int** generateAdjacencyMatrix(intn, doubledensity) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)rand() / RAND_MAX < density) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

void printMatrix(int** matrix, intn) {
    printf("Матрица смежности графа G (%dx%d):\n", n, n);
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%3d", i);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d:", i);
        for (int j = 0; j < n; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Graph* createGraph(intnumVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, intsrc, intdest) {

    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = src;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

Graph* matrixToAdjacencyList(int** matrix, intn) {
    Graph* graph = createGraph(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }

    return graph;
}

void printAdjacencyList(Graph* graph) {
    printf("Спискисмежностиграфа G:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        AdjListNode* currentNode = graph->array[i].head;
        while (currentNode != NULL) {
            printf("%d", currentNode->dest);
            currentNode = currentNode->next;
            if (currentNode != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void BFS_matrix(int** G, intsize_G) {
    bool* NUM = (bool*)malloc(size_G * sizeof(bool));
    for (int i = 0; i < size_G; i++) {
        NUM[i] = false;
    }

    Queue* Q = createQueue();

    printf("Обход в ширину (матрица смежности) ===\n");
    printf("Порядок обхода вершин: ");


    for (int start = 0; start < size_G; start++) {
        if (!NUM[start]) {

            enqueue(Q, start);
            NUM[start] = true;

            while (!isEmpty(Q)) {

                int v = Q->front->data;


                dequeue(Q);


                printf("%d ", v);


                for (int i = 0; i < size_G; i++) {

                    if (G[v][i] == 1 && !NUM[i]) {

                        enqueue(Q, i);


                        NUM[i] = true;
                    }
                }
            }
        }
    }

    printf("\n\n");
    free(NUM);
    free(Q);
}

void BFS_adjacency_list(Graph* graph) {
    int size_G = graph->numVertices;
    bool* NUM = (bool*)malloc(size_G * sizeof(bool));
    for (int i = 0; i < size_G; i++) {
        NUM[i] = false;
    }

    Queue* Q = createQueue();

    printf("Обход в ширину (списки смежности) ===\n");
    printf("Порядок обхода вершин: ");


    for (int start = 0; start < size_G; start++) {
        if (!NUM[start]) {
            enqueue(Q, start);
            NUM[start] = true;
            while (!isEmpty(Q)) {
                int v = Q->front->data;
                dequeue(Q);
                printf("%d ", v);


                AdjListNode* currentNode = graph->array[v].head;
                while (currentNode != NULL) {
                    int i = currentNode->dest;


                    if (!NUM[i]) {

                        enqueue(Q, i);


                        NUM[i] = true;
                    }
                    currentNode = currentNode->next;
                }
            }
        }
    }

    printf("\n\n");
    free(NUM);
    free(Q);
}

void freeMatrix(int** matrix, intn) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        AdjListNode* currentNode = graph->array[i].head;
        while (currentNode != NULL) {
            AdjListNode* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    srand(time(NULL));

    int n = 6;
    double density = 0.3;

    printf("=========================================\n");
    printf("        ОБХОД ГРАФА В ШИРИНУ (BFS)\n");
    printf("=========================================\n\n");


    printf("Генерация матрицы смежности ===\n");
    int** adjMatrix = generateAdjacencyMatrix(n, density);
    printMatrix(adjMatrix, n);


    BFS_matrix(adjMatrix, n);


    printf("Нажмите Enter дляпродолжения");
    getchar();


    printf("\n");
    Graph* graph = matrixToAdjacencyList(adjMatrix, n);
    printAdjacencyList(graph);
    BFS_adjacency_list(graph);


    freeMatrix(adjMatrix, n);
    freeGraph(graph);

    return 0;
}



Задание 2
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <queue> // Добавляем стандартную библиотеку queue

using namespace std;

// Переименовал вашу очередь в MyQueue
struct MyNode {
    int data;
    struct MyNode* next;
};

struct MyQueue {
    struct MyNode* front;
    struct MyNode* rear;
};

void init_myqueue(struct MyQueue* q) {
    q->front = q->rear = NULL;
}

void enqueue_myqueue(struct MyQueue* q, int value) {
    struct MyNode* new_node = (struct MyNode*)malloc(sizeof(struct MyNode));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    new_node->data = value;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    }
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

int dequeue_myqueue(struct MyQueue* q) {
    if (q->front == NULL) {
        printf("Очередь пуста\n");
        return -1;
    }
    struct MyNode* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int is_empty_myqueue(struct MyQueue* q) {
    return q->front == NULL;
}

void free_myqueue(struct MyQueue* q) {
    while (!is_empty_myqueue(q)) {
        dequeue_myqueue(q);
    }
}

void generate_random_graph(int** graph, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 100 < 30) {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
}

void print_graph(int** graph, int n) {
    printf("\nМатрица смежности графа (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// BFS с вашей очередью (переименованной в MyQueue)
void BFS_myqueue(int start, int** graph, int n) {
    struct MyQueue q;
    init_myqueue(&q);

    int* visited = (int*)malloc(n * sizeof(int));
    if (visited == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    visited[start] = 1;
    enqueue_myqueue(&q, start);

    printf("Порядок обхода BFS с MyQueue (начиная с вершины %d): ", start);

    while (!is_empty_myqueue(&q)) {
        int current = dequeue_myqueue(&q);
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue_myqueue(&q, i);
            }
        }
    }
    printf("\n");

    free(visited);
    free_myqueue(&q);
}

// BFS со стандартной очередью из библиотеки
void BFS_std_queue(int start, int** graph, int n) {
    queue<int> q; // Стандартная очередь C++

    int* visited = (int*)malloc(n * sizeof(int));
    if (visited == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    visited[start] = 1;
    q.push(start);

    printf("Порядок обхода BFS со StdQueue (начиная с вершины %d): ", start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                q.push(i);
            }
        }
    }
    printf("\n");

    free(visited);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;

    printf("=== Сравнение алгоритма BFS с MyQueue и StdQueue ===\n");
    printf("Введите количество вершин графа: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: количество вершин должно быть положительным числом\n");
        return 1;
    }

    srand(time(NULL));

    int** graph = (int**)malloc(n * sizeof(int*));
    if (graph == NULL) {
        printf("Ошибка выделения памяти для графа\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
        if (graph[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d\n", i);
            for (int j = 0; j < i; j++) {
                free(graph[j]);
            }
            free(graph);
            return 1;
        }

        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    generate_random_graph(graph, n);
    print_graph(graph, n);

    // Тестирование MyQueue (вашей очереди)
    printf("\n--- Тестирование MyQueue ---\n");
    clock_t start_myqueue = clock();
    BFS_myqueue(0, graph, n);
    clock_t end_myqueue = clock();
    double time_myqueue = (double)(end_myqueue - start_myqueue) / CLOCKS_PER_SEC;

    // Тестирование StdQueue (стандартной очереди)
    printf("\n--- Тестирование StdQueue ---\n");
    clock_t start_stdqueue = clock();
    BFS_std_queue(0, graph, n);
    clock_t end_stdqueue = clock();
    double time_stdqueue = (double)(end_stdqueue - start_stdqueue) / CLOCKS_PER_SEC;

    // Вывод результатов сравнения
    printf("\n=== РЕЗУЛЬТАТЫ СРАВНЕНИЯ ===\n");
    printf("Время выполнения BFS с MyQueue: %f секунд\n", time_myqueue);
    printf("Время выполнения BFS со StdQueue: %f секунд\n", time_stdqueue);
    printf("Разница: %f секунд\n", time_myqueue - time_stdqueue);

    if (time_myqueue < time_stdqueue) {
        printf("MyQueue быстрее на %.2f%%\n",
               ((time_stdqueue - time_myqueue) / time_stdqueue) * 100);
    } else {
        printf("StdQueue быстрее на %.2f%%\n",
               ((time_myqueue - time_stdqueue) / time_myqueue) * 100);
    }

    printf("Размер графа: %d вершин\n", n);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
*/