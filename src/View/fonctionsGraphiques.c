#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/View/callbacks.h"
#include "GPCalendar/Model/patient.h"
#include <gtk/gtk.h>
#include <stdlib.h>

#define LARGEUR_COLONNE 266
#define HAUTEUR_PREMIERE_LIGNE 50


/**
 * fenetreOuverture : fenetre permettant à l'utilisateur de choisir entre l'ouverture et la création d'un projet
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreOuverture(GtkWidget * widget, gpointer data)
{

    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,50);

    GtkWidget * labelHaut = gtk_label_new("\nBienvenue dans GPCalendar, souhaitez vous travailler avec un projet déjà existant ou souhaitez vous en créer un nouveau ?\n Cliquez sur new pour créer un nouveau projet ou entrez directement le chemin absolu du fichier JSON correspondant à un projet précédemment sauvegardé.\n");
    GtkWidget * vide1 = gtk_label_new("                                                                                         ");
    GtkWidget * vide2 = gtk_label_new("                                                                                                                            ");
    GtkWidget * chemin = gtk_entry_new();
    GtkWidget * valider = gtk_button_new_with_label("VALIDER");
    GtkWidget * newButton = gtk_button_new_with_label("new");


    /* Paramètres graphiques des widgets */
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Ouverture du Projet");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_widget_set_hexpand(labelHaut, TRUE);
    gtk_widget_set_halign(labelHaut, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(labelHaut), GTK_JUSTIFY_CENTER);
    gtk_widget_set_hexpand(valider, TRUE);
    gtk_widget_set_halign(valider, GTK_ALIGN_CENTER);


    /* Ajout à la fenêtre */
    gtk_container_add (GTK_CONTAINER (window), box0);
    gtk_container_add (GTK_CONTAINER (box0), box1);
    gtk_container_add (GTK_CONTAINER (box0), box2);
    gtk_container_add (GTK_CONTAINER (box0), box3);
    gtk_container_add (GTK_CONTAINER (box1), labelHaut);
    gtk_container_add (GTK_CONTAINER (box2), vide1);
    gtk_container_add (GTK_CONTAINER (box2), newButton);
    gtk_container_add (GTK_CONTAINER (box2), vide2);
    gtk_container_add (GTK_CONTAINER (box2), chemin);
    gtk_container_add (GTK_CONTAINER (box3), valider );

    gtk_widget_show_all(window);

    /* Recuperation des donnees */

    struct RechercheProjet * rechercheProj;
    rechercheProj = (struct RechercheProjet*)malloc(sizeof(struct RechercheProjet));

    rechercheProj->chemin=chemin;
    rechercheProj->window=window;

    /* callbacks */
    g_signal_connect(G_OBJECT(newButton), "clicked", G_CALLBACK(cb_newProject), window);
    g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(cb_rechercheProjet), rechercheProj );
}

