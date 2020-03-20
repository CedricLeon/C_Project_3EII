#include <string.h>
#include "patient.h"


Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel){

    Patient * p;
    p->nom = nom;
    p->prenom = prenom;
    p->date_naissance = CreerDate(annee_naissance, mois_naissance, jour_naissance);
    p->adresse_mail = mail;
    p->numero_telephone = num_tel;

    return p;
}
void SetNomPatient(Patient * p, char * nom){
    p->nom = nom;
}
void SetPrenomPatient(Patient * p, char * prenom){
    p->prenom = prenom;
}
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour){
    p->date_naissance = CreerDate(an, mois, jour);
}
void SetAdresseMailPatient(Patient * p, char * mail){
    p->adresse_mail = mail;
}
void SetNumeroTelephonePatient(Patient * p, char * tel){
    p->numero_telephone = tel;
}

int InscriptionPatient(Patient * patient, RendezVous * rdv);
/* Il y aura un malloc � g�rer ici*/
void InitMedecinConsultesPatient(){

}
/*Donc on g�re aussi un potentiel free*/
void FreeMedecinsConsultesPatient(){

}

int AddMedecinPatient(Patient * p, Medecin * medecin);
int DeleteMedecinPatient(Patient * p, Medecin * medecin); //Si jamais on a besoin de retirer un medecin

