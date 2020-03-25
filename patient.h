#ifndef PATIENT_H
#define PATIENT_H

#include "date.h"
#include "rendezvous.h"     //Pour l'inscription du patient : à revoir plus tard

#define NB_MAX_MEDECINS_CONSULTES 10    //Nombre arbitraire à modifié plus tard

typedef struct Patient Patient;     /*Je pense pas que il faille definir les 2 struct à la fois dans patient.h et medecin.h mais comme ca ca compile ...*/
typedef struct Medecin Medecin;
/**
 * Structure patient représentant un patient qui vient consulté dans l'application
 */
struct Patient{
    char * nom;
    char * prenom;
    Date * date_naissance;
    char * adresse_mail;
    char * numero_telephone;
    Medecin * medecins_consultes;
    int nb_medecins_consultes;
};


Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel);
void DeletePatient(Patient * patient);

//int InscriptionPatient(Patient * patient, RendezVous * rdv);              //A implémenter quand toutes les structures seront completes et testées

/* Setteurs */
void SetNomPatient(Patient * p, char * nom);
void SetPrenomPatient(Patient * p, char * prenom);
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour);
void SetAdresseMailPatient(Patient * p, char * mail);
void SetNumeroTelephonePatient(Patient * p, char * tel);

/* Gestion de la liste des mèdecins consultés par le patient */
int InitMedecinConsultesPatient(Patient * patient);
void FreeMedecinsConsultesPatient(Patient * patient);

int AddMedecinPatient(Patient * p, Medecin * medecin);
int DeleteMedecinPatient(Patient * p, Medecin * medecin);


#endif