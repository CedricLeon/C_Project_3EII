#include "medecin.h"

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
    Medecin * m;
    m->nom = nom;
    m->prenom = prenom;
    m->adresse_mail = mail;
    m->numero_telephone = num_tel;
    m->numero_RPS = num_RPS;
    if(InitPatientRecusMedecin(m) == -1){
        printf("Le malloc de InitPatientRecusMedecin() a échoué ...\n");
    }
    m->nb_patients_recus = 0;
    return m;
}
/**
 * DeleteMedecin : Supprime proprement une instance de la structure medecin
 * @param medecin : le medecin à supprimer
 */
void DeleteMedecin(Medecin * medecin){
    FreePatientRecusMedecin(medecin);
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
 * InitPatientRecusMedecin : Initialisation de la liste des Patient Recus par un medecin
 * @param medecin : le medecin recevant
 */
int InitPatientRecusMedecin(Medecin * medecin){
    medecin->patient_recus = (Patient *) malloc(NB_MAX_PATIENT_RECUS * sizeof(Patient *));
    return medecin->patient_recus != NULL;
}
/**
 * FreePatientRecusMedecin : Libère la mémoire de la liste des patient recus par un medecin
 * @param medecin : le medecin recevant
 */
void FreePatientRecusMedecin(Medecin * medecin){
    free(medecin->patient_recus);
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
    if(m->nb_patients_recus == 0){
        printf("Le medecin %s n'a pas encore recu de patient ici.\n", m->nom);
        return -1;
    }
    m->patient_recus + m->nb_patients_recus = NULL;
    /*for(){
        Replace les patients suicvant le patient retiré dans l'ordre
    }*/
    m->nb_patients_recus--;
    return 0;
}