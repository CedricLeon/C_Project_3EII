#include "rendezvous.h"

/**
 * CreerRendezVous : Creer dynamiquement un objet RendezVous
 * @param an : l'annee
 * @param mois : le mois
 * @param jour : le jour
 * @param heure_debut : l'heure ((sous forme de double : 16.5 <=> 16H30) du début du rdv
 * @param duree : la duree du rdv, avec on détermine heure_fin du rdv
 * @param lieu : le lieu du rdv
 * @param patient : le patient demandant le rdv
 * @param médecin : le medecin choisi pour le rdv
 * @param motif : le motif du rdv
 * @return le rdv créé
 */
RendezVous * CreerRendezVous(int an, int mois, int jour, double heure_debut, int duree, char * lieu, Patient * patient, Medecin * medecin, char * motif){

    RendezVous * rdv = (RendezVous *) malloc(sizeof(RendezVous));
    rdv->heure_debut = heure_debut;
    rdv->heure_fin = heure_debut + (double) (duree/60);
    rdv->date = CreerDate(an, mois, jour);
    rdv->lieu = lieu;
    rdv->patient = patient;
    rdv->medecin = medecin;
    rdv->motif = motif;
    return rdv;
}

/**
 * FreeRendezVous : Free un objet rdv (seulement sa date et le rdv en lui-même), on ne touche pas au patient et au
 *                  medecin car il existent toujours dans d'autres rdv
 * @param rdv : le rdv à free
 */
void FreeRendezVous(RendezVous * rdv){
    printf("\t\t\t\t\tFreeRendezVous() : Le RendezVous du %d/%d/%d à %2.1f a bien été free.\n", rdv->date->jour, rdv->date->mois, rdv->date->annee, rdv->heure_debut);
    FreeDate(rdv->date);
    free((void *) rdv);         //Apparement le rdv est déjà free mais je sais pas où ???
}

/**
 * AnnulerRendezVous : Annuler un RendezVous, l'initialiser à vide          FONCTION PAS FINIE
 * @param rdv : le rdv qu'on veut annuler
 * @return 1 si le rdv a bien été annulé
 */
int AnnulerRendezVous(RendezVous * rdv){

    //On test si le rendez-vous est passé, si c'est le cas on ne peut pas l'annuler, on regarde pas l'heure pour cela : si le rdv est passé mais du jour même on peut l'annuler
    Date * date_courante = CreerDateCourante();
    if ((date_courante->annee - rdv->date->annee)>0 || (date_courante->mois - rdv->date->mois)>0 || (date_courante->jour - rdv->date->jour)>0){

        //Si c'était le premier rdv entre un medecin et un patient il faut les retirer de leurs listes medecins_consultes et patient_recus respectives

        /*Pour cela on parcourt tout les rdv du patient dans le calendrier et on cherche le medecin*/

        if(DeleteMedecinConsultePatient(rdv->patient, rdv->medecin) && DeletePatientRecuMedecin(rdv->medecin, rdv->patient)) {
            char * tmpP = (char*) malloc(100);
            char * tmpM = (char*) malloc(100);
            getNomPatient(tmpP, rdv->patient);
            getNomMedecin(tmpM, rdv->medecin);
            printf("Il n'a pas été possible de retirer le mèdecin %s de la liste de mèdecins consultés du patient %s.\n Donc le rdv n'a pas était annulé.\n", tmpM, tmpP);
            free((void*) tmpP);
            free((void*) tmpM);
        }

        //Une fois ceci fait on libère l'instance Date liée au rdv et on free le tout
        FreeDate(rdv->date);
        free((void *) rdv);
        printf("Le rendez-vous daté du %d/%d/%d a bien été annulé.\n", rdv->date->jour, rdv->date->mois, rdv->date->jour);
        return 1;
    }
    //On oublie pas de free les objets utilisés
    FreeDate(date_courante);
    printf("Impossible d'annuler ce rendez-vous, il est daté du %d/%d/%d et est déjà passé.\n", rdv->date->jour, rdv->date->mois, rdv->date->jour);
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
RendezVous * DeplacerRendezVous(RendezVous * rdv, int n_an, int n_mois, int n_jour, double n_heure_debut, int n_duree){
    rdv->date->annee=n_an;
    rdv->date->mois=n_mois;
    rdv->date->jour=n_jour;

    rdv->heure_debut = n_heure_debut;
    rdv->heure_fin = n_heure_debut + (double) (n_duree/60);
    return rdv;
}
