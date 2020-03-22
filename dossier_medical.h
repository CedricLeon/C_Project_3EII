#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H

#include "ordonnance.h"

typedef struct DossierMedical DossierMedical;
struct DossierMedical{
    Patient * patient;
    Medecin * medecins; //Liste des m�decins consult�s pour ce dossier
    //static int nb_medecins;    // Peut �tre utile
    Ordonnance * ordonnances; //En vrai on devrait aussi faire une structure ordonnance, c'est plus clean
    //static int nb_ordonnaces;    // idem
    DossierMedical * antecedents; //Liste des pr�c�dents passage � l'hopital
    //static int nb_antecedents;    // idem�
};

DossierMedical * CreerDossier(Patient * patient);   //On y fera les 3 mallocs
void FreeDossier();                     //Il y aura donc 3 free je pense

void AccesDossier(DossierMedical * d);    //Print toutes les infos je suppose
void SetPatientDossier(DossierMedical * dm, Patient * patient);
int AddMedecinDossierMedical(DossierMedical * dm, Medecin * medecin);
int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance);
int AddAntecedentDossierMedical(DossierMedical * dm, DossierMedical * antecedent);

//void TransfertDossier(DossierMedical dm, ???); //J'avoue que je vois pas trop

#endif
