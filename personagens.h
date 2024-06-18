/*Aqui está definido a estrutura dos personagens */

#ifndef PERSONAGENS_H
#define PERSONAGENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fila.h"


#define MAX_PERSONAGENS 21
#define MAX 100
#define MAX_EQUIPE 5
#define CUSTO_PERSONAGEM 3
#define CUSTO_RENOVAR 1

typedef struct {
  char nome[50];
  int vida;
  int ataque;
  int ocupado;
} Personagens;

typedef struct {
  int topo;
  Personagens item[MAX];
} tp_pilha;

typedef struct {
  Personagens equipe[MAX_EQUIPE];
  int vida;
  int ouro;
  int trofeus;
} Jogador;

void inicializarPilha(tp_pilha *p) { p->topo = -1; }

int pilhaVazia(tp_pilha *p) {
  if (p->topo == -1)
    return 1;
  return 0;
}


int pilhaCheia(tp_pilha *p) {
  if (p->topo == MAX - 1)
    return 1;
  return 0;
}


int push(tp_pilha *p, Personagens e) {
  if (pilhaCheia(p) == 1)
    return 0;
  p->topo++;
  p->item[p->topo] = e;
  return 1;
}


int pop(tp_pilha *p, Personagens *e) {
  if (pilhaVazia(p) == 1)
    return 0;
  *e = p->item[p->topo];
  p->topo--;
  return 1;
}


int top(tp_pilha *p, Personagens *e) {
  if (pilhaVazia(p))
    return 0;
  *e = p->item[p->topo];
  return 1;
}


void imprimePilha(tp_pilha p) {
  Personagens e;
  printf("\n");
  while (!pilhaVazia(&p)) {
    pop(&p, &e);
    printf("Nome: %s, Vida: %d, Ataque: %d\n", e.nome, e.vida, e.ataque);
  }
}


