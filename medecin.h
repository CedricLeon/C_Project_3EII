#ifndef MEDECIN_H
#define MEDECIN_H

typedef struct{
    char * nom;
    char * prenom;
    char ** specialites;    //Pas sûr pour le format mais c'est un tableau de String quoi
    char ** diplomes;       //idem
    char * adresse_mail;
    char * numero_telephone;
    Patient * patient_recus;
    char * numero_RPS;
}Medecin;

/*On gerera les specialites, les diplomes et les patients dans d'autres fonctions ce sera plus simple je pense
 * car le medecin peut continuer de se former ou autre */
Medecin * CreerMedecin(char * nom, char * prenom,  char * mail, char * num_tel, char * num_RPS);

void SetNomMedecin(char * nom);
void SetPrenomMedecin(char * prenom);
void SetAdresseMailMedecin(char * mail);
void SetNumeroTelephoneMedecin(char * tel);
void SetNumeroRPSMedecin(char * num_RPS);

/* Il y aura un malloc à gérer ici*/
void InitPatientRecusMedecin();
/*Donc on gère aussi un potentiel free*/
void FreePatientRecusMedecin();

int AddPatientMedecin(Medecin * m, Patient * patient);
int DeletePatientMedecin(Medecin * m, Patient * patient); //Si jamais on a besoin de retirer un patient

#endif
