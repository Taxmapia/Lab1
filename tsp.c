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

Lista Ln = NULL;
Lista Ls = NULL;

void MostrarLista(Lista L)
{
   Lista aux = L;
   printf("L\n");
   while(aux != NULL)
   {
    printf("-> %d \n",aux->id);
    aux = aux->sig;
   }
   
}
int DistanciaAcumulada(Lista L)
{
    Lista aux;
    double dist_acum, dist, x1, y1, x2, y2;
    aux = L;
    while(aux->sig != NULL)
    {
        x1 = aux->x;
        y1 = aux->y;
        x2 = aux->sig->x;
        y2 = aux->sig->y;
        dist = sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
        dist_acum = dist_acum + distancia;
        aux = aux->sig;
    }
    x1 = aux->x;
    y1 = aux->y;
    x2 = L->x;
    y2 = L->y;
    distancia = sqrt(pow(Cx1 - Cx2,2) + pow(Cy1 - Cy2,2));
    dist_acum += dsit;

    return acum;
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
            if (id == c1||id == c2||id == c3)
            {
                Ls = InsertarFinal(Ls,id,x,y);
            }
            else
            {
                Ln = InsertarFinal(Ln,id,x,y);
            }
            MostrarLista(Ls);
            MostrarLista(Ln);
    	}
    	fclose(arch);
    }
    else
    {
        printf("\nEl archivo no se ha podido leer");
        printf("\nEjecute el programa ingresando la instancia.");
        printf("\nEj: ./Tsp burma14.tsp\n");
    }
    
}
//Main
int main(int argc , char* argv[])
{

	LecturaArchivo(argv[1]);


    return 0;
}

