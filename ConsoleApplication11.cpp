#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<locale.h>

typedef struct QueueNode {
    int vertex;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int vertex) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->vertex = vertex;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }

    QueueNode* temp = q->front;
    int vertex = temp->vertex;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return vertex;
}

void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

int** generateAdjacencyMatrix(int n, int isDirected, int maxWeight) {
    int** matrix = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    double edgeProbability = 0.6;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
                continue;
            }

            if ((double)rand() / RAND_MAX < edgeProbability) {
                int weight = 1 + rand() % maxWeight;
                matrix[i][j] = weight;

                if (!isDirected) {
                    matrix[j][i] = weight;
                }
            }
        }
    }

    if (isDirected) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && matrix[i][j] == 0 && (double)rand() / RAND_MAX < edgeProbability * 0.3) {
                    matrix[i][j] = 1 + rand() % maxWeight;
                }
            }
        }
    }

    return matrix;
}

void printMatrix(int** matrix, int n, const char* graphType) {
    printf("\n=== Матрица смежности %s графа ===\n", graphType);
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%4d ", i);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int* BFSD(int** G, int n, int v) {
    int* DIST = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        DIST[i] = -1;
    }

    Queue* Q = createQueue();
    enqueue(Q, v);
    DIST[v] = 0;

    while (!isEmpty(Q)) {
        int current_v = dequeue(Q);

        for (int i = 0; i < n; i++) {
            if (G[current_v][i] > 0 && DIST[i] == -1) {
                enqueue(Q, i);
                DIST[i] = DIST[current_v] + G[current_v][i];
            }
        }
    }

    freeQueue(Q);
    return DIST;
}

int** findAllDistances(int** graph, int n) {
    int** allDist = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        allDist[i] = BFSD(graph, n, i);
    }

    return allDist;
}

int eccentricity(int* distances, int n) {
    int maxDist = -1;
    for (int i = 0; i < n; i++) {
        if (distances[i] > maxDist) {
            maxDist = distances[i];
        }
    }
    return maxDist;
}

void analyzeGraph(int** graph, int n, const char* graphType) {
    printf("\n=== Анализ %s графа ===\n", graphType);

    int** allDist = findAllDistances(graph, n);

    printf("\nМатрица расстояний (сумма весов ребер):\n");
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%5d ", i);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < n; j++) {
            if (allDist[i][j] == -1) {
                printf("   INF ");
            }
            else {
                printf("%5d ", allDist[i][j]);
            }
        }
        printf("\n");
    }

    int* ecc = (int*)malloc(n * sizeof(int));
    printf("\nЭксцентриситеты вершин:\n");
    for (int i = 0; i < n; i++) {
        ecc[i] = eccentricity(allDist[i], n);
        printf("Вершина %d: e = ", i);
        if (ecc[i] == -1) {
            printf("INF (не связана со всеми вершинами)\n");
        }
        else {
            printf("%d\n", ecc[i]);
        }
    }

    int radius = INT_MAX;
    int diameter = -1;

    for (int i = 0; i < n; i++) {
        if (ecc[i] != -1 && ecc[i] < radius) {
            radius = ecc[i];
        }
        if (ecc[i] > diameter) {
            diameter = ecc[i];
        }
    }

    if (radius == INT_MAX) {
        radius = -1;
    }

    printf("\nРадиус графа: ");
    if (radius == -1) {
        printf("граф не связен\n");
    }
    else {
        printf("%d\n", radius);
    }

    printf("Диаметр графа: ");
    if (diameter == -1) {
        printf("граф не связен\n");
    }
    else {
        printf("%d\n", diameter);
    }

    printf("\nЦентральные вершины ");
    if (radius != -1) {
        printf("(e = радиус = %d):\n", radius);
        int hasCentral = 0;
        for (int i = 0; i < n; i++) {
            if (ecc[i] == radius) {
                printf("%d ", i);
                hasCentral = 1;
            }
        }
        if (!hasCentral) {
            printf("нет");
        }
    }
    else {
        printf(": нет (граф не связен)");
    }
    printf("\n");

    printf("\nПериферийные вершины ");
    if (diameter != -1) {
        printf("(e = диаметр = %d):\n", diameter);
        int hasPeripheral = 0;
        for (int i = 0; i < n; i++) {
            if (ecc[i] == diameter) {
                printf("%d ", i);
                hasPeripheral = 1;
            }
        }
        if (!hasPeripheral) {
            printf("нет");
        }
    }
    else {
        printf(": нет (граф не связен)");
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(allDist[i]);
    }
    free(allDist);
    free(ecc);
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

void processGraph(int graphType, int n, int startVertex) {
    int maxWeight = 10;
    int** graph = NULL;
    const char* typeName = "";

    if (graphType == 1) {
        typeName = "неориентированного";
        graph = generateAdjacencyMatrix(n, 0, maxWeight);
    }
    else if (graphType == 2) {
        typeName = "ориентированного";
        graph = generateAdjacencyMatrix(n, 1, maxWeight);
    }

    if (graph == NULL) {
        printf("Ошибка создания графа!\n");
        return;
    }

    printMatrix(graph, n, typeName);

    printf("\nПоиск расстояний от вершины %d (сумма весов ребер):\n", startVertex);
    int* distances = BFSD(graph, n, startVertex);

    for (int i = 0; i < n; i++) {
        printf("Расстояние до вершины %d: ", i);
        if (distances[i] >= 0) {
            printf("%d\n", distances[i]);
        }
        else {
            printf("недостижима\n");
        }
    }
    free(distances);

    printf("\n=== Анализ графа ===\n");
    analyzeGraph(graph, n, typeName);


    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
}

void showMenu() {
    printf("\n");
    printf("1. Работать с неориентированным графом  \n");
    printf("2. Работать с ориентированным графом    \n");
    printf("3. Работать с обоими графами            \n");
    printf("Выберите опцию (1-4): ");
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int n = 0;
    int startVertex = 0;
    int choice = 0;

    printf("=========================================\n");
    printf("    Поиск расстояний во взвешенном графе\n");
    printf("=========================================\n");


    printf("\nВведите количество вершин в графе: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некорректный ввод! Введите положительное целое число: ");
        clearInputBuffer();
    }


    printf("Введите номер начальной вершины для обхода (0-%d): ", n - 1);
    while (scanf("%d", &startVertex) != 1 || startVertex < 0 || startVertex >= n) {
        printf("Некорректный ввод! Введите число от 0 до %d: ", n - 1);
        clearInputBuffer();
    }

    do {
        showMenu();
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf("Некорректный ввод! Выберите опцию от 1 до 4: ");
            clearInputBuffer();
        }

        switch (choice) {
        case 1:
            printf("\nВы выбрали работу с неориентированным графом\n");
            processGraph(1, n, startVertex);
            break;

        case 2:
            printf("\nВы выбрали работу с ориентированным графом\n");
            processGraph(2, n, startVertex);
            break;

        case 3:
            printf("\nВы выбрали работу с обоими графами\n");

            printf("\n=== НЕОРИЕНТИРОВАННЫЙ ГРАФ ===\n");
            processGraph(1, n, startVertex);

            printf("\n\n=== ОРИЕНТИРОВАННЫЙ ГРАФ ===\n");
            processGraph(2, n, startVertex);
            break;

        case 4:
            printf("\nВыход из программы...\n");
            break;

        default:
            printf("\nНеверный выбор!\n");
            break;
        }

        if (choice != 4) {
            printf("\nНажмите Enter для продолжения...");
            clearInputBuffer();
            getchar();
        }

    } while (choice != 4);

    return 0;
}
