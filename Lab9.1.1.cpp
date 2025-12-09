/* ЗАДАНИЕ 1
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <queue>  

using namespace std;

#define SIZE 10 

struct Node {
    int vertex;
    struct Node* next;
};

void generateGraph(int graph[SIZE][SIZE]) {
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            if (i == j) {
                graph[i][j] = 0; 
            }
            else {
                graph[i][j] = graph[j][i] = rand() % 10 < 3;
            }
        }
    }
}

void printGraph(int graph[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrixToAdjList(int graph[SIZE][SIZE], struct Node* adjList[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < SIZE; j++) {
            if (graph[i][j] == 1) {
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;
            }
        }
    }
}

void printAdjList(struct Node* adjList[SIZE]) {
    printf("Списки смежности:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Вершина %d: ", i);
        struct Node* current = adjList[i];
        while (current != NULL) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}

void BFSD_matrix(int graph[SIZE][SIZE], int start, int dist[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        dist[i] = -1;
    }

    queue<int> q;  

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < SIZE; i++) {
            if (graph[current][i] == 1 && dist[i] == -1) {
                q.push(i);
                dist[i] = dist[current] + 1;
            }
        }
    }
}

void BFSD_adjList(struct Node* adjList[SIZE], int start, int dist[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        dist[i] = -1;
    }

    queue<int> q; 

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        struct Node* temp = adjList[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (dist[neighbor] == -1) {
                q.push(neighbor);
                dist[neighbor] = dist[current] + 1;
            }
            temp = temp->next;
        }
    }
}

void printDistances(int dist[SIZE], int start, const char* title) {
    printf("%s от вершины %d:\n", title, start);
    for (int i = 0; i < SIZE; i++) {
        printf("До вершины %d: ", i);
        if (dist[i] == -1) {
            printf("нет пути\n");
        }
        else {
            printf("%d\n", dist[i]);
        }
    }
    printf("\n");
}

void freeAdjList(struct Node* adjList[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        struct Node* current = adjList[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(42);  

    int graph[SIZE][SIZE];
    int dist_matrix[SIZE], dist_list[SIZE];
    int start_vertex = 0;

    struct Node* adjList[SIZE];

    generateGraph(graph);
    printGraph(graph);

    BFSD_matrix(graph, start_vertex, dist_matrix);
    printDistances(dist_matrix, start_vertex, "Расстояния (матрица смежности)");

    matrixToAdjList(graph, adjList);
    printAdjList(adjList);

    BFSD_adjList(adjList, start_vertex, dist_list);
    printDistances(dist_list, start_vertex, "Расстояния (списки смежности)");

    freeAdjList(adjList);

    return 0;
}
*/