/**
 * fenetreSauvegarde : fenetre permettant à l'utilisateur de choisir s'il veut sauvegarder ou non son projet et sous quel nom à la fermeture du programme
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreSauvegarde(GtkWidget * widget, gpointer data)
{

    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,50);

    GtkWidget * labelHaut = gtk_label_new("\nAvant de partir, souhaitez-vous enregistrer votre projet ? Si oui, entrez directement le chemin absolu avec le nom du fichier de sauvegarde JSON que vous souhaitez créer.\nEt si vous ne souhaitez pas sauvegarder votre projet cliquez sur \"supprimer\".\n");
    GtkWidget * vide1 = gtk_label_new("                                                                                         ");
    GtkWidget * vide2 = gtk_label_new("                                                                                                                            ");
    GtkWidget * chemin = gtk_entry_new();
    GtkWidget * valider = gtk_button_new_with_label("VALIDER");
    GtkWidget * newButton = gtk_button_new_with_label("Supprimer");


    /* Paramètres graphiques des widgets */
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Fermeture du projet");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_widget_set_hexpand(labelHaut, TRUE);
    gtk_widget_set_halign(labelHaut, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(labelHaut), GTK_JUSTIFY_CENTER);
    gtk_widget_set_hexpand(valider, TRUE);
    gtk_widget_set_halign(valider, GTK_ALIGN_CENTER);


    /* Ajout à la fenêtre */
    gtk_container_add (GTK_CONTAINER (window), box0);
    gtk_container_add (GTK_CONTAINER (box0), box1);
    gtk_container_add (GTK_CONTAINER (box0), box2);
    gtk_container_add (GTK_CONTAINER (box0), box3);
    gtk_container_add (GTK_CONTAINER (box1), labelHaut);
    gtk_container_add (GTK_CONTAINER (box2), vide1);
    gtk_container_add (GTK_CONTAINER (box2), newButton);
    gtk_container_add (GTK_CONTAINER (box2), vide2);
    gtk_container_add (GTK_CONTAINER (box2), chemin);
    gtk_container_add (GTK_CONTAINER (box3), valider);

    gtk_widget_show_all(window);

    /* Recuperation des donnees */
    struct RechercheProjet * finProj;
    finProj = (struct RechercheProjet*)malloc(sizeof(struct RechercheProjet));
    finProj->project = ((struct DateCalendrier *)data)->projet;
    finProj->window=window;
    finProj->chemin=chemin;


    /* callbacks */
    g_signal_connect(G_OBJECT(newButton), "clicked", G_CALLBACK(cb_non_sauvegarde), finProj);
    g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(cb_sauvegarde), finProj);
}
/**
 * fenetreNouveauProjet : fenêtre permettant à l'utilisateur de créer un nouveau projet
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreNouveauProjet(GtkWidget * widget, gpointer data){

    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

    GtkWidget * label_titre = gtk_label_new("\tCréation d'un nouveau projet :");
    GtkWidget * label_nom = gtk_label_new("\tNom du nouveau projet :\t\t");

    GtkWidget * nom = gtk_entry_new();
    GtkWidget * ok = gtk_button_new_with_label("OK");

    /*paramètres graphiques des widgets */
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Nouveau Projet");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 300);
    gtk_widget_set_hexpand(ok, TRUE);
    gtk_widget_set_halign(ok, GTK_ALIGN_CENTER);


    /*ajout à la fenêtre*/

    gtk_container_add(GTK_CONTAINER(window), box0);
    gtk_container_add(GTK_CONTAINER(box0), box1);
    gtk_container_add(GTK_CONTAINER(box0), box2);
    gtk_container_add(GTK_CONTAINER(box0), box3);
    gtk_container_add(GTK_CONTAINER(box1), label_titre);
    gtk_container_add(GTK_CONTAINER(box2), label_nom);
    gtk_container_add(GTK_CONTAINER(box2), nom);
    gtk_container_add(GTK_CONTAINER(box3), ok);


    /*Récupération des données*/
    struct RechercheProjet * rechercheProj;
    rechercheProj = (struct RechercheProjet*)malloc(sizeof(struct RechercheProjet));
    rechercheProj->nom=nom;
    rechercheProj->window=window;


    g_signal_connect(G_OBJECT(ok), "clicked", G_CALLBACK(cb_creerProjet), (struct rechercheProjet *)rechercheProj);

    gtk_widget_show_all(window);

}


