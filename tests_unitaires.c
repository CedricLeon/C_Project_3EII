/*tests_unitaires.h n'a pas d'utilité puique les seules fonctions présentes ici sont static*/

/*Header Files du Projet*/
#include "medecin.h"
#include "patient.h"
#include "date.h"
#include "calendrier.h"
#include "ordonnance.h"
#include "dossier_medical.h"
#include "rendezvous.h"

/*Librairies nécessaire à CMocka*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*Librairies standart de C*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************************************************************/
                                    /*Tests des fonctions Patient*/
/**********************************************************************************************************************/

//Fonctions de setup et teardown de la structure Patient
static int setup_Patient(void ** state){
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP");
    *state = p;
    return *state == NULL;
}

static int teardown_Patient(void ** state){
    DeletePatient((Patient *) *state);
    return 0;
}

static void testPatient_creerPatient(void ** state){
    assert_string_equal(((Patient *) *state)->nom,"NomTestP");
    assert_string_equal(((Patient *) *state)->prenom,"PrenomTestP");
    assert_int_equal(((Patient *) *state)->date_naissance->annee,2020);
    assert_int_equal(((Patient *) *state)->date_naissance->mois, 03);
    assert_int_equal(((Patient *) *state)->date_naissance->jour, 29);
    assert_string_equal(((Patient *) *state)->adresse_mail, "test@adresseMailP");
    assert_string_equal(((Patient *) *state)->numero_telephone,"testNumeroTelephoneP");
}
//no need testfonction pour deletePatient

//static void testPatient_inscriptionPatient(void ** state);    Pour plus tard

static void testPatient_setNomPatient(void ** state){
    SetNomPatient(((Patient *) *state),"NewNom");
    assert_string_equal(((Patient *) *state)->nom,"NewNom");
}
static void testPatient_setPrenomPatient(void ** state){
    SetPrenomPatient(((Patient *) *state),"NewPrenom");
    assert_string_equal(((Patient *) *state)->prenom,"NewPrenom");
}
static void testPatient_setDateNaissancePatient(void ** state){
    SetDateNaissancePatient(((Patient *) *state),1,1,1);
    assert_int_equal(((Patient *) *state)->date_naissance->jour,1);
    assert_int_equal(((Patient *) *state)->date_naissance->mois,1);
    assert_int_equal(((Patient *) *state)->date_naissance->annee,1);
}
static void testPatient_setAdresseMailPatient(void ** state){
    SetAdresseMailPatient(((Patient *) *state),"NewMail");
    assert_string_equal(((Patient *) *state)->adresse_mail,"NewMail");
}
static void testPatient_setNumeroTelephonePatient(void ** state){
    SetNumeroTelephonePatient(((Patient *) *state),"NewTel");
    assert_string_equal(((Patient *) *state)->numero_telephone,"NewTel");
}
/**
 * On test si le mèdecin est bien ajouté
 * @param state
 */
static void testPatient_AddMedecinPatient_handlesMedecinAdded(void ** state){
    printf("\n");
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    ListMedecin_setOnFirst(((Patient *) *state)->medecins_consultes);
    assert_ptr_equal(ListMedecin_getCurrent(((Patient *) *state)->medecins_consultes), m);

    DeleteMedecinConsultePatient((Patient *) *state, m);
    DeleteMedecin(m);
    printf("\n");
}
/**
 * On test si il ne se passe rien car le mèdecin a déjà été ajouté
 * @param state
 */
static void testPatient_AddMedecinPatient_handlesMedecinDejaConsulte(void ** state){
    printf("\n");
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    assert_int_equal(AddMedecinConsultePatient((Patient *) *state, m), 1);                  //Should print "medecin add au debut de la liste"
    assert_int_equal(AddMedecinConsultePatient((Patient *) *state, m), 0);                  //Should print "cant add, deja consulté"
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 0);     //test par principe mais pas très utile

    DeleteMedecinConsultePatient((Patient *) *state, m);
    DeleteMedecin(m);
    printf("\n");
}
/**
 * On test si le delete de medecin est bien enlevé de la liste
 * @param state
 */
static void testPatient_DeleteMedecinPatient_handlesMedecinsEnleve(void ** state){
    printf("\n");
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m), 1);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 1);

    DeleteMedecin(m);
    printf("\n");
}
/**
 * On test si on essaye d'enlever un medecin d'une liste vide
 * @param state
 */
static void testPatient_DeleteMedecinPatient_handlesPasDeMedecin(void ** state){
    printf("\n");
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m),0);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 1);

    DeleteMedecin(m);
    printf("\n");
}
/**
 * On test d'enlever un medecin non présent dans la liste
 * @param state
 */
static void testPatient_DeleteMedecinPatient_handlesMedecinNonPresent(void ** state){
    printf("\n");
    Medecin * m1 = CreerMedecin("NomTestM1", "PrenomTestM1", "test@adresseMailM1", "testNumeroTelephoneM1", "NumRPSM1");
    Medecin * m2 = CreerMedecin("NomTestM2", "PrenomTestM2", "test@adresseMailM2", "testNumeroTelephoneM2", "NumRPSM2");

    AddMedecinConsultePatient((Patient *) *state, m1);
    //On add pas m2 et on essaye de le delete

    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m2),0);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 0);

    DeleteMedecin(m1);
    DeleteMedecin(m2);
    printf("\n");
}

/**********************************************************************************************************************/
                                        /*Tests des fonctions Medecin*/
/**********************************************************************************************************************/


//Fonctions de setup et teardown de la structure Medecin
static int setup_Medecin(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");
    *state = m;
    return *state == NULL;
}

