#include "patient.h"

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

    Patient * p;
    p->nom = nom;
    p->prenom = prenom;
    p->date_naissance = CreerDate(annee_naissance, mois_naissance, jour_naissance);
    p->adresse_mail = mail;
    p->numero_telephone = num_tel;
    if(InitMedecinConsultesPatient(p) == -1){
        printf("Le malloc de InitMedecinsConsultesPatient() a échoué ...\n");
    }
    p->nb_medecins_consultes = 0;

    return p;
}

/**
 * DeletePatient : Supprime proprement une instance de la structure patient
 * @param patient : le patient à supprimer
 */
void DeletePatient(Patient * patient){
    FreeMedecinsConsultesPatient(patient);
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
 * InitMedecinConsultesPatient : Initialise à vide la liste des medecins consultés par un patient
 * @param patient : le patient
 * @return 1 si l'initialisation s'est bien passée 0 sinon
 */
int InitMedecinConsultesPatient(Patient * patient){
    patient->medecins_consultes = (Medecin *) malloc(NB_MAX_MEDECINS_CONSULTES * sizeof(Medecin *));
    //Comme c'est un tableau de pointeurs medecins consultés il faut bien lui donner une taille lors de son initialisation
    //Par défaut jai mis 10 medecins mais on changera plus tard (peut etre allocation dynamique)
    return patient->medecins_consultes != NULL;
}
/**
 * FreeMedecinsConsultesPatient : Libère la mémoire de la liste des medecins consultés par un patient
 * @param patient : le patient
 */
void FreeMedecinsConsultesPatient(Patient * patient){
    free(patient->medecins_consultes);
}

/**
 * AddMedecinPatient : Ajoute un Medecin à la liste des medecins consultés par un patient
 * @param p : le patient consultant
 * @param medecin : le medecin consulté
 * @return 1 si l'ajout du mèdecin a bien été réalisé 0 sinon (le patient a déjà consulté trop de mèdecins ou autre)
 */
int AddMedecinConsultePatient(Patient * p, Medecin * medecin){
    if(p->nb_medecins_consultes == NB_MAX_MEDECINS_CONSULTES){
        printf("Le patient %s a déjà consulté trop de medecins différents : %d.\nLe medecin n'a donc pas été ajouté à sa liste.;\n", p->nom,  NB_MAX_MEDECINS_CONSULTES);
        return  -1;
    }

    (*(p->medecins_consultes + p->nb_medecins_consultes)) = * medecin;
    p->nb_medecins_consultes++;

    printf("Le patient %s a consultés le medecin %s.\n", p->nom, medecin->nom);
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
 * ListPatient_init : Initialise correctement une liste de NodePatient en mettant first last et current à NULL
 * @param l : la liste à initialiser
 */
void ListPatient_init(ListPatient * l){
    if (l != NULL){
        l->first = NULL;
        l->current = NULL;
        l->last = NULL;
    }
}

/**
 * ListPatient_isEmpty : Vérifie si la liste de Patient est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListPatient_isEmpty(ListPatient * l){
    if (l != NULL){
        return  NULL == l->first;
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
        return  l->current == l->first;
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
        return  l->current == l->last;
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
        return  NULL == l->current;
    }
    return -1; //La liste est NULL
}

/**
 * ListPatient_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListPatient_setOnFirst(ListPatient * l){
    if(l != NULL && !ListPatient_isOutOfList(l)){
        l->current = l->first;
    }
}
/**
 * ListPatient_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListPatient_setOnLast(ListPatient * l){
    if(l != NULL && !ListPatient_isOutOfList(l)){
        l->current = l->last;
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
 * ListPatient_getCurrent : Permet d'acceder au Patient pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Patient de l'élément courant de la liste
 */
Patient * ListPatient_getCurrent(ListPatient * l){
    return l->current->patient;
}

