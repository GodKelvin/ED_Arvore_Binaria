#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arvoreBinaria.h" 
#include "characters.h"

/*Adaptavel ao tipo de texto, basta trocar o
segundo argumento de strtok para o que desejar*/
char *split(char *palavra)
{
	char *novaPalavra = strtok(palavra, " .,;:""?!-\n\t");
	
	return novaPalavra;
}

//FUNCAO DADA PELO PROFESSOR
char *lowerCase(char *str)
{
	int i = 0;
	while(str[i])
	{
		str[i] = tolower(str[i]);
		i++;
	}
	return str;
}
