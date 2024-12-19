#include <gtk/gtk.h>


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
