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


/**
 * ListPatient_jsonSave : fonction qui écrit dans un objet cJson une liste de patient
 * Chaque patient possédant un dossier médical possédant lui même une liste de medecins consultes et une liste d'ordonnances
 * On écrira directement ces infos dans le patient (pour éviter la création d'une liste de dossier médicaus inutile)
 * Et on écrira uniquement l'ID des medecins consultes (aka leur numéro RPS) dans cette liste de medeci dans patient
 * Pui un tableau d'ordonnances représentant la liste des ordonnaces du dossier médical du patient
 * @param listPatientJson : l'objet cJson dans lequel on écrit la liste de patient, c'est un tableau
 * @param l : la liste de patients à save
 * @return 1 si tout s'est bien passé
 *         0 si une des étapes a échoué
 */
int ListPatient_jsonSave(cJSON* listPatientJson, ListPatient* l){

    for(ListPatient_setOnFirst(l); !ListPatient_isOutOfList(l); ListPatient_setOnNext(l)){

        cJSON* patient = cJSON_CreateObject();
        cJSON_AddItemToArray(listPatientJson, patient); //On le fait juste après la création de l'objet pour ne pas avoir
                                                        //de LEAK MEMORY si l'y=un des ajouts qui suit fail et du coup
                                                        //quitte la fonction avant d'avoir ajouter l'objet au tableau

        if (cJSON_AddStringToObject(patient, "nom", ListPatient_getCurrent(l)->nom) == NULL)  return 0;
        if (cJSON_AddStringToObject(patient, "prenom", ListPatient_getCurrent(l)->prenom) == NULL) return 0;

        char* tmp1 = (char*) malloc(10);
        getInfosDate(tmp1, ListPatient_getCurrent(l)->date_naissance);
        if (cJSON_AddStringToObject(patient, "dateNaissance", tmp1) == NULL) return 0;
        free((void*) tmp1);

        if (cJSON_AddStringToObject(patient, "mail", ListPatient_getCurrent(l)->adresse_mail) == NULL) return 0;
        if (cJSON_AddStringToObject(patient, "tel", ListPatient_getCurrent(l)->numero_telephone) == NULL) return 0;
        if (cJSON_AddStringToObject(patient, "numeroSecuriteSociale", ListPatient_getCurrent(l)->numero_secu_social) == NULL) return 0;

        //A partir d'ici ce qu'on écrit à sa place dans le dossier médical du patient mais par soucis de simplicité on le met dans le patient directement
        /**
         * On gère la liste des medecins consultes : on crée un tableau, on parcourt la liste des medecins consultes et à chaque
         * medecin on crée un string avec son numéro_RPS puis on ajoute ce string au tableau que l'on
         * vient de créer et à la fin du parcours de la liste on ajoute notre tableau à son patient
         */

        cJSON* medecinsConsultes = cJSON_AddArrayToObject(patient, "medecinsConsultes");   //idem

        for(ListMedecin_setOnFirst(l->current->patient->dossierMedical->medecins_consultes); !ListMedecin_isOutOfList(l->current->patient->dossierMedical->medecins_consultes); ListMedecin_setOnNext(l->current->patient->dossierMedical->medecins_consultes)){
            cJSON* IDmedecin = cJSON_CreateString(ListMedecin_getCurrent(l->current->patient->dossierMedical->medecins_consultes)->numero_RPS);
            if(IDmedecin == NULL) return 0;
            cJSON_AddItemToArray(medecinsConsultes, IDmedecin);
        }

        /**
         * On gère la liste d'ordonnances du dossier médical de notre patient
         */
        cJSON* listOrdonnances = cJSON_AddArrayToObject(patient, "ordonnances");   //idem

        ListOrdonnance * ordonnancesPatients = l->current->patient->dossierMedical->ordonnances;

        for(ListOrdonnance_setOnFirst(ordonnancesPatients); !ListOrdonnance_isOutOfList(ordonnancesPatients); ListOrdonnance_setOnNext(ordonnancesPatients)){

            cJSON* ordonnance = cJSON_CreateObject();
            cJSON_AddItemToArray(listOrdonnances, ordonnance);

            if (cJSON_AddStringToObject(ordonnance, "IDpatient", ListOrdonnance_getCurrent(ordonnancesPatients)->patient->numero_secu_social) == NULL)  return 0;
            if (cJSON_AddStringToObject(ordonnance, "IDmedecin", ListOrdonnance_getCurrent(ordonnancesPatients)->medecin->numero_RPS) == NULL)  return 0;

            char* tmp2 = (char*) malloc(10);
            getInfosDate(tmp2, ListOrdonnance_getCurrent(ordonnancesPatients)->date_edition);
            if (cJSON_AddStringToObject(ordonnance, "date_edition", tmp2) == NULL) return 0;
            free((void*) tmp2);

            char* tmp3 = (char*) malloc(10);
            getInfosDate(tmp3, ListOrdonnance_getCurrent(ordonnancesPatients)->date_expiration);
            if (cJSON_AddStringToObject(ordonnance, "date_expiration", tmp3) == NULL) return 0;
            free((void*) tmp3);

            if (cJSON_AddStringToObject(ordonnance, "description", ListOrdonnance_getCurrent(ordonnancesPatients)->description) == NULL)  return 0;
            //Là normalement on a tout ajouté à notre ordonnance à notre liste d'ordonnances, on peut passer au suivant
        }
        //Là normalement on a tout ajouté à notre patient on peut passer au suivant
    }
    return 1;
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