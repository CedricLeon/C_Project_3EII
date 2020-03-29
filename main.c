#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"


int main (int argc, char *argv[])
{

   create_window(argc, argv);
   gtk_main ();
   return EXIT_SUCCESS;
}
