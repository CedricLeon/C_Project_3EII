/*Header Files du Projet*/
#include "GPCalendar/Model/project_GPCalendar.h"
#include "GPCalendar/Model/medecin.h"
#include "GPCalendar/Model/patient.h"
#include "GPCalendar/Model/date.h"
#include "GPCalendar/Model/calendrier.h"
#include "GPCalendar/Model/ordonnance.h"
#include "GPCalendar/Model/dossier_medical.h"
#include "GPCalendar/Model/rendezvous.h"


/*Librairies nécessaire à CMocka*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h> //Ne pas enlever même si l'IDE dit qu'elle n'est pas utilisée (Cf type ‘jmp_buf’)
#include <cmocka.h> //bien mettre ce include après <setjmp.h>

/*Librairies standards de C*/
#include <stdio.h>
#include <stdlib.h>

#ifndef CMAKE_TODAY_TESTS
#define CMAKE_TODAY_TESTS "Not Defined"
#endif

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

/**
 * On teste si le médecin est bien ajouté
 * @param state
 */
static void testPatient_AddMedecinPatient_handlesMedecinAdded(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    ListMedecin_setOnFirst(((Patient *) *state)->dossierMedical->medecins_consultes);
    assert_ptr_equal(ListMedecin_getCurrent(((Patient *) *state)->dossierMedical->medecins_consultes), m);

    DeleteMedecinConsultePatient((Patient *) *state, m);
    DeleteMedecin(m);
}
/**
 * On teste si il ne se passe rien car le médecin a déjà été ajouté
 * @param state
 */
static void testPatient_AddMedecinPatient_handlesMedecinDejaConsulte(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    assert_int_equal(AddMedecinConsultePatient((Patient *) *state, m), 1);                  //Should print "medecin add au debut de la liste"
    assert_int_equal(AddMedecinConsultePatient((Patient *) *state, m), 0);                  //Should print "cant add, deja consulté"
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 0);

    DeleteMedecinConsultePatient((Patient *) *state, m);
    DeleteMedecin(m);
}
/**
 * On teste si le delete de medecin est bien enlevé de la liste
 * @param state
 */
static void testPatient_DeleteMedecinPatient_handlesMedecinsEnleve(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    AddMedecinConsultePatient((Patient *) *state, m);
    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m), 1);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 1);

    DeleteMedecin(m);
}
/**
 * On teste si on essaye d'enlever un medecin d'une liste vide
 * @param state
 */
static void testPatient_DeleteMedecinPatient_handlesPasDeMedecin(void ** state){
    Medecin * m = CreerMedecin("NomTestM", "PrenomTestM", "test@adresseMailM", "testNumeroTelephoneM", "NumRPSM");

    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m),0);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 1);

    DeleteMedecin(m);
}
/**
 * On teste d'enlever un medecin non présent dans la liste
 * @param state
 */
static void testPatient_DeleteMedecinPatient_handlesMedecinNonPresent(void ** state){
    Medecin * m1 = CreerMedecin("NomTestM1", "PrenomTestM1", "test@adresseMailM1", "testNumeroTelephoneM1", "NumRPSM1");
    Medecin * m2 = CreerMedecin("NomTestM2", "PrenomTestM2", "test@adresseMailM2", "testNumeroTelephoneM2", "NumRPSM2");

    AddMedecinConsultePatient((Patient *) *state, m1);
    //On add pas m2 et on essaye de le delete

    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m2),0);
    assert_int_equal(ListMedecin_isEmpty(((Patient *) *state)->dossierMedical->medecins_consultes), 0);
    assert_int_equal(DeleteMedecinConsultePatient((Patient *) *state, m1),1);

    DeleteMedecin(m1);
    DeleteMedecin(m2);
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
 * On teste de créer un Medecin
 * @param state
 */
static void testMedecin_creerMedecin(void ** state){
    assert_string_equal(((Medecin *) *state)->nom,"NomTestM");
    assert_string_equal(((Medecin *) *state)->prenom,"PrenomTestM");
    assert_string_equal(((Medecin *) *state)->adresse_mail, "test@adresseMailM");
    assert_string_equal(((Medecin *) *state)->numero_telephone,"testNumeroTelephoneM");
    assert_string_equal(((Medecin *) *state)->numero_RPS, "NumRPSM");
}
/**
 * On teste si le patient recu est bien ajouté à la liste
 * @param state
 */
static void testMedecin_AddPatientRecuMedecin_handlesPatientAdded(void ** state){
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

    AddPatientRecuMedecin((Medecin *) *state, p);
    ListPatient_setOnFirst(((Medecin *) *state)->patients_recus);
    assert_ptr_equal(ListPatient_getCurrent(((Medecin *) *state)->patients_recus), p);

    DeletePatientRecuMedecin((Medecin *) *state, p);
    DeletePatient(p);
}
/**
 * On teste si il ne se passe rien car le patient a déjà été ajouté
 * @param state
 */
