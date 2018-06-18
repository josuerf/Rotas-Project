/* 
 * File:   main.c
 * Author: Josue
 *
 * Created on 16 de Junho de 2018, 22:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "main.h"
#include "vertices.h"

CidVert vert[50] = {};
Incid incid[50] = {};
char oldIni[20] = {};
int remIdx = -1;
int retorno = 0;
int globalIdx = 9;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Portuguese");
    fillList();
    printf(">> Trajeto <<\n");
    buscaLiga("SM", "POA");
    if (retorno == 0) {
        printf("Caminho Não Econtrado!\n");
    }
    return (EXIT_SUCCESS);
}

void menuPrincipal() {
    int opc;
    printf(">> Bem Vindo Ao Mapa Rodoviário <<\n1.");
    while (opc != 9) {

        switch (opc) {
            case 1:
                break;
            case 2:
                break;
        }
    }
}

void buscaCid(char ini[], char dest[]) {
    if (ini == dest) {
        printf("Caminho Possível em: [%s][%s]\n", oldIni, dest);
        retorno = 1;
        return;
    } else if (ini == oldIni) {
        retorno = 0;
        return;
    } else {
        for (; vert[ini].adjacentes != NULL; vert[ini].adjacentes = vert[ini].adjacentes->prox) {
            int num = vert[ini].adjacentes->num;
            if (vert[num].visitado != 1) {
                oldIni = ini;
                vert[ini].visitado = 1;
                printf("[%s][%s]\n", ini, num);
                buscaLiga(num, dest);
                if (retorno == 1) {
                    break;
                }
                vert[ini].visitado = 0;
            }
        }
    }
}

void InsereVertice(char nome[]) {
    int idxHolder;
    if (remIdx != -1) {
        idxHolder = remIdx;
    } else {
        idxHolder = globalIdx++;
    }
    strcpy(vert[idxHolder], nome);
    vert[idxHolder].visitado = 0;
    vert[idxHolder].adjacentes = NULL;
    remIdx = -1;
}

IncidNo *insereIncid(IncidNo *incid, int num) {
    IncidNo *aux = incid;
    IncidNo *novo = (IncidNo*) malloc(sizeof (IncidNo));
    novo->num = num;
    novo->prox = NULL;
    if (aux == NULL) {
        return novo;
    }
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    return incid;
}

CidNo *insereNo(CidNo *nos, int idx, int distancia) {
    CidNo *noAux = nos;
    CidNo *novo = (CidNo*) malloc(sizeof (CidNo));
    novo->cidade = idx;
    novo->distancia = distancia;
    novo->prox = NULL;
    if (nos != NULL) {
        while (noAux->prox != NULL) {
            noAux = noAux->prox;
        }
        noAux->prox = novo;

    } else {
        nos = novo;
    }
    return nos;
}

void removerCidade(char cidade[]) {
    int index = buscaIndice(cidade);
    removerNo(vert[index].adjacentes);
    vert[index].adjacentes = NULL;
    IncidNo *holder = incid[index].adjacentes;
    while (holder != NULL) {
        buscaLigaRemove(holder->num, cidade);
        holder = holder->prox;
    }
    removerNo(incid[index].adjacentes);
    incid[index].adjacentes = NULL;
}

void buscaLigaRemove(int incidIdx, char cidade[]) {
    CidNo *holder, *ant;
    int i = 0;
    for (holder = vert[incidIdx].adjacentes; holder.prox != NULL; holder = holder->prox) {
        if (strcmp(buscaIndice(holder->cidade),cidade) {
            if (i == 0) {
                vert[globalIdx].adjacentes->prox = holder->prox;
                free(holder);
            } else {
                ant->prox = holder->prox;
                free(holder);
            }
        }
        ant = holder;
        i++;
    }
}

void removerNo(CidNo *no) {
    if (no->prox != NULL) {
        removerNo(no->prox);
    }
    free(no);
}

void removerNo(IncidNo *no) {
    if (no->prox != NULL) {
        removerNo(no->prox);
    }
    free(no);
}

int buscaIndice(char cidade[]) {
    int i;
    for (i = 0; i < globalIdx; i++) {
        if (strcmp(cidade, vert[i].nome)) {
            return i;
        }
    }
    i = -1;
    return i;
}

char* buscaNomeCidade(int idx) {
    int i;
    for (i = 0; i < globalIdx; i++) {
        if(c)
    }
}

void fillList() {
    strcpy(vert[0].nome, "Alegrete");
    incid[0].num = 0;
    incid[0].adjacentes = NULL;
    strcpy(vert[1].nome, "Bage");
    incid[1].num = 1;
    incid[1].adjacentes = NULL;
    strcpy(vert[2].nome, "Cruz Alta");
    incid[2].num = 2;
    incid[2].adjacentes = NULL;
    strcpy(vert[3].nome, "Passo Fundo");
    incid[3].num = 3;
    incid[3].adjacentes = NULL;
    strcpy(vert[4].nome, "Pelotas");
    incid[4].num = 4;
    incid[4].adjacentes = NULL;
    strcpy(vert[5].nome, "POA");
    incid[5].num = 5;
    incid[5].adjacentes = NULL;
    strcpy(vert[6].nome, "São Borja");
    incid[6].num = 6;
    incid[6].adjacentes = NULL;
    strcpy(vert[7].nome, "São Gabriel");
    incid[7].num = 7;
    incid[7].adjacentes = NULL;
    strcpy(vert[8].nome, "Santiago");
    incid[8].num = 8;
    incid[8].adjacentes = NULL;
    strcpy(vert[9].nome, "SM");
    incid[9].num = 9;
    incid[9].adjacentes = NULL;
    vert[0].adjacentes = insereNo(vert[0].adjacentes, 6, 315);
    vert[1].adjacentes = insereNo(vert[1].adjacentes, 7, 268);
    vert[2].adjacentes = insereNo(vert[2].adjacentes, 3, 149);
    vert[2].adjacentes = insereNo(vert[2].adjacentes, 9, 134);
    vert[3].adjacentes = insereNo(vert[3].adjacentes, 5, 289);
    vert[4].adjacentes = insereNo(vert[4].adjacentes, 1, 189);
    vert[5].adjacentes = insereNo(vert[5].adjacentes, 4, 261);
    vert[5].adjacentes = insereNo(vert[5].adjacentes, 1, 377);
    vert[6].adjacentes = insereNo(vert[6].adjacentes, 8, 141);
    vert[7].adjacentes = insereNo(vert[7].adjacentes, 0, 204);
    vert[8].adjacentes = insereNo(vert[8].adjacentes, 2, 242);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 8, 152);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 0, 258);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 7, 182);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 1, 239);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 5, 291);
    incid[6].adjacentes = insereIncid(incid[6].adjacentes, 0);
    incid[7].adjacentes = insereIncid(incid[7].adjacentes, 1);
    incid[7].adjacentes = insereIncid(incid[7].adjacentes, 9);
    incid[5].adjacentes = insereIncid(incid[5].adjacentes, 3);
    incid[5].adjacentes = insereIncid(incid[5].adjacentes, 9);
    incid[4].adjacentes = insereIncid(incid[4].adjacentes, 5);
    incid[3].adjacentes = insereIncid(incid[3].adjacentes, 2);
    incid[2].adjacentes = insereIncid(incid[2].adjacentes, 8);
    incid[1].adjacentes = insereIncid(incid[1].adjacentes, 4);
    incid[1].adjacentes = insereIncid(incid[1].adjacentes, 5);
    incid[1].adjacentes = insereIncid(incid[1].adjacentes, 9);
    incid[0].adjacentes = insereIncid(incid[0].adjacentes, 9);
    incid[0].adjacentes = insereIncid(incid[0].adjacentes, 7);
    incid[8].adjacentes = insereIncid(incid[8].adjacentes, 9);
    incid[8].adjacentes = insereIncid(incid[8].adjacentes, 6);
    incid[9].adjacentes = insereIncid(incid[9].adjacentes, 2);
}
