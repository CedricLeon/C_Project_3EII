#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"

/**
 * CreerMedecin : Creer une nouvelle instance de la structure Medecin avec toutes les informations basiques mais pas ses spécialités ou ses diplômes
 * @param nom : le nom du medecin
 * @param prenom : le prenom du medecin
 * @param mail : l'adresse mail du medecin
 * @param num_tel  : le numero de telephone du medecin
 * @param num_RPS : le numéro RPS du medecin
 * @return un pointeur sur le medecin créé
 */
Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS){

    Medecin * m = (Medecin *) malloc(sizeof(Medecin));

    m->nom = (char*) malloc(strlen(nom)+1);
    strcpy(m->nom, nom);
    m->prenom = (char*) malloc(strlen(prenom)+1);
    strcpy(m->prenom, prenom);
    m->adresse_mail = (char*) malloc(strlen(mail)+1);
    strcpy(m->adresse_mail, mail);
    m->numero_telephone = (char*) malloc(strlen(num_tel)+1);
    strcpy(m->numero_telephone, num_tel);
    m->numero_RPS = (char*) malloc(strlen(num_RPS)+1);
    strcpy(m->numero_RPS, num_RPS);

    m->patients_recus = (ListPatient *) malloc(sizeof(struct ListPatient));
    ListPatient_init(m->patients_recus);

    return m;
}
/**
 * DeleteMedecin : Supprime proprement une instance de la structure medecin
 * @param medecin : le medecin à supprimer
 */
void DeleteMedecin(Medecin * medecin){
    free((void*) medecin->nom);
    free((void*) medecin->prenom);
    free((void*) medecin->adresse_mail);
    free((void*) medecin->numero_telephone);
    free((void*) medecin->numero_RPS);
    ListPatient_free_withoutDeletingPatient(medecin->patients_recus);
    free((void *) medecin);
}

/********************************************************************************************************************/
                                            /*Getteurs de Medecin*/
/*******************************************************************************************************************/

/**
 * getNomMedecin : retourne le nom et le prénom du Medecin sous forme de char* (pour l'affichage du RDV)
 * @param nom : la chaine où on veut stocker le nom
 * @param medecin : le Medecin dont on veut le nom
 */
void getNomMedecin(char* nom, Medecin* m){
    strcpy(nom,m->prenom);
    strcat(nom, " ");
    strcat(nom, m->nom);
}
/**
 * getAdresseMailMedecin : retourne l'adresse mail du Medecin sous forme de char* (pour l'affichage)
 * @param medecin : le Medecin dont on veut l'adresse mail
 * @return un char* avec l'adresse mail
 */
char * getAdresseMailMedecin(Medecin* medecin){
    return medecin->adresse_mail;
}
/**
 * getNumeroTelephoneMedecin : retourne le numéro de téléphone du Medecin sous forme de char* (pour l'affichage)
 * @param medecin : le Medecin dont on veut le numéro de téléphone
 * @return un char * avec le numero de téléphone
 */
char * getNumeroTelephoneMedecin(Medecin * medecin){
    return  medecin->numero_telephone;
}
/**
 * getNumeroRPSMedecin : retourne le Numero RPS du Medecin sous forme de char* (pour l'affichage)
 * @param medecin : le Medecin dont on veut le Numero RPS
 * @return un char* avec le Numero RPS
 */
char * getNumeroRPSMedecin(Medecin * medecin){
    return medecin->numero_RPS;
}
/**
 * getInfoMedecin : retourne une chaine de caractères résumant les attributs du Medecin
 * @param infos : la chaine où l'on stocke les infos sur le médecin
 * @param medecin : le Medecin dont on veut les informations
 */
void getInfoMedecin(char * infos, Medecin * medecin){
    getNomMedecin(infos, medecin);
    strcat(infos,"\n\tNuméro RPS : ");
    strcat(infos,getNumeroRPSMedecin(medecin));
    strcat(infos, "\n\t@ : ");
    strcat(infos, getAdresseMailMedecin(medecin));
    strcat(infos, "\n\tTel : ");
    strcat(infos, getNumeroTelephoneMedecin(medecin));
    strcat(infos, "\n\tPatients Recus :  ");

    for(ListPatient_setOnFirst(medecin->patients_recus); !ListPatient_isOutOfList(medecin->patients_recus); ListPatient_setOnNext(medecin->patients_recus)) {
        strcat(infos, "\"");
        strcat(infos, ListPatient_getCurrent(medecin->patients_recus)->nom);
        strcat(infos, " ");
        strcat(infos, ListPatient_getCurrent(medecin->patients_recus)->prenom);
        strcat(infos, "\" ; ");
    }
}

