#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/medecin.h"

/**
 * CreerPatient : Creer une nouvelle instance de la structure Patient avec toutes les informations basiques
 * @param nom : nom du patient
 * @param prenom : prénom du patient
 * @param annee_naissance : Année, mois et jour de naissance du patient
 * @param mois_naissance
 * @param jour_naissance
 * @param mail : adresse mail du patient
 * @param num_tel :numéro de téléphone du patient
 * @return un pointeur sur le patient créé
 */
Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel, char* numero_secu_social){

    Patient* p = (Patient *) malloc(sizeof(Patient));

    p->nom = (char*) malloc(strlen(nom)+1);
    strcpy(p->nom, nom);
    p->prenom = (char*) malloc(strlen(prenom)+1);
    strcpy(p->prenom, prenom);
    p->date_naissance = CreerDate(annee_naissance, mois_naissance, jour_naissance);
    p->adresse_mail = (char*) malloc(strlen(mail)+1);
    strcpy(p->adresse_mail, mail);
    p->numero_telephone = (char*) malloc(strlen(num_tel)+1);
    strcpy(p->numero_telephone, num_tel);
    p->numero_secu_social = (char*) malloc(strlen(numero_secu_social)+1);
    strcpy(p->numero_secu_social, numero_secu_social);

    p->dossierMedical = CreerDossierMedical();
    return p;
}

/**
 * DeletePatient : Supprime proprement une instance de la structure patient
 * @param patient : le patient à supprimer
 */
void DeletePatient(Patient * patient){
    printf("DeletePatient() : pour le patient %s.\n", patient->numero_secu_social);

    FreeDossierMedical(patient->dossierMedical);

    FreeDate(patient->date_naissance);

    free((void*)patient->nom);
    free((void*)patient->prenom);
    free((void*)patient->adresse_mail);
    free((void*)patient->numero_telephone);
    free((void*)patient->numero_secu_social);

    free((void *) patient);
}

/**
 * AffichePatient : Affiche les informations d'un patient dans la console
 * @param p : le patient
 */
void printPatient(char* infos, Patient * p){
    /*printf("Le patient %s %s né le %d/%d/%d est contactable au %s ou par mail à l'adresse suivante : %s. Ce patient est associé au numéro de sécurité social suivant : %s\n",
            p->nom, p->prenom, p->date_naissance->jour, p->date_naissance->mois, p->date_naissance->annee,
            p->numero_telephone, p->adresse_mail, p->numero_secu_social);
    printf("\tIl a consulté les médecins suivants :\n");*/


    getNomPatient(infos, p);
    strcat(infos,",\n\tNuméro Sécu : ");
    strcat(infos, getNumeroSecuSocialePatient(p));
    strcat(infos, "\n\t@ : ");
    strcat(infos, getAdresseMailPatient(p));
    strcat(infos, "\n\tNé le : ");
    char* tmp = (char*) malloc(10);
    getDateNaissancePatient(tmp,p);
    strcat(infos, tmp);
    free((void*) tmp);
    strcat(infos, "\n\tTel : ");
    strcat(infos, getNumeroTelephonePatient(p));
    strcat(infos, "\n\tMedecins consultés : ");
    AccesDossierMedical(infos, p);
}

/**
* AccesDossierMedical : Accede au dossier du patient et l'affiche
* @param p : le patient dont on veut acceder au dossier
*/
void AccesDossierMedical(char* infos, Patient * p){

    char* nom = (char*) malloc(100);
    DossierMedical * d = p->dossierMedical;
    strcat(infos, "  ");

    for(ListMedecin_setOnFirst(d->medecins_consultes); !ListMedecin_isOutOfList(d->medecins_consultes); ListMedecin_setOnNext(d->medecins_consultes)) {
        getNomMedecin(nom, ListMedecin_getCurrent(d->medecins_consultes));
        strcat(infos, "\"");
        strcat(infos, nom);
        strcat(infos, "\"");
        strcat(infos, " ; ");
    }
    free((void*) nom);

    strcat(infos, "\n\tOrdonnances :\n");
    PrintListOrdonnances(infos, p);
    strcat(infos, "\tAntécédents :");
    PrintListAntecedents(infos, p);
}

/**
* voidPrintListOrdonnances : Affiche la liste d'ordonnances du patient
* @param p : le patient dont on veut afficher les ordonnances
*/

