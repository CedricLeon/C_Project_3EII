#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/View/callbacks.h"
#include <gtk/gtk.h>
#include <stdlib.h>

void cb_create_entry(GtkWidget *p_widget, gpointer user_data){
    GtkWidget *p_window;
    GtkWidget *p_v_box;
    /*GtkWidget *p_entry;*/

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Informations patient");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 320, 200);

    p_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

   /* p_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(p_v_box), p_entry, TRUE, FALSE, 0);*/
    gtk_widget_show_all(p_window);
}

void cb_create_entry1(GtkWidget *p_widget, gpointer user_data){
    GtkWidget *p_window;
    GtkWidget *p_v_box;
    /*GtkWidget *p_entry;*/

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Liste de rendez-vous de la journée");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 320, 200);

    p_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
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



void enter_callback( GtkWidget *widget, GtkWidget *entry)
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}



void cb_creationPatient(GtkWidget * widget, gpointer data){

    char* nom ="";
    char* prenom="";
    char* mail="";
    char* tel="";
    char* secu="";
    int jour, mois, annee;

    /* Recuperation du texte contenu dans le GtkEntry */
    nom = gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->Enom));
    prenom = gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->Eprenom));
    mail = gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->Email));
    tel = gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->EnumTel));
    secu = gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->EnumSecu));
    jour = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->jour)));
    mois = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->mois)));
    annee = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->annee)));

    Patient *p = CreerPatient(nom, prenom,jour,mois,annee, mail, tel, secu);         //Il faudra exporter la donnée au format Json
    printf("\n\n\n");
    char* infos = (char*) malloc(1000);
    printPatient(infos, p); //  pour tester par affichage sur console
    printf("%s", infos);
    free((void*) infos);
    fenetreCreerRDV(widget,data);

}


void cb_creationRDV(GtkWidget * widget, gpointer datardv){


    int jour = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)datardv)->jour)));
    int mois = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)datardv)->mois)));
    int annee = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)datardv)->annee)));
    double hDebut = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)datardv)->heure)))+(atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)datardv)->minutes)))/60);
    int duree = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)datardv)->duree)));
    char * motif = gtk_entry_get_text(GTK_ENTRY(((struct DataRDV*)datardv)->motif));
    //Patient *p
    //CreerRendezVous();

}
