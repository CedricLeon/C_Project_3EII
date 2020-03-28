#include "patient.h"
#include "medecin.h"

/**
 * CreerPatient : Creer une nouvelle instance de la structure Patient avec toutes les informations basiques
 * @param nom : nom du patient
 * @param prenom : prénom du patient
 * @param annee_naissance : Année, mois et jour de naissance du patient
 * @param mois_naissance
 * @param jour_naissance
 * @param mail : adresse mail du patient
 * @param num_tel :numéro de téléphone du patient
 * @return un pointeur sur le patient crée
 */
Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel){

    Patient * p = (Patient *) malloc(sizeof(Patient));
    p->nom = nom;
    p->prenom = prenom;
    p->date_naissance = CreerDate(annee_naissance, mois_naissance, jour_naissance);
    p->adresse_mail = mail;
    p->numero_telephone = num_tel;
    ListMedecin_init(p->medecins_consultes);

    return p;
}

/**
 * DeletePatient : Supprime proprement une instance de la structure patient
 * @param patient : le patient à supprimer
 */
void DeletePatient(Patient * patient){
    free((void *) patient);
}

/**
 * SetNomPatient : Setteur du nom d'un patient
 * @param p : le patient
 * @param nom : le nouveau nom
 */
void SetNomPatient(Patient * p, char * nom){
    p->nom = nom;
}
/**
 * SetPrenomPatient : Setteur du prénom d'un patient
 * @param p : la patient
 * @param prenom : le nouveau prénom
 */
void SetPrenomPatient(Patient * p, char * prenom){
    p->prenom = prenom;
}
/**
 * SetDateNaissancePatient : Setteur de la date de naissance d'un patient
 * @param p : le patient
 * @param an : la nouvelle date de naissance
 * @param mois
 * @param jour
 */
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour){
    p->date_naissance = CreerDate(an, mois, jour);
}
/**
 * SetAdresseMailPatient : Setteur de l'adresse mail d'un patient
 * @param p : la patient
 * @param mail : la nouvelle adresse mail
 */
void SetAdresseMailPatient(Patient * p, char * mail){
    p->adresse_mail = mail;
}
/**
 * SetNumeroTelephonePatient : Setteur du numero de telephone d'un patient
 * @param p : la patient
 * @param tel : le nouveau numero de telephone
 */
void SetNumeroTelephonePatient(Patient * p, char * tel){
    p->numero_telephone = tel;
}

//int InscriptionPatient(Patient * patient, RendezVous * rdv);


/**
 * AddMedecincConsultePatient : Ajoute un Medecin à la première position de la liste des medecins consultés par un patient
 * @param p : le patient consultant
 * @param medecin : le medecin consulté
 * @return 1 si l'ajout du mèdecin a bien été réalisé 0 sinon (le patient a déjà consulté trop de mèdecins ou autre)
 */
int AddMedecinConsultePatient(Patient * p, Medecin * medecin){
    ListMedecin_setOnFirst(p->medecins_consultes);

    /*if(p->nb_medecins_consultes == NB_MAX_MEDECINS_CONSULTES){
        printf("Le patient %s a déjà consulté trop de medecins différents : %d.\nLe medecin n'a donc pas été ajouté à sa liste.;\n", p->nom,  NB_MAX_MEDECINS_CONSULTES);
        return  -1;
    }

    (*(p->medecins_consultes + p->nb_medecins_consultes)) = * medecin;
    p->nb_medecins_consultes++;

    printf("Le patient %s a consultés le medecin %s.\n", p->nom, medecin->nom);*/
    return 0;   //reussite
}
/**
 * DeleteMedecinPatient : Enleve un Medecin de la liste des medecins consultés par un patient
 * @param p : le patient à qui on retire un medecin consultés
 * @param medecin : le medecin qui n'a pas été consulté
 * @return 1 si l'enlevement du mèdecin a bien été réalisé 0 sinon (le patient n'avait pas consulté ce mèdecin par exemple)
 */
int DeleteMedecinConsultePatient(Patient * p, Medecin * medecin){
    /*if(p->nb_medecins_consultes == 0){
        printf("Le Patient %s n'a pas encore consulté de mèdecin ici.\n", p->nom);
        return -1;
    }
    p->medecins_consultes + p->nb_medecins_consultes = NULL;

    p->nb_medecins_consultes--;*/
    return 0;
}

/**********************************************************************************************************************/
                                                /*ListPatient*/
/**********************************************************************************************************************/

/**
 * Static newNodePatient : Permet de créer dynamiquement un nouveau node de patient pour la liste
 * @param patient : le patient pointé par ce nouveau noeud
 * @param previous : le noeud précédant le nouveau noeud dans la liste
 * @param next : le prochain noeud de la liste
 * @return un pointeur sur le nouveau noeud créé
 */
static NodePatient * newNodePatient(Patient * patient, NodePatient * previous, NodePatient * next){
    NodePatient * newNode = (NodePatient *) malloc(sizeof(NodePatient));
    newNode->patient = patient;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * static freeNodePatient : Permet de delete proprement (avec un free) un nodePatient
 * @param n : le node à delete
 */
static void freeNodePatient(NodePatient * n){
    free((void*) n);
}


/**
 * ListPatient_init : Initialise correctement une liste de NodePatient en mettant reliant sentinel_begin et end entre eux
 * et en mettant current à NULL en dehors de la liste
 * @param l : la liste à initialiser
 */
void ListPatient_init(ListPatient * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
    }
}

/**
 * ListPatient_isEmpty : Vérifie si la liste de Patient est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListPatient_isEmpty(ListPatient * l){
    if (l != NULL){
        return  l->sentinel_begin.next == &(l->sentinel_end);
    }
    return -1; //La liste est NULL
}
/**
 * ListPatient_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
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
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
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
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
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
    if(l != NULL && !ListPatient_isOutOfList(l)){
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
    if(l != NULL && !ListPatient_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListPatient_setOnPrevious : Positionne le pointeur courant sur l'élément avant lui dans la liste
 * @param l : la liste
 */
void ListPatient_setOnPrevious(ListPatient * l){
    if(l != NULL && !ListPatient_isOutOfList(l)){
        l->current = l->current->previous;
    }
}
/**
 * ListPatient_getCurrent : Permet d'acceder au Patient pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Patient de l'élément courant de la liste
 */
Patient * ListPatient_getCurrent(ListPatient * l){
    return l->current->patient;
}

