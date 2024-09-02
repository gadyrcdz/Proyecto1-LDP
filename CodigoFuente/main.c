
#include <stdio.h> 
#include "cJSON.h" 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h> 
#include <limits.h>


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

/////////////////////////////////////////////////IMPORTACION DE DATOS/////////////////////////////////////////////////////////////////////////////////////
// nodos de JSON
struct JsonInfo* AgregarinfoJson(int venta_id,char* fecha,int producto_id,char* producto_nombre,char* categoria,int cantidad,int precio_unitario,int total) {
    struct JsonInfo* nuevoJson = (struct JsonInfo*)malloc(sizeof(struct JsonInfo));
    int notFoundN = -1;
    if (nuevoJson == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    //Asifnacion de la fecha del JSON al struct 
    if(strcmp(fecha, "NOT")==0){
       printf("No se incluye el apartado de FECHA!!\n");
    }
    nuevoJson->fecha = malloc(strlen(fecha) + 1);
    if (nuevoJson->fecha == NULL) {
        printf("Date not found.\n");
        exit(1);
    }
    strcpy(nuevoJson->fecha, fecha);
    //Asignacion de producto nombre al Struct
    if(strcmp(producto_nombre, "NOT")==0){
       printf("No se incluye el apartado de PRODUCTO_NOMBRE!!\n");
    }
    nuevoJson->producto_nombre = malloc(strlen(producto_nombre) + 1);
    if (nuevoJson->producto_nombre == NULL) {
        printf("Producto_nombre not found.\n");
        exit(1);
    }
    strcpy(nuevoJson->producto_nombre, producto_nombre);
    //Asignacion de categoria al struct
    if(strcmp(categoria, "NOT")==0){
       printf("No se incluye el apartado de CATEGORIA!! \n");
    }
    nuevoJson->categoria = malloc(strlen(categoria) + 1);
    if (nuevoJson->categoria == NULL) {
        printf("categoria not found.\n");
        exit(1);
    }
    strcpy(nuevoJson->categoria, categoria);
    //asignacion de venta id al struct
    if(venta_id == 0){
        nuevoJson->venta_id = notFoundN;
        printf("No se incluye el apartado de VENTA_ID!!\n");
    }else{
        nuevoJson->venta_id = venta_id;
    }
    
    //asignacion del producto id al struct
    if(producto_id == 0){
        nuevoJson->producto_id = notFoundN;
        printf("No se incluye el apartado de PRODUCTO_ID!!\n");
    }else{
        nuevoJson->producto_id = producto_id;
    }
    //asignacion de la cantidad al struct
    if(cantidad == 0){
        nuevoJson->cantidad = notFoundN;
        printf("No se incluye el apartado de CANTIDAD!!\n");
    }else{
        nuevoJson->cantidad = cantidad;
    }
    //Asignacion del precio unitario al struct
    if(precio_unitario == 0){
        nuevoJson->precio_unitario = notFoundN;
        printf("No se incluye el apartado de PRECIO_UNITARIO!!\n");
    }else{
        nuevoJson->precio_unitario = precio_unitario;
    }
    //asignacion del total al struct
    if(total == 0){
        nuevoJson->total = notFoundN;
        printf("No se incluye el apartado de TOTAL!!\n");
    }else{
        nuevoJson->total = total;
    }
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
    int valor;
    int valor2;
    int valor3;
    int valor4;
    int valor5;
    char* notVal;
    char* notVal2;
    char* notVal3;
    for (int i = 0; i < arraySize; i++) {

        printf("Informacion del bloque JSON %d\n", i+1);
        cJSON *item = cJSON_GetArrayItem(jsonArray, i);
        cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
        if(venta_id == NULL){
            valor = 0;
        }else{
            valor = venta_id->valueint;
        }
        cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
        if(fecha == NULL){
            notVal = "NOT";
        }else{
            notVal = fecha->valuestring;
        }
        cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
        if(producto_id == NULL){
            valor2 = 0;
        }else{
            valor2 = producto_id->valueint;
        }
        cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
        if(producto_nombre == NULL){
            notVal2 = "NOT";
        }else{
            notVal2 = producto_nombre->valuestring;
        }
        cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
        if(categoria == NULL){
            notVal3 = "NOT";
        }else{
            notVal3 = categoria->valuestring;
        }
        cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
        if(cantidad == NULL){
            valor3 = 0;
        }else{
            valor3 = cantidad->valueint;
        }
        cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
        if(precio_unitario == NULL){
            valor4 = 0;
        }else{
            valor4 = precio_unitario->valueint;
        }
        cJSON *total = cJSON_GetObjectItem(item, "total");
        if(total == NULL){
            valor5 = 0;
        }else{
            valor5 = total->valueint;
        }

        // Imprimir los valores
        if(agregarJSONLISTA(head,valor,notVal,valor2,notVal2,notVal3,valor3, valor4,valor5)== 0){
            printf("Info JSON agregada con exito!\n");  
        }
        
        
    }
    // Liberar la memoria
    cJSON_Delete(jsonArray);
    free(jsonString);

    
} 

// imprime structs de json
void imprimirAllJSON(struct JsonInfo* head) {
    struct JsonInfo* temp = head;

    if(temp == NULL){
        printf("No se han ingresado datos!!\n");
    }
    while (temp != NULL) {
        printf("Venta ID: %d, Fecha:%s, ID de producto:%d, Nombre de producto:%s, Categoria:%s, Cantidad:%d, Precio unitario:%d, Total:  %d\n", temp->venta_id, temp->fecha, temp->producto_id,temp->producto_nombre,temp->categoria,temp->cantidad,temp->precio_unitario,temp->total);
        temp = temp->next;
    }
}

void importarDatos(struct JsonInfo** head) {
    char* filename = (char*)malloc(100 * sizeof(char)); // Nombre del archivo JSON
 
    printf("Put the PATH of the .JSON: \n");
    scanf("%s", filename);
    
    // Consumir el newline sobrante
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    fuap(filename, head);
    // Liberacion de memoria del file
    free(filename);
    
}
/////////////////////////////////////////////PROCESAR DATOS/////////////////////////////////////////////////////////////////////////////////////////
void eliminarDuplicados(struct JsonInfo* head) {
    struct JsonInfo* current = head;
    struct JsonInfo* prev = NULL;

    while (current != NULL) {
        struct JsonInfo* temp = current->next;
        prev = current;

        while (temp != NULL) {
            if (current->venta_id == temp->venta_id) {
                // Si hay un duplicado, imprimir el ID del registro que será eliminado
                printf("Duplicado encontrado y eliminado: Venta ID %d\n", temp->venta_id);

                // Eliminar el nodo duplicado
                prev->next = temp->next;
                free(temp->fecha);
                free(temp->producto_nombre);
                free(temp->categoria);
                free(temp);
                temp = prev->next;
            } else {
                prev = temp;
                temp = temp->next;
            }
        }

        current = current->next;
    }
}




// Calcula la media de un campo específico en la lista
double calcularMedia(struct JsonInfo* head, int isCantidad) {
    struct JsonInfo* temp = head;
    int suma = 0;
    int contador = 0;

    while (temp != NULL) {
        if (isCantidad) {
            suma += temp->cantidad;
        } else {
            suma += temp->precio_unitario;
        }
        contador++;
        temp = temp->next;
    }

    return (contador > 0) ? (double)suma / contador : 0.0;
}

void completarDatosFaltantes(struct JsonInfo* head) {
    struct JsonInfo* temp = head;

    // Calcular media para cantidad y precio_unitario
    double mediaCantidad = calcularMedia(head, 1);
    double mediaPrecioUnitario = calcularMedia(head, 0);

    while (temp != NULL) {
        if (temp->cantidad == -1) {
            printf("Cantidad faltante encontrada en venta ID %d. Completando con la media: %f\n", temp->venta_id, mediaCantidad);
            temp->cantidad = (int)round(mediaCantidad);
        }
        if (temp->precio_unitario == -1) {
            printf("Precio unitario faltante encontrado en venta ID %d. Completando con la media: %f\n", temp->venta_id, mediaPrecioUnitario);
            temp->precio_unitario = (int)round(mediaPrecioUnitario);
        }
        temp = temp->next;
    }
}


// Función para encontrar la moda en un campo específico
int calcularModa(struct JsonInfo* head, int isCantidad) {
    // se crea un arreglo para almacenar la frecuencia de cada valor
    int frecuencia[1000] = {0};  // segun sea el valor, va a estar entre 0 y 999
    struct JsonInfo* temp = head;
    int valor;

    while (temp != NULL) {
        if (isCantidad) {
            valor = temp->cantidad;
        } else {
            valor = temp->precio_unitario;
        }
        // Incrementar la frecuencia del valor
        if (valor != -1) {  // Ignorar valores que fueron marcados como faltantes
            frecuencia[valor]++;
        }
        temp = temp->next;
    }

    // Encontrar el valor con mayor frecuencia
    int moda = -1;
    int maxFrecuencia = -1;
    for (int i = 0; i < 1000; i++) {
        if (frecuencia[i] > maxFrecuencia) {
            maxFrecuencia = frecuencia[i];
            moda = i;
        }
    }

    return moda;
}


void completarDatosFaltantesConModa(struct JsonInfo* head) {
    struct JsonInfo* temp = head;
    // Calcular moda para cantidad y precio_unitario
    int modaCantidad = calcularModa(head, 1);
    int modaPrecioUnitario = calcularModa(head, 0);

    while (temp != NULL) {
        if (temp->cantidad == -1) {
            printf("Cantidad faltante encontrada en venta ID %d. Completando con la moda: %d\n", temp->venta_id, modaCantidad);
            temp->cantidad = modaCantidad;
        }
        if (temp->precio_unitario == -1) {
            printf("Precio unitario faltante encontrado en venta ID %d. Completando con la moda: %d\n", temp->venta_id, modaPrecioUnitario);
            temp->precio_unitario = modaPrecioUnitario;
        }
        temp = temp->next;
    }
}

void procesarDatos(struct JsonInfo* headlist) {

    char input[10];
    int opcion;

     do {
        printf("\n=== Menu de Procesamiento de Datos ===\n");
        printf("1. Completar datos faltantes con moda\n");
        printf("2. Completar datos faltantes con mediana\n");
        printf("3. Eliminar Datos Duplicados\n");
        printf("4. Mostar Contenido\n");
        printf("5. Regresar\n");
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
                completarDatosFaltantesConModa(headlist);
                break;
            case 2:
                completarDatosFaltantes(headlist);
                break;
            case 3:
                eliminarDuplicados(headlist);
                break;

            case 4:
                // Imprimir los datos procesados
                imprimirAllJSON(headlist);
                break;
            case 5:
                return;
                
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion);

}
////////////////////ANALISIS DE DATOS/////////////////////////////////////////////////////////////////////////////////////////////////////////

void analizarDatos(struct JsonInfo* headlist) {
    char input[10];
    int opcion;

     do {
        printf("\n=== Menu de Analisis de Datos ===\n");
        printf("1. Total de Ventas\n");
        printf("2. Total de Ventas Mensuales\n");
        printf("3. Total de Ventas Anuales\n");
        printf("4. Mostar Contenido\n");
        printf("5. Regresar\n");
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
                break;
            case 2:
                
                break;
            case 3:
                
                break;

            case 4:
                // Imprimir los datos procesados
                imprimirAllJSON(headlist);
                break;
            case 5:
                return;
                
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion);
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
                procesarDatos(contenidoJSON);
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