static void testMedecin_AddPatientRecuMedecin_handlesPatientDejaRecu(void ** state){
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 1);                  //Should print "patient add au debut de la liste"
    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 0);                  //Should print "cant add, deja consulté"
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 0);     //test par principe mais pas très utile

    DeletePatientRecuMedecin((Medecin *) *state, p);
    DeletePatient(p);
}
static void testMedecin_DeletePatientRecuMedecint_handlesPatientEnleve(void ** state){
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

    assert_int_equal(AddPatientRecuMedecin((Medecin *) *state, p), 1);
    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p), 1);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 1);

    DeletePatient(p);
}
static void testMedecin_DeletePatientRecuMedecin_handlesPasDePatient(void ** state){
    Patient * p = CreerPatient("NomTestP", "PrenomTestP", 2020, 03, 29, "test@adresseMailP", "testNumeroTelephoneP", "testNumSecuP");

    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p),0);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 1);

    DeletePatient(p);
}
static void testMedecin_DeletePatientRecuMedecin_handlesPatientNonPresent(void ** state){
    Patient * p1 = CreerPatient("NomTestP1", "PrenomTestP1", 20201, 031, 291, "test@adresseMailP1", "testNumeroTelephoneP1", "testNumSecuP1");
    Patient * p2 = CreerPatient("NomTestP2", "PrenomTestP2", 20202, 032, 292, "test@adresseMailP2", "testNumeroTelephoneP2", "testNumSecuP2");

    AddPatientRecuMedecin((Medecin *) *state, p1);
    //On add pas p2 et on essaye de le delete

    assert_int_equal(DeletePatientRecuMedecin((Medecin *) *state, p2),0);
    assert_int_equal(ListPatient_isEmpty(((Medecin *) *state)->patients_recus), 0);

    DeletePatient(p1);
    DeletePatient(p2);
}

/**********************************************************************************************************************/
                                            /*Tests Calendrier N°1*/
/**********************************************************************************************************************/

/**
 * Première rédaction de la fonction test : 15/04/20
 * Ici je vais tester la grosse fonction AddRendezVous_Calendrier() en testant tous les cas que j'ai dissocié en écrivant
 * la fonction.
 * Cette fonction de test changera certainement plus tard (après l'implémentation de rdv_valable() par exemple) car pour
 * l'instant AddRendezVous_Calendrier() ne return que 1, donc pas de cas d'erreur, on viendra vérifier manuellement
 * qu'on trouve bien le rdv au bon endroit
 * On verra en dessous si on peut tester freeCalendrier() aussi
 */

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
    Patient* p1 = CreerPatient("nomP1", "prenomP1", 1111, 11, 11, "mailP1", "telP1", "secuP1");
    Medecin* m1 = CreerMedecin("nomM1", "prenomM1", "mailM1", "telM1", "rpsM1");

    RendezVous * rdv = CreerRendezVous(2001, 01, 01, 01, 60, "lieu1", p1, m1, "motif1");
    //On ajoute le rdv au calendrier
    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));

    //On teste qu'on trouve bien le rdv dans le calendrier et que ce rdv est bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //On teste aussi le motif pcq pk pas
    assert_string_equal("motif1", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);

    //On ne free pas le rdv ajouté car ce sera fait dans le teardown de toutes ces fonctions tests
    //par contre on free le patient et le médecin

    DeleteMedecin(m1);
    DeletePatient(p1);
}
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteAnneeExistante : Test l'ajout d'un 2eme rdv au calendrier,
 * dont l'annee est deja présente dans le calendrier
 * @param state : le calendrier
 */
static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteAnneeExistante(void ** state){
    Patient* p2 = CreerPatient("nomP2", "prenomP2", 2222, 22, 22, "mailP2", "telP2", "secuP2");
    Medecin* m2 = CreerMedecin("nomM2", "prenomM2", "mailM2", "telM2", "rpsM2");

    //On crée un rdv pour le 02/02/2001, année qui compte déjà un rdv le 01/01/2001
    RendezVous * rdv = CreerRendezVous(2001, 02, 02, 02, 120, "lieu2", p2, m2, "motif2");

    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));
    //On teste qu'on trouve bien le rdv dans le calendrier et que ce rdv est bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(02, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(02, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //On teste aussi le motif
    assert_string_equal("motif2", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);
    DeleteMedecin(m2);
    DeletePatient(p2);
}
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteMoisExistant : Test l'ajout d'un 3eme rdv au calendrier,
 * dont l'annee et le mois sont deja présents dans le calendrier
 * @param state : le calendrier
 */
