//Header Files du Projet
//Model
#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/calendrier.h"
#include "GPCalendar/Model/ordonnance.h"
#include "GPCalendar/Model/dossier_medical.h"
#include "GPCalendar/Model/rendezvous.h"
#include "GPCalendar/Model/calendrier.h"
//View
#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/View/callbacks.h"
#include "GPCalendar/View/time_GPCalendar.h"

#include <gtk/gtk.h>

//Librairies standards de C
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

     //L'appli se lancera d'ici, je vais donc commenter ce qui devrait chrnologiquement se lancer

    /***********************************Lancement de GTK / Affichage du menu d'accueil*********************************/
    GtkWidget* widget;
    gpointer data;
    gtk_init (&argc, &argv);


    // char* result=(char*)malloc(10*sizeof(char));
    // char* result1=(char*)malloc(4*sizeof(char));

    // JourCourantNom(result);
    // printf("It is the day %s\n",result);

    // JourCourantDate(result1);
    // printf("It is the day %s\n",result1);
    // printf("Day in int %d\n",atoi(result1));

    // free((void*)result);

    fenetreOuverture(widget, data);

    //create_window(argc, argv);

    //create_calendar(widget, data);
    gtk_main ();
    return EXIT_SUCCESS;
    /******************************Si voulu par l'utilisateur : Chargement des fichiers ISC****************************/

    /**
     * 1 - Récupération des listes de patients et de mèdecins existants (On les appellera un truc comme RegisteredPatient/Medecin)
     *
     * 2 - Récupération du ou des Calendriers (dépendra de la version, pour la V0 c'est du : le calendrier de l'hopital)
     *
     * 3 - Un petit print dans GTK et la console pour voir le fichier ISC qu'on à load
     */

    /*********************************************Fonctionnement de l'appli********************************************/

    /**
     * Inscription de nouveaux patients / mèdecins
     * Création de nouveaux rdv / ordonnances et maj du calendrier
     * Lecture d'infos persos de Patient / Medecins
     * etc ...
     */

    /********************************************Fermeture de l'appli via GTK******************************************/

    /**
     * 1 - Demande à l'utilisateur si il veut save ses données dans un fichier ISC, si oui bah le faire
     *
     * 2 - Après avoir save, free tout les objets load en mémoire après l'ouverture et l'utilisation de l'appli
     *
     * 3 - Fermer GTK
     */
}
