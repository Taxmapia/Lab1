#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//Estructura
typedef struct Nodo
{
    int nodos;
    int id;
    double x, y;
    struct Nodo *sig;
}tNodo;
typedef tNodo *Lista;

Lista Ls = NULL;
Lista Ln = NULL;

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
        dist = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
        dist_acum = dist_acum + dist;
        aux = aux->sig;
    }
    x1 = aux->x;
    y1 = aux->y;
    x2 = L->x;
    y2 = L->y;
    dist = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
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
Lista InsertarPosicion(Lista L, int id, double x ,double y, int p)
{
    Lista pNodo, aux;
    int i, largo;

    largo = LargoLista(L);
    pNodo = CreaNodo(id,x,y);
    if (p <= largo+1)
    {
        if (p == 1)
            L = InsertarInicio(L,id,x,y);
        else
        {
            if (p == largo+1)
                L = InsertarFinal(L,id,x,y);
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
void MostrarLista(Lista L)
{
   Lista aux = L;
   printf("-------------------------------------------------------------\n");
   printf("L");
   if (L != NULL)
    {
       while(aux != NULL)
       {
        printf("-> (%d,%.2lf,%.2lf) ",aux->id,aux->x,aux->y);
        aux = aux->sig;
       }
       //printf("-> (%d,%.2lf,%.2lf).\n",L->id,L->x,L->y);
       printf("\n-------------------------------------------------------------\n");
    }
    else 
    {
        printf("-> NULL\n");
    }
}
bool BuscarElemento(Lista L, int id)
{
    Lista aux;

    aux = L;
    while(aux != NULL)
    {
        if (aux->id == id)
        {
            return true;
        }
        else
        {
            aux = aux->sig;
        }
    }
    return false;
}
int LocalizarPosicion(Lista L, int id)
{
    Lista aux;
    int i;

    if (BuscarElemento(L,id))
    {
        aux = L;
        i = 1;
        while (aux->id != id)
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
    Lista C1= NULL, C2=NULL, C3=NULL;

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

            if(id == c1)
            {
                C1 = CreaNodo(id,x,y);
            }
            else if(id == c2)
            {
                C2 = CreaNodo(id,x,y);
            }
            else if(id == c3)
            {
                C3 = CreaNodo(id,x,y);
            }
            if((id != c1) && (id != c2) && (id != c3))
            {
                Ln = InsertarFinal(Ln,id,x,y);
            }
        }
        fclose(arch);
        printf("--------------------------------------------------\n\n\n");
        printf("**************************************************\n");
        printf("Nodos Iniciales:\n");
        Ls = CreaNodo(C1->id,C1->x,C1->y);
        Ls = InsertarFinal(Ls,C2->id,C2->x,C2->y);
        Ls = InsertarFinal(Ls,C3->id,C3->x,C3->y);
        printf("***************************************************\n\n\n");
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

        printf("\t<Lista Solucion Inicial>\n");
        MostrarLista(Ls);
        printf("\t<Lista Ciudades Restantes>\n");
        MostrarLista(Ln);
    return 0;
}
