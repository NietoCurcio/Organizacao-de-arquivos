#include <stdio.h>

/*
Cópia de arquivos por batches

diferente de fgetc e fputc,

fread(buffer, tamanho do dado, quantidade de dados, arquivo);

lê um bloco de bytes de uma vez (4096 bytes) e armazena NO buffer,
se o valor retornado for > 0, significa que algum dado foi lido,
em seguida le outro bloco ate o EOF

fwrite possui o mesmo funcionamento, porém para escrita

*/
#define TAMANHO 4096

int main(int argc, char** argv)
{
	FILE *entrada, *saida;
	char buffer[TAMANHO];
	int qtd;

	if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"rb");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	saida = fopen(argv[2],"wb");
	if(!saida)
	{
		fclose(entrada);
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
		return 1;
	}

	qtd = fread(buffer, 1, TAMANHO, entrada);
	while(qtd > 0)
	{
		fwrite(buffer, 1, qtd,saida);
		qtd = fread(buffer, 1, TAMANHO, entrada);
	}

	fclose(entrada);
	fclose(saida);
	return 0;
}

