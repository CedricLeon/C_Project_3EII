#include <stdlib.h>
#include <gtk/gtk.h>


int main (int argc, char *argv[])
{


    /* Variables */
  GtkWidget *button = NULL;
  GtkWidget *mainWindow = NULL;
  GtkWidget *vbox = NULL;

  /* Initialisation GTK+ */
  gtk_init (&argc, &argv);


  /* Création de la fenêtre principale */
  mainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  /*gtk_window_set_frame_dimensions (GTK_WINDOW(mainWindow), 8, 8, 8, 8);  => ne marche plus je n'ai pas trouvé d'équivalent*/

  gtk_window_set_title (GTK_WINDOW (mainWindow), "Calendrier");
  gtk_window_set_position (GTK_WINDOW (mainWindow), GTK_WIN_POS_CENTER);
  gtk_window_resize (GTK_WINDOW(mainWindow), 1600, 900);                       /*possibilité d'utiliser également la taille par défaut*/
  gtk_widget_realize (mainWindow);
  g_signal_connect(G_OBJECT(mainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);


  /* Enter the main loop */
  gtk_widget_show_all (mainWindow);
  gtk_main ();
  return EXIT_SUCCESS;
}
