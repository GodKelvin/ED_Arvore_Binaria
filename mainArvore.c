#include <stdio.h>
#include <time.h>

#include "arvoreBinaria.h"
#include "characters.h"

/* argv[1] = dicionario, argv[2] = texto */
int main(int argc, char *argv[])
{
	Arvore* dicionario = criaArvore();
	
	//Insercao mais rapida do que no modo lista, porem ordenado
	/*Insercao rapida devido a verificacao de palavras repetidas
	que jah esta ordenado, ficando mais facil a localizacao da mesma*/
	dicionario = arvorePalavras(dicionario, argv[1]);

	//Correcao mais rapida do que no modo lista
	corretorArvore(dicionario, argv[2]);
	
	//Destruicao em tempos equivalentes
	freeArvore(dicionario);

	//DEBUG: Para verificar se o programa rodou por completo
	//printf("\n------FIM--------\n");
	
	return 0;
}