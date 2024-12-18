#include <gtk/gtk.h>

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
                                        
