#ifndef CALENDRIER_H
#define CALENDRIER_H

#include "rendezvous.h"

typedef struct{                 //Au niveau des dates / jour / mois etc ... je sais pas trop comment g�rer �a
    RendezVous * rendez_vous;   //Un tableau de rendez-vous pour l'instant
    int taille;                 //Nombre de rendez-vous actuels dans le calendrier
}Calendrier;

Calendrier * InitCalendrier(Calendrier * c); //Cr�e un calendrier vide

#endif
