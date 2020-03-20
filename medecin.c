#include "medecin.h"

Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS){
    Medecin * m;
    m->nom = nom;
    m->prenom = prenom;
    m->adresse_mail = mail;
    m->numero_telephone = num_tel;
    m->numero_RPS = num_RPS;
    return m;
}

void SetNomMedecin(Medecin * medecin, char * nom){
    medecin->nom = nom;
}
void SetPrenomMedecin(Medecin * medecin, char * prenom){
    medecin->prenom = prenom;
}
void SetAdresseMailMedecin(Medecin * medecin, char * mail){
    medecin->adresse_mail = mail;
}
void SetNumeroTelephoneMedecin(Medecin * medecin, char * tel){
    medecin->numero_telephone = tel;
}
void SetNumeroRPSMedecin(Medecin * medecin, char * num_RPS){
    medecin->numero_RPS = num_RPS;
}


void InitPatientRecusMedecin(Medecin * medecin){
    //medecin->patient_recus = (Patient *) malloc();
}
void FreePatientRecusMedecin(Medecin * medecin);