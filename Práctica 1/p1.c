#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>


int sumaSubMax1(int v[], int n) {
	int i, j;
	int estaSuma, sumaMax = 0;
	for (i = 0; i < n; i++) {
		estaSuma = 0;
		for (j = i; j < n; j++) {
			estaSuma += v[j];
			if (estaSuma > sumaMax) {
				sumaMax = estaSuma;
			}
		}
	}
	return sumaMax;
}

int sumaSubMax2(int v[], int n) {
	int j, estaSuma = 0, sumaMax = 0;
	for (j = 0; j < n; j++) {
		estaSuma += v[j];
		if (estaSuma > sumaMax) {
            sumaMax = estaSuma;
        } else if (estaSuma < 0)
            estaSuma = 0;
	}
    return sumaMax;
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

void listar_vector(int v[], int n){
	int i;
    printf("[");
    for (i = 0; i < n; i++)
        printf(" %2d", v[i]);
    printf(" ]");
}

void test1() {
    int i;
    int v[6] [5] = { {-9, 2, -5, -4, 6},
                     {4, 0, 9, 2, 5},
                     {-2, -1, -9, -7, -1},
                     {9, -2, 1, -7, -8},
                     {15, -2, -5, -4, 16},
                     {7, -5, 6, 7, -7} };
    printf("test 1\n");
    printf("%15s%15s%15s", "", "resultado1", "resultado2\n");
    for(i = 0; i < 6; i++){
        listar_vector(v[i], 5);
        printf("%9d", sumaSubMax1(v[i], 5));
        printf("%16d", sumaSubMax2(v[i], 5));
        printf("\n");
    }
    printf("\n\n");
}

void test2() {
	int i, a, b;
	int v[9];
	printf("test\n");
	printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for (i=0; i<10; i++) {
		aleatorio(v, 9);
		listar_vector(v, 9);
		a = sumaSubMax1(v, 9);
		b = sumaSubMax2(v, 9);
		printf("%15d%15d\n", a, b);
	}
}

void tablas1 () {
    int t[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int num_t = sizeof(t) / sizeof(t[0]);
    int j, k = 100, n, i;
    double inicio, fin, tiempo1, tiempo2, tiempo;

    printf("\nTiempos de ejecución (SumaSubMax 1)\n\n");
    printf("%16s%15s\n", "Tamaño", "Tiempo");

    for (i = 0; i < num_t; i++) {
        n = t[i];
        int v[n];
        aleatorio(v, n);
        inicio = microsegundos();
        sumaSubMax1(v, n);
        fin = microsegundos();
        tiempo = fin - inicio;
        if (tiempo < 500) {
            j = 0;
            inicio = microsegundos();
            while (j < k) {
                aleatorio(v, n);
                sumaSubMax1(v, n);
                j++;
            }
            fin = microsegundos();
            tiempo1 = fin - inicio;
            printf("%f\n", tiempo1);
            inicio = microsegundos();
            j = 0;
            while (j < k) {
                aleatorio(v, n);
                j++;
            }
            fin = microsegundos();
            tiempo2 = fin - inicio;
            printf("%f\n", tiempo2);
            tiempo = (tiempo1 - tiempo2) / k;
        }
        printf("%15d%15.2f\n", n, tiempo);
    }
    printf("\n");
}

void tablas2() {
    int t[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int num_t = sizeof(t) / sizeof(t[0]);
    int j, k = 1000, n, i;
    double inicio, fin, tiempo1, tiempo2, tiempo;

    printf("\nTiempos de ejecución (SumaSubMax 2)\n\n");
    printf("%16s%15s\n", "Tamaño", "Tiempo");

    for (i = 0; i < num_t; i++) {
        n = t[i];
        int v[n];
        aleatorio(v, n);
        inicio = microsegundos();
        sumaSubMax2(v, n);
        fin = microsegundos();
        tiempo = fin - inicio;
        if (tiempo < 500) {
            j = 0;
            inicio = microsegundos();
            while (j < k) {
                aleatorio(v, n);
                sumaSubMax2(v, n);
                j++;
            }
            fin = microsegundos();
            tiempo1 = fin - inicio;
            j = 0;
            inicio = microsegundos();
            while (j < k) {
                aleatorio(v, n);
                j++;
            }
            fin = microsegundos();
            tiempo2 = fin - inicio;
            tiempo = (tiempo1 - tiempo2) / k;
        }

        printf("%15d%15.2f\n", n, tiempo);
    }
}

int main() {
	inicializar_semilla();

	test1();
	test2();

    tablas1();
    tablas2();
	return 0;
}
