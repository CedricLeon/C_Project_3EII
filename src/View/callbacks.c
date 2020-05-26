#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/View/callbacks.h"
#include <gtk/gtk.h>
#include <stdlib.h>



/**
 * calendar_date_to_string : fonction de récupération de la date au format GDate (00/00/0000)
 * @param data : le calendrier en entrée
 * @param buffer : la chaine de récupération
 * @param bufferSize : la taille du buffer
 */
 void calendar_date_to_string(CalendarData *data, char *buffer, gint bufferSize)
{
  GDate date;
  guint year, month, day;

  gtk_calendar_get_date (GTK_CALENDAR (data->window),&year, &month, &day);             //Obtains the selected date from a GtkCalendar
  g_date_set_dmy (&date, day, month + 1, year);                                        //Sets the value of a GDate (here &date) from a day, month, and year
  g_date_strftime (buffer, bufferSize - 1, "%x", &date);                               //Generates a printed representation of the date, in a locale-specific way: %x for 00/00/0000 format

}


/**
 * getDateCalendrier : récupère la date et la stocke dans la structure
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void getDateCalendrier(GtkWidget * widget, gpointer data){

    gtk_calendar_get_date(GTK_CALENDAR((((struct DateCalendrier *)data)->calendar)->window),&((struct DateCalendrier *)data)->an, &((struct DateCalendrier *)data)->mois,&((struct DateCalendrier *)data)->jour);
    ((struct DateCalendrier *)data)->mois ++;

}


/**
 * cb_affichageInfosRdv : callback d'ouverture de la fenêtre qui affiche les infos du rdv après un clic sur le bouton du rdv
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_affichageInfosRdv(GtkWidget * widget, gpointer data){
    GtkWidget *window;
    GtkWidget *box;
    char * infos = malloc(500);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);
    gtk_window_set_title(GTK_WINDOW(window), "Informations du Rendez-vous");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

    getInfosRendezVous(infos, data);
    GtkWidget * labelHaut = gtk_label_new(infos);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_container_add (GTK_CONTAINER (box), labelHaut);

    gtk_widget_show_all(window);
    free(infos);
}

/**
 * cb_create_entry1 : callback d'ouverture d'une fenêtre affichant les rdv de la journée sélectionnée sous forme de boutons
 * @param p_widget : le widget associé à l'ouverture
 * @param user_data : les informations transmises par le widget au callback
 */
void cb_create_entry1(GtkWidget *p_widget, gpointer user_data){

    GtkWidget *p_window;
    GtkWidget *p_v_box;
    GtkWidget* button;

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Liste de rendez-vous de la journée");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 350, 500);

    p_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

    /* Récupération de la date */

    getDateCalendrier(NULL, ((struct DateCalendrier *)user_data));

    Annee anneeRdv = Annee_existe(((struct DateCalendrier *)user_data)->projet->calendrier, ((struct DateCalendrier *)user_data)->an);
    Mois moisRdv = Mois_existe(anneeRdv, ((struct DateCalendrier *)user_data)->mois);

    Date* date_rdv_cherche = CreerDate(((struct DateCalendrier *)user_data)->an,((struct DateCalendrier *)user_data)->mois, (((struct DateCalendrier *)user_data)->jour));
    Jour jourRdv = Jour_existe(moisRdv, date_rdv_cherche);
    FreeDate(date_rdv_cherche);

    /*parcours de la journée */
    for(ListRendezVous_setOnFirst(jourRdv); !ListRendezVous_isOutOfList(jourRdv); ListRendezVous_setOnNext(jourRdv))
    {
        RendezVous* rdv = ListRendezVous_getCurrent(jourRdv);

        /*création bouton */
        GtkWidget * bouton = NULL;
        char * nom = malloc(75);
        char * infos = malloc(100);
        getNomPatient(nom, rdv->patient);
        sprintf(infos,"%1.2f : ",rdv->heure_debut);
        strcat(infos, nom);
        bouton=gtk_button_new_with_label (infos);
        g_signal_connect(G_OBJECT(bouton), "clicked", G_CALLBACK(cb_affichageInfosRdv), rdv);
        free(nom);
        free(infos);

        /*attache du bouton à la colonne du jour */
        gtk_container_add(GTK_CONTAINER(p_v_box), bouton);

    }

    gtk_widget_show_all(p_window);

}


