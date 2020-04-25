#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H

#include "ordonnance.h"

typedef struct DossierMedical DossierMedical;
struct DossierMedical{
    Patient * patient;
    ListMedecin * medecins; //Liste des m�decins consult�s pour ce dossier
    int nb_medecins;
    ListOrdonnance * ordonnances;
    int nb_ordonnances;
    char * antecedents; //CR des pr�c�dents passage � l'hopital
    int nb_antecedents;    // idem�
};

DossierMedical * CreerDossier(Patient * patient);   //On y fera les 3 mallocs
void FreeDossier(DossierMedical * d);                     //Il y aura donc 3 free je pense

void AccesDossier(DossierMedical * d);    //Print toutes les infos je suppose
void SetPatientDossier(DossierMedical * dm, Patient * patient);
int AddMedecinDossierMedical(DossierMedical * dm, Medecin * medecin);
int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance);
int AddAntecedentDossierMedical(DossierMedical * dm, char * antecedent);

//void TransfertDossier(DossierMedical dm, ???); //J'avoue que je vois pas trop

#endif
