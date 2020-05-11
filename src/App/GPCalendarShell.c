#include "GPCalendarShell.h"

/**********************************************************************************************************************/
                                            /*Fonctions de print*/
/**********************************************************************************************************************/

void printPossibleAction(){
    printf("\t- 1 : Créer un Patient\n");
    printf("\t- 2 : Créer un Médecin\n");
    printf("\t- 3 : Créer un Rendez-vous entre un Patient et un Médecin\n");
    printf("\t- 4 : Consulter les informations de l'Hôpital\n");
    printf("\t- 5 : Annuler un Rendez-vous\n");
    printf("\t- 6 : Supprimer un Patient de la liste de l'Hôpital\n");
    printf("\t- 7 : Supprimer un Médecin de la liste de l'Hôpital\n");
    printf("\t- 8 : Sauvegarder un Projet (Liste des Patients consultants, des Médecins travaillants et le calendrier de l'hôpital\n");
}

/**********************************************************************************************************************/
                                            /*Fonctions d'actions*/
/**********************************************************************************************************************/

void Shell_creerPatient(Project* project){

    char nomP[20];
    char prenomP[20];
    int jourP;
    int moisP;
    int anneeP;
    char mail[30];
    char tel[11];
    char secu[30];

    printf("Pour créer un patient vous avez besoin des informations suivantes :\n");
    printf("\tNom \t Prénom \t Date de Naissance (au format XX/XX/XXXX)\tAdresse Mail\tNuméro de Téléphone\tNuméro de sécurité sociale\n");
    printf("Veuillez donc rentrez, dans l'ordre et séparées par un espace, les informations du patient :\n");
    scanf("%s %s %d/%d/%d %s %s %s", nomP, prenomP, &jourP, &moisP, &anneeP, mail, tel, secu);
    Patient* p = CreerPatient(nomP, prenomP, anneeP, moisP, jourP, mail, tel, secu);

    char* infos = (char*) malloc(200);
    printPatient(infos, p);
    printf("%s",infos);
    free((void*) infos);

    if(ListPatient_add(project->consultingPatient, p) != -1){
        printf("Le patient \"%s %s\" a bien été ajouté à la liste des patients consultants de l'hôpital, vous "
               "pourrez accéder à ses informations à partir de son numéro de sécurité sociale.\n", nomP, prenomP);
    }
}
void Shell_creerMedecin(Project* project){

    char nomM[20];
    char prenomM[20];
    char mail[30];
    char tel[11];
    char rps[30];

    printf("Pour créer un médecin vous avez besoin des informations suivantes :\n");
    printf("\tNom \t Prénom \tAdresse Mail\tNuméro de Téléphone\t Numéro RPS\n");
    printf("Veuillez donc rentrez, dans l'ordre et séparées par un espace, les informations du médecin :\n");
    scanf("%s %s %s %s %s", nomM, prenomM, mail, tel, rps);
    Medecin* m = CreerMedecin(nomM, prenomM, mail, tel, rps);

    char* infos = (char*) malloc(200);
    getInfoMedecin(infos, m);
    printf("%s\n",infos);
    free((void*) infos);

    if(ListMedecin_add(project->workingMedecins, m) != -1){
        printf("Le medecin\"%s %s\" a bien été ajouté à la liste des médecins actifs de l'hôpital, vous "
               "pourrez accéder à ses informations à partir de son numéro RPS.\n", nomM, prenomM);
    }
}
void Shell_creerRendezVous(Project* project){
    int jourRdv;
    int moisRdv;
    int anneeRdv;
    float heure_debut;
    int duree;
    char lieu[30];
    char motif[100];
    char secuP[30];
    char rpsM[30];

    char addOrdonnance_ask[10];
    char descripionOrdo[200];
    char antecedent[200];

    printf("Pour créer un rendez-vous, vous avez besoin des informations suivantes :\n");
    printf("\t- Date (au format XX/XX/XXXX)\n\t- Heure de début (au format 16.5 pour 16h30 par exemple)\n\t- "
           "Durée (en min)\n\t- Lieu\n\t- Motif\n\t- Numéro de sécurité sociale du patient\n\t- Numéro RPS du mèdecin\n");
    printf("Veuillez donc rentrez, dans l'ordre et séparées par un espace, les informations du rendez-vous :\n");
    scanf("%d/%d/%d %f %d %s %s %s %s", &jourRdv, &moisRdv, &anneeRdv, &heure_debut, &duree, lieu, motif, secuP, rpsM);

    Patient* p = ListPatient_seek(project->consultingPatient, secuP);
    if(p == NULL){
        printf("Le patient au numéro de sécurité sociale \"%s\" ne fait pas partie de notre base de données, "
               "veuillez l'inscrire avant de mettre en place ce rendez-vous", secuP);
        return;
    }
    Medecin* m = ListMedecin_seek(project->workingMedecins, rpsM);
    if(m == NULL){
        printf("Le médecin au numéro RPS \"%s\" ne fait pas partie de notre base de données, "
               "veuillez l'inscrire avant de mettre en place ce rendez-vous", rpsM);
        return;
    }

    RendezVous* rdv = CreerRendezVous(anneeRdv, moisRdv, jourRdv, heure_debut, duree, lieu, p, m, motif);

    char* infos = (char*) malloc(200);
    getInfosRendezVous(infos, rdv);
    printf("%s",infos);
    free((void*) infos);

    if(AddRendezVous_Calendrier(project->calendrier, rdv)){
        printf("Le rendez-vous a bien été ajouté au calendrier de l'hôpital, vous "
               "pourrez le voir en affichant le calendrier.\n");
    }else{
        fprintf(stderr, "Erreur lors de l'ajout du rendez-vous au calendrier de l'hopital. RendezVous deleted.\n");
        FreeRendezVous(rdv);
        return;
    }

    AddMedecinConsultePatient(p, m);    //pas de cas d'erreur (le return 0 est uniquement dans le cas ou le patient connaissait déjà le medecin)
    AddPatientRecuMedecin(m, p);

    printf("Suite au rendez-vous, une ordonnance a pu être prescrite, souhaitez-vous l'ajouter, ainsi qu'un antécédent, au dossier médical du patient (\"yes\" ou \"no\")? :");
    scanf("%s", addOrdonnance_ask);
    if(strcmp(addOrdonnance_ask, "yes") == 0)
    {
        printf("Veuillez entrer la description de l'ordonnance : \n");
        scanf("%s", descripionOrdo);
        Ordonnance* ordo = CreerOrdonnance(m, descripionOrdo);
        if(AddOrdonnanceDossierMedical(p->dossierMedical, ordo) == -1)
        {
            fprintf(stderr, "Erreur lors de l'ajout de l'ordonnance au dossier médical.\n");
        }
    }
    else if(strcmp(addOrdonnance_ask, "no") == 0)
    {
        printf("Vous avez choisi de ne pas pas proscrire d'ordonnance après ce rendez-vous.\n");
    }else{
        fprintf(stderr, "Votre réponse ne fait pas partie de celles attendues, uune ordonnance ne sera pas proscrite.\n");
    }
    printf("Veuillez maintenant entrer un compte rendu de ce rendez-vous. Ce compte-rendu sera ajouté aux "
           "antécédents du patient et permettra un suivi plus précis de sa santé lors de ses prochaines consultations :\n");
    scanf("%s", antecedent);
    if(ListAntecedent_add(p->dossierMedical->antecedents, antecedent) == -1)
    {
        fprintf(stderr, "Erreur lors de l'ajout de l'antécédent au dossier médical.\n");
    }
    printf("Félicitations, vous avez créé un rendez-vous.\n");
}
void Shell_consulterInformations(Project* project){

    long infos_actions = -1;
    char infos_ask[10];
    char* infos_ask_tmp;

    printf("Quelles informations voulez-vous consulter ?\n");
    printf("\t- 1 : Liste des patients inscrits dans l'hôpital ;\n");
    printf("\t- 2 : Liste des médecins travaillants dans l'hôpital ;\n");
    printf("\t- 3 : Tout les rendez-vous de l'hôpital (calendrier) ;\n");
    printf("\t- 4 : L'entièreté du projet (patients, médecins et calendrier).\n");

    while (fgets(infos_ask, sizeof(infos_ask), stdin)) {
        infos_actions = strtol(infos_ask, &infos_ask_tmp, 10);
        if (infos_ask_tmp == infos_ask || *infos_ask_tmp != '\n')
        {
            printf("Veuillez entrer un chiffre : ");
        }
        else if (infos_actions < 1 || infos_actions > 4)
        {
            printf("Veuillez entrer un chiffre correspondant aux actions possibles : \n");
            printf("\t- 1 : Liste des patients inscrits dans l'hôpital ;\n");
            printf("\t- 2 : Liste des médecins travaillants dans l'hôpital ;\n");
            printf("\t- 3 : Tout les rendez-vous de l'hôpital (calendrier) ;\n");
            printf("\t- 4 : L'entièreté du projet (patients, médecins et calendrier).\n");
        }
        else break;
    }
    switch (infos_actions) {
        case 1:
            printf("********************Liste des patients inscrits dans l'hôpital**********************");
            printListPatient(project->consultingPatient);
            printf("************************************************************************************");
            break;
        case 2:
            printf("*******************Liste des médecins travaillants dans l'hôpital********************");
            printListMedecin(project->workingMedecins);
            printf("************************************************************************************");
            break;
        case 3:
            printCalendrier(project->calendrier);
            break;
        case 4:
            printProject(project);
            break;
        default:
            //Normalement on n'arrivera jamais ici puisque tout est déjà vérifier plus haut
            printf("Le chiffre que vous avez tapé ne fait pas parti des choix, que voulez-vous faire ?\n");
            break;
    }
}
void Shell_annulerRendezVous(Project* project){

}
void Shell_supprimerPatient(Project* project){

}
void Shell_supprimerMedecin(Project* project){

}
void Shell_saveProject(Project* project){

}
void Shell_loadProject(Project* project){

}

