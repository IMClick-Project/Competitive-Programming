//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//CIIC 2016 - Don Porfirio
//Union-Find
//dado un árbol, la belleza de un camino es la arista máxima del camino de u a v
//calcula la suma de todas las bellezas de cada pareja u,v con u<v;
//ordenar las aristas de menor a mayor e ir uniendo el grafo tomando en cuenta que esa arista que en ese momento se esta usando es la belleza de los caminos de un nodo la primera componente a un nodo de la segunda componente
#include<bits/stdc++.h>
#define lady pair < long long int , pair < long long int , long long int > >
#define costo first
#define origen second.first
#define destino second.second
#define MOD 1000000007
#define ll long long int
using namespace std;
ll N, h[100005], UAF[100005], tam[100005], res, aux;
lady ady[100005];
ll padre(ll p)
{
    if(UAF[p]!=p)
        return UAF[p]=padre(UAF[p]);
    return UAF[p];
}
void unir(ll a, ll b)
{
    ll ra=padre(a);
    ll rb=padre(b);
    if(h[rb]>h[ra])
        UAF[ra]=rb, tam[rb]+=tam[ra];
    else
        UAF[rb]=ra, tam[ra]+=tam[rb];
    if(h[rb]==h[ra])
        h[ra]++;
}
int main()
{
    scanf("%lld", &N);
    for(ll i=0; i<N-1; i++)
        scanf("%lld %lld %lld", &ady[i].origen, &ady[i].destino, &ady[i].costo), ady[i].costo%=MOD;
    sort(ady, ady+N-1);
    for(ll i=1; i<=N; i++)
        UAF[i]=i, h[i]=1, tam[i]=1;
    for(ll i=0; i<N-1; i++)
    {
            aux=(ady[i].costo*tam[padre(ady[i].origen)])%MOD;
            aux=(aux*tam[padre(ady[i].destino)])%MOD;
            res=(res+aux)%MOD;
            unir(ady[i].origen, ady[i].destino);
    }
    printf("%lld", res);
}
