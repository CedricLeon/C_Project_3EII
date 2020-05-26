#include "GPCalendarShell.h"

/**********************************************************************************************************************/
                                            /*Fonctions de print*/
/**********************************************************************************************************************/
/**
 * printPossibleAction  :Affiche les actions disponibles dans le menu principal
 */
void printPossibleAction(){
    printf("\t- 1 : Créer un Patient\n");
    printf("\t- 2 : Créer un Médecin\n");
    printf("\t- 3 : Créer un Rendez-vous entre un Patient et un Médecin\n");
    printf("\t- 4 : Consulter les informations de l'Hôpital\n");
    printf("\t- 5 : Modifier des informations d'un Patient, d'un Médecin, d'une Ordonnance ou d'un Rendez-Vous'\n");
    printf("\t- 6 : Annuler un Rendez-vous\n");
    printf("\t- 7 : Supprimer un Patient de la liste de l'Hôpital\n");
    printf("\t- 8 : Supprimer un Médecin de la liste de l'Hôpital\n");
}

void checkHelpDisplayAction(char* ask){
    if(strcmp(ask, "help\n") == 0)
    {
        printPossibleAction();
    }
}
/**
 * checkQuit : check si l'utilisateur a rentré "quit"
 * @param ask : la chaîne de caractères checkées
 * @return 1 si l'utilisateur veut vraiment quitter
 *         0 sinon
 */
int checkQuit(char* ask){
    if(strcmp(ask, "quit\n") == 0)
    {
        char continue_ask[10];
        printf("Etes vous sûr de vouloir quitter ce que vous étiez en train de faire ? (\"yes\" / \"no\") : \n");
        scanf("%s", continue_ask);
        if(strcmp(continue_ask, "yes") == 0)
        {
            printf("Retour au menu précédent.\n");
            return 1;
        } else{
            printf("Vous n'avez pas quitté ce que vous étiez en train de faire.\n");
            return 0;
        }
    }
    return 0;
}

/**********************************************************************************************************************/
                                            /*Fonctions d'actions*/
/**********************************************************************************************************************/
/**
 * Shell_creerPatient : Crée un patient en demandant ses informations à l'utilisateur
 * @param project : le projet dans lequel est inscrit le patient
 */
void Shell_creerPatient(Project_GPCalendar* project){

    char nomP[50];
    char prenomP[50];
    int jourP;
    int moisP;
    int anneeP;
    char mail[50];
    char tel[50];
    char secu[50];

    printf("Pour créer un patient vous avez besoin des informations suivantes :\n");
    printf("\tNom \t Prénom \t Date de Naissance (au format XX/XX/XXXX)\tAdresse Mail\tNuméro de Téléphone\tNuméro de sécurité sociale\n");
    printf("Veuillez donc rentrez, dans l'ordre et séparées par un espace, les informations du patient :\n");
    scanf("%s %s %d/%d/%d %s %s %s", nomP, prenomP, &jourP, &moisP, &anneeP, mail, tel, secu);
    Patient* p = CreerPatient(nomP, prenomP, anneeP, moisP, jourP, mail, tel, secu);

    char* infos = (char*) malloc(200);
    printPatient(infos, p);
    printf("%s",infos);
    free((void*) infos);

    if(ListPatient_add(project->consultingPatient, p) != -1)
    {
        printf("Le patient \"%s %s\" a bien été ajouté à la liste des patients consultants de l'hôpital, vous "
               "pourrez accéder à ses informations à partir de son numéro de sécurité sociale.\n", nomP, prenomP);
    }
}
/**
 * Shell_creerMedecin : Crée un médecin en demandant ses informations à l'utilisateur
 * @param project : le projet dans lequel est inscrit le médecin
 */
void Shell_creerMedecin(Project_GPCalendar* project){

    char nomM[50];
    char prenomM[50];
    char mail[40];
    char tel[50];
    char rps[50];

    printf("Pour créer un médecin vous avez besoin des informations suivantes :\n");
    printf("\tNom \t Prénom \tAdresse Mail\tNuméro de Téléphone\t Numéro RPS\n");
    printf("Veuillez donc rentrez, dans l'ordre et séparées par un espace, les informations du médecin :\n");
    scanf("%s %s %s %s %s", nomM, prenomM, mail, tel, rps);
    Medecin* m = CreerMedecin(nomM, prenomM, mail, tel, rps);

    char* infos = (char*) malloc(200);
    getInfoMedecin(infos, m);
    printf("%s\n",infos);
    free((void*) infos);

    if(ListMedecin_add(project->workingMedecins, m) != -1)
    {
        printf("Le medecin\"%s %s\" a bien été ajouté à la liste des médecins actifs de l'hôpital, vous "
               "pourrez accéder à ses informations à partir de son numéro RPS.\n", nomM, prenomM);
    }
}
/**
 * Shell_creerRendezVous : Crée un rendez-Vous entre un patient et un médecin en demandant les informations à l'utilisateur
 * @param project : le projet dans lequel sera inscrit le rdv
 */
