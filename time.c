#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"
#include "time.h"
#include "fonctionsGraphiques.h"

#define DEF_PAD 50
#define DEF_PAD_SMALL 5

#define TM_YEAR_BASE 1900

typedef struct _CalendarData {
  GtkWidget *flag_checkboxes[5];
  gboolean  settings[5];
  GtkWidget *font_dialog;
  GtkWidget *window;
  GtkWidget *prev2_sig;
  GtkWidget *prev_sig;
  GtkWidget *last_sig;
  GtkWidget *month;
} CalendarData;

enum {
  calendar_show_header,
  calendar_show_days,
  calendar_month_change,
  calendar_show_week,
  calendar_monday_first
};

/*
 * GtkCalendar
 */

static void calendar_date_to_string( CalendarData *data, char *buffer, gint buff_len )
{
  GDate date;
  guint year, month, day;

  gtk_calendar_get_date (GTK_CALENDAR (data->window),&year, &month, &day);
  g_date_set_dmy (&date, day, month + 1, year);
  g_date_strftime (buffer, buff_len - 1, "%x", &date);

}

static void calendar_set_signal_strings( char *sig_str,CalendarData *data )
{
  const gchar *prev_sig;

  /*prev_sig = gtk_label_get_text (GTK_LABEL (data->prev_sig));
  gtk_label_set_text (GTK_LABEL (data->prev2_sig), prev_sig);*/

  prev_sig = gtk_label_get_text (GTK_LABEL (data->last_sig));
  //gtk_label_set_text (GTK_LABEL (data->prev_sig), prev_sig);
  gtk_label_set_text (GTK_LABEL (data->last_sig), sig_str);
}

static void calendar_month_changed( GtkWidget    *widget,
                                    CalendarData *data )
{
  char buffer[256] = "month_changed: ";

  calendar_date_to_string (data, buffer + 15, 256 - 15);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_day_selected( GtkWidget    *widget,
                                   CalendarData *data )
{
  char buffer[256] = "day_selected: ";

  calendar_date_to_string (data, buffer + 14, 256 - 14);
  calendar_set_signal_strings (buffer, data);
}


static void calendar_prev_month( GtkWidget    *widget,
                                 CalendarData *data )
{
  char buffer[256] = "prev_month: ";

  calendar_date_to_string (data, buffer + 12, 256 - 12);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_next_month( GtkWidget    *widget,
                                 CalendarData *data )
{
  char buffer[256] = "next_month: ";

  calendar_date_to_string (data, buffer + 12, 256 - 12);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_prev_year( GtkWidget    *widget,
                                CalendarData *data )
{
  char buffer[256] = "prev_year: ";

  calendar_date_to_string (data, buffer + 11, 256 - 11);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_next_year( GtkWidget    *widget,
                                CalendarData *data )
{
  char buffer[256] = "next_year: ";

  calendar_date_to_string (data, buffer + 11, 256 - 11);
  calendar_set_signal_strings (buffer, data);
}


void create_calendar()
{
  GtkWidget *window;
  GtkWidget *vbox, *vbox2, *vbox3;
  GtkWidget *hbox;
  GtkWidget *hbbox;
  GtkWidget *calendar;
  GtkWidget *toggle;
  GtkWidget *button;
  GtkWidget *frame;
  GtkWidget *separator;
  GtkWidget *label;
  GtkWidget *bbox;
  static CalendarData calendar_data;
  gint i;



  calendar_data.window = NULL;


  for (i = 0; i < 5; i++) {
    calendar_data.settings[i] = 0;
  }

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Calendrier médecin n°1");
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit),NULL);
  g_signal_connect (window, "delete-event", G_CALLBACK (gtk_false), NULL);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

  vbox = gtk_vbox_new (FALSE, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  /*
   * The top part of the window, Calendar, flags and fontsel.
   */

  hbox = gtk_hbox_new (FALSE, DEF_PAD);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, DEF_PAD);
  hbbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (hbox), hbbox, FALSE, FALSE, DEF_PAD);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbbox), GTK_BUTTONBOX_SPREAD);
  gtk_box_set_spacing (GTK_BOX (hbbox), 5);

  /* Calendar widget */
  frame = gtk_frame_new ("Calendrier");
  gtk_box_pack_start(GTK_BOX (hbbox), frame, FALSE, TRUE, DEF_PAD);
  calendar=gtk_calendar_new ();
  calendar_data.window = calendar;
  gtk_calendar_set_detail_height_rows (calendar,127);
  gtk_calendar_set_detail_width_chars (calendar,127);

