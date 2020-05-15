#include <stdio.h>
#include <time.h>

#include "listaSimples.h"
#include "characters.h"

/* argv[1] = dicionario, argv[2] = texto */
int main(int argc, char *argv[])
{
	Lista* dicionario = criaLista();
	
	//Insercao mais lenta do que no modo arvore e nao ordenado
	/*Mais lenta devido a, eu tenho que percorrer a lista ate
	o fim para me certificar se a palavra ja foi inserida*/
	dicionario = listaPalavras(dicionario, argv[1]);
	
	//Correcao mais lenta do que no modo arvore
	corretorLista(dicionario, argv[2]);

	//Destruicao em tempos equivalentes
	freeLista(dicionario);

	//DEBUG: Para verificar se o programa rodou por completo
	//printf("\n---------FIM---------\n");
	return 0;
}