void Shell_creerRendezVous(Project_GPCalendar* project){
    int jourRdv;
    int moisRdv;
    int anneeRdv;
    float heure_debut;
    int duree;
    char lieu[30];
    char* motif = (char*) malloc(MAX_ORDO_DESCRIPTION_SIZE);
    char secuP[30];
    char rpsM[30];

    char addOrdonnance_ask[20];
    //char descripionOrdo[200];
    //char antecedent[200];

    printf("Pour créer un rendez-vous, vous avez besoin des informations suivantes :\n");
    printf("\t- Date (au format XX/XX/XXXX)\n\t- Heure de début (au format 16.5 pour 16h30 par exemple)\n\t- "
           "Durée (en min)\n\t- Lieu\n\t- Numéro de sécurité sociale du patient\n\t- Numéro RPS du mèdecin\n");
    printf("Veuillez donc rentrez, dans l'ordre et séparées par un espace, les informations du rendez-vous :\n");
    scanf("%d/%d/%d %f %d %s %s %s", &jourRdv, &moisRdv, &anneeRdv, &heure_debut, &duree, lieu, secuP, rpsM);

    printf("Veuillez maintenant entrer le motif de ce rendez-vous : ");
    fgets(motif, MAX_ORDO_DESCRIPTION_SIZE, stdin);
    fgets(motif, MAX_ORDO_DESCRIPTION_SIZE, stdin);
    if ((strlen(motif) > 0) && (motif[strlen (motif) - 1] == '\n'))  motif[strlen (motif) - 1] = '\0';

    Patient* p = ListPatient_seek(project->consultingPatient, secuP);
    if(p == NULL)
    {
        printf("Le patient au numéro de sécurité sociale \"%s\" ne fait pas partie de notre base de données, "
               "veuillez l'inscrire avant de mettre en place ce rendez-vous", secuP);
        free((void*) motif);
        return;
    }
    Medecin* m = ListMedecin_seek(project->workingMedecins, rpsM);
    if(m == NULL)
    {
        printf("Le médecin au numéro RPS \"%s\" ne fait pas partie de notre base de données, "
               "veuillez l'inscrire avant de mettre en place ce rendez-vous", rpsM);
        free((void*) motif);
        return;
    }

    RendezVous* rdv = CreerRendezVous(anneeRdv, moisRdv, jourRdv, heure_debut, duree, lieu, p, m, motif);
    free((void*) motif);
    //La patient est ajouté à la liste des patients recus du médecin et récipoquement dans la fonction CreerRendezVous

    if(!RendezVousValable(project->calendrier, rdv))
    {
        printf("Votre rendez-vous n'est pas valable, il ne peut pas être ajouté au calendrier de l'hôpital.\nRetour au menu principal\n");
        FreeRendezVous(rdv);
        return;

    }
    printf("Votre rendez-vous est valable (le créneau, la salle et le médecin sont libres), il va être ajouté au calendrier de l'hôpital.\n");
    char* infos = (char*) malloc(200);
    getInfosRendezVous(infos, rdv);
    printf("%s",infos);
    free((void*) infos);

    if(AddRendezVous_Calendrier(project->calendrier, rdv))
    {
        printf("Le rendez-vous a bien été ajouté au calendrier de l'hôpital, vous "
               "pourrez le voir en affichant le calendrier.\n");
    }
    else
    {
        fprintf(stderr, "Erreur lors de l'ajout du rendez-vous au calendrier de l'hopital. RendezVous deleted.\n");
        FreeRendezVous(rdv);
        return;
    }

    printf("Suite au rendez-vous, une ordonnance a pu être prescrite, souhaitez-vous l'ajouter, au dossier médical du patient (\"yes\" ou \"no\")? :\n");
    scanf("%s", addOrdonnance_ask);
    if(strcmp(addOrdonnance_ask, "yes") == 0)
    {
        char* descripionOrdo = (char*) malloc(MAX_ORDO_DESCRIPTION_SIZE);
        printf("Veuillez entrer la description de l'ordonnance : \n");
        //scanf("%s", descripionOrdo);
        fgets(descripionOrdo, MAX_ORDO_DESCRIPTION_SIZE, stdin);
        fgets(descripionOrdo, MAX_ORDO_DESCRIPTION_SIZE, stdin);

        if ((strlen(descripionOrdo) > 0) && (descripionOrdo[strlen (descripionOrdo) - 1] == '\n'))  descripionOrdo[strlen (descripionOrdo) - 1] = '\0';

        Ordonnance* ordo = CreerOrdonnance(m, descripionOrdo);
        free((void*) descripionOrdo);
        if(AddOrdonnanceDossierMedical(p->dossierMedical, ordo) == -1)
        {
            fprintf(stderr, "Erreur lors de l'ajout de l'ordonnance au dossier médical.\n");
        }
    }
    else if(strcmp(addOrdonnance_ask, "no") == 0)
    {
        printf("Vous avez choisi de ne pas pas proscrire d'ordonnance après ce rendez-vous.\n");
    }
    else
    {
        fprintf(stderr, "Votre réponse ne fait pas partie de celles attendues, par conséquent aucune ordonnance ne sera proscrite.\n");
    }


    char* antecedent = (char*) malloc(MAX_ANTECEDENT_SIZE);
    printf("Veuillez maintenant entrer un compte rendu de ce rendez-vous. Ce compte-rendu sera ajouté aux "
           "antécédents du patient et permettra un suivi plus précis de sa santé lors de ses prochaines consultations :\n");
    //scanf("%s", antecedent);
    fgets(antecedent, MAX_ANTECEDENT_SIZE, stdin);
    if ((strlen(antecedent) > 0) && (antecedent[strlen (antecedent) - 1] == '\n'))  antecedent[strlen (antecedent) - 1] = '\0';

    if(ListAntecedent_add(p->dossierMedical->antecedents, antecedent) == -1)
    {
        fprintf(stderr, "Erreur lors de l'ajout de l'antécédent au dossier médical.\n");
    }
    free((void*) antecedent);
    printf("Félicitations, vous avez créé un rendez-vous.\n");
}
/**
 * Shell_consulterInformations : permet à l'utilisateur de consulter les informations du projet sur lequel il travaille
 * @param project : le projet en question
 */
void Shell_consulterInformations(Project_GPCalendar* project){

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
            printf("Le chiffre que vous avez entré ne fait pas parti des choix, que voulez-vous faire ?\n");
            break;
    }
}
/**
 * Shell_modifierInformations : permet à l'utilisateur de venir modifier certaines informations des composants de son projet
 * @param project : le projet en question
 */
void Shell_modifierInformations(Project_GPCalendar* project){
    /**
     * Modifier :
     * - Un paramètre d'un patient
     * - Un paramètre d'un médecin
     * - Un rendezVous (motif, heure, date)
     * - Une ordonnance (Motif)
    */

    long GPCalendar_action = -1;
    char GPCalendar_ask[10];
    char* GPCalendar_ask_tmp;

    printf("Quelles informations souhaitez-vous modifier ?\n");
    printf("\t1 - une information d'un patient (nom, prenom, date_naissance, adresse_mail, telephone)\n");
    printf("\t2 - une information d'un médecin (nom, prenom, adresse_mail, telephone)\n");
    printf("\t3 - une information d'un rendez-vous (date, heure_debut, duree, lieu, motif)\n");
    printf("\t4 - une information d'une ordonnance (description, mise à jour des dates d'édition et d'expiration)\n");
    printf("Que voulez-vous faire ? Si vous souhaitez quitter vous pouvez entrer \"0\" :");
    while (fgets(GPCalendar_ask, sizeof(GPCalendar_ask), stdin)) {
        GPCalendar_action = strtol(GPCalendar_ask, &GPCalendar_ask_tmp, 10);
        if (GPCalendar_ask_tmp == GPCalendar_ask || *GPCalendar_ask_tmp != '\n')
        {
            printf("Veuillez entrer un chiffre : ");
        }
        else if (GPCalendar_action < 0 || GPCalendar_action > 5)
        {
            printf("Veuillez entrer un chiffre correspondant aux actions possibles : \n");
        }
        else break;
    }
    switch (GPCalendar_action)
    {
        case 0:
            printf("Vous avez choisi de quitter le menu de modification.\nRetour au menu principal.\n");
            return;
        case 1:
            printf("Vous avez choisi de modifier un Patient.\n");
            Shell_modifierPatient(project);
            break;
        case 2:
            printf("Vous avez choisi de modifier un Médecin.\n");
            Shell_modifierMedecin(project);
            break;
        case 3:
            printf("Vous avez choisi de modifier un Rendez-vous.\n");
            printf(" /!\\ Attention, vous ne pourrez pas modifier les informations d'un rendez-vous passé !\n\n");
            Shell_modifierRendezVous(project);
            break;
        case 4:
            printf("Vous avez choisi de modifier une Ordonnance.\n");
            Shell_modifierOrdonnance(project);
            break;
        default :
            //Normalement on n'arrivera jamais ici puisque tout est déjà vérifié plus haut
            printf("Le chiffre que vous avez entré ne fait pas partie des choix, que voulez-vous faire ?\n");
            break;
    }
}

