#include "tests_unitaires.h"

/*Tout les tests unitaires a la main*/
/* Cf Cmocka*/
/*Minis tests tous lancés à la fin dans un espèce de main*/

/*Compiler le tests_unitaires de Cmocka et vérifier que le bon résultat est attendu*/


/**********************************************************************************************************************/
                                    /*Tests des fonctions Patient*/
/**********************************************************************************************************************/

//static void testPatient_creerPatient(void ** state);
//static void testPatient_deletePatient(void ** state);
//static void testPatient_inscriptionPatient(void ** state);



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

static void testPatient_InitMedecinConsultesPatient(void ** state);
static void testPatient_FreeMedecinsConsultesPatient(void ** state);

static void testPatient_AddMedecinPatient_handlesMedecinAdded(void ** state);
static void testPatient_AddMedecinPatient_handlesNbMaMedecinAtteient(void ** state);
static void testPatient_DeleteMedecinPatient_handlesMedecinsEnleve(void ** state);
static void testPatient_DeleteMedecinPatient_handlesPasDeMedecin(void ** state);
static void testPatient_DeleteMedecinPatient_handlesMedecinNonPresent(void ** state);

//Fonctions de setup et teardown des setteurs de la structure Patient
static int setup_setteurs_Patient(void ** state){
    Patient * p = CreerPatient("NomTest", "PrenomTest", 2020, 03, 29, "test@adresseMail", "testNumeroTelephone");
    *state = p;
}
static int teardown_setteurs_Patient(void ** state){
    DeletePatient((Patient *) *state);
}

int main(void){
    const struct CMUnitTest tests_fonctionsPatient[] = {

            //tests des setteurs de la structure Patient
            cmocka_unit_test(testPatient_setNomPatient),
            cmocka_unit_test(testPatient_setPrenomPatient),
            cmocka_unit_test(testPatient_setDateNaissancePatient),
            cmocka_unit_test(testPatient_setNumeroTelephonePatient),
    };

    return cmocka_run_group_tests(tests_fonctionsPatient, setup_setteurs_Patient, teardown_setteurs_Patient);

}