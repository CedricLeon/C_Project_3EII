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
void Shell_creerPatient(Project* project);
void Shell_creerMedecin(Project* project);
void Shell_creerRendezVous(Project* project);
void Shell_consulterInformations(Project* project);
void Shell_annulerRendezVous(Project* project);
void Shell_supprimerPatient(Project* project);
void Shell_supprimerMedecin(Project* project);


#endif //GPCALENDAR_GPCALENDARSHELL_H