static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjouteMoisExistant(void ** state){
    Patient* p3 = CreerPatient("nomP3", "prenomP3", 3333, 33, 33, "mailP3", "telP3", "secuP3");
    Medecin* m3 = CreerMedecin("nomM3", "prenomM3", "mailM3", "telM3", "rpsM3");
    //On crée un rdv pour le 03/01/2001, mois qui compte déjà un rdv le 01/01/2001
    RendezVous * rdv = CreerRendezVous(2001, 01, 03, 03, 180, "lieu3", p3, m3, "motif3");

    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));
    //On teste qu'on trouve bien le rdv dans le calendrier et que ce rdv est bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(03, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //On teste aussi le motif
    assert_string_equal("motif3", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);
    DeleteMedecin(m3);
    DeletePatient(p3);
}
/**
 * testCalendrier_AddRendezVous_Calendrier_handlesRdvAjoutejourExistant : Test l'ajout d'un 4eme rdv au calendrier,
 * dont l'annee, le mois et le jour sont deja présents dans le calendrier
 * @param state : le calendrier
 */
static void testCalendrier_AddRendezVous_Calendrier_handlesRdvAjoutejourExistant(void ** state){
    Patient* p4 = CreerPatient("nomP4", "prenomP4", 4444, 44, 44, "mailP4", "telP4", "secuP4");
    Medecin* m4 = CreerMedecin("nomM4", "prenomM4", "mailM4", "telM4", "rpsM4");
    //On crée un rdv pour le 01/01/2001, jour qui compte déjà un rdv le 01/01/2001 à 01h
    RendezVous * rdv = CreerRendezVous(2001, 01, 01, 04, 30, "lieu4", p4, m4, "motif4");

    assert_int_equal(1, AddRendezVous_Calendrier((Calendrier) *state, rdv));
    //On teste qu'on trouve bien le rdv dans le calendrier et que ce rdv est bien placé au bon endroit (test de l'année, du mois et du jour)
    assert_int_equal(1, chercherRendezVous_Calendrier((Calendrier) *state,rdv));
    assert_int_equal(2001, ((Calendrier) *state)->current->annee->annee);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->mois);
    assert_int_equal(01, ((Calendrier) *state)->current->annee->current->mois->current->jour->date->jour);
    //Comme il y a 2 rdv dans ce jour on test aussi l'heure du début, ici 4h
    assert_int_equal(04, ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->heure_debut);
    //On teste aussi le motif
    assert_string_equal("motif4", ((Calendrier) *state)->current->annee->current->mois->current->jour->current->rdv->motif);
    DeleteMedecin(m4);
    DeletePatient(p4);
}

/**********************************************************************************************************************/
                                    /*Tests RendezVous Valable*/
/**********************************************************************************************************************/

static int setup_RdvValable(void ** state){
    Calendrier  c = CreerCalendrier();
    ListMedecin* lM = CreerListMedecin();
    ListPatient* lP = CreerListPatient();

    Project_GPCalendar* p = CreerProject("nomProjetTest", lM, lP, c);
    *state = p;

    //ajout d'un 1er rdv au calendrier
    Patient* p1 = CreerPatient("nomP4", "prenomP4", 4444, 44, 44, "mailP4", "telP4", "secuP");
    Medecin* m = CreerMedecin("nomM4", "prenomM4", "mailM4", "telM4", "rpsM");
    RendezVous * rdv = CreerRendezVous(2001, 01, 01, 04, 30, "lieu4", p1, m, "motif4");
    AddRendezVous_Calendrier(p->calendrier, rdv);
    ListPatient_add(p->consultingPatient, p1);
    ListMedecin_add(p->workingMedecins, m);

    return *state == NULL;
}
static int teardown_RdvValable(void ** state){
    printProject((Project_GPCalendar*) *state);
    freeProject((Project_GPCalendar*) *state);
    return 0;
}

/**
 * testCalendrier_RendezVousValable_handlesRDVValable_DateDiff : Teste si le RDV est valable pour des dates nouvelles
 * @param state : le calendrier
 */
static void testCalendrier_RendezVousValable_handlesRDVValable_DateDiff(void ** state){
    Patient* p1 = CreerPatient("nomP1", "prenomP1", 1111, 11, 11, "mailP1", "telP1", "secuP1");
    Medecin* m1 = CreerMedecin("nomM1", "prenomM1", "mailM1", "telM1", "rpsM1");
    ListPatient_add(((Project_GPCalendar*) *state)->consultingPatient, p1);
    ListMedecin_add(((Project_GPCalendar*) *state)->workingMedecins, m1);

    RendezVous* rdv = CreerRendezVous(2021, 01, 01, 11, 30, "lieu1", p1, m1, "motif1");
    //printProject((Project_GPCalendar*) *state);
    assert_int_equal(1, RendezVousValable(((Project_GPCalendar*) *state)->calendrier, rdv));
    assert_int_equal(1, AddRendezVous_Calendrier(((Project_GPCalendar*) *state)->calendrier, rdv));
    assert_int_equal(1, chercherRendezVous_Calendrier(((Project_GPCalendar*) *state)->calendrier,rdv));
}

/**
 * testCalendrier_RendezVousValable_handlesRDVValable_MemeJour : Teste si le RDV est valable pour le même jour à un horaire libre
 * @param state : le calendrier
 */
