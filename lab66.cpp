// Задание 1-2
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <locale.h>
//
//#define SIZE 10
//
//void show_matrix(int n, int graph[SIZE][SIZE]) {
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", graph[i][j]);
//        }
//        printf("\n");
//    }
//}
//
//void show_list(int n, int graph[SIZE][SIZE]) {
//    for (int i = 0; i < n; i++) {
//        printf("%d: ", i);
//        for (int j = 0; j < n; j++) {
//            if (graph[i][j] == 1) printf("%d ", j);
//        }
//        printf("\n");
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    srand(time(NULL));
//
//    int n;
//    printf("Введите число вершин: ");
//    scanf("%d", &n);
//
//    // Создаемграф
//    int graph[SIZE][SIZE] = { 0 };
//
//    // Заполняемсимметрично
//    for (int i = 0; i < n; i++) {
//        for (int j = i + 1; j < n; j++) {
//            graph[i][j] = graph[j][i] = rand() % 2;
//        }
//    }
//
//    printf("Исходныйграф:\n");
//    printf("Матрица:\n");
//    show_matrix(n, graph);
//    printf("\nСписок:\n");
//    show_list(n, graph);
//
//    int choice;
//    int u, v;
//    int new_n;
//
//    while (1) {
//        printf("\n=== ВЫБЕРИТЕ ОПЕРАЦИЮ ===\n");
//        printf("1. Отождествление вершин (матрица)\n");
//        printf("2. Стягивание ребра (матрица)\n");
//        printf("3. Расщепление вершины (матрица)\n");
//        printf("4. Отождествление вершин (список)\n");
//        printf("5. Стягивание ребра (список)\n");
//        printf("6. Расщепление вершины (список)\n");
//        printf("0. Выход\n");
//        printf("Ваш выбор: ");
//        scanf("%d", &choice);
//
//        if (choice == 0) break;
//
//        int temp_graph[SIZE][SIZE] = { 0 }; // Обнуляемматрицу
//
//        switch (choice) {
//        case 1: // Отождествление вершин (матрица)
//            printf("Введите две вершины для объединения: ");
//            scanf("%d %d", &u, &v);
//            // Копируем исходный граф
//            for (int i = 0; i < n; i++) {
//                for (int j = 0; j < n; j++) {
//                    temp_graph[i][j] = graph[i][j];
//                }
//            }
//            for (int i = 0; i < n; i++) {
//                if (temp_graph[v][i] == 1) temp_graph[u][i] = 1;
//                if (temp_graph[i][v] == 1) temp_graph[i][u] = 1;
//            }
//            printf("Результат (матрица):\n");
//            for (int i = 0; i < n; i++) {
//                if (i == v) continue;
//                for (int j = 0; j < n; j++) {
//                    if (j == v) continue;
//                    printf("%d ", temp_graph[i][j]);
//                }
//                printf("\n");
//            }
//            break;
//
//        case 2: // Стягиваниеребра (матрица)
//            printf("Введите ребро для стягивания: ");
//            scanf("%d %d", &u, &v);
//            // Копируем исходный граф
//            for (int i = 0; i < n; i++) {
//                for (int j = 0; j < n; j++) {
//                    temp_graph[i][j] = graph[i][j];
//                }
//            }
//            if (temp_graph[u][v] == 1) {
//                for (inti = 0; i < n; i++) {
//                    if (temp_graph[v][i] == 1) temp_graph[u][i] = 1;
//                    if (temp_graph[i][v] == 1) temp_graph[i][u] = 1;
//                }
//                printf("Результат (матрица):\n");
//                for (inti = 0; i < n; i++) {
//                    if (i == v) continue;
//                    for (int j = 0; j < n; j++) {
//                        if (j == v) continue;
//                        printf("%d ", temp_graph[i][j]);
//                    }
//                    printf("\n");
//                }
//            }
//            else {
//                printf("Ошибка: нетребрамежду %d и %d!\n", u, v);
//            }
//            break;
//
//        case 3: // Расщепление вершины (матрица)
//            printf("Введите вершину для расщепления: ");
//            scanf("%d", &u);
//            new_n = n + 1;
//
//            // Копируем исходный граф и обнуляем новую строку/столбец
//            for (int i = 0; i < new_n; i++) {
//                for (int j = 0; j < new_n; j++) {
//                    if (i < n && j < n) {
//                        temp_graph[i][j] = graph[i][j];
//                    }
//                    else {
//                        temp_graph[i][j] = 0; // Обнуляемновыеячейки
//                    }
//                }
//            }
//
//            // Переносим часть связей на новую вершину
//            for (int i = 0; i < n; i++) {
//                if (temp_graph[u][i] == 1 && rand() % 2 == 0) {
//                    temp_graph[new_n - 1][i] = 1;
//                    temp_graph[i][new_n - 1] = 1;
//                    temp_graph[u][i] = 0;
//                    temp_graph[i][u] = 0;
//                }
//            }
//            // Связываем старую и новую вершину
//            temp_graph[u][new_n - 1] = 1;
//            temp_graph[new_n - 1][u] = 1;
//
//            printf("Результат (матрица):\n");
//            show_matrix(new_n, temp_graph);
//            break;
//
//        case 4: // Отождествление вершин (список)
//            printf("Введите две вершины для объединения: ");
//            scanf("%d %d", &u, &v);
//            // Копируем исходный граф
//            for (int i = 0; i < n; i++) {
//                for (int j = 0; j < n; j++) {
//                    temp_graph[i][j] = graph[i][j];
//                }
//            }
//            for (inti = 0; i < n; i++) {
//                if (temp_graph[v][i] == 1) temp_graph[u][i] = 1;
//                if (temp_graph[i][v] == 1) temp_graph[i][u] = 1;
//            }
//            printf("Результат (список):\n");
//            for (inti = 0; i < n; i++) {
//                if (i == v) continue;
//                printf("%d: ", i);
//                for (int j = 0; j < n; j++) {
//                    if (j == v) continue;
//                    if (temp_graph[i][j] == 1) printf("%d ", j);
//                }
//                printf("\n");
//            }
//            break;
//
//        case 5: // Стягиваниеребра (список)
//            printf("Введите ребро для стягивания: ");
//            scanf("%d %d", &u, &v);
//            // Копируем исходный граф
//            for (int i = 0; i < n; i++) {
//                for (int j = 0; j < n; j++) {
//                    temp_graph[i][j] = graph[i][j];
//                }
//            }
//            if (temp_graph[u][v] == 1) {
//                for (int i = 0; i < n; i++) {
//                    if (temp_graph[v][i] == 1) temp_graph[u][i] = 1;
//                    if (temp_graph[i][v] == 1) temp_graph[i][u] = 1;
//                }
//                printf("Результат (список):\n");
//                for (int i = 0; i < n; i++) {
//                    if (i == v) continue;
//                    printf("%d: ", i);
//                    for (int j = 0; j < n; j++) {
//                        if (j == v) continue;
//                        if (temp_graph[i][j] == 1) printf("%d ", j);
//                    }
//                    printf("\n");
//                }
//            }
//            else {
//                printf("Ошибка: нетребрамежду %d и %d!\n", u, v);
//            }
//            break;
//
//        case 6: // Расщепление вершины (список)
//            printf("Введите вершину для расщепления: ");
//            scanf("%d", &u);
//            new_n = n + 1;
//
//            // Копируем исходный граф и обнуляем новую строку/столбец
//            for (int i = 0; i < new_n; i++) {
//                for (int j = 0; j < new_n; j++) {
//                    if (i < n && j < n) {
//                        temp_graph[i][j] = graph[i][j];
//                    }
//                    else {
//                        temp_graph[i][j] = 0;
//                    }
//                }
//            }
//
//            // Переносим часть связей на новую вершину
//            for (int i = 0; i < n; i++) {
//                if (temp_graph[u][i] == 1 && rand() % 2 == 0) {
//                    temp_graph[new_n - 1][i] = 1;
//                    temp_graph[i][new_n - 1] = 1;
//                    temp_graph[u][i] = 0;
//                    temp_graph[i][u] = 0;
//                }
//            }
//            // Связываем старую и новую вершину
//            temp_graph[u][new_n - 1] = 1;
//            temp_graph[new_n - 1][u] = 1;
//
//            printf("Результат (список):\n");
//            show_list(new_n, temp_graph);
//            break;
//
//        default:
//            printf("Неверныйвыбор!\n");
//        }
//    }
//
//    return 0;
//}