static int teardown_Medecin(void ** state){
    DeleteMedecin((Medecin *) *state);
    return 0;
}

/**
 * On test de créer un Mèdecin
 * @param state
 */
static void testMedecin_creerMedecin(void ** state){                            //Pour le principe car ne peut pas fail
    assert_string_equal(((Medecin *) *state)->nom,"NomTestM");
    assert_string_equal(((Medecin *) *state)->prenom,"PrenomTestM");
    assert_string_equal(((Medecin *) *state)->adresse_mail, "test@adresseMailM");
    assert_string_equal(((Medecin *) *state)->numero_telephone,"testNumeroTelephoneM");
    assert_string_equal(((Medecin *) *state)->numero_RPS, "NumRPSM");
}
/**
 * On test 
 * @param state
 */
static void testMedecin_AddPatientRecuMedecin_handlesPatientAdded(void ** state){
    printf("\n");
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP");

    AddPatientRecuMedecin((Medecin *) *state, p);
    ListPatient_setOnFirst(((Medecin *) *state)->patients_recus);
    assert_ptr_equal(ListPatient_getCurrent(((Medecin *) *state)->patients_recus), p);

    DeletePatientRecuMedecin((Medecin *) *state, p);
    DeletePatient(p);
    printf("\n");
}
/**
 * On test si il ne se passe rien car le mèdecin a déjà été ajouté
 * @param state
 */
static void testMedecin_AddPatientRecuMedecin_handlesPatientDejaRecu(void ** state){
    printf("\n");
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP");

    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 1);                  //Should print "patient add au debut de la liste"
    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 0);                  //Should print "cant add, deja consulté"
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 0);     //test par principe mais pas très utile

    DeletePatientRecuMedecin((Medecin *) *state, p);
    DeletePatient(p);
    printf("\n");
}
static void testMedecin_DeletePatientRecuMedecint_handlesPatientEnleve(void ** state){
    //ce test est aussi là pour le principe puique dans les faits on est obligé
    // d'enlever le patient de la liste déjà dans le 1er test car les tests sont appellés à la suite
    printf("\n");
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP");

    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 1);
    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p), 1);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 1);

    DeletePatient(p);
    printf("\n");
}
static void testMedecin_DeletePatientRecuMedecin_handlesPasDePatient(void ** state){
    printf("\n");
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP");

    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p),0);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 1);

    DeletePatient(p);
    printf("\n");
}
static void testMedecin_DeletePatientRecuMedecin_handlesPatientNonPresent(void ** state){
    printf("\n");
    Patient * p1 = CreerPatient("NomTestP1", "PrenomTestP1", 20201, 031, 291, "test@adresseMailP1", "testNumeroTelephoneP2");
    Patient * p2 = CreerPatient("NomTestP2", "PrenomTestP2", 20202, 032, 292, "test@adresseMailP2", "testNumeroTelephoneP2");

    AddPatientRecuMedecin((Medecin *) *state, p1);
    //On add pas p2 et on essaye de le delete

    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p2),0);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 0);

    DeletePatient(p1);
    DeletePatient(p2);
    printf("\n");
}

/**********************************************************************************************************************/
                                            /*Main : Appel des Test*/
/**********************************************************************************************************************/

int main(void){
    const struct CMUnitTest tests_fonctionsPatient[] = {

            //tests des fonctions de création d'instances
            cmocka_unit_test(testPatient_creerPatient),

            //tests des setteurs de la structure Patient    : un peu inutile
            cmocka_unit_test(testPatient_setNomPatient),
            cmocka_unit_test(testPatient_setPrenomPatient),
            cmocka_unit_test(testPatient_setDateNaissancePatient),
            cmocka_unit_test(testPatient_setNumeroTelephonePatient),

            //Tests des fonctions d'ajout et de delte de medecins à la liste de mèdecins consultés par le patient
            cmocka_unit_test(testPatient_AddMedecinPatient_handlesMedecinAdded),
            cmocka_unit_test(testPatient_AddMedecinPatient_handlesMedecinDejaConsulte),
            cmocka_unit_test(testPatient_DeleteMedecinPatient_handlesMedecinsEnleve),
            cmocka_unit_test(testPatient_DeleteMedecinPatient_handlesPasDeMedecin),
            cmocka_unit_test(testPatient_DeleteMedecinPatient_handlesMedecinNonPresent),
    };

    const struct CMUnitTest tests_fonctionsMedecin[] = {
            cmocka_unit_test(testMedecin_creerMedecin),
            cmocka_unit_test(testMedecin_AddPatientRecuMedecin_handlesPatientAdded),
            cmocka_unit_test(testMedecin_AddPatientRecuMedecin_handlesPatientDejaRecu),
            cmocka_unit_test(testMedecin_DeletePatientRecuMedecint_handlesPatientEnleve),
            cmocka_unit_test(testMedecin_DeletePatientRecuMedecin_handlesPasDePatient),
            cmocka_unit_test(testMedecin_DeletePatientRecuMedecin_handlesPatientNonPresent),
    };

    printf("\033[34;01m\n****************************** Running Patient Tests ******************************\n\n\033[00m");
    int return_cmocka_P = cmocka_run_group_tests(tests_fonctionsPatient, setup_Patient, teardown_Patient);
    printf("\033[34;01m\n****************************** Running Medecin Tests ******************************\n\n\033[00m");
    int return_cmocka_M = cmocka_run_group_tests(tests_fonctionsMedecin, setup_Medecin, teardown_Medecin);

    //Appeler plusieurs cmocka_run_group_tests() dans le return ne marche pas, il execute seulement le premier donc je passe par des int temporaires
    return  return_cmocka_P && return_cmocka_M;
}