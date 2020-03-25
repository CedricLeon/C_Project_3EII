/*Librairies nécessaire à CMocka*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    const struct CMUnitTest tests_fonctionsBasiques[] = {
            /*list de toutes le sfonctions tests de cmocka à faire tourner*/
            /*Cf P24 du poly Code testing*/
    };

    //return cmocka_run_group_tests(tests_fonctionsBasiques, NULL, NULL);
    return 0;
}


#pragma clang diagnostic pop