// Задание 3
//int main() {
//    setlocale(LC_ALL, "Russian");
//    srand(time(NULL));
//
//    int n;
//    printf("Введите число вершин для графов: ");
//    scanf("%d", &n);
//
//    int G1[SIZE][SIZE] = { 0 };
//    int G2[SIZE][SIZE] = { 0 };
//
//    for (int i = 0; i < n; i++) {
//        for (int j = i + 1; j < n; j++) {
//            G1[i][j] = G1[j][i] = rand() % 2;
//            G2[i][j] = G2[j][i] = rand() % 2;
//        }
//    }
//
//    printf("Граф G1:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", G1[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\nГраф G2:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", G2[i][j]);
//        }
//        printf("\n");
//    }
//
//
//    int result[SIZE][SIZE] = { 0 };
//
//
//    printf("Объединение G1 и G2:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            result[i][j] = G1[i][j] || G2[i][j];
//            printf("%d ", result[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\nПересечение G1 и G2:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            result[i][j] = G1[i][j] && G2[i][j];
//            printf("%d ", result[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\nв) Кольцевая сумма G1 и G2:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            result[i][j] = G1[i][j] != G2[i][j];
//            printf("%d ", result[i][j]);
//        }
//        printf("\n");
//    }
//
//    return 0;
//}


