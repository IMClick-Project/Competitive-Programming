//Hecho por: Mariola Camacho Lie
//Fecha: 4 de Junio de 2018
//HackerEarth - Disjoint Set Union
//dados N nodos, cada vez que se da la orden de unir dos componentes, imprima el tamaño de todos los componentes (en orden creciente) hasta el momento.
#include<bits/stdc++.h>
using namespace std;
int N, x, y, h[1005], tam[1005], dad[1005], M, res[1005];
int padre(int p)
{
    if(dad[p]!=p)
        dad[p]=padre(dad[p]);
    return dad[p];
}
void unir(int a, int b)
{
    int ra=padre(a);
    int rb=padre(b);
    if(ra!=rb)
    {
        if(h[ra]<h[rb])
            tam[rb]+=tam[ra], dad[ra]=rb, tam[ra]=0;
        else
            tam[ra]+=tam[rb], dad[rb]=ra, tam[rb]=0;
        if(h[ra]==h[rb])
            h[ra]++;
    }
}
void imprimir()
{
    for(int i=1; i<=N; i++)
        res[i]=tam[i];
    sort(res+1, res+N+1);
    for(int i=1; i<=N; i++)
        if(res[i]!=0)
            printf("%d ", res[i]);
    printf("\n");
}
int main()
{
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++)
        dad[i]=i, h[i]=tam[i]=1;
    for(int i=0; i<M; i++)
        scanf("%d %d", &x, &y), unir(x,y), imprimir();
    return 0;
}
