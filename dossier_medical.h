#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H

#include "ordonnance.h"

typedef struct{
    Patient * patient;
    Medecin * medecins; //Liste des mèdecins consultés pour ce dossier
    //static int nb_medecins;    // Peut être utile
    Ordonnance * ordonnances; //En vrai on devrait aussi faire une structure ordonnance, c'est plus clean
    //static int nb_ordonnaces;    // idem
    DossierMedical * antecedents; //Liste des précédents passage à l'hopital
    //static int nb_antecedents;    // idem²
}DossierMedical;

DossierMedical * CreerDossier(Patient * patient);   //On y fera les 3 mallocs
void FreeDossier();                     //Il y aura donc 3 free je pense

void AccesDossier(DossierMedical * d);    //Print toutes les infos je suppose
void SetPatientDossier(DossierMedical * dm, Patient * patient);
int AddMedecinDossierMedical(DossierMedical * dm, Medecin * medecin);
int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance);
int AddAntecedentDossierMedical(DossierMedical * dm, DossierMedical * antecedent);

//void TransfertDossier(DossierMedical dm, ???); //J'avoue que je vois pas trop

#endif
