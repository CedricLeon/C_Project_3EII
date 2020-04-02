#include "ordonnance.h"

/**
 * CreerOrdonnance : Creer dynamiquement un objet Ordonnance
 * @param patient : le patient concern� par l'ordonnance
 * @param medecin : le medecin qui prescrit l'ordonnance
 * @param description : description de la prescription
 * @return l'ordonnance cr��e
 */
Ordonnance * CreerOrdonnance(Patient * p, Medecin * m, char * description){
    Ordonnance * o = (Ordonnance *)malloc(sizeof(Ordonnance));
    Date * d = DateCourante();
    Date * expi = AjoutMoisDateCourante(3);

    o->patient=p;
    o->medecin=m;
    strcpy(o->description, description);
    o->date_edition=d;
    o->date_expiration=expi;

    return o;
}
/**
 * DeleteOrdonnance : Free un objet ordonnance
 * @param o : l'ordonnance à supprimer
 */
void DeleteOrdonnance(Ordonnance * o){
    free((void *) o->date_edition);
    free((void *) o->date_expiration);
    free((void *) o);
}

/**
 * ModifierOrdonnance : Modifier un objet Ordonnance
 * @param ordo : l'ordonnance qui n�cessite d'�tre modifi�e
 * @param p : le patient concern� par l'ordonnance
 * @param m : le medecin qui prescrit l'ordonnance
 * @param description : nouvelle description de la prescription
 * @return l'ordonnance cr��e
 */
int ModifierOrdonnance(Ordonnance * ordo, Patient * p, Medecin * m, char * description){
    ordo->patient=p;
    ordo->medecin=m;
    strcpy(ordo->description, description);
    ordo->date_edition=DateCourante();
    ordo->date_expiration=AjoutMoisDateCourante(3);

    return 1;
}

/**
 * AfficherOrdonnance : Afficher un objet Ordonnance
 * @param ordo : l'ordonnance que l'on veut afficher
 */
void AfficherOrdonnance(Ordonnance * ordo){
    printf("Ordonnance faite le %d/%d/%d \n\n", ordo->date_edition->jour, ordo->date_edition->mois, ordo->date_edition->annee);
    printf("Patient : %s %s ", ordo->patient->nom, ordo->patient->prenom);
    printf("suivi par le m�decin : %s %s \n", ordo->medecin->nom, ordo->medecin->prenom);
    printf("Prescription : \n %s \n", ordo->description);
    printf("A r�cup�rer avant le %d/%d/%d", ordo->date_expiration->jour, ordo->date_expiration->mois, ordo->date_expiration->annee);
}
