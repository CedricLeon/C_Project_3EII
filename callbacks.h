/*!
* \file callbacks.h
* \brief Provides basic unit testing functions declaration
*/

#ifndef CALLBACKS_H_INC
#define CALLBACKS_H_INC

#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsGraphiques.h"
#include "patient.h"
#include "calendrier.h"

void cb_create_entry(GtkWidget *p_widget, gpointer user_data);
void cb_create_entry1(GtkWidget *p_widget, gpointer user_data);
void cb_clicSurPlus(GtkWidget * widget, gpointer data);
void cb_recherchePatient(GtkWidget * widget, gpointer data);
#endif