void PrintListOrdonnances(char* infos, Patient* p){

    ListOrdonnance * lo = p->dossierMedical->ordonnances;

    for(ListOrdonnance_setOnFirst(lo); !ListOrdonnance_isOutOfList(lo); ListOrdonnance_setOnNext(lo)){
        strcat(infos, "\t -  ");
        Ordonnance* ordo = ListOrdonnance_getCurrent(lo);
        printOrdonnance(infos, ordo);
    }
}

/**
* voidPrintListAntecedents : Affiche la liste d'antecedents du patient
* @param p : le patient dont on veut afficher les antecedents
*/

void PrintListAntecedents(char* infos, Patient* p){

    ListAntecedent * la = p->dossierMedical->antecedents;

    for(ListAntecedent_setOnFirst(la); !ListAntecedent_isOutOfList(la); ListAntecedent_setOnNext(la)){
        char* ante = ListAntecedent_getCurrent(la);
        printAntecedent(infos, ante);
    }
}
/********************************************************************************************************************/
                                            /*Setteurs de Patient*/
/*******************************************************************************************************************/

/**
 * SetNomPatient : Setteur du nom d'un patient
 * @param p : le patient
 * @param nom : le nouveau nom
 */
void SetNomPatient(Patient * p, char * nom){
    free((void*) p->nom);
    p->nom = (char*) malloc(strlen(nom)+1);
    strcpy(p->nom, nom);
}
/**
 * SetPrenomPatient : Setteur du prénom d'un patient
 * @param p : le patient
 * @param prenom : le nouveau prénom
 */
void SetPrenomPatient(Patient * p, char * prenom){
    free((void*) p->prenom);
    p->prenom = (char*) malloc(strlen(prenom)+1);
    strcpy(p->prenom, prenom);
}
/**
 * SetDateNaissancePatient : Setteur de la date de naissance d'un patient
 * @param p : le patient
 * @param an : la nouvelle date de naissance
 * @param mois
 * @param jour
 */
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour){
    p->date_naissance->annee = an;
    p->date_naissance->mois = mois;
    p->date_naissance->jour = jour;
}
/**
 * SetAdresseMailPatient : Setteur de l'adresse mail d'un patient
 * @param p : le patient
 * @param mail : la nouvelle adresse mail
 */
void SetAdresseMailPatient(Patient * p, char * mail){
    free((void*) p->adresse_mail);
    p->adresse_mail = (char*) malloc(strlen(mail)+1);
    strcpy(p->adresse_mail, mail);
}
/**
 * SetNumeroTelephonePatient : Setteur du numero de telephone d'un patient
 * @param p : le patient
 * @param tel : le nouveau numero de telephone
 */
void SetNumeroTelephonePatient(Patient * p, char * tel){
    free((void*) p->numero_telephone);
    p->numero_telephone = (char*) malloc(strlen(tel)+1);
    strcpy(p->numero_telephone, tel);
}
/**
 * SetNumeroSecuSocialePatient : Setteur du numero de sécurité sociale d'un patient
 * @param p : le patient
 * @param tel : le nouveau numero de sécurité sociale
 */
void SetNumeroSecuSocialePatient(Patient * p, char * secu){
    free((void*) p->numero_secu_social);
    p->numero_secu_social = (char*) malloc(strlen(secu)+1);
    strcpy(p->numero_secu_social, secu);
}
/********************************************************************************************************************/
                                             /*Getteurs de Patient*/
/*******************************************************************************************************************/

/**
 * getNomPatient : retourne le nom et le prénom du patient sous forme de char* (pour l'affichage du RDV)
 * @param p : le patient dont on veut le nom
 * @return une chaine de caractères avec le nom et le prénom du patient
 */
void getNomPatient(char * nom, Patient *p){
    strcpy(nom,p->nom);
    strcat(nom, " ");
    strcat(nom, p->prenom);
}
/**
 * getDateNaissancePatient : met la date de naissance du patient sous forme de char* (pour l'affichage) dans infos
 * @param infos : le char* dans lequel on stocke la date
 * @param p : le patient dont on veut la date de naissance
 */
void getDateNaissancePatient(char* infos, Patient* p){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    getInfosDate(infos, p->date_naissance);
}
/**
 * getAdresseMailPatient : retourne l'adresse mail du patient sous forme de char* (pour l'affichage)
 * @param p : le patient dont on veut l'adresse mail
 * @return un char* avec l'dresse mail
 */
char * getAdresseMailPatient(Patient * p){
    return p->adresse_mail;
}
/**
 * getNumeroTelephonePatient : retourne le numéro de téléphone du patient sous forme de char* (pour l'affichage)
 * @param p : le patient dont on veut le numéro de téléphone
 * @return un char * avec le numero de téléphone
 */
