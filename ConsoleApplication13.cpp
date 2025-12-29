#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#define MAX_VERTICES 50
#define FILENAME "Grafi.txt"

typedef struct {
    int adj[MAX_VERTICES][MAX_VERTICES];
    int vertices;
} Graph;

typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initGraph(Graph* g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj[i][j] = 0;
        }
    }
}

void addDirectedEdge(Graph* g, int src, int dest) {
    if (src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices) {
        g->adj[src][dest] = 1;
    }
}

void saveGraphToFile(Graph* g) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи!\n");
        return;
    }

    fprintf(file, "%d\n", g->vertices);

    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            fprintf(file, "%d ", g->adj[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Граф успешно сохранен в файл '%s'\n", FILENAME);
}

int loadGraphFromFile(Graph* g) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Файл '%s' не найден. Создайте новый граф.\n", FILENAME);
        return 0;
    }

    if (fscanf(file, "%d", &g->vertices) != 1) {
        printf("Ошибка при чтении файла!\n");
        fclose(file);
        return 0;
    }

    if (g->vertices <= 0 || g->vertices > MAX_VERTICES) {
        printf("Некорректное количество вершин в файле!\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            if (fscanf(file, "%d", &g->adj[i][j]) != 1) {
                printf("Ошибка при чтении матрицы смежности!\n");
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    printf("Граф успешно загружен из файла '%s'\n", FILENAME);
    return 1;
}

void generateRandomGraph(Graph* g, int vertices) {
    initGraph(g, vertices);
    srand(time(NULL));

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j && rand() % 2 == 0) {
                g->adj[i][j] = 1;
            }
        }
    }
}


void initQueue(Queue* q) { q->front = -1; q->rear = -1; }
bool isEmpty(Queue* q) { return q->front == -1; }

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) q->front = q->rear = -1;
    return item;
}


void BFS(Graph* g, int start, bool visited[]) {
    Queue q;
    initQueue(&q);
    visited[start] = true;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        int v = dequeue(&q);
        for (int i = 0; i < g->vertices; i++) {
            if (g->adj[v][i] && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
}


int isStronglyConnected(Graph* g) {
    for (int i = 0; i < g->vertices; i++) {
        bool visited[MAX_VERTICES] = { false };
        BFS(g, i, visited);
        for (int j = 0; j < g->vertices; j++) {
            if (!visited[j]) return 0;
        }
    }
    return 1;
}

int isWeaklyConnected(Graph* g) {
    
    bool undirected[MAX_VERTICES][MAX_VERTICES] = { false };
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj[i][j]) {
                undirected[i][j] = true;
                undirected[j][i] = true;
            }
        }
    }

    
    bool visited[MAX_VERTICES] = { false };
    Queue q;
    initQueue(&q);
    visited[0] = true;
    enqueue(&q, 0);

    while (!isEmpty(&q)) {
        int v = dequeue(&q);
        for (int i = 0; i < g->vertices; i++) {
            if (undirected[v][i] && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }

    for (int i = 0; i < g->vertices; i++) {
        if (!visited[i]) return 0;
    }
    return 1;
}


void checkConnectivity(Graph* g) {
    printf("\n=== АНАЛИЗ СВЯЗНОСТИ ОРГРАФА ===\n");

    if (isWeaklyConnected(g)) {
        printf("Орграф связный\n");
        if (isStronglyConnected(g)) {
            printf("Орграф сильно связан\n");
        }
        else {
            printf("Орграф слабо связный\n");
        }
    }
    else {
        printf("Орграф несвязный\n");
    }
}


void BFSWithDisplay(Graph* g, int startVertex) {
    bool visited[MAX_VERTICES] = { false };
    Queue q;
    initQueue(&q);

    printf("Порядок обхода BFS начиная с вершины %d: ", startVertex);
    visited[startVertex] = true;
    enqueue(&q, startVertex);

    while (!isEmpty(&q)) {
        int v = dequeue(&q);
        printf("%d ", v);
        for (int i = 0; i < g->vertices; i++) {
            if (g->adj[v][i] && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");

    printf("Недостижимые вершины: ");
    bool allReachable = true;
    for (int i = 0; i < g->vertices; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            allReachable = false;
        }
    }
    if (allReachable) {
        printf("все вершины достижимы");
    }
    printf("\n");
}

void displayGraph(Graph* g) {
    printf("\n=== Матрица смежности орграфа (%d вершин) ===\n", g->vertices);
    printf("    ");
    for (int i = 0; i < g->vertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < g->vertices; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < g->vertices; j++) {
            printf("%2d ", g->adj[i][j]);
        }
        printf("\n");
    }

    int edgeCount = 0;
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj[i][j] == 1) {
                edgeCount++;
            }
        }
    }
    printf("Всего ребер: %d\n", edgeCount);
}

