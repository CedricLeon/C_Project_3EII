#include "GPCalendar/Model/calendrier.h"
/**********************************************************************************************************************/
                                        /*Fonction d'ajout de RDV dans le calendrier*/
/**********************************************************************************************************************/
/**
 * AddRendezVous_Calendrier : Fonction permettant d'ajouter un rendez-vous à notre calendrier.
 *                            Pour cela il faut que le calendrier soit créé et initialisé avant l'appel et que le rdv
 *                            ait été testé comme valable auparavant (y'a-t-il de la place pour ce créneau horaire,
 *                            rentre-t-il dans les horaires du médecin etc...)
 *
 * @param c : Le calendrier auquel on veut ajouter notre rendez-vous
 * @param rdv : le rendez-vous à ajouter
 * @return 1 si le rdv a correctement été ajouté
 *         0 si il n'a pas pu l'être (Cf printf pour plus de détails)
 *         -1 si le calendrier ou le rdv étaient NULL
*/
int AddRendezVous_Calendrier(Calendrier c, RendezVous * rdv){
    if(c == NULL || rdv == NULL){
        printf("Calendrier ou Rdv inexistant.\n");
        return -1;
    }
    /**
     * Dans un premier temps on teste si notre rdv est valable, ce serait d'ailleurs peut-être mieux de le faire
     * dans une autre fonction, comme ça on pourrait l'appeller séparément de celle là. --> je suis ok vaut mieux en faire une à part (Elisabeth)
     * Et ensuite si le rdv peut être ajouté, bah on l'ajoute au calendrier.
     *
     * Et pour cela, la méthode va être toujours la même :
     * On regarde si dans notre calendrier l'année correspondant à l'année où le rdv va être ajouté existe déjà,
     * si ce n'est pas le cas on la crée, l'initialise (et du coup on crée aussi le mois et le jour correspondants
     * à ceux du rdv) et on ajoute le rdv.
     * Si l'année existaient déjà alors on cherche dans cette année le mois du rdv. Et là même charabia, si on ne le
     * trouve pas on le crée avec le jour du rdv et on ajoute tout ce beau monde à l'année et donc au calendrier. Et s'il
     * existait déjà on cherche le jour etc ...
     * Au final cela ressemble à ça :
     *
     * if(anneeDuRdv existe pas dans le calendrier){
     *      Creer l'année, le mois et le jour du rdv
     *      Ajoute tout ça au calendrier
     * }
     * else if(moisDuRdv existe pas){
     *      Creer Mois jour, ajouter au calendrier
     * }else if(jourDuRdv existe pas){
     *      Creer Jour du rdv l'ajouter avec le rdv au calendrier
     * }else{
     *      //On considère pour l'instant que si on est arrivé dans cette fonction c'est que le rdv a déjà été considéré
     *      //comme valide, cad qu'on peut le placer dans le jour sans qu'il empiete sur un autre rdv
     *      Ajoute le rdv au jour
     * }
     */
    /*if(RDV pas valable){
        return 0;
    }*/

    // Est-ce que notre calendrier est complétement vide ou est-ce que l'année du Rdv n'existe pas encore?
    // Si oui : On crée le jour, le mois et l'année qui correspondent au rdv et on ajoute le tout
    Annee anneeDuRdv = Annee_existe(c, rdv->date->annee);
    if(ListAnnee_isEmpty(c) || anneeDuRdv == NULL){
        //On crée notre liste de rdv, on l'initialise et on ajoute rdv dedans
        ListRendezVous * lRdv = (ListRendezVous *) malloc(sizeof(ListRendezVous));

        //Ici on recrée une date au lieu de définir la date du jour comme la date du premier rdv quil contient
        // car il ne faut pas que la date du jour et la date de son premier rdv soit lié si on veut pouvoir supprimer
        // le 1er rdv. C'est aussi plus simple pour les fonctions free
        Date * dateDuJour = CreerDate(rdv->date->annee, rdv->date->mois, rdv->date->jour);
        ListRendezVous_init(lRdv, dateDuJour);

        AddRendezVous_Jour(lRdv, rdv);
        ListRendezVous_setOnFirst(lRdv);

        //Ensuite On crée notre liste de jours, on l'initialise et on ajoute notre jour dedans
        ListJour * lJ = (ListJour *) malloc(sizeof(ListJour));
        ListJour_init(lJ, rdv->date->mois);
        AddJour_Mois(lJ, lRdv);
        ListJour_setOnFirst(lJ);

        //Puis on crée notre liste de mois, on l'initialise et on ajoute notre mois dedans
        ListMois * lM = (ListMois *) malloc(sizeof(ListMois));
        ListMois_init(lM, rdv->date->annee);
        AddMois_Annee(lM, lJ);
        ListMois_setOnFirst(lM);

        //Et finalement on prend notre calendrier, il est déjà initialisé donc on ajoute juste notre année dedans
        AddAnnee_Calendrier(c, lM);
        ListAnnee_setOnFirst(c);
        printf("Rendez-vous du %d/%d/%d à %2.1fh ajouté au calendrier.\n", rdv->date->jour, rdv->date->mois, rdv->date->annee, rdv->heure_debut);
        return 1;
    }
    //Notre calendrier n'était pas vide et l'année du rdv existait déjà donc on regarde si le mois du rdv est déjà
    //présent dans le calendrier

    Mois moisDuRdv = Mois_existe(anneeDuRdv, rdv->date->mois);
    if(moisDuRdv == NULL){
        //On crée notre liste de rdv, on l'initialise et on ajoute rdv dedans
        ListRendezVous * lRdv = (ListRendezVous *) malloc(sizeof(ListRendezVous));

        //Ici on recrée une date au lieu de définir la date du jour comme la date du premier rdv quil contient
        // car il ne faut pas que la date du jour et la date de son premier rdv soit lié si on veut pouvoir supprimer
        // le 1er rdv. C'est aussi plus simple pour les fonctions free
        Date * dateDuJour = CreerDate(rdv->date->annee, rdv->date->mois, rdv->date->jour);
        ListRendezVous_init(lRdv, dateDuJour);

        AddRendezVous_Jour(lRdv, rdv);

        //Ensuite On crée notre liste de jours, on l'initialise et on ajoute notre jour dedans
        ListJour * lJ = (ListJour *) malloc(sizeof(ListJour));
        ListJour_init(lJ, rdv->date->mois);
        AddJour_Mois(lJ, lRdv);

        //On ajoute notre nouveau mois à l'année du rdv, ce qui l'ajoute donc à notre calendrier
        AddMois_Annee(anneeDuRdv, lJ);
        printf("Rendez-vous du %d/%d/%d à %2.1fh ajouté au calendrier.\n", rdv->date->jour, rdv->date->mois, rdv->date->annee, rdv->heure_debut);
        return 1;
    }
    //Vous commencez à avoir la logique : le calendrier n'était pas vide. Il contenait déjà l'année du rdv.
    // Cette dernière contenait déjà le mois du rdv, on teste donc si ce mois contient déjà le jour du rdv :
    Jour jourDuRdv = Jour_existe(moisDuRdv, rdv->date);
    if(jourDuRdv == NULL){
        //On crée notre liste de rdv, on l'initialise et on ajoute rdv dedans
        ListRendezVous * lRdv = (ListRendezVous *) malloc(sizeof(ListRendezVous));

        //Ici on recrée une date au lieu de définir la date du jour comme la date du premier rdv quil contient
        // car il ne faut pas que la date du jour et la date de son premier rdv soit lié si on veut pouvoir supprimer
        // le 1er rdv. C'est aussi plus simple pour les fonctions free
        Date * dateDuJour = CreerDate(rdv->date->annee, rdv->date->mois, rdv->date->jour);
        ListRendezVous_init(lRdv, dateDuJour);

        AddRendezVous_Jour(lRdv, rdv);

        AddJour_Mois(moisDuRdv, lRdv);
        printf("Rendez-vous du %d/%d/%d à %2.1fh ajouté au calendrier.\n", rdv->date->jour, rdv->date->mois, rdv->date->annee, rdv->heure_debut);
        return 1;
    }else{
        AddRendezVous_Jour(jourDuRdv, rdv);
        printf("Rendez-vous du %d/%d/%d à %2.1fh ajouté au calendrier.\n", rdv->date->jour, rdv->date->mois, rdv->date->annee, rdv->heure_debut);
        return 1;
    }
}

