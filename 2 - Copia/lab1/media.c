#include <stdio.h>

#define TAMANHO 4096

/*
r - reading mode
w - writing mode, truncate if exists otherwise create
a - appending mode (write to end of file)
r+ - reading and writing mode
w+ - reading and writing mode
r+b - reading and writing binary mode
rb - reading binary mode

from help(open) in python:

binary mode reads and writes raw bytes, without any encoding

if the mode is not binary, it will encode using the encoding 
specified or using a platform-dependent enconding
*/

int countLetters(char* buffer, int length) {
  int letters = 0;
  for(int i = 0; i < length; i++) {
    // there are ";" characters in the file
    if (buffer[i] != ' ' && buffer[i] != ';') letters++;
  }
  return letters;
}

int countWords(char* buffer, int length) {
  int words = 0;
  for(int i = 0; i < length; i++) {
    if (buffer[i] == ' ') words++;
  }
  return words;
}

int main(int argc, char** argv)
{
	FILE *entrada;
	char buffer[TAMANHO];
	int qtd;

	if(argc != 2)
	{
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"rb");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	qtd = fread(buffer, 1, TAMANHO, entrada);

  int words = 0;
  int letters = 0;

	while(qtd > 0)
	{
    letters += countLetters(buffer, qtd);
    words += countWords(buffer, qtd);
		qtd = fread(buffer, 1, TAMANHO, entrada);
	}

  words++; // count last word

	fclose(entrada);

  printf("Total de palavras %d\n", words);
  printf("Tamanho medio %f\n", 1.0* letters / words);
	return 0;
}