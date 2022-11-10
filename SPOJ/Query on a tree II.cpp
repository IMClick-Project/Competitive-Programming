//Hecho por: Mariola Camacho Lie
//Fecha: 29 de Mayo de 2018
//SPOJ - QTREE2
//Heavy Light Decomposition and Lowest Common Ancestor
//dado un árbol, dist devuelve la distancia del nodo u a v y kth devuelve el kth nodo del camino de u a v
#include<bits/stdc++.h>
#define costo first
#define des second
using namespace std;
vector < pair < long long int , int > > ady[10005];
int padre[20][10005], loga, niveles[10005], N, a, b, d, cad, STpos[10005], ccad[10005], chead[10005], T, subtree[10005], posarre;
long long int c, ST[40005], arre[10005];
string ins;
void dfs(int nodo, int anterior, int nivel)
{
    niveles[nodo]=nivel, padre[0][nodo]=anterior, subtree[nodo]=1;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].des!=anterior)
        {
            dfs(ady[nodo][i].des, nodo, nivel+1);
            subtree[nodo]+=subtree[ady[nodo][i].des];
        }
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
void HLD(int nodo, int anterior, long long int costo)
{
    if(!chead[cad])
        chead[cad]=nodo;
    ccad[nodo]=cad;
    STpos[nodo]=posarre;
    arre[posarre++]=costo;
    int sc=-1;
    long long int auxcosto;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].des!=anterior)
            if(sc==-1 || subtree[sc]<subtree[ady[nodo][i].des])
                sc=ady[nodo][i].des, auxcosto=ady[nodo][i].costo;
    if(sc!=-1)
        HLD(sc, nodo, auxcosto);
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i].des!=anterior)
            if(sc!=ady[nodo][i].des)
                cad++, HLD(ady[nodo][i].des, nodo, ady[nodo][i].costo);
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
    ST[nodo]=ST[2*nodo+1]+ST[2*nodo+2];
}
long long int queryST(int nodo, int ini, int fin, int l, int r)
{
    if(ini>r || fin<l)
        return 0;
    if(ini>=l && fin<=r)
        return ST[nodo];
    return queryST(2*nodo+1, ini, (ini+fin)/2, l, r)+queryST(2*nodo+2, (ini+fin)/2+1, fin, l, r);
}
int kth(int a, int b, int k)
{
    int lca=LCA(a,b), pasos, nodo;
    if(k<=niveles[a]-niveles[lca]+1)
        pasos=k-1, nodo=a;
    else
        pasos=niveles[a]-niveles[lca]+niveles[b]-niveles[lca]-k+1, nodo=b;
    for(int i=loga; i>=0; i--)
        if(pasos>=(1<<i))
            nodo=padre[i][nodo], pasos-=(1<<i);
    return nodo;
}
long long int query(int u, int v)
{
    if(u==v)
        return 0;
    int cadu, cadv=ccad[v];
    long long int res=0LL;
    while(true)
    {
        cadu=ccad[u];
        if(cadu==cadv)
        {
            if(u==v)
                break;
            res+=queryST(0, 0, N-1, STpos[v]+1, STpos[u]);
            break;
        }
        else
        {
            res+=queryST(0, 0, N-1, STpos[chead[cadu]], STpos[u]);
            u=padre[0][chead[cadu]];
        }
    }
    return res;
}
long long int dist(int a, int b)
{
    int lca=LCA(a,b);
    return query(a, lca)+query(b, lca);
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
        memset(padre, 0, sizeof(padre));
        memset(chead, 0, sizeof(chead));
        cin >> N;
        for(int i=0; i<N-1; i++)
            cin >> a >> b >> c, ady[a].push_back(make_pair(c, b)), ady[b].push_back(make_pair(c, a));
        dfs(1, 1, 1);
        loga=log2(N);
        for(int i=1; i<=loga; i++)
            for(int j=1; j<=N; j++)
                padre[i][j]=padre[i-1][padre[i-1][j]];
        posarre=0, cad=1;
        HLD(1, 1, -1LL);
        construir(0, 0, N-1);
        cin >> ins;
        while(ins!="DONE")
        {
            cin >> a >> b;
            if(ins=="DIST")
                cout << dist(a, b);
            else
                cin >> d, cout << kth(a, b, d);
            cout << "\n";
            cin >> ins;
        }
    }
    return 0;
}
