#ifndef PATIENT_H
#define PATIENT_H

#include "GPCalendar/Model/Structures.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/dossier_medical.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Structure patient représentant un patient qui vient consulté dans l'application
 */
struct Patient{
    char * nom;
    char * prenom;
    Date * date_naissance;
    char * adresse_mail;
    char * numero_telephone;
    char * numero_secu_social;
    DossierMedical * dossierMedical;
};


Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel, char * numero_secu_social);
void DeletePatient(Patient * patient);

void AffichePatient(Patient * p); //Utilisée pour le debugging
void AccesDossierMedical(Patient * p);
void PrintListOrdonnances(Patient* p);

/* Setteurs */ /*en vrai ça sert à rien*/
void SetNomPatient(Patient * p, char * nom);
void SetPrenomPatient(Patient * p, char * prenom);
void SetDateNaissancePatient(Patient * p, int an, int mois, int jour);
void SetAdresseMailPatient(Patient * p, char * mail);
void SetNumeroTelephonePatient(Patient * p, char * tel);
void setNumeroSecuSocialePatient(Patient * p, char * secu);

/* Getteurs */ /*idem*/
void getNomPatient(char * nom, Patient *p);
void getDateNaissancePatient(char* infos, Patient* p);
char * getAdresseMailPatient(Patient * p);
char * getNumeroTelephonePatient(Patient * p);
char * getNumeroSecuSocialePatient(Patient * p);
void getInfoPatient(char* infos, Patient* p);

int AddMedecinConsultePatient(Patient * p, Medecin * medecin);
int DeleteMedecinConsultePatient(Patient * p, Medecin * medecin);

/**********************************************************************************************************************/
                                                /*ListPatient*/
/**********************************************************************************************************************/

/**
 * Structure NodePatient permettant de créer une Doubly linked list avec des sentinels pour la liste des Medecins consultés par un patient
 */
typedef struct NodePatient{
    Patient * patient;
    struct NodePatient * previous;
    struct NodePatient * next;
}NodePatient;

struct ListPatient{
    NodePatient sentinel_begin;
    NodePatient * current;
    NodePatient sentinel_end;
};

NodePatient * newNodePatient(Patient * patient, NodePatient * previous, NodePatient * next);
void freeNodePatient(ListPatient *l, NodePatient * n);

void ListPatient_init(ListPatient * l);
void ListPatient_free(ListPatient * l);

int ListPatient_add(ListPatient * l, Patient * p);

int ListPatient_isEmpty(ListPatient * l);
int ListPatient_isFirst(ListPatient * l);
int ListPatient_isLast(ListPatient * l);
int ListPatient_isOutOfList(ListPatient * l);

void ListPatient_setOnFirst(ListPatient * l);
void ListPatient_setOnLast(ListPatient * l);
void ListPatient_setOnNext(ListPatient * l);
void ListPatient_setOnPrevious(ListPatient * l);
Patient * ListPatient_getCurrent(ListPatient * l);

//void ListPatient_printList(ListPatient * l);          A voir si c'est nécessaire

#endif
