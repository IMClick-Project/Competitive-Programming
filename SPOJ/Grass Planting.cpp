//Hecho por: Mariola Camacho Lie
//Fecha: 30 de Mayo de 2018
//SPOJ - GRASSPLA
//Heavy Light Decomposition, Lowest Common Ancestor and Lazy Propagation
//dado un árbol, plantar aumenta en uno cada arista del camino de u a v y queryST devuelve el valor de la arista u-v
#include<bits/stdc++.h>
using namespace std;
int padre[20][100005], niveles[100005], N, M, a, b, chead[100005], ccad[100005], cad, ST[400005], posarre, subtree[100005], STpos[100005], loga, lazy[400005];
char ins;
vector < int > ady[100005];
void dfs(int nodo, int anterior, int nivel)
{
    padre[0][nodo]=anterior, subtree[nodo]=1, niveles[nodo]=nivel;
    for(int i=0; i<ady[nodo].size(); i++)
        if(anterior!=ady[nodo][i])
            dfs(ady[nodo][i], nodo, nivel+1), subtree[nodo]+=subtree[ady[nodo][i]];
}
void HLD(int nodo, int anterior)
{
    if(!chead[cad])
        chead[cad]=nodo;
    ccad[nodo]=cad;
    STpos[nodo]=posarre++;
    int sc=-1;
    for(int i=0; i<ady[nodo].size(); i++)
        if(anterior!=ady[nodo][i])
            if(sc==-1 || subtree[sc]<subtree[ady[nodo][i]])
                sc=ady[nodo][i];
    if(sc!=-1)
        HLD(sc, nodo);
    for(int i=0; i<ady[nodo].size(); i++)
        if(anterior!=ady[nodo][i])
            if(sc!=ady[nodo][i])
                cad++, HLD(ady[nodo][i], nodo);
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
void actualizarST(int nodo, int ini, int fin, int l, int r)
{
    if(ini>r || fin<l)
        return;
    if(ini>=l && fin<=r)
    {
        lazy[nodo]++;
        return;
    }
    actualizarST(2*nodo+1, ini, (ini+fin)/2, l, r);
    actualizarST(2*nodo+2, (ini+fin)/2+1, fin, l, r);
}
int queryST(int nodo, int ini, int fin, int l)
{
    if(lazy[nodo])
    {
        if(ini!=fin)
        {
            lazy[2*nodo+1]+=lazy[nodo];
            lazy[2*nodo+2]+=lazy[nodo];
            lazy[nodo]=0;
        }
        else
        {
            ST[nodo]+=lazy[nodo];
            lazy[nodo]=0;
            return ST[nodo];
        }
    }
    if(ini==fin)
        return ST[nodo];
    if(l<=(ini+fin)/2)
        return queryST(2*nodo+1, ini, (ini+fin)/2, l);
    else
        return queryST(2*nodo+2, (ini+fin)/2+1, fin, l);
}
void actualizar(int u, int v)
{
    if(u==v)
        return;
    int cadu, cadv=ccad[v];
    while(true)
    {
        cadu=ccad[u];
        if(cadu==cadv)
        {
            if(u==v)
                break;
            actualizarST(0, 0, N-1, STpos[v]+1, STpos[u]);
            break;
        }
        else
        {
            actualizarST(0, 0, N-1, STpos[chead[cadu]], STpos[u]);
            u=padre[0][chead[cadu]];
        }
    }
}
void plantar(int a, int b)
{
    int lca=LCA(a, b);
    if(niveles[a]<niveles[b])
        swap(a,b);
    actualizar(a, lca);
    if(ccad[a]!=ccad[b]);
        actualizar(b, lca);
}
int main()
{
    scanf("%d %d", &N, &M);
    for(int i=0; i<N-1; i++)
        scanf("%d %d", &a, &b), ady[a].push_back(b), ady[b].push_back(a);
    dfs(1,1,1);
    loga=log2(N);
    for(int i=1; i<=loga; i++)
        for(int j=1; j<=N; j++)
            padre[i][j]=padre[i-1][padre[i-1][j]];
    cad=1, posarre=0;
    HLD(1,1);
    while(M--)
    {
        scanf(" %c %d %d", &ins, &a, &b);
        if(ins=='P')
            plantar(a, b);
        else
            printf("%d\n", niveles[a]>niveles[b] ? queryST(0, 0, N-1, STpos[a]) : queryST(0, 0, N-1, STpos[b]));
    }
    return 0;
}
