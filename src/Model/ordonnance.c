#include "GPCalendar/Model/ordonnance.h"

/**
 * CreerOrdonnance : Creer dynamiquement un objet Ordonnance
 * @param patient : le patient concerné par l'ordonnance
 * @param medecin : le medecin qui prescrit l'ordonnance
 * @param description : description de la prescription
 * @return l'ordonnance créée
 */
Ordonnance* CreerOrdonnance(Medecin* m, char* description){
    Ordonnance* o = (Ordonnance*) malloc(sizeof(Ordonnance));
    Date* d = CreerDateCourante();
    Date* expi = AjoutMoisDate(d, 3);

    o->medecin = m;
    //o->numRPSMedecin = NULL;
    o->description = description;
    o->date_edition = d;
    o->date_expiration = expi;

    return o;
}

/**
 * LoadOrdonnance : Fonction utilisée lors du load d'un projet JSON, initialise une ordonnance avec son pointeur sur le mèdecin à NULL
 *                  mais avec numRPSMedecin avec le num RPS du mèdecin, il faudra donc aller chercher le mèdecin correspondant plus tard
 *                  et avec les bonnes dates (pas la courante et celle 3 mois plus tard) : l'ordonnance ne date pas forcément du jour présent,
 *                  elle peut être plus vieille
 * @param rpsMedecin : le num RPS du mèdecin ayant fait l'ordonnance
 *
 * @param date_edi_jour   |
 * @param date_edi_mois   | ---> La date d'édition de l'ordonnance
 * @param date_edi_annee  |
 *
 * @param date_expi_jour  |
 * @param date_expi_mois  | ---> La date d'espiration de l'ordonnance
 * @param date_expi_annee |
 * @param description :   la description de l'ordonnance
 * @return l'ordonnance initialisée
 */
Ordonnance* LoadOrdonnance(Medecin* medecin, int date_edi_jour, int date_edi_mois, int date_edi_annee, int date_expi_jour, int date_expi_mois, int date_expi_annee, char* description){
    Ordonnance* o = (Ordonnance*) malloc(sizeof(Ordonnance));
    Date* date_edition = CreerDate(date_edi_jour, date_edi_mois, date_edi_annee);
    Date* date_expiration = CreerDate(date_expi_jour, date_expi_mois, date_expi_annee);

    o->medecin = medecin;
    o->description = description;
    o->date_edition = date_edition;
    o->date_expiration = date_expiration;

    return o;
}
/**
 * DeleteOrdonnance : Free un objet ordonnance
 * @param o : l'ordonnance à supprimer
 */
void DeleteOrdonnance(Ordonnance * o){
    //Il ne faut pas free le medecin !
    FreeDate(o->date_edition);
    FreeDate(o->date_expiration);
    free((void *) o);
}

/**
 * ModifierOrdonnance : Modifier un objet Ordonnance
 * @param ordo : l'ordonnance qui necessite d'être modifi�e
 * @param p : le patient concerné par l'ordonnance
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
void printOrdonnance(char* infos, Ordonnance * ordo){
    strcat(infos, "date_edition : ");

    char* tmp = (char*) malloc(strlen(ordo->description)+10);
    getInfosDate(tmp, ordo->date_edition);
    strcat(infos, tmp);
    strcat(infos, "\n\t\tdate_expiration : ");
    getInfosDate(tmp, ordo->date_expiration);
    strcat(infos, tmp);
    strcat(infos, "\n\t\tMedecin : \"");
    getNomMedecin(tmp, ordo->medecin);
    strcat(infos, tmp);
    free((void*) tmp);

    strcat(infos, "\"\n\t\tPrescription : ");
    strcat(infos, ordo->description);
    strcat(infos, "\n");

    /*printf("Ordonnance faite le %d/%d/%d par le médecin \"%s %s\"\n", ordo->date_edition->jour, ordo->date_edition->mois, ordo->date_edition->annee, ordo->medecin->nom, ordo->medecin->prenom);
    printf("\t\t\tPrescription :  %s \n", ordo->description);
    printf("\t\t\tA recuperer avant le %d/%d/%d\n", ordo->date_expiration->jour, ordo->date_expiration->mois, ordo->date_expiration->annee);*/
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
    printf("freeNodeOrdonnance()\n");
    n->previous->next = n->next;
    n->next->previous = n->previous;
    DeleteOrdonnance(n->ordo);
    free((void *) n);
    ListOrdonnance_setOnFirst(l);
    ListOrdonnance_setOnPrevious(l);
}
/**
 * freeNodeOrdonnance_withoutDeletingOrdonnance : Permet de delete un nodeOrdonnance mais sans delete l'ordonnance liée au node
 * @param n : le node à delete
 */
void freeNodeOrdonnance_withoutDeletingOrdonnance(ListOrdonnance *l, NodeOrdonnance * n){
    n->previous->next = n->next;
    n->next->previous = n->previous;
    free((void *) n);
    ListOrdonnance_setOnFirst(l);
    ListOrdonnance_setOnPrevious(l);
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
 * ListOrdonnance_free : Libère la mémoire occupée par l'objet ListOrdonnance passé en paramètre
 * @param l : la liste de ordonnances à free
 */
void ListOrdonnance_free(ListOrdonnance * l){
    if (l == NULL){
        printf("ListOrdonnance_free : la liste d'ordonnance est NULL !!!\n");
    }else if (ListOrdonnance_isEmpty(l)){
        printf("ListOrdonnance_free : la liste est vide, on free donc uniquement la liste\n");
        free((void *) l);
    }else{
        for(ListOrdonnance_setOnFirst(l); !ListOrdonnance_isOutOfList(l); ListOrdonnance_setOnNext(l)) {
            printf("ListOrdonnance_free : Appel de freeNodeOrdonnance() pour l'ordonnance : %s\n", l->current->ordo->description);
            freeNodeOrdonnance(l, l->current);
        }
        free((void *) l);
    }
}

/**
 * ListOrdonnance_free_withoutDeletingOrdonnance : Libère la mémoire occupée par l'objet ListOrdonnance passé en paramètre mais
 * sans delete les ordonnances de cette liste (uniquement les nodes)
 * @param l : la liste d'ordonnances à free
 */
void ListOrdonnance_free_withoutDeletingOrdonnance(ListOrdonnance * l){
    if (l == NULL){
        printf("ListOrdonnance_free_withoutDeletingOrdonnance : le jour est NULL !!!\n");
    }else if ( ListOrdonnance_isEmpty(l)){
        printf("ListOrdonnance_free_withoutDeletingOrdonnance : la liste est vide, on ne free donc que la liste!!!\n");
        free((void *) l);
    }else {
        for (ListOrdonnance_setOnFirst(l); !ListOrdonnance_isOutOfList(l); ListOrdonnance_setOnNext(l)) {
            freeNodeOrdonnance_withoutDeletingOrdonnance(l, l->current);
        }
        free((void *) l);
    }
}

/**
 * ListOrdonnance_isEmpty : Vérifie si la liste de Ordonnance est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le premier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current vaut NULL
 *         0 sinon
 *         -1 si la liste est NULL
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
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListOrdonnance_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListOrdonnance_setOnPrevious(ListOrdonnance * l){
    if(l != NULL && l->current->previous != NULL){
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
