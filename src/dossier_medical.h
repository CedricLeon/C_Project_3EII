#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H


//#include "Structures.h"
#include "ordonnance.h"
#include "medecin.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct DossierMedical{
    ListMedecin* medecins_consultes; //Liste des m�decins consult�s pour ce dossier
    ListOrdonnance* ordonnances;
    /**
     * Pas d'antécédents pour l'instant (pas implémenté dans dossier médical.c et dans Json.c
     */
    //char ** antecedents; //CR des pr�c�dents passage � l'hopital pour les prochaines versions
};

DossierMedical * CreerDossierMedical(Patient * patient);
void FreeDossierMedical(DossierMedical * d);

void AccesDossier(DossierMedical * d);    //Print toutes les infos je suppose
void SetPatientDossier(DossierMedical * dm, Patient * patient);
int AddMedecinDossierMedical(DossierMedical * dm, Medecin * medecin);
int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance);
int AddAntecedentDossierMedical(DossierMedical * dm, char * antecedent);

//void TransfertDossier(DossierMedical dm, ???); //J'avoue que je vois pas trop

#endif
