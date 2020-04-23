#include "date.h"

/**
 * CreerDate : Creer dynamiquement un objet Date
 * @param annee : l'annee de cette date
 * @param mois : le mois
 * @param jour : le jour
 * @return la date créée
 */
Date * CreerDate(int annee, int mois, int jour){
    Date * d = (Date *) malloc(sizeof(Date));
    d->annee = annee;
    d->mois = mois;
    d->jour = jour;
    return d;
}
/**
 * FreeDate : Libère la mémoire d'une instance Date
 * @param d
 */
void FreeDate(Date * d){
    free((void *) d);
}
/**
 * DateCourante : Créer une date correspondant à la date courante
 * @return la date courante
 */
Date * CreerDateCourante(){
    int day, mois, an;
    time_t now;

  time(&now);

  struct tm *local = localtime(&now);
  day = local->tm_mday;
  mois = local->tm_mon + 1;
  an = local->tm_year + 1900;

  Date * d = CreerDate(an,mois,day);
  return d;
}

/**
 * AjoutMoisDate : Permet d'ajouter nb_mois à une date la date (utile notamment pour les ordonnances)
 * @param d : la date à laquelle on ajoute le nb de mois
 * @param nb_mois
 * @return la date + nb_mois
 */
Date * AjoutMoisDate(Date * d, int nb_mois){
    /*int day, mois, an;
   time_t now;
   time(&now);
   struct tm now_tm = *localtime( &now);
   time_t futurNMois = now + 30*86400*nb_mois;
   struct tm *nbMoisPlusTard_tm = localtime(&futurNMois);
   day = nbMoisPlusTard_tm->tm_mday;
   mois = nbMoisPlusTard_tm->tm_mon + 1;
   an = nbMoisPlusTard_tm->tm_year + 1900;
   Date * d = CreerDate(an,mois,day);
   return d;*/
    Date * d2 = CreerDate(d->annee, d->mois + nb_mois, d->jour);
    return d2;
}

/**
 * getJourDate : Retourne le jour sous forme de char*
 * @param d
 * @return le jour
 */
char * getJourDate(Date * d){
    char * jour = malloc(2);            //Obligé de malloc pour sprintf (Cf StackOverFlow briefcase) mais là on free jamais ...
    char * jour0=malloc(2);
    sprintf(jour,"%d",d->jour);
    if (strlen(jour)==1){
        sprintf(jour0, "0%s", jour);
        return jour0;
    }else{
        return jour;
    }
}
/**
 * getMoisDate : Retourne le mois sous forme de char*
 * @param d
 * @return le mois
 */
char * getMoisDate(Date * d){
    char * mois=malloc(2);
    char * mois0=malloc(2);
    sprintf(mois,"%d",d->mois);
    if (strlen(mois)==1){
        sprintf(mois0, "0%s", mois);
        return mois0;
    }else{
        return mois;
    }
}
/**
 * getAnneeDate : Retourne l'annee sous forme de char*
 * @param d
 * @return l'annee
 */
char * getAnneeDate(Date * d){
    char * annee = malloc(4);
    sprintf(annee,"%d",d->annee);
    return annee;
}
/**
 * getInfosDate : Permet d'obtenir une chaine de caractere avec toutes les infos de la date
 * @param d : la date en question
 * @return un char * sous la forme jour/mois/annee : XX/XX/XXXX
 */
char * getInfosDate(Date * d){
    char * result = malloc(10);
    strcpy(result, getJourDate(d));
    strcat(result, "/");
    strcat(result, getMoisDate(d));
    strcat(result, "/");
    strcat(result, getAnneeDate(d));
    strcat(result, "");
    return result;
}
/**
 * DateEgales : Fonction qui compare 2 dates, dit qu'elles sont égales si leurs année, leurs mois et leurs jours sont les mêmes
 * @param d1 : la première date à comparer
 * @param d2 : la 2eme date
 * @return 1 si les dates sont les mêmes
 *          0 si elles ne le sont pas
 *          -1 si l'une des dates est NULL
 */
int DateEgales(Date * d1, Date * d2){
    if(d1 == NULL || d2 == NULL){
        printf("L'une des dates est NULL.\n");
        return -1;
    }
    return (d1->annee == d2->annee) && (d1->mois == d2->mois) && (d1->jour == d2->jour);
}