/********************************************************************************************************************/
                                        /*Gestion des Patients recus*/
/*******************************************************************************************************************/

/**
 * AddPatientRecuMedecin : Ajoute un patient à la liste des patient recus par un medecin
 * @param m : le medecin recevant
 * @param patient : le patient recu
 * @return 1 si le patient a bien été ajouté à la liste
 *         0 sinon (patient déjà recu par exemple)
 */
int AddPatientRecuMedecin(Medecin * m, Patient * patient){

    /*On vient tester si le patient n'a pas déjà été recu si la liste n'est pas vide*/
    if(!ListPatient_isEmpty(m->patients_recus)){
        for(ListPatient_setOnFirst(m->patients_recus); !ListPatient_isOutOfList(
                m->patients_recus); ListPatient_setOnNext(m->patients_recus)) {
            if(strcmp(ListPatient_getCurrent(m->patients_recus)->numero_secu_social, patient->numero_secu_social) == 0){
                //printf("Le patient %s %s a déjà été recu par le medecin %s %s, il n'est donc pas ajouté à la liste.\n", patient->nom, patient->prenom, m->nom, m->prenom);
                return 0;
            }
        }
    }

    //Ajout dans le cas où c'est le premier patient recu par le medecin (setup avec sentinel_end)
    if(ListPatient_isEmpty(m->patients_recus)){
        NodePatient * newNode = newNodePatient(patient, &(m->patients_recus->sentinel_begin), &(m->patients_recus->sentinel_end));
        m->patients_recus->sentinel_begin.next = newNode;
        m->patients_recus->sentinel_end.previous = newNode;
        //printf("Le patient est le premier patient recu par le medecin, il a bien été ajouté.\n");
        return 1;
    }

    //Ajout du nouveau patient au début de la liste de patients recus
    ListPatient_setOnFirst(m->patients_recus);
    NodePatient * newNode = newNodePatient(patient, &(m->patients_recus->sentinel_begin), m->patients_recus->current);
    m->patients_recus->sentinel_begin.next = newNode;
    m->patients_recus->current->previous = newNode;
    //printf("Le patient a été ajouté au début de la liste du medecin.\n");
    return 1;
}
/**
 * DeletePatientRecuMedecin : Enlève un Patient de la liste des patients recus par un medecin
 * @param m : le medecin recevant
 * @param patient : le patient qui doit être retiré de la liste
 * @return 1 si l'enlevement du patient à la liste a bien été réalisé
 *         0 sinon (le medecin ne connaissait pas ce patient ou autre)
 */
int DeletePatientRecuMedecin(Medecin * m, Patient * patient){
    //Cas où la liste est vide
    if(ListPatient_isEmpty(m->patients_recus)){
        //printf("La liste des patients recus par le medecin %s est vide, on ne peut donc pas y retirer le patient %s.\n", m->nom, patient->nom);
        return 0;
    }

    //On cherche si le patient a été recu par le medecin
    for (ListPatient_setOnFirst(m->patients_recus); !ListPatient_isOutOfList(
            m->patients_recus); ListPatient_setOnNext(m->patients_recus)) {
        //Si on le trouve on le retire et on quitte la fonction
        if (strcmp(ListPatient_getCurrent(m->patients_recus)->numero_secu_social, patient->numero_secu_social) == 0) {
            m->patients_recus->current->previous->next = m->patients_recus->current->next;
            m->patients_recus->current->next->previous = m->patients_recus->current->previous;
            freeNodePatient_withoutDeletingPatient(m->patients_recus, m->patients_recus->current);
            //printf("Le patient %s a bien été retiré de la liste des patients recus par le medecin %s.\n", patient->nom, m->nom);
            return 1;
        }
    }

    /*Si on n'a pas trouvé le patient on l'affiche et on return -1*/
    //printf("Le medecin %s n'a pas recu le patient %s, on ne peut donc pas le retirer de la liste.\n", m->nom, patient->nom);
    return 0;
}

