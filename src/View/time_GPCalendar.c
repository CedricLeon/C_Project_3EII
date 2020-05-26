#include "GPCalendar/View/time_GPCalendar.h"


#define DEF_PAD 50
#define DEF_PAD_SMALL 5

#define TM_YEAR_BASE 1900


/**
 * calendar_set_signal_strings : fonction static permettant de stocker dans une chaîne de caractère le texte récupéré du last_sig de la data passée en parmaètre
 * @param signalString : chaîne de caractères permettant le stockage du signal
 * @param data : les informations transmises par la structure CalendarData
 */
static void calendar_set_signal_strings( char *signalString,CalendarData *data )
{
  const gchar *previousSignal;

  previousSignal = gtk_label_get_text (GTK_LABEL (data->last_sig));                           //Fetches the text from a label widget
  gtk_label_set_text (GTK_LABEL (data->last_sig), signalString);                             //Sets the text within the GtkLabel widget
}

/**
 * calendar_month_changed : fonction static permettant de stocker dans une chaîne de caractère la date récupéré si le mois change
 * @param widget : le widget associé, ici inutile
 * @param data : les informations transmises par la structure CalendarData
 */
static void calendar_month_changed( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "month_changed: ";

  calendar_date_to_string (data, buffer + 15, 256 - 15);
  calendar_set_signal_strings (buffer, data);
}

/**
 * calendar_day_selected : fonction static permettant de stocker dans une chaîne de caractère la date selectionnée
 * @param widget : le widget associé, ici inutile
 * @param data : les informations transmises par la structure CalendarData
 */
static void calendar_day_selected( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "day_selected: ";

  calendar_date_to_string (data, buffer + 14, 256 - 14);
  calendar_set_signal_strings (buffer, data);
}



/**
 * create_calendar: fonction permettant de créer notre calendrier
 * @param widget : le widget associé à l'ouverture de la fonction
 * @param data : les informations transmises par la structure CalendarData
 */
void create_calendar(GtkWidget* widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *vbox, *vbox2, *vbox3;
  GtkWidget *hbox;
  GtkWidget *hbbox;
  GtkWidget *calendar;
  GtkWidget *button;
  GtkWidget *frame;
  GtkWidget *separator;
  GtkWidget *label;
  GtkWidget *bbox;
  static CalendarData calendar_data;
  gint i;
  Project_GPCalendar * projet = ((struct RechercheProjet *)data)->project;
  struct DateCalendrier * donnees;
  donnees = (struct DateCalendrier *)malloc(sizeof(struct DateCalendrier*));
  donnees->calendar = &calendar_data;
  donnees->projet = projet;

  calendar_data.window = NULL;


  /*generate calendar window */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_title (GTK_WINDOW (window), "Calendrier");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);


  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit),NULL);
  g_signal_connect (window, "delete-event",  G_CALLBACK (gtk_false), NULL);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);                        //so that the user can not resize this window

    /*generates the box to place the window*/

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  /* generates the part of the window, Calendar, and plus button */

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, DEF_PAD);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, DEF_PAD);
  hbbox = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (hbox), hbbox, FALSE, FALSE, DEF_PAD);
  gtk_box_set_spacing (GTK_BOX (hbbox), 2);

  /* Calendar widgets , day selected and plus button */

  frame = gtk_frame_new ("Calendrier");
  gtk_box_pack_start(GTK_BOX (hbbox), frame, FALSE, TRUE, DEF_PAD);
  calendar=gtk_calendar_new ();
  calendar_data.window = calendar;

  gtk_calendar_mark_day (GTK_CALENDAR (calendar), 1);                  //Places a visual marker on a particular day here show where the month start
  gtk_container_add (GTK_CONTAINER (frame), calendar);

  /*connects the changing days,months, years to the calendar*/

  g_signal_connect (calendar, "month_changed", G_CALLBACK (calendar_month_changed), &calendar_data);
  g_signal_connect (calendar, "day_selected", G_CALLBACK (calendar_day_selected), &calendar_data);
  g_signal_connect(calendar, "day_selected", G_CALLBACK(cb_create_entry1), donnees );               //opens a new window when the day is selected

  separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
  gtk_box_pack_start (GTK_BOX (hbox), separator, FALSE, TRUE, 0);


  /* Build the Right frame with the flags in */

  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, DEF_PAD);
  vbox3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, DEF_PAD);

  frame = gtk_frame_new ("Actions :\n");

  gtk_box_pack_start (GTK_BOX (vbox2), frame, TRUE, TRUE, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (frame), vbox3);


  /* Build the plus button */

    GtkWidget * plusRDV = gtk_button_new_with_label("Ajouter un rendez-vous");
    gtk_box_pack_start(GTK_BOX(vbox3), plusRDV, FALSE, FALSE, 0);
    gtk_widget_set_size_request(plusRDV, 50, 50);
    gtk_box_pack_start (GTK_BOX (vbox2), plusRDV, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(plusRDV), "clicked", G_CALLBACK(cb_clicSurPlus), projet);       //opens a new window when the button is pressed


    /* Ajout médecin */

    GtkWidget * plusMedecin = gtk_button_new_with_label("Ajouter un médecin");
    gtk_box_pack_start(GTK_BOX(vbox3), plusMedecin, FALSE, FALSE, 0);
    gtk_widget_set_size_request(plusRDV, 50, 50);
    g_signal_connect(G_OBJECT(plusMedecin), "clicked", G_CALLBACK(cb_plusMedecin), projet);

    /* Consulter médecins */

    GtkWidget * seeDocs = gtk_button_new_with_label("Consulter la liste des médecins");
    gtk_box_pack_start(GTK_BOX(vbox3), seeDocs, FALSE, FALSE, 0);
    gtk_widget_set_size_request(seeDocs, 50, 50);
    g_signal_connect(G_OBJECT(seeDocs), "clicked", G_CALLBACK(afficherMedecins), projet);

    /* Consulter patients */

    GtkWidget * seePatients = gtk_button_new_with_label("Consulter la liste des patients");
    gtk_box_pack_start(GTK_BOX(vbox3), seePatients, FALSE, FALSE, 0);
    gtk_widget_set_size_request(seePatients, 50, 50);
    g_signal_connect(G_OBJECT(seePatients), "clicked", G_CALLBACK(afficherPatients), projet);

  /*Show the day selected signals*/

  frame = gtk_frame_new ("Affichage");
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, DEF_PAD);

  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, DEF_PAD_SMALL);
  gtk_container_add (GTK_CONTAINER (frame), vbox2);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 3);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox, FALSE, TRUE, 0);

  label = gtk_label_new ("-->");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
  calendar_data.last_sig = gtk_label_new ("");
  gtk_box_pack_start (GTK_BOX (hbox), calendar_data.last_sig, FALSE, TRUE, 0);


  /*close button*/

  bbox = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (vbox), bbox, FALSE, FALSE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), GTK_BUTTONBOX_END);
  button = gtk_button_new_with_label ("Fermer");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  g_signal_connect (button, "clicked", G_CALLBACK (cb_end),donnees);



  gtk_widget_show_all (window);
  }