//  calendar_set_flags (&calendar_data);
  gtk_calendar_mark_day (GTK_CALENDAR (calendar), 19);
  gtk_container_add (GTK_CONTAINER (frame), calendar);
  g_signal_connect (calendar, "month_changed",
		    G_CALLBACK (calendar_month_changed),
		    &calendar_data);
  g_signal_connect (calendar, "day_selected",
		    G_CALLBACK (calendar_day_selected),
		    &calendar_data);

  g_signal_connect (calendar, "prev_month",
		    G_CALLBACK (calendar_prev_month),
		    &calendar_data);
  g_signal_connect (calendar, "next_month",
		    G_CALLBACK (calendar_next_month),
		    &calendar_data);
  g_signal_connect (calendar, "prev_year",
		    G_CALLBACK (calendar_prev_year),
		    &calendar_data);
  g_signal_connect (calendar, "next_year",G_CALLBACK (calendar_next_year),&calendar_data);

  g_signal_connect(calendar, "day_selected", G_CALLBACK(cb_create_entry1), NULL);

  separator = gtk_vseparator_new ();
  gtk_box_pack_start (GTK_BOX (hbox), separator, FALSE, TRUE, 0);

  vbox2 = gtk_vbox_new (FALSE, DEF_PAD);
  gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, DEF_PAD);

  /* Build the Right frame with the flags in */

  frame = gtk_frame_new ("Recherche Rendez-vous");
  gtk_box_pack_start (GTK_BOX (vbox2), frame, TRUE, TRUE, DEF_PAD);
  vbox3 = gtk_vbox_new (TRUE, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (frame), vbox3);


  /* Build the right font-button */
 // button = gtk_button_new_with_label ("Font...");
 /* g_signal_connect (button,
		    "clicked",
		    G_CALLBACK (calendar_select_font),
		    &calendar_data);*/
  gtk_box_pack_start (GTK_BOX (vbox2), button, FALSE, FALSE, 0);

  /*
   *  Build the Signal-event part.
   */

  frame = gtk_frame_new ("Affichage");
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, DEF_PAD);

  vbox2 = gtk_vbox_new (TRUE, DEF_PAD_SMALL);
  gtk_container_add (GTK_CONTAINER (frame), vbox2);

  hbox = gtk_hbox_new (FALSE, 3);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox, FALSE, TRUE, 0);
  label = gtk_label_new ("-->");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
  calendar_data.last_sig = gtk_label_new ("");
  gtk_box_pack_start (GTK_BOX (hbox), calendar_data.last_sig, FALSE, TRUE, 0);


  bbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (vbox), bbox, FALSE, FALSE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), GTK_BUTTONBOX_END);

  /*button = gtk_button_new_with_label ("Close");
  g_signal_connect (button, "clicked",
		    G_CALLBACK (gtk_main_quit),
		    NULL);
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_widget_set_can_default (button, TRUE);
  gtk_widget_grab_default (button);*/

  gtk_widget_show_all (window);}


/*typedef struct{
    char* nom;
    int date;
    struct NodeJour* next;
    struct NodeJour* previous;
}Jour;*/

/*void JourCourantNom(char* result){

    time_t t;

   /* Retrieve the current time */
    //t = time(NULL);

   /* Output the current day into the result string */
   // strftime(result,10,"%A", localtime(&t));

//}

/*void JourCourantDate(char* result){

    time_t t;

   /* Retrieve the current time */
  //  t = time(NULL);

   /* Output the current day into the result string */
   /* strftime(result,10,"%d", localtime(&t));
}*/

/*void trouverDate(char* dateNo, char* date,char* currentDayDate,char* currentDayName){
    char* Monday=(char*)malloc(10*sizeof(char));
    Monday="Monday";
    char* Tuesday=(char*)malloc(10*sizeof(char));
    Tuesday="Tuesday";
    char* Wednesday=(char*)malloc(10*sizeof(char));
    Wednesday="Wednesday";
    char* Thursday=(char*)malloc(10*sizeof(char));
    Thursday="Thursday";
    char* Friday=(char*)malloc(10*sizeof(char));
    Friday="Friday";
    char* Saturday=(char*)malloc(10*sizeof(char));
    Saturday="Saturday";
    char* Sunday=(char*)malloc(10*sizeof(char));
    Sunday="Sunday";

    int compare0=strcmp(Monday,currentDayName);
    int compare1=strcmp(Tuesday,currentDayName);
    int compare2=strcmp(Wednesday,currentDayName);
    int compare3=strcmp(Thursday,currentDayName);
    int compare4=strcmp(Friday,currentDayName);
    int compare5=strcmp(Saturday,currentDayName);
    int compare6=strcmp(Sunday,currentDayName);


    if (compare0==0){
        date=curentDayDate;

    }else if{


    }*/



