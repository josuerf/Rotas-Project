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

#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
void buscaLiga(char ini[], char dest[]);
CidNo *insereNo(CidNo *nos, int idx, int distancia);
void fillList();
void InsereVertice(char nome[]);
void removerCidade(char cidade[]);
void removerNo(char cidade[]);
int buscaIndice(char cidade[]);
#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