void displayMenu() {
    printf("\n========================================\n");
    printf("       АЛГОРИТМ BFS ДЛЯ ОРГРАФА\n");
    printf("========================================\n");
    printf("1. Ввести количество вершин и сгенерировать случайный граф\n");
    printf("2. Показать матрицу смежности\n");
    printf("3. Выполнить BFS с заданной стартовой вершиной\n");
    printf("4. Найти все компоненты связности\n");
    printf("5. Сгенерировать новый случайный граф\n");
    printf("6. Сохранить граф в файл '%s'\n", FILENAME);
    printf("7. Загрузить граф из файла '%s'\n", FILENAME);
    printf("8. Определить тип связности графа\n");
    printf("9. Выход\n");
    printf("========================================\n");
    printf("Выберите действие: ");
}

void findAllComponents(Graph* g) {
    bool visited[MAX_VERTICES] = { false };
    int count = 0;

    printf("\n=== Все компоненты связности орграфа ===\n");
    for (int i = 0; i < g->vertices; i++) {
        if (!visited[i]) {
            printf("Компонента %d: ", ++count);

            Queue q;
            initQueue(&q);
            visited[i] = true;
            enqueue(&q, i);

            while (!isEmpty(&q)) {
                int v = dequeue(&q);
                printf("%d ", v);
                for (int j = 0; j < g->vertices; j++) {
                    if (g->adj[v][j] && !visited[j]) {
                        visited[j] = true;
                        enqueue(&q, j);
                    }
                }
            }
            printf("\n");
        }
    }
    printf("Всего компонент связности: %d\n\n", count);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    srand(time(NULL));

    Graph graph;
    int vertices = 0;
    int choice;
    bool graphInitialized = false;

    printf("=== РЕАЛИЗАЦИЯ АЛГОРИТМА BFS ДЛЯ ОРГРАФА ===\n");
    printf("Алгоритм выделения компонент связности орграфа\n");
    printf("с использованием поиска в ширину (BFS)\n");
    printf("Работа с файлом: '%s'\n\n", FILENAME);

    printf("Попытка загрузки графа из файла '%s'...\n", FILENAME);
    if (loadGraphFromFile(&graph)) {
        graphInitialized = true;
        vertices = graph.vertices;
    }

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("Введите количество вершин графа (1-%d): ", MAX_VERTICES);
            scanf("%d", &vertices);

            if (vertices < 1 || vertices > MAX_VERTICES) {
                printf("Ошибка: количество вершин должно быть от 1 до %d\n", MAX_VERTICES);
                break;
            }

            generateRandomGraph(&graph, vertices);
            graphInitialized = true;
            printf("Случайный орграф успешно сгенерирован!\n");
            displayGraph(&graph);
            checkConnectivity(&graph);
            break;
        }

        case 2:
            if (!graphInitialized) {
                printf("Ошибка: граф не инициализирован. Сначала выберите пункт 1 или 7\n");
            }
            else {
                displayGraph(&graph);
            }
            break;

        case 3:
            if (!graphInitialized) {
                printf("Ошибка: граф не инициализирован. Сначала выберите пункт 1 или 7\n");
            }
            else {
                int startVertex;
                printf("Введите стартовую вершину для BFS (0-%d): ", vertices - 1);
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= vertices) {
                    printf("Ошибка: вершина %d не существует в графе (вершины от 0 до %d)\n",
                        startVertex, vertices - 1);
                }
                else {
                    printf("\n=== BFS обход начиная с вершины %d ===\n", startVertex);
                    BFSWithDisplay(&graph, startVertex);
                }
            }
            break;

        case 4:
            if (!graphInitialized) {
                printf("Ошибка: граф не инициализирован. Сначала выберите пункт 1 или 7\n");
            }
            else {
                findAllComponents(&graph);
            }
            break;

        case 5:
            if (!graphInitialized) {
                printf("Ошибка: граф не инициализирован. Сначала выберите пункт 1 или 7\n");
            }
            else {
                printf("Генерация нового случайного графа...\n");
                generateRandomGraph(&graph, vertices);
                printf("Новый граф успешно сгенерирован!\n");
                displayGraph(&graph);
                checkConnectivity(&graph);
            }
            break;

        case 6:
            if (!graphInitialized) {
                printf("Ошибка: граф не инициализирован. Сначала создайте или загрузите граф\n");
            }
            else {
                saveGraphToFile(&graph);
            }
            break;

        case 7:
            if (loadGraphFromFile(&graph)) {
                graphInitialized = true;
                vertices = graph.vertices;
                displayGraph(&graph);
                checkConnectivity(&graph);
            }
            break;

        case 8:
            if (!graphInitialized) {
                printf("Ошибка: граф не инициализирован. Сначала создайте или загрузите граф\n");
            }
            else {
                checkConnectivity(&graph);
            }
            break;

        case 9:
            printf("Выход из программы...\n");
            if (graphInitialized) {
                char saveChoice;
                printf("Сохранить граф перед выходом? (y/n): ");
                scanf(" %c", &saveChoice);
                if (saveChoice == 'y' || saveChoice == 'Y') {
                    saveGraphToFile(&graph);
                }
            }
            break;

        default:
            printf("Ошибка: неверный выбор. Попробуйте снова.\n");
        }

    } while (choice != 9);

    return 0;
}