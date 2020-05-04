#include "GPCalendar/Model/dossier_medical.h"

/**
 * CreerDossier : Creer dynamiquement un objet DossierMedical
 * @param patient : le patient concerné par le dossier
 * @return le dossier crée
 */
DossierMedical * CreerDossierMedical(){
    DossierMedical* dm = (DossierMedical*) malloc(sizeof(DossierMedical));

    dm->medecins_consultes = (ListMedecin*) malloc(sizeof(ListMedecin));
    ListMedecin_init(dm->medecins_consultes);

    dm->ordonnances = (ListOrdonnance*) malloc(sizeof(ListOrdonnance));
    ListOrdonnance_init(dm->ordonnances);

    dm->antecedents = (ListAntecedent*) malloc(sizeof(ListAntecedent));
    ListAntecedent_init(dm->antecedents);

    return dm;
}

/**
 * FreeDossier : Free un objet DossierMedical
 * @param dm : le dossier à supprimer
 */
void FreeDossierMedical(DossierMedical * dm){
    printf("FreeDossierMedical() : \n");
    ListOrdonnance_free(dm->ordonnances);     // Il faut delete les ordonnances
    ListMedecin_free_withoutDeletingMedecin(dm->medecins_consultes);    // Il ne faut pas delete les mèdecins référencés
                                                                        // par cette liste puisqu'on les delete dèjà
    ListAntecedent_free(dm->antecedents);                                                                   // depuis la liste workingMedecins

    free((void *) dm);
}

/**
 * AddOrdonnanceDossierMedical : Ajoute une ordonnance dans le dossier medical
 * @param dm : le dossier dans lequel on veut ajouter
 * @param ordonnance : l'ordonnance à ajouter
 */

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

/**
 * AddAntecedentDossierMedical : Ajoute un antecedent dans le dossier medical
 * @param dm : le dossier dans lequel on veut ajouter
 * @param antecedent : l'antecedent à ajouter
 */

int AddAntecedentDossierMedical(DossierMedical * dm, char * ant){
     if(dm == NULL){
        printf("DossierMedical NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListAntecedent_isEmpty(dm->antecedents)){
        printf("\nCompte-rendu du rdv : \n");
        scanf("%[^\n]",ant);
        NodeAntecedent * newNode = newNodeAntecedent(ant, &(dm->antecedents->sentinel_begin), &(dm->antecedents->sentinel_end));
        dm->antecedents->sentinel_begin.next = newNode;
        dm->antecedents->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on insère l'antecedent à la fin
    printf("\nCompte-rendu du rdv : \n");
    scanf("%[^\n]",ant);
    NodeAntecedent * newNode = newNodeAntecedent(ant, dm->antecedents->sentinel_end.previous, &(dm->antecedents->sentinel_end));
    dm->antecedents->sentinel_end.previous->next = newNode;
    dm->antecedents->sentinel_end.previous = newNode;
    return 1;
}

/**
 * printAntecedent : Affiche un antecedent dans le dossier medical
 * @param ante : l'antecedent à afficher
 */

void printAntecedent(char * ante){
    printf("%s", ante);
}


/**********************************************************************************************************************/
                                                /*ListAntecedent*/
/**********************************************************************************************************************/

/**
 * newNodeAntecedent : Permet de créer dynamiquement un nouveau node de Antecedent pour la liste
 * @param ante : l'antecedent pointé par ce nouveau noeud
 * @param previous : le noeud précédant le nouveau noeud dans la liste
 * @param next : le prochain noeud de la liste
 * @return un pointeur sur le nouveau noeud créé
 */
NodeAntecedent * newNodeAntecedent(char * ante, NodeAntecedent * previous, NodeAntecedent * next){
    NodeAntecedent * newNode = (NodeAntecedent *) malloc(sizeof(NodeAntecedent));
    newNode->ante = ante;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeAntecedent : Permet de delete proprement (avec un free) un NodeAntecedent
 * @param n : le node à delete
 */
void freeNodeAntecedent(ListAntecedent *l, NodeAntecedent * n){
    n->previous->next = n->next;
    n->next->previous = n->previous;
    free((void *) n);
    ListAntecedent_setOnFirst(l);
    ListAntecedent_setOnPrevious(l);
}


/**
 * ListAntecedent_init : Initialise correctement une liste de NodeAntecedent en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 */
void ListAntecedent_init(ListAntecedent * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.ante = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.ante = NULL;
    }
}
/**
 * ListAntecedent_free : Libère la mémoire occupée par l'objet ListAntecedent passé en paramètre
 * @param l : la liste de antecedents à free
 */
void ListAntecedent_free(ListAntecedent * l){
    if (l == NULL){
        printf("ListAntecedent_free : la liste d'antecedents est NULL !!!\n");
    }else if (ListAntecedent_isEmpty(l)){
        printf("ListAntecedent_free : la liste est vide, on free donc uniquement la liste\n");
        free((void *) l);
    }else{
        for(ListAntecedent_setOnFirst(l); !ListAntecedent_isOutOfList(l); ListAntecedent_setOnNext(l)) {
            printf("ListAntecedent_free : Appel de freeNodeAntecedent() pour l'antecedent courant \n");
            freeNodeAntecedent(l, l->current);
        }
        free((void *) l);
    }
}


/**
 * ListAntecedent_isEmpty : Vérifie si la liste de Antecedent est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
 */
int ListAntecedent_isEmpty(ListAntecedent * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListAntecedent_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
 */
int ListAntecedent_isFirst(ListAntecedent * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListAntecedent_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
 */
int ListAntecedent_isLast(ListAntecedent * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListAntecedent_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL
 *         0 sinon
 *         -1 si la liste est NULL
 */
int ListAntecedent_isOutOfList(ListAntecedent * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListAntecedent_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListAntecedent_setOnFirst(ListAntecedent * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListAntecedent_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListAntecedent_setOnLast(ListAntecedent * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListAntecedent_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListAntecedent_setOnNext(ListAntecedent * l){
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListAntecedent_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListAntecedent_setOnPrevious(ListAntecedent * l){
    if(l != NULL && l->current->previous != NULL){
        l->current = l->current->previous;
    }
}
/**
 * ListAntecedent_getCurrent : Permet d'acceder à l'Ordonnance pointée par current
 * @param l : la liste
 * @return Retourne un pointeur sur l'Ordonnance de l'élément courant de la liste
 */
char * ListAntecedent_getCurrent(ListAntecedent * l){
    if(l != NULL && l->current != NULL){
        return l->current->ante;
    }
    return NULL;
}

