#include "rendezvous.h"

/**
 * CreerRendezVous : Creer dynamiquement un objet RendezVous
 * @param an : l'annee
 * @param mois : le mois
 * @param jour : le jour
 * @param heure : l'heure (heure) du début du rdv
 * @param minute : l'heure (minute) du début du rdv
 * @param duree : la duree du rdv
 * @param lieu : le lieu du rdv
 * @param patient : le patient demandant le rdv
 * @param médecin : le medecin choisi
 * @param motif : le motif du rdv
 * @return le rdv créé
 */

RendezVous * CreerRendezVous(int an, int mois, int jour, double heure_debut, int duree, char * lieu, Patient * patient, Medecin * medecin, char * motif){

    RendezVous * rdv = (RendezVous *) malloc(sizeof(RendezVous));
    rdv->heure_debut = heure_debut;
    rdv->heure_fin = heure_debut + (double) (duree/60);
    CreerDate(an, mois, jour);
    rdv->lieu = lieu;
    rdv->patient = patient;
    rdv->medecin = medecin;
    rdv->motif = motif;
    return rdv;
}

/**
 * AnnulerRendezVous : Annuler un RendezVous, l'initialiser à vide
 * @param rdv : le rdv qu'on veut annuler
 * @return 1 si le rdv a bien été annulé
 */
void AnnulerRendezVous(RendezVous * rdv){
    FreeDate(rdv->date);
    free((void *) rdv);
}

/**
 * DeplacerRendezVous : Deplacer un RendezVous
 * @param rdv : le rdv qu'on veut deplacer
 * @param n_an : nouvelle année du rdv
 * @param n_mois : nouveau mois du rdv
 * @param n_jour : nouveau jour du rdv
 * @param n_heure : nouvelle heure du rdv
 * @param n_minute : nouvelle minute de l'horaire du rdv
 * @param n_duree : nouvelle duree du rdv
 * @return le rdv deplacé
 */
RendezVous * DeplacerRendezVous(RendezVous * rdv, int n_an, int n_mois, int n_jour, double n_heure_debut, int n_duree){
    rdv->date->annee=n_an;
    rdv->date->mois=n_mois;
    rdv->date->jour=n_jour;

    rdv->heure_debut = n_heure_debut;
    rdv->heure_fin = n_heure_debut + (double) (n_duree/60);
    return rdv;
}
