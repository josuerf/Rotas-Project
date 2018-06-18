/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newsimpletest.c
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 11:05
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/*
 * Simple C Test Suite
 */

void testFillList() {
    fillList();
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testFillList (newsimpletest) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% newsimpletest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testFillList (newsimpletest)\n");
    testFillList();
    printf("%%TEST_FINISHED%% time=0 testFillList (newsimpletest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
