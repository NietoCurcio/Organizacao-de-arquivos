#include <stdio.h>
#include <string.h>

// Buscar CEP do argumento CLI

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
	FILE *f;
	Endereco e;
	int qt;
	int c;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("../datasets/cep.dat","r");
	qt = fread(&e,sizeof(Endereco),1,f);
	while(qt > 0)
	{
		c++;
		/*
		Na linguagem C, strings são null-terminated, o valor nulo é o '\0', por exemplo:

		| F | E | L | I | P | E | \0 |

		Existem funções que é posível especificar o numero de bytes, lendo a string no maximo ate esse numero.
		Um exemplo é a "strncmp"
		from man:
		The strnlen() function returns the number of bytes in the string
		pointed to by s, excluding the terminating null byte ('\0'), but
		at most maxlen.
		*/

		if(strncmp(argv[1], e.cep, 8)==0)
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
		qt = fread(&e,sizeof(Endereco),1,f);		
	}
	printf("Total Lido: %d\n", c);
	fclose(f);
}

