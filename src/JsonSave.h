#ifndef C_PROJECT_JSONSAVE_H
#define C_PROJECT_JSONSAVE_H

//Header Files du Projet
#include "medecin.h"
#include "patient.h"
#include "date.h"
#include "calendrier.h"
#include "ordonnance.h"
#include "dossier_medical.h"
#include "rendezvous.h"
#include "calendrier.h"

//Librairie nécessaire à cJSON
#include <cJSON.h>

typedef struct
{
    //Liste de Medecins inscrits dans l'hopital
    ListMedecin * workingMedecins;
    //Liste des patients ayant déjà consulté dans cet hopital
    ListPatient * consultingPatient;
    //Calendrier global de l'hopitail (pour la V0)
    Calendrier calendrier;
}Project;
/*
char* jsonSave(Project*)
{
    Project p;
    cJSON* projectJson = cJSON_CreateObject();
    cJSON* listMedecinJson = cJSON_CreateObject();
    cJSON* listPatientJson = cJSON_CreateObject();

    MedecinList_jsonSave(listMedecinJson);
    PatientList_jsonSave(listPatientJson);


    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

    //Cf example README
    cJSON_Delete(projectJson);
    cJSON_Delete(listMedecinJson, p->listMedecin); // ?
    cJSON_Delete(listPatientJson);
    return string;
}
bool jsonLoad(Project*, const char*);

MedecinList_jsonSave(cJSON* object, MedecinList* list);
MedecinList_jsonLoad(cJSON* object);
Medecin_jsonSave(cJSON* object);
Medecin_jsonLoad(cJSON* object);*/

#endif //C_PROJECT_JSONSAVE_H
