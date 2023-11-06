/*
PRÁCTICA 3: "ORDENACIÓN POR MONTÍCULOS"
AUTOR: Iván Castro Roel                 LOGIN: ivan.castro.roel
AUTOR: Alejandro Amado Fernández        LOGIN: alejandro.amado
AUTOR: Leandro Malo Balboa              LOGIN:leandro.mbalboa
GRUPO: 4.3
FECHA: 11/11/2023
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

void listar_vector(int v[], int n);

typedef struct monticulo * pmonticulo;

void hundir(pmonticulo m, int i) {
    int hijoIzq, hijoDer, j, aux;

    do {
        hijoIzq = 2 * i + 1;
        hijoDer = 2 * i + 2;
        j = i;
        if (hijoDer <= m->ultimo && m->vector[hijoDer] < m->vector[i])
            i = hijoDer;
        if (hijoIzq <= m->ultimo && m->vector[hijoIzq] < m->vector[i])
            i = hijoIzq;
        aux = m->vector[i];
        m->vector[i] = m->vector[j];
        m->vector[j] = aux;
    } while (j != i);
}

void crearMonticulo(int v[], int n, pmonticulo m) {
    int i;

    memcpy(m->vector, v, n*sizeof(int));
    m->ultimo = n - 1;

    if (n % 2 == 0) {
        i = n / 2;
    } else {
        i = n / 2-1;
    }
    while (i >= 0) {
        hundir(m, i);
        i--;
    }
    //listar_vector(m->vector, n);
}

int quitarMenor(pmonticulo m) {
    int x;
    x = m->vector[0];
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo = m->ultimo - 1;
    if (m->ultimo >= 0)
        hundir(m, 0);
    return x;
}

void ordenarPorMonticulos(int v[], int n) {
    int i;
    pmonticulo m = malloc(sizeof(struct monticulo));

    crearMonticulo(v, n, m);
    for (i = n; i >= 0; i--) {
        v[n-i] = quitarMenor(m);
    }
    free(m);
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

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* se generan números pseudoaleatorio entre -n y +n */
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i + 1;
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i;
}

void listar_vector(int v[], int n){
    int i;
    printf("[");
    for (i = 0; i < n; i++)
        printf(" %2d", v[i]);
    printf(" ]\n");
}

bool ordenado (int v[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        if (v[i] < v[i-1])
            return false;
    }
    return true;
}

void test(int v[], int n, const char *tipo_inicializacion, int iteracion) {
    printf("\nInicialización %s:\n", tipo_inicializacion);
    if (strcmp(tipo_inicializacion, "aleatorio") == 0) {
        aleatorio(v, n);
    } else if (strcmp(tipo_inicializacion, "descendente") == 0) {
        descendente(v, n);
    } else if (strcmp(tipo_inicializacion, "ascendente") == 0) {
        ascendente(v, n);
    }
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
    printf("Ordenación por Montículos:\n");
    ordenarPorMonticulos(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));

    //Test para quitarMenor
    if (iteracion==2){
        pmonticulo m = malloc(sizeof(struct monticulo));
        int menor;
        printf("\nPrueba quitarMenor:\n");
        aleatorio(v, n);
        crearMonticulo(v, n, m);
        for (int i = 0; i < n; i++) {
            listar_vector(m->vector, n);
            menor = quitarMenor(m);
            printf("Menor: %d\n", menor);
        }
        listar_vector(m->vector, n);
        free(m);
    }
}

void comprueba(const char* nombreFunc, const char* ordenacion){
    printf("\nTiempos de ejecución (%s, %s)\n\n", nombreFunc, ordenacion);
    if (strcmp(nombreFunc, "monticulo") == 0) {
        if (strcmp(ordenacion, "aleatorio") == 0) {
            printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
                   "(t(n)/n^0.9)", "(t(n)/n^1.1)", "(t(n)/n^1.3)");
        } else {
            printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
                   "(t(n)/n^0.88)", "(t(n)/n^1.08)", "(t(n)/n^1.28)");
        }
    } else
        printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
               "(t(n)/n^0.82)", "(t(n)/n^1.02)", "(t(n)/n^1.22)");
}

void tablaTiempos(void (*func)(int[], int), void (*ord)(int[], int),
                  const char* nombreFunc, const char* ordenacion, float cota){
    int t[] = {4000, 8000, 16000, 32000, 64000, 128000, 256000};
    int k = 1000, n, v[256000], asterisco = 0, i, j, l;
    double inicio, fin, tiempo1, tiempo2, tiempo;

    comprueba(nombreFunc, ordenacion);
    for (i = 0; i < 7; i++) {
        n = t[i];
        ord(v, n);
        inicio = microsegundos();
        func(v, n);
        fin = microsegundos();
        tiempo = fin - inicio;
        if (tiempo < 500) {
            asterisco = 1;
            inicio = microsegundos();
            for (j = 0; j < k; j++) {
                ord(v, n);
                func(v, n);
            }
            fin = microsegundos();
            tiempo1 = fin - inicio;
            inicio = microsegundos();
            for (l = 0; l < k; l++)
                ord(v, n);
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
    }
}

void tablaTiempos_crear(void (*func)(int[], int, pmonticulo), void (*ord)(int[], int),
                  const char* nombreFunc, const char* ordenacion, float cota){
    int t[] = {4000, 8000, 16000, 32000, 64000, 128000, 256000};
    int k = 1000, n, v[256000], asterisco = 0, i, j, l;
    double inicio, fin, tiempo1, tiempo2, tiempo;
    pmonticulo m = malloc(sizeof(struct monticulo));;

    comprueba(nombreFunc, ordenacion);
    for (i = 0; i < 7; i++) {
        n = t[i];
        ord(v, n);
        inicio = microsegundos();
        func(v, n, m);
        fin = microsegundos();
        tiempo = fin - inicio;
        if (tiempo < 500) {
            asterisco = 1;
            inicio = microsegundos();
            for (j = 0; j < k; j++) {
                ord(v, n);
                func(v, n, m);
            }
            fin = microsegundos();
            tiempo1 = fin - inicio;
            inicio = microsegundos();
            for (l = 0; l < k; l++)
                ord(v, n);
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
    }
}

int main() {
    inicializar_semilla();
    const char *inicializacion[] = {"aleatorio", "descendente", "ascendente"};
    int v[9], n = 9;
    for (int i = 0; i < 2; i++) {
        test(v, n, inicializacion[i], i);
    }

    for (int i = 0; i < 2; i++)
        tablaTiempos_crear(crearMonticulo, aleatorio, "crear", "aleatorio", 1.02);
    for (int i = 0; i < 2; i++)
        tablaTiempos_crear(crearMonticulo, descendente, "crear", "descendente", 1.02);
    for (int i = 0; i < 2; i++)
        tablaTiempos_crear(crearMonticulo, ascendente, "crear", "ascendente", 1.02);
    for (int i = 0; i < 2; i++)
        tablaTiempos(ordenarPorMonticulos, aleatorio, "monticulo", "aleatorio", 1.1);
    for (int i = 0; i < 2; i++)
        tablaTiempos(ordenarPorMonticulos, descendente, "monticulo", "descendente", 1.08);
    for (int i = 0; i < 2; i++)
        tablaTiempos(ordenarPorMonticulos, ascendente, "monticulo", "ascendente", 1.08);
}