/**
 * afficherMedecins : ouverture de la fenêtre qui affiche la liste des médecins enregistrés
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void afficherMedecins(GtkWidget * widget, gpointer data){

    GtkWidget * window;
    GtkWidget * box0;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Liste des médecins de cet hôpital");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 500);

    box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box0);

    /* Récupération de la date */


    for(ListMedecin_setOnFirst(((Project_GPCalendar *)data)->workingMedecins); !ListMedecin_isOutOfList(((Project_GPCalendar *)data)->workingMedecins); ListMedecin_setOnNext(((Project_GPCalendar *)data)->workingMedecins))
    {
        Medecin * m = ListMedecin_getCurrent(((Project_GPCalendar *)data)->workingMedecins);

        /*création bouton */
        GtkWidget * bouton = NULL;
        char * nom = malloc(75);
        getNomMedecin(nom, m);
        bouton=gtk_button_new_with_label (nom);
        free(nom);

        /*attache du bouton à la colonne du jour */
        gtk_container_add(GTK_CONTAINER(box0), bouton);

        /* callback */
        g_signal_connect(G_OBJECT(bouton), "clicked", G_CALLBACK(cb_affichageInfosMedecin), m);
    }

    gtk_widget_show_all(window);

}

/**
 * cb_affichageInfosMedecin : callback d'ouverture de la fenêtre qui affiche les infos du médecin après un clic sur le bouton du médecin
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_affichageInfosMedecin(GtkWidget * widget, gpointer data){
    GtkWidget *window;
    GtkWidget *box;
    char * infos = malloc(500);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);
    gtk_window_set_title(GTK_WINDOW(window), "Informations du médecin");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

    getInfoMedecin(infos, data);
    GtkWidget * labelHaut = gtk_label_new(infos);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_container_add (GTK_CONTAINER (box), labelHaut);

    gtk_widget_show_all(window);
    free(infos);
}


/**
 * afficherPatients : ouverture de la fenêtre qui affiche la liste des patients enregistrés
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void afficherPatients(GtkWidget * widget, gpointer data){

    GtkWidget * window;
    GtkWidget * box0;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Liste des patients");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 500);

    box0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box0);

    /* Récupération de la date */


    for(ListPatient_setOnFirst(((Project_GPCalendar *)data)->consultingPatient); !ListPatient_isOutOfList(((Project_GPCalendar *)data)->consultingPatient); ListPatient_setOnNext(((Project_GPCalendar *)data)->consultingPatient))
    {
        Patient * p = ListPatient_getCurrent(((Project_GPCalendar *)data)->consultingPatient);

        /*création bouton */
        GtkWidget * bouton = NULL;
        char * nom = malloc(75);
        getNomPatient(nom, p);
        bouton=gtk_button_new_with_label(nom);
        free(nom);

        /*attache du bouton à la colonne du jour */
        gtk_container_add(GTK_CONTAINER(box0), bouton);

        /* callback */
        g_signal_connect(G_OBJECT(bouton), "clicked", G_CALLBACK(cb_affichageInfosPatient), p);
    }

    gtk_widget_show_all(window);

}


/**
 * cb_affichageInfosPatient : callback d'ouverture de la fenêtre qui affiche les infos du patient après un clic sur le bouton du patient
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_affichageInfosPatient(GtkWidget * widget, gpointer data){
    GtkWidget *window;
    GtkWidget *box;
    char * infos = malloc(500);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);
    gtk_window_set_title(GTK_WINDOW(window), "Informations du patient");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

    printPatient(infos, data);
    GtkWidget * labelHaut = gtk_label_new(infos);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_container_add (GTK_CONTAINER (box), labelHaut);

    gtk_widget_show_all(window);
    free(infos);
}


/**
 * cb_create_entry2 : callback d'ouverture d'une fenêtre indiquant un champ non-rempli
 */