static void testCalendrier_RendezVousValable_handlesRDVValable_MemeJour(void ** state){
    Patient* p1 = ListPatient_seek(((Project_GPCalendar*) *state)->consultingPatient, "secuP1");
    Medecin* m1 = ListMedecin_seek(((Project_GPCalendar*) *state)->workingMedecins, "rpsM1");

    RendezVous* rdv = CreerRendezVous(2021, 01, 01, 12, 30, "lieu1", p1, m1, "motif1");
    assert_int_equal(1, RendezVousValable(((Project_GPCalendar*) *state)->calendrier, rdv));
    assert_int_equal(1, AddRendezVous_Calendrier(((Project_GPCalendar*) *state)->calendrier, rdv));
    assert_int_equal(1, chercherRendezVous_Calendrier(((Project_GPCalendar*) *state)->calendrier,rdv));
}
/**
 * testCalendrier_RendezVousValable_handlesRDVValable_MemeHeureMemeMedecin : Teste si le RDV est valable à la même heure de début qu'un autre RDV,
 * avec le même médecin, mais un patient et lieu différents
 * @param state : le calendrier
 */
static void testCalendrier_RendezVousValable_handlesRDVpasValable_MemeHeureMemeMedecin(void ** state){
    Patient* p3 = CreerPatient("nomP3", "prenomP3", 3333, 33, 33, "mailP3", "telP3", "secuP3");
    ListPatient_add(((Project_GPCalendar*) *state)->consultingPatient, p3);

    Medecin* m3 = ListMedecin_seek(((Project_GPCalendar*) *state)->workingMedecins, "rpsM1");

    RendezVous* rdv = CreerRendezVous(2021, 01, 01, 11, 90, "lieu1", p3, m3, "motif1");
    assert_int_equal(0, RendezVousValable(((Project_GPCalendar*) *state)->calendrier, rdv));
    FreeRendezVous(rdv);
}
/**
 * testCalendrier_RendezVousValable_handlesRDVValable_HeureChevaucheMemeMedecin : Teste si le RDV est valable pendant un autre RDV,
 * avec le même médecin, mais un patient et lieu différents
 * @param state : le calendrier
 */
static void testCalendrier_RendezVousValable_handlesRDVpasValable_HeureChevaucheMemeMedecin(void ** state){
    Patient* p4 = ListPatient_seek(((Project_GPCalendar*) *state)->consultingPatient, "secuP3");
    Medecin* m4 = ListMedecin_seek(((Project_GPCalendar*) *state)->workingMedecins, "rpsM1");

    RendezVous* rdv = CreerRendezVous(2021, 01, 01, 10.5, 60, "lieu1", p4, m4, "motif1");
    assert_int_equal(0, RendezVousValable(((Project_GPCalendar*) *state)->calendrier, rdv));
    FreeRendezVous(rdv);
}

/**
 * testCalendrier_RendezVousValable_handlesRDVValable_MemeHeureMemePatient : Teste si le RDV est valable à la même heure de début qu'un autre RDV,
 * avec le même patient, mais le médecin et le lieu différents
 * @param state : le calendrier
 */
static void testCalendrier_RendezVousValable_handlesRDVpasValable_MemeHeureMemePatient(void ** state){
    Patient* p5 = ListPatient_seek(((Project_GPCalendar*) *state)->consultingPatient, "secuP1");
    Medecin* m5 = CreerMedecin("nomM5", "prenomM5", "mailM5", "telM5", "rpsM5");
    ListMedecin_add(((Project_GPCalendar*) *state)->workingMedecins, m5);

    RendezVous* rdv = CreerRendezVous(2021, 01, 01, 11, 30, "lieu5", p5, m5, "motif5");
    assert_int_equal(0, RendezVousValable(((Project_GPCalendar*) *state)->calendrier, rdv));
    FreeRendezVous(rdv);
}

/**
 * testCalendrier_RendezVousValable_handlesRDVValable_MemeHeureMemeLieu : Teste si le RDV est valable à la même heure de début qu'un autre RDV,
 * avec le même lieu, mais le médecin et le patient différents
 * @param state : le calendrier
 */
static void testCalendrier_RendezVousValable_handlesRDVpasValable_MemeHeureMemeLieu(void ** state){
    Patient* p7 = CreerPatient("nomP7", "prenomP7", 4444, 44, 44, "mailP7", "telP7", "secuP7");
    Medecin* m7 = CreerMedecin("nomM7", "prenomM7", "mailM7", "telM7", "rpsM7");
    ListPatient_add(((Project_GPCalendar*) *state)->consultingPatient, p7);
    ListMedecin_add(((Project_GPCalendar*) *state)->workingMedecins, m7);

    RendezVous* rdv = CreerRendezVous(2021, 01, 01, 11, 30, "lieu1", p7, m7, "motif1");
    assert_int_equal(0, RendezVousValable(((Project_GPCalendar*) *state)->calendrier, rdv));
    FreeRendezVous(rdv);
}

/**********************************************************************************************************************/
                                            /*Tests Calendrier N°2*/
/**********************************************************************************************************************/

