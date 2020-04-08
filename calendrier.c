#include "calendrier.h"
/**********************************************************************************************************************/
                                        /*Fonction d'ajout de RDV dans ListRDV*/
/**********************************************************************************************************************/

int AddRendezVous_Calendrier(Calendrier c, RendezVous * rdv){
    if(c == NULL || rdv == NULL){
        printf("Calendrier ou Rdv NULL.\n");
        return 0;
    }

    Date * dateDuRdv = rdv->date;

    /*Dans un premier temps on regarde quelle tete à notre calendrier*/
    //est-ce qu'il est complétement Vide ? Si oui c'est la partie facile : On crée l'année le mosi le jour qui correspondent au rdv et on l'ajoute
    /*if(ListAnnee_isEmpty(c)){
        //
    }
    else if(!ListAnnee_isEmpty(c)){
        for(ListAnnee_setOnFirst(c); !ListAnnee_isOutOfList(c); ListAnnee_setOnNext(c)){
            if(dateDuRdv->annee == ListAnnee_getCurrentAnnee(c)){
                NodeAnnee * AnneeRdv_Calendrier = ListAnnee_getCurrentAnnee(c);
                for(ListMois_setOnFirst(c); !ListMois_isOutOfList(c); ListMois_setOnNext(c)){
                     if(rdv->date->mois == ListMois_getCurrentMois(ListAnnee_getCurrentAnnee(c)){

                     }
                }
            }
        }
    }*/
    //On vérifie que le rdv est valable (Cad si il n'empiete pas sur un autre rdv du meme patient,
    //du meme medecin ou de la meme salle
    /*A faire plus tard, pour l'instant je l'ajoute dans tout les cas*/

    //On regarde si la liste de rdv est vide, si c'est le cas on insere le nouveau noeud en premier

    //On crée un NodeRendezVous
    //Si la liste n'est pas vide on l'insère chronologiquement

    FreeDate(dateDuRdv);
    return 0;
}
/**
 * AddRendezVous_Jour : Ajoute à une liste de rdv classée chronologiquement un rdv
 * @param j : la liste de rdv
 * @param rdv : le rdv à ajouter
 * @return 1 si le rdv a bien été ajouté, 0 si le jour ou le rdv étaient NULL
 */
int AddRendezVous_Jour(Jour j, RendezVous * rdv){
    if(j == NULL || rdv == NULL){
        printf("Jour ou Rdv NULL.\n");
        return 0;
    }
    //on check si le jour est vide de rdv
    if(ListRendezVous_isEmpty(j)) {
        //Il l'est, on ajoute le rdv au début
        NodeRendezVous * newNode = newNodeRendezVous(rdv, &(j->sentinel_begin), &(j->sentinel_end));
        j->sentinel_begin.next = newNode;
        j->sentinel_end.previous = newNode;
        return 1;
    }

    //Si il n'est pas vide on cherche le rdv avant lequel on va l'insérer
    if(ChercherRendezVousSuivant(j,rdv)){
        //On l'insère avant current
        NodeRendezVous * newNode = newNodeRendezVous(rdv, j->current->previous, j->current);
        j->current->previous->next = newNode;
        j->current->previous = newNode;
        return 1;
    }
    //Dans le cas ou ChercherRendezVousSuivant n'a pas return 1 c'est que notre rdv doit etre insérer en fin de
    //listRendezVous puisque ni j ni rdv ne sont nuls (testés plus haut)
    //On l'insère donc à la fin de liste
    ListRendezVous_setOnNext(j);
    NodeRendezVous * newNode = newNodeRendezVous(rdv, j->sentinel_end.previous, &(j->sentinel_end));
    j->sentinel_end.previous->next = newNode;
    j->sentinel_end.previous = newNode;
    return 1;
}

/**
 * ChercherRendezVousPrecedant : Place Current sur le rdv dont l'heure de debut est juste apres l'heure de fin du rdv
 * passé en paramètre
 * @param j : la liste de RendezVous dans laquelle on cherche
 * @param rdv : le rendezVous dont on cherche le suivant
 * @return 1 si Current est bien placé sur le rdv suivant,
 *         0 si current est placé sur sentinel_end et qu'il faut donc ajouter notre rdv à la fin de la ListRendezVous,
 *         -1 si erreur (ne devrait jamais arriver puisque testé avant)
 */
