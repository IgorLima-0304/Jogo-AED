/*AQUI ESTÁ DEFINIDO:
combate
empilhamento de animais
turnos
nome do time
*/
#include "personagens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listade.h"
#include "fila.h"

#define MAX_ADJETIVOS 6
#define MAX_SUBSTANTIVOS 5
#define MAX_PERSONAGENS 21
#define MAX_NOME_TIME 50

void nomedoTime(char *adjetivo, char *substantivo) {
    char *adjetivos[MAX_ADJETIVOS] = {"Baratino", "Disgramado", "Migueloso", "Boca-de-afofô", "Barril", "La ele"};
    char *substantivos[MAX_SUBSTANTIVOS] = {"Guerreiro", "Herói", "Aventureiro", "Explorador", "Cavaleiro"};

    srand(time(NULL));

    strcpy(adjetivo, adjetivos[rand() % MAX_ADJETIVOS]);
    strcpy(substantivo, substantivos[rand() % MAX_SUBSTANTIVOS]);
}

void digitarNomeTime(char *nomeTime) {
    printf("Digite o nome do time: ");
    scanf("%s", nomeTime);
}

void gravarCombate(Jogador *jogador, Jogador *inimigo, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para gravar os detalhes do combate.\n");
        return;
    }

    fprintf(arquivo, "Combate:\n");
    for (int i = 0; i < MAX_EQUIPE; i++) {
        if (jogador->equipe[i].nome[0] != '\0') {
            fprintf(arquivo, "Jogador: %s, Vida: %d, Ataque: %d\n", jogador->equipe[i].nome, jogador->equipe[i].vida, jogador->equipe[i].ataque);
        }
        if (inimigo->equipe[i].nome[0] != '\0') {
            fprintf(arquivo, "Inimigo: %s, Vida: %d, Ataque: %d\n", inimigo->equipe[i].nome, inimigo->equipe[i].vida, inimigo->equipe[i].ataque);
        }
    }
    fprintf(arquivo, "Número de troféus: %d\n", jogador->trofeus);
    fprintf(arquivo, "---------------------\n");

    fclose(arquivo);
}

void lerCombates(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para ler os detalhes dos combates.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    fclose(arquivo);
}


void combate(Jogador *jogador, Jogador *inimigo) {
    tp_fila filaJogador, filaInimigo;
    inicializaFila(&filaJogador);
    inicializaFila(&filaInimigo);

    for (int j = 0; j < MAX_EQUIPE; j++) {
        if (jogador->equipe[j].vida > 0) {
            tp_item item;
            strcpy(item.nome, jogador->equipe[j].nome);
            item.vida = jogador->equipe[j].vida;
            item.ataque = jogador->equipe[j].ataque;
            insereFila(&filaJogador, item);
        }
        if (inimigo->equipe[j].vida > 0) {
            tp_item item;
            strcpy(item.nome, inimigo->equipe[j].nome);
            item.vida = inimigo->equipe[j].vida;
            item.ataque = inimigo->equipe[j].ataque;
            insereFila(&filaInimigo, item);
        }
    }

    int i = 0, j = 0;
    tp_item pj, pi;
    while (i < MAX_EQUIPE && j < MAX_EQUIPE) {
        if (filaVazia(&filaJogador)) {
            i++;
            continue;
        }
        if (filaVazia(&filaInimigo)) {
            j++;
            continue;
        }

        removeFila(&filaJogador, &pj);
        removeFila(&filaInimigo, &pi);
        printf("%s (Vida: %d, Ataque: %d) vs %s (Vida: %d, Ataque: %d)\n",
               pj.nome, pj.vida, pj.ataque, pi.nome, pi.vida, pi.ataque);

        pj.vida -= pi.ataque;
        pi.vida -= pj.ataque;

        if (pj.vida <= 0) {
            printf("%s desmaiou!\n", pj.nome);
            i++;
        } else {
            insereFila(&filaJogador, pj);
        }

        if (pi.vida <= 0) {
            printf("%s desmaiou!\n", pi.nome);
            j++;
        } else {
            insereFila(&filaInimigo, pi);
        }
    }

    if (i >= MAX_EQUIPE) {
        printf("Você perdeu o combate.\n");
        jogador->vidaj -= 1;
        if (jogador->vidaj == 0) {
            printf("Perdeu playboy.\n");
        }
    } else {
        printf("Você venceu o combate.\n");
        jogador->trofeus += 1;
        if (jogador->trofeus == 10) {
            printf("Venceu na vida!\n");
        }
    }

    gravarCombate(jogador, inimigo, "combates.txt");
}

