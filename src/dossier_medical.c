#include "dossier_medical.h"

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
    ListMedecin_free(dm->medecins_consultes);
    ListOrdonnance_free(dm->ordonnances); //pareil
    //Pour les antécédents voir comment on les gères (Cf si malloc)
    free((void *) dm);
}

/**
* AccesDossier : Accede au dossier du patient et l'affiche
* @param p : le patient dont on veut acceder au dossier
*/
void AccesDossier(Patient * p){
    char * nom;
    DossierMedical * d = p->dossierMedical;
    printf("Medecins consultés : ");
    for(ListMedecin_setOnFirst(d->medecins_consultes); !ListMedecin_isOutOfList(d->medecins_consultes); ListMedecin_setOnNext(d->medecins_consultes)) {
        getNomMedecin(nom, ListMedecin_getCurrent(d->medecins_consultes));
        printf("%s ; ", nom);
    }
    printf("\n\n Ordonnances : ");
    for(ListOrdonnance_setOnFirst(d->ordonnances); !ListOrdonnance_isOutOfList(d->ordonnances); ListOrdonnance_setOnNext(d->ordonnances)) {
        printOrdonnance(ListOrdonnance_getCurrent(d->ordonnances));
        printf("\n\n");
    }
}
