/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.h
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 10:40
 */

#ifndef MAIN_H
#include "vertices.h"
#include "menus.h"

#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

    struct distancias {
        int dist;
        struct distancias *prox;
    };
    struct excluidos{
        int index;
        struct excluidos *prox;
    };
    struct visitados{
        int *visitado;
        struct visitados *prox;
    };
    typedef struct excluidos Excluidos;
    typedef struct distancias Distancias;
    typedef struct visitados Visitados;
    void buscaCid(int ini, char dest[],int dist);
    CidNo *insereNo(CidNo *nos, int idx, int distancia, int parentIdx);
    IncidNo *insereIncid(IncidNo *incid, int num);
    void alteraDistancia(int idxOrigem, int idxDestino, int distancia);
    void fillList();
    void buscaLigaRemove(int incidIdx,int cidIndex);
    void insereVertice(char nome[]);
    void removerCidade(int index);
    void removerNo(CidNo *no);
    void removerNoIncid(IncidNo *no);
    int buscaIndice(char cidade[]);
    void atualizaCidade(int idxVert, char nome[], int distancia, int idxNo);
    void listarNos(int idxVert);
    void buscaVizinhas(int ini);
    void limparDistancias(Distancias *dist);
    void removeIncid(int incidIdx, int origem);
    void listarTodas();
    void alteraNome(char *nome);
    void limparVisitados(Visitados* visitado);
    Excluidos *insereExcluido(Excluidos *excluido, int index);
#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

