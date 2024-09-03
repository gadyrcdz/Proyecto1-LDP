#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <hpdf.h>
#include "cJSON.h"


#define MAX_CATEGORIAS 100

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

struct Mes{

    char* nombre;
    int venta;
    struct Mes* next;
    
};

struct DiaVenta {
    char* nombreDia; // Nombre del día de la semana
    int totalVentas;    // Total de ventas del día
};

struct DiaVenta ventasPorDia[7] = {
    {"LUNES", 0}, {"MARTES", 0}, {"MIERCOLES", 0}, {"JUEVES", 0},
    {"VIERNES", 0}, {"SABADO", 0}, {"DOMINGO", 0}
};



struct Categoria {
    char* nombre;
    int ventas_totales;
};



/////////////////////////////////////////////////IMPORTACION DE DATOS/////////////////////////////////////////////////////////////////////////////////////
// nodos de JSON
/// @brief 
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

// Función para crear un objeto JSON a partir de JsonInfo
cJSON* CrearJsonObject(struct JsonInfo* info) {
    cJSON* item = cJSON_CreateObject();
    if (item == NULL) {
        printf("No se pudo crear el objeto JSON.\n");
        return NULL;
    }

    cJSON_AddNumberToObject(item, "venta_id", info->venta_id);
    cJSON_AddStringToObject(item, "fecha", info->fecha);
    cJSON_AddNumberToObject(item, "producto_id", info->producto_id);
    cJSON_AddStringToObject(item, "producto_nombre", info->producto_nombre);
    cJSON_AddStringToObject(item, "categoria", info->categoria);
    cJSON_AddNumberToObject(item, "cantidad", info->cantidad);
    cJSON_AddNumberToObject(item, "precio_unitario", info->precio_unitario);
    cJSON_AddNumberToObject(item, "total", info->total);

    return item;
}

// Función para guardar varios JsonInfo en un archivo JSON como un array
void GuardarInfoJson(struct JsonInfo* lista, const char* nombre_archivo) {
    // Crear el objeto JSON array principal
    cJSON* root = cJSON_CreateArray();
    if (root == NULL) {
        printf("No se pudo crear el objeto JSON array.\n");
        return;
    }

    // Iterar sobre la lista de JsonInfo y agregar cada uno al array
    struct JsonInfo* current = lista;
    while (current != NULL) {
        cJSON* item = CrearJsonObject(current);
        if (item != NULL) {
            cJSON_AddItemToArray(root, item);
        }
        current = current->next;
    }

    // Escribir el objeto JSON array en un archivo
    FILE* archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        cJSON_Delete(root);
        return;
    }

    char* cadena_json = cJSON_Print(root);
    if (cadena_json == NULL) {
        printf("No se pudo convertir el objeto JSON a una cadena.\n");
        fclose(archivo);
        cJSON_Delete(root);
        return;
    }

    fprintf(archivo, "%s", cadena_json);
    fclose(archivo);
    free(cadena_json);
    cJSON_Delete(root);
}



// agrega los nodos JSON a la lista
/// @brief 
/// @param head 
/// @param venta_id 
/// @param fecha 
/// @param producto_id 
/// @param producto_nombre 
/// @param categoria 
/// @param cantidad 
/// @param precio_unitario 
/// @param total 
/// @return 
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
/// @brief 
/// @param head 
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
/// @brief 
/// @param filename 
/// @return 
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
/// @brief 
/// @param filename 
/// @param head 
/// @return 
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
/// @brief 
/// @param head 
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
/// @brief 
/// @param head 
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
/// @brief 
/// @param head 
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
/// @brief 
/// @param head 
/// @param isCantidad 
/// @return 
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

