#include <stdio.h>
#include <stdlib.h>
#include "avl.h"



struct NO{
    int Chave,qtdOp,Valor;//Chave, quantidade de operacoes , valor
    int altura;
    struct NO *pai;
    struct NO *esq;
    struct NO *dir;
};


ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){// Quantos nos tem a arvore
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int consulta_ArvAVL(ArvAVL *raiz, int chave){//consulta se existe o elemento existindo
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(chave == atual->Chave){
            return 1;
        }
        if(chave > atual->Chave)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}
void Att(ArvAVL *raiz, int chave,int valor){//funcao que atualiza o valor de um no
  if(raiz == NULL)
      return ;
  struct NO* atual = *raiz;
  while(atual != NULL){
      if(chave == atual->Chave){
           atual->Valor+=valor;
           atual->qtdOp++;
      }
      if(chave > atual->Chave)
          atual = atual->dir;
      else
          atual = atual->esq;
  }
  return;

}
//=================================
void RotacaoLL(ArvAVL *A){//LL
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int chave,int valor){// funcao inicial de insere(sem o tratamento)
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->Chave = chave;
        novo->qtdOp=1;
        novo->Valor=valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->pai=NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(chave < atual->Chave){
        if((res = insere_ArvAVL(&(atual->esq), chave,valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(chave < (*raiz)->esq->Chave ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(chave > atual->Chave){
            if((res = insere_ArvAVL(&(atual->dir), chave,valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->Chave < chave){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int chave){// funcao inicial de remove(sem o tratamento)
	if(*raiz == NULL){// chave não existe
	    return 0;
	}

    int res;
	if(chave < (*raiz)->Chave){
	    if((res = remove_ArvAVL(&(*raiz)->esq,chave)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->Chave < chave){
	    if((res = remove_ArvAVL(&(*raiz)->dir, chave)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->Chave == chave){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->Chave = temp->Chave;
      (*raiz)->qtdOp= temp->qtdOp;
      (*raiz)->Valor= temp->Valor;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->Chave);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}






int Insert(ArvAVL*z,int chave,int op,int valor){//funcao oficial de insercao
  if(z==NULL){
    return 0;
  }
  if(op==1)
  valor= -valor;

  if(consulta_ArvAVL(z,chave)==1){
//atualiza o valor
    Att(z,chave,valor);
    return 1;
  }
  else{
    insere_ArvAVL(z,chave,valor);
    AttPais(z);
    return 1;
  }
  return 0;
}

int Remove(ArvAVL*z,int chave){// funcao oficial de remocao
  if(z==NULL){
    return 0;
  }
  if(consulta_ArvAVL(z,chave)==1){
    remove_ArvAVL(z,chave);
    if((*z)!=NULL)
    AttPais(z);
    return 1;
  }
  return 0;
}

int NoChave(ArvAVL* Arvore){
  return (*Arvore)->Chave;
}
int NoValor(ArvAVL* Arvore){
  return (*Arvore)->Valor;
}
int NoQtdOp(ArvAVL* Arvore){
  return (*Arvore)->qtdOp;
}
ArvAVL* NoEsq(ArvAVL*raiz){
return  (&((*raiz)->esq));
}
ArvAVL* NoDir(ArvAVL*raiz){
return  (&((*raiz)->dir));
}
ArvAVL* NoPai(ArvAVL*raiz){
return  (&((*raiz)->pai));
}



void AttPais(ArvAVL *Arvore){// funcao que atualiza os pais na remocao e insercao
  if(Arvore!=NULL){
    if((*Arvore)->esq!=NULL){
    struct NO *Arvore2=(*Arvore)->esq;
    Arvore2->pai=(*Arvore);
    AttPais(&((*Arvore)->esq));
  }
  if((*Arvore)->dir!=NULL){
    struct NO *Arvore3=(*Arvore)->dir;
    Arvore3->pai=(*Arvore);
    AttPais(&((*Arvore)->dir));
  }
  }
}

