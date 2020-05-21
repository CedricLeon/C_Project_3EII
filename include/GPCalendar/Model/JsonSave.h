#ifndef C_PROJECT_JSONSAVE_H
#define C_PROJECT_JSONSAVE_H

//Header Files du Projet
#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/calendrier.h"
#include "GPCalendar/Model/ordonnance.h"
#include "GPCalendar/Model/dossier_medical.h"
#include "GPCalendar/Model/rendezvous.h"
#include "GPCalendar/Model/calendrier.h"

//Librairie nécessaire à cJSON
#include <cJSON.h>

//Librairie Standart
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    //Nom du projet, pas vraiment d'utilité pour l'instant mais c'est pour comment marche cJSON
    char* nom;
    //Liste de Medecins inscrits dans l'hopital
    ListMedecin * workingMedecins;
    //Liste des patients ayant déjà consulté dans cet hopital
    ListPatient * consultingPatient;
    //Calendrier global de l'hopitail (pour la V0)
    Calendrier calendrier;
}Project;

Project * CreerProject(char* nom, ListMedecin * workingMedecins, ListPatient * consultingPatient, Calendrier calendrier);
void freeProject(Project* project);
void printProject(Project* p);

int GPCalendar_saveProject(char* nomFichier, Project* project);

char* Project_jsonSave(Project* p);
int ListMedecin_jsonSave(cJSON* listMedecinJson, ListMedecin* l);
int ListPatient_jsonSave(cJSON* listPatientJson, ListPatient* l);
int Calendrier_jsonSave(cJSON* calendrierJson, Calendrier c);

Project* GPCalendar_loadProject(char* nomFichier);

Project* Project_jsonLoad(const char* content);
int ListMedecin_jsonLoad(cJSON* projectJson, ListMedecin* lM);
int ListPatient_jsonLoad(cJSON* projectJson, ListMedecin* project_workingMedecins, ListPatient * lP);
int Calendrier_jsonLoad(cJSON* projectJson, ListMedecin* lM, ListPatient* lP, Calendrier c);



#endif //C_PROJECT_JSONSAVE_H