/// @brief 
/// @param head 
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
    // Se crea un arreglo para almacenar la frecuencia de cada valor
    int frecuencia[1000] = {0};  // Según sea el valor, va a estar entre 0 y 999
    struct JsonInfo* temp = head;
    int valor;

    while (temp != NULL) {
        if (isCantidad) {
            valor = temp->cantidad;
        } else {
            valor = temp->precio_unitario;
        }

        // Incrementar la frecuencia del valor solo si está dentro del rango válido
        if (valor >= 0 && valor < 5000) {
            frecuencia[valor]++;
        } else {
            printf("Valor fuera de rango detectado: %d\n", valor);
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


/// @brief 
/// @param headlist 
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


/// @brief 
/// @param head 
void calcularTotal(struct JsonInfo* head){

    

    struct JsonInfo* temp = head;
    int total = 0;
    while(temp != NULL){
        total+=temp->total;
        temp = temp->next;
    }
    printf("El valor total de todas las ventas es de: %d\n", total);
}


/// @brief 
/// @param fecha 
/// @return 
const char* obtenerNombreMes(char* fecha) {
    // Arreglo con los nombres de los meses
    const char* meses[] = {
        "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", 
        "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
    };

    char mes[3];  // 2 dígitos para el mes + 1 para el carácter nulo
    strncpy(mes, fecha + 5, 2);
    mes[2] = '\0';  // Asegurarse de que la cadena esté terminada en '\0'

    int numMes = atoi(mes);  // Convertir la cadena a un entero

    return meses[numMes - 1];  // Retornar el nombre del mes
}

/// @brief 
/// @param fecha 
/// @return 
char* getYear(char* fecha) {
    char* anio = (char*)malloc(5 * sizeof(char));  // 4 dígitos para el año + 1 para el carácter nulo
    if (anio == NULL) {
        // Manejo de errores en caso de que la memoria no se pueda asignar
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    strncpy(anio, fecha, 4);
    anio[4] = '\0';  // Asegurarse de que la cadena esté terminada en '\0'

    return anio;  // Retorna la cadena de caracteres que contiene el año
}

/// @brief 
/// @param cadena 
/// @return 
char* convertirAMayusculas(char* cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = toupper(cadena[i]);
    }
    return cadena;
}

/// @brief 
/// @param head 
/// @param mesDado 
void calcularTotalMES(struct JsonInfo* head, char* mesDado){

    struct JsonInfo* temp = head;
    int total = 0;
    char* mesM = convertirAMayusculas(mesDado);
    while(temp != NULL){
        if(strcmp(obtenerNombreMes(temp->fecha), mesM)==0){
            total+=temp->total;
            temp = temp->next;
        }else{
            temp = temp->next;
        }
        
        
    }
    printf("El valor total de todas las ventas en el mes %s, es de: %d\n",mesDado, total);
}

/// @brief 
/// @param head 
/// @param anioDado 
void calcularTotalAnual(struct JsonInfo* head, char* anioDado){

    struct JsonInfo* temp = head;
    int total = 0;
  
    while(temp != NULL){
        if(strcmp(getYear(temp->fecha), anioDado)==0){
            total+=temp->total;
            temp = temp->next;
        }else{
            temp = temp->next;
        }
        
        
    }
    printf("El valor total de todas las ventas en el año de %s, es de: %d\n", anioDado, total);
}



/// @brief 
/// @param headlist 
void analizarDatos(struct JsonInfo* headlist) {
    char input[10];
    int opcion;

     do {
        printf("\n=== Menu de Analisis de Datos ===\n");
        printf("1. Total de Ventas General\n");
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
                calcularTotal(headlist);
                break;
            case 2:

                char* mesDado = (char*)malloc(100 * sizeof(char));

                printf("Escriba el nombre del mes que desea filtrar: \n");
                scanf("%s", mesDado);
                
                // Consumir el newline sobrante
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}

                calcularTotalMES(headlist, mesDado);
                break;
            case 3:
                
                char* anioDado = (char*)malloc(100 * sizeof(char));

                printf("Escriba el año que desea filtrar: \n");
                scanf("%s", anioDado);
                
                // Consumir el newline sobrante
                int a;
                while ((a = getchar()) != '\n' && a != EOF) {}

                calcularTotalAnual(headlist,anioDado);
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

/////////////////////////////////ANALISIS TEMPORAL///////////////////////////////////////////////////////////////////////////////////////////////////////////////

 

/// @brief 
/// @param head 
void mesConMayorVenta(struct JsonInfo* head) {
    int ventasPorMes[12] = {0};
    const char* meses[] = {
        "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", 
        "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
    };
    struct JsonInfo* temp = head;

    while (temp != NULL) {
        int mes = atoi(temp->fecha + 5); // Extraer el mes de la fecha en formato "YYYY-MM-DD"
        ventasPorMes[mes - 1] += temp->total;
        temp = temp->next;
    }

    int maxVenta = 0;
    int mesConMaxVenta = 0;
    for (int i = 0; i < 12; i++) {
        if (ventasPorMes[i] > maxVenta) {
            maxVenta = ventasPorMes[i];
            mesConMaxVenta = i + 1;
        }
    }

    printf("El mes con mayor venta es %s, con un total de %d\n",meses[mesConMaxVenta-1], maxVenta);
}


/// @brief 
/// @param head 
/// @param anio 
/// @param trimestre 
void calcularTasaCrecimiento(struct JsonInfo* head, int anio, int trimestre) {
    int inicioMes = (trimestre - 1) * 3 + 1;
    int finMes = inicioMes + 2;
    double totalTrimestre = 0.0;

    struct JsonInfo* temp = head;

    while (temp != NULL) {
        char mesStr[3];
        strncpy(mesStr, temp->fecha + 5, 2);
        mesStr[2] = '\0'; // Null-terminar la cadena
        int mes = atoi(mesStr);
        int anioVenta = atoi(temp->fecha);

        if (anioVenta == anio && mes >= inicioMes && mes <= finMes) {
            totalTrimestre += temp->total;
        }
        temp = temp->next;
    }

    // Suponiendo que la función calcula la tasa de crecimiento entre trimestres consecutivos
    double totalTrimestreAnterior = 0.0;
    int inicioMesAnterior = inicioMes - 3;
    int finMesAnterior = inicioMes - 1;

    // Si el trimestre anterior es el último trimestre del año, ajustar el rango
    if (inicioMesAnterior <= 0) {
        inicioMesAnterior = 10; // Octubre
        finMesAnterior = 12;    // Diciembre
    }

    temp = head;

    while (temp != NULL) {
        char mesStr[3];
        strncpy(mesStr, temp->fecha + 5, 2);
        mesStr[2] = '\0'; // Null-terminar la cadena
        int mes = atoi(mesStr);
        int anioVenta = atoi(temp->fecha);

        if (anioVenta == anio && mes >= inicioMesAnterior && mes <= finMesAnterior) {
            totalTrimestreAnterior += temp->total;
        }
        temp = temp->next;
    }

    double tasaCrecimiento = 0.0;
    if (totalTrimestreAnterior != 0) {
        tasaCrecimiento = ((totalTrimestre - totalTrimestreAnterior) / totalTrimestreAnterior) * 100;
    } else if (totalTrimestre > 0) {
        tasaCrecimiento = 100.0; // Si el trimestre anterior no tiene ventas, asumimos un crecimiento del 100%
    }

    printf("La tasa de crecimiento o decrecimiento en el trimestre %d del año %d es: %.2f%%\n", trimestre, anio, tasaCrecimiento);
}


/// @brief 
/// @param fecha 
/// @return 
const char* obtenerNombreDia(const char* fecha) {
    struct tm tm = {0};
    char buffer[10];
    int anio, mes, dia;

    // Extraer el año, mes y día de la fecha
    sscanf(fecha, "%d-%d-%d", &anio, &mes, &dia);

    // Rellenar la estructura tm
    tm.tm_year = anio - 1900; // Año desde 1900
    tm.tm_mon = mes - 1;     // Mes desde 0
    tm.tm_mday = dia;        // Día del mes
    tm.tm_hour = 0;         // Hora a 0
    tm.tm_min = 0;          // Minuto a 0
    tm.tm_sec = 0;          // Segundo a 0

    // Obtener el nombre del día de la semana
    mktime(&tm); // Normalizar la estructura tm
    strftime(buffer, sizeof(buffer), "%A", &tm);

    // Devolver el nombre del día de la semana
    return strdup(buffer);
}


/// @brief 
/// @param head 
/// @param ventasPorDia 
void acumularVentasPorDia(struct JsonInfo* head, struct DiaVenta ventasPorDia[7]) {
    struct JsonInfo* temp = head;

    while (temp != NULL) {
        const char* nombreDia = obtenerNombreDia(temp->fecha);
        
        // Buscar el día en el arreglo y sumar el total de ventas
        for (int i = 0; i < 7; i++) {
            if (strcmp(ventasPorDia[i].nombreDia, nombreDia) == 0) {
                ventasPorDia[i].totalVentas += temp->total;
                break;
            }
        }
        
        temp = temp->next;
    }
}




/// @brief 
/// @param head 
void diaMasActivo(struct JsonInfo* head) {
    double ventasPorDia[7] = {0}; // Array para almacenar las ventas por día de la semana (0=Domingo, 6=Sábado)
    struct JsonInfo* temp = head;

    while (temp != NULL) {
        struct tm tm = {0};
        char fecha[11];
        strncpy(fecha, temp->fecha, 10); // Copiar la fecha
        fecha[10] = '\0'; // Asegurar que la cadena esté terminada en nulo

        // Extraer el año, mes y día de la fecha
        sscanf(fecha, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);

        // Ajustar el año y el mes
        tm.tm_year -= 1900; // Año desde 1900
        tm.tm_mon -= 1;     // Mes desde 0

        // Obtener el día de la semana
        mktime(&tm);
        int diaSemana = tm.tm_wday; // 0=Domingo, 1=Lunes, ..., 6=Sábado

        // Acumulamos las ventas del día de la semana correspondiente
        ventasPorDia[diaSemana] += temp->total;

        temp = temp->next;
    }

    // Encontrar el día de la semana más activo
    int diaMasActivo = 0;
    for (int i = 1; i < 7; ++i) {
        if (ventasPorDia[i] > ventasPorDia[diaMasActivo]) {
            diaMasActivo = i;
        }
    }

    // Nombres de los días de la semana
    const char* nombresDias[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

    printf("El día de la semana más activo es %s con un total de %.2f ventas.\n",
           nombresDias[diaMasActivo], ventasPorDia[diaMasActivo]);
}





/// @brief //////////////////////////////////////////
/// @param headlist /
void analisisTemporal(struct JsonInfo* headlist,struct Mes* meses) {

    char input[10];
    int opcion;

    do {
        printf("\n=== Menu de Analisis de Datos ===\n");
        printf("1. Mes con mayor venta\n");
        printf("2. Dia mas activo\n");
        printf("3. Calcular Crecimiento de Ventas\n");
        printf("4. Regresar\n");
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
                mesConMayorVenta(headlist);
                break;
            case 2:

                diaMasActivo(headlist);
               
                break;
            case 3:

                int anio, trimestre;
                printf("Ingrese el año: ");
                scanf("%d", &anio);
                printf("Ingrese el trimestre (1-4): ");
                scanf("%d", &trimestre);

                // Consumir el newline sobrante
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                calcularTasaCrecimiento(headlist, anio, trimestre);
                break;

            case 4:
                return;
                
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion);

}

//////////////////ESTADISTICAS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Función para agregar o actualizar ventas en la lista de categorías

/// @brief 
/// @param categorias 
/// @param num_categorias 
/// @param nombre_categoria 
/// @param monto 
void agregarVentaCategoria(struct Categoria categorias[], int* num_categorias, const char* nombre_categoria, int monto) {
    for (int i = 0; i < *num_categorias; i++) {
        if (strcmp(categorias[i].nombre, nombre_categoria) == 0) {
            categorias[i].ventas_totales += monto;
            return;
        }
    }

    // Si la categoría no existe, agregarla
    if (*num_categorias < MAX_CATEGORIAS) {
        categorias[*num_categorias].nombre = strdup(nombre_categoria);
        categorias[*num_categorias].ventas_totales = monto;
        (*num_categorias)++;
    } else {
        printf("Número máximo de categorías alcanzado.\n");
    }
}

// Comparador para qsort
int compararCategorias(const void* a, const void* b) {
    return ((struct Categoria*)b)->ventas_totales - ((struct Categoria*)a)->ventas_totales;
}



// Función para mostrar el top 5 categorías
void mostrarTop5Categorias(struct JsonInfo* head) {
    struct Categoria categorias[MAX_CATEGORIAS];
    int num_categorias = 0;

    struct JsonInfo* temp = head;
    while (temp != NULL) {
        agregarVentaCategoria(categorias, &num_categorias, temp->categoria, temp->total);
        temp = temp->next;
    }

    // Ordenar las categorías por ventas totales
    qsort(categorias, num_categorias, sizeof(struct Categoria), compararCategorias);

    // Mostrar el top 5
    printf("Top 5 categorías con mayores ventas:\n");
    for (int i = 0; i < 5 && i < num_categorias; i++) {
        printf("%d. %s: %d\n", i + 1, categorias[i].nombre, categorias[i].ventas_totales);
        free(categorias[i].nombre); // Liberar memoria asignada
    }
}



void estadisticas() {
    printf("Generando estadísticas...\n");
    // Lógica para generar estadísticas
}

int main() {
    char input[10];
    int opcion;
    struct JsonInfo* contenidoJSON = NULL;
    struct Mes* mesesAnalisis = NULL;

    char* filename = "datos.json";

    // Comprobar si el archivo existe
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        // El archivo existe, cargar datos
        if (fuap(filename, &contenidoJSON) == 0) {
            printf("Datos cargados con éxito.\n");
        }
    } else {
        // El archivo no existe, iniciar lista vacía
        printf("No se encontró archivo de datos, comenzando con una lista vacía.\n");
    }


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
                GuardarInfoJson(contenidoJSON, "datos.json");
                break;
            case 2:
                procesarDatos(contenidoJSON);
                break;
            case 3:
                analizarDatos(contenidoJSON);
                break;
            case 4:
                analisisTemporal(contenidoJSON, mesesAnalisis);
                break;
            case 5:
                 mostrarTop5Categorias(contenidoJSON);
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