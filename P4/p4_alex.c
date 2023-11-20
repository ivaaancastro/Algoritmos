/*
PRÁCTICA 4: "GRAFOS: PROBLEMA DEL CAMINO MÍNIMO"
AUTOR: Iván Castro Roel                 LOGIN: ivan.castro.roel
AUTOR: Alejandro Amado Fernández        LOGIN: alejandro.amado
AUTOR: Leandro Malo Balboa              LOGIN:leandro.mbalboa
GRUPO: 4.3
FECHA: 25/11/2023
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX 1000

void listar_vector(int v[], int n);

typedef int ** matriz;

matriz crearMatriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}
/* Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
no dirigido con n nodos, representado por su matriz de adayencia */
void iniMatriz(matriz m, int n) {
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % TAM_MAX + 1;
    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}
void liberarMatriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

void dijkstra(matriz grafo, matriz distancias, int tam) {
    int n, i, j, min, v, iteracion;
    int *noVisitados = malloc(tam*sizeof(int));
    for (n=0; n<tam; n++) {
        for (i=0; i<tam; i++) {
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;
        for (iteracion = 0; iteracion < tam - 2; iteracion++) {
            min = -1;
            for (v = 0; v < tam; v++) {
                if (noVisitados[v] && (min == -1 ||
                    distancias[n][v] < distancias[n][min])) {
                    min = v;
                }
            }

            noVisitados[min] = 0;

            for (j = 0; j < tam; j++) {
                if (noVisitados[j] && distancias[n][j] >
                    distancias[n][min] + grafo[min][j]) {
                    distancias[n][j] = distancias[n][min] + grafo[min][j];
                }
            }
        }
    }
    free(noVisitados);
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void listar_matriz(matriz m, int n){
    int i, j;
    printf(" -");
    for (i = 0; i < n; i++)
        printf("---");
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("|");
        for (j = 0; j < n; j++) {
            printf(" %2d", m[i][j]);
        }
        printf(" |\n");
    }
    printf(" -");
    for (i = 0; i < n; i++)
        printf("---");
    printf("\n\n");
}

void test() {
    int i, j;
    matriz m1 = crearMatriz(5);
    matriz m2 = crearMatriz(4);
    int aux1[5][5] = {{0,1,8,4,7}, {1,0,2,6,5}, {8,2,0,9,5},
                      {4,6,9,0,3}, {7,5,5,3,0}};
    int aux2[4][4] = {{0,1,4,7}, {1,0,2,8}, {4,2,0,3}, {7,8,3,0}};

    for (i=0; i<5;i++) {
        for (j=0; j<5;j++) {
            m1[i][j] = aux1[i][j];
        }
    }
    for (i=0; i<4;i++) {
        for (j=0; j<4;j++) {
            m2[i][j] = aux2[i][j];
        }
    }

    printf("\nTest 1:\nMatriz de adyacencia 1:\n");
    listar_matriz(m1, 5);
    printf("Algoritmo de dijkstra...\n\nDistancias mínimas 1:\n");
    dijkstra(m1, m1, 5);
    listar_matriz(m1, 5);
    liberarMatriz(m1, 5);

    printf("\nTest 2:\nMatriz de adyacencia 2:\n");
    listar_matriz(m2, 4);
    printf("Algoritmo de dijkstra...\n\nDistancias mínimas 2:\n");
    dijkstra(m2, m2, 4);
    listar_matriz(m2, 4);
    liberarMatriz(m2, 4);
}

void cabecera() {
    printf("\nTiempos de ejecución (dijkstra, aleatorio)\n\n");
    printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
           "(t(n)/n^2.67)", "(t(n)/n^2.87)", "(t(n)/n^3.07)");
}
void tablaTiempos() {
    int t[] = {10, 20, 40, 80, 160, 320, 640};
    int k = 200, n, asterisco = 0, i, j, l;
    double inicio, fin, tiempo1, tiempo2, tiempo;
    float cota = 2.87;
    matriz m;
    cabecera();
    for (i = 0; i < 7; i++) {
        n = t[i];
        m = crearMatriz(n);
        iniMatriz(m, n);
        inicio = microsegundos();
        dijkstra(m, m, n);
        fin = microsegundos();
        tiempo = fin - inicio;
        if (tiempo < 500) {
            asterisco = 1;
            inicio = microsegundos();
            for (j = 0; j < k; j++) {
                iniMatriz(m, n);
                dijkstra(m, m, n);
            }
            fin = microsegundos();
            tiempo1 = fin - inicio;
            inicio = microsegundos();
            for (l = 0; l < k; l++)
                iniMatriz(m, n);
            fin = microsegundos();
            tiempo2 = fin - inicio;
            tiempo = (tiempo1 - tiempo2) / k;
        }
        if (asterisco == 1) {
            printf("(*)%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, tiempo/
            pow(n, cota-0.2), tiempo/pow(n, cota), tiempo/pow(n, cota+0.2));
        } else
            printf("%15d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, tiempo/
            pow(n, cota-0.2), tiempo/pow(n, cota), tiempo/pow(n, cota+0.2));
        asterisco = 0;
        liberarMatriz(m, n);
    }
}

int main() {
    int i;
    inicializar_semilla();
    test();

    for (i = 0; i < 2; i++)
        tablaTiempos();

}
