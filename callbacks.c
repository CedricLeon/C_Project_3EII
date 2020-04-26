#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"


void cb_create_entry(GtkWidget *p_widget, gpointer user_data){
    gtk_button_released(p_widget);
    GtkWidget *p_window;
    GtkWidget *p_v_box;
    /*GtkWidget *p_entry;*/

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Informations patient");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 320, 200);

    p_v_box = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

   /* p_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(p_v_box), p_entry, TRUE, FALSE, 0);*/
    gtk_widget_show_all(p_window);
}

void cb_create_entry1(GtkWidget *p_widget, gpointer user_data){
    gtk_button_released(p_widget);
    GtkWidget *p_window;
    GtkWidget *p_v_box;
    /*GtkWidget *p_entry;*/

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Liste de rendez-vous de la journée");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 320, 200);

    p_v_box = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

   /* p_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(p_v_box), p_entry, TRUE, FALSE, 0);*/
    gtk_widget_show_all(p_window);
}



void cb_clicSurPlus(GtkWidget * widget, gpointer data){
    fenetreRecherchePatient(widget, data);

}

void cb_recherchePatient(GtkWidget * widget, gpointer data){
//    char * numPatient = malloc(14);
//    char * numMedecin = malloc(12);
//    //numPatient = data->                   // A FAIRE EN FONCTION DE L'IMPLEMENTATION DES MEDECINS DU PROJET
//
//    Medecin * m=NULL;
//
//    /* Parcours de la liste des patients de m */
//    for(ListPatient_setOnFirst(m->patients_recus); ListPatient_isLast(m->patients_recus); ListPatient_setOnNext(m->patients_recus)){
//        /* Si patient présent, on ouvre la fenêtre de création d'un RDV */
//        if(strcmp(m->patients_recus->current->patient->numero_secu_social, numPatient)==0){
//            fenetreCreerRDV();
//        }else{
//            fenetreCreerPatient();
//        }
//    }

}


