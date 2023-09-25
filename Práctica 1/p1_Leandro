#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
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

int sumaSubMax2 (int v[],int n){
    int estaSuma = 0;
    int sumaMax =0;
    int j;
    for (j = 0 ; j < n ; j++) {
        estaSuma = estaSuma + v[j];
        if(estaSuma>sumaMax){
            sumaMax=estaSuma;
        }else{
            if(estaSuma<0){
                estaSuma=0;
            }
        }
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
    for (i = 0; i < n ; i++){
        printf(" %2d ",v[i]);
    }
    printf("]");
}
void test1(){
    int i ;
    int v[6][5] = { {-9, 2, -5, -4, 6},
                         {4, 0, 9, 2, 5},
                         {-2, -1, -9, -7, -1},
                         { 9, -2, 1, -7, -8},
                         {15, -2, -5, -4, 16},
                         {7, -5, 6, 7, -7} };

    printf("test 1\n");
    printf("%15s%15s%15s", "", "resultado1", "resultado2\n");
        for(i=0; i < 6; i++){
            listar_vector(v[i], 5);
            printf("%9d", sumaSubMax1(v[i],5));
            printf("%16d", sumaSubMax2(v[i],5));
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
int medirTiempo(int (*func)(int[], int), int v[], int n, int k, double* tiempo, double* relacion, double* relacion2, double* relacion3) {
    int j;
    double inicio, fin, tiempo1 = 0, tiempo2 = 0;
    inicio = microsegundos(); //Marcamos el tiempo en el momento de inicio
    func(v, n); // Llamamos al algoritmo
    fin = microsegundos(); //Marcamos el tiempo en el momento de finalización
    *tiempo = fin - inicio; //Calculamos el tiempo transcurrido

    //Se calculan las relaciones
    *relacion = *tiempo / pow(n, 1.8);
    *relacion2 = *tiempo / pow(n, 2.0);
    *relacion3 = *tiempo / pow(n, 2.2);

    if (*tiempo < 500) { //Si el tiempo es corto se repiten para obtener mediones exactas
        for (j = 0; j < k; j++) {
            aleatorio(v, n); //Generamos un array aleatorio
            inicio = microsegundos();
            func(v, n); //Llamamos al algoritmo
            fin = microsegundos();
            tiempo1 += fin - inicio; //Acumulamos tiempos
        }
        for (j = 0; j < k; j++) {
            aleatorio(v, n); //Generamos otro array nuevo
        }
        inicio = microsegundos();
        for (j = 0; j < k; j++) {
            func(v, n); //Llamamos al algoritmo
        }
        fin = microsegundos();
        tiempo2 = fin - inicio; //Tiempo de ejecucion que no se ha medido

        *tiempo = (tiempo1 - tiempo2) / k; //Calculamos tiempo medio
        *relacion = *tiempo / pow(n, 1.8);
        *relacion2 = *tiempo / pow(n, 2.0);
        *relacion3 = *tiempo / pow(n, 2.2);

        return 1; //Se han obtenido resultados válidos
    }
    return 0;
}
void tablaDeTiempos(int (*func)(int[], int), const char* nombreFunc){
    int t[] = {500, 1000, 2000, 4000, 8000, 16000, 32000}; //Tamaños de los vectores
    int num_t =sizeof(t)/sizeof(t[0]); //Obtenemos la longitud del array
    int i, n, k = 1000; //Declaramos las variables, k es el numero de ejecuciones en tiempos cortos
    double tiempo, relacion, relacion2, relacion3;

    //Cabecera de la tabla
    printf("\nTiempos de ejecución (%s)\n\n",nombreFunc);
    printf("%16s%15s%15s%15s%15s\n", "Tamaño", "n", "(t(n)/n^1.8)", "(t(n)/n^2)", "(t(n)/n^2.2)");

    //Recorremos los tamaños de prueba
    for(i = 0; i < num_t; i++){
        n = t[i];
        int v[n]; //Array de tamaño n

        aleatorio(v, n); //Llenamos el array de numeros aleatorios

        tiempo = 0; //Tiempo de ejecución
        relacion = 0; //Relación t(n)/n^1.8
        relacion2 = 0; //Relación t(n)/n^2
        relacion3 = 0; //Relación t(n)/n^2.2

        //Llamamos medirTiempo para calcular los tiempos
        if (medirTiempo(func, v, n, k, &tiempo, &relacion, &relacion2, &relacion3)){
            //Imprime resultados en las tablas
            printf("%15d%15.2f%15.6f%15.6f%15.6f\n", n, tiempo, relacion, relacion2, relacion3);
        }
    }
}


int main() {
    inicializar_semilla();


    test1();
    test2();
    return 0;
    
}
