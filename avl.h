#ifndef  AVL_H
#define  AVL_H

typedef struct NO* ArvAVL;


ArvAVL* cria_ArvAVL();
void libera_NO(struct NO* no);
void libera_ArvAVL(ArvAVL* raiz);
int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int maior(int x, int y);
int estaVazia_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int chave);
void Att(ArvAVL *raiz, int chave,int valor);
void RotacaoLL(ArvAVL *A);
void RotacaoRR(ArvAVL *A);
void RotacaoLR(ArvAVL *A);
void RotacaoRL(ArvAVL *A);
int insere_ArvAVL(ArvAVL *raiz, int chave,int valor);
int remove_ArvAVL(ArvAVL *raiz, int chave);
int Insert(ArvAVL*z,int chave,int op,int valor);
int Remove(ArvAVL*z,int chave);
int NoChave(ArvAVL* Arvore);
int NoValor(ArvAVL* Arvore);
int NoQtdOp(ArvAVL* Arvore);
ArvAVL* NoEsq(ArvAVL*raiz);
ArvAVL* NoDir(ArvAVL*raiz);
void AttPais(ArvAVL *Arvore);
void AttPais(ArvAVL *A);


#endif