char * getNumeroTelephonePatient(Patient * p){
    return  p->numero_telephone;
}
/**
 * getNumeroSecuSocialePatient : retourne le numéro de sécurité sociale du patient sous forme de char* (pour l'affichage)
 * @param p : le patient dont on veut le numéro de sécurité sociale
 * @return un char * avec le numero de sécurité sociale
 */
char * getNumeroSecuSocialePatient(Patient * p){
    return  p->numero_secu_social;
}


/**
 * getInfoPatient : Place les infos du patient dans infos
 * @param infos : le char* dans lequel on met les infos
 * @param p : le patient dont on veut les informations
 */
void getInfoPatient(char* infos, Patient* p){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    char * tmp = (char*) malloc(50);
    getNomPatient(tmp, p);
    strcpy(infos,tmp);
    strcat(infos,"\nNé(e) le : ");

    getDateNaissancePatient(tmp, p);
    strcat(infos, tmp);
    free((void*) tmp);

    strcat(infos, "\n@ : ");
    strcat(infos, getAdresseMailPatient(p));
    strcat(infos, "\nTel : ");
    strcat(infos, getNumeroTelephonePatient(p));
    strcat(infos, "\nN° sécu : ");
    strcat(infos, getNumeroSecuSocialePatient(p));
}

/********************************************************************************************************************/
                                    /*Gestion des Medecins Consultes*/
/*******************************************************************************************************************/

/**
 * AddMedecincConsultePatient : Ajoute un Medecin à la première position de la liste des medecins consultés par un patient
 * @param p : le patient consultant
 * @param medecin : le medecin consulté
 * @return 1 si le médecin a bien été ajouté à la liste
 *         0 sinon (médecin déjà consulté par exemple)
 */
int AddMedecinConsultePatient(Patient * p, Medecin * medecin){

    /*On vient tester si le médecin n'a pas déjà été consulté si la liste n'est pas vide*/
    if(!ListMedecin_isEmpty(p->dossierMedical->medecins_consultes)){
        for(ListMedecin_setOnFirst(p->dossierMedical->medecins_consultes); !ListMedecin_isOutOfList(
            p->dossierMedical->medecins_consultes); ListMedecin_setOnNext(p->dossierMedical->medecins_consultes)) {
            if(strcmp(ListMedecin_getCurrent(p->dossierMedical->medecins_consultes)->numero_RPS, medecin->numero_RPS) == 0){
                printf("Le médecin %s %s a déjà été consulté par le patient %s %s, il n'est donc pas ajouté à la liste.\n", medecin->nom, medecin->prenom, p->nom, p->prenom);
                return 0;
            }
        }
    }

    //Ajout dans le cas où c'est le premier médecin consulté (setup avec sentinel_end)
    if(ListMedecin_isEmpty(p->dossierMedical->medecins_consultes)){
        NodeMedecin * newNode = newNodeMedecin(medecin, &(p->dossierMedical->medecins_consultes->sentinel_begin), &(p->dossierMedical->medecins_consultes->sentinel_end));
        p->dossierMedical->medecins_consultes->sentinel_begin.next = newNode;
        p->dossierMedical->medecins_consultes->sentinel_end.previous = newNode;
        printf("Le mèdecin est le premier mèdecin consulté par le patient, il a bien été ajouté.\n");
        return 1;
    }

    //Ajout au début de la liste du medecin si le patient avait déjà consulté d'autres medecin
    ListMedecin_setOnFirst(p->dossierMedical->medecins_consultes);
    NodeMedecin * newNode = newNodeMedecin(medecin, &(p->dossierMedical->medecins_consultes->sentinel_begin), p->dossierMedical->medecins_consultes->current);
    p->dossierMedical->medecins_consultes->sentinel_begin.next = newNode;
    p->dossierMedical->medecins_consultes->current->previous = newNode;
    printf("Le medecin a été ajouté au début de la liste du patient.\n");
    return 1;
}
/**
 * DeleteMedecinPatient : Enleve un Medecin de la liste des medecins consultés par un patient
 * @param p : le patient à qui on retire un medecin consultés
 * @param medecin : le medecin qui n'a pas été consulté
 * @return 1 si l'enlevement du médecin a bien été réalisé
 *         0 sinon (le patient n'avait pas consulté ce médecin par exemple)
 */
