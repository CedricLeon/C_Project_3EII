//Header Files du Projet
#include "medecin.h"
#include "patient.h"
#include "date.h"
#include "calendrier.h"
#include "ordonnance.h"
#include "dossier_medical.h"
#include "rendezvous.h"
#include "calendrier.h"

//Librairies standards de C
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){

     //L'appli se lancera d'ici, je vais donc commenter ce qui devrait chrnologiquement se lancer

    /***********************************Lancement de GTK / Affichage du menu d'accueil*********************************/

    /**
     * Je connais pas GTK+ ...
     */

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
