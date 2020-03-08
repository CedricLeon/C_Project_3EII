//
// Created by cleonard on 08/03/2020.
//

#ifndef C_PROJECT_STRUCTURES_H
#define C_PROJECT_STRUCTURES_H

/*Y'a un vrai boulot pour la gestion du nom des fonctions et des attribust, là j'ai fait un peu à l'arrache, je pense qu'il y aura des trucs à changer*/

struct Patient{
    char * nom;
    char * prenom;
    int annee_naissance;    //Il y a certainement un format date en C, à voir si c'est plus facile à gérer
    int mois_naissance;
    int jour_naissance;
    char * adresse_mail;
    char * numero_telephone; //On pourrait peut-être faire un long int mais quel interêt ?
    Medecin * medecins_consultes;
};

Patient * CreerPatient(char * nom, char * prenom, int an, int mois, int jour, char * mail, char * num_tel);
int InscriptionPatient(Patient patient, RendezVous rdv); //Si j'ai bien compris
void SetNomPatient(char * nom);
void SetPrenomPatient(char * prenom);
void SetDateNaissancePatient(int an, int mois, int jour);
void SetAdresseMailPatient(char * mail);
void SetNumeroTelephonePatient(char * tel);

/* Il y aura un malloc à gérer ici*/
void InitMedecinConsultesPatient();
/*Donc on gère aussi un potentiel free*/
void FreeMedecinsConsultesPatient();

int AddMedecinPatient(Patient p, Medecin medecin);
int DeleteMedecinPatient(Patient p, Medecin medecin); //Si jamais on a besoin de retirer un medecin



struct Medecin{
    char * nom;
    char * prenom;
    char ** specialites;    //Pas sûr pour le format mais c'est un tableau de String quoi
    char ** diplomes;       //idem
    char * adresse_mail;
    char * numero_telephone;
    Patient * patient_recus;
    char * numero_RPS; //Je sais pas ce que c'est
};

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

int AddPatientMedecin(Medecin m, Patient patient);
int DeletePatientMedecin(Medecin m, Patient patient); //Si jamais on a besoin de retirer un patient

struct DossierMedical{
    Patient patient;
    Medecin * medecins; //Liste des mèdecins consultés pour ce dossier
    //static int nb_medecins;    // Peut être utile
    Ordonnance * ordonnances; //En vrai on devrait aussi faire une structure ordonnance, c'est plus clean
    //static int nb_ordonnaces;    // idem
    DossierMedical * antecedents; //Liste des précédents passage à l'hopital
    //static int nb_antecedents;    // idem²
};

int CreerDossier(Patient patient);   //On y fera les 3 mallocs
void FreeDossier();                     //Il y aura donc 3 free je pense

void AccesDossier(DossierMedical d);    //Print toutes les infos je suppose

void SetPatientDossier(DossierMedical dm, Patient patient);
int AddMedecinDossierMedical(DossierMedical dm, Medecin medecin);
int AddOrdonnanceDossierMedical(DossierMedical dm, Ordonnance ordonnance);
int AddAntecedentDossierMedical(DossierMedical dm, DossierMedical antecedent);

//void TransfertDossier(DossierMedical dm, ???); //J'avoue que je vois pas trop


struct RendezVous{
    int annee;      //Idem pour le format date
    int mois;
    int jour;
    int heure; // Comment on stocke ça ? 16h30 <=> 16.5 ? ou Alors un attribut heure et un attribut minute ?
    //int minute;
    char * lieu; //Numéro batiment / numero salle ?
    Patient patient;
    Medecin medecin;
    char * motif;
};

int CreerRendezVous(int an, int mois, int jour, int heure, char * lieu, Patient patient, Medecin medecin, char * motif);
int AnnulerRendezVous(); //Je m'arrete là

struct Calendrier{      //Au niveau des dates / jour / mois etc ... je sais pas trop comment gérer ça
    RendezVous * rendez_vous;
    static int taille = 0; //Nombre de rendez-vous actuels dans le calendrier
};

struct Ordonnance{
    //Oui oui ...
};



#endif //C_PROJECT_STRUCTURES_H
