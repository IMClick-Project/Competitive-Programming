//Hecho por: Mariola Camacho Lie
//Fecha: 2 de Junio de 2018
//CIIC 2015 - Chocolates
//Binary Search
//tienes una lista por día de cuántos chocolates recibirá, todos los días tienes que comer la misma cantidad de chocolates y guardas los que sobren, tienes que devolver la máxima cantidad de chocolates que puede comer todos los días y cumplir las condiciones ante dichas
//una búsqueda binaria respecto a la respuesta, en cada caso simulando si es posible lo que pide el problema
#include<bits/stdc++.h>
using namespace std;
int N;
long long int chocolate[100000], minimo=0, maximo=0, tengo=0, bin;
bool poder;
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; i++)
        scanf("%lld", &chocolate[i]), tengo+=chocolate[i];
    maximo=tengo/N;
    while(maximo!=minimo)
    {
        tengo=0;
        poder=false;
        bin=(minimo+maximo+1)/2;
        for(int i=0; i<N; i++)
        {
            if(tengo+(chocolate[i]-bin)<0)
            {
                maximo=bin-1;
                poder=true;
                break;
            }
            tengo+=(chocolate[i]-bin);
        }
        if(poder==true)
            continue;
        minimo=bin;
    }
    printf("%lld", maximo);
    return 0;
}