int main() {
    tp_pilha pilha;
    inicializarPilha(&pilha);

    char adjetivo[50];
    char substantivo[50];
    char nomeTime[MAX_NOME_TIME];

    digitarNomeTime(nomeTime);
    nomedoTime(adjetivo, substantivo);
    printf("Nome do time: %s %s %s\n", nomeTime, substantivo, adjetivo);

    criarAnimais(MAX_PERSONAGENS, &pilha);

    tp_listad *lista = inicializa_listad();
    Personagens loja[3];

    renovarLoja(loja, &pilha);
    for (int i = 0; i < 3; i++) {
        insere_listad_no_fim(lista, loja[i]);
    }

    Jogador jogador;
    inicializarJogador(&jogador);

    int turno = 1;
    while (jogador.vidaj > 0 && jogador.trofeus < 10) {
        Jogador inimigo;
        inicializarJogador(&inimigo);
        for (int i = 0; i < MAX_EQUIPE; i++) {
            pop(&pilha, &inimigo.equipe[i]);
        }

        printf("\n----- Turno %d -----\n", turno);
        jogador.ouro = 10;
        printf("Ouro do Jogador: %d\n", jogador.ouro);
        printf("Vida do jogador: %d\n", jogador.vidaj);
        printf("Troféus do jogador: %d\n\n", jogador.trofeus);
        printf("\nTime do jogador:\n");
        for (int i = 0; i < MAX_EQUIPE; i++) {
            if (jogador.equipe[i].nome[0] != '\0') {
                printf("%d. %s (Vida: %d, Ataque: %d)\n", i + 1, jogador.equipe[i].nome, jogador.equipe[i].vida, jogador.equipe[i].ataque);
            }
        }

        exibirLoja(loja);

        int acao;
        do {
            printf("\n1. Comprar pet\n2. Vender pet\n3. Renovar loja\n4. Ir para combate\n5. Ver histórico de combates\nEscolha: ");
            scanf("%d", &acao);
            if (acao == 1) {
                int indice;
                printf("Digite o índice do pet para comprar (1-3): ");
                scanf("%d", &indice);
                if (indice >= 1 && indice <= 3 && loja[indice-1].ocupado) {
                    comprarPersonagem(&jogador, loja, indice - 1);
                    printf("Ouro do Jogador: %d\n", jogador.ouro);
                } else {
                    printf("Posição vazia.\n");
                }
            } else if (acao == 2) {
                int indice;
                printf("Digite o índice do pet para vender (1-5): ");
                scanf("%d", &indice);
                if (indice >= 1 && indice <= 5) {
                    venderPersonagem(&jogador, indice - 1);
                    printf("Ouro do Jogador: %d\n", jogador.ouro);
                } else {
                    printf("Índice inválido.\n");
                }
            } else if (acao == 3) {
                if (jogador.ouro >= CUSTO_RENOVAR) {
                    jogador.ouro -= CUSTO_RENOVAR;
                    renovarLoja(loja, &pilha);
                    printf("Ouro do Jogador: %d\n", jogador.ouro);
                    exibirLoja(loja);
                } else {
                    printf("Ouro insuficiente.\n\n");
                }
            } else if (acao == 5) {
                lerCombates("combates.txt");
            }
        } while (acao != 4);

        combate(&jogador, &inimigo);
        turno++;
    }

    return 0;
}
