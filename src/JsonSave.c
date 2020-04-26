#include "JsonSave.h"

char* jsonSave(Project* p)
{
    //Création des variables qu'on va utiliser
    char* string = NULL;
    cJSON* listMedecinJson = NULL;
    cJSON* listPatientJson = NULL;
    cJSON* calendrierJson = NULL;

    //On crée un objet cJSOn qu'on deletera après avoir print son contenu dans un string
    cJSON* projectJson = cJSON_CreateObject();
    if (cJSON_AddStringToObject(projectJson, "nom", p->nom) == NULL)  return NULL;

    //On ajoute à notre objet cJSON un tableau appellé Working Medecins
    listMedecinJson = cJSON_AddArrayToObject(projectJson, "Working Medecins");
    if(listMedecinJson == NULL)                                             return NULL;
    //On vient écrire dans cet objet tout les medecins
    ListMedecin_jsonSave(listMedecinJson, p->workingMedecins);

    //On ajoute à notre objet cJSON un tableau appellé Working Medecins
    listPatientJson = cJSON_AddArrayToObject(projectJson, "Consulting Patients");
    if(listPatientJson == NULL)                                             return NULL;
    //On vient écrire dans cet objet tout les patients
    ListPatient_jsonSave(listPatientJson, p->consultingPatient);

    calendrierJson = cJSON_AddArrayToObject(projectJson, "Hospital Calendar");
    if(calendrierJson == NULL)                                             return NULL;
    Calendrier_jsonSave(calendrierJson, p->calendrier);

    string = cJSON_Print(projectJson);
    if (string == NULL)                                        fprintf(stderr, "Failed to print the project.\n");
    cJSON_Delete(projectJson); //cette fonction appelle cJSON_Delete(listMedecinJson); et cJSON_Delete(listPatientJson);
                               // puisque ces objets composent projectJson
    return string;
}



//NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor_with_helpers(void)
{
    const unsigned int resolution_numbers[3][2] = {
            {1280, 720},
            {1920, 1080},
            {3840, 2160}
    };
    char *string = NULL;
    cJSON *resolutions = NULL;
    size_t index = 0;

    cJSON *monitor = cJSON_CreateObject();
    if (cJSON_AddStringToObject(monitor, "name", "Awesome 4K") == NULL)                           goto end;

    resolutions = cJSON_AddArrayToObject(monitor, "resolutions");

    if (resolutions == NULL)                                                                                   goto end;

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        cJSON *resolution = cJSON_CreateObject();

        if (cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL)  goto end;

        if (cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL) goto end;

        cJSON_AddItemToArray(resolutions, resolution);
    }

    string = cJSON_Print(monitor);
    if (string == NULL)        fprintf(stderr, "Failed to print monitor.\n");

    end:
    cJSON_Delete(monitor);
    return string;
}