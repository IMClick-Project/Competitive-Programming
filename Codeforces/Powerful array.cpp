//Hecho por: Mariola Camacho Lie
//Fecha: 31 de Mayo de 2018
//Codeforces - 86D
//MO’s Algorithm
//propiedad: la suma de los impares positivos consecutivos es un cuadrado perfecto
#include<bits/stdc++.h>
using namespace std;
struct ura
{
    int bloque, ind, ini, fin;
} query[200005];
bool compara(ura a, ura b)
{
    if(a.bloque!=b.bloque)
        return a.bloque<b.bloque;
    return a.fin<b.fin;
}
int n, t, x, y, arreglo[200005], cont, raiz, cubeta[1000005];
long long int res[200005], aux;
int main()
{
    scanf("%d %d", &n, &t);
    for(int i=1; i<=n; i++)
        scanf("%d", &arreglo[i]);
    raiz=sqrt(n);
    for(int i=0; i<t; i++)
        scanf("%d %d", &x, &y), query[i].bloque=(x-1)/raiz, query[i].fin=y, query[i].ini=x, query[i].ind=i;
    sort(query, query+t, compara);
    aux=0;
    for(int i=query[0].ini; i<=query[0].fin; i++)
        aux+=(arreglo[i]*(2*cubeta[arreglo[i]]+1)), cubeta[arreglo[i]]++;
    res[query[0].ind]=aux;
    for(int i=1; i<t; i++)
    {
        if(query[i-1].ini<query[i].ini)
            for(int j=query[i-1].ini; j<query[i].ini; j++)
                cubeta[arreglo[j]]--, aux-=(arreglo[j]*(2*cubeta[arreglo[j]]+1));
        else
            for(int j=query[i].ini; j<query[i-1].ini; j++)
                aux+=(arreglo[j]*(2*cubeta[arreglo[j]]+1)), cubeta[arreglo[j]]++;
        if(query[i-1].fin<query[i].fin)
            for(int j=query[i-1].fin+1; j<=query[i].fin; j++)
                aux+=(arreglo[j]*(2*cubeta[arreglo[j]]+1)), cubeta[arreglo[j]]++;
        else
            for(int j=query[i].fin+1; j<=query[i-1].fin; j++)
                cubeta[arreglo[j]]--, aux-=(arreglo[j]*(2*cubeta[arreglo[j]]+1));
        res[query[i].ind]=aux;
    }
    for(int i=0; i<t; i++)
        printf("%I64d\n", res[i]);
    return 0;
}
