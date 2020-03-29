#include "date.h"
#include <time.h>

/*Création d'une date*/
Date * CreerDate(int annee, int mois, int jour){
    Date * d;
    d->annee = annee;
    d->mois = mois;
    d->jour = jour;
    return d;
}

/*Récupération de la date courante*/
Date * DateCourante(){
    int day, mois, an;
  time_t now;

  time(&now);

  struct tm *local = localtime(&now);
  day = local->tm_mday;
  mois = local->tm_mon + 1;
  an = local->tm_year + 1900;

  Date * d;
  d->annee=an;
  d->mois=mois;
  d->jour=day;

  return d;
}

/*Ajouter nb_mois mois à la date courante*/
Date * AjoutMoisDateCourante(int nb_mois){
    int day, mois, an;
    time_t now;
    time(&now);
    struct tm now_tm = *localtime( &now);
    time_t futurNMois = now + 30*86400*nb_mois;
    struct tm *nbMoisPlusTard_tm = localtime(&futurNMois);

    day = nbMoisPlusTard_tm->tm_mday;
    mois = nbMoisPlusTard_tm->tm_mon + 1;
    an = nbMoisPlusTard_tm->tm_year + 1900;

    Date * d;
    d->annee=an;
    d->mois=mois;
    d->jour=day;

    return d;
}

