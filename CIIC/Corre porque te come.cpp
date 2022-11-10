//Hecho por: Mariola Camacho Lie
//Fecha: 30 de Mayo de 2018
//CIIC 2017 - Corre porque te come
//Heavy Light Decomposition, Lowest Common Ancestor and Kruskal's algorithm
//dado un grafo, de las mínimas capacidades de una arista por todos los caminos posibles de u a v, obtener la máxima
//construir el árbol de expansión máximo y en él, usando HLD, obtener la mínima arista del camino de u a v
#include<bits/stdc++.h>
#define costo first
#define ori second.first
#define des second.second
#define destino second
using namespace std;
vector < pair < int , pair < int , int  > > > aristas;
vector < pair < int , int > > ady[100005];
int N, M, a, b, c, dad[100005], h[100005], Q;
int cad, loga, ccad[100005], chead[100005], padre[20][100005], niveles[100005], ST[400005], STpos[400005], arre[100005], posarre, subtree[100005];
int dady(int p)
{
    if(dad[p]!=p)
        return dad[p]=dady(dad[p]);
    return p;
}
void unir(int a, int b)
{
    int ra=dady(a), rb=dady(b);
    if(h[ra]>h[rb])
        dad[rb]=ra;
    else
        dad[ra]=rb;
    if(h[ra]==h[rb])
        h[rb]++;
}
void dfs(int nodo, int anterior, int nivel)
{
    padre[0][nodo]=anterior, niveles[nodo]=nivel, subtree[nodo]=1;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].destino!=anterior)
            dfs(ady[nodo][i].destino, nodo, nivel+1), subtree[nodo]+=subtree[ady[nodo][i].destino];
}
int LCA(int a, int b)
{
    if(niveles[a]<niveles[b])
        swap(a,b);
    for(int i=loga; i>=0; i--)
        if(niveles[padre[i][a]]>=niveles[b])
            a=padre[i][a];
    if(a==b)
        return a;
    for(int i=loga; i>=0; i--)
        if(padre[i][a]!=padre[i][b])
            a=padre[i][a], b=padre[i][b];
    return padre[0][a];
}
void HLD(int nodo, int anterior, int costo)
{
    if(!chead[cad])
        chead[cad]=nodo;
    ccad[nodo]=cad;
    STpos[nodo]=posarre;
    arre[posarre++]=costo;
    int sc=-1, auxcosto;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].destino!=anterior)
            if(sc==-1 || subtree[sc]<subtree[ady[nodo][i].destino])
                sc=ady[nodo][i].destino, auxcosto=ady[nodo][i].costo;
    if(sc!=-1)
        HLD(sc, nodo, auxcosto);
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].destino!=anterior)
            if(ady[nodo][i].destino!=sc)
                cad++, HLD(ady[nodo][i].destino, nodo, ady[nodo][i].costo);
}
void construir(int nodo, int ini, int fin)
{
    if(ini==fin)
    {
        ST[nodo]=arre[ini];
        return;
    }
    construir(2*nodo+1, ini, (ini+fin)/2);
    construir(2*nodo+2, (ini+fin)/2+1, fin);
    ST[nodo]=min(ST[2*nodo+1], ST[2*nodo+2]);
}
int queryST(int nodo, int ini, int fin, int l, int r)
{
    if(ini>r || fin<l)
        return 2000000000;
    if(ini>=l && fin<=r)
        return ST[nodo];
    return min(queryST(2*nodo+1, ini, (ini+fin)/2, l, r), queryST(2*nodo+2, (ini+fin)/2+1, fin, l, r));
}
int query(int u, int v)
{
    if(u==v)
        return 2000000000;
    int cadu, cadv=ccad[v], res=2000000000;
    while(true)
    {
        cadu=ccad[u];
        if(cadu==cadv)
        {
            if(u==v)
                break;
            res=min(res, queryST(0, 0, N-1, STpos[v]+1, STpos[u]));
            break;
        }
        else
        {
            res=min(res, queryST(0, 0, N-1, STpos[chead[cadu]], STpos[u]));
            u=padre[0][chead[cadu]];
        }
    }
    return res;
}
int minedge(int a, int b)
{
    int lca=LCA(a, b);
    return min(query(a, lca), query(b,lca));
}
int main()
{
    scanf("%d %d", &N, &M);
    for(int i=0; i<M; i++)
        scanf("%d %d %d", &a, &b, &c), aristas.push_back(make_pair(c, make_pair(a, b)));
    sort(aristas.begin(), aristas.end());
    for(int i=1; i<=N; i++)
        dad[i]=i, h[i]=1;
    for(int i=M-1; i>=0; i--)
        if(dady(aristas[i].ori)!=dady(aristas[i].des))
            unir(aristas[i].ori, aristas[i].des), ady[aristas[i].ori].push_back(make_pair(aristas[i].costo, aristas[i].des)), ady[aristas[i].des].push_back(make_pair(aristas[i].costo, aristas[i].ori));
    dfs(1,1,1);
    loga=log2(N);
    for(int i=1; i<=loga; i++)
        for(int j=1; j<=N; j++)
            padre[i][j]=padre[i-1][padre[i-1][j]];
    cad=1, posarre=0;
    HLD(1, 1, 2000000000);
    construir(0, 0, N-1);
    scanf("%d", &Q);
    while(Q--)
        scanf("%d %d", &a, &b), printf("%d\n", minedge(a, b)-1);
    return 0;
}
