/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   fill_list_test.c
 * Author: Josue
 *
 * Created on 17 de Junho de 2018, 10:38
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Simple C Test Suite
 */

void fillList();

void testFillList() {
    fillList();
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testFillList (fill_list_test) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% fill_list_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testFillList (fill_list_test)\n");
    testFillList();
    printf("%%TEST_FINISHED%% time=0 testFillList (fill_list_test)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
