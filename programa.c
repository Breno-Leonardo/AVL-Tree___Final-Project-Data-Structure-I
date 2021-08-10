#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
//Breno Leonardo Lima Macedo



//FUNCOES DE IMPRESSAO
void Ordenado(ArvAVL *raiz){//ocultar coisas da tad
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        Ordenado(NoEsq(raiz));
        printf("%i %i %i\n",NoChave(raiz),NoQtdOp(raiz),NoValor(raiz));
        Ordenado(NoDir(raiz));
    }
}

void Desordenado(ArvAVL *raiz){//ocultar coisas da tad
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
      Desordenado(NoDir(raiz));
      printf("%i %i %i\n",NoChave(raiz),NoQtdOp(raiz),NoValor(raiz));
      Desordenado(NoEsq(raiz));
    }
}

void exibir_nivel(ArvAVL *aux, int atual, int cont){
    if((*aux)==NULL){
        return;
    }
    else{
        exibir_nivel(NoEsq(aux), atual, cont+1);

           if(atual==cont)
            printf("%i\n", NoChave(aux));


        exibir_nivel(NoDir(aux), atual, cont+1);
    }
}

int main(){

  ArvAVL *Arvore;
  Arvore=cria_ArvAVL();
  int op,chave,valor;
  char com, com2;


  while(com!='f'){
    scanf("%c",&com );
    getchar();
   if (com=='i'){//Insere
     scanf("%i %i %i",&chave, &op, &valor);
     getchar();
     Insert(Arvore,chave,op,valor);
   }

   else if(com=='c'){//consulta
     scanf("%i",&chave);
     getchar();
     int j=consulta_ArvAVL(Arvore,chave);
     if(j==1)
      printf("existe no com chave: %i\n",chave );
     else
     printf("nao existe no com chave: %i\n",chave );
   }
   else if(com=='r'){//remove
     scanf("%i",&chave);
     getchar();
     Remove(Arvore,chave);
   }

   else if(com=='p'){//lista chaves
     scanf("%c",&com2);
     getchar();
     if(com2=='c'){//crescente
      Ordenado(Arvore);
     }
     else if(com2=='d'){//decrescente
      Desordenado(Arvore);
     }

   }

   else if(com=='n'){
    scanf("%i",&chave);//nivel
    getchar();
    exibir_nivel(Arvore,chave,1);
   }

   else if(com=='h'){
     printf("%i\n",altura_ArvAVL(Arvore));
   }

   else if(com=='f'){
     printf("-+- Inicio relatorio -+-\n"  );
     int k=totalNO_ArvAVL(Arvore);
     printf("%i\n",k );
          for (int i = 0; i < k; i++) {
            printf("%i %i %i\n",NoChave(Arvore),NoQtdOp(Arvore),NoValor(Arvore));
            Remove(Arvore,NoChave(Arvore));
          }
          printf("-+- Fim relatorio -+-\n" );
   }


}

libera_ArvAVL(Arvore);
}