/**
 * fenetreRecherchePatient : fenêtre permettant à l'utilisateur de saisir le patient à rechercher parmi ceux consultés par le médecin sélectionné
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreRecherchePatient(GtkWidget * widget, gpointer data)
{

    /* Récupération des entrées recherche*/
    Project_GPCalendar * projet = data;

    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * labelMedecin = gtk_label_new("Médecin : ");
    GtkWidget * choixMedecin = gtk_combo_box_text_new();
    GtkWidget * labelPatient = gtk_label_new("Entrer le numéro de sécurité sociale du patient : ");
    GtkWidget * saisiePatient = gtk_entry_new ();
    GtkWidget * boutonRecherche = gtk_button_new_with_label("Rechercher");

    /* Paramètres graphiques des widgets */
    gtk_entry_set_max_length(GTK_ENTRY(saisiePatient), 13);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Recherche du patient");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 400);



    /* Affichage des médecins */
    char* nomMedecin;
    char* numRPPS;
    for (ListMedecin_setOnFirst(projet->workingMedecins); !ListMedecin_isOutOfList(projet->workingMedecins); ListMedecin_setOnNext(projet->workingMedecins)) {
        nomMedecin = (char*) malloc(30);
        numRPPS = (char*) malloc(15);
        getNomMedecin(nomMedecin, ListMedecin_getCurrent(projet->workingMedecins));
        strcpy(numRPPS,getNumeroRPSMedecin(ListMedecin_getCurrent(projet->workingMedecins)));
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMedecin), numRPPS, nomMedecin);
        free((void*)nomMedecin);
        free((void*)numRPPS);
    }


    /* Ajout à la fenetre */
    gtk_container_add (GTK_CONTAINER (window), box0);
    gtk_container_add (GTK_CONTAINER (box0), box1);
    gtk_container_add (GTK_CONTAINER (box1), labelMedecin);
    gtk_container_add (GTK_CONTAINER (box1), choixMedecin);
    gtk_container_add (GTK_CONTAINER (box0), box2);
    gtk_container_add (GTK_CONTAINER (box2), labelPatient);
    gtk_container_add (GTK_CONTAINER (box2), saisiePatient);
    gtk_container_add (GTK_CONTAINER (box0), box3);
    gtk_container_add (GTK_CONTAINER (box3), boutonRecherche);

    /*récupération données passées dans la fenêtre*/

    struct RecherchePatient * donnees;
    donnees = (struct RecherchePatient*)malloc(sizeof(struct RecherchePatient));
    ((struct RecherchePatient *)donnees)->EnumSecu = saisiePatient;
    ((struct RecherchePatient *)donnees)->med = choixMedecin;
    ((struct RecherchePatient *)donnees)->window = window;
    ((struct RecherchePatient *)donnees)->projet = data;

    g_signal_connect(G_OBJECT(boutonRecherche), "clicked", G_CALLBACK(cb_recherchePatient), donnees);

    gtk_widget_show_all(window);


}