static int setup_Calendrier2(void ** state){
    Calendrier  c = CreerCalendrier();
    *state = c;
    return *state == NULL;
}
static int teardown_Calendrier2(void ** state){
    printCalendrier((Calendrier) *state);
    freeCalendrier((Calendrier) *state);
    return 0;
}
static void testCalendrier_AnnulerRendezVous_Calendrier_handlesRdvAnnule_PasAutresRDVPatientMedecin(void ** state){
    Patient* p1 = CreerPatient("nomP1", "prenomP1", 1111, 11, 11, "mailP1", "telP1", "secuP1");
    Medecin* m1 = CreerMedecin("nomM1", "prenomM1", "mailM1", "telM1", "rpsM1");
    RendezVous* rdv = CreerRendezVous(2021, 11, 11, 16, 30, "lieuRDV", p1, m1, "motifRDV");
    assert_int_equal(AddRendezVous_Calendrier((Calendrier) *state, rdv), 1);
    assert_int_equal( AnnulerRendezVous((Calendrier) *state, rdv), 1);
    assert_int_equal(ListPatient_isEmpty(m1->patients_recus), 1);
    assert_int_equal(ListMedecin_isEmpty(p1->dossierMedical->medecins_consultes), 1);
    DeleteMedecin(m1);
    DeletePatient(p1);
}
static void testCalendrier_AnnulerRendezVous_Calendrier_handlesRdvAnnule_AutreRDVPatientMedecin(void ** state){
    //Patient* p2 = CreerPatient("nomP2", "prenomP2", 1222, 12, 12, "mailP2", "telP2", "secuP2");
    //Medecin* m2 = CreerMedecin("nomM2", "prenomM2", "mailM2", "telM2", "rpsM2");
    Patient* p1 = CreerPatient("nomP1", "prenomP1", 1111, 11, 11, "mailP1", "telP1", "secuP1");
    Medecin* m1 = CreerMedecin("nomM1", "prenomM1", "mailM1", "telM1", "rpsM1");
    RendezVous* rdv1 = CreerRendezVous(2021, 11, 11, 11, 30, "lieuRDV1", p1, m1, "motifRDV1");
    RendezVous* rdv2 = CreerRendezVous(2022, 22, 22, 22, 60, "lieuRDV2", p1, m1, "motifRDV2");
    assert_int_equal(AddRendezVous_Calendrier((Calendrier) *state, rdv1), 1);
    assert_int_equal(AddRendezVous_Calendrier((Calendrier) *state, rdv2), 1);
    assert_int_equal( AnnulerRendezVous((Calendrier) *state, rdv2), 1);
    assert_int_equal(ListPatient_isEmpty(m1->patients_recus), 0);
    assert_int_equal(ListMedecin_isEmpty(p1->dossierMedical->medecins_consultes), 0);
    DeleteMedecin(m1);
    DeletePatient(p1);
}
static void testCalendrier_AnnulerRendezVous_Calendrier_handlesRdvPasse(void ** state){
    Patient* p3 = CreerPatient("nomP3", "prenomP3", 3333, 33, 33, "mailP3", "telP3", "secuP3");
    Medecin* m3 = CreerMedecin("nomM3", "prenomM3", "mailM3", "telM3", "rpsM3");
    RendezVous* rdv3 = CreerRendezVous(333, 03, 03, 03, 30, "lieuRDV3", p3, m3, "motifRDV3");
    assert_int_equal(AddRendezVous_Calendrier((Calendrier) *state, rdv3), 1);
    assert_int_equal( AnnulerRendezVous((Calendrier) *state, rdv3), 0);
    assert_int_equal(ListPatient_isEmpty(m3->patients_recus), 0);
    assert_int_equal(ListMedecin_isEmpty(p3->dossierMedical->medecins_consultes), 0);
    DeleteMedecin(m3);
    DeletePatient(p3);
}
static void testCalendrier_DeplacerRendezVous(void ** state){
    Patient* p4 = CreerPatient("nomP4", "prenomP4", 3333, 33, 33, "mailP3", "telP3", "secuP3");
    Medecin* m4 = CreerMedecin("nomM4", "prenomM4", "mailM3", "telM3", "rpsM3");
    RendezVous* rdv4 = CreerRendezVous(2021, 10, 01, 12, 60, "lieuRDV3", p4, m4, "motifRDV4");
    assert_int_equal(AddRendezVous_Calendrier((Calendrier) *state, rdv4), 1);
    assert_ptr_equal(DeplacerRendezVous(rdv4, 2021, 12, 02, 13, 120), rdv4);
    assert_int_equal(rdv4->date->annee, 2021);
    assert_int_equal(rdv4->date->mois, 12);
    assert_int_equal(rdv4->date->jour, 02);
    assert_int_equal(rdv4->heure_debut, 13);
    assert_int_equal(rdv4->heure_fin, 15);
    char infos[1000];
    getInfosRendezVous(infos, rdv4);
    printf("Infos du rendez-vous de testCalendrier_DeplacerRendezVous() : \n\n%s", infos);
    DeleteMedecin(m4);
    DeletePatient(p4);
}