void Shell_modifierPatient(Project_GPCalendar* project){
    int while_ask = 0;
    char IDPatient[100];
    char continue_ask[10];
    char GPCalendar_ask[50];
    printf("Voici la liste des patients actuellement inscrits dans l'hôpital :\n");
    printListPatient(project->consultingPatient);
    printf("Veuillez entrer le numéro de sécurité sociale du patient que vous souhaitez modifier :\n");
    scanf("%s", IDPatient);
    printf("\n");
    Patient* p = ListPatient_seek(project->consultingPatient, IDPatient);

    char* infosPatient = (char*) malloc(sizeof(char) * 5000);
    printPatient(infosPatient, p);
    printf("%s\n", infosPatient);
    free((void*) infosPatient);

    printf("Ce patient est-il celui que vous voulez modifier ? (\"yes\" ou \"no\") :");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
    {
        printf("Vous avez choisi d'arrêtez.\nRetour au menu principal.\n");
        return;
    }

    printf("\nVous pouvez modifier l'un des paramètres suivants : nom, prenom, date_naissance, adresse_mail, telephone. Pour ce faire, tapez simplement le nom du paramètre : \n");
    do
    {
        scanf("%s", GPCalendar_ask);
        if (strcmp(GPCalendar_ask, "nom") == 0)
        {
            char new_nom[50];
            printf("Vous souhaitez donc renommer le patient \"%s %s\", quel est son nouveau nom ?\n", p->nom, p->prenom);
            scanf("%s", new_nom);
            free((void *) p->nom);
            p->nom = (char*) malloc(strlen(new_nom)+1);
            strcpy(p->nom, new_nom);
            printf("Ce patient s'appelle donc désormais : \"%s %s\".\nRetour au menu principal.\n", p->nom, p->prenom);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "prenom") == 0)
        {
            char new_prenom[50];
            printf("Vous souhaitez donc renommer le patient \"%s %s\", quel est son nouveau prénom ?\n", p->nom, p->prenom);
            scanf("%s", new_prenom);
            free((void *) p->prenom);
            p->prenom = (char*) malloc(strlen(new_prenom)+1);
            strcpy(p->prenom, new_prenom);
            printf("Ce patient s'appelle donc désormais : \"%s %s\".\nRetour au menu principal.\n", p->nom, p->prenom);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "date_naissance") == 0)
        {
            int new_jour;
            int new_mois;
            int new_annee;
            char old_date[50];
            getInfosDate(old_date, p->date_naissance);
            printf("Vous souhaitez modifier la date de naissance du patient \"%s %s\", né le %s.\n", p->nom, p->prenom, old_date);
            printf("veuillez donc entrer sa nouvelle date de naissance au format \"XX/XX/XXXX\" : \n");
            scanf("%d/%d/%d", &new_jour, &new_mois, &new_annee);
            FreeDate(p->date_naissance);
            p->date_naissance = CreerDate(new_annee, new_mois, new_jour);
            getInfosDate(old_date, p->date_naissance);
            printf("Le patient \"%s %s\" est maintenant né le %s.\nRetour au menu principal.\n", p->nom, p->prenom, old_date);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "adresse_mail") == 0)
        {
            char new_mail[50];
            printf("Vous souhaitez donc modifier l'adresse mail du patient \"%s %s\", anciennement joignable à l'adresse mail : \"%s\". Quel est sa nouvelle adresse mail ?\n", p->nom, p->prenom, p->adresse_mail);
            scanf("%s", new_mail);
            free((void *) p->adresse_mail);
            p->adresse_mail = (char*) malloc(strlen(new_mail)+1);
            strcpy(p->adresse_mail, new_mail);
            printf("Ce patient \"%s %s\" est donc désormais joignable à l'adresse mail suivante : \"%s\".\nRetour au menu principal.\n", p->nom, p->prenom, p->adresse_mail);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "telephone") == 0)
        {
            char new_tel[50];
            printf("Vous souhaitez donc modifier le numéro de téléphone du patient \"%s %s\", anciennement joignable au  \"%s\". Quel est son nouveau numéro de téléphone ?\n", p->nom, p->prenom, p->numero_telephone);
            scanf("%s", new_tel);
            free((void *) p->numero_telephone);
            p->numero_telephone = (char*) malloc(strlen(new_tel)+1);
            strcpy(p->numero_telephone, new_tel);
            printf("Ce patient \"%s %s\" est donc désormais joignable au : \"%s\".\nRetour au menu principal.\n", p->nom, p->prenom, p->numero_telephone);
            while_ask = 0;
        }else if (strcmp(GPCalendar_ask, "quit") == 0)
        {
            printf("Vous avez choisi de quitter le menu de modification des paramètres du patient \"%s %s\".\nRetour au menu principal.\n", p->nom, p->prenom);
            while_ask = 0;
        }
        else
        {
            printf("Vous devez entrer l'un des paramètres spécifiés. Si vous souhaitez quitter ce menu entrez \"quit\" : \n");
            while_ask = 1;
        }
    }while(while_ask);
}
void Shell_modifierMedecin(Project_GPCalendar* project){
    int while_ask = 0;
    char IDMedecin[100];
    char continue_ask[10];
    char GPCalendar_ask[50];
    printf("Voici la liste des médecins actuellement inscrits dans l'hôpital :\n");
    printListMedecin(project->workingMedecins);
    printf("Veuillez entrer le numéro RPPS du patient que vous souhaitez modifier :\n");
    scanf("%s", IDMedecin);
    printf("\n");
    Medecin* m = ListMedecin_seek(project->workingMedecins, IDMedecin);

    char* infosMedecin = (char*) malloc(sizeof(char) * 5000);
    getInfoMedecin(infosMedecin, m);
    printf("%s\n", infosMedecin);
    free((void*) infosMedecin);

    printf("\nCe médecin est-il celui que vous voulez modifier ? (\"yes\" ou \"no\") :");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
    {
        printf("Vous avez choisi d'arrêtez.\nRetour au menu principal.\n");
        return;
    }

    printf("\nVous pouvez modifier l'un des paramètres suivants : nom, prenom, adresse_mail, telephone. Pour ce faire, tapez simplement le nom du paramètre : \n");
    do
    {
        scanf("%s", GPCalendar_ask);
        if (strcmp(GPCalendar_ask, "nom") == 0)
        {
            char new_nom[50];
            printf("Vous souhaitez donc renommer le médecin \"%s %s\", quel est son nouveau nom ?\n", m->nom, m->prenom);
            scanf("%s", new_nom);
            free((void *) m->nom);
            m->nom = (char*) malloc(strlen(new_nom)+1);
            strcpy(m->nom, new_nom);
            printf("Ce médecin s'appelle donc désormais : \"%s %s\".\nRetour au menu principal.\n", m->nom, m->prenom);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "prenom") == 0)
        {
            char new_prenom[50];
            printf("Vous souhaitez donc renommer le médecin \"%s %s\", quel est son nouveau prénom ?\n", m->nom, m->prenom);
            scanf("%s", new_prenom);
            free((void *) m->prenom);
            m->prenom = (char*) malloc(strlen(new_prenom)+1);
            strcpy(m->prenom, new_prenom);
            printf("Ce médecin s'appelle donc désormais : \"%s %s\".\nRetour au menu principal.\n", m->nom, m->prenom);
            while_ask = 0;
        }else if (strcmp(GPCalendar_ask, "adresse_mail") == 0)
        {
            char new_mail[50];
            printf("Vous souhaitez donc modifier l'adresse mail du médecin \"%s %s\", anciennement joignable à l'adresse mail : \"%s\". Quel est sa nouvelle adresse mail ?\n", m->nom, m->prenom, m->adresse_mail);
            scanf("%s", new_mail);
            free((void *) m->adresse_mail);
            m->adresse_mail = (char*) malloc(strlen(new_mail)+1);
            strcpy(m->adresse_mail, new_mail);
            printf("Ce médecin \"%s %s\" est donc désormais joignable à l'adresse mail suivante : \"%s\".\nRetour au menu principal.\n", m->nom, m->prenom, m->adresse_mail);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "telephone") == 0)
        {
            char new_tel[50];
            printf("Vous souhaitez donc modifier le numéro de téléphone du médecin \"%s %s\", anciennement joignable au  \"%s\". Quel est son nouveau numéro de téléphone ?\n", m->nom, m->prenom, m->numero_telephone);
            scanf("%s", new_tel);
            free((void *) m->numero_telephone);
            m->numero_telephone = (char*) malloc(strlen(new_tel)+1);
            strcpy(m->numero_telephone, new_tel);
            printf("Ce médecin \"%s %s\" est donc désormais joignable au : \"%s\".\nRetour au menu principal.\n", m->nom, m->prenom, m->numero_telephone);
            while_ask = 0;
        }else if (strcmp(GPCalendar_ask, "quit") == 0)
        {
            printf("Vous avez choisi de quitter le menu de modification des paramètres du médecin \"%s %s\".\nRetour au menu principal.\n", m->nom, m->prenom);
            while_ask = 0;
        }
        else
        {
            printf("Vous devez entrer l'un des paramètres spécifiés. Si vous souhaitez quitter ce menu entrez \"quit\" : \n");
            while_ask = 1;
        }
    }while(while_ask);
}

