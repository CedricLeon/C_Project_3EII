#ifndef C_PROJECT_JSONSAVE_H
#define C_PROJECT_JSONSAVE_H

#include <cJSON.h>
/*
struct Project
{
    // ListMedecin
    // ListPatient
    // RendezVous
    // Calendrier
}

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
