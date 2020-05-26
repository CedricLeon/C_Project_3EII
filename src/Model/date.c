#include "GPCalendar/Model/date.h"

/**
 * CreerDate : Creer dynamiquement un objet Date
 * @param annee : l'annee de cette date
 * @param mois : le mois
 * @param jour : le jour
 * @return la date créée
 */
Date * CreerDate(int annee, int mois, int jour){
    Date* d = (Date *) malloc(sizeof(Date));
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
 *  getJourDate : Passe le jour de la date en paramètre sous forme de string dans infos
 * @param infos : le jour de la date sous forme de string
 * @param d : la date dont on veut le jour
 */
void getJourDate(char * infos, Date * d){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    sprintf(infos,"%02d",d->jour);

}
/**
 *  getMoisDate : Passe le mois de la date en paramètre sous forme de string dans infos
 * @param infos : le mois de la date sous forme de string
 * @param d : la date dont on veut le mois
 */
void getMoisDate(char * infos, Date * d){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    sprintf(infos,"%02d", d->mois);
}
/**
 *  getAnneeDate : Passe l'annee de la date en paramètre sous forme de string dans infos
 * @param infos : l'annee de la date sous forme de string
 * @param d : la date dont on veut l'annee
 */
void getAnneeDate(char * infos, Date * d){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    sprintf(infos,"%d",d->annee);
    if(strlen(infos) != 4) printf("Vous êtes bizarre à mettre des années à 3 chiffre.\n");
}
/**
 *  getInfosDate : Passe la date en paramètre sous forme de string XX/XX/XXXX dans infos
 * @param infos : le jour/le mois/l'annee de la date sous forme de string
 * @param d : la date dont on veut les infos
 */
void getInfosDate(char * infos, Date * d){
    // !!!!!!!!!! il faut malloc infos avant la fonction et le free après son utilisation !!!!!!!!!
    char* tmp1 = (char*) malloc(sizeof(char) * 6);
    char* tmp2 = (char*) malloc(sizeof(char) * 6);
    char* tmp3 = (char*) malloc(sizeof(char) * 6);
    getJourDate(tmp1, d);
    strcpy(infos, tmp1);
    strcat(infos, "/");
    getMoisDate(tmp2, d);
    strcat(infos, tmp2);
    strcat(infos, "/");
    getAnneeDate(tmp3, d);
    strcat(infos, tmp3);
    free((void*) tmp1);
    free((void*) tmp2);
    free((void*) tmp3);
}
/**
 * DateEgales : Fonction qui compare 2 dates, dit qu'elles sont égales si leur année, leur mois et leur jours sont les mêmes
 * @param d1 : la première date à comparer
 * @param d2 : la 2eme date
 * @return 1 si les dates sont les mêmes
 *         0 si elles ne le sont pas
 *        -1 si l'une des dates est NULL
 */
int DateEgales(Date * d1, Date * d2){
    if(d1 == NULL || d2 == NULL){
        printf("L'une des dates est NULL.\n");
        return -1;
    }
    return (d1->annee == d2->annee) && (d1->mois == d2->mois) && (d1->jour == d2->jour);
}