/**********************************************************************************************************************/
                                            /*Tests Date*/
/**********************************************************************************************************************/


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
    char* tmp = (char*) malloc(20);
    getInfosDate(tmp,d);
    assert_string_equal(tmp, CMAKE_TODAY_TESTS); 
	free((void*)tmp);
    FreeDate(d);
}

/**
 * On test l'ajout de nb mois à la Date
 * sachant qu'ici on a pris 1 mois = 30 jours pour chaque mois
 * même problème qu'au dessus il faut changer le test à la main
 * @param state
 */
static void testDate_AjoutMoisDate(void ** state){
    Date * d = AjoutMoisDate((Date*) *state, 3); //test ajout de 3 mois = 90 jours
    assert_int_equal(d->annee,2920); //! à changer !
    assert_int_equal(d->mois,5);   //! à changer !
    assert_int_equal(d->jour,01);   //! à changer !
    FreeDate(d);
}

/**
 * On test getJourDate
 * paramètre du assert en fonction de setup_Date
 * @param state
 */
static void testDate_getJourDate(void ** state){
    char* tmp = (char*) malloc(10);
    getJourDate(tmp, (Date *) *state);
    assert_string_equal("01",tmp);
    free((void*) tmp);
}

/**
 * On test getMoisDate
 * paramètre du assert en fonction de setup_Date
 * @param state
 */
static void testDate_getMoisDate(void ** state){
    char* tmp = (char*) malloc(10);
    getMoisDate(tmp, (Date *) *state);
    assert_string_equal("02",tmp);
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
    assert_string_equal("01/02/2920",tmp);
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

    //Si il y a un MemoryLeak sur tmp c'est pcq le test CMocka n'est pas passé et CMocka a donc quitté la fonction avant de free tmp
    //Cela N'arrivera pas dans Normal_Exec

    char* tmp = (char*) malloc(20);
    getInfosDate(tmp, ((Ordonnance *) *state)->date_edition);
    assert_string_equal(tmp, CMAKE_TODAY_TESTS); //! à changer : si le test fail c'est car la date comparée ne
                                             //! correspond plus à la date courante (On est peut etre plus le 26/4/2020)
    getInfosDate(tmp, ((Ordonnance *) *state)->date_expiration);
    char* str = (char*) malloc(strlen(CMAKE_TODAY_TESTS)+1);
    strcpy(str, CMAKE_TODAY_TESTS);
    char month[3];
    sprintf(month,"%02d", ((Ordonnance *) *state)->date_edition->mois + 3);
    str[3] = month[0];
    str[4] = month[1];
    assert_string_equal(tmp, str); //! à changer : idem
    free((void*) tmp);
    free((void *) str);
}

/**
 * On test de modifier une Ordonnance
 * @param state
 */
static void testOrdonnance_modifierOrdonnance(void ** state){
    assert_int_equal((modifierOrdonnance((Ordonnance *)*state, ((Ordonnance *)*state)->medecin, "description2")),1);
}

/**********************************************************************************************************************/
                                                /*Tests DossierMedical*/
/**********************************************************************************************************************/

static int setup_DossierMedical(void ** state){
    DossierMedical* doss = CreerDossierMedical();
    *state = doss;
    return *state == NULL;

}
static int teardown_DossierMedical(void ** state){
    FreeDossierMedical((DossierMedical*) *state);
    return 0;
}

static void testDossierMedical_AddOrdonnanceDossierMedical_handlesOrdonnanceAdded(void ** state){
    Ordonnance* o = CreerOrdonnance(NULL, "test");
    assert_int_equal(AddOrdonnanceDossierMedical((DossierMedical *) *state, o), 1);
    ListOrdonnance_setOnFirst(((DossierMedical *) *state)->ordonnances);
    assert_ptr_equal(ListOrdonnance_getCurrent(((DossierMedical *) *state)->ordonnances), o);
    // /!\ il ne faut pas delete l'ordonnance ici car on le fait déjà dans le teardown !
}

static void testDossierMedical_AddAntecedentsDossierMedical_handlesAntecedentAdded(void ** state){
    assert_int_equal(AddAntecedentDossierMedical((DossierMedical *) *state, "test si espaces marchent"), 1); //!il faut ecrire "test si espaces marchent"
    ListAntecedent_setOnFirst(((DossierMedical *) *state)->antecedents);
    assert_string_equal(ListAntecedent_getCurrent(((DossierMedical *) *state)->antecedents), "test si espaces marchent");
}
static void testDossierMedical_AddAntecedentsDossierMedical_handlesAntecedentAdded2(void ** state){
    assert_int_equal(AddAntecedentDossierMedical((DossierMedical *) *state, "antecedent 2"), 1);
    ListAntecedent_setOnFirst(((DossierMedical *) *state)->antecedents);
    ListAntecedent_setOnNext(((DossierMedical *) *state)->antecedents);
    assert_string_equal(ListAntecedent_getCurrent(((DossierMedical *) *state)->antecedents), "antecedent 2");
}


