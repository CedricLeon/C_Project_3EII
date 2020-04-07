#include "medecin.h"
#include "patient.h"

/**
 * CreerMedecin : Creer une nouvelle instance de la structure Medecin avec toutes les informations basiques mais pas ses spécialités ou ses diplômes
 * @param nom : le nom du medecin
 * @param prenom : le prenom du medecin
 * @param mail : l'adresse mail du medecin
 * @param num_tel  : le numero de telephone du medecin
 * @param num_RPS : le numéro RPS du mèdecin
 * @return un pointeur sur le medecin créé
 */
Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS){

    Medecin * m = (Medecin *) malloc(sizeof(Medecin));
    m->nom = nom;
    m->prenom = prenom;
    m->adresse_mail = mail;
    m->numero_telephone = num_tel;
    m->numero_RPS = num_RPS;

    m->patients_recus = (ListPatient *) malloc(sizeof(struct ListPatient));
    ListPatient_init(m->patients_recus);

    return m;
}
/**
 * DeleteMedecin : Supprime proprement une instance de la structure medecin
 * @param medecin : le medecin à supprimer
 */
void DeleteMedecin(Medecin * medecin){
    ListPatient_free(medecin->patients_recus);
    free((void *) medecin);
    //Un free pour les spécialités et les diplômes ?
}

/**
 * AfficheMedecin : Affiche les informations d'un medecin dans la console
 * @param m : le medecin
 */
void AfficheMedecin(Medecin * m){
    printf("Le medecin %s %s associé au numéro RPS suivant : %s est contactable au %s ou par mail à l'adresse suivante : %s.\n",
           m->nom, m->prenom, m->numero_RPS, m->numero_telephone, m->adresse_mail);
    printf("Flemme d'afficher les spécialités, les diplomes et la liste de patients recus pour l'instant.\n");
}

/********************************************************************************************************************/
                                            /*Setteurs de Medecin*/
/*******************************************************************************************************************/

/**
 * SetNomMedecin : Setteur du nom d'un medecin
 * @param medecin : le medecin
 * @param nom : le nouveau nom
 */
void SetNomMedecin(Medecin * medecin, char * nom){
    medecin->nom = nom;
}
/**
 * SetPrenomMedecin : Setteur du prenom d'un medecin
 * @param medecin : le medecin
 * @param prenom : le nouveau prenom
 */
void SetPrenomMedecin(Medecin * medecin, char * prenom){
    medecin->prenom = prenom;
}
/**
 * SetAdresseMailMedecin : Setteur de l'adrese mail d'un medecin
 * @param medecin : le medecin
 * @param mail : la nouvelle adresse mail
 */
void SetAdresseMailMedecin(Medecin * medecin, char * mail){
    medecin->adresse_mail = mail;
}
/**
 * SetNumeroTelephoneMedecin : Setteur du numero de telephone professionnel d'un medecin
 * @param medecin : le medecin
 * @param tel : le nouveau numero de telephone
 */
void SetNumeroTelephoneMedecin(Medecin * medecin, char * tel){
    medecin->numero_telephone = tel;
}
/**
 * SetNumeroRPSMedecin : Setteur du numéro RPS d'un medecin
 * @param medecin : le medecin
 * @param num_RPS : le nouveau numéro RPS
 */
void SetNumeroRPSMedecin(Medecin * medecin, char * num_RPS){
    medecin->numero_RPS = num_RPS;
}

/********************************************************************************************************************/
                                            /*Getteurs de Medecin*/
/*******************************************************************************************************************/

/**
 * getNomMedecin : retourne le nom et le prénom du Medecin sous forme de char* (pour l'affichage du RDV)
 * @param medecin : le Medecin dont on veut le nom
 * @return une chaine de caractères avec le nom et le prénom du Medecin
 */
char * getNomMedecin(Medecin * medecin){
    char * nom = "";
    strcpy(nom,medecin->nom);
    strcat(nom, " ");
    strcat(nom, medecin->prenom);
    return nom;
}
/**
 * getAdresseMailMedecin : retourne l'adresse mail du Medecin sous forme de char* (pour l'affichage)
 * @param medecin : le Medecin dont on veut l'adresse mail
 * @return un char* avec l'dresse mail
 */
