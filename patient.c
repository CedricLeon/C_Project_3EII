#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "patient.h"


Patient * CreerPatient(char * nom, char * prenom, int annee_naissance, int mois_naissance, int jour_naissance, char * mail, char * num_tel){

    Patient * p;
    p->nom = nom;
    p->prenom = prenom;
    p->date_naissance = CreerDate(annee_naissance, mois_naissance, jour_naissance);
    p->adresse_mail = mail;
    p->numero_telephone = num_tel;

    InitMedecinConsultesPatient(p);
    p->nb_medecins_consultes = 0;

    return p;
}

void DeletePatient(Patient * patient){
    FreeMedecinsConsultesPatient(patient);
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

//int InscriptionPatient(Patient * patient, RendezVous * rdv);


int InitMedecinConsultesPatient(Patient * patient){
    patient->medecins_consultes = (Medecin *) malloc(NB_MAX_MEDECINS_CONSULTES * sizeof(Medecin));
    //Comme c'est un tableau de medecins consultés il faut bien lui donner une taille lors de son initialisation
    //Par défaut jai mis 10 medecins mais on changera plus tard (peut etre allocation dynamique)

    return patient->medecins_consultes != NULL;
}
void FreeMedecinsConsultesPatient(Patient * patient){
    free(patient->medecins_consultes);
}

int AddMedecinPatient(Patient * p, Medecin * medecin){
    if(p->nb_medecins_consultes == NB_MAX_MEDECINS_CONSULTES){
        printf("Le patient %s a déjà consulté trop de medecins différents ici : %d;\n", p->nom,  NB_MAX_MEDECINS_CONSULTES);
        return  -1;
    }
    /*La faut faire mumuse avec la dynamique des pointeurs et je crois que j'ai jamais compris*/
    //p->medecins_consultes + p->nb_medecins_consultes = medecin; // ?????pas sur du tout

    printf("Le patient %s a consultés le medecin %s.\n", p->nom, medecin->nom);
    return 0;   //reussite
}
int DeleteMedecinPatient(Patient * p, Medecin * medecin){
    if(p->nb_medecins_consultes == 0){
        printf("Le Patient %s n'a pas encore consulté de mèdecin ici.\n", p->nom);
        return -1;
    }

    return 0;
}