/**
 * fenetreCreerRDV : fenêtre permettant à l'utilisateur de saisir les données du RDV à créer
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreCreerRDV(GtkWidget * widget, gpointer data){

    int i =0;

    /* Récupération données */
    Patient * p = malloc(sizeof(Patient));
    p=((struct Data *)data)->patient;

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
    GtkWidget * box9 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    GtkWidget * box10 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * box11 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget * labelHaut = gtk_label_new("Patient sélectionné dans la base de données\n");
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
    GtkWidget * choixMinutes = gtk_combo_box_text_new();
    GtkWidget * choixDuree = gtk_combo_box_text_new();
    GtkWidget * labelHeure = gtk_label_new("\t Choix de l'heure : ");
    GtkWidget * labelMinutes = gtk_label_new("    min : ");
    GtkWidget * labelDuree = gtk_label_new("\t\t Durée du RDV : ");
    GtkWidget * labelDuree2 = gtk_label_new("minutes");
    GtkWidget * labelMotif = gtk_label_new("\t Motif du RDV : ");
    GtkWidget * saisirMotif = gtk_entry_new();
    GtkWidget * valider = gtk_button_new_with_label("VALIDER");
    GtkWidget * saisirLieu = gtk_entry_new();
    GtkWidget * labelLieu = gtk_label_new("\t Lieu : ");

    char * tmp = malloc(100);
    getNomPatient(tmp,p);
    GtkWidget * nom = gtk_label_new(p->nom);
    GtkWidget * prenom = gtk_label_new( p->prenom);
    GtkWidget * mail = gtk_label_new(p->adresse_mail);
    GtkWidget * tel = gtk_label_new(p->numero_telephone);
    GtkWidget * secu = gtk_label_new(p->numero_secu_social);
    getDateNaissancePatient(tmp,p);
    GtkWidget * date = gtk_label_new(tmp);
    free(tmp);


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
    gtk_widget_set_hexpand(valider, TRUE);
    gtk_widget_set_halign(valider, GTK_ALIGN_CENTER);



    /* Listes déroulantes */
        /* Liste jours */
    char j[3];
    for(i=1; i<32; i++){
        sprintf(j,"%d",i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixJour),j,j);
    }

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
    char a[5];
    for(i=2020; i<2040; i++){
        sprintf(a,"%d",i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixAnnee),a,a);
    }


        /* Liste Heures */
    char h[3];
    for(i=8; i<20; i++){
        sprintf(h,"%d",i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixHeure),h,h);
    }

        /* Liste Minutes */
    char m[3];
    for(i=0; i<=60; i=i+5){
        sprintf(m,"%d",i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixMinutes),m,m);
    }

        /* Liste Durées */
    char d[3];
    for(i=5; i<=90; i=i+5){
        sprintf(d,"%d",i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixDuree),d,d);
    }

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
    gtk_container_add (GTK_CONTAINER (box2), nom);
    gtk_container_add (GTK_CONTAINER (box3), labelPrenom);
    gtk_container_add (GTK_CONTAINER (box3), prenom);
    gtk_container_add (GTK_CONTAINER (box4), labelDdN);
    gtk_container_add (GTK_CONTAINER (box4), date);
    gtk_container_add (GTK_CONTAINER (box5), labelNumSS);
    gtk_container_add (GTK_CONTAINER (box5), secu);
    gtk_container_add (GTK_CONTAINER (box6), ligne);
    gtk_container_add (GTK_CONTAINER (box7), labelRDV);
    gtk_container_add (GTK_CONTAINER (box8), labelDate);
    gtk_container_add (GTK_CONTAINER (box8), choixJour);
    gtk_container_add (GTK_CONTAINER (box8), choixMois);
    gtk_container_add (GTK_CONTAINER (box8), choixAnnee);
    gtk_container_add (GTK_CONTAINER (box9), labelHeure);
    gtk_container_add (GTK_CONTAINER (box9), choixHeure);
    gtk_container_add (GTK_CONTAINER (box9), labelMinutes);
    gtk_container_add (GTK_CONTAINER (box9), choixMinutes);
    gtk_container_add (GTK_CONTAINER (box9), labelDuree);
    gtk_container_add (GTK_CONTAINER (box9), choixDuree);
    gtk_container_add (GTK_CONTAINER (box9), labelDuree2);
    gtk_container_add (GTK_CONTAINER (box10), labelMotif);
    gtk_container_add (GTK_CONTAINER (box10), saisirMotif);
    gtk_container_add (GTK_CONTAINER (box11), valider);
    gtk_container_add (GTK_CONTAINER (box10), labelLieu);
    gtk_container_add (GTK_CONTAINER (box10), saisirLieu);


    gtk_widget_show_all(window);

    /* Recuperation des donnees */

    struct DataRDV * datardv;
    datardv = (struct DataRDV*)malloc(sizeof(struct DataRDV));

    datardv->jour=choixJour;
    datardv->mois=choixMois;
    datardv->annee=choixAnnee;
    datardv->heure=choixHeure;
    datardv->minutes=choixMinutes;
    datardv->duree=choixDuree;
    datardv->motif=saisirMotif;
    datardv->p=data;
    datardv->lieu=saisirLieu;
    datardv->window=window;
    datardv->p=(((struct Data*)data)->patient);
    datardv->m=(((struct Data*)data)->medecin);
    datardv->projet=(((struct Data *)data)->projet);

    /* callbacks */

     g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(cb_creationRDV), datardv);

}



