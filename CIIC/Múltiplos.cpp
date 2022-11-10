//Hecho por: Mariola Camacho Lie
//Fecha: 1 de Junio de 2018
//CIIC 2017 - Múltiplos
//MO’s Algorithm
//dado un arreglo y M, hay queries que consisten en devolver cuántos subarreglos en el rango de i a j cumplen que la suma de sus elementos es divisible entre M
//suma de prefijos p(i) y usar la propiedad: la suma del subarreglo de x a y es p(y)-p(x-1)
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll cuantos[105], res[50005], ans;
struct ura
{
    int bloque, ini, fin, ind;
} pre[50005];
int N, M, Q, x, y, raiz, v[50005], sum, st, nd;
bool cmp(ura a, ura b)
{
    if(a.bloque!=b.bloque)
        return a.bloque<b.bloque;
    return a.fin<b.fin;
}
int main()
{
    scanf("%d %d %d", &N, &M, &Q);
    raiz=sqrt(N);
    for(int i=1; i<=N; i++)
        scanf("%d", &x), sum+=x, sum%=M, cuantos[sum]++, v[i]=sum;
    for(int i=0; i<Q; i++)
        scanf("%d %d", &x, &y), pre[i].ini=x, pre[i].fin=y, pre[i].bloque=(x-1)/raiz, pre[i].ind=i;
    sort(pre, pre+Q, cmp);
    st=1;
    nd=N;
    for(int j=0; j<Q; j++)
    {
        ans=0;
        if(st<pre[j].ini)
            for(int i=st; i<=pre[j].ini-1; i++)
                cuantos[v[i]]--;
        else
            for(int i=pre[j].ini; i<=st-1; i++)
                cuantos[v[i]]++;
        if(nd<pre[j].fin)
            for(int i=nd+1; i<=pre[j].fin; i++)
                cuantos[v[i]]++;
        else
            for(int i=pre[j].fin+1; i<=nd; i++)
                cuantos[v[i]]--;
        for(int i=0; i<M; i++)
            ans+=(cuantos[i]*(cuantos[i]-1))/2;
        ans+=cuantos[v[pre[j].ini-1]];
        res[pre[j].ind]=ans;
        st=pre[j].ini, nd=pre[j].fin;
    }
    for(int i=0; i<Q; i++)
        printf("%lld\n", res[i]);
    return 0;
}