int alturaPilha(tp_pilha *p) { return p->topo + 1; }


    void criarAnimais(int numPersonagens, tp_pilha *p) {
      Personagens personagem[MAX_PERSONAGENS];
      srand(time(NULL)); // função usada para randomizar o nome dos personagens

      for (int i = 0; i < MAX_PERSONAGENS; i++) {
        switch (i) {
        // código de inicialização dos personagens]
        }
        personagem[i].ocupado = 1; 
      }

      for (int i = 0; i < MAX_PERSONAGENS; i++) {
        int randnum = rand() % MAX_PERSONAGENS;
        push(p, personagem[randnum]);
      
    switch (i) {
    case 0:
      strcpy(personagem[i].nome, "Elefante");
      personagem[i].vida = 10;
      personagem[i].ataque = 9;
      break;
    case 1:
      strcpy(personagem[i].nome, "Gorila");
      personagem[i].vida = 8;
      personagem[i].ataque = 8;
      break;
    case 2:
      strcpy(personagem[i].nome, "Bisão");
      personagem[i].vida = 9;
      personagem[i].ataque = 7;
      break;
    case 3:
      strcpy(personagem[i].nome, "Urso");
      personagem[i].vida = 9;
      personagem[i].ataque = 8;
      break;
    case 4:
      strcpy(personagem[i].nome, "Leão");
      personagem[i].vida = 8;
      personagem[i].ataque = 9;
      break;
    case 5:
      strcpy(personagem[i].nome, "Tigre");
      personagem[i].vida = 7;
      personagem[i].ataque = 9;
      break;
    case 6:
      strcpy(personagem[i].nome, "Rinoceronte");
      personagem[i].vida = 9;
      personagem[i].ataque = 7;
      break;
    case 7:
      strcpy(personagem[i].nome, "Crocodilo");
      personagem[i].vida = 8;
      personagem[i].ataque = 8;
      break;
    case 8:
      strcpy(personagem[i].nome, "Hipopótamo");
      personagem[i].vida = 8;
      personagem[i].ataque = 8;
      break;
    case 9:
      strcpy(personagem[i].nome, "Leopardo");
      personagem[i].vida = 6;
      personagem[i].ataque = 7;
      break;
    case 10:
      strcpy(personagem[i].nome, "Lobo");
      personagem[i].vida = 7;
      personagem[i].ataque = 7;
      break;
    case 11:
      strcpy(personagem[i].nome, "Hiena");
      personagem[i].vida = 6;
      personagem[i].ataque = 6;
      break;
    case 12:
      strcpy(personagem[i].nome, "Guepardo");
      personagem[i].vida = 5;
      personagem[i].ataque = 6;
      break;
    case 13:
      strcpy(personagem[i].nome, "Alce");
      personagem[i].vida = 7;
      personagem[i].ataque = 6;
      break;
    case 14:
      strcpy(personagem[i].nome, "Onça");
      personagem[i].vida = 6;
      personagem[i].ataque = 7;
      break;
    case 15:
      strcpy(personagem[i].nome, "Camelo");
      personagem[i].vida = 5;
      personagem[i].ataque = 2;
      break;
    case 16:
      strcpy(personagem[i].nome, "Leão-marinho");
      personagem[i].vida = 7;
      personagem[i].ataque = 7;
      break;
    case 17:
      strcpy(personagem[i].nome, "Orangotango");
      personagem[i].vida = 5;
      personagem[i].ataque = 5;
      break;
    case 18:
      strcpy(personagem[i].nome, "Lince");
      personagem[i].vida = 4;
      personagem[i].ataque = 5;
      break;
    case 19:
      strcpy(personagem[i].nome, "Javali");
      personagem[i].vida = 6;
      personagem[i].ataque = 6;
      break;
    case 20:
      strcpy(personagem[i].nome, "Coelho");
      personagem[i].vida = 3;
      personagem[i].ataque = 3;
      break;
    }
  }

  for (int i = 0; i < MAX_PERSONAGENS; i++) {
    int randnum = rand() % MAX_PERSONAGENS;
    push(p, personagem[randnum]);
  }
}
// Inventário do jogador
void inicializarJogador(Jogador *jogador) {
  jogador->vida = 10;
  jogador->ouro = 10;
  jogador->trofeus = 0;
  for (int i = 0; i < MAX_EQUIPE; i++) {
    jogador->equipe[i].nome[0] = '\0';
    jogador->equipe[i].vida = 0;
    jogador->equipe[i].ataque = 0;
  }
}

void exibirLoja(Personagens *loja) {
  printf("Loja:\n");
  for (int i = 0; i < 3; i++) {
    printf("%d. %s (Vida: %d, Ataque: %d)\n", i + 1, loja[i].nome, loja[i].vida, loja[i].ataque);
  }
}

void comprarPersonagem(Jogador *jogador, Personagens *loja, int indice){
  if (jogador->ouro >= CUSTO_PERSONAGEM) {
    for (int i = 0; i < MAX_EQUIPE; i++) {
      if (jogador->equipe[i].nome[0] == '\0') {
        jogador->equipe[i] = loja[indice];
        jogador->ouro -= CUSTO_PERSONAGEM;
        loja[indice].ocupado = 0; // Marca a posição na loja como vazia
        printf("Você comprou %s.\n", loja[indice].nome);
        return;
      }
    }
    printf("Sua equipe está cheia.\n");
  } else {
    printf("Ouro insuficiente.\n");
  }
}

void venderPersonagem(Jogador *jogador, int indice) {
  if (jogador->equipe[indice].nome[0] != '\0') {
    jogador->ouro += 1;
    printf("Você vendeu %s.\n", jogador->equipe[indice].nome);
    jogador->equipe[indice].nome[0] = '\0';
    jogador->equipe[indice].vida = 0;
    jogador->equipe[indice].ataque = 0;
  } else {
    printf("Não há pet para vender nessa posição.\n");
  }
}

void renovarLoja(Personagens *loja, tp_pilha *pilha) {
  for (int i = 0; i < 3; i++) {
    pop(pilha, &loja[i]);
    loja[i].ocupado = 1; 
  }
}




#endif