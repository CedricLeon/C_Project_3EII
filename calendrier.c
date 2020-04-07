#include "calendrier.h"

/**********************************************************************************************************************/
                                        /*List de RendezVous pour un Jour*/
/**********************************************************************************************************************/

/**
 * newNodeRendezVous : Fonction static permettant de créer un nouvel objet NodeRendezVous
 * @param rdv : le rendezvous pointé par ce nouveau Node
 * @param previous : le NodeRendezVous précédant le nouveau node
 * @param next : le NodeRendezVous suivant le nouveau node
 * @return un pointeur sur le noeud créé
 */
NodeRendezVous * newNodeRendezVous(RendezVous * rdv , NodeRendezVous * previous, NodeRendezVous * next){
    NodeRendezVous * newNode = (NodeRendezVous *) malloc(sizeof(NodeRendezVous));
    newNode->rdv = rdv;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeRendezVous : Fonction static libérant permettant de free un objet NodeRendezVous
 * @param n : le node en question
 */
void freeNodeRendezVous(NodeRendezVous * n){
    free((void *) n);
}

/**
 * ListRendezVous_init : Initialise correctement une liste de NodeRendezVous en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 */
void ListRendezVous_init(ListRendezVous * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.rdv = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.rdv = NULL;
    }
}
/**
 * ListRendezVous_free : Libère la mémoire occupée par l'objet ListRendezVous passée en paramètre
 * @param l : la liste de rendezVous à free
 */
void ListRendezVous_free(ListRendezVous * l){
    if (l!= NULL && !ListRendezVous_isEmpty(l)){
        for(ListRendezVous_setOnFirst(l); ListRendezVous_isOutOfList(l); ListRendezVous_setOnNext(l)) {
            freeNodeRendezVous(l->current);
        }
    }
    free((void *) l);
}

/**
 * ListRendezVous_isEmpty : Vérifie si la liste de RendezVous est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListRendezVous_isEmpty(ListRendezVous * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListRendezVous_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListRendezVous_isFirst(ListRendezVous * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListRendezVous_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListRendezVous_isLast(ListRendezVous * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListRendezVous_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
 */
int ListRendezVous_isOutOfList(ListRendezVous * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListRendezVous_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListRendezVous_setOnFirst(ListRendezVous * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListRendezVous_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListRendezVous_setOnLast(ListRendezVous * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListRendezVous_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListRendezVous_setOnNext(ListRendezVous * l){
    if(l != NULL && !ListRendezVous_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListRendezVous_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListRendezVous_setOnPrevious(ListRendezVous * l){
    if(l != NULL && !ListRendezVous_isOutOfList(l)){
        l->current = l->current->previous;
    }
}
/**
 * ListRendezVous_getCurrent : Permet d'acceder au RendezVous pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le RendezVous de l'élément courant de la liste
 */
RendezVous * ListRendezVous_getCurrent(ListRendezVous * l){
    if(l != NULL && l->current != NULL){
        return l->current->rdv;
    }
    return NULL;
}


