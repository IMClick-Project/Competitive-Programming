//Hecho por: Mariola Camacho Lie
//Fecha: 28 de Mayo de 2018
//SPOJ - QTREE
//dado un árbol, change cambia el valor de la ith arista y query devuelve el valor de la arista máxima del camino de u a v
#include<bits/stdc++.h>
#define costo first
#define destino second.first
#define ind second.second
using namespace std;
string ins;
vector < pair < int , pair < int , int > > > ady[10005];
int T, N, a, b, c, loga, padre[20][10005], ST[60005], arre[10005], posarre;
int ccad[10005], chead[10005], STpos[10005], subtree[10005], cad, niveles[10005];
int indedge[10005];
void dfs(int nodo, int anterior, int nivel)
{
    niveles[nodo]=nivel, subtree[nodo]=1, padre[0][nodo]=anterior;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].destino!=anterior)
        {
            indedge[ady[nodo][i].ind]=ady[nodo][i].destino;
            dfs(ady[nodo][i].destino, nodo, nivel+1);
            subtree[nodo]+=subtree[ady[nodo][i].destino];
        }
}
int LCA(int a, int b)
{
    if(niveles[a]<niveles[b])
        swap(a, b);
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
            if(sc==-1 || subtree[ady[nodo][i].destino]>subtree[sc])
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
    ST[nodo]=max(ST[2*nodo+1], ST[2*nodo+2]);
}
void actualizar(int nodo, int ini, int fin, int l, int v)
{
    if(ini==fin)
    {
        ST[nodo]=v;
        arre[ini]=v;
        return;
    }
    if(l<=(ini+fin)/2)
        actualizar(2*nodo+1, ini, (ini+fin)/2, l, v);
    else
        actualizar(2*nodo+2, (ini+fin)/2+1, fin, l, v);
    ST[nodo]=max(ST[2*nodo+1], ST[2*nodo+2]);
}
int queryST(int nodo, int ini, int fin, int l, int r)
{
    if(fin<l || ini>r)
        return -1;
    if(ini>=l && fin<=r)
        return ST[nodo];
    return max(queryST(2*nodo+1, ini, (ini+fin)/2, l, r), queryST(2*nodo+2, (ini+fin)/2+1, fin, l, r));
}
int query(int u, int v)
{
    if(u==v)
        return 0;
    int cadu, cadv=ccad[v], res=-1;
    while(true)
    {
        cadu=ccad[u];
        if(cadu==cadv)
        {
            if(u==v)
                break;
            res=max(res, queryST(0, 0, N-1, STpos[v]+1, STpos[u]));
            break;
        }
        else
        {
            res=max(res, queryST(0, 0, N-1, STpos[chead[cadu]], STpos[u]));
            u=padre[0][chead[cadu]];
        }
    }
    return res;
}
int maxedge(int a, int b)
{
    int lca=LCA(a,b);
    return max(query(a,lca), query(b,lca));
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while(T--)
    {
        for(int i=1; i<=N; i++)
            ady[i].clear();
        cin >> N;
        for(int i=0; i<N-1; i++)
            cin >> a >> b >> c, ady[a].push_back(make_pair(c, make_pair(b, i+1))), ady[b].push_back(make_pair(c, make_pair(a, i+1)));
        memset(padre, 0, sizeof(padre));
        memset(chead, 0, sizeof(chead));
        dfs(1, 1, 1);
        loga=log2(N);
        for(int i=1; i<=loga; i++)
            for(int j=1; j<=N; j++)
                padre[i][j]=padre[i-1][padre[i-1][j]];
        cad=1, posarre=0;
        HLD(1, 1, -1);
        construir(0, 0, N-1);
        cin >> ins;
        while(ins!="DONE")
        {
            if(ins=="CHANGE")
                cin >> a >> b, actualizar(0, 0, N-1, STpos[indedge[a]], b);
            else
                cin >> a >> b, cout << maxedge(a, b) << "\n";
            cin >> ins;
        }
    }
    return 0;
}
