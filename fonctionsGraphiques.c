#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"
#include "patient.h"

#define LARGEUR_COLONNE 266
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
    gtk_window_resize_to_geometry(GTK_WINDOW(p_window), 1600, 900);
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
    GtkWidget * boxSupp = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    gtk_container_add (GTK_CONTAINER (p_window), box0);
    gtk_container_add (GTK_CONTAINER (box0), boxLundi);
    gtk_container_add (GTK_CONTAINER (box0), boxMardi);
    gtk_container_add (GTK_CONTAINER (box0), boxMercredi);
    gtk_container_add (GTK_CONTAINER (box0), boxJeudi);
    gtk_container_add (GTK_CONTAINER (box0), boxVendredi);
    gtk_container_add (GTK_CONTAINER (box0), boxSamedi);
    gtk_container_add (GTK_CONTAINER (box0), boxDimanche);
    gtk_container_add (GTK_CONTAINER (box0), boxSupp);



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



    /* Bouton d'ajout de RDV */

    GtkWidget * plusRDV = gtk_button_new_with_label("+");
    gtk_box_pack_start(GTK_BOX(boxSupp), plusRDV, FALSE, FALSE, 0);
    gtk_widget_set_size_request(plusRDV, HAUTEUR_PREMIERE_LIGNE, HAUTEUR_PREMIERE_LIGNE);

    g_signal_connect(G_OBJECT(plusRDV), "clicked", G_CALLBACK(cb_clicSurPlus), NULL);



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
void fenetreRecherchePatient(GtkWidget * widget, gpointer data)
{

    /*Pour test du transfert de données via g_signal_connect*/

    Medecin * m1 = CreerMedecin("Numéro1", "Docteur", "test@adresseMailM1", "testNumeroTelephoneM1", "NumRPSM1");
    Medecin * m2 = CreerMedecin("Numéro2", "Docteur", "test@adresseMailM2", "testNumeroTelephoneM2", "NumRPSM2");
    Patient * p1 = CreerPatient("NomPatient","PrenomPatient",2000,01,01,"adresseMailPatient","telPatient", "numSecu");
    ListMedecin * l = malloc(sizeof(ListMedecin));
    ListMedecin_init(l);
    newNodeMedecin(m1, &l->sentinel_begin, &l->sentinel_end);
    ListMedecin_setOnFirst(l);
    newNodeMedecin(m2, l->current, &l->sentinel_end);




    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * labelMedecin = gtk_label_new("Médecin : ");
    GtkWidget * choixMedecin = gtk_combo_box_text_new();
    GtkWidget * numeroPatient = gtk_label_new("Entrer le numéro de sécurité sociale du patient : ");
    GtkEntryBuffer * buffer = gtk_entry_buffer_new (NULL, 13);
    GtkWidget * saisiePatient = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(buffer));
    GtkWidget * boutonRecherche = gtk_button_new_with_label("Rechercher");
    const gchar * MedecinSelectionne = NULL;


    gtk_entry_set_max_length(GTK_ENTRY(saisiePatient), 13);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Recherche du patient");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);

    char * tmp = malloc(50);
    getNomMedecin(tmp, m1);
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(choixMedecin), m1->numero_RPS, tmp);   //A implémenter d'après données projet
    getNomMedecin(tmp, m2);
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(choixMedecin), m2->numero_RPS, tmp);
    free(tmp);

    gtk_container_add (GTK_CONTAINER (window), box0);
    gtk_container_add (GTK_CONTAINER (box0), box1);
    gtk_container_add (GTK_CONTAINER (box1), labelMedecin);
    gtk_container_add (GTK_CONTAINER (box1), choixMedecin);
    gtk_container_add (GTK_CONTAINER (box0), box2);
    gtk_container_add (GTK_CONTAINER (box2), numeroPatient);
    gtk_container_add (GTK_CONTAINER (box2), saisiePatient);
    gtk_container_add (GTK_CONTAINER (box0), box3);
    gtk_container_add (GTK_CONTAINER (box3), boutonRecherche);

    MedecinSelectionne = gtk_combo_box_get_active_id(GTK_COMBO_BOX(choixMedecin));

    const char ** association = malloc(26);
    association[0] = (char*)buffer;
    association[1] = MedecinSelectionne;

    g_signal_connect(G_OBJECT(boutonRecherche), "clicked", G_CALLBACK(cb_recherchePatient), p1);

    gtk_widget_show_all(window);
    free(association);

}


