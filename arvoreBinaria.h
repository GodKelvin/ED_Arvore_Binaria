#ifndef ARVORE_BINARIA
#define ARVORE_BINARIA

/*Coloquei aqui as funcoes que usei, mesmo que por debug*/
typedef struct Noh Arvore;
typedef struct Noh Noh;

void freeArvore(Arvore* raiz);
void ordemSimetrica(Arvore* raiz);
int buscaBinariaLaco(Arvore* raiz, char elemento[]);
void corretorArvore(Arvore* raizDicionario, char *nomeArquivo);

Arvore* criaArvore();
Arvore* insereOrdenado(Arvore* raiz, char *novaInfo);
Arvore* arvorePalavras(Arvore* raiz, char *nomeArquivo);

#endif