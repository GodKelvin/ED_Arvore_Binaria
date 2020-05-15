#ifndef LISTA_SIMPLES
#define LISTA_SIMPLES

/* Coloquei aqui as funcoes que usei, mesmo que por debug*/

typedef struct Celula Cell;
typedef struct Celula Lista;

void freeLista(Lista* lista);
void printLista(Lista* lista);
void corretorLista(Lista* topoDicionario, char *nomeArquivo);

int buscaElemento(Lista* lista, char *elemento);

Lista* criaLista();
Lista* insereInicia(Lista* lista, Cell* celula);
Lista* listaPalavras(Lista* topo, char *nomeArquivo);

Cell* criaCelula(char info[]);


#endif