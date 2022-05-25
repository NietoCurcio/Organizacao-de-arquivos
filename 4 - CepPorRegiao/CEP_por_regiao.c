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

int main(int argc, char**argv)
{
	char UFAtual[2];
	char nomeArquivo[12];

	FILE *f;
	FILE *outputFile = NULL;
	
	Endereco e;
	int qt;

	f = fopen("../datasets/cep.dat","r");
	qt = fread(&e, sizeof(Endereco), 1, f);

	while(qt > 0)
	{
		if(strncmp(e.sigla, UFAtual, 2) == 0) {
			fwrite(&e, sizeof(Endereco), 1, outputFile);
		} else {
			if (outputFile) fclose(outputFile);

			sprintf(nomeArquivo, "cep-%.2s.dat", e.sigla);
			outputFile = fopen(nomeArquivo, "a");

			strncpy(UFAtual, e.sigla, 2);

			fwrite(&e, sizeof(Endereco), 1, outputFile);
		}
		qt = fread(&e,sizeof(Endereco), 1, f);		
	}
	fclose(f);
	fclose(outputFile);

}