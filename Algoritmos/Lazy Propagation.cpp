//Hecho por: Mariola Camacho Lie
//Fecha: 4 de Junio de 2018
//SPOJ - LITE
//dado un arreglo de luces apagado inicialmente, puedes cambiar el estado de las luces de un rango y preguntar cuántas luces están encendidas en un rango
#include<bits/stdc++.h>
using namespace std;
struct ura
{
    int p[2];
} ST[400005];
int A[400005], N, Q, lazy[400005], a, b, c;
void crear(int i, int j, int nodo)
{
    if(i==j)
    {
        ST[nodo].p[0]++;
        return;
    }
    int mitad=(i+j)/2;
    int hijo_izq=2*nodo+1;
    int hijo_der=2*nodo+2;
    crear(i, mitad, hijo_izq);
    crear(mitad+1, j, hijo_der);
    ST[nodo].p[0]=ST[hijo_izq].p[0]+ST[hijo_der].p[0];
}
void actualizar(int i, int j, int nodo, int a, int b)
{
    int p0, p1;
    if(lazy[nodo]!=0)
    {
        p0=ST[nodo].p[0];
        p1=ST[nodo].p[1];
        if(lazy[nodo]%2==1)
        {
            ST[nodo].p[0]=p1;
            ST[nodo].p[1]=p0;
        }
        if(i!=j)
        {
            lazy[2*nodo+1]+=lazy[nodo];
            lazy[2*nodo+2]+=lazy[nodo];
        }
        lazy[nodo]=0;
    }
    if(a>j || b<i)
        return;
    if(i>=a && j<=b)
    {
        p0=ST[nodo].p[0];
        p1=ST[nodo].p[1];
        ST[nodo].p[0]=p1;
        ST[nodo].p[1]=p0;
        if(i!=j)
        {
            lazy[2*nodo+1]++;
            lazy[2*nodo+2]++;
        }
        return;
    }
    int mitad=(i+j)/2;
    int hijo_izq=2*nodo+1;
    int hijo_der=2*nodo+2;
    actualizar(i, mitad, hijo_izq, a, b);
    actualizar(mitad+1, j, hijo_der, a, b);
    ST[nodo].p[0]=ST[hijo_izq].p[0]+ST[hijo_der].p[0];
    ST[nodo].p[1]=ST[hijo_izq].p[1]+ST[hijo_der].p[1];
}
int query(int i, int j, int nodo, int a, int b)
{
    if(j<a || i>b)
        return 0;
    int p0, p1;
    if(lazy[nodo]!=0)
    {
        p0=ST[nodo].p[0];
        p1=ST[nodo].p[1];
        if(lazy[nodo]%2==1)
        {
            ST[nodo].p[0]=p1;
            ST[nodo].p[1]=p0;
        }
        if(i!=j)
        {
            lazy[2*nodo+1]+=lazy[nodo];
            lazy[2*nodo+2]+=lazy[nodo];
        }
        lazy[nodo]=0;
    }
    if(i>=a && j<=b)
        return ST[nodo].p[1];
    int mitad=(i+j)/2;
    int hijo_izq=2*nodo+1;
    int hijo_der=2*nodo+2;
    return query(i, mitad, hijo_izq, a, b)+query(mitad+1, j, hijo_der, a, b);
}
int main()
{
    scanf("%d %d", &N, &Q);
    crear(0, N-1, 0);
    for(int i=0; i<Q; i++)
    {
        scanf("%d %d %d", &a, &b, &c);
        if(a==0)
            actualizar(0, N-1, 0, b-1, c-1);
        else if(a==1)
            printf("%d\n", query(0, N-1, 0, b-1, c-1));
    }
    return 0;
}
