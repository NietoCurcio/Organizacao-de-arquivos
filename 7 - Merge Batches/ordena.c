#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

int particiona(int *vet, int inicio, int fim)
{
	int aux, pivo, temp;
	aux = inicio - 1;
	pivo = vet[fim];
	
	for(int i = inicio; i <= fim; i++)
	{
		if(vet[i] <= pivo)
		{
			aux++;
			temp = vet[i];
			vet[i] = vet[aux];
			vet[aux] = temp;
		}
	}
	return aux;
}

void quick(int *vet, int inicio, int fim)
{
	int p;
	if(inicio < fim)
	{
		p = particiona(vet,inicio,fim); // N
		quick(vet,inicio,p-1);
		quick(vet,p+1,fim);
	}
}

void sel(int *vet, int inicio, int fim)
{
	int i, maior, temp;
	while(inicio < fim)
	{
		maior = fim;
		for(i = inicio; i < fim; i++)
		{
			if(vet[i] > vet[maior])
			{
				maior = i;
			}
		}
		if(maior != fim)
		{
			temp = vet[maior];
			vet[maior] = vet[fim];
			vet[fim] = temp;
		}
		fim--;
	}
}

int main(int argc, char** argv)
{
	// srand(time(NULL));

  int vet[N], i;
  for(i=0; i<N; i++)
  {
		vet[i] = rand() % 100000;
  }
  // for(i=0; i<N; i++)
  // {
	// 	printf("%d ",vet[i]);
  // }
  // printf("\n");
  sel(vet,0,N);
  // for(i=0; i<N; i++)
  // {
  //      printf("%d ",vet[i]);
  // }
  // printf("\n");
  return 0;
}