/**********************************************************************************************************************/
                                                /*ListMedecin*/
/**********************************************************************************************************************/

/**
 * newNodeMedecin : Permet de créer dynamiquement un nouveau node de Medecin pour la liste
 * @param Medecin : le Medecin pointé par ce nouveau noeud
 * @param previous : le noeud précédant le nouveau noeud dans la liste
 * @param next : le prochain noeud de la liste
 * @return un pointeur sur le nouveau noeud créé
 */
NodeMedecin * newNodeMedecin(Medecin * medecin, NodeMedecin * previous, NodeMedecin * next){
    NodeMedecin * newNode = (NodeMedecin *) malloc(sizeof(NodeMedecin));
    newNode->medecin = medecin;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeMedecin : Permet de delete proprement un nodeMedecin (en deletant le medecin lié au node) (workingMedecins)
 * @param n : le node à delete
 */
void freeNodeMedecin(ListMedecin *l, NodeMedecin * n){
    //C'est ici qu'on vient free les medecins.
    //Pour l'instant cette fonction n'est appellée que par ListMedecin_free() qui est uniquement appellée par freeProject()

    //On set les pointeurs des objets précédants et suivants le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    DeleteMedecin(n->medecin);
    free((void *) n);

    //On place current sur sentinel_begin pour quye le setOnnext de la boucle for le place sur le premier élément de liste
    //On est obligé de faire ça car sinon current reste sur le noeud qu'on vient de free et donc sur NULL et isOutOfList return true alors que pas forcément
    ListMedecin_setOnFirst(l);
    ListMedecin_setOnPrevious(l);
}
/**
 * freeNodeMedecin_withoutDeletingMedecin : Permet de delete un nodeMedecin mais sans delete le médecin lié au node *
 *                                          (utile pour la liste des médecins consultés par un patient)
 * @param n : le node à delete
 */
void freeNodeMedecin_withoutDeletingMedecin(ListMedecin *l, NodeMedecin * n){
    //printf("freeNodeMedecin_withoutDeletingMedecin()\n");
    n->previous->next = n->next;
    n->next->previous = n->previous;
    free((void *) n);
    ListMedecin_setOnFirst(l);
    ListMedecin_setOnPrevious(l);
}

/**
 * CreerListMedecin : malloc et initialise une liste de médecins
 * @return la liste initialisée
 */
ListMedecin * CreerListMedecin(){
    ListMedecin * lM;
    lM = (ListMedecin*) malloc(sizeof(ListMedecin));
    ListMedecin_init(lM);
    return lM;
}

/**
 * printListMedecin : Affiche une liste de mèdecins (notamment pour printProject)
 * @param l : la liste à afficher
 */
void printListMedecin(ListMedecin* l){
    char* infosMedecin;
    for (ListMedecin_setOnFirst(l); !ListMedecin_isOutOfList(l); ListMedecin_setOnNext(l)) {
        printf("\n *  ");
        infosMedecin = (char*) malloc(1000);
        getInfoMedecin(infosMedecin, ListMedecin_getCurrent(l));
        printf("%s",infosMedecin);
        free((void*)infosMedecin);
        printf("\n");
    }
}

/**
 * ListMedecin_init : Initialise correctement une liste de NodeMedecin en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 */
void ListMedecin_init(ListMedecin * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.medecin = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.medecin = NULL;
    }
}
/**
 * ListMedecin_free : Libère la mémoire occupée par l'objet ListMedecin passé en paramètre
 * @param l : la liste de médecins à free
 */
void ListMedecin_free(ListMedecin * l){

    if (l == NULL){
        printf("ListMedecin_free : le jour est NULL !!!\n");
    }else if ( ListMedecin_isEmpty(l)){
        //printf("ListMedecin_free : la liste est vide, ce n'est pas normal !!!\n");
        free((void *) l);
    }else {
        for (ListMedecin_setOnFirst(l); !ListMedecin_isOutOfList(l); ListMedecin_setOnNext(l)) {
            freeNodeMedecin(l, l->current);
        }
        free((void *) l);
    }
}
/**
 * ListMedecin_free_withoutDeletingMedecin : Libère la mémoire occupée par l'objet ListMedecin passé en paramètre mais
 *                                           sans delete les médecins de cette liste (uniquement les nodes)
 * @param l : la liste de médecins à free
 */
