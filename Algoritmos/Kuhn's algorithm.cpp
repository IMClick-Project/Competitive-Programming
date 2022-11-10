//Hecho por: Mariola Camacho Lie
//Fecha: 4 de Junio de 2018
//dado un grafo bipartito, encuentra el máximo emparejamiento
#include<vector>
#include<stdio.h>
using namespace std;
vector < int > ady[10005];
int match[10005], L, R, K, x, y, tam, vis[10005], marca=1;
vector < pair < int, int > > res;
bool dfs(int x)
{
    if(vis[x]==marca)
        return false;
    vis[x]=marca;
    for(int i=0; i<ady[x].size(); i++)
        if(!match[ady[x][i]])
        {
            match[ady[x][i]]=x;
            return true;
        }
    for(int i=0; i<ady[x].size(); i++)
        if(dfs(match[ady[x][i]]))
        {
            match[ady[x][i]]=x;
            return true;
        }
    return false;
}
void Kuhn()
{
    for(int i=1; i<=L; i++)
    {
        marca++;
        if(dfs(i))
            tam++;
    }
}
int main()
{
    scanf("%d %d %d", &L, &R, &K);
    for(int i=0; i<K; i++)
        scanf("%d %d", &x, &y), ady[x].push_back(y);
    Kuhn();
    printf("%d\n", tam);
    for(int i=1; i<=R; i++)
        if(match[i])
            printf("%d %d\n", match[i], i);
    return 0;
}
