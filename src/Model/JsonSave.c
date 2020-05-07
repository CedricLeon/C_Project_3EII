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
 *             - le calendrier de l'hopital (et donc tous les rdv qui le composent)
 *             - les médecins de l'hopital qui ont été rentrés dans la liste workingMedecins
 *             - les patients de l'hopital qui ont été rentrés dans la liste consultingPatients et donc leur dossier médical et leurs ordonnances
 * @param project : le projet à free
 */
void freeProject(Project* project){

    freeCalendrier(project->calendrier);
    ListPatient_free(project->consultingPatient);
    ListMedecin_free(project->workingMedecins);

    free((void*) project);
}

/**
 * printProject : Affiche dans la console toutes les données d'un projet
 * @param p : le projet à afficher
 */
void printProject(Project* p){
    printf("\n*******************************Affichage du projet : \"%s\"******************************\n", p->nom);
    //Affichage de la liste des mèdecins de l'hopital
    printf("\n *** Working medecins :\n");
    printListMedecin(p->workingMedecins);
    //Affichage de la liste de patients de l'hopital avec leurs ordonnances
    printf("\n\n *** Consulting Patients :\n");
    printListPatient(p->consultingPatient);
    //Affichage du calendrier de l'hopital
    printf("\n\n *** Hospital Calendar :\n");
    printCalendrier(p->calendrier);
    printf("\n**************************************************************************************\n");
}

/**********************************************************************************************************************/
                                            /*Save Functions*/
/**********************************************************************************************************************/

/**
 * Pour l'instant On ne sauvegarde pas les diplomes et spécialités des médecins ainsi que les antécédents des DossierMédicaux
 */
 /**
  * GPCalendar_saveProject : Sauvegarde un projet (liste de médecins, patients et un calendrier) sous forme de fichier texte au format JSON
  * @param nomFichier : le nom du fichier qui contiendra les données au format JSON
  * @param project : le projet à sauvegarder
  * @return 1 si tout s'est bien passé
  *         0 sinon (erreur d'ouverture de fichier ou de parsing : Cf cJSON)
  */
