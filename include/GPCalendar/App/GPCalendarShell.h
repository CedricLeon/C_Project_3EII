#ifndef GPCALENDAR_GPCALENDARSHELL_H
#define GPCALENDAR_GPCALENDARSHELL_H

//Header du projet
#include "GPCalendar/Model/project_GPCalendar.h"
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

//Define size of buffer
#define MAX_ORDO_DESCRIPTION_SIZE 1000
#define MAX_ANTECEDENT_SIZE 1000


//Fonctions de print
void printPossibleAction();
void checkHelpDisplayAction(char* ask);

//Fonctions pour les actions choisies
void Shell_creerPatient(Project_GPCalendar* project);
void Shell_creerMedecin(Project_GPCalendar* project);
void Shell_creerRendezVous(Project_GPCalendar* project);
void Shell_consulterInformations(Project_GPCalendar* project);
void Shell_modifierInformations(Project_GPCalendar* project);
void Shell_modifierPatient(Project_GPCalendar* project);
void Shell_modifierMedecin(Project_GPCalendar* project);
void Shell_modifierRendezVous(Project_GPCalendar* project);
void Shell_modifierOrdonnance(Project_GPCalendar* project);
void Shell_annulerRendezVous(Project_GPCalendar* project);
void Shell_supprimerPatient(Project_GPCalendar* project);
void Shell_supprimerMedecin(Project_GPCalendar* project);


#endif //GPCALENDAR_GPCALENDARSHELL_H
