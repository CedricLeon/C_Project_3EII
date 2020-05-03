#include "GPCalendar/Model/JsonSave.h"

Project * CreerProject(char* nom, ListMedecin * workingMedecins, ListPatient * consultingPatient, Calendrier calendrier){
    Project* p = (Project*) malloc(sizeof(Project));
    p->nom = nom;
    p->workingMedecins = workingMedecins;
    p->consultingPatient = consultingPatient;
    p->calendrier = calendrier;
}

/**
 * freeProject : Free entièrement un projet, à savoir :
 *             - le calendrier de l'hopital (et donc tout les rdv qui le composent)
 *             - les mèdecins de l'hopital qui ont été rentré dans la liste workingMedecins
 *             - les patients de l'hopital qui ont été rentré dans la liste consultingPatients et donc leur dossier médical et ses ordonnances
 * @param project : le projet à free
 */
void freeProject(Project* project){

    freeCalendrier(project->calendrier);
    ListPatient_free(project->consultingPatient);
    ListMedecin_free(project->workingMedecins);

    free((void*) project);
}

/**
 * Pour l'instant On ne sauvegarde pas les diplomes et spécialités des mèdecins ainsi que les antécédents des DossierMédicaux
 */

int GPCalendar_saveProject(char* nomFichier, Project* project){

    FILE* savingFile = NULL;
    savingFile = fopen(nomFichier, "w");

    if (savingFile != NULL)
    {
        char* toPrint = jsonSave(project);
        if(toPrint == NULL){
            printf("\n MDR go debugger.\n");
            return 0;
        }
        fprintf(savingFile, "%s", toPrint);

        free((void*) toPrint);      //Ici on free le char* car il est malloc dans les fonctions de cJSON

        fclose(savingFile);
        return 1;
    }
    else
    {
        printf("\nGPCalendar_saveProject : Impossible d'ouvrir le fichier %s\n", nomFichier);
        return 0;
    }
}

/**
 * jsonSave : Fonction permettant de sauvegarder un objet projet dans un fichier .json à l'aide de la librairie cjson
 * @param p : l'instance de projet à save
 * @return un string qu'il faudra écrire dans un fichier texte
 */
char* jsonSave(Project* project)
{
    //Création des variables qu'on va utiliser
    char* string = NULL;
    cJSON* listMedecinJson = NULL;
    cJSON* listPatientJson = NULL;
    cJSON* calendrierJson = NULL;

    //On crée un objet cJSOn qu'on deletera après avoir print son contenu dans un string
    cJSON* projectJson = cJSON_CreateObject();
    //On y ajoute le nom du projet
    if (cJSON_AddStringToObject(projectJson, "nom", project->nom) == NULL)  goto end;

    //On ajoute à notre objet cJSON un tableau appellé Working Medecins
    listMedecinJson = cJSON_AddArrayToObject(projectJson, "Working Medecins");
    if(listMedecinJson == NULL)                                             goto end;
    //On vient écrire dans cet objet tout les medecins
    if(ListMedecin_jsonSave(listMedecinJson, project->workingMedecins) != 1) goto end;

    //On ajoute à notre objet cJSON un tableau appellé Consulting Patients
    listPatientJson = cJSON_AddArrayToObject(projectJson, "Consulting Patients");
    if(listPatientJson == NULL)                                             goto end;
    //On vient écrire dans cet objet tout les patients
    ListPatient_jsonSave(listPatientJson, project->consultingPatient);

    //On ajoute à notre objet cJSON un tableau de drv appellé Hospital Calendar
    calendrierJson = cJSON_AddArrayToObject(projectJson, "Hospital Calendar");
    if(calendrierJson == NULL)                                             goto end;
    Calendrier_jsonSave(calendrierJson, project->calendrier);

    //Une fois tout ajouté on écrit notre objet cjson dans un char* et on le return
    string = cJSON_Print(projectJson);
    if (string == NULL) {
        fprintf(stderr, "Failed to print the project.\n");
    }

    end: //Plus lisible d'utiliser les goto car sinon il faut mettre cJSON_Delete(projectJson) dans toutes les boucles if

    cJSON_Delete(projectJson); //cette fonction appelle cJSON_Delete(listMedecinJson); et cJSON_Delete(listPatientJson);
                               // puisque ces objets composent projectJson
    return string;
}

/**
 * ListMedecin_jsonSave : fonction qui écrit dans un objet cJson une liste de mèdecins
 * Chaque mèdecin possédant une liste de patients recus, on écrira uniquement l'ID de ces patients (aka leur numéro de sécurité social) dans cette liste
 * @param listMedecinJson : l'objet cJson dans lequel on écrit la liste de mèdecin, c'est un tableau
 * @param l : la liste de mèdecins à écrire
 * @return 1 si tout s'est bien passé
 *         0 si une des étapes a échoué
 */
