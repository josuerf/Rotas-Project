/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newsimpletest1.c
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 11:06
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/*
 * Simple C Test Suite
 */

void testBuscaLiga() {
    int ini;
    int dest;
    buscaLiga(ini, dest);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testBuscaLiga (newsimpletest1) message=error message sample\n");
    }
}

void testInsereNo() {
    CidNo* nos;
    int num;
    CidNo* result = insereNo(nos, num);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testInsereNo (newsimpletest1) message=error message sample\n");
    }
}

void testFillList() {
    fillList();
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testFillList (newsimpletest1) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% newsimpletest1\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testBuscaLiga (newsimpletest1)\n");
    testBuscaLiga();
    printf("%%TEST_FINISHED%% time=0 testBuscaLiga (newsimpletest1)\n");

    printf("%%TEST_STARTED%%  testInsereNo (newsimpletest1)\n");
    testInsereNo();
    printf("%%TEST_FINISHED%% time=0 testInsereNo (newsimpletest1)\n");

    printf("%%TEST_STARTED%%  testFillList (newsimpletest1)\n");
    testFillList();
    printf("%%TEST_FINISHED%% time=0 testFillList (newsimpletest1)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
