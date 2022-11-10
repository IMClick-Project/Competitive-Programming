//Hecho por: Mariola Camacho Lie
//Fecha: 4 de Junio de 2018
//dado un árbol, devuelve por cada query el LCA(a,b)
#include<bits/stdc++.h>
using namespace std;
int N, Q, a, b, loga, padre[20][100005], niveles[100005];
vector < int > ady[100005];
void dfs(int nodo, int anterior, int nivel)
{
    padre[0][nodo]=anterior, niveles[nodo]=nivel;
    for(int i=0; i<ady[nodo].size(); i++)
        if(anterior!=ady[nodo][i])
            dfs(ady[nodo][i], nodo, nivel+1);
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
int main()
{
    scanf("%d %d", &N, &Q);
    for(int i=0; i<N-1; i++)
        scanf("%d %d", &a, &b), ady[a].push_back(b), ady[b].push_back(a);
    dfs(1,1,1);
    loga=log2(N);
    for(int i=1; i<=loga; i++)
        for(int j=1; j<=N; j++)
            padre[i][j]=padre[i-1][padre[i-1][j]];
    for(int i=0; i<Q; i++)
        scanf("%d %d", &a, &b), printf("%d\n", LCA(a, b));
    return 0;
}
