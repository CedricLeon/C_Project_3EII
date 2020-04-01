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

RendezVous * CreerRendezVous(int an, int mois, int jour, int heure, int minute, int duree, char * lieu, Patient * p, Medecin * m, char * motif){
    RendezVous * rdv = (RendezVous *)malloc(sizeof(RendezVous));

    rdv->date->annee=an;
    rdv->date->mois=mois;
    rdv->date->jour=jour;
    rdv->heure=heure;
    rdv->minute=minute;
    strcpy(rdv->lieu, lieu);
    rdv->patient=p;
    rdv->medecin=m;
    strcpy(rdv->motif, motif);

    return rdv;
}

/**
 * AnnulerRendezVous : Annuler un RendezVous, l'initialiser à vide
 * @param rdv : le rdv qu'on veut annuler
 * @return 1 si le rdv a bien été annulé
 */
int AnnulerRendezVous(RendezVous * rdv){
    free(rdv->date);
    rdv->heure=0;
    rdv->minute=0;
    rdv->duree=0;
    free(rdv->patient);
    free(rdv->medecin);

    free((void *) rdv);

    return 1;
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
RendezVous * DeplacerRendezVous(RendezVous * rdv, int n_an, int n_mois, int n_jour, int n_heure, int n_minute, int n_duree){
    rdv->date->annee=n_an;
    rdv->date->mois=n_mois;
    rdv->date->jour=n_jour;
    rdv->heure=n_heure;
    rdv->minute=n_minute;
    rdv->duree=n_duree;

    return rdv;
}