int ChercherRendezVousSuivant(Jour j, RendezVous * rdv){
    if(j == NULL || rdv == NULL){
        printf("Jour ou Rdv NULL.\n");
        return -1;
    }
    //On parcours chronologiquement les rdv du jour
    for(ListRendezVous_setOnFirst(j); !ListRendezVous_isLast(j); ListRendezVous_setOnNext(j)){
        if(ListRendezVous_getCurrent(j)->heure_debut >= rdv->heure_fin){            //On met >= pcq pas de
                                                                                    //pause pour les medecins #corona
            return 1;   //Current est bien placé sur le rdv "suivant" celui passé en paramètre
        }
    }
    //Si on arrive là ça veut dire que notre rdv est le dernier de la journée, en effet dans la boucle for précédente,
    // current est arrivé jusqu'à sentinel_end. On le remet donc dans la liste (au début par exemple)
    // et on return donc 0 pour l'indiquer.
    ListRendezVous_setOnFirst(j);
    return 0;
}
int AddJour_Mois(Mois m, Jour j){
    if(j == NULL || m == NULL){
        printf("Jour ou Rdv NULL.\n");
        return -1;
    }
    int jour = j->date->jour;
    if(ListJour_isEmpty(m)){
        NodeJour * newNode = newNodeJour(j, &(m->sentinel_begin), &(m->sentinel_end));
        m->sentinel_begin.next = newNode;
        m->sentinel_end.previous = newNode;
        return 1;
    }
    for(ListJour_setOnFirst(m); !ListJour_isLast(m); ListJour_setOnNext(m)){
        if(jour > ListJour_getCurrent(m)->date->jour){
            ListJour_setOnNext(m);
            NodeJour * newNode = newNodeJour(j, m->current->previous, m->current);
            m->current->previous->next = newNode;
            m->current->previous = newNode;
            return 1;
        }
    }
    ListJour_setOnNext(m);
    NodeJour * newNode = newNodeJour(j, m->sentinel_end.previous, &(m->sentinel_end));
    m->sentinel_end.previous->next = newNode;
    m->sentinel_end.previous = newNode;
    return 1;
}
int AddMois_Annee(Annee a, Mois m);
int AddAnnee_Calendrier(Calendrier c, Annee a);



/**********************************************************************************************************************/
                                        /*List de RendezVous pour un Jour*/
/**********************************************************************************************************************/

/**
 * newNodeRendezVous : Fonction permettant de créer un nouvel objet NodeRendezVous
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
 * freeNodeRendezVous : Fonction libérant permettant de free un objet NodeRendezVous
 * @param n : le node en question
 */
void freeNodeRendezVous(NodeRendezVous * n){
    //Faut-il free les rdv ici ? Je pense pas mais sinon on le fait pas
    free((void *) n);
}

/**
 * ListRendezVous_init : Initialise correctement une liste de NodeRendezVous en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 * @param date : la date correspond au Mois (la liste de rdv)
 */
