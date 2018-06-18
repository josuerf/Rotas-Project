/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   metodos_main_test.c
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 10:43
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
        printf("%%TEST_FAILED%% time=0 testname=testBuscaLiga (metodos_main_test) message=error message sample\n");
    }
}

void testInsereNo() {
    No* nos;
    int num;
    No* result = insereNo(nos, num);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testInsereNo (metodos_main_test) message=error message sample\n");
    }
}

void testFillList() {
    fillList();
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testFillList (metodos_main_test) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% metodos_main_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testBuscaLiga (metodos_main_test)\n");
    testBuscaLiga();
    printf("%%TEST_FINISHED%% time=0 testBuscaLiga (metodos_main_test)\n");

    printf("%%TEST_STARTED%%  testInsereNo (metodos_main_test)\n");
    testInsereNo();
    printf("%%TEST_FINISHED%% time=0 testInsereNo (metodos_main_test)\n");

    printf("%%TEST_STARTED%%  testFillList (metodos_main_test)\n");
    testFillList();
    printf("%%TEST_FINISHED%% time=0 testFillList (metodos_main_test)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
