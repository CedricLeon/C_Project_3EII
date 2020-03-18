#ifndef PATIENT_H
#define PATIENT_H

#include "date.h"
#include "rendezvous.h"

typedef struct{
    char * nom;
    char * prenom;
    Date * date_naissance;    //Il y a certainement un format date en C, � voir si c'est plus facile � g�rer   --> pourquoi ne pas faire une structure date ? OK
    char * adresse_mail;
    char * numero_telephone; //On pourrait peut-�tre faire un long int mais quel inter�t ?
    Medecin * medecins_consultes;
}Patient;

Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel);
int InscriptionPatient(Patient * patient, RendezVous * rdv); //Si j'ai bien compris
void SetNomPatient(char * nom);
void SetPrenomPatient(char * prenom);
void SetDateNaissancePatient(int an, int mois, int jour);
void SetAdresseMailPatient(char * mail);
void SetNumeroTelephonePatient(char * tel);

/* Il y aura un malloc � g�rer ici*/
void InitMedecinConsultesPatient();
/*Donc on g�re aussi un potentiel free*/
void FreeMedecinsConsultesPatient();

int AddMedecinPatient(Patient * p, Medecin * medecin);
int DeleteMedecinPatient(Patient * p, Medecin * medecin); //Si jamais on a besoin de retirer un medecin


#endif
