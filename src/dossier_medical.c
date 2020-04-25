#include "dossier_medical.h"

/**
 * CreerDossier : Creer dynamiquement un objet DossierMedical
 * @param patient : le patient concerne par le dossier=
 * @return le dossier créé
 */
DossierMedical * CreerDossier(Patient * patient){
    DossierMedical * dm = (DossierMedical *)malloc(sizeof(DossierMedical));

    dm->patient=patient;
    dm->medecins=patient->medecins_consultes;

    ListMedecin_setOnFirst(dm->medecins);
    while(ListMedecin_isLast(dm->medecins)!=1){
        dm->nb_medecins+=1;
        ListMedecin_setOnNext(dm->medecins);
    }

    dm->ordonnances=(ListOrdonnance *)malloc(sizeof(ListOrdonnance));
    ListOrdonnance_init(dm->ordonnances);
    dm->nb_ordonnances=0;

    dm->antecedents="";
    dm->nb_antecedents=0;

    return dm;
}

/**
 * FreeDossier : Free un objet DossierMedical
 * @param dm : le dossier à supprimer
 */
void FreeDossier(DossierMedical * dm){
    DeletePatient(dm->patient); //pas sûre mais pour moi quand tu supprimes le dossier médical d'un patient c'est que ce patient est parti/mort/jsp mais ne doit plus apparaître
    ListOrdonnance_free(dm->ordonnances); //pareil
    free((void *) dm);
}

void AccesDossier(DossierMedical * d);
