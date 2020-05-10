#ifndef GPCALENDAR_GPCALENDARSHELL_H
#define GPCALENDAR_GPCALENDARSHELL_H

//Header du projet
#include "GPCalendar/Model/JsonSave.h"
#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/calendrier.h"
#include "GPCalendar/Model/ordonnance.h"
#include "GPCalendar/Model/dossier_medical.h"
#include "GPCalendar/Model/rendezvous.h"

//Librairies Standarts
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Fonctions de print
void printPossibleAction();

//Fonctions pour les actions choisies
void Shell_creerPatient();
void Shell_creerMedecin();
void Shell_creerRendezVous();
void Shell_consulterInformations();
void Shell_annulerRendezVous();
void Shell_supprimerPatient();
void Shell_supprimerMedecin();
void Shell_saveProject();
void Shell_loadProject();


#endif //GPCALENDAR_GPCALENDARSHELL_H
