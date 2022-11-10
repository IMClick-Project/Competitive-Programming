//Hecho por: Mariola Camacho Lie
//Fecha: 1 de Junio de 2018
//SPOJ - ORDERSET
//insertar (si no existe), eliminar (si existe) un elemento, devolver el kth elemento menor (si existe) y cuántos elementos son menores a k.
#include<bits/stdc++.h>
using namespace std;
struct node
{
    node *l, *r;
    int p, k, s;
};
typedef node * pnode;
pnode newNode(int k)
{
    pnode x=new node();
    x->k=k, x->p=rand(), x->s=1;
    x->l=x->r=NULL;
    return x;
}
int cnt(pnode &n)
{
    return n ? n->s : 0;
}
void split(pnode n, pnode &l, pnode &r, int k)
{
    if(!n)
    {
        l=r=NULL;
        return;
    }
    if(n->k<k)
        split(n->r, n->r, r, k), l=n;
    else
        split(n->l, l, n->l, k), r=n;
    n->s=cnt(n->l)+cnt(n->r)+1;
}
void mezclar(pnode &n, pnode l, pnode r)
{
    if(!l || !r)
    {
        n = l ? l : r;
        return;
    }
    if(l->p>r->p)
        mezclar(l->r, l->r, r), n=l;
    else
        mezclar(r->l, l, r->l), n=r;
    n->s=cnt(n->l)+cnt(n->r)+1;
}
void insertar(pnode &n, int k)
{
    pnode x, y, z, p;
    split(n, x, y, k);
    split(y, p, z, k+1);
    if(p==NULL)
        p=newNode(k);
    mezclar(n, x, p);
    mezclar(n, n, z);
}
void eliminar(pnode &n, int k)
{
    pnode x, y, z, p;
    split(n, x, y, k);
    split(y, p, z, k+1);
    mezclar(n, x, z);
}
int kth(pnode &n, int k)
{
    if(cnt(n->l)==k-1)
        return n->k;
    if(cnt(n->l)>=k)
        return kth(n->l, k);
    return kth(n->r, k-1-cnt(n->l));
}
int contar(pnode &n, int k)
{
    pnode x, y;
    split(n, x, y, k);
    int res=cnt(x);
    mezclar(n, x, y);
    return res;
}
int Q, a;
char ins;
int main()
{
    scanf("%d", &Q);
    pnode root=NULL;
    for(int i=0; i<Q; i++)
    {
        scanf(" %c %d", &ins, &a);
        if(ins=='I')
            insertar(root, a);
        else if(ins=='D')
            eliminar(root, a);
        else if(ins=='K')
            if(cnt(root)>=a)
                printf("%d\n", kth(root, a));
            else
                printf("invalid\n");
        else
            printf("%d\n", contar(root, a));

    }
    return 0;
}
