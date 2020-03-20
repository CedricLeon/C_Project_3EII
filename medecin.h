#ifndef MEDECIN_H
#define MEDECIN_H

typedef struct Medecin Medecin;
typedef struct{
    char * nom;
    char * prenom;
    char ** specialites;    //Pas s�r pour le format mais c'est un tableau de String quoi
    char ** diplomes;       //idem
    char * adresse_mail;
    char * numero_telephone;
    Patient * patient_recus;
    char * numero_RPS;
}

/*On gerera les specialites, les diplomes et les patients dans d'autres fonctions ce sera plus simple je pense
 * car le medecin peut continuer de se former ou autre */
Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS);

void SetNomMedecin(Medecin * medecin, char * nom);
void SetPrenomMedecin(Medecin * medecin, char * prenom);
void SetAdresseMailMedecin(Medecin * medecin, char * mail);
void SetNumeroTelephoneMedecin(Medecin * medecin, char * tel);
void SetNumeroRPSMedecin(Medecin * medecin, char * num_RPS);

/* Il y aura un malloc � g�rer ici*/
void InitPatientRecusMedecin(Medecin * medecin);
/*Donc on g�re aussi un potentiel free*/
void FreePatientRecusMedecin(Medecin * medecin);

int AddPatientMedecin(Medecin * m, Patient * patient);
int DeletePatientMedecin(Medecin * m, Patient * patient); //Si jamais on a besoin de retirer un patient

#endif