void ListRendezVous_init(ListRendezVous * l, Date * date){
    if (l != NULL){
        l->date = date;
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
    if (l!= NULL && !ListRendezVous_isEmpty(l)) {
        for (ListRendezVous_setOnFirst(l); ListRendezVous_isOutOfList(l); ListRendezVous_setOnNext(l)) {
            freeNodeRendezVous(l->current);
        }
        FreeDate(l->date);
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
/**
 * ListRendezVous_getDate : Permet d'accéder à la date de cette liste de rdv (un jour)
 * @param l : la liste
 * @return la date si la liste n'est pas NULL, NULL si la liste est NULL
 */
Date * ListRendezVous_getDate(ListRendezVous * l){
    if(l != NULL){
        return l->date;
    }
    printf("La liste de RendezVous (Donc un Jour) est NULL, on ne peut donc pas accéder à sa date.\n ");
    return NULL;
}

/**********************************************************************************************************************/
                                        /*List de Jour pour un Mois*/
/**********************************************************************************************************************/

/**
 * newNodeJour : Fonction permettant de créer un nouvel objet NodeJour
 * @param jour : le jour (donc une liste de RendezVous) pointé par ce nouveau NodeJour
 * @param previous : le NodeJour précédant le nouveau node
 * @param next : le NodeJour suivant le nouveau node
 * @return un pointeur sur le noeud créé
 */
NodeJour * newNodeJour(Jour jour , NodeJour * previous, NodeJour * next){
    NodeJour * newNode = (NodeJour *) malloc(sizeof(NodeJour));
    newNode->jour = jour;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeJour : Fonction permettant de free un objet NodeJour
 * @param n : le node en question
 */
void freeNodeJour(NodeJour * n){
    ListRendezVous_free(n->jour);   //On free le jour (donc la liste de RDV qui vient elle meme free tout ses nodes) pointé par le Node
    free((void *) n);
}

/**
 * ListJour_init : Initialise correctement une liste de NodeJour en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 * @param mois : le numéro correspondant au mois (la listes de jours)
 */
void ListJour_init(ListJour * l, int mois){
    if (l != NULL){
        l->mois = mois;
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.jour = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.jour = NULL;
    }
}
/**
 * ListJour_free : Libère la mémoire occupée par l'objet ListJour passée en paramètre
 * @param l : la liste de Jour à free
 */
void ListJour_free(ListJour * l){
    if (l!= NULL && !ListJour_isEmpty(l)){
        for(ListJour_setOnFirst(l); ListJour_isOutOfList(l); ListJour_setOnNext(l)) {
            freeNodeJour(l->current);
        }
    }
    free((void *) l);
}

/**
 * ListJour_isEmpty : Vérifie si la liste de Jour est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListJour_isEmpty(ListJour * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListJour_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListJour_isFirst(ListJour * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListJour_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListJour_isLast(ListJour * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListJour_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
 */
int ListJour_isOutOfList(ListJour * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListJour_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListJour_setOnFirst(ListJour * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListJour_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListJour_setOnLast(ListJour * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListJour_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListJour_setOnNext(ListJour * l){
    if(l != NULL && !ListJour_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListJour_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListJour_setOnPrevious(ListJour * l){
    if(l != NULL && !ListJour_isOutOfList(l)){
        l->current = l->current->previous;
    }
}
/**
 * ListJour_getCurrent : Permet d'acceder au Jour pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Jour de l'élément courant de la liste
 */
Jour ListJour_getCurrent(ListJour * l){
    if(l != NULL && l->current != NULL){
        return l->current->jour;
    }
    return NULL;
}
/**
 * ListJour_getMois : Permet d'accéder au numéro correspondant au mois de la liste de Jour (donc au mois)
 * @param l : la liste de jour
 * @return le numéro du mois si la liste n'est pas vide 0 sinon
 */
int ListJour_getMois(ListJour * l){
    if(l != NULL){
        return l->mois;
    }
    printf("La liste de Jours (Donc un Mois) est NULL, on ne peut donc pas accéder au numéro de son mois.\n ");
    return 0;
}
/**********************************************************************************************************************/
                                    /*List de Mois pour une Annee*/
/**********************************************************************************************************************/

/**
 * newNodeMois : Fonction permettant de créer un nouvel objet NodeMois
 * @param mois : le mois (donc une liste de jour ou une liste de liste de rdv) pointé par ce nouveau NodeMois
 * @param previous : le NodeMois précédant le nouveau node
 * @param next : le NodeMois suivant le nouveau node
 * @return un pointeur sur le noeud créé
 */
NodeMois * newNodeMois(Mois mois , NodeMois * previous, NodeMois * next){
    NodeMois * newNode = (NodeMois *) malloc(sizeof(NodeMois));
    newNode->mois = mois;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeMois : Fonction permettant de free un objet NodeMois
 * @param n : le node en question
 */
void freeNodeMois(NodeMois * n){
    ListJour_free(n->mois);   //On free le mois (donc la liste de listes de RDV qui vient elle meme free tout ses nodes) pointé par le Node
    free((void *) n);
}

/**
 * ListMois_init : Initialise correctement une liste de NodeMois en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 * @param annee : le numéro correspondant au mois (la listes de Moiss)
 */
void ListMois_init(ListMois * l, int annee){
    if (l != NULL){
        l->annee = annee;
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.mois = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.mois = NULL;
    }
}
/**
 * ListMois_free : Libère la mémoire occupée par l'objet ListMois passée en paramètre
 * @param l : la liste de Mois à free
 */
void ListMois_free(ListMois * l){
    if (l!= NULL && !ListMois_isEmpty(l)){
        for(ListMois_setOnFirst(l); ListMois_isOutOfList(l); ListMois_setOnNext(l)) {
            freeNodeMois(l->current);
        }
    }
    free((void *) l);
}

/**
 * ListMois_isEmpty : Vérifie si la liste de Mois est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListMois_isEmpty(ListMois * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListMois_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListMois_isFirst(ListMois * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListMois_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListMois_isLast(ListMois * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListMois_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
 */
int ListMois_isOutOfList(ListMois * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListMois_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListMois_setOnFirst(ListMois * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListMois_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListMois_setOnLast(ListMois * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListMois_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListMois_setOnNext(ListMois * l){
    if(l != NULL && !ListMois_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListMois_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListMois_setOnPrevious(ListMois * l){
    if(l != NULL && !ListMois_isOutOfList(l)){
        l->current = l->current->previous;
    }
}
/**
 * ListMois_getCurrent : Permet d'acceder au Mois pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Mois de l'élément courant de la liste
 */
Mois ListMois_getCurrent(ListMois * l){
    if(l != NULL && l->current != NULL){
        return l->current->mois;
    }
    return NULL;
}
/**
 * ListMois_getMois : Permet d'accéder au numéro correspondant au mois de la liste de Mois (donc au mois)
 * @param l : la liste de Mois
 * @return le numéro de l'annéée si la liste n'est pas vide 0 sinon
 */
int ListMois_getAnnee(ListMois * l){
    if(l != NULL){
        return l->annee;
    }
    printf("La liste de Mois (Donc une année) est NULL, on ne peut donc pas accéder au numéro de son année.\n ");
    return 0;
}

/**********************************************************************************************************************/
                                    /*List d'Année pour un Calendrier*/
/**********************************************************************************************************************/

/**
 * newNodeAnnee : Fonction permettant de créer un nouvel objet NodeAnnee
 * @param annee : l'annee' (donc une liste de mois ou une liste de listes de listes de rdv) pointé par ce nouveau NodeAnnee
 * @param previous : le NodeAnnee précédant le nouveau node
 * @param next : le NodeAnnee suivant le nouveau node
 * @return un pointeur sur le noeud créé
 */
NodeAnnee * newNodeAnnee(Annee annee , NodeAnnee * previous, NodeAnnee * next){
    NodeAnnee * newNode = (NodeAnnee *) malloc(sizeof(NodeAnnee));
    newNode->annee = annee;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeAnnee : Fonction permettant de free un objet NodeAnnee
 * @param n : le node en question
 */
void freeNodeAnnee(NodeAnnee * n){
    ListMois_free(n->annee);   //On free l'annee (donc la liste de listes de listes de RDV qui vient elle meme free tout ses nodes) pointé par le Node
    free((void *) n);
}

/**
 * ListAnnee_init : Initialise correctement une liste de NodeAnnee en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 */
void ListAnnee_init(ListAnnee * l){
    if (l != NULL){
        l->current = NULL;
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_begin.annee = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->sentinel_end.annee = NULL;
    }
}
/**
 * ListAnnee_free : Libère la mémoire occupée par l'objet ListAnnee passée en paramètre
 * @param l : la liste de Annee à free
 */
void ListAnnee_free(ListAnnee * l){
    if (l!= NULL && !ListAnnee_isEmpty(l)){
        for(ListAnnee_setOnFirst(l); ListAnnee_isOutOfList(l); ListAnnee_setOnNext(l)) {
            freeNodeAnnee(l->current);
        }
    }
    free((void *) l);
}

/**
 * ListAnnee_isEmpty : Vérifie si la liste de Annee est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide 0 si elle ne l'est pas et -1 si la liste est NULL
 */
int ListAnnee_isEmpty(ListAnnee * l){
    if (l != NULL){
        return  (l->sentinel_begin.next == &(l->sentinel_end)) && (l->sentinel_end.previous == &(l->sentinel_begin));
    }
    return -1; //La liste est NULL
}
/**
 * ListAnnee_isFirst : Vérifie si current est positionné sur le premier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le premier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListAnnee_isFirst(ListAnnee * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListAnnee_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément 0 si il ne l'est pas et -1 si la liste est NULL
 */
int ListAnnee_isLast(ListAnnee * l){
    if (l != NULL){
        return  l->current == l->sentinel_end.previous;
    }
    return -1; //La liste est NULL
}
/**
 * ListAnnee_isOutOfList : Vérifie si current est bien placé sur un élément de la liste
 * (les sentinels ne sont pas considérées comme dans la liste)
 * @param l : la liste
 * @return 1 si current vaut NULL 0 sinon et -1 si la liste est NULL
 */
int ListAnnee_isOutOfList(ListAnnee * l){
    if (l != NULL){
        return  (l->current == NULL) || (l->current == &(l->sentinel_begin)) || (l->current == &(l->sentinel_end));
    }
    return -1; //La liste est NULL
}

/**
 * ListAnnee_setOnFirst : Positionne le pointeur courant sur le premier élément de la liste
 * @param l : la liste
 */
void ListAnnee_setOnFirst(ListAnnee * l){
    if(l != NULL){
        l->current = l->sentinel_begin.next;
    }
}
/**
 * ListAnnee_setOnLast : Positionne le pointeur courant sur le dernier élément de la liste
 * @param l : la liste
 */
void ListAnnee_setOnLast(ListAnnee * l){
    if(l != NULL){
        l->current = l->sentinel_end.previous;
    }
}
/**
 * ListAnnee_setOnNext : Positionne le pointeur courant sur le prochain élément de la liste
 * @param l : la liste
 */
void ListAnnee_setOnNext(ListAnnee * l){
    if(l != NULL && !ListAnnee_isOutOfList(l)){
        l->current = l->current->next;
    }
}
/**
 * ListAnnee_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListAnnee_setOnPrevious(ListAnnee * l){
    if(l != NULL && !ListAnnee_isOutOfList(l)){
        l->current = l->current->previous;
    }
}
/**
 * ListAnnee_getCurrent : Permet d'acceder au Annee pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur le Annee de l'élément courant de la liste
 */
Annee ListAnnee_getCurrent(ListAnnee * l){
    if(l != NULL && l->current != NULL){
        return l->current->annee;
    }
    return NULL;
}