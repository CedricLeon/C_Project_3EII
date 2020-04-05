#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include "date.h"
#include "medecin.h"
#include "patient.h"

typedef struct{
    Date * date;
    double heure_debut;      //16h30 <=> 16.5
    double heure_fin;
    char * lieu;
    Patient * patient;
    Medecin * medecin;
    char * motif;
}RendezVous;

RendezVous * CreerRendezVous(int an, int mois, int jour, double heure_debut, int duree, char * lieu, Patient * patient, Medecin * medecin, char * motif);
int AnnulerRendezVous(RendezVous * rdv);
RendezVous * DeplacerRendezVous(RendezVous * rdv, int n_an, int n_mois, int n_jour, double n_heure_debut, int n_duree);

#endif
