#include <stdio.h> 
#include "cJSON.h" 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



void importarDatos() {
    fuap();
    // Lógica para la importación de datos
}

void procesarDatos() {
    printf("Procesando datos...\n");
    // Lógica para el procesamiento de datos
}

void analizarDatos() {
    printf("Analizando datos...\n");
    // Lógica para el análisis de datos
}

void analisisTemporal() {
    printf("Realizando análisis temporal...\n");
    // Lógica para el análisis temporal
}

void estadisticas() {
    printf("Generando estadísticas...\n");
    // Lógica para generar estadísticas
}

int main() {
    char input[10];
    int opcion;

    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Importacion de datos\n");
        printf("2. Procesamiento de datos\n");
        printf("3. Analisis de datos\n");
        printf("4. Analisis temporal\n");
        printf("5. Estadisticas\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        
        // Leer la entrada como una cadena
        fgets(input, sizeof(input), stdin);

        // Intentar convertir la entrada a un número entero
        if (sscanf(input, "%d", &opcion) != 1) {
            printf("Entrada no válida. Por favor, ingrese un número.\n");
            continue;  // Volver a mostrar el menú
        }

        switch (opcion) {
            case 1:
                importarDatos();
                break;
            case 2:
                procesarDatos();
                break;
            case 3:
                analizarDatos();
                break;
            case 4:
                analisisTemporal();
                break;
            case 5:
                estadisticas();
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}