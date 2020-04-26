#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"
#include "time.h"


int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);


    /*char* result=(char*)malloc(10*sizeof(char));
    char* result1=(char*)malloc(4*sizeof(char));

    JourCourantNom(result);
    printf("It is the day %s\n",result);

    JourCourantDate(result1);
    printf("It is the day %s\n",result1);
    printf("Day in int %d\n",atoi(result1));

    free((void*)result);
    create_window(argc, argv);*/

   create_calendar ();
   gtk_main ();
   return EXIT_SUCCESS;
}


