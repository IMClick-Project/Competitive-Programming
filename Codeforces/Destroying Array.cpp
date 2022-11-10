//Hecho por: Mariola Camacho Lie
//Fecha: 31 de Mayo de 2018
//Codeforces - 722C
//Union-Find
//dado un arreglo, se van a quitar por turno un número, por cada turno hay que decir la máxima suma de los subarreglos restantes
//verlo del final al inicio, inicialmente no hay dsus, por turno unir y agregar el número a los dsus que se encuentran hasta el momento correspondientes
#include<bits/stdc++.h>
using namespace std;
int N, d[100005], dad[100005], h[100005];
long long int v[100005], suma[100005], mejor, res[100005];
bool vis[100005];
int padre(int p)
{
    if(dad[p]!=p)
        return dad[p]=padre(dad[p]);
    return p;
}
void unir(int a, int b)
{
    int ra=padre(a), rb=padre(b);
    if(h[ra]>h[rb])
        dad[rb]=ra, suma[ra]+=suma[rb];
    else
        dad[ra]=rb, suma[rb]+=suma[ra];
    if(h[ra]==h[rb])
        h[rb]++;
}
int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++)
        scanf("%I64d", &v[i]);
    for(int i=1; i<=N; i++)
        scanf("%d", &d[i]);
    for(int i=1; i<=N; i++)
        h[i]=1, dad[i]=i, suma[i]=v[i];
    for(int i=N; i>=1; i--)
    {
        res[i]=mejor;
        vis[d[i]]=true;
        if(vis[d[i]+1])
            unir(d[i]+1, d[i]);
        if(vis[d[i]-1])
            unir(d[i]-1, d[i]);
        mejor=max(mejor, suma[padre(d[i])]);
    }
    for(int i=1; i<=N; i++)
        printf("%I64d\n", res[i]);
    return 0;
}
