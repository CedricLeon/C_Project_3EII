#include "GPCalendar/Model/rendezvous.h"

/**
 * CreerRendezVous : Creer dynamiquement un objet RendezVous
 *                   Et ajoute le patient et le médecin à leur liste respective de personnes rencontrées
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
RendezVous * CreerRendezVous(int an, int mois, int jour, double heure_debut, double duree, char * lieu, Patient * patient, Medecin * medecin, char * motif){

    RendezVous * rdv = (RendezVous *) malloc(sizeof(RendezVous));
    rdv->heure_debut = heure_debut;
    rdv->heure_fin = heure_debut + (duree/60);
    rdv->date = CreerDate(an, mois, jour);

    rdv->lieu = (char*) malloc(strlen(lieu)+1);
    strcpy(rdv->lieu, lieu);

    rdv->patient = patient;
    rdv->medecin = medecin;

    AddMedecinConsultePatient(patient, medecin);
    AddPatientRecuMedecin(medecin, patient);

    rdv->motif = (char*) malloc(strlen(motif)+1);
    strcpy(rdv->motif, motif);

    return rdv;
}

/**
 * FreeRendezVous : Free un objet rdv (seulement sa date et le rdv en lui-même), on ne touche pas au patient et au
 *                  medecin car ils existent toujours dans d'autres rdv
 * @param rdv : le rdv à free
 */
void FreeRendezVous(RendezVous * rdv){
    //printf("\t\t\t\t\tFreeRendezVous() : Le RendezVous du %d/%d/%d à %2.1f a bien été free.\n", rdv->date->jour, rdv->date->mois, rdv->date->annee, rdv->heure_debut);
    FreeDate(rdv->date);
    free((void*) rdv->motif);
    free((void*) rdv->lieu);
    free((void *) rdv);
}
/**
 * EqualsRendezVous : fonction permettant de savoir si 12 rendez-vous sont les memes en comparant leurs dates et leurs horaires
 * @param rdv1 }
 *             } Les 2 rdv à comparer
 * @param rdv2 }
 * @return 1 si ils sont égaux
 *         0 sinon
 *         -1 si l'un des rdv est NULL
 */
int EqualsRendezVous(RendezVous * rdv1, RendezVous * rdv2){
    if(rdv1 == NULL || rdv2 == NULL)
    {
        printf("EqualsRendezVous() : L'un des 2 rdv est NULL.\n");
        return -1;
    }
    //test si mêmes dates
    if(DateEgales(rdv1->date, rdv2->date))
    {
        //test mêmes horaires
        if(rdv1->heure_debut == rdv2->heure_debut && rdv1->heure_fin == rdv2->heure_fin)
        {
            //test mêmes motifs et lieux
            if(strcmp(rdv1->lieu, rdv2->lieu) == 0 && strcmp(rdv1->motif,  rdv2->motif) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
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

/**
 * getInfosRendezVous : Place dans une chaine de caractères passée en paramètre les informations d'un RendezVous
 * @param infos : la chaîne qui va contenir les informations
 * @param rdv : le rdv dont on veut les infos
 */
void getInfosRendezVous(char* infos, RendezVous* rdv){

    char* tmp = (char*) malloc(30);

    strcpy(infos, "\tRendez-vous du : ");
    getInfosDate(tmp, rdv->date);
    strcat(infos, tmp);

    strcat(infos,"\n\tDe ");
    sprintf(tmp, "%2.1f", rdv->heure_debut);
    strcat(infos, tmp);
    strcat(infos,"h à ");

    sprintf(tmp, "%2.1f", rdv->heure_fin);
    strcat(infos, tmp);
    strcat(infos,"h.\n\tA l'endroit : ");
    strcat(infos, rdv->lieu);

    strcat(infos,"\n\tEntre le patient \"");
    strcat(infos, rdv->patient->nom);
    strcat(infos, " ");
    strcat(infos, rdv->patient->prenom);
    strcat(infos, "\" et le médecin \"");
    strcat(infos, rdv->medecin->nom);
    strcat(infos, " ");
    strcat(infos, rdv->medecin->prenom);
    strcat(infos, "\".\n\tPour le motif : ");

    strcat(infos, rdv->motif);
    strcat(infos, "\n\n");

    free((void*) tmp);
}