int DeleteMedecinConsultePatient(Patient * p, Medecin * medecin){

    //Cas où la liste est vide
    if(ListMedecin_isEmpty(p->dossierMedical->medecins_consultes)){
        printf("La liste des mèdecins consultés par le patient %s est vide, on ne peut donc pas y retirer le mèdecin %s.\n", p->nom, medecin->nom);
        return 0;
    }

    //On cherche si le médecin a été consulté par le patient
    for (ListMedecin_setOnFirst(p->dossierMedical->medecins_consultes); !ListMedecin_isOutOfList(
            p->dossierMedical->medecins_consultes); ListMedecin_setOnNext(p->dossierMedical->medecins_consultes)) {

        //Si on le trouve on le retire et on quitte la fonction
        if (ListMedecin_getCurrent(p->dossierMedical->medecins_consultes) == medecin) {
            p->dossierMedical->medecins_consultes->current->previous->next = p->dossierMedical->medecins_consultes->current->next;
            p->dossierMedical->medecins_consultes->current->next->previous = p->dossierMedical->medecins_consultes->current->previous;
            freeNodeMedecin_withoutDeletingMedecin(p->dossierMedical->medecins_consultes, p->dossierMedical->medecins_consultes->current);
            printf("Le mèdecin %s a bien été retiré de la liste des mèdecins consulté par le patient %s.\n", medecin->nom, p->nom);
            return 1;
        }
    }

    /*Si on n'a pas trouvé le médecin on l'affiche et on return 0*/
    printf("Le patient %s n'a pas consuté le médecin %s, on ne peut donc pas le retirer de la liste.\n", p->nom, medecin->nom);
    return 0;
}

/**********************************************************************************************************************/
                                                /*ListPatient*/
/**********************************************************************************************************************/

/**
 * newNodePatient : Permet de créer dynamiquement un nouveau node de patient pour la liste
 * @param patient : le patient pointé par ce nouveau noeud
 * @param previous : le noeud précédant le nouveau noeud dans la liste
 * @param next : le prochain noeud de la liste
 * @return un pointeur sur le nouveau noeud créé
 */
NodePatient * newNodePatient(Patient * patient, NodePatient * previous, NodePatient * next){
    NodePatient * newNode = (NodePatient *) malloc(sizeof(NodePatient));
    newNode->patient = patient;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodePatient : Permet de delete proprement (avec un free) un nodePatient
 * @param n : le node à delete
 */
void freeNodePatient(ListPatient *l, NodePatient * n){
    //C'est ici qu'on vient free les patients.
    //Pour l'instant cette fonction n'est appelée que par ListPatient_free() qui est uniquement appelée par freeProject()

    //On set les pointeurs des objets précédent et suivant le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    DeletePatient(n->patient);
    free((void *) n);

    //On place current sur sentinel_begin pour que le setOnnext de la boucle for le place sur le premier élément de liste
    //On est obligé de faire ça car sinon current reste sur le noeud qu'on vient de free et donc sur NULL et isOutOfList return true alors que pas forcément
    ListPatient_setOnFirst(l);
    ListPatient_setOnPrevious(l);
}
/**
 * freeNodePatient_withoutDeletingPatient : Permet de delete proprement (avec un free) un nodePatient
 * @param n : le node à delete
 */
void freeNodePatient_withoutDeletingPatient(ListPatient *l, NodePatient * n){
    n->previous->next = n->next;
    n->next->previous = n->previous;
    free((void *) n);
    ListPatient_setOnFirst(l);
    ListPatient_setOnPrevious(l);
}

/**
 * CreerListPatient : malloc et initialise une liste de patients
 * @return la liste initialisée
 */
ListPatient * CreerListPatient(){
    ListPatient * lP;
    lP = (ListPatient*) malloc(sizeof(ListPatient));
    ListPatient_init(lP);
    return lP;
}

/**
 * printListPatient : Affiche une liste de mèdecins (notamment pour printProject)
 * @param l : la liste à afficher
 */
void printListPatient(ListPatient* l){
    char* infosPatient;
    for (ListPatient_setOnFirst(l); !ListPatient_isOutOfList(l); ListPatient_setOnNext(l)) {
        printf("\n *  ");
        infosPatient = (char*) malloc(1000);
        printPatient(infosPatient, ListPatient_getCurrent(l));
        printf("%s", infosPatient);
        free((void*) infosPatient);
        printf("\n");
    }
}


/**
 * ListPatient_init : Initialise correctement une liste de NodePatient en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL en dehors de la liste
 * @param l : la liste à initialiser
 */
void ListPatient_init(ListPatient * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.patient = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.patient = NULL;
    }
}

/**
 * ListPatient_free : Free toute la liste de patients
 * @param l : la liste en question
 */
