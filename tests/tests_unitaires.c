/*Header Files du Projet*/
#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/calendrier.h"
#include "GPCalendar/Model/ordonnance.h"
#include "GPCalendar/Model/dossier_medical.h"
#include "GPCalendar/Model/rendezvous.h"
#include "GPCalendar/Model/calendrier.h"

/*Librairies nécessaire à CMocka*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*Librairies standards de C*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************************************************************/
                                    /*Tests des fonctions Patient*/
/**********************************************************************************************************************/

//Fonctions de setup et teardown de la structure Patient
static int setup_Patient(void ** state){
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecu");
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
    ListMedecin_setOnFirst(((Patient *) *state)->dossierMedical->medecins_consultes);
    assert_ptr_equal(ListMedecin_getCurrent(((Patient *) *state)->dossierMedical->medecins_consultes), m);

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
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 0);     //test par principe mais pas très utile

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
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 1);

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
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 1);

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
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 0);

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
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

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
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

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
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 1);
    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p), 1);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 1);

    DeletePatient(p);
    printf("\n");
}
static void testMedecin_DeletePatientRecuMedecin_handlesPasDePatient(void ** state){
    printf("\n");
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p),0);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 1);

    DeletePatient(p);
    printf("\n");
}
static void testMedecin_DeletePatientRecuMedecin_handlesPatientNonPresent(void ** state){
    printf("\n");
    Patient * p1 = CreerPatient("NomTestP1", "PrenomTestP1", 20201, 031, 291, "test@adresseMailP1", "testNumeroTelephoneP1", "testNumSecuP1");
    Patient * p2 = CreerPatient("NomTestP2", "PrenomTestP2", 20202, 032, 292, "test@adresseMailP2", "testNumeroTelephoneP2", "testNumSecuP2");

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
    ListAnnee *c;
    c = (ListAnnee *) malloc(sizeof(ListAnnee));
    ListAnnee_init(c);
    *state = c;
    return *state == NULL;
}
static int teardown_Calendrier(void ** state){
    printCalendrier((Calendrier) *state);
    freeCalendrier((Calendrier) *state);
    return 0;
}
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesPremierRdvAjoute : Test l'ajout d'un premier rdv au calendrier,
 * pour cela on vérifie que la fonction AddRdvCalendrier return bien 1 et qu'ensuite on trouve bien le rdv dans le calendrier
 * @param state : le calendrier
 */
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
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteAnneeExistante : Test l'ajout d'un 2eme rdv au calendrier,
 * dont l'annee est deja présente dans le calendrier
 * @param state : le calendrier
 */
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
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteMoisExistant : Test l'ajout d'un 3eme rdv au calendrier,
 * dont l'annee et le mois sont deja présents dans le calendrier
 * @param state : le calendrier
 */
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
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesRdvAjoutejourExistant : Test l'ajout d'un 4eme rdv au calendrier,
 * dont l'annee, le mois et le jour sont deja présents dans le calendrier
 * @param state : le calendrier
 */
static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjoutejourExistant(void ** state){
    //On crée un rdv pour le 01/01/2001, jour qui compte déjà un rdv le 01/01/2001 à 01h
    RendezVous * rdv = CreerRendezVous(2001, 01, 01, 04, 240, "lieu4", NULL, NULL, "motif4");

    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));
    //On test qu'on trouve bien le rdv dans le calendrier et que ce rdv et bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //Comme il y a 2 rdv dans ce jour on test aussi l'heure du début, ici 4h
    assert_int_equal(04, ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->heure_debut);
    //On test aussi le motif pcq pk pas
    assert_string_equal("motif4", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);
}

/**********************************************************************************************************************/
                                            /*Tests Date*/
/**********************************************************************************************************************/
/**
 * Première rédaction de la fonction test : 21/04/20
 */

static int setup_Date(void ** state){
    Date * d = CreerDate(2920, 02, 01);     //date test lambda
    *state = d;
    return *state == NULL;
}

static int teardown_Date(void ** state){
    FreeDate((Date *) *state);
    return 0;
}

/**
 * On teste de créer une Date
 * @param state
 */
static void testDate_creerDate(void ** state){
    assert_int_equal(((Date *) *state)->annee,2920);
    assert_int_equal(((Date *) *state)->mois,02);
    assert_int_equal(((Date *) *state)->jour, 01);
}

/**
 * On test de créer la Date Courante
 * Je n'ai pas encore trouvé comment faire pour mettre en paramètre la date courante (sans réécrire la fonction CreerDateCourante sinon c'est un peu débile)
 * Donc il faut faire attention à changer la date en paramètre des assert_int_equal sinon le test ne passera pas
 * @param state
 */