/* ЗАДАНИЕ 2#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stack>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define SIZE 7
#define START_VERTEX 0

struct Node {
    int vertex;
    Node* next;
};

void generateGraph(int graph[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = graph[j][i] = rand() % 100 < 30;
            }
        }
    }
}

void printGraph(int graph[SIZE][SIZE]) {
    printf("Матрица смежности графа (%dx%d):\n", SIZE, SIZE);
    printf("    ");
    for (int i = 0; i < SIZE; i++) printf("V%-2d", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("V%-2d:", i);
        for (int j = 0; j < SIZE; j++) {
            printf(" %2d", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrixToAdjList(int graph[SIZE][SIZE], Node* adjList[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < SIZE; j++) {
            if (graph[i][j] == 1) {
                Node* newNode = new Node;
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;
            }
        }
    }
}

void DFSD_matrix(int graph[SIZE][SIZE], int start, int dist[SIZE]) {
    for (int i = 0; i < SIZE; i++) dist[i] = -1;

    stack<pair<int, int>> s;
    s.push({ start, 0 });
    dist[start] = 0;

    while (!s.empty()) {
        int current = s.top().first;
        int currentDist = s.top().second;
        s.pop();

        for (int i = 0; i < SIZE; i++) {
            if (graph[current][i] == 1 && dist[i] == -1) {
                dist[i] = currentDist + 1;
                s.push({ i, currentDist + 1 });
            }
        }
    }
}

void DFSD_matrix_dynamic(int** graph, int size, int start, int* dist) {
    for (int i = 0; i < size; i++) dist[i] = -1;

    stack<pair<int, int>> s;
    s.push({ start, 0 });
    dist[start] = 0;

    while (!s.empty()) {
        int current = s.top().first;
        int currentDist = s.top().second;
        s.pop();

        for (int i = 0; i < size; i++) {
            if (graph[current][i] == 1 && dist[i] == -1) {
                dist[i] = currentDist + 1;
                s.push({ i, currentDist + 1 });
            }
        }
    }
}

void DFSD_adjList_dynamic(Node** adjList, int size, int start, int* dist) {
    for (int i = 0; i < size; i++) dist[i] = -1;

    stack<pair<int, int>> s;
    s.push({ start, 0 });
    dist[start] = 0;

    while (!s.empty()) {
        int current = s.top().first;
        int currentDist = s.top().second;
        s.pop();

        Node* temp = adjList[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (dist[neighbor] == -1) {
                dist[neighbor] = currentDist + 1;
                s.push({ neighbor, currentDist + 1 });
            }
            temp = temp->next;
        }
    }
}

void DFSD_adjList(Node* adjList[SIZE], int start, int dist[SIZE]) {
    for (int i = 0; i < SIZE; i++) dist[i] = -1;

    stack<pair<int, int>> s;
    s.push({ start, 0 });
    dist[start] = 0;

    while (!s.empty()) {
        int current = s.top().first;
        int currentDist = s.top().second;
        s.pop();

        Node* temp = adjList[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (dist[neighbor] == -1) {
                dist[neighbor] = currentDist + 1;
                s.push({ neighbor, currentDist + 1 });
            }
            temp = temp->next;
        }
    }
}

void BFSD_matrix_dynamic(int** graph, int size, int start, int* dist) {
    for (int i = 0; i < size; i++) dist[i] = -1;

    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < size; i++) {
            if (graph[current][i] == 1 && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                q.push(i);
            }
        }
    }
}

void BFSD_matrix(int graph[SIZE][SIZE], int start, int dist[SIZE]) {
    for (int i = 0; i < SIZE; i++) dist[i] = -1;

    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < SIZE; i++) {
            if (graph[current][i] == 1 && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                q.push(i);
            }
        }
    }
}

void printDistances(int dist[SIZE], const char* algorithm) {
    printf("%s:\n", algorithm);
    printf("Вершина: ");
    for (int i = 0; i < SIZE; i++) {
        printf("V%-2d ", i);
    }
    printf("\nРасстояние: ");
    for (int i = 0; i < SIZE; i++) {
        if (dist[i] == -1) printf(" -  ");
        else printf("%-3d ", dist[i]);
    }
    printf("\n\n");
}

void freeAdjList(Node* adjList[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        Node* current = adjList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

double measureTime(int size, bool useDFS, bool useAdjList) {
    int** graph = new int* [size];
    for (int i = 0; i < size; i++) {
        graph[i] = new int[size];
        for (int j = 0; j < size; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = rand() % 100 < 20;
        }
    }

    Node** adjList = NULL;
    if (useAdjList) {
        adjList = new Node * [size];
        for (int i = 0; i < size; i++) {
            adjList[i] = NULL;
            for (int j = 0; j < size; j++) {
                if (graph[i][j] == 1) {
                    Node* newNode = new Node;
                    newNode->vertex = j;
                    newNode->next = adjList[i];
                    adjList[i] = newNode;
                }
            }
        }
    }

    int* dist = new int[size];

    auto start = high_resolution_clock::now();

    if (useDFS) {
        if (useAdjList) {
            DFSD_adjList_dynamic(adjList, size, 0, dist);
        }
        else {
            DFSD_matrix_dynamic(graph, size, 0, dist);
        }
    }
    else {
        BFSD_matrix_dynamic(graph, size, 0, dist);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    delete[] dist;
    for (int i = 0; i < size; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    if (useAdjList) {
        for (int i = 0; i < size; i++) {
            Node* current = adjList[i];
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;
    }

    return duration.count() / 1000.0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(42);


    int graph[SIZE][SIZE];
    Node* adjList[SIZE] = { NULL };

    generateGraph(graph);
    printGraph(graph);

    matrixToAdjList(graph, adjList);

    int dist_dfs_matrix[SIZE];
    int dist_dfs_list[SIZE];
    int dist_bfs[SIZE];

    printf("1. Результаты поиска расстояний (от вершины V%d):\n", START_VERTEX);

    DFSD_matrix(graph, START_VERTEX, dist_dfs_matrix);
    printDistances(dist_dfs_matrix, "DFS на матрице смежности");

    DFSD_adjList(adjList, START_VERTEX, dist_dfs_list);
    printDistances(dist_dfs_list, "DFS на списках смежности");

    BFSD_matrix(graph, START_VERTEX, dist_bfs);
    printDistances(dist_bfs, "BFS на матрице смежности");

    printf("\n2. Оценка времени работы (в миллисекундах):\n");
    printf("Размер графа | DFS (матрица) | DFS (списки) | BFS (матрица)\n");
    printf("-----------------------------------------------------------\n");

    int sizes[] = { 100, 200, 300, 400 };
    for (int size : sizes) {
        double time_dfs_matrix = measureTime(size, true, false);
        double time_dfs_list = measureTime(size, true, true);
        double time_bfs = measureTime(size, false, false);

        printf("%11d | %13.2f | %12.2f | %13.2f\n",
            size, time_dfs_matrix, time_dfs_list, time_bfs);
    }

    freeAdjList(adjList);

    printf("\nНажмите Enter для выхода...");
    getchar();

    return 0;
}




Дополнительное задание*/
//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <stack>
//#include <queue>
//#include <chrono>
//
//using namespace std;
//using namespace std::chrono;
//
//struct Node {
//    int vertex;
//    Node* next;
//};
//
//void generateGraph(int** graph, int size) {
//    for (int i = 0; i < size; i++) {
//        for (int j = i; j < size; j++) {
//            if (i == j) {
//                graph[i][j] = 0;
//            }
//            else {
//                graph[i][j] = graph[j][i] = rand() % 100 < 30;
//            }
//        }
//    }
//}
//
//void printGraph(int** graph, int size) {
//    printf("Матрица смежности графа (%dx%d):\n", size, size);
//    printf("    ");
//    for (int i = 0; i < size; i++) printf("V%-2d", i);
//    printf("\n");
//
//    for (int i = 0; i < size; i++) {
//        printf("V%-2d:", i);
//        for (int j = 0; j < size; j++) {
//            printf(" %2d", graph[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}
//
//void matrixToAdjList(int** graph, Node** adjList, int size) {
//    for (int i = 0; i < size; i++) {
//        adjList[i] = NULL;
//        for (int j = 0; j < size; j++) {
//            if (graph[i][j] == 1) {
//                Node* newNode = new Node;
//                newNode->vertex = j;
//                newNode->next = adjList[i];
//                adjList[i] = newNode;
//            }
//        }
//    }
//}
//
//void DFS_matrix(int** graph, int size, int start, int* dist) {
//    for (int i = 0; i < size; i++) dist[i] = -1;
//
//    stack<pair<int, int>> s;
//    s.push({ start, 0 });
//    dist[start] = 0;
//
//    while (!s.empty()) {
//        int current = s.top().first;
//        int currentDist = s.top().second;
//        s.pop();
//
//        for (int i = 0; i < size; i++) {
//            if (graph[current][i] == 1 && dist[i] == -1) {
//                dist[i] = currentDist + 1;
//                s.push({ i, currentDist + 1 });
//            }
//        }
//    }
//}
//
//void BFS_matrix(int** graph, int size, int start, int* dist) {
//    for (int i = 0; i < size; i++) dist[i] = -1;
//
//    queue<int> q;
//    q.push(start);
//    dist[start] = 0;
//
//    while (!q.empty()) {
//        int current = q.front();
//        q.pop();
//
//        for (int i = 0; i < size; i++) {
//            if (graph[current][i] == 1 && dist[i] == -1) {
//                dist[i] = dist[current] + 1;
//                q.push(i);
//            }
//        }
//    }
//}
//
//void BFS_adjList(Node** adjList, int size, int start, int* dist) {
//    for (int i = 0; i < size; i++) dist[i] = -1;
//
//    queue<int> q;
//    q.push(start);
//    dist[start] = 0;
//
//    while (!q.empty()) {
//        int current = q.front();
//        q.pop();
//
//        Node* temp = adjList[current];
//        while (temp != NULL) {
//            int neighbor = temp->vertex;
//            if (dist[neighbor] == -1) {
//                dist[neighbor] = dist[current] + 1;
//                q.push(neighbor);
//            }
//            temp = temp->next;
//        }
//    }
//}
//
//void printDistances(int* dist, int size, const char* algorithm) {
//    printf("%s:\n", algorithm);
//    printf("Вершина: ");
//    for (int i = 0; i < size; i++) {
//        printf("V%-2d ", i);
//    }
//    printf("\nРасстояние: ");
//    for (int i = 0; i < size; i++) {
//        if (dist[i] == -1) printf(" -  ");
//        else printf("%-3d ", dist[i]);
//    }
//    printf("\n\n");
//}
//
//double measureTime_DFS_matrix(int size) {
//    int** graph = new int* [size];
//    for (int i = 0; i < size; i++) {
//        graph[i] = new int[size];
//    }
//    generateGraph(graph, size);
//
//    int* dist = new int[size];
//    int start_vertex = 0;
//
//    auto start = high_resolution_clock::now();
//    DFS_matrix(graph, size, start_vertex, dist);
//    auto end = high_resolution_clock::now();
//    auto duration = duration_cast<microseconds>(end - start);
//
//    delete[] dist;
//    for (int i = 0; i < size; i++) {
//        delete[] graph[i];
//    }
//    delete[] graph;
//
//    return duration.count() / 1000.0;
//}
//
//double measureTime_BFS_matrix(int size) {
//    int** graph = new int* [size];
//    for (int i = 0; i < size; i++) {
//        graph[i] = new int[size];
//    }
//    generateGraph(graph, size);
//
//    int* dist = new int[size];
//    int start_vertex = 0;
//
//    auto start = high_resolution_clock::now();
//    BFS_matrix(graph, size, start_vertex, dist);
//    auto end = high_resolution_clock::now();
//    auto duration = duration_cast<microseconds>(end - start);
//
//    delete[] dist;
//    for (int i = 0; i < size; i++) {
//        delete[] graph[i];
//    }
//    delete[] graph;
//
//    return duration.count() / 1000.0;
//}
//
//double measureTime_BFS_adjList(int size) {
//    int** graph = new int* [size];
//    for (int i = 0; i < size; i++) {
//        graph[i] = new int[size];
//    }
//    generateGraph(graph, size);
//
//    Node** adjList = new Node * [size];
//    matrixToAdjList(graph, adjList, size);
//
//    int* dist = new int[size];
//    int start_vertex = 0;
//
//    auto start = high_resolution_clock::now();
//    BFS_adjList(adjList, size, start_vertex, dist);
//    auto end = high_resolution_clock::now();
//    auto duration = duration_cast<microseconds>(end - start);
//
//    delete[] dist;
//    for (int i = 0; i < size; i++) {
//        delete[] graph[i];
//    }
//    delete[] graph;
//
//    for (int i = 0; i < size; i++) {
//        Node* current = adjList[i];
//        while (current != NULL) {
//            Node* temp = current;
//            current = current->next;
//            delete temp;
//        }
//    }
//    delete[] adjList;
//
//    return duration.count() / 1000.0;
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    srand(42);
//
//    int size;
//    printf("Введите количество вершин графа: ");
//    scanf_s("%d", &size);
//
//    if (size <= 0) {
//        printf("Количество вершин должно быть положительным числом!\n");
//        return 1;
//    }
//
//    int** graph = new int* [size];
//    for (int i = 0; i < size; i++) {
//        graph[i] = new int[size];
//    }
//    generateGraph(graph, size);
//    printGraph(graph, size);
//
//    Node** adjList = new Node * [size];
//    matrixToAdjList(graph, adjList, size);
//
//    int* dist_dfs_matrix = new int[size];
//    DFS_matrix(graph, size, 0, dist_dfs_matrix);
//    printDistances(dist_dfs_matrix, size, "DFS на матрице смежности");
//
//    int* dist_bfs_matrix = new int[size];
//    BFS_matrix(graph, size, 0, dist_bfs_matrix);
//    printDistances(dist_bfs_matrix, size, "BFS на матрице смежности");
//
//    int* dist_bfs_adjList = new int[size];
//    BFS_adjList(adjList, size, 0, dist_bfs_adjList);
//    printDistances(dist_bfs_adjList, size, "BFS на списках смежности");
//
//    printf("\n=== 3. Измерение времени обхода графа (в миллисекундах) ===\n");
//    printf("+--------------+-----------------+------------------+-----------------+\n");
//    printf("| %-12s | %-15s | %-16s | %-15s |\n", "Вершин", "DFS (матрица)", "BFS (матрица)", "BFS (списки)");
//    printf("+--------------+-----------------+------------------+-----------------+\n");
//
//    double time_dfs_matrix = measureTime_DFS_matrix(size);
//    double time_bfs_matrix = measureTime_BFS_matrix(size);
//    double time_bfs_adjList = measureTime_BFS_adjList(size);
//
//    printf("| %-12d | %-15.3f | %-16.3f | %-15.3f |\n",
//        size, time_dfs_matrix, time_bfs_matrix, time_bfs_adjList);
//    printf("+--------------+-----------------+------------------+-----------------+\n");
//
//    delete[] dist_dfs_matrix;
//    delete[] dist_bfs_matrix;
//    delete[] dist_bfs_adjList;
//
//    for (int i = 0; i < size; i++) {
//        delete[] graph[i];
//        Node* current = adjList[i];
//        while (current != NULL) {
//            Node* temp = current;
//            current = current->next;
//            delete temp;
//        }
//    }
//    delete[] graph;
//    delete[] adjList;
//
//    printf("\nНажмите Enter для выхода...");
//    getchar();
//    getchar();
//
//    return 0;
//}