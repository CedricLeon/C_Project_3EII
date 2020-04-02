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
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    ListMedecin_setOnFirst(((Patient *) *state)->medecins_consultes);
    assert_ptr_equal(ListMedecin_getCurrent(((Patient *) *state)->medecins_consultes), m);

    DeleteMedecin(m);
}
/**
 * On test si il ne se passe rien car le mèdein a déjà été ajouté
 * @param state
 */
static void testPatient_AddMedecinPatient_handlesMedecinDejaConsulte(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    AddMedecinConsultePatient((Patient *) *state, m);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 0);

    DeleteMedecin(m);
}
static void testPatient_DeleteMedecinPatient_handlesMedecinsEnleve(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    DeleteMedecinConsultePatient((Patient *) *state, m);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 0);

    DeleteMedecin(m);
}
static void testPatient_DeleteMedecinPatient_handlesPasDeMedecin(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m),0);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 0);

    DeleteMedecin(m);
}
static void testPatient_DeleteMedecinPatient_handlesMedecinNonPresent(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m),0);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->medecins_consultes), 0);

    DeleteMedecin(m);
}

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
    return cmocka_run_group_tests(tests_fonctionsPatient, setup_Patient, teardown_Patient);
}