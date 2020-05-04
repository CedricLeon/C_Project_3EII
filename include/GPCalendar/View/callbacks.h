/*!
* \file callbacks.h
* \brief Provides basic unit testing functions declaration
*/

#ifndef CALLBACKS_H_INC
#define CALLBACKS_H_INC

#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/calendrier.h"
#include <gtk/gtk.h>
#include <stdlib.h>

   typedef struct Data{
   GtkWidget * Enom;
   GtkWidget * Eprenom;
   GtkWidget * EnumSecu;
   GtkWidget * EnumTel;
   GtkWidget * Email;
   GtkWidget * jour;
   GtkWidget * mois;
   GtkWidget * annee;
   Patient * p;
   }dataPatient;

   typedef struct DataRDV{
    GtkWidget * jour;
    GtkWidget * mois;
    GtkWidget * annee;
    GtkWidget * heure;
    GtkWidget * minutes;
    GtkWidget * duree;
    GtkWidget * motif;
    RendezVous *r;
    dataPatient * p;
    //Medecin *m;
   }dataRdv;

void cb_create_entry(GtkWidget *p_widget, gpointer user_data);
void cb_create_entry1(GtkWidget *p_widget, gpointer user_data);
void cb_clicSurPlus(GtkWidget * widget, gpointer data);
void cb_recherchePatient(GtkWidget * widget, gpointer data);
void cb_creationPatient(GtkWidget * widget, gpointer data);
void cb_creationRDV(GtkWidget * widget, gpointer data);
void enter_callback( GtkWidget *widget, GtkWidget *entry);


#endif
