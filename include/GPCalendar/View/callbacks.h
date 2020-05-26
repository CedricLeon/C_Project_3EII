
#ifndef CALLBACKS_H_INC
#define CALLBACKS_H_INC

#include "GPCalendar/Model/project_GPCalendar.h"
#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/calendrier.h"
#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct _CalendarData {
  GtkWidget *window;
  GtkWidget *prev_sig;
  GtkWidget *last_sig;
  GtkWidget *month;
}CalendarData;

typedef struct DateCalendrier{
    Project_GPCalendar * projet;
    CalendarData * calendar;
    guint jour;
    guint mois;
    guint an;
}datecalendrier;


typedef struct Data{
    GtkWidget * Enom;
    GtkWidget * Eprenom;
    GtkWidget * EnumSecu;
    GtkWidget * EnumTel;
    GtkWidget * Email;
    GtkWidget * jour;
    GtkWidget * mois;
    GtkWidget * annee;
    GtkWidget * window;
    Patient * patient;
    Medecin * medecin;
    Project_GPCalendar * projet;
}dataPatient;

typedef struct DataRDV{
    GtkWidget * jour;
    GtkWidget * mois;
    GtkWidget * annee;
    GtkWidget * heure;
    GtkWidget * minutes;
    GtkWidget * duree;
    GtkWidget * motif;
    GtkWidget * lieu;
    GtkWidget* window;
    RendezVous *r;
    Patient * p;
    Medecin *m;
    Project_GPCalendar * projet;
}datardv;

typedef struct RecherchePatient{
    GtkWidget * med;
    GtkWidget * EnumSecu;
    GtkWidget * window;
    Medecin* medecin;
    Patient* patient;
    Project_GPCalendar * projet;

}recherchepatient;

typedef struct RechercheProjet{
    GtkWidget * chemin;
    GtkWidget* nom;
    GtkWidget* window;
    Project_GPCalendar *project;
}rechercheprojet;

typedef struct DataMedecin{
    GtkWidget * Enom;
    GtkWidget * Eprenom;
    GtkWidget * EnumRPPS;
    GtkWidget * EnumTel;
    GtkWidget * Email;
    GtkWidget * window;
    Medecin * medecin;
    Project_GPCalendar * projet;
}dataMedecin;



void getDateCalendrier(GtkWidget * widget, gpointer data);
void calendar_date_to_string( CalendarData *data, char *buffer, gint bufferSize );

void cb_create_entry(GtkWidget *p_widget, gpointer user_data);
void cb_create_entry1(GtkWidget *p_widget, gpointer user_data);
void cb_clicSurPlus(GtkWidget * widget, gpointer data);
void cb_recherchePatient(GtkWidget * widget, gpointer data);
void cb_creationPatient(GtkWidget * widget, gpointer data);
void cb_creationRDV(GtkWidget * widget, gpointer data);
void cb_rechercheProjet(GtkWidget * widget, gpointer data);
void enter_callback( GtkWidget *widget, GtkWidget *entry);
void closeTest(GtkWidget * widget, gpointer data);
void cb_create_entry2(void);
void cb_newProject(GtkWidget * widget, gpointer data);
void cb_creerProjet(GtkWidget * widget, gpointer data);
void cb_end( GtkWidget *widget, gpointer data);
void cb_non_sauvegarde( GtkWidget *widget, gpointer data);
void cb_sauvegarde( GtkWidget *widget, gpointer data);
void cb_creationMedecin(GtkWidget * widget, gpointer data);
void cb_plusMedecin(GtkWidget * widget, gpointer data);
void afficherMedecins(GtkWidget * widget, gpointer data);
void cb_affichageInfosMedecin(GtkWidget * widget, gpointer data);
void afficherPatients(GtkWidget * widget, gpointer data);
void cb_affichageInfosPatient(GtkWidget * widget, gpointer data);

#endif