/**********************************************************************************************************************/
                                                /*Tests jsonSave*/
/**********************************************************************************************************************/

static int setup_JsonSave(void ** state){
    //On crée un projet
    Medecin * m1 = CreerMedecin("NomTestM1", "PrenomTestM1", "test@adresseMailM1", "testNumeroTelephoneM1", "NumRPSM1");
    Medecin * m2 = CreerMedecin("NomTestM2", "PrenomTestM2", "test@adresseMailM2", "testNumeroTelephoneM2", "NumRPSM2");

    ListMedecin * workingMedecins = CreerListMedecin();
    ListMedecin_add(workingMedecins, m1);
    ListMedecin_add(workingMedecins, m2);

    Patient * p1 = CreerPatient("NomTestP1", "PrenomTestP1", 1111, 01, 01, "test@adresseMailP1", "testNumeroTelephoneP1", "testNumSecuP1");
    Patient * p2 = CreerPatient("NomTestP2", "PrenomTestP2", 2222, 02, 02, "test@adresseMailP2", "testNumeroTelephoneP2", "testNumSecuP2");

    ListPatient * consultingPatients = CreerListPatient();
    ListPatient_add(consultingPatients, p1);
    ListPatient_add(consultingPatients, p2);

    RendezVous * rdv1 = CreerRendezVous(2001, 01, 01, 8, 60, "lieu1", p1, m1, "motif1");
    RendezVous * rdv2 = CreerRendezVous(2001, 02, 02, 9, 120, "lieu2", p2, m2, "motif2");
    RendezVous * rdv3 = CreerRendezVous(2021, 01, 01, 10, 180, "lieu3", p2, m1, "motif3");
    RendezVous * rdv4 = CreerRendezVous(2021, 01, 03, 11, 240, "lieu4", p1, m2, "motif4");

    Calendrier c = CreerCalendrier();

    AddRendezVous_Calendrier(c, rdv1);
    AddRendezVous_Calendrier(c, rdv2);
    AddRendezVous_Calendrier(c, rdv3);
    AddRendezVous_Calendrier(c, rdv4);

    Ordonnance * o1 = CreerOrdonnance(m1, "descriptionOrdonnance1");
    Ordonnance * o2 = CreerOrdonnance(m2, "descriptionOrdonnance2");
    Ordonnance * o3 = CreerOrdonnance(m1, "descriptionOrdonnance3");

    AddOrdonnanceDossierMedical(p1->dossierMedical, o1);
    AddOrdonnanceDossierMedical(p1->dossierMedical, o2);
    AddOrdonnanceDossierMedical(p2->dossierMedical, o3);

    ListAntecedent_add(p1->dossierMedical->antecedents, "antecedent1P1");
    ListAntecedent_add(p1->dossierMedical->antecedents, "antecedent2P1");
    ListAntecedent_add(p2->dossierMedical->antecedents, "antecedent1P2");
    ListAntecedent_add(p2->dossierMedical->antecedents, "antecedent2P2");

    Project_GPCalendar* p = CreerProject("nomProjetTest", workingMedecins, consultingPatients, c);

    *state = p;
    return *state == NULL;
}
static int teardown_JsonSave(void ** state){
    freeProject((Project_GPCalendar*) *state);
    return 0;
}
static void testJsonSave_GPCalendar_saveProject(void ** state){
    printProject((Project_GPCalendar*) *state);
    assert_int_equal(GPCalendar_saveProject("CefichierEstUnTestdeSaveGPCalendarJson.json", (Project_GPCalendar*) *state), 1);
}

static void testJsonSave_GPCalendar_loadProject(void ** state){
    Project_GPCalendar* p = GPCalendar_loadProject("CefichierEstUnTestdeSaveGPCalendarJson.json");
    printProject(p);
    assert_int_equal(GPCalendar_saveProject("CefichierEstUnTestdeLoadGPCalendarJson.json", p), 1);
    freeProject(p);
}

/**********************************************************************************************************************/
                                            /*Main : Appel des Tests*/
/**********************************************************************************************************************/

