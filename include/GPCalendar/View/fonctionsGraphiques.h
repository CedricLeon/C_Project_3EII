/*!
* \file fonctionsGraphiques.h
* \brief Provides basic unit testing functions declaration
*/

#ifndef FONCTIONSGRAPHIQUES_H_INC
#define FONCTIONSGRAPHIQUES_H_INC

#include "GPCalendar/View/callbacks.h"
#include <gtk/gtk.h>
#include <stdlib.h>

int create_window(int argc, char *argv[]);
//void boutonRDV(GtkWidget *button, GtkGrid* grid, gchar* nomRendezVous, gint left, gint top,gint width,gint height);
void boutonRDV(GtkWidget *wid, GtkGrid grid);
void parcoursJour(Jour j);
void creerBoutonRDV(GtkWidget * bouton, RendezVous * rdv);

void fenetreRecherchePatient(GtkWidget * widget, gpointer data);
void fenetreCreerRDV(GtkWidget * widget, gpointer data);
void fenetreCreerPatient(GtkWidget * widget, gpointer data);
#endif

