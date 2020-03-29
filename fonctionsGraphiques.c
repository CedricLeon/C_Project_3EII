#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsGraphiques.h"
#include "callbacks.h"


void boutonRDV(GtkWidget *wid, GtkGrid grid)
{
  GtkWidget *dialog = NULL;
  dialog = gtk_message_dialog_new (GTK_WINDOW (wid), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

int create_window(int argc, char *argv[]){

   /* Variables */
   GtkGrid *p_grid = NULL;
   GtkWidget *p_window = NULL;
   GtkWidget *p_main_box = NULL;
   GtkWidget *p_button[100];

   /* Initialisation GTK+ */
   gtk_init (&argc, &argv);

   /* Création de la fenêtre principale */
   p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

   gtk_window_set_title(GTK_WINDOW(p_window), "Calendrier");
   gtk_window_resize (GTK_WINDOW(p_window), 1600, 900);                         /*possibilité d'utiliser également la taille par défaut*/
   gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_CENTER);
   gtk_widget_realize (p_window);
   g_signal_connect(G_OBJECT(p_window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

  /* p_main_box = gtk_vbox_new(TRUE, 0);
   gtk_container_add(GTK_CONTAINER(p_window), p_main_box);*/


  /* Création de la grille */

  p_grid = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER (p_window), p_grid);
  gtk_grid_set_column_spacing(p_grid, 1);

  /*Ajout des jours de la semaine */

  gtk_grid_attach (p_grid, gtk_label_new("Lundi"), 0, 0, 100, 100);
  gtk_grid_attach (p_grid, gtk_label_new("Mardi"), 500, 0, 100, 100);
  gtk_grid_attach (p_grid, gtk_label_new("Mercredi"),1000 , 0, 100, 100);
  gtk_grid_attach (p_grid, gtk_label_new("Jeudi"), 1500, 0, 100, 100);
  gtk_grid_attach (p_grid, gtk_label_new("Vendredi"), 2000, 0, 100, 100);
  gtk_grid_attach (p_grid, gtk_label_new("Samedi"), 2500, 0, 100, 100);


    /* Ajout de boutons sur la grille de manière arbitraire (coordonnées)
 (j'ai l'impression que c'est par rapport au 1er widget sur la grille, et j'ai pas tout compris aux coordonnées, reste à creuser)*/


  /*Rendez-vous 1*/
    p_button[0] = gtk_button_new_with_label("Rendez-vous 1");
    gtk_grid_attach (p_grid, p_button[0], 500, 700, 100, 100);
   g_signal_connect(G_OBJECT(p_button[0]), "clicked", G_CALLBACK(cb_create_entry), NULL);
   /*gtk_box_pack_start(GTK_BOX(p_main_box), p_button[0], FALSE, FALSE, 0);*/

   p_button[1] = gtk_button_new_with_label("Rendez-vous 2");
   gtk_grid_attach(p_grid, p_button[0], 500,1000, 100,100);
   g_signal_connect(G_OBJECT(p_button[1]), "clicked", G_CALLBACK(cb_create_entry), NULL);
   /*gtk_box_pack_start(GTK_BOX(p_main_box), p_button[0], FALSE, FALSE, 0);*/


   gtk_widget_show_all(p_window);
}
