#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


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

double DistanciaAcumulada(Lista L)
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
        dist_acum = dist_acum + dist;
        aux = aux->sig;
    }
    x1 = aux->x;
    y1 = aux->y;
    x2 = L->x;
    y2 = L->y;
    dist = sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
    dist_acum += dist;

    return dist_acum;
}
int LargoLista(Lista L)
{
    Lista aux= L;
    int i = 0;

    while (aux != NULL)
    {
        aux = aux->sig;
        i++;
    }
    return i;
}
Lista InsertarPosicion(Lista L, int id, double x ,double y, int p)
{
    Lista pNodo, aux;
    int i, largo;

    largo = LargoLista(L);
    pNodo = CreaNodo(id,x,y);
    if (p <= largo+1)
    {
        if (p == 1)
            L = InsertarInicio(L, x);
        else
        {
            if (p == largo+1)
                L = InsertarFinal(L, x);
            else
            {
                aux = L;
                i = 1;
                while (i < p-1)
                {
                    aux = aux->sig;
                    i = i+1;
                }
                pNodo->sig = aux->sig;
                aux->sig = pNodo;
                aux = NULL;
            }
        }
    }
    pNodo = NULL;
    return L;
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
        //aux = aux->sig;
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
Lista InsertarInicio(Lista L, int id, double x, double y)
{
    Lista pNodo;

    pNodo = CreaNodo(id,x,y);
    pNodo->sig = L;
    L = pNodo;
    pNodo = NULL;

    return L;
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
void MostrarLista(Lista L)
{
   Lista aux = L;
   printf("-------------------------------------------------------------\n");
   printf("L->");
   while(aux != NULL)
   {
    printf(" %d",aux->id);
    aux = aux->sig;
   }
   printf(" %d\n",L->id);
   printf("-------------------------------------------------------------\n");

}
int LocalizarPosicion(Lista L, int id)
{
Lista aux;
int i;

    if (BuscarElemento(L,id))
    {
    aux = L;
    i = 1;
    while (aux->info != id)
    {
        aux = aux->sig;
        i++;
    }
    return i;
}
    else
    {
      return -1;
    }
}
bool BuscarElemento(Lista L, int id)
{
Lista aux;

    aux = L;
    while(aux != NULL)
    {
        if (aux->info == id)
            return true;
        else
            aux = aux->sig;
    }
    return false;
}
Lista ActualizaLista(Lista L, int p, int id, double x, double y)
{
    Lista aux, auxNodo;
    int largo, i;

    largo = LargoLista(L);

    if ((p <= largo) || (L != NULL))
    {
        i = 1;
        aux = L;
        while (i < p)
        {
            aux = aux->sig;
            i++;
        }
        aux->id  = id;
        aux->x  = x;
        aux->y  = y;
        aux = NULL;
    }
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
            if (id == c1||id == c2||id == c3||id==(nodos)-1)
            {
                Ls = InsertarFinal(Ls,id,x,y);
            }
            else
            {
                Ln = InsertarFinal(Ln,id,x,y);
            }
    	}
    	fclose(arch);
        printf("******************************************\n");
        printf("\t<Lista Solucion>\n");
        MostrarLista(Ls);
        printf("\t<Lista Ciudades>\n");
        MostrarLista(Ln);
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
