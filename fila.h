

#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include "personagens.h"
#define MAX 100

typedef struct {
  char nome[50];
  int vida;
  int ataque;
} Personagens1;

typedef Personagens1 tp_item;
typedef struct{
  tp_item item[MAX];
  int ini, fim;
//int tam;
}tp_fila;

//Inicia a fila
void inicializaFila(tp_fila *f){
  f->ini = f->fim = MAX-1;
  //f->tam=0;
}
//se o incio for igual ao fim, significa que a fila esta vazia 
int filaVazia(tp_fila *f){
  if(f->ini == f->fim) return 1;

  return 0;
}
int proximo(int pos){
  if(pos==MAX-1)return 0;
  return ++pos;
}
int filaCheia(tp_fila *f){
  if(proximo(f->fim)==f->ini)
    return 1;
  return 0;
}

int insereFila(tp_fila *f, tp_item Personagens1){
  if(filaCheia(f))
    return 0; //diz que nao foi possivel adicinar na fila
  f->fim = proximo(f->fim);
  f->item[f->fim]=Personagens1;
  //f->tam++;
  return 1;
}

int removeFila(tp_fila *f, tp_item *e){
  if(filaVazia(f))
    return 0; //diz que nao foi possivel remover da fila
  f->ini = proximo(f->ini);
  *e=f->item[f->ini];
  //f->tam--;
  return 1;
}

//Tira todos os elementos da fila (igual em uma pilha) e imprime eles em tela
void imprimeFila(tp_fila f){
  tp_item e;
  printf("\n");
  while(!filaVazia(&f)){
    removeFila(&f, &e);
    printf("%d", e);
  }
}




//Mostra o tamanho da fila
int tamFila(tp_fila *f){
  if(filaVazia(f)) return 0;
  if(f->ini < f->fim) return f->fim - f->ini;
  return MAX-1-f->ini+f->fim+1;
}
//outro jeito de fazer

//int tamFila1(tp_fila f){
  //int count=0;
  //tp_item e;
  //while(!filaVazia(&f)){
   // removeFila(&f,&e);
   // count++;
 // }
  //return count;
//}
#endif