/**
 * fenetreCreerMedecin : fenêtre permettant à l'utilisateur de saisir les coordonnées du médecin à créer
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreCreerMedecin(GtkWidget * widget, gpointer data){

    int i;


    /* Widgets */
        GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box7 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box8 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * labelHaut = gtk_label_new("Entrez les informations du médecin");
    GtkWidget * labelNom = gtk_label_new("\tNom d'usage : ");
    GtkWidget * labelPrenom = gtk_label_new("\tPrénom : ");
    GtkWidget * labelNumRPPS = gtk_label_new("\tNuméro RPPS : ");
    GtkWidget * labelMail = gtk_label_new("\tAdresse e-mail : ");
    GtkWidget * labelTel = gtk_label_new("\tNuméro de téléphone : ");
    char * nom = malloc(50);
    GtkWidget * saisieNom = gtk_entry_new();
    char * prenom = malloc(50);
    GtkWidget * saisiePrenom = gtk_entry_new();
    char * numSecu = malloc(14);
    GtkWidget * saisieNumRPPS = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(saisieNumRPPS), 11);
    char * mail = malloc(50);
    GtkWidget * saisieMail = gtk_entry_new();
    char * numTel = malloc(11);
    GtkWidget * saisieTel = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(saisieTel), 10);
    GtkWidget * valider = gtk_button_new_with_label("VALIDER");


    /* Paramètres graphiques des widgets */
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Création d'un médecin");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_widget_set_hexpand(labelHaut, TRUE);
    gtk_widget_set_halign(labelHaut, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(labelHaut), GTK_JUSTIFY_CENTER);
    gtk_widget_set_hexpand(valider, TRUE);
    gtk_widget_set_halign(valider, GTK_ALIGN_CENTER);

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
    gtk_container_add (GTK_CONTAINER (box1), labelHaut);
    gtk_container_add (GTK_CONTAINER (box2), labelNom);
    gtk_container_add (GTK_CONTAINER (box3), labelPrenom);
    gtk_container_add (GTK_CONTAINER (box4), labelNumRPPS);
    gtk_container_add (GTK_CONTAINER (box5), labelMail);
    gtk_container_add (GTK_CONTAINER (box6), labelTel);
    gtk_container_add (GTK_CONTAINER (box2), saisieNom);
    gtk_container_add (GTK_CONTAINER (box3), saisiePrenom);
    gtk_container_add (GTK_CONTAINER (box4), saisieNumRPPS);
    gtk_container_add (GTK_CONTAINER (box5), saisieMail);
    gtk_container_add (GTK_CONTAINER (box6), saisieTel);
    gtk_container_add (GTK_CONTAINER (box7), valider);

    gtk_widget_show_all(window);

    /* Récupération des entrées patient */
   struct DataMedecin * donnees;
   donnees = (struct DataMedecin*)malloc(sizeof (struct DataMedecin));

   donnees->Enom =saisieNom;
   donnees->Eprenom=saisiePrenom;
   donnees->EnumRPPS=saisieNumRPPS;
   donnees->EnumTel=saisieTel;
   donnees->Email=saisieMail;
   donnees->window=window;
   donnees->projet =(struct RecherchePatient *)data;

    /* callbacks */

    g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(cb_creationMedecin), donnees);
}