void cb_create_entry2(void){
    GtkWidget *window;
    GtkWidget *box;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), " /!\\ Attention /!\\ ");
    gtk_window_set_default_size(GTK_WINDOW(window), 50, 50);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);


    GtkWidget * message = gtk_label_new("\n\nparametre(s) manquant(s) : veuillez compléter les informations manquantes");
    gtk_container_add (GTK_CONTAINER (box), message);

    gtk_widget_show_all(window);

}

/**
 * closeTest : callback de fermeture d'une fenêtre après son utilisation
 * @param p_widget : le widget associé à l'ouverture
 * @param user_data : les informations transmises par le widget au callback
 */
void closeTest(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(widget);
}

/**
 * cb_clicSurPlus : callback d'ouverture de la fenêtre RecherchePatient après un clic sur le bouton '+'
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_clicSurPlus(GtkWidget * widget, gpointer data){
    fenetreRecherchePatient(widget, data);
}


/**
 * cb_recherchePatient : callback de la fenêtre RecherchePatient afin de parcourir la liste des patients
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_recherchePatient(GtkWidget * widget, gpointer data){

    /* Récupération des données */
    char * IDPatient = (char*)malloc(30*sizeof(char));
    char * IDMedecin = (char*)malloc(30*sizeof(char));
    IDPatient = (char*)gtk_entry_get_text(GTK_ENTRY(((struct RecherchePatient *)data)->EnumSecu));
    IDMedecin = (char*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct RecherchePatient *)data)->med));


    /*Parcours de la liste de médecins*/
    Medecin * m = malloc(sizeof(Medecin));
    m=ListMedecin_seek((((struct RecherchePatient *)data)->projet)->workingMedecins,IDMedecin);
    ((struct RecherchePatient *)data)->medecin = m;


    /*recherche patient*/
    Patient * p = ListPatient_seek(m->patients_recus,IDPatient);
    if (p == NULL){
        fenetreCreerPatient(widget, data);
        closeTest(((struct RecherchePatient *)data)->window,NULL);
    }
    else{
       /* Création d'une structure Data*/
        struct Data *dataPatient;
        dataPatient = (struct Data*)malloc(sizeof (struct Data));
        ((struct Data *)dataPatient)->patient = p;
        ((struct Data *)dataPatient)->medecin = m;
        ((struct Data *)dataPatient)->projet = ((struct RecherchePatient *)data)->projet;

        fenetreCreerRDV(widget, dataPatient);
    }


}


/**
 * cb_rechercheProjet : callback de la fenêtre fenetreOuverture afin de recuperer le chemin du projet
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_rechercheProjet(GtkWidget * widget, gpointer data){
    char* nomChemin=(char*)malloc(500);
    nomChemin = (char*)gtk_entry_get_text(GTK_ENTRY(((struct RechercheProjet*)data)->chemin));
//    nomChemin = "/home/user/ProjdeC/C_Project/build/CefichierEstUnTestdeLoadGPCalendarJson.json";              /**ELISABETH Pour simplifier les tests, à enlever */
//    nomChemin = "/home/user/Desktop/dproject/C_Project/build/CefichierEstUnTestdeLoadGPCalendarJson.json";            /** ROMANE Pour simplifier les tests, à enlever */
    if(strcmp(nomChemin,"")==0){                                                                                        /** il faudra remplir l'entry même si tu charges ton projet */
        cb_create_entry2();
    }else{
    (((struct RechercheProjet*)data)->project) = GPCalendar_loadProject(nomChemin);
    create_calendar(widget, data);
    closeTest(((struct RechercheProjet *) data)->window, data);
    }
}


