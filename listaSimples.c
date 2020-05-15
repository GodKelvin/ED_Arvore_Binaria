#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSimples.h"
#include "characters.h"

//String de chars == palavras.
struct Celula
{
	char info[30];
	struct Celula *proximo;
};

//Celula de palavras
Cell* criaCelula(char *info)
{
	Cell* novaCelula = (Cell*) malloc(sizeof(Cell));
	//novaCelula->info = info;
	//Destino, fonte
	strcpy(novaCelula->info, info);
	novaCelula->proximo = NULL;

	return novaCelula;
}


Lista* criaLista()
{
	return NULL;
}

int buscaElemento(Lista* lista, char *elemento)
{
	Cell* celulaAtual = lista;
	int achou = 1;

	//Se achar, achou == 0(strcmp)
	while(celulaAtual != NULL && achou != 0)
	{
		achou = strcmp(celulaAtual->info, elemento);
		if(achou != 0)
		{
			celulaAtual = celulaAtual->proximo;
		}
		else
		{
			//Achou o elemento
			return 1;
		}
	}
	return 0;
}

Lista* insereInicio(Lista* lista, char *novaInfo)
{
	/* Aumenta o tempo de execucao consideravelmente
	com a verificacao de palavras repetidas na lista*/

	int achou = buscaElemento(lista, novaInfo);
	//1 == achou o elemento
	if(achou == 1)
	{
		return lista;
	}
	
	//ELSE
	Cell* novaCelula = criaCelula(novaInfo);
	novaCelula->proximo = lista;

	//Cabeca da lista
	return novaCelula;
}

/* DEBUG: Verificar se todos os elementos
foram inseridos*/
void printLista(Lista *lista)
{
	Cell *celulaAux;
	celulaAux = lista;

	while(celulaAux != NULL)
	{
		printf("%s, ", celulaAux->info);
		//printCell(celulaAux);
		celulaAux = celulaAux->proximo;
		
	}
}



Lista* listaPalavras(Lista* topo, char *nomeArquivo)
{
	FILE *arq = fopen(nomeArquivo, "r");
	char palavra[40];
	while(!feof(arq))
	{
		
		fscanf(arq, "%s", palavra);
		char *novaPalavra = split(palavra);
		topo = insereInicio(topo, novaPalavra);

	}

	fclose(arq);

	return topo;
}


/* Funcao da arvore e lista semelhantes, mudando o parametro de busca*/
void corretorLista(Lista* topoDicionario, char *nomeArquivo)
{
	FILE *arq = fopen(nomeArquivo, "r");
	while(!feof(arq))
	{
		char palavra[40];
		fscanf(arq, "%s", palavra);
		char *palavraOriginal = split(palavra);

		/*Se eu tiver alguma coisa para procurar*/
		/*strtok(split) retorna NULL caso de algum erro ou
		simplesmente o que ele retirou tornou a palavra NULL*/
		/*Eh dependente dos characters (pontuacao) que estao na funcao do mesmo*/
		if(palavraOriginal != NULL)
		{
			int achou = buscaElemento(topoDicionario, palavraOriginal);
			if(achou == 0)
			{
				char* palavraCopia = malloc(sizeof(char) * strlen(palavraOriginal) + sizeof(char));
				strcpy(palavraCopia, palavraOriginal);
				palavraCopia = lowerCase(palavraCopia);

				/*DEBUG:Para verificar se a palavra original nao esta
				sendo alterada*/
				//printf("%s, %s\n", palavraOriginal, palavraCopia);
				achou = buscaElemento(topoDicionario, palavraCopia);
				if(achou == 0)
				{
					printf("%s\n", palavraOriginal);
				}
				free(palavraCopia);
			}

		}
	}
	fclose(arq);
}

/* destruicao da celula sozinha*/
void freeCell(Cell* celula)
{
	free(celula);
}

/*Destruicao da lista inteira*/
void freeLista(Lista* topo)
{
	Cell* celulaAtual = topo;
	Cell* celulaEsquerda;

	/*Enquanto eu n achar o fim da lista,
	fico andando com ela e destruindo*/
	while(celulaAtual != NULL)
	{
		celulaEsquerda = celulaAtual->proximo;
		freeCell(celulaAtual);
		celulaAtual = celulaEsquerda;

	}
}