int main(int argc, char *argv[]){

    /**
     * Trucs qu'il faut changer :
     *  - Les scanf pour demander des infos (on vérifié pas le format des données)
     *
     * Idées d'amélioration :
     *  - mettre de la couleur (pour les questions ou autres, pour différencier les print de ce main ou les print des fonctions appellées)
     *  - implémenter un "help"
     *  - permettre de modifier les informations d'un mèdecin ou d'un patient
     */

    //Initialisation des variables

    //Variables nécessaires au load ou à la création d'un projet par l'utilisateur
    char GPCalendar_project_path[200];
    Project* current_project = NULL;
    char project_name[200];

    //Variables nécessaires au choix de l'action par l'utilisateur
    long GPCalendar_action = -1;
    char GPCalendar_ask[10];
    char* GPCalendar_ask_tmp;

    //Variables nécessaires au choix de quitter ou non l'application par l'utilisateur
    long GPCalendar_exit = -1;
    char GPCalendar_exit_ask[100];
    char* GPCalendar_exit_ask_tmp;

    char project_save_file_name[100];


    //Ouverture de l'appli
    printf("************************** GPCalendar_Shell ******************************\n");

    printf("\nBienvenue dans la version console de GPCalendar, souhaitez vous travailler avec un projet déjà existant ou souhaitez vous en créer un nouveau ?\n");
    printf("Entrez \"new\" pour créer un nouveau projet ou entrez directement le chemin absolu du fichier JSON correspondant à un projet précédemment suavegardé.\n");
    printf("Exemple : \"C:\\Documents\\YourProject.json\"\n");

    do{
        scanf("%s", GPCalendar_project_path);
        /* /home/cleonard/dev/C_Project/C_Project/cmake-build-debug/CefichierEstUnTestdeSaveGPCalendarJson.json */

        if(strcmp(GPCalendar_project_path, "new") == 0)
        {

            printf("Vous avez choisi de créer un nouveau projet, comment souhaitez vous l'appeller ? : ");
            scanf("%s", project_name);

            ListMedecin* project_workingMedecins = CreerListMedecin();
            ListPatient* project_consultingPatients = CreerListPatient();
            Calendrier project_calendrier = CreerCalendrier();

            current_project = CreerProject(project_name, project_workingMedecins, project_consultingPatients, project_calendrier);
            printf("Vous avez créé un nouveau projet \"%s\", vous allez maintenant pouvoir le manipuler.\n", project_name);
            printf("Si vous souhaitez travailler sur un autre projet, vous devrez fermer l'application et la réouvrir avec un autre projet.\n");
            break;
        }
        else
        {
            current_project = GPCalendar_loadProject(GPCalendar_project_path);
            if (current_project != NULL){
                printf("\nVous avez choisi de load le projet \"%s\", le voici :\n", current_project->nom);
                printProject(current_project);
            }else {
                printf("Le fichier est introuvable, veuillez entrez un chemin valide ou \"new\" pour créer un nouveau projet.\n");
            }
        }
    } while (current_project == NULL);

    printf("\nPour utiliser l'application vous devrez entrer "
           "des chiffres correspondants chacun à une action particulière :\n");
    printPossibleAction();

    //gestion de l'aide : [NOT IMPLEMENTED]
    printf("\nSi vous avez besoin d'aide à propos des commandes vous pouvez taper \"help\" à n'importe quel moment.[NOT IMPLEMENTED]\n\n");

    do
    {
        /**
         * Demande de l'action à l'utilisateur (utilisation de fgets et strtol)
         */
        printf("Que voulez-vous faire ? ");
        while (fgets(GPCalendar_ask, sizeof(GPCalendar_ask), stdin)) {
            GPCalendar_action = strtol(GPCalendar_ask, &GPCalendar_ask_tmp, 10);
            if (GPCalendar_ask_tmp == GPCalendar_ask || *GPCalendar_ask_tmp != '\n')
            {
                printf("Veuillez entrer un chiffre : ");
            }
            else if (GPCalendar_action < 1 || GPCalendar_action > 8)
            {
                printf("Veuillez entrer un chiffre correspondant aux actions possibles : \n");
                printPossibleAction();
            }
            else break;
        }
        /**
         * Switch case pour appeller la fonction correspondant à l'action demandée
         */
        switch (GPCalendar_action)
        {
            case 1:
                printf("Vous avez choisi de créer un Patient.\n");
                Shell_creerPatient(current_project);
                /* nomP prenomP 01/02/1234 mailP telP secuP */
                break;
            case 2:
                printf("Vous avez choisi de créer un Médecin.\n");
                Shell_creerMedecin(current_project);
                /* nomM prenomM mailM telM RPS */
                break;
            case 3:
                printf("Vous avez choisi de créer un Rendez-vous.\n");
                Shell_creerRendezVous(current_project);
                /* 11/11/1111 16.5 30 lieuRDV motifRDV secuP RPS */
                /* descriptionOrdonnanceRDV */
                /* compte-rendu du rdv (antécédent du patient) */
                break;
            case 4:
                printf("Vous avez choisi de consulter des informations.\n");
                Shell_consulterInformations(current_project);
                break;
            case 5:
                printf("Vous avez choisi d'annuler un Rendez-vous.\n");
                break;
            case 6:
                printf("Vous avez choisi de supprimer un Patient.\n");
                break;
            case 7:
                printf("Vous avez choisi de supprimer un Médecin.\n");
                break;
            case 8:
                printf("Vous avez choisi de sauvegarder le Projet actuel.\n");
                break;
            default :
                //Normalement on n'arrivera jamais ici puisque tout est déjà vérifier plus haut
                printf("Le chiffre que vous avez tapé ne fait pas parti des choix, que voulez-vous faire ?\n");
                break;
        }

        /**
         * On demande à l'utilisateur si il veut continuer à utiliser l'appli :
         *  - "yes" pour continuer
         *   - "no" pour arreter
         */
        printf("\nVoulez-vous continuez ? Entrez '1' si oui, '0' si non : ");
        while (fgets(GPCalendar_exit_ask, sizeof(GPCalendar_exit_ask), stdin)) {
            GPCalendar_exit = strtol(GPCalendar_exit_ask, &GPCalendar_exit_ask_tmp, 10);
            if (GPCalendar_exit_ask_tmp == GPCalendar_exit_ask || *GPCalendar_exit_ask_tmp != '\n')
            {
                printf("Veuillez entrer un chiffre : ");
            }
            else if (GPCalendar_exit < 0 || GPCalendar_exit > 1)
            {
                printf("Veuillez entrer un chiffre correspondant aux actions possibles : \n");
                printf("Entrez '1' si vous voulez continuer, '0' si vous souhaitez quitter l'application : ");
            }
            else
                break;
        }
    } while (GPCalendar_exit);

    printf("\nAvant de partir, souhaitez-vous enregistrer votre projet ? Si oui, entrez directement le chemin absolu avec le nom du fichier de sauvegarde JSON que vous souhaitez créer.\n");
    printf("Exemple : \"C:\\Documents\\NomDeMonFichierDeSauvegarde.json\".\n");
    printf("Et si vous ne souhaitez pas sauvegarder votre projet tapez simplement \"no\".\n");
    scanf("%s", project_save_file_name);
    /* /home/cleonard/dev/C_Project/C_Project/Test_GPCalendar_Shell1.json */
    if(strcmp(project_save_file_name, "no") == 0)
    {
        freeProject(current_project);
    }
    else{
        if(GPCalendar_saveProject(project_save_file_name, current_project) == 1){
            printf("Votre projet \"%s\" a bien été sauvegardé ici : \"%s\".\n", current_project->nom, project_save_file_name);
            freeProject(current_project);
        }else{
            printf("La sauvegarde du projet a échouée, le projet est tout de même supprimé pour des raisons de fuites mémoire.\n");
            freeProject(current_project);
        }
    }
    printf("Merci d'avoir utilisé notre application ;).\n");
    printf("\n************************** GPCalendar_Shell ******************************\n");
}