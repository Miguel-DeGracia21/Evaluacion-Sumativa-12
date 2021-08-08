#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char nombreApellido[30];
    char Telefono[20];
	char correoElectronico[30];  //Se definen estructuras para crear un nuevo tipo de datos y asi almacenar cadenas con las especificaciones pedidas para el programa
}registro;
int imprimirMenu(void);
void formularioRegistros(registro ahoraRegistro[], int k, int g);
void mensajeRegistroLleno(int g);
void imprimirListaRegistros(int g, int *i, registro ahoraRegistro[]);
void mostrarValorIncorrecto(void);
void eliminarRegistro(registro ahoraRegistro[], int *k, int g);
void errorEnArchivos(FILE * ptr);
void regresarAlMenu(void);
int main(){
    //Bloque de declarativa de variables
    
    /*Varibles para el registro*/
    registro arreRegistro[30];
    int i = 0;
    
    /*Otras variables*/
    int g, respuesta;
    
    //Bloque de Instrucciones
    system("title Sistema de Registros"); //Para cambiar el nombre de la ventana de la ejecucion
    system("color 0C"); //Para cambiar el color de las letras
    do{
        respuesta = imprimirMenu();
        
            switch(respuesta) //switch con opciones para el momento en el que el arreglo este lleno notifique al usuario.
            {
                case 1:
                    g = 12;
                    (i < 30) ? formularioRegistros(arreRegistro, i, g) : mensajeRegistroLleno(g); //Expresion condicional que simplifica la sintaxis del if-else
                    i++;                                                            //Si se cumple la condicion se ejecuta formularioRegistros(), si no mensajeRegistroLleno()
                    break;   
                case 2:
                    g = 12;
                    imprimirListaRegistros(g, &i, arreRegistro); //Se imprime la lista de registros
                    break;
                case 3:
                    g = 12;
                    eliminarRegistro(arreRegistro, &i, g); //Para elminar un registro de la lista
                    break;
                case 4:
                    return 0;
                    break;
                
                default:
                    mostrarValorIncorrecto();
                    break;  
            }
        
    }while(1);
    
    return 0;
}
/*Bloque de Funciones*/
int imprimirMenu(void) //Menu creado para que el usuario revise las diferentes opciones
{
    //Bloque de declarativa de variables
    int resp;
    //Bloque de Instrucciones
    system("color 0C");
    printf("\t   \\                                       /\n");
    printf("\t    \\\t            Registros             /"); 
    printf("\n\t     \\___________________________________/\n\n");
    printf("           \"BIENVNIDO A TU SERVICIO DE REGISTROS\"\n\n");
    printf("\t ____________________________________________\n");
    printf("\t|____________________________________________|\n");
    printf("\t|\t\tMenu Principal\t\t     |\n\t|\t\t\t\t\t     |");
    printf("\n\t|	Agregar un registro -> (1)           |\n");
    printf("\t| 	Ver registros -> (2)                 |");
    printf("\n\t|	Eliminar registros -> (3)            |");
    printf("\n\t|\tCerrar -> (4) \t                     |");
    printf("\n\t|____________________________________________|\n");
    printf("\t|____________________________________________|\n");
    printf("\nEligir opcion: ");
    scanf("%d", &resp);
    return (resp);
}

