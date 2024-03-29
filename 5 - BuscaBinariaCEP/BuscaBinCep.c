#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

long buscaBin(int inicio, int fim, FILE *f, char* cepProcurado, Endereco* e, int* count){
    int meio;

    while(inicio <= fim){
        meio = (inicio + fim)/2;
        fseek(f, meio*sizeof(Endereco), SEEK_SET);
        fread(e, sizeof(Endereco), 1, f);
        *count += 1;
        if (strncmp(cepProcurado, e->cep, 8) == 0){
            return ftell(f);

        } else if(strncmp(cepProcurado, e->cep, 8) > 0){
            inicio = meio + 1;

        } else {
            fim = meio - 1;
        }
    }
    return -1;
}


int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
  long tamanho_bytes;
  long tamanho_registros;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));

	f = fopen("../datasets/cep_ordenado.dat","rb");

  fseek(f, 0, SEEK_END);
  tamanho_bytes = ftell(f);
  tamanho_registros = tamanho_bytes/sizeof(Endereco);

  int inicio = 0;
  int fim = tamanho_registros - 1;

  int count = 0;

  long idx = buscaBin(inicio, fim, f, argv[1], &e, &count);
  
  if(idx == -1){
      printf("Nao encontrou\n");
  } else {
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
  }

  printf("Enderecos lidos: %d\n", count);
	fclose(f);
  return 0;
}