/**
 * freeCalendrier : Cette fonction va entièrement free le contenu d'un calendrier, notamment ses rdv. Dans les faits elle
 *                  sera appelée quand l'utilisateur fermera l'application, après avoir sauvegardé le calendrier en
 *                  question dans un fichier cJSON.
 * @param c : le calendrier à free
 */
void freeCalendrier(Calendrier c){
    printf("\n Entrée dans FreeCalendrier() :\n\n");
    ListAnnee_free(c);
    printf("\n Fin de FreeCalendrier().\n");
}

/**
 * chercherRendezVous_Calendrier : Fonction qui positionne tous les pointeurs courants des listes d'années, de mois, de
 *                                 jours et de rdv sur la liste contenant notre rendez-vous s'il appartient au calendrier.
 * @param c : le calendrier dans lequel on cherche
 * @param rdv : le rdv cherché
 * @return 1 si le rdv a été trouvé, 0 si le rdv n'appartient pas au calendrier, -1 si l'un des objets est NULL
 */
int chercherRendezVous_Calendrier(Calendrier c, RendezVous * rdv){
    if(c == NULL || rdv == NULL){
        printf("Dans la fonction chercherRendezVous_Calendrier(), le calendrier ou le rdv sont NULL.\n");
        return  -1;
    }

    Date * dateDuRdv = rdv->date;
    Annee anneeRdv = Annee_existe(c, dateDuRdv->annee);
    if (anneeRdv != NULL){
        Mois moisRdv = Mois_existe(anneeRdv, dateDuRdv->mois);
        if(moisRdv != NULL){
            Jour jourRdv = Jour_existe(moisRdv, dateDuRdv);
            if(jourRdv != NULL){
                RendezVous * rdvCalendrier = RendezVous_existe(jourRdv, rdv);
                return 1;
            }else{
                printf("Le jour %d n'appartient pas au calendrier.\n", dateDuRdv->jour);
                return 0;
            }
        }else{
            printf("Le mois %d n'appartient pas au calendrier.\n", dateDuRdv->mois);
            return 0;
        }
    }else{
        printf("L'année %d n'appartient pas au calendrier.\n", dateDuRdv->annee);
        return 0;
    }
}

