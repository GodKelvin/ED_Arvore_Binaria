#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBinaria.h"
#include "characters.h"

//ArvoreBinaria
/*Professor, tentei modularizar Arvore / Noh, mas acabei
me complicando e me perdendo na codificacao*/
struct Noh
{
	char info[30];
	struct Noh* esquerda;
	struct Noh* direita;
};

Arvore* criaArvore()
{
	return NULL;
}

/*Arvore Binaria, cuja a informacao eh uma palavra (especificada em Noh)*/
Noh* criaNoh(char info[])
{
	Noh* novoNoh = (Noh*) malloc(sizeof(Noh));
	strcpy(novoNoh->info, info);
	novoNoh->esquerda = NULL;
	novoNoh->direita = NULL;
	
	return novoNoh;
}


/*Retorna 1 caso encontra a palavra (elemento) e
0 caso nao encontre*/
int buscaBinariaLaco(Arvore* raiz, char *elemento)
{
	if(raiz != NULL)
	{
		//Se for == 0, info e elemento sao iguais
		while(strcmp(raiz->info, elemento) !=  0)
		{
			//Elemento menor que raiz->info
			if(strcmp(elemento, raiz->info) < 0)
			{
				raiz = raiz->esquerda;
			}

			//Elemento maior que raiz->info
			else
			{
				raiz = raiz->direita;
			}

			//Nao achou o elemento
			if(raiz == NULL)
			{
				return 0;
			}
		}

		//Achou o elemento
		return 1;
	}
	//Raiz vazia / nao achou o elemento
	return 0;
}

/*Aqui vai o motivo da Arvore ser mais rapida: ORDENACAO */
Arvore* insereOrdenado(Arvore* raiz, char *novaInfo)
{
	Noh* novoNoh = criaNoh(novaInfo);
	if(raiz == NULL)
	{
		raiz = novoNoh;
		return raiz;
	}
	//ELSE
	Noh* nohAtual = raiz;

	
	int achouNovaInfo = buscaBinariaLaco(nohAtual, novaInfo);
	//Jah existe essa palavra na arvore
	if(achouNovaInfo == 1)
	{
		//--DEBUG--
		//printf("Jah existe! %d\n", novaInfo);
		return raiz;
	}

	//ELSE
	//Busco o Noh Antecessor ao novo Noh
	while(nohAtual != NULL)
	{
		if(strcmp(novaInfo, nohAtual->info) < 0)
		{
			//Nao tenho mais o que descer pra esquerda
			if(nohAtual->esquerda == NULL)
			{
				nohAtual->esquerda = novoNoh;
				return raiz;
			}
			
			nohAtual = nohAtual->esquerda;
		}
		else
		{
			//Nao tenho mais o que descer pra direita
			if(nohAtual->direita == NULL)
			{
				nohAtual->direita = novoNoh;
				return raiz;
			}
			nohAtual = nohAtual->direita;
		}
	}
	/*So pro GCC parar de reclamar*/
	/*Nao faz diferenca*/
	return raiz;
}

/*Aqui eu apliquei um metodo de destruicao recursivo.
Testei com uma variavel global, e a cada malloc eu aumentava
ela em 1 e a cada free eu diminuia ela em 1, no final ela estava
zerada, chegando a conclusao que a arvore foi destruida corretamente */ 
void freeArvore(Arvore* raiz)
{
	if(raiz != NULL)
	{
		if(raiz->esquerda != NULL)
		{
			freeArvore(raiz->esquerda);
		}
		
		if(raiz->direita != NULL)
		{
			freeArvore(raiz->direita);
		}
		
		free(raiz);
	}
}


/*ERD*/
/*DEBUG: Funcao para verificar se a 
arvore estava inserindo seus elementos corretamente.
(em ordem crescente)*/
void ordemSimetrica(Arvore* raiz)
{
	if(raiz != NULL)
	{
		ordemSimetrica(raiz->esquerda);
		printf("%s, ", raiz->info);
		ordemSimetrica(raiz->direita);
	}
}

/*Funcao para montar a arvore (o dicionario, no caso)*/
Arvore* arvorePalavras(Arvore* raiz, char *nomeArquivo)
{
	//Arvore* novaArvore = criaArvore();	
	FILE *arq = fopen(nomeArquivo, "r");
	char palavra[40];
	while(!feof(arq))
	{
		
		fscanf(arq, "%s", palavra);
		char *novaPalavra = split(palavra);
		raiz = insereOrdenado(raiz, novaPalavra);

	}

	fclose(arq);

	return raiz;
}

/* Funcao da arvore e lista semelhantes, mudando o parametro de busca*/
void corretorArvore(Arvore* raizDicionario, char *nomeArquivo)
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
			int achou = buscaBinariaLaco(raizDicionario, palavraOriginal);
			if(achou == 0)
			{
				char* palavraCopia = malloc(sizeof(char) * strlen(palavraOriginal) + sizeof(char));
				strcpy(palavraCopia, palavraOriginal);
				palavraCopia = lowerCase(palavraCopia); 
				
				/*DEBUG IMPORTANTISSIMO*/
				/*Verifico se a palavra original n foi modificada,
				para que ela saia corretamente na tela do terminal*/
				//printf("%s, %s\n", palavraOriginal, palavraCopia); 
				achou = buscaBinariaLaco(raizDicionario, palavraCopia);
				if(achou == 0)
				{
					/*Caso o programa n encontre a palavra em sua forma
					normal e nem em lowerCase, eu mostro na tela*/
					printf("%s\n", palavraOriginal);
					
				}
				free(palavraCopia);
			}
		}
	}
	fclose(arq);
}
