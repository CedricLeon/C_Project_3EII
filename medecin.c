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
Medecin *CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS){
    Medecin * m;
    m->nom = nom;
    m->prenom = prenom;
    m->adresse_mail = mail;
    m->numero_telephone = num_tel;
    m->numero_RPS = num_RPS;
    return m;
}
/**
 * DeleteMedecin : Supprime proprement une instance de la structure medecin
 * @param medecin : le medecin à supprimer
 */
void DeleteMedecin(Medecin * medecin){
    FreePatientRecusMedecin(medecin);
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

void InitPatientRecusMedecin(Medecin * medecin){
    //medecin->patient_recus = (Patient *) malloc();
}
void FreePatientRecusMedecin(Medecin * medecin);