#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void ord_ins(int v[], int n) {
    int i, x, j;
    for (i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
    }
}

void ord_shell(int v[], int n) {
    int incr = n, i, tmp, j;
    bool seguir;
    do {
        incr /= 2;
        for (i = incr; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = true;
            while ((j - incr) >= 0 && seguir) {
                if (tmp < v[j-incr]) {
                    v[j] = v[j-incr];
                    j = j-incr;
                } else
                    seguir = false;
            }
            v[j] = tmp;
        }
    } while (incr != 1);
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

void ascendente (int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i + 1;
}

void descendente (int v[], int n) {
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
    for (i = 1; i < n-1; i++) {
        if (v[i] < v[i-1])
            return false;
    }
    return true;
}

void test_ins() {
    int v[10], w[17], n = 10, m = 17;
    printf("\nInicialización aleatoria:\n");
    aleatorio(w, m);
    listar_vector(w, m);
    printf("ordenado? %d\n", ordenado(w, m));
    printf("Ordenación por Inserción:\n");
    ord_ins(w, m);
    listar_vector(w, m);
    printf("ordenado? %d\n", ordenado(w, m));

    printf("\nInicialización descendente:\n");
    descendente(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
    printf("Ordenación por Inserción:\n");
    ord_ins(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));

    printf("\nInicialización ascendente:\n");
    ascendente(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
    printf("Ordenación por Inserción:\n");
    ord_ins(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
}

void test_shell() {
    int v[10], w[17], n = 10, m = 17;
    printf("\nInicialización aleatoria:\n");
    aleatorio(w, m);
    listar_vector(w, m);
    printf("ordenado? %d\n", ordenado(w, m));
    printf("Ordenación por Shell:\n");
    ord_shell(w, m);
    listar_vector(w, m);
    printf("ordenado? %d\n", ordenado(w, m));

    printf("\nInicialización descendente:\n");
    descendente(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
    printf("Ordenación por Shell:\n");
    ord_shell(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));

    printf("\nInicialización ascendente:\n");
    ascendente(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
    printf("Ordenación por Shell:\n");
    ord_shell(v, n);
    listar_vector(v, n);
    printf("ordenado? %d\n", ordenado(v, n));
}

void comprueba(const char* nombreFunc, const char* ordenacion){
    printf("\nTiempos de ejecución (%s, %s)\n\n", nombreFunc, ordenacion);
    if (strcmp(nombreFunc, "insercion") == 0) {
        if (strcmp(ordenacion, "ascendente") == 0) {
            printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
                   "(t(n)/n^0.8)", "(t(n)/n^1)", "(t(n)/n^1.2)");
        } else {
            printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
                   "(t(n)/n^1.8)", "(t(n)/n^2)", "(t(n)/n^2.2)");
        }
    } else {
        if (strcmp(ordenacion, "aleatorio") == 0) {
            printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
                   "(t(n)/n^1)", "(t(n)/n^1.2)", "(t(n)/n^1.4)");
        } else {
            printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
                   "(t(n)/n^0.95)", "(t(n)/n^1.15)", "(t(n)/n^1.35)");
        }
    }
}

void tablaTiempos(void (*func)(int[], int), void (*ord)(int[], int),
                  const char* nombreFunc, const char* ordenacion, float cota){
    int t[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int k = 1000, n, v[32000], asterisco = 0, i, j, l;
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

int main() {
    //int i;
    inicializar_semilla();
    test_ins();
    test_shell();

    tablaTiempos(ord_ins, aleatorio, "insercion", "aleatorio", 2);
    tablaTiempos(ord_ins, descendente, "insercion", "descendente", 2);
    tablaTiempos(ord_ins, ascendente, "insercion", "ascendente", 1);
    tablaTiempos(ord_shell, aleatorio, "shell", "aleatorio", 1.2);
    tablaTiempos(ord_shell, descendente, "shell", "descendente", 1.15);
    tablaTiempos(ord_shell, ascendente, "shell", "ascendente", 1.15);

    /*for (i = 0; i < 3; i++) {
        //tablaTiempos
    }*/
}
