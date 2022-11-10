//Hecho por: Mariola Camacho Lie
//Fecha: 30 de Mayo de 2018
//CIIC 2017 - Brincando
//Dynamic Programming
//¿de cuantás maneras puedes cubrir una distancia de D si puedes dar saltos de 1 a k?
//ver que para cubrir de 1 a distancia k es igual a 2^(i-1) ya que para i=1 hay una forma, para i=2 son dos (1,1; 2) ... checar que siempre para la posición i es la suma de los anteriores + 1 y ver propiedad que 1+(1+2+4+2^j)=2^(j+1)
//para una distancia k+1 en adelante es la suma de los k anteriores
#include<stdio.h>
using namespace std;
int N, K, DP[100005], res, x;
int main()
{
    scanf("%d %d", &K, &N);
    x=1;
    for(int i=0; i<K; i++)
    {
        res+=x;
        res%=1000000;
        DP[i]=x;
        x*=2;
        x%=1000000;
    }
    for(int i=K; i<N; i++)
    {
        x=DP[i%K];
        DP[i%K]=res;
        res*=2;
        res-=x;
        res+=1000000;
        res%=1000000;
    }
    printf("%d", DP[(N-1)%K]);
}
