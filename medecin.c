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
    ListPatient_init(m->patient_recus);

    return m;
}
/**
 * DeleteMedecin : Supprime proprement une instance de la structure medecin
 * @param medecin : le medecin à supprimer
 */
void DeleteMedecin(Medecin * medecin){
    free((void *)medecin);
    //Un free pour les spécialités et les diplômes ?
}

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

/**
 * AddPatientRecuMedecin : Ajoute un patient à la liste des patient recus par un medecin
 * @param m : le medecin recevant
 * @param patient : le patient recu
 * @return 1 si l'ajout du patient à la liste a bien été réalisé 0 sinon (le medecin a déjà recus trop de patients ou autre)
 */
int AddPatientRecuMedecin(Medecin * m, Patient * patient){
   /* if(m->nb_patients_recus == NB_MAX_PATIENT_RECUS){
        printf("Le medecin %s a déjà recu trop de patients différents : %d.\nLe patient n'a donc pas été ajouté à sa liste.;\n", m->nom,  NB_MAX_PATIENT_RECUS);
        return  -1;
    }

    m->patient_recus + m->nb_patients_recus = patient;

    m->nb_patients_recus++;

    printf("Le medecin %s a recu le patient %s.\n", m->nom, patient->nom);
    return 0;   //reussite*/
}
/**
 * DeletePatientRecuMedecin : Enlève un Patient de la liste des patient recus par un medecin
 * @param m : le medecin recevant
 * @param patient : le patient qui doit être retiré de la liste
 * @return 1 si l'enlevement du patient à la liste a bien été réalisé 0 sinon (le medecin ne connaissait pas ce patient ou autre)
 */
int DeletePatientRecuMedecin(Medecin * m, Patient * patient){
    /*if(m->nb_patients_recus == 0){
        printf("Le medecin %s n'a pas encore recu de patient ici.\n", m->nom);
        return -1;
    }
    m->patient_recus + m->nb_patients_recus = NULL;*/
    /*for(){
        Replace les patients suicvant le patient retiré dans l'ordre
    }*/
    //m->nb_patients_recus--;
    return 0;
}

/**********************************************************************************************************************/
                                                /*ListMedecin*/
/**********************************************************************************************************************/

/**
 * Static newNodeMedecin : Permet de créer dynamiquement un nouveau node de Medecin pour la liste
 * @param Medecin : le Medecin pointé par ce nouveau noeud
 * @param previous : le noeud précédant le nouveau noeud dans la liste
 * @param next : le prochain noeud de la liste
 * @return un pointeur sur le nouveau noeud créé
 */
static NodeMedecin * newNodeMedecin(Medecin * medecin, NodeMedecin * previous, NodeMedecin * next){
    NodeMedecin * newNode = (NodeMedecin *) malloc(sizeof(NodeMedecin));
    newNode->medecin = medecin;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * static freeNodeMedecin : Permet de delete proprement (avec un free) un nodeMedecin
 * @param n : le node à delete
 */
static void freeNodeMedecin(NodeMedecin * n){
    free((void*) n);
}


/**
 * ListMedecin_init : Initialise correctement une liste de NodeMedecin en mettant reliant sentinel_begin et end entre eux
 * et en mettant current à NULL en dehors de la liste
 * @param l : la liste à initialiser
 */
void ListMedecin_init(ListMedecin * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
    }
}

/**
 * ListMedecin_isEmpty : Vérifie si la liste de Medecin est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListMedecin_isEmpty(ListMedecin * l){
    if (l != NULL){
        return  l->sentinel_begin.next == &(l->sentinel_end);
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
    if(l != NULL && !ListMedecin_isOutOfList(l)){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListMedecin_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListMedecin_setOnLast(ListMedecin * l){
    if(l != NULL && !ListMedecin_isOutOfList(l)){
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
 * ListMedecin_setOnPrevious : Positionne le pointeur courant sur l'élément avant lui dans la liste
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
    return l->current->medecin;
}