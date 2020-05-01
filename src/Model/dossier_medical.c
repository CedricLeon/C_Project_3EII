#include "GPCalendar/Model/dossier_medical.h"

/**
 * CreerDossier : Creer dynamiquement un objet DossierMedical
 * @param patient : le patient concerne par le dossier=
 * @return le dossier cr��
 */
DossierMedical * CreerDossierMedical(Patient * patient){
    DossierMedical * dm = (DossierMedical*)malloc(sizeof(DossierMedical));

    dm->medecins_consultes = (ListMedecin*) malloc(sizeof(ListMedecin));
    ListMedecin_init(dm->medecins_consultes);

    dm->ordonnances = (ListOrdonnance*) malloc(sizeof(ListOrdonnance));
    ListOrdonnance_init(dm->ordonnances);

    //On initialise pas les antécédents

    return dm;
}

/**
 * FreeDossier : Free un objet DossierMedical
 * @param dm : le dossier � supprimer
 */
void FreeDossierMedical(DossierMedical * dm){
    ListMedecin_free_withoutDeletingMedecin(dm->medecins_consultes);    //Il ne faut pas delete les mèdecins référencés
                                                                        // par cette liste puisqu'on les delete dèjà
                                                                        // depuis la liste workingMedecins
    ListOrdonnance_free(dm->ordonnances); //pareil
    free((void *) dm);
}

int AddOrdonnanceDossierMedical(DossierMedical * dm, Ordonnance * ordonnance){
    if(dm == NULL || ordonnance == NULL){
        printf("DossierMedical ou Ordonnance NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListOrdonnance_isEmpty(dm->ordonnances)){
        NodeOrdonnance * newNode = newNodeOrdonnance(ordonnance, &(dm->ordonnances->sentinel_begin), &(dm->ordonnances->sentinel_end));
        dm->ordonnances->sentinel_begin.next = newNode;
        dm->ordonnances->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on insère l'ordonnance à la fin
    NodeOrdonnance * newNode = newNodeOrdonnance(ordonnance, dm->ordonnances->sentinel_end.previous, &(dm->ordonnances->sentinel_end));
    dm->ordonnances->sentinel_end.previous->next = newNode;
    dm->ordonnances->sentinel_end.previous = newNode;
    return 1;
}