static void testDate_creerDateCourante(void ** state){
    Date * d = CreerDateCourante();
    assert_int_equal(d->annee,2020);//! à changer !
    assert_int_equal(d->mois,04);   //! à changer !
    assert_int_equal(d->jour,30);   //! à changer : si le test fail c'est car la date comparée ne
                                           //! correspond plus à la date courante (On est peut etre plus le 23/4/2020
    FreeDate(d);
}

/**
 * On test l'ajout de nb mois à la Date Courante
 * sachant qu'ici on a pris 1 mois = 30 jours pour chaque mois
 * même problème qu'au dessus il faut changer le test à la main
 * @param state
 */
static void testDate_AjoutMoisDateCourante(void ** state){
    Date * d = AjoutMoisDate((Date*) *state, 3); //test ajout de 3 mois = 90 jours
    assert_int_equal(d->annee,2920); //! à changer !
    assert_int_equal(d->mois,05);   //! à changer !
    assert_int_equal(d->jour,01);   //! à changer !
    FreeDate(d);
}

/**
 * On test getJourDate
 * paramètre du assert en fonction de setup_Date
 * @param state
 */
static void testDate_getJourDate(void ** state){
    char* tmp = (char*) malloc(10); //large
    getJourDate(tmp, (Date *) *state);
    assert_string_equal("1",tmp);
    free((void*) tmp);
}

/**
 * On test getMoisDate
 * paramètre du assert en fonction de setup_Date
 * @param state
 */
static void testDate_getMoisDate(void ** state){
    char* tmp = (char*) malloc(10); //large
    getMoisDate(tmp, (Date *) *state);
    assert_string_equal("2",tmp);
    free((void*) tmp);
}

/**
 * On test getAnneeDate
 * paramètre du assert en fonction de setup_Date
 * @param state
 */
static void testDate_getAnneeDate(void ** state){
    char* tmp = (char*) malloc(10); //large
    getAnneeDate(tmp, (Date *) *state);
    assert_string_equal("2920",tmp);
    free((void*) tmp);
}

/**
 * On test getInfosDate
 * paramètre du assert en fonction de setup_Date
 * @param state
 */
static void testDate_getInfosDate(void ** state){
    char* tmp = (char*) malloc(20); //large
    getInfosDate(tmp, (Date *) *state);
    assert_string_equal("1/2/2920",tmp);
    free((void*) tmp);
}

/**
 * On test DateEgales
 * @param state
 */
static void testDate_DateEgaleshandlesDatesDiff(void ** state){
    //Test 2 dates différentes
    Date * d2 = CreerDate(2801,04,24);
    assert_int_equal(0,DateEgales((Date *) *state, d2));
    FreeDate(d2);
}

static void testDate_DateEgaleshandlesDatesEgales(void ** state){
    //Test 2 dates égales
    Date * d2 = (Date *) *state;
    assert_int_equal(1,DateEgales((Date *) *state, d2));
}

static void testDate_DateEgaleshandlesDateNULL(void ** state){
    //Test avec une date NULL
    Date * d2 = NULL;
    assert_int_equal(-1,DateEgales((Date *) *state, d2));
}

/**********************************************************************************************************************/
                                            /*Tests Ordonnance*/
/**********************************************************************************************************************/
/**
 * Première rédaction de la fonction test : 21/04/20
 */

static int setup_Ordonnance(void ** state){
    Medecin* med = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    Ordonnance* ord = CreerOrdonnance(med,"TestDescription");
    *state = ord;
    return *state == NULL;
}

static int teardown_Ordonnance(void ** state){
    //Penser à free le medecin et le patient ici et non dans DeleteOrdonnace !
    DeleteMedecin(((Ordonnance *) *state)->medecin);
    DeleteOrdonnance((Ordonnance *) *state);
    return 0;
}

/**
 * On teste de créer une Ordonnance
 * @param state
 */
static void testOrdonnance_creerOrdonnance(void ** state){
    assert_string_equal(((Ordonnance *) *state)->medecin->nom,"NomTestM");
    assert_string_equal(((Ordonnance *) *state)->description,"TestDescription");

    //Si il y a un MemoryLeak sur tmp c'est pcq le test CMocka n'est pas passé et CMocka a donc quitter la fonction avant de free tmp
    //Cela N'arrivera pas dans Normal_Exec

    char* tmp = (char*) malloc(10); //large
    getInfosDate(tmp, ((Ordonnance *) *state)->date_edition);
    assert_string_equal(tmp,"30/4/2020"); //! à changer : si le test fail c'est car la date comparée ne
                                             //! correspond plus à la date courante (On est peut etre plus le 26/4/2020)
    getInfosDate(tmp, ((Ordonnance *) *state)->date_expiration);
    assert_string_equal(tmp, "30/7/2020"); //! à changer : idem
    free((void*) tmp);
}

/**
 * On test de modifier une Ordonnance
 * @param state
 */
