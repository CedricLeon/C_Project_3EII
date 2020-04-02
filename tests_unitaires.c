#include "tests_unitaires.h"

/*Tout les tests unitaires a la main*/
/* Cf Cmocka*/
/*Minis tests tous lancés à la fin dans un espèce de main*/

/*Compiler le tests_unitaires de Cmocka et vérifier que le bon résultat est attendu*/


/**********************************************************************************************************************/
                                    /*Tests des fonctions Patient*/
/**********************************************************************************************************************/

static void testPatient_creerPatient(void ** state){
    assert_string_equal(((Patient *) *state)->nom,"NomTest");
    assert_string_equal(((Patient *) *state)->prenom,"PrenomTest");
    assert_int_equal(((Patient *) *state)->date_naissance->annee,2020);
    assert_int_equal(((Patient *) *state)->date_naissance->mois, 03);
    assert_int_equal(((Patient *) *state)->date_naissance->jour, 29);
    assert_string_equal(((Patient *) *state)->adresse_mail, "test@adresseMail");
    assert_string_equal(((Patient *) *state)->numero_telephone,"testNumeroTelephone");
}

//static void testPatient_deletePatient(void ** state);
// Je sais pas trop comment faire un test d'un free,
// j'ai essayé test_free() mais erreur et puis dans tout les cas je fait mon free dans le teardown ...
// et puis ça existe un free qui plante ?


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

static void testPatient_AddMedecinPatient_handlesMedecinAdded(void ** state{

}
static void testPatient_AddMedecinPatient_handlesNbMaMedecinAtteint(void ** state){

}
static void testPatient_DeleteMedecinPatient_handlesMedecinsEnleve(void ** state){

}
static void testPatient_DeleteMedecinPatient_handlesPasDeMedecin(void ** state){

}
static void testPatient_DeleteMedecinPatient_handlesMedecinNonPresent(void ** state){

}

//Fonctions de setup et teardown de la structure Patient
static int setup_Patient(void ** state){
    Patient * p = CreerPatient("NomTest", "PrenomTest", 2020, 03, 29, "test@adresseMail", "testNumeroTelephone");
    *state = p;
    return *state == NULL;
}
static int teardown_Patient(void ** state){
    DeletePatient((Patient *) *state);
    return 0;
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
            cmocka_unit_test(testPatient_AddMedecinPatient_handlesNbMaMedecinAtteint),
            cmocka_unit_test(testPatient_DeleteMedecinPatient_handlesMedecinsEnleve),
            cmocka_unit_test(testPatient_DeleteMedecinPatient_handlesPasDeMedecin),
            cmocka_unit_test(testPatient_DeleteMedecinPatient_handlesMedecinNonPresent),
    };
    return cmocka_run_group_tests(tests_fonctionsPatient, setup_Patient, teardown_Patient);
}