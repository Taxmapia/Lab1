#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Nodo{
    int n_nodo;
    float x;
    float y;
    struct Nodo *sig;
};

typedef struct Nodo tNodo;
typedef tNodo *Lista;

int ciudad1, ciudad2, ciudad3;
Lista ListaDatos = NULL;
Lista ListaSolucion = NULL;

Lista CreaNodo(int indice, float x, float y)
{
    Lista aux;

    aux = (Lista)malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->n_nodo = indice;
        aux->x = x;
        aux->y = y;
        aux->sig = NULL;
    }
    else
    {
        system("cls");
        printf("\n\tERROR: No hay memoria suficiente para generar un nuevo Nodo.");
        printf("\n\tEste programa se cerrar%c.", 160);
        exit(1);
    }
    return aux;
}

Lista Lista_INSERTA_PRINCIPIO(Lista L, int indice, float x, float y)
{
    Lista pNodo;

    pNodo = CreaNodo(indice, x, y);
    pNodo->sig = L;
    L = pNodo;
    pNodo = NULL;

    return L;
}

Lista Lista_INSERTA_FINAL(Lista L, int indice, float x, float y)
{
    Lista pNodo, aux;

    pNodo = CreaNodo(indice, x, y);

    if (L == NULL)
        L = pNodo;
    else
    {
        aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = pNodo;
        aux = NULL;
    }
    pNodo = NULL;
    return L;
}

Lista Lista_ELIMINA(Lista L, int p)
{
    int cont = 1;
    Lista aux, aux2;

    aux = L;
    if (p == 1)
    {
        L = L->sig;
        aux->sig = NULL;
        free(aux);
    }
    else
    {
        while (cont < p-1)
        {
            aux = aux->sig;
            cont++;
        }
        aux2 = aux->sig;
        aux->sig = aux2->sig;
        aux2->sig = NULL;
        free(aux2);
    }
    return L;
}

void Lista_IMPRIME(Lista L)
{
    Lista aux;

    aux = L;
    printf("\n\n\tL -> ");
    while(aux != NULL)
    {
        printf("%d , %.2f, %.2f -> ", aux->n_nodo, aux->x, aux->y);
        aux = aux->sig;
    }
    printf("NULL");
}

void Lectura_archivo (void)
{
    FILE *archivo;
    int i=1, n_ciudades, indice;
    float coor_x, coor_y;
    char n_archivo[20];

    do
    {
        printf("Ingrese nombre del archivo: ");
        scanf("%s", n_archivo);

        archivo=fopen(n_archivo, "r");
        if(archivo!=NULL)
        {
            fscanf(archivo, "%d", &n_ciudades);
            printf("\nEl numero de ciudades es: %d", n_ciudades);
            fscanf(archivo, "%d", &ciudad1);
            fscanf(archivo, "%d", &ciudad2);
            fscanf(archivo, "%d", &ciudad3);
            printf("\nCiudades de inicio: %d, %d, %d", ciudad1, ciudad2, ciudad3);
            printf("\n");
                /*Insertamos todos los datos a una lista*/
                for(i=0;i<n_ciudades;i++){
                    fscanf(archivo, "%d", &indice);
                    fscanf(archivo, "%f", &coor_x);
                    fscanf(archivo, "%f", &coor_y);
                    /*Se insertan las primeras 3 ciudades a una lista*/
                    if(indice==ciudad1)
                    {
                        ListaSolucion = Lista_INSERTA_PRINCIPIO(ListaSolucion, indice, coor_x, coor_y);
                    }
                    else if (indice == ciudad2|| indice == ciudad3)
                    {
                        ListaSolucion = Lista_INSERTA_FINAL(ListaSolucion, indice, coor_x, coor_y);
                    }
                    if(i==0)
                    {
                        if((indice!=ciudad1)&&(indice!=ciudad2)&&(indice!=ciudad3))
                            ListaDatos = Lista_INSERTA_PRINCIPIO(ListaDatos, indice, coor_x, coor_y);
                    }
                    else
                    {
                        if((indice!=ciudad1)&&(indice!=ciudad2)&&(indice!=ciudad3))
                            ListaDatos = Lista_INSERTA_FINAL(ListaDatos, indice, coor_x, coor_y);
                    }
                }
                /*Termina el proceso*/
                if(i==n_ciudades)
                {
                    printf("\nLista solucion:\n");
                    Lista_IMPRIME(ListaSolucion);
                    printf("\n\nLista Datos:\n");
                    Lista_IMPRIME(ListaDatos);
                }
                fclose(archivo);
        }
        else
        {
            printf("No se encontr%c el archivo.\n\n", 162);
        }
    }while(i==0);
}

void TSP(void){
Lista Listasolucion = NULL;

}

int main()
{
    Lectura_archivo();
    return 0;
}