int ListMedecin_jsonSave(cJSON* listMedecinJson, ListMedecin* l){

    for(ListMedecin_setOnFirst(l); !ListMedecin_isOutOfList(l); ListMedecin_setOnNext(l)){

        cJSON* medecin = cJSON_CreateObject();
        cJSON_AddItemToArray(listMedecinJson, medecin); //On le fait juste après la création de l'objet pour ne pas avoir
                                                        //de LEAK MEMORY si l'y=un des ajouts qui suit fail et du coup
                                                        //quitte la fonction avant d'avoir ajouter l'objet au tableau

        if (cJSON_AddStringToObject(medecin, "nom", ListMedecin_getCurrent(l)->nom) == NULL)  return 0;
        if (cJSON_AddStringToObject(medecin, "prenom", ListMedecin_getCurrent(l)->prenom) == NULL) return 0;
        if (cJSON_AddStringToObject(medecin, "mail", ListMedecin_getCurrent(l)->adresse_mail) == NULL) return 0;
        if (cJSON_AddStringToObject(medecin, "tel", ListMedecin_getCurrent(l)->numero_telephone) == NULL) return 0;
        if (cJSON_AddStringToObject(medecin, "rps", ListMedecin_getCurrent(l)->numero_RPS) == NULL) return 0;

        /**
         * On gère la liste des patients recus : on crée un tableau, on parcourt la liste des patients recus et à chaque
         * patient on crée un string avec son numéro de sécurité sociale puis on ajoute ce string au tableau que l'on
         * vient de créer et à la fin du parcours de la liste on ajoute notre tableau à son mèdecin
         */

        cJSON* patientsRecus = cJSON_AddArrayToObject(medecin, "patientsRecus");

        for(ListPatient_setOnFirst(l->current->medecin->patients_recus); !ListPatient_isOutOfList(l->current->medecin->patients_recus); ListPatient_setOnNext(l->current->medecin->patients_recus)){
            cJSON* IDpatient = cJSON_CreateString(ListPatient_getCurrent(l->current->medecin->patients_recus)->numero_secu_social);
            if(IDpatient == NULL) return 0;
            cJSON_AddItemToArray(patientsRecus, IDpatient);
        }
        //Là normalement on a tout ajouté à notre mèdecin on peut passer au suivant
    }
    return 1;
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

            //Une ordonnance ne contient plus de patient, on considère donc que toutes les ordonnances présentes dans la structure d'un patient le concerne
            //Par conséquent on ne rajoute plus l'IDPatient dans une ordonnance
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
int Calendrier_jsonSave(cJSON* calendrierJson, Calendrier c){

    /**
     * Avec les 4 boucles for qui suivent on vient chercher tout les rdv
     */
    for(ListAnnee_setOnFirst(c); !ListAnnee_isOutOfList(c); ListAnnee_setOnNext(c))
    {
        Annee a = ListAnnee_getCurrent(c);
        for(ListMois_setOnFirst(a); !ListMois_isOutOfList(a); ListMois_setOnNext(a))
        {
            Mois m = ListMois_getCurrent(a);
            for(ListJour_setOnFirst(m); !ListJour_isOutOfList(m); ListJour_setOnNext(m))
            {
                Jour j = ListJour_getCurrent(m);
                for(ListRendezVous_setOnFirst(j); !ListRendezVous_isOutOfList(j); ListRendezVous_setOnNext(j))
                {
                    RendezVous * rdv = ListRendezVous_getCurrent(j);

                    //Puis on store un à un les rdv
                    cJSON* rdvJson = cJSON_CreateObject();
                    cJSON_AddItemToArray(calendrierJson, rdvJson);

                    char* tmp1 = (char*) malloc(10);
                    getInfosDate(tmp1, rdv->date);
                    if (cJSON_AddStringToObject(rdvJson, "date", tmp1) == NULL)  return 0;
                    free((void*) tmp1);

                    if (cJSON_AddNumberToObject(rdvJson, "heure_debut", rdv->heure_debut) == NULL)  return 0;
                    if (cJSON_AddNumberToObject(rdvJson, "heure_fin", rdv->heure_fin) == NULL)  return 0;

                    if (cJSON_AddStringToObject(rdvJson, "lieu", rdv->lieu) == NULL)  return 0;
                    if (cJSON_AddStringToObject(rdvJson, "patient", rdv->patient->numero_secu_social) == NULL)  return 0;
                    if (cJSON_AddStringToObject(rdvJson, "medecin", rdv->medecin->numero_RPS) == NULL)  return 0;
                    if (cJSON_AddStringToObject(rdvJson, "motif", rdv->motif) == NULL)  return 0;

                    //Là normalement on a tout ajouté à notre rdv on peut passer au suivant
                }
            }
        }
    }
    //Là normalement on a ajouté tout les rdv de notre calendrier à l'objet cJson
    return 1;
}


/**
 * Exemple de cJSON sur leur git
 */
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