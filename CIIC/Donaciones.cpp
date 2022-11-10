//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//CIIC 2015 - Donaciones
//Binary Indexed Tree
//dada N donaciones que consisten que en el tiempo de L a R pueden dar c pesos (solo una vez), pueden cambiarse en cierto tiempo las donaciones (tiempo o dinero) y por cada querie tienes que contestar en un tiempo de L a R cuánto dinero pueden conseguir en ese tiempo
//ver las queries como: la suma de todas las donaciones - la suma de las donaciones que no estén en el rango
#include<bits/stdc++.h>
#define ll long long int
using namespace std;
ll fines[1000006], inis[1000006], total, x;
int N, M, ins, a, b, ind;
struct ura
{
    int s, e;
    ll p;
} datos[100006];
void agf(int pos, ll v)
{
    while(pos<=1000000)
    {
        fines[pos]+=v;
        pos+=pos&(-pos);
    }
}
void agi(int pos, ll v)
{
    while(pos<=1000000)
    {
        inis[pos]+=v;
        pos+=pos&(-pos);
    }
}
ll qf(int ini, int fin)
{
    ll res=0;
    while(fin)
    {
        res+=fines[fin];
        fin-=fin&(-fin);
    }
    ini--;
    while(ini)
    {
        res-=fines[ini];
        ini-=ini&(-ini);
    }
    return res;
}
ll qi(int ini, int fin)
{
    ll res=0;
    while(fin)
    {
        res+=inis[fin];
        fin-=fin&(-fin);
    }
    ini--;
    while(ini)
    {
        res-=inis[ini];
        ini-=ini&(-ini);
    }
    return res;
}
int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++)
    {
        scanf("%d %d %lld", &datos[i].s, &datos[i].e, &datos[i].p);
        agf(datos[i].e, datos[i].p);
        agi(datos[i].s, datos[i].p);
        total+=datos[i].p;
    }
    scanf("%d", &M);
    while(M--)
    {
        scanf("%d", &ins);
        if(ins==1)
        {
            scanf("%d %d", &a, &b);
            printf("%lld\n", total-qf(1, a-1)-qi(b+1, 1000000));
        }
        else
        {
            scanf("%d %d %d %lld", &ind, &a, &b, &x);
            agf(datos[ind].e, -datos[ind].p);
            agi(datos[ind].s, -datos[ind].p);
            total-=datos[ind].p;
            datos[ind].s=a;
            datos[ind].e=b;
            datos[ind].p=x;
            agf(datos[ind].e, datos[ind].p);
            agi(datos[ind].s, datos[ind].p);
            total+=datos[ind].p;
        }
    }
    return 0;
}