char * getAdresseMailMedecin(Medecin * medecin){
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
 * @param medecin : le Medecin dont on veut les informations
 * @return une chaine de caractères avec les informations sur le Medecin
 */
char * getInfoMedecin(Medecin * medecin){
    char * info = "";
    strcpy(info,getNomMedecin(medecin));
    strcat(info,"\nNuméro RPS : ");
    strcat(info,getNumeroRPSMedecin(medecin));
    strcat(info, "\n@ : ");
    strcat(info, getAdresseMailMedecin(medecin));
    strcat(info, "\nTel : ");
    strcat(info, getNumeroTelephoneMedecin(medecin));
    return info;
}

/********************************************************************************************************************/
                                        /*Gestion des Patients recus*/
/*******************************************************************************************************************/

/**
 * AddPatientRecuMedecin : Ajoute un patient à la liste des patient recus par un medecin
 * @param m : le medecin recevant
 * @param patient : le patient recu
 * @return 1 si le patient a bien été ajouté à la liste 0 sinon (patient déjà recu par exemple)
 */
int AddPatientRecuMedecin(Medecin * m, Patient * patient){

    /*On vient tester si le patient n'a pas déjà été recu si la liste n'est pas vide*/
    if(!ListPatient_isEmpty(m->patients_recus)){
        for(ListPatient_setOnFirst(m->patients_recus); !ListPatient_isOutOfList(
                m->patients_recus); ListPatient_setOnNext(m->patients_recus)) {
            if(ListPatient_getCurrent(m->patients_recus) == patient){
                printf("Le patient %s %s a déjà été recu par le medecin %s %s, il n'est donc pas ajouté à la liste.\n", patient->nom, patient->prenom, m->nom, m->prenom);
                return 0;
            }
        }
    }

    //Ajout dans le cas où c'est le premier patient recu par le medecin (setup avec sentinel_end)
    if(ListPatient_isEmpty(m->patients_recus)){
        NodePatient * newNode = newNodePatient(patient, &(m->patients_recus->sentinel_begin), &(m->patients_recus->sentinel_end));
        m->patients_recus->sentinel_begin.next = newNode;
        m->patients_recus->sentinel_end.previous = newNode;
        printf("Le patient est le premier patient recu par le medecin, il a bien été ajouté.\n");
        return 1;
    }

    //Ajout du nouveau patient au début de la liste de patients recus
    ListPatient_setOnFirst(m->patients_recus);
    NodePatient * newNode = newNodePatient(patient, &(m->patients_recus->sentinel_begin), m->patients_recus->current);
    m->patients_recus->sentinel_begin.next = newNode;
    m->patients_recus->current->previous = newNode;
    printf("Le patient a été ajouté au début de la liste du medecin.\n");
    return 1;
}
/**
 * DeletePatientRecuMedecin : Enlève un Patient de la liste des patient recus par un medecin
 * @param m : le medecin recevant
 * @param patient : le patient qui doit être retiré de la liste
 * @return 1 si l'enlevement du patient à la liste a bien été réalisé 0 sinon (le medecin ne connaissait pas ce patient ou autre)
 */
int DeletePatientRecuMedecin(Medecin * m, Patient * patient){
    //Cas où la liste est vide
    if(ListPatient_isEmpty(m->patients_recus)){
        printf("La liste des patients recus par le medecin %s est vide, on ne peut donc pas y retirer le patient %s.\n", m->nom, patient->nom);
        return 0;
    }

    //On cherche si le patient a été recu par le medecin
    for (ListPatient_setOnFirst(m->patients_recus); !ListPatient_isOutOfList(
            m->patients_recus); ListPatient_setOnNext(m->patients_recus)) {
        //Si on le trouve on le retire et on quitte la fonction
        if (ListPatient_getCurrent(m->patients_recus) == patient) {
            m->patients_recus->current->previous->next = m->patients_recus->current->next;
            m->patients_recus->current->next->previous = m->patients_recus->current->previous;
            freeNodePatient(m->patients_recus->current);
            printf("Le patient %s a bien été retiré de la liste des patients recus par le medecin %s.\n", patient->nom, m->nom);
            return 1;
        }
    }

    /*Si on n'a pas trouvé le patient on l'affiche et on return -1*/
    printf("Le medecin %s n'a pas recu le patient %s, on ne peut donc pas le retirer de la liste.\n", m->nom, patient->nom);
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
 * freeNodeMedecin : Permet de delete proprement (avec un free) un nodeMedecin
 * @param n : le node à delete
 */
void freeNodeMedecin(NodeMedecin * n){
    free((void*) n);
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
 * ListMedecin_free : Libère la mémoire occupée par l'objet ListMedecin passée en paramètre
 * @param l : la liste de mèdecin à free
 */
void ListMedecin_free(ListMedecin * l){
    if (l!= NULL && !ListMedecin_isEmpty(l)){
        for(ListMedecin_setOnFirst(l); ListMedecin_isOutOfList(l); ListMedecin_setOnNext(l)) {
            freeNodeMedecin(l->current);
        }
    }
    free((void *) l);
}

/**
 * ListMedecin_isEmpty : Vérifie si la liste de Medecin est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListMedecin_isEmpty(ListMedecin * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListMedecin_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListMedecin_isFirst(ListMedecin * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListMedecin_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListMedecin_isLast(ListMedecin * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListMedecin_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
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
 * ListMedecin_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListMedecin_setOnLast(ListMedecin * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListMedecin_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListMedecin_setOnNext(ListMedecin * l){
    if(l != NULL && !ListMedecin_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListMedecin_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListMedecin_setOnPrevious(ListMedecin * l){
    if(l != NULL && !ListMedecin_isOutOfList(l)){
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