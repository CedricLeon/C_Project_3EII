#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H

#include "GPCalendar/Model/ordonnance.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct DossierMedical{
    ListMedecin* medecins_consultes; //Liste des m�decins consult�s pour ce dossier
    ListOrdonnance* ordonnances;
    /**
     * Pas d'antécédents pour l'instant (pas implémenté dans dossier médical.c et dans Json.c
     */
   // char antecedents[]; //CR des pr�c�dents passage � l'hopital pour les prochaines versions
}DossierMedical;

DossierMedical * CreerDossierMedical(Patient * patient);
void FreeDossierMedical(DossierMedical * d);
void AccesDossier(Patient * p);    //Print toutes les infos je suppose

//void SetPatientDossier(DossierMedical * dm, Patient * patient); -> plus besoin comme le dossier fait partie d'un patient ?
// int AddMedecinDossierMedical(DossierMedical * dm, Medecin * medecin); ->plus besoin du coup fonction déjà présente dans patient.c


int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance);
int AddAntecedentDossierMedical(DossierMedical * dm, char antecedent);

//void TransfertDossier(DossierMedical dm, ???); //J'avoue que je vois pas trop

#endif