void ListMedecin_free_withoutDeletingMedecin(ListMedecin * l){

    if (l == NULL){
        printf("ListMedecin_free_withoutDeletingMedecin : le jour est NULL !!!\n");
    }else if ( ListMedecin_isEmpty(l)){
        //printf("ListMedecin_free_withoutDeletingMedecin : la liste est vide, on ne free donc que la liste!!!\n");
        free((void *) l);
    }else {
        for (ListMedecin_setOnFirst(l); !ListMedecin_isOutOfList(l); ListMedecin_setOnNext(l)) {
            //printf("ListMedecin_free_withoutDeletingMedecin() Appel de freeNodeMedecin_withoutDeletingMedecin() pour le mèdecin : %s\n", l->current->medecin->numero_RPS);
            freeNodeMedecin_withoutDeletingMedecin(l, l->current);
        }
        free((void *) l);
    }
}
/**
 * ListMedecin_add : Ajoute un medecin à une liste de medecin (pas triée)
 * @param l : la liste à laquelle on ajoute
 * @param m : le medecin à ajouter
 * @return -1 si la liste ou le medecin étaient NULL
 *          1 si tout s'est bien passé
 */
int ListMedecin_add(ListMedecin * l, Medecin * m){
    if(l == NULL || m == NULL){
        printf("ListMedecin ou Medecin NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListMedecin_isEmpty(l)){
        NodeMedecin * newNode = newNodeMedecin(m, &(l->sentinel_begin), &(l->sentinel_end));
        l->sentinel_begin.next = newNode;
        l->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on insère le mèdecine à la fin
    NodeMedecin * newNode = newNodeMedecin(m, l->sentinel_end.previous, &(l->sentinel_end));
    l->sentinel_end.previous->next = newNode;
    l->sentinel_end.previous = newNode;
    return 1;
}
/**
 * ListMedecin_seek : Permet de chercher un Medecin dans une list de Medecin depuis son Numéro RPS (son ID)
 * @param lP : la liste dans laquelle on cherche
 * @param IDMedecin : l'ID du Medecin cherché
 * @return un pointeur sur le Medecin
 *         NULL si on ne l'a pas trouvé
 */
Medecin* ListMedecin_seek(ListMedecin* lP, char* IDMedecin){
    for(ListMedecin_setOnFirst(lP); !ListMedecin_isOutOfList(lP); ListMedecin_setOnNext(lP))
    {
        if(strcmp(ListMedecin_getCurrent(lP)->numero_RPS, IDMedecin) == 0)
        {
            //printf("ListMedecin_seek() : On a trouvé le Medecin au numéro de sécu : \"%s\".\n", IDMedecin);
            return ListMedecin_getCurrent(lP);
        }
    }
    //printf("ListMedecin_seek() : On a pas trouvé le Medecin au numéro de sécu : \"%s\".\n", IDMedecin);
    return NULL;
}
/**
 * ListMedecin_isEmpty : Vérifie si la liste de Medecin est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
 */
int ListMedecin_isEmpty(ListMedecin * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListMedecin_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL
 *         0 sinon
 *         -1 si la liste est NULL
 */
int ListMedecin_isOutOfList(ListMedecin * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListMedecin_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListMedecin_setOnFirst(ListMedecin * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListMedecin_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListMedecin_setOnNext(ListMedecin * l){
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListMedecin_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListMedecin_setOnPrevious(ListMedecin * l){
    if(l != NULL && l->current->previous != NULL){
        l->current = l->current->previous;
    }
}
/**
 * ListMedecin_getCurrent : Permet d'acceder au Medecin pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Medecin de l'élément courant de la liste
 */
Medecin * ListMedecin_getCurrent(ListMedecin * l){
    if(l != NULL && l->current != NULL){
        return l->current->medecin;
    }
    return NULL;
}
