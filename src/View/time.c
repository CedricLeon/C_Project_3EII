#include "GPCalendar/View/time.h"


#define DEF_PAD 50
#define DEF_PAD_SMALL 5

#define TM_YEAR_BASE 1900

typedef struct _CalendarData {
  GtkWidget *window;
  GtkWidget *prev_sig;
  GtkWidget *last_sig;
  GtkWidget *month;
} CalendarData;

char* nomFichier;


//Project* projet=GPCalendar_loadProject(nomFichier);

/** POUR GERER INT DANS LES PARAM NUM: faire boucle de 0 à 12 pour num secu, 0à 9 pour numTel if(((gtk_entry_get_text(GTK_ENTRY(widget)))[0]>=48) && (gtk_entry_get_text(GTK_ENTRY(widget))[0]<=57))**/

/** Calendrier médecin **/



static void calendar_date_to_string( CalendarData *data, char *buffer, gint bufferSize )
{
  GDate date;
  guint year, month, day;

  gtk_calendar_get_date (GTK_CALENDAR (data->window),&year, &month, &day);             //Obtains the selected date from a GtkCalendar
  g_date_set_dmy (&date, day, month + 1, year);                                        //Sets the value of a GDate (here &date) from a day, month, and year
  g_date_strftime (buffer, bufferSize - 1, "%x", &date);                               //Generates a printed representation of the date, in a locale-specific way: %x for 00/00/0000 format

}

static void calendar_set_signal_strings( char *signalString,CalendarData *data )
{
  const gchar *previousSignal;

  previousSignal = gtk_label_get_text (GTK_LABEL (data->last_sig));                           //Fetches the text from a label widget
  gtk_label_set_text (GTK_LABEL (data->last_sig), signalString);                             //Sets the text within the GtkLabel widget
}

static void calendar_month_changed( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "month_changed: ";

  calendar_date_to_string (data, buffer + 15, 256 - 15);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_day_selected( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "day_selected: ";

  calendar_date_to_string (data, buffer + 14, 256 - 14);
  calendar_set_signal_strings (buffer, data);
}


static void calendar_prev_month( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "prev_month: ";

  calendar_date_to_string (data, buffer + 12, 256 - 12);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_next_month( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "next_month: ";

  calendar_date_to_string (data, buffer + 12, 256 - 12);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_prev_year( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "prev_year: ";

  calendar_date_to_string (data, buffer + 11, 256 - 11);
  calendar_set_signal_strings (buffer, data);
}

static void calendar_next_year( GtkWidget *widget, CalendarData *data )
{
  char buffer[256] = "next_year: ";

  calendar_date_to_string (data, buffer + 11, 256 - 11);
  calendar_set_signal_strings (buffer, data);
}

/**create Calendar function**/

void create_calendar()
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



  calendar_data.window = NULL;


  /*generates calendar window */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Calendrier médecin n°1");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);


  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit),NULL);
  g_signal_connect (window, "delete-event", gtk_false, NULL);
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
  g_signal_connect (calendar, "prev_month", G_CALLBACK (calendar_prev_month), &calendar_data);
  g_signal_connect (calendar, "next_month", G_CALLBACK (calendar_next_month), &calendar_data);
  g_signal_connect (calendar, "prev_year", G_CALLBACK (calendar_prev_year), &calendar_data);
  g_signal_connect (calendar, "next_year",G_CALLBACK (calendar_next_year),&calendar_data);
  g_signal_connect(calendar, "day_selected", G_CALLBACK(cb_create_entry1), NULL);               //opens a new window when the day is selected

  separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
  gtk_box_pack_start (GTK_BOX (hbox), separator, FALSE, TRUE, 0);


  /* Build the Right frame with the flags in */

  vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, DEF_PAD);
  vbox3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 100);
  gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, DEF_PAD);

  frame = gtk_frame_new ("Recherche Rendez-vous\n");

  gtk_box_pack_start (GTK_BOX (vbox2), frame, TRUE, TRUE, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (frame), vbox3);


  /* Build the plus button */

    GtkWidget * plusRDV = gtk_button_new_with_label("+");
    gtk_box_pack_start(GTK_BOX(vbox3), plusRDV, FALSE, FALSE, 0);
    gtk_widget_set_size_request(plusRDV, 50, 50);

    g_signal_connect(G_OBJECT(plusRDV), "clicked", G_CALLBACK(cb_clicSurPlus), NULL);       //opens a new window when the button is pressed
    gtk_box_pack_start (GTK_BOX (vbox2), plusRDV, FALSE, FALSE, 0);

  /*Build button test fentre creer rdv*/
    GtkWidget * testButton = gtk_button_new_with_label("Test");
    gtk_box_pack_start(GTK_BOX(vbox3), testButton, FALSE, FALSE, 0);
    gtk_widget_set_size_request(testButton, 20, 20);

    g_signal_connect(G_OBJECT(testButton),"clicked", G_CALLBACK(fenetreCreerRDV), NULL);       //opens a new window when the button is pressed
    gtk_box_pack_start (GTK_BOX (vbox2), testButton, FALSE, FALSE, 0);





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
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit),NULL);
  gtk_container_add (GTK_CONTAINER (bbox), button);


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


