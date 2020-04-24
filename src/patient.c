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
 * @return un pointeur sur le patient créé
 */
Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel){

    Patient * p = (Patient *) malloc(sizeof(Patient));
    p->nom = nom;
    p->prenom = prenom;
    p->date_naissance = CreerDate(annee_naissance, mois_naissance, jour_naissance);
    p->adresse_mail = mail;
    p->numero_telephone = num_tel;

    p->medecins_consultes = (ListMedecin *) malloc(sizeof(struct ListMedecin));
    ListMedecin_init(p->medecins_consultes);

    return p;
}

/**
 * DeletePatient : Supprime proprement une instance de la structure patient
 * @param patient : le patient à supprimer
 */
void DeletePatient(Patient * patient){
    FreeDate(patient->date_naissance);
    ListMedecin_free(patient->medecins_consultes);
    free((void *) patient);
}

/**
 * AffichePatient : Affiche les informations d'un patient dans la console
 * @param p : le patient
 */
void AffichePatient(Patient * p){
    printf("Le patient %s %s né le %d/%d/%d est contactable au %s ou par mail à l'adresse suivante : %s.\n",
            p->nom, p->prenom, p->date_naissance->jour, p->date_naissance->mois, p->date_naissance->annee,
            p->numero_telephone, p->adresse_mail);
    printf("Flemme d'afficher la liste des medecins consultés pour l'instant.\n");
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
    p->date_naissance->annee = an;
    p->date_naissance->mois = mois;
    p->date_naissance->jour = jour;
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

/********************************************************************************************************************/
                                             /*Getteurs de Patient*/
/*******************************************************************************************************************/

/**
 * getNomPatient : retourne le nom et le prénom du patient sous forme de char* (pour l'affichage du RDV)
 * @param p : le patient dont on veut le nom
 * @return une chaine de caractères avec le nom et le prénom du patient
 */
char * getNomPatient(Patient *p){
    char * nom = "";
    strcpy(nom,p->nom);
    strcat(nom, " ");
    strcat(nom, p->prenom);
    return nom;
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
 * getInfoPatient : Place les infos du patient dans infos
 * @param infos : La char* dans lequel on met les infos
 * @param p : le patient dont on veut les informations
 */
void getInfoPatient(char* infos, Patient* p){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    char * tmp = (char*) malloc(10);
    strcpy(infos,getNomPatient(p));
    strcat(infos,"\nNé(e) le : ");

    getDateNaissancePatient(tmp, p);
    strcat(infos, tmp);
    free((void*) tmp);

    strcat(infos, "\n@ : ");
    strcat(infos, getAdresseMailPatient(p));
    strcat(infos, "\nTel : ");
    strcat(infos, getNumeroTelephonePatient(p));
}

/********************************************************************************************************************/
                                    /*Gestion des Medecins Consultes*/
/*******************************************************************************************************************/

/**
 * AddMedecincConsultePatient : Ajoute un Medecin à la première position de la liste des medecins consultés par un patient
 * @param p : le patient consultant
 * @param medecin : le medecin consulté
 * @return 1 si le mèdecin a bien été ajouté à la liste 0 sinon (mèdecin déjà consulté par exemple)
 */
int AddMedecinConsultePatient(Patient * p, Medecin * medecin){

    /*On vient tester si le mèdecin n'a pas déjà été consulté si la liste n'est pas vide*/
    if(!ListMedecin_isEmpty(p->medecins_consultes)){
        for(ListMedecin_setOnFirst(p->medecins_consultes); !ListMedecin_isOutOfList(
            p->medecins_consultes); ListMedecin_setOnNext(p->medecins_consultes)) {
            if(ListMedecin_getCurrent(p->medecins_consultes) == medecin){
                printf("Le mèdecin %s %s a déjà été consulté par le patient %s %s, il n'est donc pas ajouté à la liste.\n", medecin->nom, medecin->prenom, p->nom, p->prenom);
                return 0;
            }
        }
    }

    //Ajout dans le cas où c'est le premier mèdecin consulté (setup avec sentinel_end)
    if(ListMedecin_isEmpty(p->medecins_consultes)){
        NodeMedecin * newNode = newNodeMedecin(medecin, &(p->medecins_consultes->sentinel_begin), &(p->medecins_consultes->sentinel_end));
        p->medecins_consultes->sentinel_begin.next = newNode;
        p->medecins_consultes->sentinel_end.previous = newNode;
        printf("Le mèdecin est le premier mèdecin consulté par le patient, il a bien été ajouté.\n");
        return 1;
    }

    //Ajout au début de la liste du medecin si le patient avait déjà consulté d'autres medecin
    ListMedecin_setOnFirst(p->medecins_consultes);
    NodeMedecin * newNode = newNodeMedecin(medecin, &(p->medecins_consultes->sentinel_begin), p->medecins_consultes->current);
    p->medecins_consultes->sentinel_begin.next = newNode;
    p->medecins_consultes->current->previous = newNode;
    printf("Le medecin a été ajouté au début de la liste du patient.\n");
    return 1;
}
/**
 * DeleteMedecinPatient : Enleve un Medecin de la liste des medecins consultés par un patient
 * @param p : le patient à qui on retire un medecin consultés
 * @param medecin : le medecin qui n'a pas été consulté
 * @return 1 si l'enlevement du mèdecin a bien été réalisé 0 sinon (le patient n'avait pas consulté ce mèdecin par exemple)
 */
int DeleteMedecinConsultePatient(Patient * p, Medecin * medecin){

    //Cas où la liste est vide
    if(ListMedecin_isEmpty(p->medecins_consultes)){
        printf("La liste des mèdecins consultés par le patient %s est vide, on ne peut donc pas y retirer le mèdecin %s.\n", p->nom, medecin->nom);
        return 0;
    }

    //On cherche si le mèdecin a été consulté par le patient
    for (ListMedecin_setOnFirst(p->medecins_consultes); !ListMedecin_isOutOfList(
            p->medecins_consultes); ListMedecin_setOnNext(p->medecins_consultes)) {

        //Si on le trouve on le retire et on quitte la fonction
        if (ListMedecin_getCurrent(p->medecins_consultes) == medecin) {
            p->medecins_consultes->current->previous->next = p->medecins_consultes->current->next;
            p->medecins_consultes->current->next->previous = p->medecins_consultes->current->previous;
            freeNodeMedecin(p->medecins_consultes, p->medecins_consultes->current);
            printf("Le mèdecin %s a bien été retiré de la liste des mèdecins consulté par le patient %s.\n", medecin->nom, p->nom);
            return 1;
        }
    }

    /*Si on n'a pas trouvé le mèdecin on l'affiche et on return 0*/
    printf("Le patient %s n'a pas consuté le mèdecin %s, on ne peut donc pas le retirer de la liste.\n", p->nom, medecin->nom);
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
 * reeNodePatient : Permet de delete proprement (avec un free) un nodePatient
 * @param n : le node à delete
 */
void freeNodePatient(ListPatient *l, NodePatient * n){
    //On place current sur l'objet avant le noeud qu'on veut supprimer
    ListPatient_setOnPrevious(l);
    //On set les pointeurs des objets précédants et suivants le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    //et enfin on supprime le noeud
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
    if (l != NULL && !ListPatient_isEmpty(l)){
        for (ListPatient_setOnFirst(l); !ListPatient_isOutOfList(l); ListPatient_setOnNext(l)){
            freeNodePatient(l, l->current);
        }
    }
    free((void *) l);
}

/**
 * ListPatient_isEmpty : Vérifie si la liste de Patient est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
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
    if(l != NULL && l->current != NULL){
        return l->current->patient;
    }
    return NULL;
}

