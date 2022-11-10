//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//CIIC 2016 - Enredados
//Binary Indexed Tree
//dados dos arreglos permutaciones de N(físicamente uno arriba del otro) que se unen con sus correspondientes, devuelve la mínima cantidad de movimientos para que no se tenga cruces
//un movimiento se define como intercambiar dos posiciones adyacentes que están en el mismo arreglo
//contar la cantidad de cruces : ir formando las uniones respecto al segundo arreglo, viendo respecto al primer arreglo, aumentar la res cada unión: del total de puntos vistos hasta el momento - cuántos antes se la posición de unión ya están relacionados, esos son con lo que se cruzan
#include<iostream>
using namespace std;
#define ll long long int
int N, ini[1500005], BIT[1500005];
ll p, res;
ll sum(ll pos)
{
    ll s=0;
    while(pos>0)
        s+=BIT[pos], pos-=(pos&-pos);
    return s;
}
void act(ll pos)
{
    while(pos<=N)
        BIT[pos]++, pos+=(pos&-pos);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    N/=2;
    for(int i=1; i<=N; i++)
        cin >> p, ini[p]=i;
    for(int i=0; i<N; i++)
        cin >> p, res+=(i-sum(ini[p])), act(ini[p]);
    cout << res;
}
