
#include <stdio.h> 
#include "cJSON.h" 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct JsonInfo {
    int venta_id;
    char* fecha;
    int producto_id;
    char* producto_nombre;
    char* categoria;
    int cantidad;
    int precio_unitario;
    int total;
    struct JsonInfo* next;
};

// nodos de patogeno
struct JsonInfo* AgregarinfoJson(int venta_id,char* fecha,int producto_id,char* producto_nombre,char* categoria,int cantidad,int precio_unitario,int total) {
    struct JsonInfo* nuevoJson = (struct JsonInfo*)malloc(sizeof(struct JsonInfo));
    if (nuevoJson == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    //Asifnacion de la fecha del JSON al struct 
    nuevoJson->fecha = malloc(strlen(fecha) + 1);
    if (nuevoJson->fecha == NULL) {
        printf("Date not found.\n");
        exit(1);
    }
    strcpy(nuevoJson->fecha, fecha);
    //Asignacion de producto nombre al Struct
    nuevoJson->producto_nombre = malloc(strlen(producto_nombre) + 1);
    if (nuevoJson->producto_nombre == NULL) {
        printf("Producto_nombre not found.\n");
        exit(1);
    }
    strcpy(nuevoJson->producto_nombre, producto_nombre);
    //Asignacion de categoria al struct
    nuevoJson->categoria = malloc(strlen(categoria) + 1);
    if (nuevoJson->categoria == NULL) {
        printf("categoria not found.\n");
        exit(1);
    }
    strcpy(nuevoJson->categoria, categoria);
    //asignacion de venta id al struct
    nuevoJson->venta_id = venta_id;
    //asignacion del producto id al struct
    nuevoJson->producto_id = producto_id;
    //asignacion de la cantidad al struct
    nuevoJson->cantidad = cantidad;
    //Asignacion del precio unitario al struct
    nuevoJson->precio_unitario = precio_unitario;
    //asignacion del total al struct
    nuevoJson->total = total;
    //
    nuevoJson->next = NULL;
    return nuevoJson;
}

// agrega los nodos JSON a la lista
int agregarJSONLISTA(struct JsonInfo** head, int venta_id,char* fecha,int producto_id,char* producto_nombre,char* categoria,int cantidad,int precio_unitario,int total) {
    struct JsonInfo* newJsonInfo = AgregarinfoJson(venta_id,fecha,producto_id,producto_nombre,categoria,cantidad,precio_unitario,total);
    if (*head == NULL) {
        *head = newJsonInfo;
    } else {
        struct JsonInfo* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newJsonInfo;
    }
    return 0;
}


// free obligatorio
void liberarListaPatogenos(struct JsonInfo* head) {
    struct JsonInfo* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->fecha);
        free(temp->producto_nombre);
        free(temp->categoria);
        free(temp);
    }
}



// Función para leer un archivo en una cadena
char* readFile(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return NULL;
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Asignar memoria para el contenido del archivo
    char *content = (char*)malloc(length + 1);
    if (content == NULL) {
        printf("No se pudo asignar memoria para el contenido del archivo\n");
        fclose(file);
        return NULL;
    }

    // Leer el contenido y cerrar el archivo
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    return content;
}

int fuap(char* filename, struct JsonInfo** head) {
    char* jsonString = readFile(filename); // Leer el archivo JSON
    if (jsonString == NULL) {
        return 1;
    }

    // Parsear el JSON
    cJSON *jsonArray = cJSON_Parse(jsonString);
    if (jsonArray == NULL) {
        printf("Error al parsear JSON, probablemente JSON vacio\n");
        free(jsonString);
        return 1;
    }

    // Iterar sobre los elementos del array JSON
    int arraySize = cJSON_GetArraySize(jsonArray);
    for (int i = 0; i < arraySize; i++) {
        cJSON *item = cJSON_GetArrayItem(jsonArray, i);

        cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
        cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
        cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
        cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
        cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
        cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
        cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
        cJSON *total = cJSON_GetObjectItem(item, "total");

        // Imprimir los valores
        if(agregarJSONLISTA(head,venta_id->valueint,fecha->valuestring,producto_id->valueint, producto_nombre->valuestring,categoria->valuestring, cantidad->valueint, precio_unitario->valuedouble,total->valuedouble)== 0){
            printf("Info JSON agregada con exito!\n");
        }
        
    }

    // Liberar la memoria
    cJSON_Delete(jsonArray);
    free(jsonString);

    
} 


void importarDatos(struct JsonInfo** head) {
    char* filename = (char*)malloc(100 * sizeof(char)); // Nombre del archivo JSON
 
    printf("Put the PATH of the .JSON: \n");
    scanf("%s", filename);
    
    // Consumir el newline sobrante
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    fuap(filename, head);
 
    // Lógica para la importación de datos
    free(filename);
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
    struct JsonInfo* contenidoJSON = NULL;

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
                importarDatos(&contenidoJSON);
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