int GPCalendar_saveProject(char* nomFichier, Project* project){

    FILE* savingFile = NULL;
    savingFile = fopen(nomFichier, "w");

    if (savingFile != NULL)
    {
        char* toPrint = Project_jsonSave(project);
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
 * Project_jsonSave : Fonction permettant de sauvegarder un objet projet dans un fichier .json à l'aide de la librairie cjson
 * @param p : l'instance de projet à save
 * @return un string qui sera écrit dans un fichier texte
 */
char* Project_jsonSave(Project* project)
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
    //On vient écrire dans cet objet tous les medecins
    if(ListMedecin_jsonSave(listMedecinJson, project->workingMedecins) != 1) goto end;

    //On ajoute à notre objet cJSON un tableau appellé Consulting Patients
    listPatientJson = cJSON_AddArrayToObject(projectJson, "Consulting Patients");
    if(listPatientJson == NULL)                                             goto end;
    //On vient écrire dans cet objet tous les patients
    ListPatient_jsonSave(listPatientJson, project->consultingPatient);

    //On ajoute à notre objet cJSON un tableau de rdv appellé Hospital Calendar
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
 * ListMedecin_jsonSave : fonction qui écrit dans un objet cJson une liste de médecins
 * Chaque médecin possédant une liste de patients recus, on écrira uniquement l'ID de ces patients (= leur numéro de sécurité social) dans cette liste
 * @param listMedecinJson : l'objet cJson dans lequel on écrit la liste de médecins, c'est un tableau
 * @param l : la liste de médecins à écrire
 * @return 1 si tout s'est bien passé
 *         0 si une des étapes a échoué
 */
int ListMedecin_jsonSave(cJSON* listMedecinJson, ListMedecin* l){

    for(ListMedecin_setOnFirst(l); !ListMedecin_isOutOfList(l); ListMedecin_setOnNext(l)){

        cJSON* medecin = cJSON_CreateObject();
        cJSON_AddItemToArray(listMedecinJson, medecin); //On le fait juste après la création de l'objet pour ne pas avoir
                                                        //de LEAK MEMORY si l'un des ajouts qui suit fail et du coup
                                                        //quitte la fonction avant d'avoir ajouté l'objet au tableau

        if (cJSON_AddStringToObject(medecin, "nom", ListMedecin_getCurrent(l)->nom) == NULL)  return 0;
        if (cJSON_AddStringToObject(medecin, "prenom", ListMedecin_getCurrent(l)->prenom) == NULL) return 0;
        if (cJSON_AddStringToObject(medecin, "mail", ListMedecin_getCurrent(l)->adresse_mail) == NULL) return 0;
        if (cJSON_AddStringToObject(medecin, "tel", ListMedecin_getCurrent(l)->numero_telephone) == NULL) return 0;
        if (cJSON_AddStringToObject(medecin, "rps", ListMedecin_getCurrent(l)->numero_RPS) == NULL) return 0;

        /**
         * On gère la liste des patients recus : on crée un tableau, on parcourt la liste des patients recus et à chaque
         * patient on crée un string avec son numéro de sécurité sociale puis on ajoute ce string au tableau que l'on
         * vient de créer et à la fin du parcours de la liste on ajoute notre tableau à son médecin
         *
         * EDIT : POUR LA V0 ON NE MET PAS LES PATIENTS RECUS : TROP GALERE, ON AJOUTERA LES COUPLES PATIENT / MEDECIN DEPUIS LES RDV
         */

        /*cJSON* patientsRecus = cJSON_AddArrayToObject(medecin, "patientsRecus");

        for(ListPatient_setOnFirst(l->current->medecin->patients_recus); !ListPatient_isOutOfList(l->current->medecin->patients_recus); ListPatient_setOnNext(l->current->medecin->patients_recus)){
            cJSON* IDpatient = cJSON_CreateString(ListPatient_getCurrent(l->current->medecin->patients_recus)->numero_secu_social);
            if(IDpatient == NULL) return 0;
            cJSON_AddItemToArray(patientsRecus, IDpatient);
        }*/
        //Là normalement on a tout ajouté à notre médecin on peut passer au suivant
    }
    return 1;
}

/**
 * ListPatient_jsonSave : fonction qui écrit dans un objet cJson une liste de patient
 * Chaque patient possédant un dossier médical possédant lui même une liste de medecins consultes et une liste d'ordonnances
 * On écrira directement ces infos dans le patient (pour éviter la création d'une liste de dossier médicaux inutile)
 * Et on écrira uniquement l'ID des medecins consultes (= leur numéro RPS) dans cette liste de medecin dans patient
 * Puis un tableau d'ordonnances représentant la liste des ordonnaces du dossier médical du patient
 * @param listPatientJson : l'objet cJson dans lequel on écrit la liste de patient, c'est un tableau
 * @param l : la liste de patients à save
 * @return 1 si tout s'est bien passé
 *         0 si une des étapes a échoué
 */
int ListPatient_jsonSave(cJSON* listPatientJson, ListPatient* l){

    for(ListPatient_setOnFirst(l); !ListPatient_isOutOfList(l); ListPatient_setOnNext(l)){

        cJSON* patient = cJSON_CreateObject();
        cJSON_AddItemToArray(listPatientJson, patient); //On le fait juste après la création de l'objet pour ne pas avoir
                                                        //de LEAK MEMORY si l'un des ajouts qui suit fail et du coup
                                                        //quitte la fonction avant d'avoir ajouter l'objet au tableau
        Patient* p = ListPatient_getCurrent(l);

        if (cJSON_AddStringToObject(patient, "nom", p->nom) == NULL)  return 0;
        if (cJSON_AddStringToObject(patient, "prenom", p->prenom) == NULL) return 0;

        if (cJSON_AddNumberToObject(patient, "date_naissance_jour", p->date_naissance->jour) == NULL)  return 0;
        if (cJSON_AddNumberToObject(patient, "date_naissance_mois", p->date_naissance->mois) == NULL)  return 0;
        if (cJSON_AddNumberToObject(patient, "date_naissance_annee", p->date_naissance->annee) == NULL)  return 0;

        //On ne passe pas la date sous forme de String car c'est trop galère à load (=> 3 int)
        /*char* tmp1 = (char*) malloc(10);
        getInfosDate(tmp1, ListPatient_getCurrent(l)->date_naissance);
        if (cJSON_AddStringToObject(patient, "dateNaissance", tmp1) == NULL) return 0;
        free((void*) tmp1);*/

        if (cJSON_AddStringToObject(patient, "mail", ListPatient_getCurrent(l)->adresse_mail) == NULL) return 0;
        if (cJSON_AddStringToObject(patient, "tel", ListPatient_getCurrent(l)->numero_telephone) == NULL) return 0;
        if (cJSON_AddStringToObject(patient, "numeroSecuriteSociale", ListPatient_getCurrent(l)->numero_secu_social) == NULL) return 0;

        //A partir d'ici ce qu'on écrit à sa place dans le dossier médical du patient mais par soucis de simplicité on le met dans le patient directement
        /**
         * On gère la liste des medecins consultes : on crée un tableau, on parcourt la liste des medecins consultes et à chaque
         * medecin on crée un string avec son numéro_RPS puis on ajoute ce string au tableau que l'on
         * vient de créer et à la fin du parcours de la liste on ajoute notre tableau à son patient
         *
         * EDIT : POUR LA V0 ON NE MET PAS LES MEDECINS CONSULTES : TROP GALERE, ON AJOUTERA LES COUPLES PATIENT / MEDECIN DEPUIS LES RDV
         */

        /*cJSON* medecinsConsultes = cJSON_AddArrayToObject(patient, "medecinsConsultes");   //idem

        for(ListMedecin_setOnFirst(l->current->patient->dossierMedical->medecins_consultes); !ListMedecin_isOutOfList(l->current->patient->dossierMedical->medecins_consultes); ListMedecin_setOnNext(l->current->patient->dossierMedical->medecins_consultes)){
            cJSON* IDmedecin = cJSON_CreateString(ListMedecin_getCurrent(l->current->patient->dossierMedical->medecins_consultes)->numero_RPS);
            if(IDmedecin == NULL) return 0;
            cJSON_AddItemToArray(medecinsConsultes, IDmedecin);
        }*/

        /**
         * On gère la liste d'ordonnances du dossier médical de notre patient
         */
        cJSON* listOrdonnances = cJSON_AddArrayToObject(patient, "ordonnances");   //idem

        ListOrdonnance * ordonnancesPatients = l->current->patient->dossierMedical->ordonnances;

        for(ListOrdonnance_setOnFirst(ordonnancesPatients); !ListOrdonnance_isOutOfList(ordonnancesPatients); ListOrdonnance_setOnNext(ordonnancesPatients)){

            cJSON* ordonnance = cJSON_CreateObject();
            cJSON_AddItemToArray(listOrdonnances, ordonnance);

            Ordonnance* ordo = ListOrdonnance_getCurrent(ordonnancesPatients);

            //Une ordonnance ne contient plus de patient, on considère donc que toutes les ordonnances présentes dans la structure d'un patient le concerne
            //Par conséquent on ne rajoute plus l'IDPatient dans une ordonnance
            if (cJSON_AddStringToObject(ordonnance, "IDmedecin", ordo->medecin->numero_RPS) == NULL)  return 0;

            if (cJSON_AddNumberToObject(ordonnance, "date_edition_jour", ordo->date_edition->jour) == NULL)  return 0;
            if (cJSON_AddNumberToObject(ordonnance, "date_edition_mois", ordo->date_edition->mois) == NULL)  return 0;
            if (cJSON_AddNumberToObject(ordonnance, "date_edition_annee", ordo->date_edition->annee) == NULL)  return 0;

            //On ne passe pas la date sous forme de String car c'est trop galère à load (=> 3 int)
            /*char* tmp2 = (char*) malloc(10);
            getInfosDate(tmp2, ordo->date_edition);
            if (cJSON_AddStringToObject(ordonnance, "date_edition", tmp2) == NULL) return 0;
            free((void*) tmp2);*/

            if (cJSON_AddNumberToObject(ordonnance, "date_expiration_jour", ordo->date_expiration->jour) == NULL)  return 0;
            if (cJSON_AddNumberToObject(ordonnance, "date_expiration_mois", ordo->date_expiration->mois) == NULL)  return 0;
            if (cJSON_AddNumberToObject(ordonnance, "date_expiration_annee", ordo->date_expiration->annee) == NULL)  return 0;

            //On ne passe pas la date sous forme de String car c'est trop galère à load (=> 3 int)
            /*char* tmp3 = (char*) malloc(10);
            getInfosDate(tmp3, ordo->date_expiration);
            if (cJSON_AddStringToObject(ordonnance, "date_expiration", tmp3) == NULL) return 0;
            free((void*) tmp3);*/

            if (cJSON_AddStringToObject(ordonnance, "description", ordo->description) == NULL)  return 0;
            //Là normalement on a tout ajouté à notre ordonnance à notre liste d'ordonnances, on peut passer au suivant
        }
        //Là normalement on a tout ajouté à notre patient on peut passer au suivant
    }
    return 1;
}
/**
 * Calendrier_jsonSave : fonction qui écrit dans un objet cJson une liste de Rendez-vous (triée chronologiquement)
 * @param calendrierJson : l'objet cJSON dans lequel on sauvegarde le calendrier
 * @param c : le calendrier à save
 * @return 1 si tout s'est bien passé
 *         0 sinon
 */
int Calendrier_jsonSave(cJSON* calendrierJson, Calendrier c){

    /**
     * Avec les 4 boucles for qui suivent on vient chercher tous les rdv
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

                    if (cJSON_AddNumberToObject(rdvJson, "date_jour", rdv->date->jour) == NULL)  return 0;
                    if (cJSON_AddNumberToObject(rdvJson, "date_mois", rdv->date->mois) == NULL)  return 0;
                    if (cJSON_AddNumberToObject(rdvJson, "date_annee", rdv->date->annee) == NULL)  return 0;

                    //On ne passe pas la date sous forme de String car c'est trop galère à load (=> 3 int)
                    /*char* tmp1 = (char*) malloc(10);
                    getInfosDate(tmp1, rdv->date);
                    if (cJSON_AddStringToObject(rdvJson, "date", tmp1) == NULL)  return 0;
                    free((void*) tmp1);*/

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

/**********************************************************************************************************************/
                                            /*Load Functions*/
/**********************************************************************************************************************/

 /**
  * GPCalendar_loadProject : fonction récupérant les données d'un projet depuis un fichier au format JSON
  * @param nomFichier : le fichier depuis lequel on récupère les données
  * @return un pointeur sur le projet créé avec les données JSON
  */
Project*  GPCalendar_loadProject(char* nomFichier){

    FILE* loadingFile = NULL;
    //on ouvre le fichier
    loadingFile = fopen(nomFichier, "r");
    long int size = 0;

    if (loadingFile != NULL)
    {
        //Pn se place à la fin du fichier
        fseek(loadingFile, 0L, SEEK_END);
        //et on cherche le nb de caractère qu'on a parcouru
        size = ftell(loadingFile);
        //On alloue un tableau de char de la taille du fichier
        char content[size + 1];
        //On se remet au début du fichier
        rewind(loadingFile);
        //On charge dans notre tableau de charge 1 buffer de la taille du fichier
        fread(content, size, 1, loadingFile);
        // terminate the string
        content[size] = 0;
        // On affiche le fichier pour tester
        printf("\n\nGPCalendar_loadProject() : the whole file is:\n %s\n", content);

        //on load un projet depuis le contenu du fichier
        Project * p = Project_jsonLoad(content);

        //Et enfin on ferme le fichier
        fclose(loadingFile);
        return p;
    }
    else
    {
        printf("\nGPCalendar_loadProject : Impossible d'ouvrir le fichier \"%s\".\nLe projet return est donc NULL.\n", nomFichier);
        return NULL;
    }
}
/**
 * Project_jsonLoad : Crée un objet project depuis un char* au format JSON
 * @param content : le char* avec les données du projet
 * @return un pointeur sur le projet créé si tout s'est bien passé
 *         NULL si un erreur a eu lieu (Cf cJSON)
 */
Project* Project_jsonLoad(const char* const content){

    Project * project = NULL;

    const cJSON* nameJson = NULL;
    char* project_name = NULL;
    ListMedecin* project_workingMedecins = CreerListMedecin();
    ListPatient* project_consultingPatient = CreerListPatient();
    Calendrier project_calendrier = CreerCalendrier();

    //On crée d'abord un objet cJSON avec tout le contenu du fichier qu'il faudra delete à la fin !!!
    cJSON* projectJson = cJSON_Parse(content);
    if (projectJson == NULL)
    {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    //Puis on commence à aller chercher les infos : d'abord le nom du projet
    nameJson = cJSON_GetObjectItemCaseSensitive(projectJson, "name");
    if (cJSON_IsString(nameJson) && (nameJson->valuestring != NULL))
    {
        project_name = nameJson->valuestring;
        printf("Name of project loaded : \"%s\"\n", project_name);
    }

    if(!ListMedecin_jsonLoad(projectJson, project_workingMedecins))
    {
        printf("Erreur dans ListMedecin_jsonLoad().\n");
        goto end;
    }
    // ListMedecin_jsonLoad() s'est bien passé on ajoute la liste de mèdecin au projet lors de sa création
    if(!ListPatient_jsonLoad(projectJson, project_workingMedecins, project_consultingPatient))
    {
        printf("Erreur dans ListPatient_jsonLoad().\n");
        goto end;
    }
    // ListPatient_jsonLoad() s'est bien passé on ajoute la liste de patient au projet lors de sa création
    if(!Calendrier_jsonLoad(projectJson, project_workingMedecins, project_consultingPatient, project_calendrier))
    {
        printf("Erreur dans Calendrier_jsonLoad().\n");
        goto end;
    }
    // Calendrier_jsonLoad() s'est bien passé on ajoute la liste de rdv au projet lors de sa création
    project = CreerProject(project_name, project_workingMedecins, project_consultingPatient, project_calendrier);

    end:
    cJSON_Delete(projectJson);
    return project;
}
/**
 * ListMedecin_jsonLoad : Load depuis un objet cJSON une liste de médecins
 * @param projectJson : l'objet cJSON contenant les données pour la liste de médecins
 * @return 1 si tout s'est bien passé
 *         0 sinon
 */
int ListMedecin_jsonLoad(cJSON* projectJson, ListMedecin* lM){

    const cJSON* workingMedecinsJson = NULL;
    const cJSON* medecinJson = NULL;

    workingMedecinsJson = cJSON_GetObjectItemCaseSensitive(projectJson, "Working Medecins");
    cJSON_ArrayForEach(medecinJson, workingMedecinsJson)
    {
        cJSON* nomMedecinJson = cJSON_GetObjectItemCaseSensitive(medecinJson, "nom");
        cJSON* prenomMedecinJson = cJSON_GetObjectItemCaseSensitive(medecinJson, "prenom");
        cJSON* mailMedecinJson = cJSON_GetObjectItemCaseSensitive(medecinJson, "mail");
        cJSON* telMedecinJson = cJSON_GetObjectItemCaseSensitive(medecinJson, "tel");
        cJSON* rpsMedecinJson = cJSON_GetObjectItemCaseSensitive(medecinJson, "rps");

        //Comme il y a déjà un check de NULL dans cJson_isString() on est pas obligé de le faire :
        if (!cJSON_IsString(nomMedecinJson) || !cJSON_IsString(prenomMedecinJson) || !cJSON_IsString(mailMedecinJson)
            || !cJSON_IsString(telMedecinJson) || !cJSON_IsString(rpsMedecinJson)){
            printf("ListMedecin_jsonLoad() : une des valeurs n'est pas au format attendu : return 0.\n");
            //l'une des valeur lue n'est pas un string : erreur
            return 0;
        }

        Medecin * medecin = CreerMedecin(nomMedecinJson->valuestring, prenomMedecinJson->valuestring,
                mailMedecinJson->valuestring, telMedecinJson->valuestring, rpsMedecinJson->valuestring);
        if(!ListMedecin_add(lM, medecin)){
            printf("ListMedecin_jsonLoad() : Echec de l'ajout du mèdecin %s %s à la liste.\n", medecin->nom, medecin->prenom);
            return 0;
        }

    }
    printf("ListMedecin_jsonLoad() : normalement tous les mèdecins ont été add à la liste workingMedecins.\n");
    return 1;
}
int ListPatient_jsonLoad(cJSON* projectJson, ListMedecin* project_workingMedecins, ListPatient * lP){

    const cJSON* consultingPatientsJson = NULL;
    const cJSON* patientJson = NULL;

    const cJSON* ordonnancesPatientJson = NULL;
    const cJSON* ordonnanceJson = NULL;

    consultingPatientsJson = cJSON_GetObjectItemCaseSensitive(projectJson, "Consulting Patients");
    cJSON_ArrayForEach(patientJson, consultingPatientsJson)
    {
        cJSON* nomPatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "nom");
        cJSON* prenomPatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "prenom");

        cJSON* jourDatePatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "date_naissance_jour");
        cJSON* moisDatePatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "date_naissance_mois");
        cJSON* anneeDatePatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "date_naissance_annee");

        cJSON* mailPatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "mail");
        cJSON* telPatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "tel");
        cJSON* secuPatientJson = cJSON_GetObjectItemCaseSensitive(patientJson, "numeroSecuriteSociale");

        //Comme il y a déjà un check de NULL dans cJson_isString() on est pas obligé de le faire :
        if (!cJSON_IsString(nomPatientJson) || !cJSON_IsString(prenomPatientJson) || !cJSON_IsNumber(jourDatePatientJson)
            || !cJSON_IsNumber(moisDatePatientJson) || !cJSON_IsNumber(anneeDatePatientJson) ||!cJSON_IsString(mailPatientJson)
            || !cJSON_IsString(telPatientJson) || !cJSON_IsString(secuPatientJson))
        {
            //l'une des valeur lue n'est pas au format attendu : erreur
            printf("ListPatient_jsonLoad() : une des valeurs du Patient n'est pas au format attendu : return 0.\n");
            return 0;
        }
        Patient * patient = CreerPatient(nomPatientJson->valuestring, prenomPatientJson->valuestring, jourDatePatientJson->valueint,
                moisDatePatientJson->valueint, anneeDatePatientJson->valueint,
                mailPatientJson->valuestring, telPatientJson->valuestring, secuPatientJson->valuestring);

        ordonnancesPatientJson = cJSON_GetObjectItemCaseSensitive(projectJson, "ordonnances");
        cJSON_ArrayForEach(ordonnanceJson, ordonnancesPatientJson)
        {
            cJSON* IDmedecinJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "IDmedecin");

            cJSON* jourDateEditionOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "date_edition_jour");
            cJSON* moisDateEditionOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "date_edition_mois");
            cJSON* anneeDateEditionOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "date_edition_annee");

            cJSON* jourDateExpirationOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "date_expiration_jour");
            cJSON* moisDateExpirationOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "date_expiration_mois");
            cJSON* anneeDateExpirationOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "date_expiration_annee");

            cJSON* descriptionOrdonnanceJson = cJSON_GetObjectItemCaseSensitive(ordonnanceJson, "description");

            if (!cJSON_IsString(IDmedecinJson) || !cJSON_IsNumber(jourDateEditionOrdonnanceJson) || !cJSON_IsNumber(moisDateEditionOrdonnanceJson)
                || !cJSON_IsNumber(anneeDateEditionOrdonnanceJson) || !cJSON_IsNumber(jourDateExpirationOrdonnanceJson)
                || !cJSON_IsNumber(moisDateExpirationOrdonnanceJson) || !cJSON_IsNumber(anneeDateExpirationOrdonnanceJson)
                || !cJSON_IsString(descriptionOrdonnanceJson))
            {
                //l'une des valeur lue n'est pas au format attendu : erreur
                printf("ListPatient_jsonLoad() : une des valeurs d'une ordonnance' n'est pas au format attendu : return 0.\n");
                return 0;
            }

            Medecin* medecinOrdo = ListMedecin_seek(project_workingMedecins, IDmedecinJson->valuestring);
            if(medecinOrdo == NULL)
            {
                printf("ListPatient_jsonLoad() : On a pas trouvé le mèdecin d'une des ordonnances : return 0.\n");
                return 0;
            }

            Ordonnance* ordo = LoadOrdonnance(medecinOrdo, jourDateEditionOrdonnanceJson->valueint, moisDateEditionOrdonnanceJson->valueint,
                    anneeDateEditionOrdonnanceJson->valueint, jourDateExpirationOrdonnanceJson->valueint, moisDateExpirationOrdonnanceJson->valueint,
                    anneeDateExpirationOrdonnanceJson->valueint, descriptionOrdonnanceJson->valuestring);

            if(AddOrdonnanceDossierMedical(patient->dossierMedical, ordo) == -1)
            {
                printf("ListPatient_jsonLoad() : Echec (ordo NULL ou litsOrdo NULL) de l'ajout d'une ordonnance au dossier médical du patient %s %s.\n", patient->nom, patient->prenom);
                return 0;
            }
        }

        if(!ListPatient_add(lP, patient))
        {
            printf("ListPatient_jsonLoad() : Echec de l'ajout du patient %s %s à la liste.\n", patient->nom, patient->prenom);
            return 0;
        }

    }
    printf("ListPatient_jsonLoad() : normalement tous les patients et toutes leurs ordonnances ont bien été load.\n");
    return 1;
}
int Calendrier_jsonLoad(cJSON* projectJson, ListMedecin* lM, ListPatient* lP, Calendrier c){
    const cJSON* calendrierJson = NULL;
    const cJSON* rendezVousJason = NULL;

    calendrierJson = cJSON_GetObjectItemCaseSensitive(projectJson, "Hospital Calendar");
    cJSON_ArrayForEach(rendezVousJason, calendrierJson)
    {
        cJSON* jourDateRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "date_jour");
        cJSON* moisDateRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "date_mois");
        cJSON* anneeDateRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "date_annee");

        cJSON* heureDebutRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "heure_debut");
        cJSON* heureFinRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "heure_fin");

        cJSON* lieuRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "lieu");
        cJSON* IDpatientRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "patient");
        cJSON* IDmedecinRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "medecin");
        cJSON* motifRDVJson = cJSON_GetObjectItemCaseSensitive(rendezVousJason, "motif");

        if (   !cJSON_IsNumber(jourDateRDVJson)  || !cJSON_IsNumber(moisDateRDVJson)
            || !cJSON_IsNumber(anneeDateRDVJson) || !cJSON_IsNumber(heureDebutRDVJson)
            || !cJSON_IsNumber(heureFinRDVJson)  || !cJSON_IsString(lieuRDVJson)
            || !cJSON_IsString(IDpatientRDVJson) || !cJSON_IsString(IDmedecinRDVJson)
            || !cJSON_IsString(motifRDVJson))
        {
            //l'une des valeur lue n'est pas au format attendu : erreur
            printf("Calendrier_jsonLoad() : une des valeurs d'un rendezVous n'est pas au format attendu : return 0.\n");
            return 0;
        }

        //on cherche le patient et le mèdecin correspondant à ces ID avec Listpatient_seek(ListPatient* lP, char* IDPatient) et idem pour Mèdecin

        Patient* patientRDV = ListPatient_seek(lP, IDpatientRDVJson->valuestring);
        Medecin* medecinRDV = ListMedecin_seek(lM, IDmedecinRDVJson->valuestring);
        if(patientRDV == NULL || medecinRDV == NULL)
        {
            printf("Calendrier_jsonLoad() : On a pas trouvé le patient ou le mèdecin d'un des rendezVous : return 0.\n");
            return 0;
        }
        RendezVous* rdv = CreerRendezVous(anneeDateRDVJson->valueint, moisDateRDVJson->valueint, jourDateRDVJson->valueint,
                heureDebutRDVJson->valueint, 0, lieuRDVJson->valuestring, patientRDV, medecinRDV, motifRDVJson->valuestring);
        rdv->heure_fin = heureFinRDVJson->valueint; //C'est moche mais sinon c'est galère de re caster la diff entre les 2 heures en int pour la duree

        AddRendezVous_Calendrier(c,rdv);
    }
    return 0;
}
/**
 * Exemple de cJSON sur leur git
 */
int supports_full_hd(const char * const monitor)
{
    const cJSON *resolution = NULL;
    const cJSON *resolutions = NULL;
    const cJSON *name = NULL;
    int status = 0;
    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking monitor \"%s\"\n", name->valuestring);
    }

    resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
    cJSON_ArrayForEach(resolution, resolutions)
    {
        cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
        cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

        if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
        {
            status = 0;
            goto end;
        }

        if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
        {
            status = 1;
            goto end;
        }
    }

    end:
    cJSON_Delete(monitor_json);
    return status;
}