void ListPatient_free(ListPatient * l){
    if (l == NULL){
        printf("ListPatient_free : le jour est NULL !!!\n");
    }else if ( ListPatient_isEmpty(l)){
        printf("ListPatient_free : la liste est vide, ce n'est pas normal !!!\n");
        free((void *) l);
    }else {
        for (ListPatient_setOnFirst(l); !ListPatient_isOutOfList(l); ListPatient_setOnNext(l)) {
            printf("ListPatient_free() : appel de freeNodePatient() sur %s.\n", l->current->patient->numero_secu_social);
            freeNodePatient(l, l->current);
        }
        free((void *) l);
    }
}
/**
 * ListPatient_free_withoutDeletingPatient : Free toute la liste de patients
 * @param l : la liste en question
 */
void ListPatient_free_withoutDeletingPatient(ListPatient * l){
    if (l == NULL){
        printf("ListPatient_free_withoutDeletingPatient : le jour est NULL !!!\n");
    }else if ( ListPatient_isEmpty(l)){
        printf("ListPatient_free_withoutDeletingPatient : la liste est vide, on ne free donc que la liste!!!\n");
        free((void *) l);
    }else {
        for (ListPatient_setOnFirst(l); !ListPatient_isOutOfList(l); ListPatient_setOnNext(l)) {
            freeNodePatient_withoutDeletingPatient(l, l->current);
        }
        free((void *) l);
    }
}
/**
 * ListPatient_add : Ajoute un patient à une liste de patients (pas triée)
 * @param l : la liste à laquelle on ajoute
 * @param p : le patient à ajouter
 * @return -1 si la liste ou le patient étaient NULL
 *          1 si tout s'est bien passé
 */
int ListPatient_add(ListPatient * l, Patient * p){
    if(l == NULL || p == NULL){
        printf("ListPatient ou Patient NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListPatient_isEmpty(l)){
        NodePatient * newNode = newNodePatient(p, &(l->sentinel_begin), &(l->sentinel_end));
        l->sentinel_begin.next = newNode;
        l->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on insère le patient à la fin
    NodePatient * newNode = newNodePatient(p, l->sentinel_end.previous, &(l->sentinel_end));
    l->sentinel_end.previous->next = newNode;
    l->sentinel_end.previous = newNode;
    return 1;
}
/**
 * Listpatient_seek : Permet de chercher un patient dans une list de patient depuis son Numéro de sécurité sociale (son ID)
 * @param lP : la liste dans laquelle on cherche
 * @param IDPatient : l'ID du patient cherché
 * @return un pointeur sur le patient
 *         NULL si on ne l'a pas trouvé
 */
Patient* ListPatient_seek(ListPatient* lP, char* IDPatient){
    for(ListPatient_setOnFirst(lP); !ListPatient_isOutOfList(lP); ListPatient_setOnNext(lP))
    {
        if(strcmp(ListPatient_getCurrent(lP)->numero_secu_social, IDPatient) == 0)
        {
            printf("ListPatient_seek() : On a trouvé le patient au numéro de sécu : \"%s\".\n", IDPatient);
            return ListPatient_getCurrent(lP);
        }
    }
    printf("ListPatient_seek() : On a pas trouvé le patient au numéro de sécu : \"%s\".\n", IDPatient);
    return NULL;
}
/**
 * ListPatient_isEmpty : Vérifie si la liste de Patient est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
 */
int ListPatient_isEmpty(ListPatient * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end) && l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListPatient_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
 */
int ListPatient_isFirst(ListPatient * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListPatient_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
 */
int ListPatient_isLast(ListPatient * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListPatient_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * @param l : la liste
 * @return 1 si current vaut NULL
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
 */
int ListPatient_isOutOfList(ListPatient * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListPatient_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListPatient_setOnFirst(ListPatient * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListPatient_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListPatient_setOnLast(ListPatient * l){
    if(l != NULL && !ListPatient_isOutOfList(l)){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListPatient_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListPatient_setOnNext(ListPatient * l){
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListPatient_setOnPrevious : Positionne le pointeur courant sur l'élément avant lui dans la liste
 * @param l : la liste
 */
void ListPatient_setOnPrevious(ListPatient * l){
    if(l != NULL && l->current->previous != NULL){
        l->current = l->current->previous;
    }
}
/**
 * ListPatient_getCurrent : Permet d'acceder au Patient pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Patient de l'élément courant de la liste
 */
Patient * ListPatient_getCurrent(ListPatient * l){
    if(l != NULL && l->current != NULL){
        return l->current->patient;
    }
    return NULL;
}

