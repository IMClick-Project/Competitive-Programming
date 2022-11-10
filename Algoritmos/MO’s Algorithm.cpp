//Hecho por: Mariola Camacho Lie
//Fecha: 31 de Mayo de 2018
//SPOJ - DQUERY
//contestar queries de cúantos números diferentes hay en un rango
#include<bits/stdc++.h>
using namespace std;
int a[30005], N, Q, cont[1000006], x, y, raiz, res[200005], dif;
struct ura
{
    int ini, fin, bloque, id;
} query[200005];
bool cmp(ura a, ura b)
{
    if(a.bloque!=b.bloque)
        return a.bloque<b.bloque;
    return a.fin<b.fin;
}
int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++)
        scanf("%d", &a[i]);
    scanf("%d", &Q);
    raiz=sqrt(N);
    for(int i=0; i<Q; i++)
        scanf("%d %d", &query[i].ini, &query[i].fin), query[i].id=i, query[i].bloque=(query[i].ini-1)/raiz;
    sort(query, query+Q, cmp);
    for(int i=query[0].ini; i<=query[0].fin; i++)
    {
        cont[a[i]]++;
        if(cont[a[i]]==1)
            dif++;
    }
    res[query[0].id]=dif;
    x=query[0].ini, y=query[0].fin;
    for(int j=1; j<Q; j++)
    {
        if(query[j].ini<x)
            for(int i=query[j].ini; i<=x-1; i++)
            {
                cont[a[i]]++;
                if(cont[a[i]]==1)
                    dif++;
            }
        else
            for(int i=x; i<=query[j].ini-1; i++)
            {
                cont[a[i]]--;
                if(cont[a[i]]==0)
                    dif--;
            }
        if(query[j].fin<y)
            for(int i=query[j].fin+1; i<=y; i++)
            {
                cont[a[i]]--;
                if(cont[a[i]]==0)
                    dif--;
            }
        else
            for(int i=y+1; i<=query[j].fin; i++)
            {
                cont[a[i]]++;
                if(cont[a[i]]==1)
                    dif++;
            }
        x=query[j].ini, y=query[j].fin, res[query[j].id]=dif;
    }
    for(int i=0; i<Q; i++)
        printf("%d\n", res[i]);
    return 0;
}