RendezVous* Shell_chercherRendezVous(Project_GPCalendar* project){
    int annee_ask;
    int mois_ask;
    int jour_ask;
    float heure_ask;
    printf("Veuillez dans un premier temps entrer l'année de la date du rendez-vous que nous cherchons : ");
    scanf("%d", &annee_ask);
    Annee anneeRdv = Annee_existe(project->calendrier, annee_ask);
    if (anneeRdv == NULL)
    {
        printf("\nAucun rendez-vous n'a été organisé pour cette année. Retour au menu principal.\n");
        return NULL;
    }
    printf("Veuillez maintenant entrer le mois de ce rendez-vous : ");
    scanf("%d", &mois_ask);
    Mois moisRdv = Mois_existe(anneeRdv, mois_ask);
    if (moisRdv == NULL)
    {
        printf("\nAucun rendez-vous n'a été organisé pour ce mois. Retour au menu principal.\n");
        return NULL;
    }
    printf("Enfin veuillez entrer le jour de ce rendez-vous : ");
    scanf("%d", &jour_ask);
    Date* date_rdv_cherche = CreerDate(annee_ask, mois_ask, jour_ask);
    Jour jourRdv = Jour_existe(moisRdv, date_rdv_cherche);
    FreeDate(date_rdv_cherche);
    if (jourRdv == NULL)
    {
        printf("\nAucun rendez-vous n'a été organisé pour ce jour. Retour au menu principal.\n");
        return NULL;
    }
    printf("Voici la liste de rendez-vous de ce jour : \n\n");
    for(ListRendezVous_setOnFirst(jourRdv); !ListRendezVous_isOutOfList(jourRdv); ListRendezVous_setOnNext(jourRdv))
    {
        RendezVous* rdv = ListRendezVous_getCurrent(jourRdv);
        printf("\t- De %2.1fh à %2.1fh entre le patient \"%s %s\" et le médecin \"%s %s\".\n",
               rdv->heure_debut, rdv->heure_fin, rdv->patient->nom, rdv->patient->prenom, rdv->medecin->nom, rdv->medecin->prenom);
    }
    printf("\nPour sélectionner le Rendez-Vous que nous cherchons veuillez entrer son heure.\n"
           "Si le rendez-vous que nous cherchons ne fait pas partie de la liste, vous pouvez quitter en tapant : \"-1\" : ");
    scanf("%f", &heure_ask);
    if(heure_ask == -1)
    {
        printf("Retour au menu principal.\n");
        return NULL;
    }
    RendezVous* rdv_cherche = NULL;
    for(ListRendezVous_setOnFirst(jourRdv); !ListRendezVous_isOutOfList(jourRdv); ListRendezVous_setOnNext(jourRdv))
    {
        RendezVous* tmp = ListRendezVous_getCurrent(jourRdv);
        if((int) tmp->heure_debut == (int) heure_ask)
        {
            rdv_cherche = tmp;
            break;
        }
    }
    if(rdv_cherche == NULL)
    {
        printf("Le rendez-vous que nous cherchions n'a pas été trouvé, veuillez réessayer. Retour au menu principal.\n");
        return NULL;
    }
    Date* date_courante = CreerDateCourante();
    if (date_courante->annee > rdv_cherche->date->annee)
    {
        FreeDate(date_courante);
        return NULL;
    }
    if((date_courante->annee == rdv_cherche->date->annee) && (date_courante->mois > rdv_cherche->date->mois))
    {
        FreeDate(date_courante);
        return NULL;
    }
    if((date_courante->annee == rdv_cherche->date->annee) && (date_courante->mois == rdv_cherche->date->mois) && (date_courante->jour > rdv_cherche->date->jour))
    {
        FreeDate(date_courante);
        return NULL;
    }
    FreeDate(date_courante);
    return rdv_cherche;
}

