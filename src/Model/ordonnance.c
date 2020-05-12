#include "GPCalendar/Model/ordonnance.h"

/**
 * CreerOrdonnance : Creer dynamiquement un objet Ordonnance
 * @param patient : le patient concern� par l'ordonnance
 * @param medecin : le medecin qui prescrit l'ordonnance
 * @param description : description de la prescription
 * @return l'ordonnance cr��e
 */
Ordonnance* CreerOrdonnance(Medecin* m, char* description){
    Ordonnance* o = (Ordonnance*) malloc(sizeof(Ordonnance));
    Date* d = CreerDateCourante();
    Date* expi = AjoutMoisDate(d, 3);

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
int modifierOrdonnance(Ordonnance * ordo, Medecin * m, char * description){
    ordo->medecin = m;
    ordo->description = description;

    FreeDate(ordo->date_edition);
    FreeDate(ordo->date_expiration);

    ordo->date_edition = CreerDateCourante();
    ordo->date_expiration = AjoutMoisDate(ordo->date_edition, 3);
    if( (ordo->medecin == m) && (strcmp(ordo->description, description) == 0)){
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
    printf("suivi par le m�decin : %s %s \n", ordo->medecin->nom, ordo->medecin->prenom);
    printf("Prescription : \n %s \n", ordo->description);
    printf("A r�cup�rer avant le %d/%d/%d", ordo->date_expiration->jour, ordo->date_expiration->mois, ordo->date_expiration->annee);
}

/**********************************************************************************************************************/
                                                /*ListOrdonnance*/
/**********************************************************************************************************************/

/**
 * newNodeOrdonnance : Permet de créer dynamiquement un nouveau node de Ordonnance pour la liste
 * @param Ordonnance : l'Ordonnance pointée par ce nouveau noeud
 * @param previous : le noeud précédant le nouveau noeud dans la liste
 * @param next : le prochain noeud de la liste
 * @return un pointeur sur le nouveau noeud créé
 */
NodeOrdonnance * newNodeOrdonnance(Ordonnance * ordo, NodeOrdonnance * previous, NodeOrdonnance * next){
    NodeOrdonnance * newNode = (NodeOrdonnance *) malloc(sizeof(NodeOrdonnance));
    newNode->ordo = ordo;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeOrdonnance : Permet de delete proprement (avec un free) un NodeOrdonnance
 * @param n : le node à delete
 */
void freeNodeOrdonnance(ListOrdonnance *l, NodeOrdonnance * n){
    //On place current sur l'objet avant le noeud qu'on veut supprimer
    ListOrdonnance_setOnPrevious(l);
    //On set les pointeurs des objets précédants et suivants le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    //et enfin on supprime le noeud
    DeleteOrdonnance(n->ordo);
    free((void*) n);
}


/**
 * ListOrdonnance_init : Initialise correctement une liste de NodeOrdonnance en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 */
void ListOrdonnance_init(ListOrdonnance * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.ordo = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.ordo = NULL;
    }
}
/**
 * ListOrdonnance_free : Libère la mémoire occupée par l'objet ListOrdonnance passée en paramètre
 * @param l : la liste de ordonnances à free
 */
void ListOrdonnance_free(ListOrdonnance * l){
    if (l!= NULL && !ListOrdonnance_isEmpty(l)){
        for(ListOrdonnance_setOnFirst(l); !ListOrdonnance_isOutOfList(l); ListOrdonnance_setOnNext(l)) {
            freeNodeOrdonnance(l, l->current);
        }
    }
    free((void *) l);
}

/**
 * ListOrdonnance_isEmpty : Vérifie si la liste de Ordonnance est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListOrdonnance_isEmpty(ListOrdonnance * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListOrdonnance_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListOrdonnance_isFirst(ListOrdonnance * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListOrdonnance_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListOrdonnance_isLast(ListOrdonnance * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListOrdonnance_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
 */
int ListOrdonnance_isOutOfList(ListOrdonnance * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListOrdonnance_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListOrdonnance_setOnFirst(ListOrdonnance * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListOrdonnance_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListOrdonnance_setOnLast(ListOrdonnance * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListOrdonnance_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListOrdonnance_setOnNext(ListOrdonnance * l){
    if(l != NULL && !ListOrdonnance_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListOrdonnance_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListOrdonnance_setOnPrevious(ListOrdonnance * l){
    if(l != NULL && !ListOrdonnance_isOutOfList(l)){
        l->current = l->current->previous;
    }
}
/**
 * ListOrdonnance_getCurrent : Permet d'acceder à l'Ordonnance pointée par current
 * @param l : la liste
 * @return Retourne un pointeur sur l'Ordonnance de l'élément courant de la liste
 */
Ordonnance * ListOrdonnance_getCurrent(ListOrdonnance * l){
    if(l != NULL && l->current != NULL){
        return l->current->ordo;
    }
    return NULL;
}