void fenetreCreerRDV(GtkWidget * widget, gpointer data){

    int i =0;

    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box7 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box8 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,50);
    GtkWidget * box9 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,40);
    GtkWidget * box10 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box11 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * labelHaut = gtk_label_new("Patient trouvé dans la base de données\n");
    GtkWidget * labelNom = gtk_label_new("\tNom : ");
    GtkWidget * labelPrenom = gtk_label_new("\tPrénom : ");
    GtkWidget * labelDdN = gtk_label_new("\tDate de Naissance : ");
    GtkWidget * labelNumSS = gtk_label_new("\tNuméro de Sécurité Sociale : ");
    GtkWidget * ligne = gtk_label_new("____________________________________\n");
    GtkWidget * labelRDV = gtk_label_new("\tRendez-vous : ");
    GtkWidget * labelDate = gtk_label_new("\t Choix de la date : ");
    GtkWidget * choixJour = gtk_combo_box_text_new();
    GtkWidget * choixMois = gtk_combo_box_text_new();
    GtkWidget * choixAnnee = gtk_combo_box_text_new();
    GtkWidget * choixHeure = gtk_combo_box_text_new();
    GtkWidget * choixDuree = gtk_combo_box_text_new();
    GtkWidget * labelHeure = gtk_label_new("\t Choix de l'heure : ");
    GtkWidget * labelDuree = gtk_label_new("\t Choix de la durée : ");

//    char* nom = malloc(50);
//    getNomPatient(nom, data);
//    GtkWidget * labelNomPatient = gtk_label_new(nom);
//    free(nom);




    /* Paramètres graphiques des widgets */
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Création d'un rendez-vous");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_widget_set_hexpand(labelHaut, TRUE);
    gtk_widget_set_halign(labelHaut, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(labelHaut), GTK_JUSTIFY_CENTER);
    gtk_widget_set_hexpand(ligne, TRUE);
    gtk_widget_set_halign(ligne, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(ligne), GTK_JUSTIFY_CENTER);




    /* Listes déroulantes  A FINIR */
        /* Liste jours */
//    char j[0] = "";
//    for(i=1; i<32; i++){
//        j[0]=(char)i;
//        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixJour),j,j);
//    }

        /* Liste Mois */
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "1","Janvier");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "2","Février");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "3","Mars");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "4","Avril");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "5","Mai");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "6","Juin");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "7","Juillet");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "8","Août");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "9","Septembre");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "10","Octobre");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "11","Novembre");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMois), "12","Décembre");

        /* Liste Années */
        /* Liste Heures */
        /* Liste Durées */



    /* Ajout à la fenêtre */
    gtk_container_add (GTK_CONTAINER (window), box0);
    gtk_container_add (GTK_CONTAINER (box0), box1);
    gtk_container_add (GTK_CONTAINER (box0), box2);
    gtk_container_add (GTK_CONTAINER (box0), box3);
    gtk_container_add (GTK_CONTAINER (box0), box4);
    gtk_container_add (GTK_CONTAINER (box0), box5);
    gtk_container_add (GTK_CONTAINER (box0), box6);
    gtk_container_add (GTK_CONTAINER (box0), box7);
    gtk_container_add (GTK_CONTAINER (box0), box8);
    gtk_container_add (GTK_CONTAINER (box0), box9);
    gtk_container_add (GTK_CONTAINER (box0), box10);
    gtk_container_add (GTK_CONTAINER (box0), box11);
    gtk_container_add (GTK_CONTAINER (box1), labelHaut);
    gtk_container_add (GTK_CONTAINER (box2), labelNom);
    gtk_container_add (GTK_CONTAINER (box3), labelPrenom);
    gtk_container_add (GTK_CONTAINER (box4), labelDdN);
    gtk_container_add (GTK_CONTAINER (box5), labelNumSS);
    gtk_container_add (GTK_CONTAINER (box6), ligne);
    gtk_container_add (GTK_CONTAINER (box7), labelRDV);
    gtk_container_add (GTK_CONTAINER (box8), labelDate);
    gtk_container_add (GTK_CONTAINER (box8), choixJour);
    gtk_container_add (GTK_CONTAINER (box8), choixMois);
    gtk_container_add (GTK_CONTAINER (box8), choixAnnee);
    gtk_container_add (GTK_CONTAINER (box9), labelHeure);
    gtk_container_add (GTK_CONTAINER (box9), choixHeure);
    gtk_container_add (GTK_CONTAINER (box9), labelDuree);
    gtk_container_add (GTK_CONTAINER (box9), choixDuree);


    gtk_widget_show_all(window);


}

void fenetreCreerPatient(){
    //A FAIRE




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
        /*attache du bouton à la colonne du jour */

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