/**
 * enter_callback : callback permettant de récupérer le texte d'une entry et de l'afficher
 * @param widget : le widget associé à l'ouverture
 * @param entry : les informations transmises par le widget au callback
 */
void enter_callback( GtkWidget *widget, GtkWidget *entry)
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

/**
 * cb_end : callback de fermeture du projet, lance la fenetre de choix de sauvegarde
 * @param widget : le widget associé à l'ouverture
 * @param entry : les informations transmises par le widget au callback
 */
void cb_end( GtkWidget *widget, gpointer data)
{
     fenetreSauvegarde(widget, data);
  }

/**
 * cb_sauvegarde : callback de fermeture du projet, sauvegarde et libère ensuite le projet
 * @param widget : le widget associé à l'ouverture
 * @param entry : les informations transmises par le widget au callback
 */
void cb_sauvegarde( GtkWidget *widget, gpointer data)
{

    char * lien = malloc(200);
    lien = gtk_entry_get_text(GTK_ENTRY(((struct RechercheProjet*)data)->chemin));
    if(GPCalendar_saveProject(lien, ((struct RechercheProjet*)data)->project)==0){
        cb_create_entry2();
    }else{
        freeProject(((struct RechercheProjet*)data)->project);
        gtk_main_quit();
    }
  }

/**
 * cb_non_sauvegarde : callback de fermeture du projet,libère le projet
 * @param widget : le widget associé à l'ouverture
 * @param entry : les informations transmises par le widget au callback
 */
void cb_non_sauvegarde( GtkWidget *widget, gpointer data)
{
    freeProject(((struct RechercheProjet*)data)->project);
    gtk_main_quit();
  }

/**
 * cb_creationPatient : callback de création du patient suite à la fenêtre creerPatient
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_creationPatient(GtkWidget * widget, gpointer data){

    char* nom ="";
    char* prenom="";
    char* mail="";
    char* tel="";
    char* secu="";

    /* Recuperation du texte contenu dans le GtkEntry */

    nom = (char*)gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->Enom));
    prenom = (char*)gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->Eprenom));
    mail = (char*)gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->Email));
    tel = (char*)gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->EnumTel));
    secu = (char*)gtk_entry_get_text(GTK_ENTRY(((struct Data*)data)->EnumSecu));

    char * jour,* mois,* annee;
    jour = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->jour)) == 0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->jour)));
    mois = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->mois)) == 0 ? -1 :(int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->mois)));
    annee = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->annee)) == 0 ? -1 :  (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct Data*)data)->annee)));

    if(jour==-1 || mois==-1 || annee==-1 || strcmp(nom, "")==0 || strcmp(prenom, "")==0 || strcmp(mail, "")==0 || strcmp(tel, "")==0 || strcmp(secu, "")==0){

             cb_create_entry2();

}else{



    Patient *p = CreerPatient(nom, prenom,(int)jour,(int)mois,(int)annee, mail, tel, secu);

    /* Ajout au projet */
    ListPatient_add(((struct Data *)data)->projet->consultingPatient, p);

    /* passage des données */

    ((struct Data*)data)->patient =p;

    fenetreCreerRDV(widget,data);
    closeTest(((struct Data*)data)->window, data);

    }
}

