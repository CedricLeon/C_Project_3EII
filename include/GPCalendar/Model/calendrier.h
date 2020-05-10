#ifndef CALENDRIER_H
#define CALENDRIER_H

//Header du projet
#include "GPCalendar/Model/rendezvous.h"

//Librairies Standarts
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Pour le fonctionnement du calendrier je pense que pour que ça reste simple au maximum mais sans qu'il soit
 * quand même trop compliqué d'aller chercher un rdv en particulier, il faut fonctionner avec une liste de liste.
 *
 * On fait une liste de RendezVous, que l'on appelle un Jour. Ensuite un fait une liste de Jour qui est donc dans les
 * faits une liste de listes de RendezVous) qu'on appelle un Mois. Puis une liste de Mois, ça s'appelle une année.
 * Et enfin une liste d'année, notre Calendrier.
 *
 * Ainsi pour accéder à un rdv particulier de notre Calendrier, si on le cherche par la date, il suffit de faire
 * quelque chose comme ça :
 *
 * for(Parcours du calendrier){
 *      if(rdv->date->annee == ListAnnee_getCurrentAnnee(Calendrier)){
 *          for(Parcours de l'année){
 *              if(rdv->date->mois == ListMois_getCurrentMois(ListAnnee_getCurrentAnnee(Calendrier)){
 *                  etc....
 *
 *                  C'est long à écrire mais facile à lire et comprendre et rapide à calculer je pense
 *
 *
 * Ce raisonnement a aussi l'avantage de pouvoir facilement créer plusieurs calendrier si plus tard on permet à
 * l'application de gérer l'emploi du temps de plusieurs mèdecin etc...
 * Si on veut faire ça on à juste à ajouter un paramètre Medecin * medecin à notre ListAnnee
 * Ou alors à créer différents type comme CalendrierMedecin qui contient comme attributs une ListAnnee (pas un pointeur)
 * et un medecin. et on peut faire CalendrierPatient, CalendrierSalle, CalendrierHopital etc...
 */

/**********************************************************************************************************************/
                                        /*List de RendezVous pour un Jour*/
/**********************************************************************************************************************/
typedef struct NodeRendezVous NodeRendezVous;

struct NodeRendezVous{
    RendezVous * rdv;
    NodeRendezVous * next;
    NodeRendezVous * previous;
};

typedef struct{
    Date * date;
    NodeRendezVous sentinel_begin;
    NodeRendezVous * current;
    NodeRendezVous sentinel_end;
}ListRendezVous;

                            /*Fonctions Basiques pour notre liste de Rdv*/

NodeRendezVous * newNodeRendezVous(RendezVous * rdv , NodeRendezVous * previous, NodeRendezVous * next);
void freeNodeRendezVous(ListRendezVous * l,NodeRendezVous * n);

void ListRendezVous_init(ListRendezVous * l, Date * date);
void ListRendezVous_free(ListRendezVous * l);

int ListRendezVous_isEmpty(ListRendezVous * l);
int ListRendezVous_isFirst(ListRendezVous * l);
int ListRendezVous_isLast(ListRendezVous * l);
int ListRendezVous_isOutOfList(ListRendezVous * l);

void ListRendezVous_setOnFirst(ListRendezVous * l);
void ListRendezVous_setOnLast(ListRendezVous * l);
void ListRendezVous_setOnNext(ListRendezVous * l);
void ListRendezVous_setOnPrevious(ListRendezVous * l);
RendezVous * ListRendezVous_getCurrent(ListRendezVous * l);
Date * ListRendezVous_getDate(ListRendezVous * l);


typedef ListRendezVous * Jour;      //On redéfinis une liste de rdv comme étant un jour, c'est juste pour la lisibilité
                                    //(Cf Cours sur les liste chainées)

/**********************************************************************************************************************/
                                        /*List de Jour pour un Mois*/
/**********************************************************************************************************************/

typedef struct NodeJour NodeJour;

struct NodeJour{
    Jour jour;              //C'est un pointeur sur une Liste de RendezVous
    struct NodeJour * next;
    struct NodeJour * previous;
};

typedef struct{
    int mois;
    NodeJour sentinel_begin;
    NodeJour * current;
    NodeJour sentinel_end;
}ListJour;

                            /*Fonctions Basiques pour notre liste de Jour*/

NodeJour * newNodeJour(Jour jour , NodeJour * previous, NodeJour * next);
void freeNodeJour(ListJour * l, NodeJour * n);

void ListJour_init(ListJour * l, int mois);
void ListJour_free(ListJour * l);

int ListJour_isEmpty(ListJour * l);
int ListJour_isFirst(ListJour * l);
int ListJour_isLast(ListJour * l);
int ListJour_isOutOfList(ListJour * l);

void ListJour_setOnFirst(ListJour * l);
void ListJour_setOnLast(ListJour * l);
void ListJour_setOnNext(ListJour * l);
void ListJour_setOnPrevious(ListJour * l);
Jour ListJour_getCurrent(ListJour * l);
int ListJour_getMois(ListJour * l);


typedef ListJour * Mois;            //Idem mais pour les mois

/**********************************************************************************************************************/
                                        /*List de Mois pour une Année*/
/**********************************************************************************************************************/

typedef struct NodeMois NodeMois;

struct NodeMois{
    Mois mois;              //C'est un pointeur sur une liste de Jour
    struct NodeMois * next;
    struct NodeMois * previous;
};

typedef struct{
    int annee;
    NodeMois sentinel_begin;
    NodeMois * current;
    NodeMois sentinel_end;
}ListMois;

                            /*Fonctions Basiques pour notre liste de Mois*/

NodeMois * newNodeMois(Mois mois , NodeMois * previous, NodeMois * next);
void freeNodeMois(ListMois * l, NodeMois * n);

void ListMois_init(ListMois * l, int annee);
void ListMois_free(ListMois * l);

int ListMois_isEmpty(ListMois * l);
int ListMois_isFirst(ListMois * l);
int ListMois_isLast(ListMois * l);
int ListMois_isOutOfList(ListMois * l);

void ListMois_setOnFirst(ListMois * l);
void ListMois_setOnLast(ListMois * l);
void ListMois_setOnNext(ListMois * l);
void ListMois_setOnPrevious(ListMois * l);
Mois ListMois_getCurrent(ListMois * l);
int ListMois_getAnnee(ListMois * l);


typedef ListMois * Annee;           //encore une fois une Liste de mois est une année

/**********************************************************************************************************************/
                                        /*List d'Année pour un calendrier*/
/**********************************************************************************************************************/

typedef struct NodeAnnee NodeAnnee;

struct NodeAnnee{
    Annee annee;        //Pointeur sur une liste de Mois
    struct NodeAnnee * next;
    struct NodeAnnee * previous;
};

typedef struct{
    //int id_calendrier;            //Si on souhaite identifier les calendrier, mais pas pour l'instant
                                    //Si on l'ajoute il faut mettre à jour void ListAnnee_init(ListAnnee * l, int id_calendrier);
                                    //Et faire une fonction int ListAnnee_getIDCalendrier(ListAnnee * l);
    NodeAnnee sentinel_begin;
    NodeAnnee * current;
    NodeAnnee sentinel_end;
}ListAnnee;

                                /*Fonctions Basiques pour notre liste d'Annee*/

NodeAnnee * newNodeAnnee(Annee annee , NodeAnnee * previous, NodeAnnee * next);
void freeNodeAnnee(ListAnnee * l, NodeAnnee * n);

void ListAnnee_init(ListAnnee * l);
void ListAnnee_free(ListAnnee * l);

int ListAnnee_isEmpty(ListAnnee * l);
int ListAnnee_isFirst(ListAnnee * l);
int ListAnnee_isLast(ListAnnee * l);
int ListAnnee_isOutOfList(ListAnnee * l);

void ListAnnee_setOnFirst(ListAnnee * l);
void ListAnnee_setOnLast(ListAnnee * l);
void ListAnnee_setOnNext(ListAnnee * l);
void ListAnnee_setOnPrevious(ListAnnee * l);
Annee ListAnnee_getCurrent(ListAnnee * l);

typedef ListAnnee * Calendrier;

Calendrier CreerCalendrier();

/**********************************************************************************************************************/
                                /*Fonction d'ajout aux calendriers*/
/**********************************************************************************************************************/
int ChercherRendezVousSuivant(Jour j, RendezVous * rdv);
int AddRendezVous_Jour(Jour j, RendezVous * rdv);
int AddJour_Mois(Mois m, Jour j);
int AddMois_Annee(Annee a, Mois m);
int AddAnnee_Calendrier(Calendrier c, Annee a);

RendezVous * RendezVous_existe(ListRendezVous * l, RendezVous * rdv);
ListRendezVous * Jour_existe(ListJour * l, Date * d);
ListJour *  Mois_existe(ListMois * l, int mois);
ListMois * Annee_existe(ListAnnee * l, int annee);

int AddRendezVous_Calendrier(Calendrier c, RendezVous * rdv);
void freeCalendrier(Calendrier c);


int chercherRendezVous_Calendrier(Calendrier c, RendezVous * rdv);
void printCalendrier(Calendrier c);

#endif