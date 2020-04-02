#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include "date.h"
#include "medecin.h"
#include "patient.h"

typedef struct{
    Date * date;
    int heure;      // Comment on stocke ça ? 16h30 <=> 16.5 ? ou Alors un attribut heure et un attribut minute ?
    int minute;
    int duree;  //Tout les rendez-vous ne durent pas aussi longtemps
    char * lieu; //Numéro batiment / numero salle ?
    Patient * patient;
    Medecin * medecin;
    char * motif;
}RendezVous;

RendezVous * CreerRendezVous(int an, int mois, int jour, int heure, int minute, int duree, char * lieu, Patient * patient, Medecin * medecin, char * motif);
int AnnulerRendezVous(RendezVous * rdv);
RendezVous * DeplacerRendezVous(RendezVous * rdv, int n_an, int n_mois, int n_jour, int n_heure, int n_minute, int n_duree);

#endif
