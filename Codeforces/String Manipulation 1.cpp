//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//Codeforces - 159C
//Treap implícito
//dado un string que es palabra que se repite K veces y puedes quitar la ith vez que se repite alguna letra, imprime cómo queda el string al final
//hacer un treap de posiciones por cada letra y eliminar la ith de su respectivo treap y al final ordenar por posición todo e imprimirlo
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int k, s, p;
    node *l, *r;
};
typedef node * pnode;
string s;
int N, K, tam, pp;
pnode raiz[30], aux;
char c;
vector < pair < int , char > > lista;
pnode newNode(int k)
{
    pnode x=new node();
    x->l=x->r=NULL;
    x->k=k;
    x->p=rand();
    x->s=1;
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
void mezclar(pnode &n, pnode l, pnode r)
{
    if(!l || !r)
    {
        n = l ? l : r;
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
void borrar(pnode &n, int k)
{
    pnode x, y, z;
    split(n, x, y, k-1);
    split(y, y, z, 1);
    mezclar(n, x, z);
}
void recorrer(pnode &n)
{
    if(!n)
        return;
    recorrer(n->l);
    lista.push_back(make_pair(n->k, c));
    recorrer(n->r);
}
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> K;
    cin >> s;
    for(int i=0; i<26; i++)
        raiz[i]=NULL;
    for(int i=0; i<K; i++)
        for(int j=0; j<s.size(); j++)
            aux=newNode(tam), mezclar(raiz[s[j]-'a'], raiz[s[j]-'a'], aux), tam++;
    cin >> N;
    for(int i=0; i<N; i++)
    {
        cin >> pp >> c;
        borrar(raiz[c-'a'], pp);
    }
    for(int i=0; i<26; i++)
        c=i+'a', recorrer(raiz[i]);
    sort(lista.begin(), lista.end());
    for(int i=0; i<lista.size(); i++)
        cout << lista[i].second;
    return 0;
}
