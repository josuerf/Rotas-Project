/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nos.h
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 10:28
 */

#ifndef NOS_H
#define NOS_H

#ifdef __cplusplus
extern "C" {
#endif

struct cid_no {
        int cidade;
        int distancia;
        int visitado;
        struct cid_no *prox;
    };

    struct incid_no {
        int num;
        struct incid_no *prox;
    };
    typedef struct incid_no IncidNo;
    typedef struct cid_no CidNo;


#ifdef __cplusplus
}
#endif

#endif /* NOS_H */

