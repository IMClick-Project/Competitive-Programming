//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//CIIC 2015 - Cocodrilos
//Teoría de grafos
//Cada cocodrilo inicialmente tiene 10 boondollars y un mejor amigo, cada 5 minutos dan todo su dinero a su mejor amigo, quieres saber la mayor cantidad de dinero que puede tener un cocodrilo en el menor tiempo y que tenga el menor índice
//Observar que cada conjunto de cocodrilos está en un grafo con un ciclo
//En el ciclo el dinero gira alrededor de ellos y en las ramas va bajando el dinero hasta llegar al ciclo
//La idea es por conjunto de cocodrilos encontrar el ciclo y por cada cocodrilo en las ramas ver por nodo a qué lugar en el ciclo correspondiente terminaría cuando sus 10 boondollars llegaran a su ciclo
#include<bits/stdc++.h>
using namespace std;
vector < int > ciclo;
int N, x, ady[100005], estado[100005];
vector < int > monedas[100005];
int tiempo=0, ind=1, pesos=1, tamciclo, pos, aux, numciclo, marca[100005], hijo, t, ult;
bool vis[100005];
stack < int > pila;
vector < int > rev[100005];
queue < pair < int , int >  > cola[2];
void verciclo(int ini)
{
    while(!pila.empty())
        pila.pop();
    pila.push(ini);
    while(true)
    {
        pos=pila.top();
        if(!vis[ady[pos]])
            pila.push(ady[pos]), vis[ady[pos]]=true;
        else
        {
            aux=ady[pos];
            while(pos!=aux)
                marca[pos]=numciclo, ciclo.push_back(pos), pila.pop(), pos=pila.top();
            ciclo.push_back(aux), marca[aux]=numciclo;
            break;
        }
    }
}
int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++)
        scanf("%d", &ady[i]), rev[ady[i]].push_back(i);
    for(int i=1; i<=N; i++)
        if(!vis[i])
        {
            ciclo.clear(), numciclo++;
            verciclo(i);
            tamciclo=ciclo.size();
            for(int i=0; i<tamciclo; i++)
                estado[i]=1;
            for(int i=0; i<tamciclo; i++)
                for(int j=0; j<rev[ciclo[i]].size(); j++)
                    if(marca[rev[ciclo[i]][j]]!=numciclo)
                        cola[0].push(make_pair(rev[ciclo[i]][j], i)), vis[rev[ciclo[i]][j]]=true;
            pos=0, t=1;
            while(!cola[pos].empty())
            {
                while(!cola[pos].empty())
                {
                    hijo=cola[pos].front().first;
                    aux=cola[pos].front().second;
                    ult=(aux+t-1)%tamciclo;
                    cola[pos].pop();
                    estado[ult]++;
                    if(estado[ult]>pesos)
                        pesos=estado[ult], ind=ciclo[aux], tiempo=t;
                    else if(estado[ult]==pesos)
                        if(tiempo>t)
                            ind=ciclo[aux], tiempo=t;
                        else if(tiempo==t)
                            ind=min(ind, t);
                    for(int i=0; i<rev[hijo].size(); i++)
                        cola[(pos+1)%2].push(make_pair(rev[hijo][i], aux)), vis[rev[hijo][i]]=true;
                }
                pos++, pos%=2, t++;
            }
        }
    printf("%d %d %d", tiempo*5, pesos*10, ind);
    return 0;
}