int main(void){

    const struct CMUnitTest tests_fonctionsPatient[] = {
            cmocka_unit_test(testPatient_creerPatient),
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

    const struct CMUnitTest tests_RendezVousValable[] = {
            cmocka_unit_test(testCalendrier_RendezVousValable_handlesRDVValable_DateDiff),
            cmocka_unit_test(testCalendrier_RendezVousValable_handlesRDVValable_MemeJour),
            cmocka_unit_test(testCalendrier_RendezVousValable_handlesRDVpasValable_MemeHeureMemeMedecin),
            cmocka_unit_test(testCalendrier_RendezVousValable_handlesRDVpasValable_HeureChevaucheMemeMedecin),
            cmocka_unit_test(testCalendrier_RendezVousValable_handlesRDVpasValable_MemeHeureMemePatient),
            cmocka_unit_test(testCalendrier_RendezVousValable_handlesRDVpasValable_MemeHeureMemeLieu),
    };

    const struct CMUnitTest tests_fonctionsCalendrier2[] = {
            cmocka_unit_test(testCalendrier_AnnulerRendezVous_Calendrier_handlesRdvAnnule_PasAutresRDVPatientMedecin),
            cmocka_unit_test(testCalendrier_AnnulerRendezVous_Calendrier_handlesRdvAnnule_AutreRDVPatientMedecin),
            cmocka_unit_test(testCalendrier_AnnulerRendezVous_Calendrier_handlesRdvPasse),
            cmocka_unit_test(testCalendrier_DeplacerRendezVous),
    };

    const struct CMUnitTest tests_fonctionsDate[] = {
            cmocka_unit_test(testDate_creerDate),
            cmocka_unit_test(testDate_creerDateCourante),
            cmocka_unit_test(testDate_AjoutMoisDate),
            cmocka_unit_test(testDate_getJourDate),
            cmocka_unit_test(testDate_getMoisDate),
            cmocka_unit_test(testDate_getAnneeDate),
            cmocka_unit_test(testDate_getInfosDate),
            cmocka_unit_test(testDate_DateEgaleshandlesDatesDiff),
            cmocka_unit_test(testDate_DateEgaleshandlesDatesEgales),
            cmocka_unit_test(testDate_DateEgaleshandlesDateNULL),
    };

    const struct CMUnitTest tests_fonctionsOrdonnance[] = {
            cmocka_unit_test(testOrdonnance_creerOrdonnance),
            cmocka_unit_test(testOrdonnance_modifierOrdonnance),
    };

    const struct CMUnitTest tests_fonctionsDossierMedical[]={
        cmocka_unit_test(testDossierMedical_AddOrdonnanceDossierMedical_handlesOrdonnanceAdded),
        cmocka_unit_test(testDossierMedical_AddAntecedentsDossierMedical_handlesAntecedentAdded),
        cmocka_unit_test(testDossierMedical_AddAntecedentsDossierMedical_handlesAntecedentAdded2),
    };

    const struct CMUnitTest tests_fonctionsJsonSave[] = {
            cmocka_unit_test(testJsonSave_GPCalendar_saveProject),
            cmocka_unit_test(testJsonSave_GPCalendar_loadProject)
    };

    printf("\033[34;01m\n****************************** Running Patient Tests ******************************\n\n\033[00m");
    int return_cmocka_P = cmocka_run_group_tests(tests_fonctionsPatient, setup_Patient, teardown_Patient);
    printf("\033[34;01m\n****************************** Running Medecin Tests ******************************\n\n\033[00m");
    int return_cmocka_M = cmocka_run_group_tests(tests_fonctionsMedecin, setup_Medecin, teardown_Medecin);
    printf("\033[34;01m\n***************************** Running Calendrier Tests N°1 *****************************\n\n\033[00m");
    int return_cmocka_C1 = cmocka_run_group_tests(tests_fonctionsCalendrier, setup_Calendrier, teardown_Calendrier);
    printf("\033[34;01m\n***************************** Running RendezVous_Valable Tests *****************************\n\n\033[00m");
    int return_cmocka_RDV = cmocka_run_group_tests(tests_RendezVousValable, setup_RdvValable, teardown_RdvValable);
    printf("\033[34;01m\n***************************** Running Calendrier Tests N°2 *****************************\n\n\033[00m");
    int return_cmocka_C2 = cmocka_run_group_tests(tests_fonctionsCalendrier2, setup_Calendrier2, teardown_Calendrier2);
    printf("\033[34;01m\n***************************** Running Date Tests *****************************\n\n\033[00m");
    int return_cmocka_D = cmocka_run_group_tests(tests_fonctionsDate, setup_Date, teardown_Date);
    printf("\033[34;01m\n***************************** Running Ordonnance Tests *****************************\n\n\033[00m");
    int return_cmocka_O = cmocka_run_group_tests(tests_fonctionsOrdonnance, setup_Ordonnance, teardown_Ordonnance);
    printf("\033[34;01m\n***************************** Running DossierMedical Tests *****************************\n\n\033[00m");
    int return_cmocka_DM = cmocka_run_group_tests(tests_fonctionsDossierMedical, setup_DossierMedical, teardown_DossierMedical);
    printf("\033[34;01m\n***************************** Running JsonSave Tests *****************************\n\n\033[00m");
    int return_cmocka_J = cmocka_run_group_tests(tests_fonctionsJsonSave, setup_JsonSave, teardown_JsonSave);

    //Appeler plusieurs cmocka_run_group_tests() dans le return ne marche pas, il execute seulement le premier donc je passe par des int temporaires
    return  return_cmocka_P && return_cmocka_M && return_cmocka_C1 && return_cmocka_RDV && return_cmocka_C2 && return_cmocka_D && return_cmocka_O && return_cmocka_DM && return_cmocka_J;

}
