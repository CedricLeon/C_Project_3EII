#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"
#include "patient.h"

#define LARGEUR_COLONNE 274
#define HAUTEUR_PREMIERE_LIGNE 50




void boutonRDV(GtkWidget *wid, GtkGrid grid)
{
    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (GTK_WINDOW (wid), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}


int create_window(int argc, char *argv[])
{

    /* Initialisation GTK+ */
    gtk_init (&argc, &argv);

    /* Création de la fenêtre principale */

    GtkWidget *p_window = NULL;
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(p_window), "Calendrier");
    gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_NONE);
    gtk_window_resize_to_geometry(p_window, 1600, 900);
    gtk_widget_realize (p_window);
    g_signal_connect(G_OBJECT(p_window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);


    /* Création des espaces de la fenêtre */
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    GtkWidget * boxLundi = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget * boxMardi = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget * boxMercredi = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget * boxJeudi = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget * boxVendredi = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget * boxSamedi = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget * boxDimanche = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    gtk_container_add (GTK_CONTAINER (p_window), box0);
    gtk_container_add (GTK_CONTAINER (box0), boxLundi);
    gtk_container_add (GTK_CONTAINER (box0), boxMardi);
    gtk_container_add (GTK_CONTAINER (box0), boxMercredi);
    gtk_container_add (GTK_CONTAINER (box0), boxJeudi);
    gtk_container_add (GTK_CONTAINER (box0), boxVendredi);
    gtk_container_add (GTK_CONTAINER (box0), boxSamedi);
    gtk_container_add (GTK_CONTAINER (box0), boxDimanche);


    /*Ajout des jours de la semaine */

    GtkWidget * L_lundi = gtk_label_new("Lundi");
    GtkWidget * L_mardi = gtk_label_new("Mardi");
    GtkWidget * L_mercredi = gtk_label_new("Mercredi");
    GtkWidget * L_jeudi = gtk_label_new("Jeudi");
    GtkWidget * L_vendredi = gtk_label_new("Vendredi");
    GtkWidget * L_samedi = gtk_label_new("Samedi");
    GtkWidget * L_dimanche = gtk_label_new("Dimanche");

    gtk_box_pack_start(GTK_BOX(boxLundi),L_lundi, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxMardi),L_mardi, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxMercredi),L_mercredi, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxJeudi),L_jeudi, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxVendredi),L_vendredi, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxSamedi),L_samedi, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxDimanche),L_dimanche, FALSE, FALSE, 0);

    gtk_widget_set_size_request(L_lundi, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);
    gtk_widget_set_size_request(L_mardi, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);
    gtk_widget_set_size_request(L_mercredi, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);
    gtk_widget_set_size_request(L_jeudi, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);
    gtk_widget_set_size_request(L_vendredi, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);
    gtk_widget_set_size_request(L_samedi, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);
    gtk_widget_set_size_request(L_dimanche, LARGEUR_COLONNE, HAUTEUR_PREMIERE_LIGNE);



    /*Test d'ajout de Rendez-vous*/

    GtkWidget * button1 = gtk_button_new_with_label("rdv1");
    gtk_box_pack_start(GTK_BOX(boxLundi), button1, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(cb_create_entry), NULL);

    GtkWidget * button2 = gtk_button_new_with_label("Rendez-vous n°2");
    gtk_box_pack_start(GTK_BOX(boxJeudi), button2, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(cb_create_entry), NULL);


    gtk_widget_show_all(p_window);
    return EXIT_SUCCESS;
}


/**
 * parcoursJour : Parcourir le jour en paramètre et créer un bouton associé à chaque rendez-vous
 * @param j : le jour (liste de rendez-vous) parcouru
 */

void parcoursJour(Jour j)
{
    /*parcours de la journée */
    for(ListRendezVous_setOnFirst(j); ListRendezVous_isLast(j); ListRendezVous_setOnNext(j))
    {
        /*création bouton */
        GtkWidget * bouton = NULL;
        creerBoutonRDV(bouton, ListRendezVous_getCurrent(j));
        //attache du bouton à la colonne du jour
        //en fonction des nomenclatures colonne/jour et de la date du jour


        /*free bouton */
        free(bouton);
    }


}

/**
 * creerBoutonRDV : associe un bouton du calendrier au patient reçu lors du rendez-vous
 * @param bouton : le bouton affiché
 * @param rdv : le rendez-vous dont on veut associer le patient
 */

void creerBoutonRDV(GtkWidget * bouton, RendezVous * rdv)
{
    char * nom = malloc(50);
    getNomPatient(nom, rdv->patient);
    bouton = gtk_button_new_with_label(nom);
    free(nom);
}

