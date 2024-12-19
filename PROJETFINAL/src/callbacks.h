#include <gtk/gtk.h>
void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonverif_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data);



void
on_button29_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_AFFICHER_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualisersalma_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_retoursalma_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview22_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview11_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonup_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_search_downup_clicked               (GtkButton       *button,
                                        gpointer         user_data);
                                        
                                        void
on_b_button_mesavisreclam_clicked      (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_classements_clicked        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_ajoutavisreclam_clicked    (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_soumajout_clicked          (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_retourajout_clicked        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_checkbutton_ajoutanonymat_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_radiobutton_ajouterneg_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_radiobutton_ajouterneu_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_radiobutton_ajouterpos_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_treeview_mesavis_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_b_button_actualisermesavis_clicked  (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_modifieravis_clicked       (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_supprimeravis_clicked      (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_radiobutton_modifpos_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_checkbutton_modifanonymat_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_button_retourmodif_clicked        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_enregistrermodif_clicked   (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_radiobutton_modifneg_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_radiobutton_modifneu_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void on_b_treeview_classements_row_activated( GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);

void
on_b_button_retourclass_clicked        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_b_button_retouravispark_clicked     (GtkWidget       *widget,
                                        gpointer         user_data);
                                        
                                        void
on_login_clicked                       (GtkWidget       *button,
                                        gpointer         user_data);

void
on_signin_clicked                      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_Valider_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_Homme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_ModifierCompte_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_ReserverParking_clicked             (GtkWidget       *button,
                                        gpointer         user_data);

void
on_SupprimerCmpt_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_Enregistrer_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_actualiser_clicked                  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_chercher_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);
                                        
             void on_butajouter_clicked (GtkButton  *button, gpointer  user_data);
void on_but1modifier_clicked(GtkButton *button, gpointer user_data);
void on_butsupprimer_clicked (GtkButton *button, gpointer user_data);
void on_butajouteragent_clicked(GtkButton *button, gpointer user_data);
void on_buttafficher_clicked (GtkButton *button,gpointer user_data);
void on_butaffecter__clicked (GtkButton  *button,gpointer user_data);
void on_butaffecter_clicked (GtkWidget *objet, gpointer user_data);
void on_buttonajoutprecedent_clicked(GtkButton *button, gpointer user_data);
void on_buttonmodifprecedent_clicked(GtkButton *button,gpointer user_data);
void on_buttonaffichageprecent_clicked (GtkButton *button,gpointer user_data);
void on_buttongereraffectationprecedent__clicked(GtkButton *button, gpointer user_data);
void on_buttonajouterparking_clicked (GtkButton       *button,
                                        gpointer         user_data);
void
on_buttonsupprimerprecedent_clicked    (GtkButton       *button,
                                        gpointer         user_data);
void
on_buttonmodifierparking_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonsupprimerparking_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonafficherparking_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button43_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttongereraffectation__clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttongereraffectationafficher_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttongereraffecterunagent__clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttongereraffecterunagent__clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonafficher2_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonaffichagajouter_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonaffichagemodif_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonaffichagesupprimer_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonaaficherajout__clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonafficheraffectationsupprimr_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonafficheraffectationmodifier__clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_affecterprecedent__clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data);


void
on_button44_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonadministrateur_clicked        (GtkButton       *button,
                                        gpointer         user_data);


void
on_buttonnouveaucitoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonparking_clicked               (GtkButton       *button,
                                        gpointer         user_data);


void
on_button_add_citoyen_clicked          (GtkButton       *button,
                                        gpointer         user_data);


void
on_del_citoyen_clicked                  (GtkButton       *button,
                                        gpointer         user_data);


void
on_boutton_afficher_citoyen_clicked    (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_supprimer_espace_citoyen_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_modifier_espace_citoyen_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_home_ajout_client_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_home_supprimer_citoyen_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_home_afficher_citoyen_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_home_calculer_facture_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_home_modifier_citoyen_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_espace_calculer_facture_clicked     (GtkButton       *button,
                                        gpointer         user_data);


void
on_saveupdate_clicked                  (GtkButton       *button,
                                        gpointer         user_data);


void
on_button_login_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonanciencitoyen_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_login_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_init_clicked                 (GtkButton       *button,
                                        gpointer         user_data);


void
on_deconect_espace_citoyen_clicked     (GtkButton       *button,
                                        gpointer         user_data);


void
on_cnx_loginadmin_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_admin_init_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_retour_ladmincitoyen_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_ajout_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_dcnx_du_calcul_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_retour_ladmincitoyen_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_deconect_espace_citoyen_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_ajout_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_cnx_loginadmin_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_admin_init_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_dcnx_du_calcul_clicked              (GtkButton       *button,
                                        gpointer         user_data);
void
on_Affiche_clicked                     (GtkButton       *button,
                                        gpointer         user_data);
void
on_deconect_facture_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_login_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_init_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button45_clicked                    (GtkButton       *button,
                                        gpointer         user_data);
void
on_affiche_fact_clicked                (GtkButton       *button,
                                        gpointer         user_data);
void
on_boutton_calculer_fact_clicked       (GtkButton       *button,
                                        gpointer         user_data);
                                        
