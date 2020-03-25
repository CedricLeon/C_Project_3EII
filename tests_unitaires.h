#ifndef C_PROJECT_TESTS_UNITAIRES_H
#define C_PROJECT_TESTS_UNITAIRES_H

/*Header Files du Projet*/
#include "medecin.h"
#include "patient.h"
#include "date.h"
#include "calendrier.h"
#include "ordonnance.h"
#include "dossier_medical.h"
#include "rendezvous.h"

/*Librairies nécessaire à CMocka*/          //pas sûr d'en avoir besoin ici
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*Librairies standart de C*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Tests de la structure Patient */
static void testPatient_creerPatient(void ** state);
static void testPatient_deletePatient(void ** state);
//static void testPatient_inscriptionPatient(void ** state);

static void testPatient_setNomPatient(void ** state);
static void testPatient_setPrenomPatient(void ** state);
static void testPatient_setDateNaissancePatient(void ** state);
static void testPatient_setAdresseMailPatient(void ** state);
static void testPatient_setNumeroTelephonePatient(void ** state);

static void testPatient_InitMedecinConsultesPatient(void ** state);
static void testPatient_FreeMedecinsConsultesPatient(void ** state);

static void testPatient_AddMedecinPatient_handlesMedecinAdded(void ** state);
static void testPatient_AddMedecinPatient_handlesNbMaMedecinAtteient(void ** state);
static void testPatient_DeleteMedecinPatient_handlesMedecinsEnleve(void ** state);
static void testPatient_DeleteMedecinPatient_handlesPasDeMedecin(void ** state);
static void testPatient_DeleteMedecinPatient_handlesMedecinNonPresent(void ** state);


#endif //C_PROJECT_TESTS_UNITAIRES_H
