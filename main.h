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
void buscaLiga(char ini[], char dest[]);
CidNo *insereNo(CidNo *nos, int idx, int distancia, int parentIdx);
void fillList();
void InsereVertice(char nome[]);
void removerCidade(char cidade[]);
void removerNo(CidNo *no);
void removerNoIncid(IncidNo *no);
int buscaIndice(char cidade[]);
void buscaLigaRemove(int incidIdx, char cidade[]);
void atualizaCidade(int idxVert, char nome[], int distancia, int idxNo);
void listarNos(int idxVert);
#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

