/*!
* \file fonctionsGraphiques.h
* \brief Provides basic unit testing functions declaration
*/

#ifndef FONCTIONSGRAPHIQUES_H_INC
#define FONCTIONSGRAPHIQUES_H_INC

#include <stdlib.h>
#include <gtk/gtk.h>
#include "callbacks.h"
int create_window(int argc, char *argv[]);
void boutonRDV(GtkWidget *wid, GtkGrid grid);
void parcoursJour(Jour j);
void creerBoutonRDV(GtkWidget * bouton, RendezVous * rdv);

#endif