/**
 * fenetreCreerPatient : fenêtre permettant à l'utilisateur de saisir les coordonnées du patient à créer
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void fenetreCreerPatient(GtkWidget * widget, gpointer data){

    int i;

    /* Widgets */
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget * box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box7 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * box8 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    GtkWidget * labelHaut = gtk_label_new("Entrez les informations du patient");
    GtkWidget * labelNom = gtk_label_new("\tNom d'usage : ");
    GtkWidget * labelPrenom = gtk_label_new("\tPrénom : ");
    GtkWidget * labelDdN = gtk_label_new("\tDate de naissance : ");
    GtkWidget * labelNumSS = gtk_label_new("\tNuméro de Sécurité Sociale : ");
    GtkWidget * labelMail = gtk_label_new("\tAdresse e-mail : ");
    GtkWidget * labelTel = gtk_label_new("\tNuméro de téléphone : ");
    char * nom = malloc(50);
    GtkWidget * saisieNom = gtk_entry_new();
    char * prenom = malloc(50);
    GtkWidget * saisiePrenom = gtk_entry_new();
    char * numSecu = malloc(14);
    GtkWidget * saisieNumSecu = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(saisieNumSecu), 13);
    char * mail = malloc(50);
    GtkWidget * saisieMail = gtk_entry_new();
    char * numTel = malloc(11);
    GtkWidget * saisieTel = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(saisieTel), 10);
    GtkWidget * choixJour = gtk_combo_box_text_new();
    GtkWidget * choixMois = gtk_combo_box_text_new();
    GtkWidget * choixAnnee = gtk_combo_box_text_new();
    GtkWidget * labelBarre1 = gtk_label_new("/");
    GtkWidget * labelBarre2 = gtk_label_new("/");
    GtkWidget * valider = gtk_button_new_with_label("VALIDER");



    /* Listes déroulantes */
        /* Liste jours */
    char j[3];
    for(i=1; i<32; i++){
        sprintf
        (j,"%d",i);
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(choixJour),j,j);
    }


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
    char a[5];
    for(i=1900; i<2021; i++){
        sprintf(a,"%d",i);
        gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(choixAnnee),a,a);
    }


    /* Paramètres graphiques des widgets */
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Création d'un patient");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_widget_set_hexpand(labelHaut, TRUE);
    gtk_widget_set_halign(labelHaut, GTK_ALIGN_CENTER);
    gtk_label_set_justify(GTK_LABEL(labelHaut), GTK_JUSTIFY_CENTER);
    gtk_widget_set_hexpand(valider, TRUE);
    gtk_widget_set_halign(valider, GTK_ALIGN_CENTER);

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
    gtk_container_add (GTK_CONTAINER (box1), labelHaut);
    gtk_container_add (GTK_CONTAINER (box2), labelNom);
    gtk_container_add (GTK_CONTAINER (box3), labelPrenom);
    gtk_container_add (GTK_CONTAINER (box4), labelDdN);
    gtk_container_add (GTK_CONTAINER (box5), labelNumSS);
    gtk_container_add (GTK_CONTAINER (box6), labelMail);
    gtk_container_add (GTK_CONTAINER (box7), labelTel);
    gtk_container_add (GTK_CONTAINER (box2), saisieNom);
    gtk_container_add (GTK_CONTAINER (box3), saisiePrenom);
    gtk_container_add (GTK_CONTAINER (box5), saisieNumSecu);
    gtk_container_add (GTK_CONTAINER (box6), saisieMail);
    gtk_container_add (GTK_CONTAINER (box7), saisieTel);
    gtk_container_add (GTK_CONTAINER (box4), choixJour);
    gtk_container_add (GTK_CONTAINER (box4), labelBarre1);
    gtk_container_add (GTK_CONTAINER (box4), choixMois);
    gtk_container_add (GTK_CONTAINER (box4), labelBarre2);
    gtk_container_add (GTK_CONTAINER (box4), choixAnnee);
    gtk_container_add (GTK_CONTAINER (box8), valider);

    gtk_widget_show_all(window);

    /* Récupération des entrées patient */
   struct Data *dataPatient;
   dataPatient = (struct Data*)malloc(sizeof (struct Data));

   dataPatient->Enom =saisieNom;
   dataPatient->Eprenom=saisiePrenom;
   dataPatient->EnumSecu=saisieNumSecu;
   dataPatient->EnumTel=saisieTel;
   dataPatient->Email=saisieMail;
   dataPatient->jour=choixJour;
   dataPatient->mois=choixMois;
   dataPatient->annee=choixAnnee;
   dataPatient->window=window;
   dataPatient->projet =((struct RecherchePatient *)data)->projet;
   dataPatient->medecin =((struct RecherchePatient *)data)->medecin;

    /* callbacks */

    g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(cb_creationPatient), dataPatient);
}
