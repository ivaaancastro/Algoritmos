#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

void ordenacionInsercion(int v[], int n)
{
    int i, j, x;

    for (i = 1; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void ordenacionShell(int v[], int n)
{
    int i, seguir, tmp, j, incremento = n;
    do
    {
        incremento = incremento / 2;
        for (i = incremento; i < n; i++)
        {
            tmp = v[i];
            j = i;
            seguir = 1;
            while (j - incremento >= 0 && seguir)
            {
                if (tmp < v[j - incremento])
                {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                }
                else
                {
                    seguir = 0;
                }
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
}

double microsegundos()
{ /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla()
{
    srand(time(NULL));
    /* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void aleatorio(int v[], int n)
{
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* se generan números pseudoaleatorio entre -n y +n */
}

void listar_vector(int v[], int n)
{
    int i;
    printf("[");
    for (i = 0; i < n; i++)
        printf(" %2d", v[i]);
    printf(" ]");
}

int esta_ordenado(int v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (v[i] < v[i - 1])
        {
            return 0; // No está ordenado
        }
    }
    return 1; // Está ordenado
}

void inicializar_descendente(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = n - i;
    }
}

void inicializar_ascendente(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = n + i;
    }
}

void test_inserccion()
{
    printf("INSERCCIÓN\n\n");
    int v[9];
    printf("Inicializacion aleatoria\n\n");
    aleatorio(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\n ordenado? %d\n", esta_ordenado(v, 9));

    printf("Ordenacion por Insercion\n\n");
    ordenacionInsercion(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n", esta_ordenado(v, 9));

    printf("\nInicializacion descendente\n\n");
    inicializar_descendente(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n", esta_ordenado(v, 9));

    printf("Ordenacion por Insercion\n\n");
    ordenacionInsercion(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n\n\n", esta_ordenado(v, 9));
}

void test_shell()
{
    printf("SHELL\n\n");
    int v[9];
    printf("Inicializacion aleatoria\n\n");
    aleatorio(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n", esta_ordenado(v, 9));

    printf("Ordenacion por Shell\n\n");
    ordenacionShell(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n", esta_ordenado(v, 9));

    printf("\nInicializacion descendente\n\n");
    inicializar_descendente(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n", esta_ordenado(v, 9));

    printf("Ordenacion por Shell\n\n");
    ordenacionShell(v, 9);
    listar_vector(v, 9);
    printf("\n");

    printf("\nEstá ordenado? %d\n", esta_ordenado(v, 9));
}

void comprueba(const char* nombreFunc, int situacion_inicial){
    if (situacion_inicial == 0){
        printf("\nTiempos de ejecución (%s Ascendente)\n\n", nombreFunc);
    }
    else if (situacion_inicial == 1){
        printf("\nTiempos de ejecución (%s Descendente)\n\n", nombreFunc);
    }
    else{
        printf("\nTiempos de ejecución (%s Aleatorio)\n\n", nombreFunc);
    }
        
    if (strcmp(nombreFunc, "ordenacionInsercion") == 0) {
        printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
               "(t(n)/n^1.8)", "(t(n)/n^2)", "(t(n)/n^2.2)");
    } else
        printf("%16s%15s%15s%15s%15s\n", "Tamaño", "t(n)",
               "(t(n)/n^0.8)", "(t(n)/n^1.0)", "(t(n)/n^1.2)");
}

void tablaTiempos(int (*func)(int[], int), const char* nombreFunc, float cota, int situacion_inicial){
    int t[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int k = 1000, n, v[32000], asterisco = 0, i, j;
    double inicio, fin, tiempo, tiempoPromedio;
    
    comprueba(nombreFunc, situacion_inicial);

    for (i = 0; i < 7; i++) {
        n = t[i];
        if (situacion_inicial == 0){
            inicializar_ascendente(v,n);
        }
        else if (situacion_inicial == 1){
            inicializar_descendente(v,n);
        }
        else{
            aleatorio(v,n);
        }
        
        aleatorio(v, n);
        inicio = microsegundos();
        func(v, n);
        fin = microsegundos();
        tiempo = fin - inicio;
        if (tiempo < 500) { 
            asterisco = 1;
            tiempoPromedio = 0.0;
            for (j = 0; j < k; j++) {
                aleatorio(v, n);
                inicio = microsegundos();
                func(v, n);
                fin = microsegundos();
                tiempoPromedio += fin - inicio;
            }
            tiempoPromedio /= k;
            tiempo = tiempoPromedio;
        }
        if (asterisco == 1) {
            printf("(*)%12d%15.2f%15.6f%15.6f%15.6f\n", n, tiempo, tiempo/pow(n, cota-0.2), tiempo/pow(n, cota), tiempo/pow(n, cota+0.2));
        } else {
            printf("%15d%15.2f%15.6f%15.6f%15.6f\n", n, tiempo, tiempo/pow(n, cota-0.2), tiempo/pow(n, cota), tiempo/pow(n, cota+0.2));
        }
        asterisco = 0;
    }
}




int main()
{
    inicializar_semilla();
    test_inserccion();
    test_shell();
    tablaTiempos(ordenacionInsercion, "ordenacionInsercion", 2.0, 0);
    tablaTiempos(ordenacionInsercion, "ordenacionInsercion", 2.0, 1);
    tablaTiempos(ordenacionInsercion, "ordenacionInsercion", 2.0, 2);
    tablaTiempos(ordenacionShell, "ordenacionShell", 1.0, 0);
    tablaTiempos(ordenacionShell, "ordenacionShell", 1.0, 1);
    tablaTiempos(ordenacionShell, "ordenacionShell", 1.0, 2);
}