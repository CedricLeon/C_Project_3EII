#ifndef MEDECIN_H
#define MEDECIN_H

typedef struct Medecin Medecin;             /*Je pense pas que il faille definir les 2 struct à la fois dans patient.h et medecin.h mais comme ca ca compile ...*/
typedef struct Patient Patient;

struct Medecin{
    char * nom;
    char * prenom;
    char ** specialites;
    char ** diplomes;
    char * adresse_mail;
    char * numero_telephone;
    Patient * patient_recus;
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
void InitPatientRecusMedecin(Medecin * medecin);
void FreePatientRecusMedecin(Medecin * medecin);

int AddPatientMedecin(Medecin * m, Patient * patient);
int DeletePatientMedecin(Medecin * m, Patient * patient);

#endif