void formularioRegistros(registro ahoraRegistro[], int k, int g) //Funcion que va almacenando en un espacio del arreglo el nuevo registro
{
	
    /*Manejo de archivos*/
    FILE * arch;
    if (g == 12 && k == 0) //Dependiendo del registro se creará un archivo de texto para el mismo
    {
        arch = fopen("Registros.txt","w");
    }
    else
        if (g == 12 && k > 0) //Si el registro ya posee datos, los demás se irán anexando al final
        {
            arch = fopen("Registros.txt","a");
        }
    errorEnArchivos(arch); //Funcion para el manejo de errores
   
    //Bloque de Instrucciones
    system("color 0C");
    system("cls"); //Funcion para limpiar la pantalla
    fflush(stdin); //Se usa para limpiar el buffer de entrada para que no de error por ocupar demasiada memoria.
    printf("\nIngrese los siguientes datos->\n");
    printf("\n\t* Ingrese el nombre y apellido: ");
    fgets(ahoraRegistro[k].nombreApellido,30,stdin);
    strtok(ahoraRegistro[k].nombreApellido,"\n"); //Funcion para recortar un caracter de una cadena, en este caso el "\n" que agrega el fgets
    printf("\n\t* Ingrese el numero telefonico: ");
    fgets(ahoraRegistro[k].Telefono,30,stdin);
    strtok(ahoraRegistro[k].Telefono,"\n");
    printf("\n\t* Ingrese el correo electronico:  ");
    fgets (ahoraRegistro[k].correoElectronico,30,stdin);
    strtok(ahoraRegistro[k].correoElectronico,"\n");
    fprintf(arch,"%s  %s %s\n",ahoraRegistro[k].nombreApellido,ahoraRegistro[k].Telefono,ahoraRegistro[k].correoElectronico); //Funcion que va escribiendo los registros en el archivo de texto
    printf("____________________________________________________________");
    fclose(arch); //Para cerrar el archivo
    
    regresarAlMenu();
}
void mensajeRegistroLleno(int g) //Funcion  que se ejecuta en el momento que el arreglo se llena.
{
    //Bloque de Instrucciones
    system("color 0C");
    system("cls");
    printf("\t\tEl registro ya esta lleno", g);
    regresarAlMenu();
}
void imprimirListaRegistros(int g, int *i, registro ahoraRegistro[]) //Funcion para la lista de datos del registro 
{
    //Bloque de declarativa de variables
    int h;
    //Bloque de Instrucciones
    system("color 0C");
    system("cls");
    printf("\t       \\                                /\n");
    printf("\t\t\\       Lista de Registros     /");
    printf("\n\t         \\____________________________/\n");
    printf("%d/30 Registros", *i);
    printf("\n");
    for (h = 0; h < *i; h++)
    {
        printf("\nRegistro %d\nNombre: %s\nTelefono: %s\nCorreo: %s\n", h+1, ahoraRegistro[h].nombreApellido, ahoraRegistro[h].Telefono, ahoraRegistro[h].correoElectronico);
        printf("____________________________________________\n");
    }
    
    regresarAlMenu();
}
void mostrarValorIncorrecto(void) //Funcion en caso de que alguien inserte un valor no esperado
{
    //Bloque de Instrucciones
    system("color 0C");
    system("cls");
    printf("\n\t\tDato incorrecto ingresado\n");
    regresarAlMenu();
}
void errorEnArchivos(FILE * ptr)
{
    if (ptr == NULL)
    {
        printf("Error en manejo de archivos\n");
        exit(EXIT_FAILURE);
    }
}
void eliminarRegistro(registro ahoraRegistro[], int *k, int g) //Para eliminar un registro de un arreglo
{
    //Bloque de declarativa de variables
    FILE * arch;
    char elim[30];
    int j2, h, opel, j, r;
    registro auxRegistro[30];
    //Manejo de archivos
    if (g == 12)
    {
        arch = fopen("Registros.txt","w"); //Se abre en modo "w" porque se reescribirá el archivo de texto
    }
    errorEnArchivos(arch);  
    //Bloque de Instrucciones
    system("cls");
    printf("\t       \\                                        /\n");
    printf("\t\t\\           Eliminar Registros         /");
    printf("\n\t         \\____________________________________/\n\n");
        
    if (*k == 0)
    {
        printf("Todavia no hay registros\n");
    }
    else
    {
        j2 = 0;
        fflush(stdin);
        printf("Introduzca el nombre y apellido: ");
        fgets(elim,30,stdin);
        strtok(elim,"\n");
        for (h = 0; h < *k; h++) {
            if (strcmp(elim,ahoraRegistro[h].nombreApellido) == 0) { //Se compara el nombre ingresado con los nombres de los registros
                printf("\nDesea eliminar? -> %s %s %s",ahoraRegistro[h].nombreApellido, ahoraRegistro[h].Telefono, ahoraRegistro[h].correoElectronico);
                printf("\n\nSi = 1 / No = 2: ");
                scanf("%d",&opel);
                if (opel == 1) {
                    for (j = 0; j < *k; j++) {
                        if (j != h) {
                            auxRegistro[j2] = ahoraRegistro[j]; //Utilizamos un arreglo auxiliar para guardar todos los datos menos el que queremos eliminar de la lista
                            j2++;
                        }
                    }
                    *k = *k - 1; //Luego le disminuimos el numero de registros al arreglo principal
                    for (r = 0; r < *k; r++) {
                        strcpy(ahoraRegistro[r].nombreApellido, auxRegistro[r].nombreApellido); //Se reescribe el arreglo principal con los datos del arreglo auxiliar, ahora sin el registro eliminado
                        strcpy(ahoraRegistro[r].Telefono, auxRegistro[r].Telefono);
                        strcpy(ahoraRegistro[r].correoElectronico, auxRegistro[r].correoElectronico);
                        fprintf(arch,"%s  %s %s\n",ahoraRegistro[r].nombreApellido,ahoraRegistro[r].Telefono,ahoraRegistro[r].correoElectronico); //Se reescribe en el archivo de texto
                    }
                }
            }
        }
        fclose(arch);
    }   
    regresarAlMenu();
}
void regresarAlMenu(void) // Funcion para regresar al menu principal
{
    printf("\n\nPresione cualquier tecla para regresar al menu principal ->");
    getch();
    system("cls");
}
