/*!
* \file fonctionsGraphiques.h
* \brief Provides basic unit testing functions declaration
*/

#ifndef TIME_GPCALENDAR_H
#define TIME_GPCALENDAR_H
#include "GPCalendar/Model/project_GPCalendar.h"
#include "GPCalendar/View/fonctionsGraphiques.h"
#include "GPCalendar/View/callbacks.h"
#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/calendrier.h"
#include "GPCalendar/Model/dossier_medical.h"
#include <gtk/gtk.h>
//#include <time.h>
#include <stdlib.h>
#include <stdio.h>



Project_GPCalendar * initProjet();
void create_calendar(GtkWidget* widget, gpointer data);



#endif
