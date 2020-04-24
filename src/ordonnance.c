#include "ordonnance.h"

/**
 * CreerOrdonnance : Creer dynamiquement un objet Ordonnance
 * @param patient : le patient concern� par l'ordonnance
 * @param medecin : le medecin qui prescrit l'ordonnance
 * @param description : description de la prescription
 * @return l'ordonnance cr��e
 */
Ordonnance* CreerOrdonnance(Patient* p, Medecin* m, char* description){
    Ordonnance* o = (Ordonnance*) malloc(sizeof(Ordonnance));
    Date* d = CreerDateCourante();
    Date* expi = AjoutMoisDate(d, 3);

    o->patient = p;
    o->medecin = m;
    o->description = description;
    o->date_edition = d;
    o->date_expiration = expi;

    return o;
}
/**
 * DeleteOrdonnance : Free un objet ordonnance
 * @param o : l'ordonnance à supprimer
 */
void DeleteOrdonnance(Ordonnance * o){
    //Il ne faut pas free le patient et le medecin !
    FreeDate(o->date_edition);
    FreeDate(o->date_expiration);
    free((void *) o);
}

/**
 * ModifierOrdonnance : Modifier un objet Ordonnance
 * @param ordo : l'ordonnance qui n�cessite d'�tre modifi�e
 * @param p : le patient concern� par l'ordonnance
 * @param m : le medecin qui prescrit l'ordonnance
 * @param description : nouvelle description de la prescription
 * @return 1 si l'ordonnance a été modifiée
           0 sinon
 */
int modifierOrdonnance(Ordonnance * ordo, Patient * p, Medecin * m, char * description){
    ordo->patient = p;
    ordo->medecin = m;
    ordo->description = description;

    FreeDate(ordo->date_edition);
    FreeDate(ordo->date_expiration);

    ordo->date_edition = CreerDateCourante();
    ordo->date_expiration = AjoutMoisDate(ordo->date_edition, 3);
    if( (ordo->patient == p) && (ordo->medecin == m) && (strcmp(ordo->description, description) == 0)){
        return 1;
    }else{
        return 0;
    }
}

/**
 * AfficherOrdonnance : Afficher un objet Ordonnance
 * @param ordo : l'ordonnance que l'on veut afficher
 */
void printOrdonnance(Ordonnance * ordo){
    printf("Ordonnance faite le %d/%d/%d \n\n", ordo->date_edition->jour, ordo->date_edition->mois, ordo->date_edition->annee);
    printf("Patient : %s %s ", ordo->patient->nom, ordo->patient->prenom);
    printf("suivi par le m�decin : %s %s \n", ordo->medecin->nom, ordo->medecin->prenom);
    printf("Prescription : \n %s \n", ordo->description);
    printf("A r�cup�rer avant le %d/%d/%d", ordo->date_expiration->jour, ordo->date_expiration->mois, ordo->date_expiration->annee);
}