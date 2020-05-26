/*!
* \file fonctionsGraphiques.h
* \brief Provides basic unit testing functions declaration
*/

#ifndef FONCTIONSGRAPHIQUES_H_INC
#define FONCTIONSGRAPHIQUES_H_INC

#include "GPCalendar/View/callbacks.h"
#include <gtk/gtk.h>
#include <stdlib.h>

void fenetreOuverture(GtkWidget * widget, gpointer data);
void fenetreNouveauProjet(GtkWidget * widget, gpointer data);
int create_window(int argc, char *argv[]);
void parcoursJour(Jour j);
void creerBoutonRDV(GtkWidget * bouton, RendezVous * rdv);

void fenetreRecherchePatient(GtkWidget * widget, gpointer data);
void fenetreCreerRDV(GtkWidget * widget, gpointer data);
void fenetreCreerPatient(GtkWidget * widget, gpointer data);
void fenetreSauvegarde(GtkWidget * widget, gpointer data);

#endif

