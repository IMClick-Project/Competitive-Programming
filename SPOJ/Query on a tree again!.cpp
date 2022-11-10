//Hecho por: Mariola Camacho Lie
//Fecha: 30 de Mayo de 2018
//SPOJ - QTREE3
//Heavy Light Decomposition
//dado un árbol, cambiar cambia el estado del nodo(blanco-negro o negro-blanco) y negro devuelve el primer nodo negro del camino de 1 a v, si no existe devuelve -1
#include<bits/stdc++.h>
using namespace std;
vector < int > ady[100005];
int N, Q, a, b, ccad[100005], chead[100005], cad, subtree[100005], STpos[100005], posarre, anteriores[100005], posnodo[100005];
bool ST[400005], arre[100005];
void dfs(int nodo, int anterior)
{
    anteriores[nodo]=anterior, subtree[nodo]=1;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i]!=anterior)
            dfs(ady[nodo][i], nodo), subtree[nodo]+=subtree[ady[nodo][i]];
}
void HLD(int nodo, int anterior)
{
    if(!chead[cad])
        chead[cad]=nodo;
    ccad[nodo]=cad;
    STpos[nodo]=posarre;
    posnodo[posarre++]=nodo;
    int sc=-1;
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i]!=anterior)
            if(sc==-1 || subtree[sc]<subtree[ady[nodo][i]])
                sc=ady[nodo][i];
    if(sc!=-1)
        HLD(sc, nodo);
    for(int i=0; i<ady[nodo].size(); i++)
        if(ady[nodo][i]!=anterior)
            if(ady[nodo][i]!=sc)
                cad++, HLD(ady[nodo][i], nodo);
}
void cambiar(int nodo, int ini, int fin, int l)
{
    if(ini==fin)
    {
        arre[ini]^=true;
        ST[nodo]^=true;
        return;
    }
    if(l<=(ini+fin)/2)
        cambiar(2*nodo+1, ini, (ini+fin)/2, l);
    else
        cambiar(2*nodo+2, (ini+fin)/2+1, fin, l);
    if(ST[2*nodo+1] || ST[2*nodo+2])
        ST[nodo]=true;
    else
        ST[nodo]=false;
}
int query(int nodo, int ini, int fin, int l, int r)
{
    if(ini>r || fin<l)
        return -1;
    if(!ST[nodo])
        return -1;
    if(ini==fin)
        return ini;
    int z=query(2*nodo+1, ini, (ini+fin)/2, l, r);
    if(z==-1)
        z=query(2*nodo+2, (ini+fin)/2+1, fin, l, r);
    return z;
}
int negro(int u)
{
    int aux;
    if(u==1)
    {
        aux=query(0, 0, N-1, STpos[1], STpos[1]);
        return (aux!=-1) ? 1 : -1;
    }
    int cadu, cadv=ccad[1], res=-1;
    while(true)
    {
        cadu=ccad[u];
        if(cadv==cadu)
        {
            if(u==1)
            {
                aux=query(0, 0, N-1, STpos[1], STpos[1]);
                res= (aux!=-1) ? 0 : res;
                break;
            }
            aux=query(0, 0, N-1, STpos[1], STpos[u]);
            res=(aux!=-1) ? aux : res;
            break;
        }
        else
        {
            aux=query(0, 0, N-1, STpos[chead[cadu]], STpos[u]);
            res=(aux!=-1) ? aux : res;
            u=anteriores[chead[cadu]];
        }
    }
    return (res!=-1) ? posnodo[res] : -1;
}
int main()
{
    scanf("%d %d", &N, &Q);
    for(int i=0; i<N-1; i++)
        scanf("%d %d", &a, &b), ady[a].push_back(b), ady[b].push_back(a);
    memset(chead, 0, sizeof(chead));
    dfs(1, 1);
    cad=1, posarre=0;
    HLD(1, 1);
    for(int i=0; i<Q; i++)
    {
        scanf("%d %d", &a, &b);
        if(a==0)
            cambiar(0, 0, N-1, STpos[b]);
        else
            printf("%d\n", negro(b));
    }
    return 0;
}
