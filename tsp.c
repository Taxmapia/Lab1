#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Estructura
typedef struct Nodo
{
    int nodos;
    int id;
    double x, y;
    struct Nodo *sig;
}tNodo;
typedef tNodo *Lista;

void MostrarLista(Lista L)
{
   Lista aux;
   printf("\nL");
   while(aux != NULL)
   {
	printf(" -> %d",aux->id);
	aux = aux->sig;
   }
}
Lista CreaNodo(int id, double x, double y)
{
    Lista aux;
    aux = (Lista)malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->id = id;
        aux->x = x;
        aux->y = y;
        aux->sig = NULL;
        printf("Nodo %d, tiene las coordenadas X: %.2lf , Y: %.2lf\n", aux->id, aux->x, aux->y);
        aux = aux->sig;
    }
    else
    {
        system("cls");
        printf("\n----------------------------------------------");
        printf("\n\tERROR: No Hay espacio suficiente.");
        printf("\n\tEste programa se cerrar%c.", 160);
        printf("\n----------------------------------------------");
        exit(1);
    }
    return aux;
}

Lista InsertarFinal(Lista L,int id, double x, double y)
{
    Lista pNodo, aux;
    pNodo = CreaNodo(id,x,y);
    if (L == NULL)
    {
        L = pNodo;
    }
    else 
    {
        aux = L;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = pNodo;
        aux = NULL;
    }
    pNodo = NULL;
    return L;
}

void LecturaArchivo(char n_arch[50])
{
    FILE *arch;
    int nodos, id, c1, c2, c3, i;
    double x, y;
	Lista L = NULL;


    arch = fopen(n_arch, "r");
    if (arch != NULL)
    {
	
        fscanf(arch, "%d", &nodos);
        printf("\nLa cantidad de ciudades es: %d", nodos);
        fscanf(arch, "%d", &c1);
        fscanf(arch, "%d", &c2);
        fscanf(arch, "%d", &c3);
        printf("\nCiudades de inicio: %d, %d, %d \n", c1, c2, c3);
        for (i = 0; i < nodos; i++)
        {
	    printf("--------------------------------------------------\n");
            fscanf(arch, "%d", &id);
            fscanf(arch, "%lf", &x);
            fscanf(arch, "%lf", &y);
            InsertarFinal(L,id,x,y);
            
    	}
    	fclose(arch);
    }
    else
    {
        printf("\nEl archivo no se ha podido leer");
        printf("\nEjecute el programa ingresando la instancia.");
        printf("\nEj: ./Tsp burma14.tsp\n");
    }
    
    MostrarLista(L);
}
//Main
int main(int argc , char* argv[])
{
	
	LecturaArchivo(argv[1]);
	

    return 0;
}