void printCalendrier(Calendrier c)
{
    printf("\n***************Affichage du calendrier*************\n");
    for(ListAnnee_setOnFirst(c); !ListAnnee_isOutOfList(c); ListAnnee_setOnNext(c))
    {
        Annee a = ListAnnee_getCurrent(c);
        printf("%d :\n",a->annee);
        //On parcourt tous les mois présents dans l'année' et on "entre dedans"
        for(ListMois_setOnFirst(a); !ListMois_isOutOfList(a); ListMois_setOnNext(a))
        {
            Mois m = ListMois_getCurrent(a);
            printf("\t - %d :\n",m->mois);
            //On parcourt tous les jours présents dans le mois et on "entre dedans"
            for(ListJour_setOnFirst(m); !ListJour_isOutOfList(m); ListJour_setOnNext(m))
            {
                Jour j = ListJour_getCurrent(m);
                printf("\t\t-- %d/%d/%d :", j->date->jour, j->date->mois, j->date->annee);
                for(ListRendezVous_setOnFirst(j); !ListRendezVous_isOutOfList(j); ListRendezVous_setOnNext(j))
                {
                    if(ListRendezVous_isLast(j)){
                        printf("  %2.1f-%2.1fh", ListRendezVous_getCurrent(j)->heure_debut, ListRendezVous_getCurrent(j)->heure_fin);
                    }else {
                        printf("  %2.1f-%2.1fh  /", ListRendezVous_getCurrent(j)->heure_debut, ListRendezVous_getCurrent(j)->heure_fin);
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    printf("***************Fin du calendrier*************\n");

}

/**********************************************************************************************************************/
                        /*Sous fonctions d'ajouts et de recherches dans le calendrier*/
/**********************************************************************************************************************/

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
    //Dans le cas ou ChercherRendezVousSuivant n'a pas return 1 c'est que notre rdv doit etre inséré en fin de
    //listRendezVous puisque ni j ni rdv ne sont nuls (testés plus haut)
    //On l'insère donc à la fin de liste
    ListRendezVous_setOnNext(j);
    NodeRendezVous * newNode = newNodeRendezVous(rdv, j->sentinel_end.previous, &(j->sentinel_end));
    j->sentinel_end.previous->next = newNode;
    j->sentinel_end.previous = newNode;
    return 1;
}

/**
 * ChercherRendezVousSuivant : Place Current sur le rdv dont l'heure de debut est juste apres l'heure de fin du rdv
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
    //On parcourt chronologiquement les rdv du jour
    for(ListRendezVous_setOnFirst(j); !ListRendezVous_isLast(j); ListRendezVous_setOnNext(j)){
        if(ListRendezVous_getCurrent(j)->heure_debut >= rdv->heure_fin){            //On met >= pcq pas de
                                                                                    //pause pour les medecins
            return 1;   //Current est bien placé sur le rdv "suivant" celui passé en paramètre
        }
    }
    //Si on arrive là ça veut dire que notre rdv est le dernier de la journée, en effet dans la boucle for précédente,
    // current est arrivé jusqu'à sentinel_end. On le remet donc dans la liste (au début par exemple)
    // et on return donc 0 pour l'indiquer.
    ListRendezVous_setOnFirst(j); /* Last ou first peu importe on veut juste pas le laisser en dehors de liste*/
    return 0;
}
/**
 * AddJour_Mois : Ajoute un Jour à une liste de Jour triée chrnologiquement (via leur attribut Date)
 * @param m : la liste de jour, le mois
 * @param j : le jour a ajouter
 * @return 1 Si le jour a bien été ajouté
 *         0 Si il ne l'a pas été
 *         -1 si le mois ou le jour étaient NULL
 */
int AddJour_Mois(Mois m, Jour j){
    if(j == NULL || m == NULL){
        printf("Jour ou Mois NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListJour_isEmpty(m)){
        NodeJour * newNode = newNodeJour(j, &(m->sentinel_begin), &(m->sentinel_end));
        m->sentinel_begin.next = newNode;
        m->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on cherche et on insère
    for(ListJour_setOnFirst(m); !ListJour_isLast(m); ListJour_setOnNext(m)){
        if(j->date->jour < ListJour_getCurrent(m)->date->jour){
            NodeJour * newNode = newNodeJour(j, m->current->previous, m->current);
            m->current->previous->next = newNode;
            m->current->previous = newNode;
            return 1;
        }else if(j->date->jour == ListJour_getCurrent(m)->date->jour){
            printf("Dans AddJour_Mois : Cas bizarre : égalité de 2 jours.\n");
        }
    }
    //Si on a rien trouvé alors c'est le dernier, on insère à la fin
    ListJour_setOnNext(m);
    NodeJour * newNode = newNodeJour(j, m->sentinel_end.previous, &(m->sentinel_end));
    m->sentinel_end.previous->next = newNode;
    m->sentinel_end.previous = newNode;
    return 1;
}
/**
 * AddMois_Annee : Ajoute un Mois à une liste de Mois triée chrnologiquement (via leur attribut int mois)
 * @param a : la liste de mois, l'année
 * @param m : le mois à ajouter
 * @return 1 Si le mois a bien été ajouté
 *         0 Si il ne l'a pas été
 *         -1 si le mois ou l'année étaient NULL
 */
int AddMois_Annee(Annee a, Mois m){
    if(a == NULL || m == NULL){
        printf("Mois ou Année NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListMois_isEmpty(a)){
        NodeMois * newNode = newNodeMois(m, &(a->sentinel_begin), &(a->sentinel_end));
        a->sentinel_begin.next = newNode;
        a->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on cherche et on insère
    for(ListMois_setOnFirst(a); !ListMois_isLast(a); ListMois_setOnNext(a)){
        if(m->mois < ListMois_getCurrent(a)->mois){
            NodeMois * newNode = newNodeMois(m, a->current->previous, a->current);
            a->current->previous->next = newNode;
            a->current->previous = newNode;
            return 1;
        }else if(m->mois == ListMois_getCurrent(a)->mois){
            printf("Dans AddMois_Annee : Cas bizarre : égalité de 2 mois.\n");
        }
    }
    //Si on a rien trouvé alors c'est le dernier, on insère à la fin
    ListMois_setOnNext(a);
    NodeMois * newNode = newNodeMois(m, a->sentinel_end.previous, &(a->sentinel_end));
    a->sentinel_end.previous->next = newNode;
    a->sentinel_end.previous = newNode;
    return 1;
}
/**
 * AddAnnee_Calendrier : Ajoute une annee à une liste d'annee triée chrnologiquement (via leur attribut int annee)
 * @param c : la liste d'annee, le calendrier
 * @param a : l'annee à ajouter
 * @return 1 Si l'annee a bien été ajoutée
 *         0 Si elle ne l'a pas été
 *         -1 si le calendrier ou l'année étaient NULL
 */
int AddAnnee_Calendrier(Calendrier c, Annee a){
    if(a == NULL || c == NULL){
        printf("Calendrier ou Année NULL.\n");
        return -1;
    }
    //Si Liste vide on insère au début
    if(ListAnnee_isEmpty(c)){
        NodeAnnee * newNode = newNodeAnnee(a, &(c->sentinel_begin), &(c->sentinel_end));
        c->sentinel_begin.next = newNode;
        c->sentinel_end.previous = newNode;
        return 1;
    }
    //Si pas vide on cherche et on insère
    for(ListAnnee_setOnFirst(c); !ListAnnee_isLast(c); ListAnnee_setOnNext(c)){
        if(a->annee < ListAnnee_getCurrent(c)->annee){
            NodeAnnee * newNode = newNodeAnnee(a, c->current->previous, c->current);
            c->current->previous->next = newNode;
            c->current->previous = newNode;
            return 1;
        }
        else if(a->annee == ListAnnee_getCurrent(c)->annee){
            printf("Dans AddAnnee_Calendrier : Cas bizarre : égalité de 2 années.\n");
        }
    }
    //Si on a rien trouvé alors c'est le dernier, on insère à la fin
    ListAnnee_setOnNext(c);
    NodeAnnee * newNode = newNodeAnnee(a, c->sentinel_end.previous, &(c->sentinel_end));
    c->sentinel_end.previous->next = newNode;
    c->sentinel_end.previous = newNode;
    return 1;
}
/**
 * Rdv_existe : Cherche un rdv dans une liste de rdv
 * @param l : la liste dans laquelle on cherche
 * @param rdv : le rdv cherché
 * @return un pointeur sur le rdv si il est trouvé
 *         NULL si il n'est pas trouvé ou si la liste ou le rdv étaient NULL
 */
RendezVous * RendezVous_existe(ListRendezVous * l, RendezVous * rdv){
    if (l == NULL || rdv == NULL){
        printf("RendezVous_existe() : La list de rdv ou le rdv est NULL.\n");
        return NULL;
    }else if(ListRendezVous_isEmpty(l)){
        printf("RendezVous_existe() : La liste de rdv est vide, on ne peut donc pas trouver le rdv cherché.\n");
        return NULL;
    }
    for (ListRendezVous_setOnFirst(l); !ListRendezVous_isOutOfList(l); ListRendezVous_setOnNext(l)){
        if(ListRendezVous_getCurrent(l) == rdv){
            return ListRendezVous_getCurrent(l);
        }
    }
    printf("RendezVous_existe() : Rdv non-trouvé.\n");
    return NULL;
}
/**
 * Jour_existe : Cherche un jour dans une liste de jours
 * @param l : la liste dans laquelle on cherche
 * @param j : le jour cherché
 * @return un pointeur sur le jour si il est trouvé
 *         NULL si il n'est pas trouvé ou si la liste ou le jour étaient NULL
 */
ListRendezVous * Jour_existe(ListJour * l, Date * d){
    if (l == NULL || d == NULL){
        printf("Jour_existe() : La list de jour ou le jour est NULL.\n");
        return NULL;
    }else if(ListJour_isEmpty(l)){
        printf("Jour_existe() : La liste de jours est vide, on ne peut donc pas trouver le jour cherché.\n");
        return NULL;
    }
    for (ListJour_setOnFirst(l); !ListJour_isOutOfList(l); ListJour_setOnNext(l)){
        if(DateEgales(ListRendezVous_getDate(ListJour_getCurrent(l)), d)){   // On compare la date des jours puisqu'ils sont uniques
            return ListJour_getCurrent(l);
        }
    }
    printf("Jour_existe() : Jour non-trouvé.\n");
    return NULL;
}
/**
 * Mois_existe : Cherche un mois dans une liste de mois
 * @param l : la liste dans laquelle on cherche
 * @param m : le mois cherché
 * @return un pointeur sur le mois si il est trouvé
 *         NULL si il n'est pas trouvé ou si la liste était NULL
 */
ListJour *  Mois_existe(ListMois * l, int mois){
    if (l == NULL){
        printf("Mois_existe() : La list de mois est NULL.\n");
        return NULL;
    }else if(ListMois_isEmpty(l)){
        printf("Mois_existe() : La liste de mois est vide, on ne peut donc pas trouver le mois cherché.\n");
        return NULL;
    }
    for (ListMois_setOnFirst(l); !ListMois_isOutOfList(l); ListMois_setOnNext(l)){
        if(ListMois_getCurrent(l)->mois == mois){
            return ListMois_getCurrent(l);
        }
    }
    printf("Mois_existe() : Mois non-trouvé.\n");
    return NULL;
}
/**
 * Annee_existe : Cherche une Annee dans une liste d'Annee
 * @param l : la liste dans laquelle on cherche
 * @param a : l'Annee cherchée
 * @return un pointeur sur l'Annee si elle est trouvée
 *         NULL si elle n'est pas trouvée ou si la liste était NULL
 */
ListMois * Annee_existe(ListAnnee * l, int annee){
    if (l == NULL){
        printf("Annee_existe() : La list d'Annee est NULL.\n");
        return NULL;
    }else if(ListAnnee_isEmpty(l)){
        printf("Annee_existe() : La liste d'années est vide, on ne peut donc pas trouver l'année cherchée.\n");
        return NULL;
    }
    for (ListAnnee_setOnFirst(l); !ListAnnee_isOutOfList(l); ListAnnee_setOnNext(l)){
        if(ListAnnee_getCurrent(l)->annee == annee){
            return ListAnnee_getCurrent(l);
        }
    }
    printf("Annee_existe() : Annee non-trouvé.\n");
    return NULL;
}

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
 * freeNodeRendezVous : Fonction permettant de free un objet NodeRendezVous
 * @param n : le node en question
 */
void freeNodeRendezVous(ListRendezVous * l, NodeRendezVous * n){
    //C'est ici qu'on vient free les rdv.
    //Pour l'instant cette fonction n'est appellée que par ListRendezVous_free() qui est uniquement appellée par free_calendrier()

    //On set les pointeurs des objets précédant et suivant le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    //et enfin on supprime le noeud
    printf("\t\t\t\tfreeNodeRendezVous : appel de FreeRendezVous.\n");
    FreeRendezVous(n->rdv);
    free((void *) n);
    //On place current sur sentinel_begin pour que le setOnnext de la boucle for le place sur le premier élément de liste
    //On est obligé de faire ça car sinon current reste sur le noeud qu'on vient de free et donc sur NULL et isOutOfList return true alors que pas forcément
    ListRendezVous_setOnFirst(l);
    ListRendezVous_setOnPrevious(l);
    printf("\t\t\t\tfreeNodeRendezVous : fin de la fonction.\n");
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
 * ListRendezVous_free : Libère la mémoire occupée par l'objet ListRendezVous passé en paramètre
 * @param l : la liste de rendezVous à free
 */
void ListRendezVous_free(ListRendezVous * l){
    if (l == NULL){
        printf("ListRendezVous_free : le jour est NULL !!!\n");
    }else if ( ListRendezVous_isEmpty(l)){
        printf("ListRendezVous_free : la liste est vide, ce n'est pas normal (mais si ca arrive on free juste la liste)!!!\n");
        free((void *) l);
    }else{
        printf("\t\t\tEntrée dans ListRendezVous_free() pour le jour : %d/%d/%d.\n", l->date->jour, l->date->mois, l->date->annee);
        for (ListRendezVous_setOnFirst(l); !ListRendezVous_isOutOfList(l); ListRendezVous_setOnNext(l)) {
            printf("\t\t\t\tListRendezVous_free : début boucle for \n");
            freeNodeRendezVous(l, l->current);
        }
        printf("\t\t\tLe jour %d/%d/%d a bien été free.\n", l->date->jour, l->date->mois, l->date->annee);
        FreeDate(l->date);
        free((void *) l);
    }
}

/**
 * ListRendezVous_isEmpty : Vérifie si la liste de RendezVous est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le premier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current vaut NULL
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListRendezVous_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListRendezVous_setOnPrevious(ListRendezVous * l){
    if(l != NULL && l->current->previous != NULL){
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
 * @return la date si la liste n'est pas NULL,
 *         NULL si la liste est NULL
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
    NodeJour* newNode;
    newNode = (NodeJour*) malloc(sizeof(NodeJour));
    newNode->jour = jour;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}
/**
 * freeNodeJour : Fonction permettant de free un objet NodeJour
 * @param n : le node en question
 */
void freeNodeJour(ListJour * l, NodeJour * n){

    //On set les pointeurs des objets précédant et suivant le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    //et enfin on supprime le noeud

    char * tmp = (char*) malloc(10);
    getInfosDate(tmp, l->current->jour->date);
    printf("\t\t\tfreeNodeJour : Appel de ListRendezVous_free pourle jour : %s\n", tmp);
    free((void*) tmp);

    ListRendezVous_free(n->jour);   //On free le jour (donc la liste de RDV qui vient elle même free tous ses nodes) pointé par le Node
    free((void *) n);

    //On place current sur sentinel_begin pour que le setOnnext de la boucle for le place sur le premier élément de liste
    //On est obligé de faire ça car sinon current reste sur le noeud qu'on vient de free et donc sur NULL et isOutOfList return true alors que pas forcément
    ListJour_setOnFirst(l);
    ListJour_setOnPrevious(l);
}

/**
 * ListJour_init : Initialise correctement une liste de NodeJour en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 * @param mois : le numéro correspondant au mois (la liste de jours)
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
 * ListJour_free : Libère la mémoire occupée par l'objet ListJour passé en paramètre
 * @param l : la liste de Jour à free
 */
void ListJour_free(ListJour * l){
    if (l == NULL){
        printf("ListJour_free : le jour est NULL !!!\n");
    }else if ( ListJour_isEmpty(l)){
        printf("ListJour_free : la liste est vide, ce n'est pas normal (mais si ca arrive on free juste la liste)!!!\n");
        free((void *) l);
    }else{
        printf("\t\tEntrée dans la fonction ListJour_Free().\n");
        for(ListJour_setOnFirst(l); !ListJour_isOutOfList(l); ListJour_setOnNext(l)) {
            printf("\t\t\tListJour_free : début boucle for\n");
            freeNodeJour(l, l->current);
            if(l->current == &(l->sentinel_begin)) printf("\t\t\tOn est sur sentinel_begin : normal\n");
        }
        printf("\t\tLe mois %d a été free.\n", l->mois);
        free((void *) l);
    }
}

/**
 * ListJour_isEmpty : Vérifie si la liste de Jour est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le premier élément
            0 si il ne l'est pas
            -1 si la liste est NULL
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
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current vaut NULL
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
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
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListJour_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListJour_setOnPrevious(ListJour * l){
    if(l != NULL && l->current->previous != NULL){
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
 * @return le numéro du mois si la liste n'est pas vide
 *         0 sinon
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
void freeNodeMois(ListMois * l, NodeMois * n){

    //On set les pointeurs des objets précédant et suivant le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    //et enfin on supprime le noeud
    printf("\t\tfreeNodeMois : Appel de ListJour_free pour le mois : %d\n", l->current->mois->mois);
    ListJour_free(n->mois);   //On free le mois (donc la liste de listes de RDV qui vient elle meme free tous ses nodes) pointé par le Node
    free((void *) n);

    //On place current sur sentinel_begin pour que le setOnnext de la boucle for le place sur le premier élément de liste
    //On est obligé de faire ça car sinon current reste sur le noeud qu'on vient de free et donc sur NULL et isOutOfList return true alors que pas forcément
    ListMois_setOnFirst(l);
    ListMois_setOnPrevious(l);
}

/**
 * ListMois_init : Initialise correctement une liste de NodeMois en reliant sentinel_begin et end entre eux
 * et en mettant current à NULL (en dehors de la liste)
 * @param l : la liste à initialiser
 * @param annee : le numéro correspondant au mois (la liste de Mois)
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
 * ListMois_free : Libère la mémoire occupée par l'objet ListMois passé en paramètre
 * @param l : la liste de Mois à free
 */
void ListMois_free(ListMois * l){
    if (l == NULL){
        printf("ListMois_free : le jour est NULL !!!\n");
    }else if ( ListMois_isEmpty(l)){
        printf("ListMois_free : la liste est vide, ce n'est pas normal (mais si ca arrive on free juste la liste)!!!\n");
        free((void *) l);
    }else{
        printf("\tEntrée dans ListMois_free.\n");
        for(ListMois_setOnFirst(l); !ListMois_isOutOfList(l); ListMois_setOnNext(l)) {
            printf("\t\tListMois_free : debut boucle for\n");
            freeNodeMois(l, l->current);
            printf("\t\tNodeMois free (fin boucle for).\n");
        }
    }
    printf("\tLa liste de mois %d a bien été free.\n", l->annee);
    free((void *) l);
}

/**
 * ListMois_isEmpty : Vérifie si la liste de Mois est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le premier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current vaut NULL
 *         0 sinon
 *         -1 si la liste est NULL
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
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListMois_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListMois_setOnPrevious(ListMois * l){
    if(l != NULL && l->current->previous != NULL){
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
 * @return le numéro de l'annéée si la liste n'est pas vide
 *         0 sinon
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
 * CreerCalendrier : Fonction qui Cree et intialise un objet calendrier
 * @return le calendrier initialisé.
 */
Calendrier CreerCalendrier(){
    ListAnnee* c;
    c = (ListAnnee*) malloc(sizeof(ListAnnee));
    ListAnnee_init(c);
    return c;
}

/**
 * newNodeAnnee : Fonction permettant de créer un nouvel objet NodeAnnee
 * @param annee : l'annee (donc une liste de mois ou une liste de liste de liste de rdv) pointé par ce nouveau NodeAnnee
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
void freeNodeAnnee(ListAnnee * l, NodeAnnee * n){
    //On set les pointeurs des objets précédant et suivant le noeud à supprimer correctement
    n->previous->next = n->next;
    n->next->previous = n->previous;
    //et enfin on supprime le noeud
    printf("\tfreeNodeAnnee : Appel de ListMois_free() pour l'année : %d\n", l->current->annee->annee);
    ListMois_free(n->annee);   //On free l'annee (donc la liste de liste de liste de RDV qui vient elle meme free tous ses nodes) pointé par le Node
    free((void *) n);

    //On place current sur sentinel_begin pour que le setOnnext de la boucle for le place sur le premier élément de liste
    //On est obligé de faire ça car sinon current reste sur le noeud qu'on vient de free et donc sur NULL et isOutOfList return true alors que pas forcément
    ListAnnee_setOnFirst(l);
    ListAnnee_setOnPrevious(l);
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
 * ListAnnee_free : Libère la mémoire occupée par l'objet ListAnnee passé en paramètre
 * @param l : la liste de Annee à free
 */
void ListAnnee_free(ListAnnee * l){
    if (l == NULL){
        printf("ListAnnee_free : le jour est NULL !!!\n");
    }else if ( ListAnnee_isEmpty(l)){
        printf("ListAnnee_free : la liste est vide, ce n'est pas normal (mais si ca arrive on free juste la liste)!!!\n");
        free((void *) l);
    }else{
        printf("Entrée dans ListAnnee_free.\n");
        for(ListAnnee_setOnFirst(l); !ListAnnee_isOutOfList(l); ListAnnee_setOnNext(l)) {
            printf("\tListAnnee_free : debut boucle for\n");
            freeNodeAnnee(l, l->current);
            printf("\tNodeAnnee free (fin boucle for.\n");
        }
    }
    printCalendrier(l); // On vérifie que le calendrier est vide
    free((void *) l);
    printf("La liste d'années a bien été free.\n");
}

/**
 * ListAnnee_isEmpty : Vérifie si la liste de Annee est vide ou non
 * @param l : la liste
 * @return 1 si la liste est vide
 *         0 si elle ne l'est pas
 *         -1 si la liste est NULL
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
 * @return 1 si current est bien sur le premier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL */
int ListAnnee_isFirst(ListAnnee * l){
    if (l != NULL){
        return  l->current == l->sentinel_begin.next;
    }
    return -1; //La liste est NULL
}
/**
 * ListAnnee_isLast : Vérifie si current est positionné sur le dernier élément de la liste
 * @param l : la liste
 * @return 1 si current est bien sur le dernier élément
 *         0 si il ne l'est pas
 *         -1 si la liste est NULL */
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
 * @return 1 si current vaut NULL
 *         0 sinon
 *         -1 si la liste est NULL */
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
    if(l != NULL && l->current->next != NULL){
        l->current = l->current->next;
    }
}
/**
 * ListAnnee_setOnPrevious : Positionne le pointeur courant sur l'élément le précédant dans la liste
 * @param l : la liste
 */
void ListAnnee_setOnPrevious(ListAnnee * l){
    if(l != NULL && l->current->previous != NULL){
        l->current = l->current->previous;
    }
}
/**
 * ListAnnee_getCurrent : Permet d'acceder au Annee pointé par current
 * @param l : la liste
 * @return Retourne un pointeur sur l'Annee de l'élément courant de la liste
 */
Annee ListAnnee_getCurrent(ListAnnee * l){
    if(l != NULL && l->current != NULL){
        return l->current->annee;
    }
    return NULL;
}