void Shell_modifierRendezVous(Project_GPCalendar* project){
    char GPCalendar_ask[50];
    int while_ask = 0;

    printf("Nous allons d'abord chercher quel rendez-vous vous souhaitez modifier.\n");
    RendezVous* rdv_cherche = Shell_chercherRendezVous(project);
    if(rdv_cherche == NULL)
    {
        printf("Le rendez-vous que vous souhaitiez modifier n'a pas été trouvé ou est passé (ce qui implique qu'on ne peut plus le modifier), veuillez réessayer. Retour au menu principal.\n");
        return;
    }
    char* infos_rdv = (char*) malloc(200);
    getInfosRendezVous(infos_rdv, rdv_cherche);
    printf("Le rendez-vous que vous souhaitez modifier a bien été identifié : \n\n%s", infos_rdv);
    free((void*) infos_rdv);
    printf("Vous pouvez modifier les informations suivantes : date, heure_debut, duree, lieu, motif. Pour ce faire, tapez simplement le nom du paramètre : \n");
    do
    {
        scanf("%s", GPCalendar_ask);
        if (strcmp(GPCalendar_ask, "date") == 0)
        {
            int new_jour;
            int new_mois;
            int new_annee;
            char old_date[50];
            char new_date[50];
            getInfosDate(old_date, rdv_cherche->date);
            printf("Vous souhaitez modifier la date du rendez-vous prévu le %s à %2.1fh.", old_date, rdv_cherche->heure_debut);
            printf("Veuillez donc entrer une nouvelle date pour ce rendez-vous, au format \"XX/XX/XXXX\" : \n");
            scanf("%d/%d/%d", &new_jour, &new_mois, &new_annee);
            RendezVous* new_rdv = CreerRendezVous(new_annee, new_mois, new_jour, rdv_cherche->heure_debut,
                    rdv_cherche->heure_fin - rdv_cherche->heure_debut, rdv_cherche->lieu, rdv_cherche->patient,
                    rdv_cherche->medecin, rdv_cherche->motif);
            getInfosDate(new_date, new_rdv->date);
            if(!RendezVousValable(project->calendrier, new_rdv))
            {
                printf("Déplacer le rendez-vous du %s à %2.1fh au %s à %2.1fh n'est pas possible.\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut, new_date, new_rdv->heure_debut);
                FreeRendezVous(new_rdv);
                return;
            }
            if(!AnnulerRendezVous(project->calendrier, rdv_cherche))
            {
                printf("Déplacer le rendez-vous du %s à %2.1fh au %s à %2.1fh n'est pas possible.\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut, new_date, new_rdv->heure_debut);
                FreeRendezVous(new_rdv);
                return;
            }
            printf("Déplacer le rendez-vous du %s à %2.1fh au %s à %2.1fh est possible. Déplacement du rendez-vous.\n", old_date, rdv_cherche->heure_debut, new_date, new_rdv->heure_debut);
            AddRendezVous_Calendrier(project->calendrier, new_rdv);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "heure_debut") == 0)
        {
            float new_heure;
            char old_date[50];
            getInfosDate(old_date, rdv_cherche->date);
            printf("Vous souhaitez modifier le rendez-vous du %s à %2.1fh.\n", old_date, rdv_cherche->heure_debut);
            printf("Veuillez donc entrer une nouvelle heure de début pour ce rendez-vous, au format \"XX.X\" (exemple : 21h30 = \"21.5\") : \n");
            scanf("%f", &new_heure);
            RendezVous* new_rdv = CreerRendezVous(rdv_cherche->date->annee, rdv_cherche->date->mois, rdv_cherche->date->jour, new_heure,
                                                  rdv_cherche->heure_fin - rdv_cherche->heure_debut, rdv_cherche->lieu, rdv_cherche->patient,
                                                  rdv_cherche->medecin, rdv_cherche->motif);
            /* DOUILLE */
            double old_heure = rdv_cherche->heure_debut;
            if(!AnnulerRendezVous(project->calendrier, rdv_cherche))
            {
                printf("Déplacer le rendez-vous du %s à %2.1fh au %s à %2.1fh n'est pas possible.\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut, old_date, new_rdv->heure_debut);
                FreeRendezVous(new_rdv);
                return;
            }
            if(!RendezVousValable(project->calendrier, new_rdv))
            {
                printf("Déplacer le rendez-vous du %s à %2.1fh au %s à %2.1fh n'est pas possible.\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut, old_date, new_rdv->heure_debut);
                RendezVous* restauration_ancien_rdv = CreerRendezVous(rdv_cherche->date->annee, rdv_cherche->date->mois, rdv_cherche->date->jour, old_heure,
                                                                      (rdv_cherche->heure_fin - rdv_cherche->heure_debut) * 60, rdv_cherche->lieu, rdv_cherche->patient, rdv_cherche->medecin, rdv_cherche->motif);
                AddRendezVous_Calendrier(project->calendrier, restauration_ancien_rdv);
                FreeRendezVous(new_rdv);
                return;
            }
            printf("Déplacer le rendez-vous du %s à %2.1fh au %s à %2.1fh est possible. Déplacement du rendez-vous.\n", old_date, old_heure, old_date, new_rdv->heure_debut);
            AddRendezVous_Calendrier(project->calendrier, new_rdv);
            while_ask = 0;
        }else if (strcmp(GPCalendar_ask, "duree") == 0)
        {
            float new_duree;
            char old_date[50];
            getInfosDate(old_date, rdv_cherche->date);
            printf("Vous souhaitez modifier le rendez-vous du %s à %2.1fh.\n", old_date, rdv_cherche->heure_debut);
            printf("Veuillez donc entrer une nouvelle durée pour ce rendez-vous, en minutes (exemple : pour un rendez-vous de 1h30, \"90\") : \n");
            scanf("%f", &new_duree);
            RendezVous* new_rdv = CreerRendezVous(rdv_cherche->date->annee, rdv_cherche->date->mois, rdv_cherche->date->jour, rdv_cherche->heure_debut,
                                                  new_duree, rdv_cherche->lieu, rdv_cherche->patient, rdv_cherche->medecin, rdv_cherche->motif);
            /* DOUILLE */
            double old_duree = rdv_cherche->heure_fin - rdv_cherche->heure_debut;
            if(!AnnulerRendezVous(project->calendrier, rdv_cherche))
            {
                printf("Déplacer le rendez-vous du %s de %2.1fh à %2.1fh au %s de %2.1fh à %2.1fh n'est pas possible.\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut,
                       rdv_cherche->heure_fin, old_date, new_rdv->heure_debut, new_rdv->heure_fin);
                FreeRendezVous(new_rdv);
                return;
            }
            if(!RendezVousValable(project->calendrier, new_rdv))
            {
                printf("Déplacer le rendez-vous du %s de %2.1fh à %2.1fh au %s de %2.1fh à %2.1fh n'est pas possible.\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut,
                        rdv_cherche->heure_fin, old_date, new_rdv->heure_debut, new_rdv->heure_fin);
                RendezVous* restauration_ancien_rdv = CreerRendezVous(rdv_cherche->date->annee, rdv_cherche->date->mois, rdv_cherche->date->jour, rdv_cherche->heure_debut,
                                                                      old_duree, rdv_cherche->lieu, rdv_cherche->patient, rdv_cherche->medecin, rdv_cherche->motif);
                AddRendezVous_Calendrier(project->calendrier, restauration_ancien_rdv);
                FreeRendezVous(new_rdv);
                return;
            }
            printf("Déplacer le rendez-vous du %s qui durait %f minutes au %s de %2.1fh à %2.1fh est possible. Déplacement du rendez-vous.\n", old_date, old_duree, old_date, new_rdv->heure_debut, new_rdv->heure_fin);
            AddRendezVous_Calendrier(project->calendrier, new_rdv);
            while_ask = 0;
        } else if (strcmp(GPCalendar_ask, "lieu") == 0)
        {
            char new_lieu[50];
            char old_date[50];
            getInfosDate(old_date, rdv_cherche->date);
            printf("Vous souhaitez donc modifier le lieu du rendez-vous du %s à %2.1fh, anciennement prévu au lieu suivant : \"%s\". Quel est son nouveau lieu ?\n", old_date, rdv_cherche->heure_debut, rdv_cherche->lieu);
            scanf("%s", new_lieu);
            free((void *) rdv_cherche->lieu);
            rdv_cherche->lieu = (char*) malloc(strlen(new_lieu)+1);
            strcpy(rdv_cherche->lieu, new_lieu);
            printf("Le rendez-vous du %s à %2.1fh aura donc lieu ici : \"%s\".\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut, rdv_cherche->lieu);
            while_ask = 0;
        }else if (strcmp(GPCalendar_ask, "motif") == 0)
        {
            char new_motif[50];
            char old_date[50];
            getInfosDate(old_date, rdv_cherche->date);
            printf("Vous souhaitez donc modifier le motif du rendez-vous du %s à %2.1fh, anciennement prévu pour le motif suivant : \"%s\". Quel est son nouveau motif ?\n", old_date, rdv_cherche->heure_debut, rdv_cherche->motif);
            scanf("%s", new_motif);
            free((void *) rdv_cherche->motif);
            rdv_cherche->motif = (char*) malloc(strlen(new_motif)+1);
            strcpy(rdv_cherche->motif, new_motif);
            printf("Le rendez-vous du %s à %2.1fh aura donc pour le motif suivant : \"%s\".\nRetour au menu principal.\n", old_date, rdv_cherche->heure_debut, rdv_cherche->motif);
            while_ask = 0;
        }else if (strcmp(GPCalendar_ask, "quit") == 0)
        {
            char old_date[50];
            getInfosDate(old_date, rdv_cherche->date);
            printf("Vous avez choisi de quitter le menu de modification du rendez-vous du %s à %2.1fh.\nRetour au menu principal.\n",  old_date, rdv_cherche->heure_debut);
            while_ask = 0;
        }
        else
        {
            printf("Vous devez entrer l'un des paramètres spécifiés. Si vous souhaitez quitter ce menu entrez \"quit\" : \n");
            while_ask = 1;
        }
    }while(while_ask);
}
void Shell_modifierOrdonnance(Project_GPCalendar* project){
    char ID_patient[50];
    char continue_ask[20];
    int annee_ask;
    int mois_ask;
    int jour_ask;
    char ID_medecin[50];
    char update_date_ask[20];

    printf("De quel patient souhaitez-vous modifier une ordonannce ?\n");
    printf("Veuillez entrer le numéro de sécurité sociale de ce patient : ");
    scanf("%s", ID_patient);
    Patient* p = ListPatient_seek(project->consultingPatient, ID_patient);
    if(p == NULL)
    {
        printf("Le patient au numéro de sécurité sociale \"%s\" ne fait pas partie de notre base de données.\n"
               "Retour au menu principal.\n", ID_patient);
        return;
    }
    char* infosPatient = (char*) malloc(1000);
    printPatient(infosPatient, p);
    printf("\n%s\n", infosPatient);
    free((void*) infosPatient);
    printf("Ce patient est-il celui dont vous souhaitez modifier une ordonnnance ? (\"yes\" ou \"no\") : ");
    scanf("%s", continue_ask);
    if(strcmp(continue_ask, "yes") != 0)
    {
        printf("Vous n'avez pas identifié le patient dont vous souhaitiez modifier l'une des ordonnnances.\nRetour au menu principal.\n");
        return;
    }
    printf("Pour identifier précisement l'ordonnance à modifier, veuillez dans un premier temps entrer l'année de la date d'édition de l'ordonnance : ");
    scanf("%d", &annee_ask);
    printf("Veuillez maintenant entrer le mois de cette même date d'édition : ");
    scanf("%d", &mois_ask);
    printf("Et enfin, veuillez entrer le jour de cette date : ");
    scanf("%d", &jour_ask);
    Date* date_ordo_cherche = CreerDate(annee_ask, mois_ask, jour_ask);
    ListOrdonnance* lO = p->dossierMedical->ordonnances;
    int nb_ordo = 0;
    for(ListOrdonnance_setOnFirst(lO); !ListOrdonnance_isOutOfList(lO); ListOrdonnance_setOnNext(lO))
    {
        Ordonnance* ordo = ListOrdonnance_getCurrent(lO);
        if(DateEgales(date_ordo_cherche, ordo->date_edition))
        {
            char date_ordo[20];
            getInfosDate(date_ordo, ordo->date_edition);
            printf("\t- Ordonnance du %s faite par le médecin \"%s %s\" (N° RPPS : \"%s\") ayant pour description : \"%s\".\n", date_ordo,
                    ordo->medecin->nom, ordo->medecin->prenom, ordo->medecin->numero_RPS, ordo->description);
            nb_ordo ++;
        }
    }
    if(nb_ordo == 0)
    {
        char date_entree[20];
        getInfosDate(date_entree, date_ordo_cherche);
        FreeDate(date_ordo_cherche);
        printf("Aucune ordonnance ne correspond à cette date : %s.\nretour au menu principal.\n", date_entree);
        return;
    }
    printf("Veuillez finalement entrer le numéro RPPS du médecin ayant prescrit l'ordonnance : ");
    scanf("%s", ID_medecin);
    Ordonnance* ordo_modifier = NULL;
    for(ListOrdonnance_setOnFirst(lO); !ListOrdonnance_isOutOfList(lO); ListOrdonnance_setOnNext(lO))
    {
        Ordonnance* ordo = ListOrdonnance_getCurrent(lO);
        if(DateEgales(date_ordo_cherche, ordo->date_edition))
        {
            if(strcmp(ID_medecin, ordo->medecin->numero_RPS) == 0)
            {
                ordo_modifier = ordo;
                break;
            }
        }
    }
    FreeDate(date_ordo_cherche);
    if(ordo_modifier == NULL)
    {
        printf("Aucune ordonnances du patient \"%s %s\" ne correspond aux critères entrés.\nRetour au menu principal.\n", p->nom, p->prenom);
        return;
    }
    printf("L'ordonnance que vous souhaitez modifier est donc la suivante : \n");
    char* infosOrdo = (char*) malloc(200);
    strcpy(infosOrdo, "\n\t\t");
    printOrdonnance(infosOrdo, ordo_modifier);
    printf("%s\n", infosOrdo);
    free((void*) infosOrdo);
    printf("Veuillez maintenant entrer la nouvelle description de cette ordonnance.\n"
           "Vous pourrez ensuite mettre à jour sa date d'édition (et donc celle d'expiration également) : ");

    char* descripionOrdo = (char*) malloc(MAX_ORDO_DESCRIPTION_SIZE);
    fgets(descripionOrdo, MAX_ORDO_DESCRIPTION_SIZE, stdin);
    fgets(descripionOrdo, MAX_ORDO_DESCRIPTION_SIZE, stdin);
    if ((strlen(descripionOrdo) > 0) && (descripionOrdo[strlen (descripionOrdo) - 1] == '\n'))  descripionOrdo[strlen (descripionOrdo) - 1] = '\0';
    free((void*) ordo_modifier->description);
    ordo_modifier->description = (char*) malloc(strlen(descripionOrdo)+1);
    strcpy(ordo_modifier->description, descripionOrdo);
    free((void*) descripionOrdo);

    Date* date_courante = CreerDateCourante();
    char date_ordo[20];
    getInfosDate(date_ordo, date_courante);
    printf("Voulez-vous maintenant mettre à jour la date d'édition de cette ordonnance modifiée ? (\"yes\" ou \"no\") :\n");
    printf("Si vous le faîtes cette dernière sera modifiée en la date courante (nous sommes le %s) et la date d'expiration de l'ordonnance aura lieu 3 mois plus tard.\n", date_ordo);
    scanf("%s", update_date_ask);
    if(strcmp(update_date_ask, "yes") != 0)
    {
        printf("Vous avez choisi de ne pas update les dates de l'ordonannce.\nRetour au menu principal.\n");
        FreeDate(date_courante);
        return;
    }
    FreeDate(ordo_modifier->date_edition);
    ordo_modifier->date_edition = date_courante;
    FreeDate(ordo_modifier->date_expiration);
    ordo_modifier->date_expiration = AjoutMoisDate(date_courante, 3);
    printf("Vous avez fini de modifier votre ordonnance.\nRetour au menu principal.\n");
}

/**
 * Shell_annulerRendezVous : Permet d'annuler un Rendez-Vous
 * @param project : le projet dans lequel on annule le rdv
 */
void Shell_annulerRendezVous(Project_GPCalendar* project){
    char date_courante[20];
    char continue_ask[50];
    printf("Si vous annulez un rendez-vous, vous perdrez toute trace de lui dans le calendrier.\n");
    printf("De plus, vous ne pouvez annuler que des rendez-vous n'ayant pas encore eu lieu.\n");
    Date* ajd = CreerDateCourante();
    getInfosDate(date_courante, ajd);
    printf("Pour information nous somme le : %s\n", date_courante);
    FreeDate(ajd);
    printf("Voulez vous continuer ? (\"yes\" ou \"no\") : ");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
    {
        printf("Vous avez choisi d'arrêtez, retour au menu principal.\n");
        return;
    }
    printf("Nous allons d'abord chercher quel rendez-vous vous souhaitez annuler.\n");
    RendezVous* rdv_cherche = Shell_chercherRendezVous(project);
    if(rdv_cherche == NULL)
    {
        printf("Le rendez-vous que vous souhaitiez annuler n'a pas été trouvé, veuillez réessayer. Retour au menu principal.\n");
        return;
    }
    char* infos_rdv = (char*) malloc(200);
    getInfosRendezVous(infos_rdv, rdv_cherche);
    printf("Le rendez-vous que vous souhaitez annuler a bien été identifié : \n\n%s", infos_rdv);
    free((void*) infos_rdv);
    printf("Suppression du rendez-vous : ");
    if(!AnnulerRendezVous(project->calendrier, rdv_cherche))
    {
        printf("Retour au menu principal.\n");
        return;
    }
    printf("Votre rendez-vous a bien été annulé.\n");
}

/**
 * Shell_supprimerPatient : Supprime un patient de la base de données
 * @param project : le projet dans lequel on supprime le patient
 */
void Shell_supprimerPatient(Project_GPCalendar* project){
    char continue_ask[50];
    char num_secu_patientDelete[100];
    char* infos = (char*) malloc(1000);
    printf("Supprimer un patient, supprimera toutes traces de lui de notre base de données, à savoir ses informations "
           "personnelles, ses rendez-vous n'ayant pas encore eu lieu, ses rendez-vous passés et sa présence en tant "
           "que patient reçu chez les médecins qu'il a déjà consulté.\n");
    printf("Souhaitez-vous continuez ? (\"yes\" ou \"no\") : ");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
    {
        printf("Vous avez choisi d'arrêtez, retour au menu principal.\n");
        free((void*) infos);
        return;
    }
    printf("\nVeuillez entrer le numéro de sécurité sociale du patient que vous voulez supprimer : ");
    scanf("%s", num_secu_patientDelete);
    if(checkQuit(num_secu_patientDelete))
    {
        free((void*) infos);
        return;
    }

    Patient* p = ListPatient_seek(project->consultingPatient, num_secu_patientDelete);
    if(p == NULL)
    {
        printf("Le patient au numéro de sécurité sociale \"%s\" ne fait pas partie de notre base de données, "
               "retour au menu principal.\n", num_secu_patientDelete);
        free((void*) infos);
        return;
    }
    printf("\n");
    printPatient(infos, p);
    printf("%s\n",infos);
    free((void*) infos);
    printf("Ce patient est-il bien celui que vous voulez supprimer ? (\"yes\" ou \"no\") : ");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
        {
        printf("\nLe numéro de sécurité sociale du patient que vous avez entré ne correspondait pas au bon patient : retour au menu principal.\n");
        return;
    }

    printf("Suppression des rendez-vous du patient \"%s %s\".\n",p->nom, p->prenom);
    Calendrier c = project->calendrier;
    for(ListAnnee_setOnFirst(c); !ListAnnee_isOutOfList(c); ListAnnee_setOnNext(c))
    {
        Annee a = ListAnnee_getCurrent(c);
        for (ListMois_setOnFirst(a); !ListMois_isOutOfList(a); ListMois_setOnNext(a))
        {
            Mois m = ListMois_getCurrent(a);
            for (ListJour_setOnFirst(m); !ListJour_isOutOfList(m); ListJour_setOnNext(m))
            {
                Jour j = ListJour_getCurrent(m);
                for (ListRendezVous_setOnFirst(j); !ListRendezVous_isOutOfList(j); ListRendezVous_setOnNext(j))
                {
                    RendezVous* current_rdv = ListRendezVous_getCurrent(j);
                    if(strcmp(p->numero_secu_social, current_rdv->patient->numero_secu_social) == 0){
                        char date_rdv[20];
                        getInfosDate(date_rdv, current_rdv->date);
                        printf("\tAnnulation de la consultation du %s à %2.1f entre le patient \"%s %s\" et le médecin \"%s %s\""
                               " \n", date_rdv, current_rdv->heure_debut, p->nom, p->prenom, current_rdv->medecin->nom, current_rdv->medecin->prenom);
                        freeNodeRendezVous(j, j->current);
                    }
                }
                if(ListRendezVous_isEmpty(j))
                {
                    FreeDate(j->date);
                    freeNodeJour(m, m->current);
                }
            }
            if(ListJour_isEmpty(m))
            {
                freeNodeMois(a, a->current);
            }
        }
        if(ListMois_isEmpty(a))
        {
            freeNodeAnnee(c, c->current);
        }
    }


    ListMedecin* lM = p->dossierMedical->medecins_consultes;
    for(ListMedecin_setOnFirst(lM); !ListMedecin_isOutOfList(lM); ListMedecin_setOnNext(lM))
    {
        Medecin* medecinConsulte = ListMedecin_getCurrent(lM);
        printf("Suppression du patient \"%s %s\" des patients reçus par le médecin \"%s %s\".\n",p->nom, p->prenom, medecinConsulte->nom, medecinConsulte->prenom);
        DeletePatientRecuMedecin(medecinConsulte, p);
    }
    printf("Suppression du patient \"%s %s\" de notre base de données.\n",p->nom, p->prenom);
    ListPatient* consultingPatient = project->consultingPatient;
    for(ListPatient_setOnFirst(consultingPatient); !ListPatient_isOutOfList(consultingPatient); ListPatient_setOnNext(consultingPatient))
    {
        if(strcmp(ListPatient_getCurrent(consultingPatient)->numero_secu_social, p->numero_secu_social) == 0)
        {
            freeNodePatient(consultingPatient, consultingPatient->current);
            break;
        }
    }
}
/**
 * Shell_supprimerMedecin : Supprime un médecin de la base de données
 * @param project : le projet dans lequel on supprime le médecin
 */
void Shell_supprimerMedecin(Project_GPCalendar* project){
    char continue_ask[50];
    char num_rps_medecinDelete[100];
    char* infos = (char*) malloc(1000);
    printf("Supprimer un médecin, supprimera toutes traces de lui de notre base de données. A savoir ses informations "
           "personnelles, ses consultations n'ayant pas encore eu lieu, ses consultations passés, sa présence en tant "
           "que médecin consulté chez les patients qu'il a déjà reçu et toutes les ordonnances qu'il a prescrites à ses patients !\n");
    printf("Souhaitez-vous continuez ? (\"yes\" ou \"no\") : ");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
    {
        printf("Vous avez choisi d'arrêtez, retour au menu principal.\n");
        free((void*) infos);
        return;
    }
    printf("\nVeuillez entrer le numéro RPS du médecin que vous voulez supprimer : ");
    scanf("%s", num_rps_medecinDelete);
    if(checkQuit(num_rps_medecinDelete))
    {
        free((void*) infos);
        return;
    }
    Medecin* medecin = ListMedecin_seek(project->workingMedecins, num_rps_medecinDelete);
    if(medecin == NULL)
    {
        printf("Le médecin au numéro RPS \"%s\" ne fait pas partie de notre base de données, "
               "retour au menu principal.\n", num_rps_medecinDelete);
        free((void*) infos);
        return;
    }
    printf("\n");
    getInfoMedecin(infos, medecin);
    printf("%s\n\n",infos);
    free((void*) infos);
    printf("Ce médecin est-il bien celui que vous voulez supprimer ? (\"yes\" ou \"no\") : ");
    scanf("%s", continue_ask);
    if( strcmp(continue_ask, "yes") != 0 )
    {
        printf("\nLe numéro RPS du médecin que vous avez entré ne correspondait pas au bon médecin : retour au menu principal.\n");
        return;
    }

    printf("Suppression des consultations du médecin \"%s %s\".\n", medecin->nom, medecin->prenom);
    Calendrier c = project->calendrier;
    for(ListAnnee_setOnFirst(c); !ListAnnee_isOutOfList(c); ListAnnee_setOnNext(c))
    {
        Annee a = ListAnnee_getCurrent(c);
        for (ListMois_setOnFirst(a); !ListMois_isOutOfList(a); ListMois_setOnNext(a))
        {
            Mois m = ListMois_getCurrent(a);
            for (ListJour_setOnFirst(m); !ListJour_isOutOfList(m); ListJour_setOnNext(m))
            {
                Jour j = ListJour_getCurrent(m);
                for (ListRendezVous_setOnFirst(j); !ListRendezVous_isOutOfList(j); ListRendezVous_setOnNext(j))
                {
                    RendezVous* current_rdv = ListRendezVous_getCurrent(j);
                    if(strcmp(medecin->numero_RPS, current_rdv->medecin->numero_RPS) == 0){
                        char date_rdv[20];
                        getInfosDate(date_rdv, current_rdv->date);
                        printf("\tAnnulation de la consultation du %s à %2.1f entre le médecin \"%s %s\" et le patient \"%s %s\""
                               " \n", date_rdv, current_rdv->heure_debut, medecin->nom, medecin->prenom, current_rdv->patient->nom, current_rdv->patient->prenom);
                        freeNodeRendezVous(j, j->current);
                    }
                }
                if(ListRendezVous_isEmpty(j))
                {
                    FreeDate(j->date);
                    freeNodeJour(m, m->current);
                }
            }
            if(ListJour_isEmpty(m))
            {
                freeNodeMois(a, a->current);
            }
        }
        if(ListMois_isEmpty(a))
        {
            freeNodeAnnee(c, c->current);
        }
    }

    ListPatient* lP = medecin->patients_recus;
    for(ListPatient_setOnFirst(lP); !ListPatient_isOutOfList(lP); ListPatient_setOnNext(lP))
    {
        Patient* patientRecu = ListPatient_getCurrent(lP);
        printf("Suppression du médecin \"%s %s\" de la liste des médecins consultés par le patient \"%s %s\".\n", medecin->nom, medecin->prenom, patientRecu->nom, patientRecu->prenom);
        DeleteMedecinConsultePatient(patientRecu, medecin);
        ListOrdonnance* lOrdo = patientRecu->dossierMedical->ordonnances;
        for(ListOrdonnance_setOnFirst(lOrdo); !ListOrdonnance_isOutOfList(lOrdo); ListOrdonnance_setOnNext(lOrdo))
        {
            if(strcmp(ListOrdonnance_getCurrent(lOrdo)->medecin->numero_RPS, medecin->numero_RPS) == 0)
            {
                char date_ordo[20];
                getInfosDate(date_ordo, ListOrdonnance_getCurrent(lOrdo)->date_edition);
                printf("\tSuppression de l'ordonnance éditée le %s par le médecin \"%s %s\" pour le patient \"%s %s\".\n", date_ordo, medecin->nom, medecin->prenom, patientRecu->nom, patientRecu->prenom);
                freeNodeOrdonnance(lOrdo, lOrdo->current);
            }
        }
    }

    printf("Suppression du médecin \"%s %s\" de notre base de données.\n", medecin->nom, medecin->prenom);
    ListMedecin* workingMedecins = project->workingMedecins;
    for(ListMedecin_setOnFirst(workingMedecins); !ListMedecin_isOutOfList(workingMedecins); ListMedecin_setOnNext(workingMedecins))
    {
        if(strcmp(ListMedecin_getCurrent(workingMedecins)->numero_RPS, medecin->numero_RPS) == 0)
        {
            freeNodeMedecin(workingMedecins, workingMedecins->current);
            break;
        }
    }
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
    Project_GPCalendar* current_project = NULL;
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

    /******************************************************************************************************************/
    /*                                       Ouverture de l'Application                                               */
    /******************************************************************************************************************/

    printf("************************** GPCalendar_Shell ******************************\n");

    printf("\nBienvenue dans la version console de GPCalendar, souhaitez-vous travailler avec un projet déjà existant ou souhaitez vous en créer un nouveau ?\n");
    printf("Entrez \"new\" pour créer un nouveau projet ou entrez directement le chemin absolu du fichier JSON correspondant à un projet précédemment sauvegardé.\n");
    printf("Exemple : \"../docs/example1_project.json\"\n");

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
    printf("\nSi vous avez besoin d'aide à propos des commandes vous pouvez tapez \"help\" lorsque vous êtes dans le menu principal.\n");
    printf("De la même façon, si vous souhaitez quitter l'action que vous êtes en train de réaliser, tapez \"quit\" lorsque vous\n êtes en train de réaliser l'une des actions du menu principal\n\n");


    /******************************************************************************************************************/
    /*                                          Switch Case Principal                                                 */
    /******************************************************************************************************************/

    do
    {
        /**
         * Demande de l'action à l'utilisateur (utilisation de fgets et strtol)
         */
        printf("Que voulez-vous faire ? ");
        while (fgets(GPCalendar_ask, sizeof(GPCalendar_ask), stdin)) {
            GPCalendar_action = strtol(GPCalendar_ask, &GPCalendar_ask_tmp, 10);
            //printf("GPCalendar_ask : %s", GPCalendar_ask);
            checkHelpDisplayAction(GPCalendar_ask);
            if (GPCalendar_ask_tmp == GPCalendar_ask || *GPCalendar_ask_tmp != '\n')
            {
                printf("Veuillez entrer un chiffre : ");
            }
            else if (GPCalendar_action < 1 || GPCalendar_action > 9)
            {
                printf("Veuillez entrer un chiffre correspondant aux actions possibles : \n");
                printPossibleAction();
            }
            else break;
        }
        /**
         * Switch case pour appeller la fonction correspondant à l'action demandée
         */
        char ask_continue[20];
        switch (GPCalendar_action)
        {
            case 1: /* nomP prenomP 01/02/1234 mailP telP secuP */
                printf("Souhaitez vous bien créer un Patient ? (\"yes\" or \"no\")\n");
                scanf("%s", ask_continue);
                if(strcmp(ask_continue, "yes") == 0)
                {
                    Shell_creerPatient(current_project);
                } else{
                    printf("Vous n'avez pas souhaité créer un Patient.\nRetour au menu principal.\n");
                }
                break;
            case 2: /* nomM prenomM mailM telM RPS */
                printf("Souhaitez vous bien créer un Médecin ? (\"yes\" or \"no\")\n");
                scanf("%s", ask_continue);
                if(strcmp(ask_continue, "yes") == 0)
                {
                    Shell_creerMedecin(current_project);
                } else{
                    printf("Vous n'avez pas souhaité créer un Médecin.\nRetour au menu principal.\n");
                }
                break;
            case 3:
                /* 01/02/2021 16.5 60 cabinet numeroSecuElona numeroRPPSFred */
                /* descriptionOrdonnanceRDV */
                /* compte-rendu du rdv (antécédent du patient) */

                printf("Souhaitez vous bien créer un Rendez-vous ? (\"yes\" or \"no\")\n");
                scanf("%s", ask_continue);
                if(strcmp(ask_continue, "yes") == 0)
                {
                    Shell_creerRendezVous(current_project);
                } else
                {
                    printf("Vous n'avez pas souhaité créer un Rendez-vous.\nRetour au menu principal.\n");
                }
                break;
            case 4:
                printf("Vous avez choisi de consulter des informations.\n");
                Shell_consulterInformations(current_project);
                break;
            case 5:
                printf("Vous avez choisi de modifier des informations.\n");
                Shell_modifierInformations(current_project);
                break;
            case 6:
                printf("Vous avez choisi d'annuler un Rendez-vous.\n");
                Shell_annulerRendezVous(current_project);
                break;
            case 7:
                printf("Vous avez choisi de supprimer un Patient.\n");
                Shell_supprimerPatient(current_project);
                break;
            case 8:
                printf("Vous avez choisi de supprimer un Médecin.\n");
                Shell_supprimerMedecin(current_project);
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
        printf("\nMenu principal : Voulez-vous continuez à utiliser l'application ? Entrez \"1\" si oui, \"0\" si non : ");
        while (fgets(GPCalendar_exit_ask, sizeof(GPCalendar_exit_ask), stdin)) {
            GPCalendar_exit = strtol(GPCalendar_exit_ask, &GPCalendar_exit_ask_tmp, 10);
            checkHelpDisplayAction(GPCalendar_exit_ask);
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

    /******************************************************************************************************************/
    /*                                       Fermeture de l'Application                                               */
    /******************************************************************************************************************/

    printf("Avant de partir, souhaitez-vous enregistrer votre projet ? Si oui, entrez directement le chemin absolu avec le nom du fichier de sauvegarde JSON que vous souhaitez créer.\n");
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