static void testOrdonnance_modifierOrdonnance(void ** state){
    Medecin * m2 = CreerMedecin("NomTestM2", "PrenomTestM2", "test@adresseMailM2", "testNumeroTelephoneM2", "NumRPSM2");
    DeleteMedecin(((Ordonnance *)*state)->medecin);
    assert_int_equal((modifierOrdonnance((Ordonnance *)*state, m2, "description2")),1);
}

/**********************************************************************************************************************/
                                            /*Main : Appel des Tests*/
/**********************************************************************************************************************/

int main(void){

    //tests à la main//

    Patient * p1 = CreerPatient("NomPatient","PrenomPatient",2000,01,01,"adresseMailPatient","telPatient","numSecuSocialPatient");
    Medecin * m1 = CreerMedecin("NomMedecin", "PrenomMedecin", "mailMedecin", "telMedecin", "NumRPSMedecin");

    RendezVous * rdv1 = CreerRendezVous(2001,01,01,01,60,"lieu1",p1,m1,"motif1");
    RendezVous * rdv2 = CreerRendezVous(2002,02,02,02,120,"lieu2",p1,m1,"motif2");
    RendezVous * rdv3 = CreerRendezVous(2003,03,03,03,180,"lieu3",p1,m1,"motif3");

    ListAnnee * c = (ListAnnee *) malloc(sizeof(ListAnnee));
    ListAnnee_init(c);

    AddRendezVous_Calendrier(c,rdv1);
    AddRendezVous_Calendrier(c,rdv2);
    AddRendezVous_Calendrier(c,rdv3);

    printCalendrier(c);
    freeCalendrier(c);
    DeletePatient(p1);
    DeleteMedecin(m1);

    const struct CMUnitTest tests_fonctionsPatient[] = {

            //tests des fonctions de création d'instances
            cmocka_unit_test(testPatient_creerPatient),

            //tests des setteurs de la structure Patient    : inutile
            cmocka_unit_test(testPatient_setNomPatient),
            cmocka_unit_test(testPatient_setPrenomPatient),
            cmocka_unit_test(testPatient_setDateNaissancePatient),
            cmocka_unit_test(testPatient_setAdresseMailPatient),
            cmocka_unit_test(testPatient_setNumeroTelephonePatient),

            //Tests des fonctions d'ajout et de delete de medecins à la liste de mèdecins consultés par le patient
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

    const struct CMUnitTest tests_fonctionsDate[] = {
            cmocka_unit_test(testDate_creerDate),
            //cmocka_unit_test(testDate_creerDateCourante),
            cmocka_unit_test(testDate_AjoutMoisDateCourante),
            cmocka_unit_test(testDate_getJourDate),
            cmocka_unit_test(testDate_getMoisDate),
            cmocka_unit_test(testDate_getAnneeDate),
            cmocka_unit_test(testDate_getInfosDate),
            cmocka_unit_test(testDate_DateEgaleshandlesDatesDiff),
            cmocka_unit_test(testDate_DateEgaleshandlesDatesEgales),
            cmocka_unit_test(testDate_DateEgaleshandlesDateNULL),
    };

    const struct CMUnitTest tests_fonctionsOrdonnance[] = {
            //cmocka_unit_test(testOrdonnance_creerOrdonnance),
            //cmocka_unit_test(testOrdonnance_modifierOrdonnance),
    };

    printf("\033[34;01m\n****************************** Running Patient Tests ******************************\n\n\033[00m");
    int return_cmocka_P = cmocka_run_group_tests(tests_fonctionsPatient, setup_Patient, teardown_Patient);
    printf("\033[34;01m\n****************************** Running Medecin Tests ******************************\n\n\033[00m");
    int return_cmocka_M = cmocka_run_group_tests(tests_fonctionsMedecin, setup_Medecin, teardown_Medecin);
    printf("\033[34;01m\n***************************** Running Calendrier Tests *****************************\n\n\033[00m");
    int return_cmocka_C = cmocka_run_group_tests(tests_fonctionsCalendrier, setup_Calendrier, teardown_Calendrier);
    printf("\033[34;01m\n***************************** Running Date Tests *****************************\n\n\033[00m");
    int return_cmocka_D = cmocka_run_group_tests(tests_fonctionsDate, setup_Date, teardown_Date);
    printf("\033[34;01m\n***************************** Running Ordonnance Tests *****************************\n\n\033[00m");
    int return_cmocka_O = cmocka_run_group_tests(tests_fonctionsOrdonnance, setup_Ordonnance, teardown_Ordonnance);

    //Appeler plusieurs cmocka_run_group_tests() dans le return ne marche pas, il execute seulement le premier donc je passe par des int temporaires
    return  return_cmocka_P && return_cmocka_M &&return_cmocka_C && return_cmocka_D && return_cmocka_O;

}
