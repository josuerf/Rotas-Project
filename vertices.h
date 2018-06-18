
/* 
 * File:   vertices.h
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 10:26
 */

#ifndef VERTICES_H
#define VERTICES_H
#include "Nos.h"
#ifdef __cplusplus
extern "C" {
#endif

struct cid_vert{
	char nome[20];
	int visitado;
	struct cid_no *adjacentes;
};
struct incid_vert{
    int num;
    struct incid_no *adjacentes;
};
typedef struct incid_vert Incid;
typedef struct cid_vert CidVert;

#ifdef __cplusplus
}
#endif

#endif /* VERTICES_H */

