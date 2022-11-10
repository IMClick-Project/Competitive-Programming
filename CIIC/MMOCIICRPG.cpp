//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//CIIC 2016 - MMOCIICRPG
//Binary Indexed Tree
//dado un árbol, determina dado un k la ganancia del camino de 1 a v (Q queries)
//cada arista tiene un arma con cierto valor, sea p el conjunto de armas del camino de 1 a v que tienen valor mayor o igual a k, la ganancia es la suma del valor de las armas de p - k * la cantidad de armas es p (la suma de los valores por cada arma en p que se le reste k)
//realizar un dfs desde 1 en donde se ira desarrollando p hasta el momento e ir guardando las respuestas si hay preguntas en el nodo donde se está.
#include<bits/stdc++.h>
#define ll long long int
using namespace std;
int N, M, Q, x;
ll armas[200005], res[200005], BIT[1000005], y, BITc[1000005];
int frec[200005];
vector < pair < int , ll > > preg[200005];
vector < int > ady[200005];
ll aa[200005];
void agregar(ll pos, ll v)
{
    while(pos<=1000000)
    {
        BIT[pos]+=v;
        pos+=pos&(-pos);
    }
}
ll query(ll ini, ll fin)
{
    ll res=0;
    while(fin>=1)
    {
        res+=BIT[fin];
        fin-=fin&(-fin);
    }
    ini--;
    while(ini>=1)
    {
        res-=BIT[ini];
        ini-=ini&(-ini);
    }
    return res;
}
void agregarc(ll pos, ll v)
{
    while(pos<=1000000)
    {
        BITc[pos]+=v;
        pos+=pos&(-pos);
    }
}
ll queryc(ll ini, ll fin)
{
    ll res=0;
    while(fin>=1)
    {
        res+=BITc[fin];
        fin-=fin&(-fin);
    }
    ini--;
    while(ini>=1)
    {
        res-=BITc[ini];
        ini-=ini&(-ini);
    }
    return res;
}
void dfs(int nodo, int anterior)
{
    frec[aa[nodo]]++;
    if(frec[aa[nodo]]==1 && nodo!=1)
        agregar(armas[aa[nodo]], armas[aa[nodo]]), agregarc(armas[aa[nodo]], 1);
    for(int i=0; i<preg[nodo].size(); i++)
        res[preg[nodo][i].first]=query(preg[nodo][i].second, 1000000)-queryc(preg[nodo][i].second, 1000000)*preg[nodo][i].second;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i]!=anterior)
            dfs(ady[nodo][i], nodo);
    frec[aa[nodo]]--;
    if(frec[aa[nodo]]==0 && nodo!=1)
        agregar(armas[aa[nodo]], -armas[aa[nodo]]), agregarc(armas[aa[nodo]], -1);
}
int main()
{
    scanf("%d %d %d", &N, &M, &Q);
    for(int i=1; i<=M; i++)
        scanf("%lld", &armas[i]);
    for(int i=2; i<=N; i++)
        scanf("%d %lld", &x, &y), ady[i].push_back(x), ady[x].push_back(i), aa[i]=y;
    for(int i=1; i<=Q; i++)
        scanf("%d %lld", &x, &y), preg[x].push_back(make_pair(i, y));
    dfs(1, 0);
    for(int i=1; i<=Q; i++)
        printf("%lld\n", res[i]);
    return 0;
}
