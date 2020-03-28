#ifndef MEDECIN_H
#define MEDECIN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_MAX_PATIENT_RECUS 500    //Nombre arbitraire à modifié plus tard (Elisabeth)

typedef struct Medecin Medecin;             /*Je pense pas que il faille definir les 2 struct à la fois dans patient.h et medecin.h mais comme ca ca compile ...*/
typedef struct Patient Patient;

/**
 * Structure Medecin représentant un Medecin exercant dans l'hopital
 */
struct Medecin{
    char * nom;
    char * prenom;
    char ** specialites;            //medecin->specialites = (char **) malloc(NB_MAX_SPECIALITES * sizeof(char*));
    char ** diplomes;               //medecin->diplomes = (char **) malloc(NB_MAX_DIPLOMES * sizeof(char*));        Pour une V1 ou V2 je pense
    char * adresse_mail;
    char * numero_telephone;
    Patient * patient_recus;
    int nb_patients_recus;
    char * numero_RPS;
};

/*On gerera les specialites, les diplomes et les patients dans d'autres fonctions ce sera plus simple je pense
 * car le medecin peut continuer de se former ou autre */
Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS);
void DeleteMedecin(Medecin * medecin);

void SetNomMedecin(Medecin * medecin, char * nom);
void SetPrenomMedecin(Medecin * medecin, char * prenom);
void SetAdresseMailMedecin(Medecin * medecin, char * mail);
void SetNumeroTelephoneMedecin(Medecin * medecin, char * tel);
void SetNumeroRPSMedecin(Medecin * medecin, char * num_RPS);


/* Gestion de la liste des patients recus par le medecin*/
int InitPatientRecusMedecin(Medecin * medecin);
void FreePatientRecusMedecin(Medecin * medecin);

int AddPatientRecuMedecin(Medecin * m, Patient * patient);
int DeletePatientRecuMedecin(Medecin * m, Patient * patient);

/**********************************************************************************************************************/
                                                /*ListMedecin*/
/**********************************************************************************************************************/

/**
 * Structure NodeMedecin permettant de créer une Doubly linked list pour la liste des medecins consultés par un patient
 */
typedef struct NodeMedecin{
    Medecin * medecin;
    struct NodeMedecin * previous;
    struct NodeMedecin * next;
}NodeMedecin;

typedef struct{
    NodeMedecin * first;
    NodeMedecin * current;
    NodeMedecin * last;
}ListMedecin;

void ListMedecin_init(ListMedecin * l);

int ListMedecin_isEmpty(ListMedecin * l);
int ListMedecin_isFirst(ListMedecin * l);
int ListMedecin_isLast(ListMedecin * l);
int ListMedecin_isOutOfList(ListMedecin * l);

void ListMedecin_setOnFirst(ListMedecin * l);
void ListMedecin_setOnLast(ListMedecin * l);
void ListMedecin_setOnNext(ListMedecin * l);
Medecin * ListMedecin_getCurrent(ListMedecin * l);

//void ListMedecin_printList(ListMedecin * l);          A voir si c'est nécessaire



#endif