/**
 * cb_creationRDV : callback de création du rdv suite à la fenetreCreerRDV
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_creationRDV(GtkWidget * widget, gpointer data){

    int  jour, mois, annee, duree, heure, minutes;
    double heureDebut;
    double minutes2;
    double heure2;
    char* motif=(char*)malloc(500);
    char* lieu=(char*)malloc(500);

    jour = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->jour)) == 0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->jour))) ;
    mois = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->mois)) == 0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->mois))) ;
    annee = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->annee))== 0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->annee))) ;
    heure = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->heure))==0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->heure))) ;
    minutes = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->minutes))==0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->minutes))) ;
    duree = gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->duree))==0 ? -1 : (int)atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(((struct DataRDV*)data)->duree))) ;


    if(jour==-1 ||mois==-1 || annee==-1 || duree==-1 || minutes==-1 || heure==-1){
            cb_create_entry2();
            printf("Rajoutez un paramètre svp\n");}
    else{

     heure2= heure;
     minutes2= minutes;
     heureDebut = heure2;
     minutes2=minutes2/60;
     heureDebut+=minutes2;
     motif = gtk_entry_get_text(GTK_ENTRY(((struct DataRDV*)data)->motif));
     lieu = gtk_entry_get_text(GTK_ENTRY(((struct DataRDV*)data)->lieu));

   (((struct DataRDV*)data)->r)=CreerRendezVous(annee, mois, jour, heureDebut, duree, lieu, ((struct DataRDV*)data)->p, ((struct DataRDV*)data)->m, motif);

   AddRendezVous_Calendrier(((((struct DataRDV*)data)->projet)->calendrier), (((struct DataRDV*)data)->r));

    closeTest(((struct DataRDV*)data)->window, data);

    }
}


/**
 * cb_newProject : callback d'ouverture de la fenêtre de création d'un nouveau projet
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_newProject(GtkWidget * widget, gpointer data){

    fenetreNouveauProjet(widget, data);
    closeTest(data, data);

}

/**
 * cb_creerProjet : callback de création d'un nouveau projet
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_creerProjet(GtkWidget * widget, gpointer data){

    char * name = (char*)gtk_entry_get_text(GTK_ENTRY(((struct RechercheProjet *)data)->nom));
    ListMedecin* medecins = CreerListMedecin();
    ListPatient* patients = CreerListPatient();
    Calendrier calendrier = CreerCalendrier();
    ListMedecin_init(medecins);
    ListPatient_init(patients);

    Project_GPCalendar * projet = CreerProject(name, medecins, patients,calendrier);
    create_calendar(widget, projet);

    ((struct RechercheProjet *)data)->project = projet;

    closeTest(((struct RechercheProjet *)data)->window,((struct RechercheProjet *)data)->window);
}



/**
 * cb_creationMedecin : callback de création du médecin suite à la fenêtre creerMedecin
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_creationMedecin(GtkWidget * widget, gpointer data){

    char* nom ="";
    char* prenom="";
    char* mail="";
    char* tel="";
    char* RPPS="";

    /* Recuperation du texte contenu dans le GtkEntry */

    nom = (char*)gtk_entry_get_text(GTK_ENTRY(((struct DataMedecin*)data)->Enom));
    prenom = (char*)gtk_entry_get_text(GTK_ENTRY(((struct DataMedecin*)data)->Eprenom));
    mail = (char*)gtk_entry_get_text(GTK_ENTRY(((struct DataMedecin*)data)->Email));
    tel = (char*)gtk_entry_get_text(GTK_ENTRY(((struct DataMedecin*)data)->EnumTel));
    RPPS = (char*)gtk_entry_get_text(GTK_ENTRY(((struct DataMedecin*)data)->EnumRPPS));

    if(strcmp(nom,"") ==0 || strcmp(prenom,"") ==0 || strcmp(mail,"") ==0 || strcmp(tel,"") ==0 || strcmp(RPPS,"") ==0){
        cb_create_entry2();

    }else{

        Medecin * m = CreerMedecin(nom, prenom, mail, tel, RPPS);

        /* Ajout au projet */
        ListMedecin_add(((struct DataMedecin *)data)->projet->workingMedecins, m);

        /* passage des données */
        ((struct DataMedecin*)data)->medecin =m;

        closeTest(((struct DataMedecin*)data)->window, data);
    }

}

/**
 * cb_plusMedecin : callback d'appel de la fenêtre creerMedecin
 * @param widget : le widget associé à l'ouverture
 * @param data : les informations transmises par le widget au callback
 */
void cb_plusMedecin(GtkWidget * widget, gpointer data){
    fenetreCreerMedecin(widget, data);

}
