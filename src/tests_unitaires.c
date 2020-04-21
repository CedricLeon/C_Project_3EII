/*tests_unitaires.h n'a pas d'utilité puique les seules fonctions présentes ici sont static*/

/*Header Files du Projet*/
#include "medecin.h"
#include "patient.h"
#include "date.h"
#include "calendrier.h"
#include "ordonnance.h"
#include "dossier_medical.h"
#include "rendezvous.h"
#include "calendrier.h"

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
                                            /*Tests Calendrier*/
/**********************************************************************************************************************/

/**
 * Première rédaction de la fonction test : 15/04/20
 * Ici je vais testé la grosse fonction AddRendezVous_Calendrier() en testant tout les cas que j'ai dissocié en écrivant
 * la fonction.
 * Cette fonction de test changera certainement plus tard (après l'implémentation de rdv_valable() par exemple) car pour
 * l'instant AddRendezVous_Calendrier() ne return que 1, donc pas de cas d'erreur, on viendra vérifier manuellement
 * qu'on trouve bien le rdv au bon endroit
 * On verra en dessous si onn peut tester freeCalendrier() aussi
 */

//On fera le test de Rdv_valable après
static int setup_Calendrier(void ** state){
    Calendrier c = (Calendrier) malloc(sizeof(Calendrier));
    ListAnnee_init(c);
    *state = c;
    return *state == NULL;
}
static int teardown_Calendrier(void ** state){
    freeCalendrier((Calendrier) *state);
    return 0;
}
static void testCalendrier_AddRendezVous_Calendrier_handlesPremierRdvAjoute(void ** state){
    //On va créer un rdv où le patient et le mèdecin sont des objets NULL par soucis de simplicité, on fera attention
    //à ne pas y accéder
    RendezVous * rdv = CreerRendezVous(2001, 01, 01, 01, 60, "lieu1", NULL, NULL, "motif1");
    //On ajoute le rdv au calendrier
    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));

    //On test qu'on trouve bien le rdv dans le calendrier et que ce rdv et bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //On test aussi le motif pcq pk pas
    assert_string_equal("motif1", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);

    //On ne free pas le rdv ajouté car ce sera fait dans le teardown de toutes ces fonctions tests
}

static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteAnneeExistante(void ** state){
    //On crée un rdv pour le 02/02/2001, année qui compte déjà un rdv le 01/01/2001
    RendezVous * rdv = CreerRendezVous(2001, 02, 02, 02, 120, "lieu2", NULL, NULL, "motif2");

    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));
    //On test qu'on trouve bien le rdv dans le calendrier et que ce rdv et bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(02, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(02, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //On test aussi le motif pcq pk pas
    assert_string_equal("motif2", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);
}
static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteMoisExistant(void ** state){
    //On crée un rdv pour le 03/01/2001, mois qui compte déjà un rdv le 01/01/2001
    RendezVous * rdv = CreerRendezVous(2001, 01, 03, 03, 180, "lieu3", NULL, NULL, "motif3");

    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));
    //On test qu'on trouve bien le rdv dans le calendrier et que ce rdv et bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(03, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //On test aussi le motif pcq pk pas
    assert_string_equal("motif3", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);
}
static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjoutejourExistant(void ** state){

}



/**********************************************************************************************************************/
                                            /*Main : Appel des Test*/
/**********************************************************************************************************************/

int main(void){

    //tests à la main pour les listes de rdv, jours, mois et année :
    Patient * p1 = CreerPatient("NomPatient","PrenomPatient",2000,01,01,"adresseMailPatient","telPatient");
    Medecin * m1 = CreerMedecin("NomMedecin", "PrenomMedecin", "mailMedecin", "telMedecin", "NumRPSMedecin");

    RendezVous * rdv1 = CreerRendezVous(2020,04,8,16,60,"TieKar",p1,m1,"Motif : Test1");


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

    const struct CMUnitTest tests_fonctionsCalendrier[] = {
            cmocka_unit_test(testCalendrier_AddRendezVous_Calendrier_handlesPremierRdvAjoute),
            cmocka_unit_test(testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteAnneeExistante),
            cmocka_unit_test(testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteMoisExistant),
            cmocka_unit_test(testCalendrier_AddRendezVous_Calendrier_handlesRdvAjoutejourExistant),
    };

    printf("\033[34;01m\n****************************** Running Patient Tests ******************************\n\n\033[00m");
    int return_cmocka_P = cmocka_run_group_tests(tests_fonctionsPatient, setup_Patient, teardown_Patient);
    printf("\033[34;01m\n****************************** Running Medecin Tests ******************************\n\n\033[00m");
    int return_cmocka_M = cmocka_run_group_tests(tests_fonctionsMedecin, setup_Medecin, teardown_Medecin);
    printf("\033[34;01m\n***************************** Running Calendrier Tests *****************************\n\n\033[00m");
    int return_cmocka_C = cmocka_run_group_tests(tests_fonctionsCalendrier, setup_Calendrier, teardown_Calendrier);

    //Appeler plusieurs cmocka_run_group_tests() dans le return ne marche pas, il execute seulement le premier donc je passe par des int temporaires
    return  return_cmocka_P && return_cmocka_M;
}