//Hecho por: Mariola Camacho Lie
//Fecha: 1 de Junio de 2018
//SPOJ - KOILINE
//Treap implícito
//dado un arreglo de alturas y un arreglo en donde cada valor corresponde a la cantidad de personas más bajas o de igual estatura que el de esa posición, devuelve la formación de alturas
//si ordenamos el arreglo de alturas de menor a mayor y vemos la última posición del otro, sabemos que su correspondiente altura es la que se encuentra en (la posición que dice ese arreglo) + 1, quitamos de la lista la altura ya encontrada y repetimos el proceso con el siguiente del final hasta el inicio
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int k, s, p;
    node *l, *r;
};
typedef node * pnode;
int S[200005], N, res[200005], pos;
pnode newNode(int k)
{
    pnode x=new node();
    x->k=k;
    x->l=x->r=NULL;
    x->s=1;
    x->p=rand();
    return x;
}
int cnt(pnode n)
{
    return n ? n->s : 0;
}
void mezclar(pnode &n, pnode l, pnode r)
{
    if(!l || !r)
    {
        n=l ? l:r;
        return;
    }
    if(l->p > r->p)
    {
        mezclar(l->r, l->r, r);
        n=l;
    }
    else
    {
        mezclar(r->l, l, r->l);
        n=r;
    }
    n->s=cnt(n->l)+cnt(n->r)+1;
}
void split(pnode n, pnode &l, pnode &r, int k)
{
    if(!n)
    {
        l=r=NULL;
        return;
    }
    if(cnt(n->l)<k)
    {
        split(n->r, n->r, r, k-cnt(n->l)-1);
        l=n;
    }
    else
    {
        split(n->l, l, n->l, k);
        r=n;
    }
    n->s=cnt(n->l)+cnt(n->r)+1;
}
void kth(pnode &n, int k)
{
    pnode x, y, z;
    split(n, x, y, k);
    split(y, y, z, 1);
    res[pos]=y->k;
    mezclar(n, x, z);
}
int x;
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; i++)
        scanf("%d", &S[i]);
    sort(S, S+N);
    pnode raiz=NULL;
    pnode aux;
    for(int i=0; i<N; i++)
        aux=newNode(S[i]), mezclar(raiz, raiz, aux);
    for(int i=0; i<N; i++)
        scanf("%d", &S[i]);
    for(pos=N-1; pos>=0; pos--)
        kth(raiz, S[pos]);
    for(int i=0; i<N; i++)
        printf("%d\n", res[i]);
    return 0;
}