// Задание 4
//int main() {
//    setlocale(LC_ALL, "Russian");
//    srand(time(NULL));
//
//    int n1, n2;
//    printf("Введите число вершин для графа G1: ");
//    scanf("%d", &n1);
//    printf("Введите число вершин для графа G2: ");
//    scanf("%d", &n2);
//
//    int G1[SIZE][SIZE] = { 0 };
//    int G2[SIZE][SIZE] = { 0 };
//
//
//    for (int i = 0; i < n1; i++) {
//        for (int j = i + 1; j < n1; j++) {
//            G1[i][j] = G1[j][i] = rand() % 2;
//        }
//    }
//
//    for (int i = 0; i < n2; i++) {
//        for (int j = i + 1; j < n2; j++) {
//            G2[i][j] = G2[j][i] = rand() % 2;
//        }
//    }
//
//    printf("Граф G1 (%d вершин):\n", n1);
//    for (int i = 0; i < n1; i++) {
//        for (int j = 0; j < n1; j++) {
//            printf("%d ", G1[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\nГраф G2 (%d вершин):\n", n2);
//    for (int i = 0; i < n2; i++) {
//        for (int j = 0; j < n2; j++) {
//            printf("%d ", G2[i][j]);
//        }
//        printf("\n");
//    }
//
//
//    int result[SIZE][SIZE] = { 0 };
//    int new_n = n1 * n2;
//
//    for (int i1 = 0; i1 < n1; i1++) {
//        for (int k1 = 0; k1 < n2; k1++) {
//            for (int i2 = 0; i2 < n1; i2++) {
//                for (int k2 = 0; k2 < n2; k2++) {
//                    int vertex1 = i1 * n2 + k1;
//                    int vertex2 = i2 * n2 + k2;
//
//                    if ((i1 == i2 && G2[k1][k2] == 1) || (k1 == k2 && G1[i1][i2] == 1)) {
//                        result[vertex1][vertex2] = 1;
//                        result[vertex2][vertex1] = 1;
//                    }
//                }
//            }
//        }
//    }
//
//    printf("Матрица смежности (%d вершин):\n", new_n);
//    for (int i = 0; i < new_n; i++) {
//        for (int j = 0; j < new_n; j++) {
//            printf("%d ", result[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\nСписок смежности:\n");
//    for (int i = 0; i < new_n; i++) {
//        printf("%d: ", i);
//        for (int j = 0; j < new_n; j++) {
//            if (result[i][j] == 1) {
//                printf("%d ", j);
//            }
//        }
//        printf("\n");
//    }
//
//    return 0;
//}