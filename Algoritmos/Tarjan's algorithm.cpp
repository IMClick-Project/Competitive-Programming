//Hecho por: Mariola Camacho Lie
//Fecha: 4 de Junio de 2018
//HackerEarth - Articulation Points and Bridges
//dado un grafo, devuelve los puentes y puntos de articulación
#include<bits/stdc++.h>
#define lady pair < int , int >
using namespace std;
int val[1005], low[1005], N, M, a , b, t, respuntos, respuentes;
vector <int> ady[1005];
bool puntos[1005];
lady puentes[1005];
int Tarjan(int nodo, int anterior)
{
    val[nodo]=low[nodo]=++t;
    int hijos=0;
    for(int i=0; i<ady[nodo].size(); i++)
    {
        int destino=ady[nodo][i];
        if(destino==anterior)
            continue;
        if(!val[destino])
        {
            hijos++;
            Tarjan(destino, nodo);
            if(val[nodo]<=low[destino])
                puntos[nodo]=true;
            if(val[nodo]<low[destino])
            {
                puentes[respuentes].first=nodo;
                puentes[respuentes++].second=destino;
            }
            low[nodo]=min(low[nodo], low[destino]);
        }
        low[nodo]=min(low[nodo], val[destino]);
    }
    return hijos;
}
int main()
{
    scanf("%d %d", &N, &M);
    for(int i=0; i<M; i++)
    {
        scanf("%d %d", &a, &b);
        ady[a].push_back(b);
        ady[b].push_back(a);
    }
    for(int i=0; i<N; i++)
        if(!val[i]) Tarjan(i, N) > 1 ? puntos[i]=true : puntos[i]=false;
    for(int i=0; i<N; i++)
        if(puntos[i]) respuntos++;
    printf("%d\n", respuntos);
    for(int i=0; i<N; i++)
        if(puntos[i])  printf("%d ", i);
    printf("\n");
    printf("%d\n", respuentes);
    sort(puentes, puentes+respuentes);
    for(int i=0; i<respuentes; i++)
        printf("%d %d\n", puentes[i].first, puentes[i].second);
    return 0;
}
