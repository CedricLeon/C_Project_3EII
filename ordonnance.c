#include "ordonnance.h"
#include <time.h>

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

int ModifierOrdonnance(Ordonnance * ordo, Patient * p, Medecin * m, char * description){
    ordo->patient=p;
    ordo->medecin=m;
    strcpy(ordo->description, description);
    ordo->date_edition=DateCourante();
    ordo->date_expiration=AjoutMoisDateCourante(3);

    return 1;
}

void AfficherOrdonnance(Ordonnance * ordo){
    printf("Ordonnance faite le %d/%d/%d \n\n", ordo->date_edition->jour, ordo->date_edition->mois, ordo->date_edition->annee);
    printf("Patient : %s %s ", ordo->patient->nom, ordo->patient->prenom);
    printf("suivi par le médecin : %s %s \n", ordo->medecin->nom, ordo->medecin->prenom);
    printf("Prescription : \n %s \n", ordo->description);
    printf("A récupérer avant le %d/%d/%d", ordo->date_expiration->jour, ordo->date_expiration->mois, ordo->date_expiration->annee);
}
