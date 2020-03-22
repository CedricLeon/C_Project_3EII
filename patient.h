#ifndef PATIENT_H
#define PATIENT_H

#include "date.h"
#include "rendezvous.h"

#define NB_MAX_MEDECINS_CONSULTES 10

typedef struct Patient Patient;     /*Je pense pas que il faille definirles 2 struct à la fois dans patient.h et medecin.h mais comme ca ca compile ...*/
typedef struct Medecin Medecin;

struct Patient{
    char * nom;
    char * prenom;
    Date * date_naissance;    //Il y a certainement un format date en C, � voir si c'est plus facile � g�rer   --> pourquoi ne pas faire une structure date ? OK
    char * adresse_mail;
    char * numero_telephone; //On pourrait peut-�tre faire un long int mais quel inter�t ?
    Medecin * medecins_consultes;
    int nb_medecins_consultes;
};

Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel);
void DeletePatient(Patient * patient);

//int InscriptionPatient(Patient * patient, RendezVous * rdv); //Si j'ai bien compris

/* Setteurs */
void SetNomPatient(Patient * p, char * nom);
void SetPrenomPatient(Patient * p, char * prenom);
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour);
void SetAdresseMailPatient(Patient * p, char * mail);
void SetNumeroTelephonePatient(Patient * p, char * tel);


int InitMedecinConsultesPatient(Patient * patient);
void FreeMedecinsConsultesPatient(Patient * patient);

int AddMedecinPatient(Patient * p, Medecin * medecin);
int DeleteMedecinPatient(Patient * p, Medecin * medecin); //Si jamais on a besoin de retirer un medecin


#endif