//Hecho por: Mariola Camacho Lie
//Fecha: 1 de Junio de 2018
//SPOJ - TWIST
//Dado un arreglo inicial con 1, 2, 3, ..., N, imprime cómo queda el arreglo después de realizar Q volteos (tomar un subarreglo de x a y e invertir el orden de sus elementos hasta el momento)
#include<bits/stdc++.h>
using namespace std;
int N, Q, x, y;
struct node
{
    node *l, *r;
    int p, k, s;
    bool lazy;
};
typedef node * pnode;
pnode newNode(int k)
{
    pnode x=new node();
    x->l=x->r=NULL;
    x->p=rand(), x->k=k, x->s=1;
    x->lazy=false;
    return x;
}
int cnt(pnode &n)
{
    return n ? n->s : 0;
}
void push(pnode &n)
{
    if(n && n->lazy)
    {
        n->lazy=false;
        swap(n->l, n->r);
        if(n->l)
            n->l->lazy^=true;
        if(n->r)
            n->r->lazy^=true;
    }
}
void split(pnode n, pnode &l, pnode &r, int k)
{
    push(n);
    if(!n)
    {
        l=r=NULL;
        return;
    }
    if(cnt(n->l)<k)
        split(n->r, n->r, r, k-cnt(n->l)-1), l=n;
    else
        split(n->l, l, n->l, k), r=n;
    n->s=cnt(n->l)+cnt(n->r)+1;
}
void mezclar(pnode &n, pnode l, pnode r)
{
    push(l), push(r);
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
void voltear(pnode &n, int l, int r)
{
    pnode x, y, z, p;
    split(n, x, y, l-1);
    split(y, p, z, r-l+1);
    p->lazy^=true;
    mezclar(n, x, p);
    mezclar(n, n, z);
}
void imprimir(pnode &n)
{
    push(n);
    if(!n)
        return;
    imprimir(n->l);
    printf("%d ", n->k);
    imprimir(n->r);
}
int main()
{
    scanf("%d %d", &N, &Q);
    pnode root=NULL, aux;
    for(int i=1; i<=N; i++)
        aux=newNode(i), mezclar(root, root, aux);
    for(int i=0; i<Q; i++)
        scanf("%d %d", &x, &y), voltear(root, x, y);
    imprimir(root);
    return 0;
}
