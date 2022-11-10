//Hecho por: Mariola Camacho Lie
//Fecha: 4 de Junio de 2018
//HackerEarth - Range Minimum Query
//dado un arreglo A, actualizar cambia el valor de alguna posición y query devuelve el valor mínimo de un rango en A
#include<bits/stdc++.h>
using namespace std;
int A[100005], ST[400005], N, M, a, b;
char c;
void crear(int i, int j, int nodo)
{
    if(i==j)
    {
        ST[nodo]=A[i];
        return;
    }
    int mitad=(i+j)/2;
    int hijo_izq=2*nodo+1;
    int hijo_der=2*nodo+2;
    crear(i, mitad, hijo_izq);
    crear(mitad+1, j, hijo_der);
    ST[nodo]=min(ST[hijo_izq],ST[hijo_der]);
}
int query(int a, int b, int i, int j, int nodo)
{
    if(b<i || a>j)
        return INT_MAX;
    if(a<=i && b>=j)
        return ST[nodo];
    int mitad=(i+j)/2;
    int hijo_izq=2*nodo+1;
    int hijo_der=2*nodo+2;
    return min(query(a, b, i, mitad, hijo_izq),query(a, b, mitad+1, j, hijo_der));
}
void actualizar(int ini, int fin, int nodo, int i, int v)
{
    if(ini==fin)
    {
        A[i]=v;
        ST[nodo]=v;
        return;
    }
    int mitad=(ini+fin)/2;
    int hijo_izq=2*nodo+1;
    int hijo_der=2*nodo+2;
    if(i>=ini && i<=mitad)
        actualizar(ini, mitad, hijo_izq, i, v);
    else
        actualizar(mitad+1, fin, hijo_der, i, v);
   ST[nodo]=min(ST[hijo_izq],ST[hijo_der]);
}
int main()
{
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++)
        scanf("%d", &A[i]);
    crear(0, N-1, 0);
    for(int i=0; i<M; i++)
    {
        scanf(" %c %d %d", &c, &a, &b);
        if(c=='q')
            printf("%d\n", query(a-1, b-1, 0, N-1, 0));
        else
            actualizar(0, N-1, 0, a-1, b);
    }
    return 0;
}
