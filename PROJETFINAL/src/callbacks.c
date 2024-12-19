#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include <string.h>
#include "support.h"
#include "reservation.h"
#include "ajoutavis.h"
#include "parking.h"
#include "compte.h"

void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *nom, *prenom, *cin, *telephone, *combobox1,  *label71 ,*label51 , *jour , *mois , *annee , *label72;
    char msg[50] = "";  
    int a ,t ;
    reservation r; 
nom = lookup_widget((GtkWidget *)button, "nom");
prenom = lookup_widget((GtkWidget *)button, "prenom");
cin = lookup_widget((GtkWidget *)button, "cin");
telephone = lookup_widget((GtkWidget *)button, "telephone");
combobox1 = lookup_widget((GtkWidget *)button, "combobox1");
mois = lookup_widget((GtkWidget *)button, "mois");
label71 = lookup_widget((GtkWidget *)button, "label71");
jour = lookup_widget((GtkWidget *)button, "jour");
annee = lookup_widget((GtkWidget *)button, "annee");

strcpy(r.client_info.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(r.client_info.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(r.client_info.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
strcpy(r.client_info.num_telephone, gtk_entry_get_text(GTK_ENTRY(telephone)));
r.date_reservation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
r.date_reservation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
r.date_reservation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
	char id_text[50];    
    	r.id = rand() % 10000 + 1;
   	 sprintf(id_text, "%d", r.id);
   	 label51 = lookup_widget((GtkWidget *)button, "label51");
   	 gtk_label_set_text(GTK_LABEL(label51),id_text);
	
const gchar *selected_text_combobox1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1));
if (selected_text_combobox1 != NULL) {
    strcpy(r.nom_parking, selected_text_combobox1);
} else {
    strcpy(r.nom_parking, "Inconnu"); 
}

    		t=ajouter_reservation("reservation.txt",r);
    		if (t)
    			gtk_label_set_text(GTK_LABEL(label71), "votre réservation a été ajouté avec succés \nmerci pour votre confiance 🌟😊 ");
    		else     
			gtk_label_set_text(GTK_LABEL(label71), "echec !");

}






void
on_button_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *id1, *label72;
    int result;
    reservation r;  
    
    id1 = lookup_widget(GTK_WIDGET(button), "id1");  
    label72 = lookup_widget(GTK_WIDGET(button), "label72");  
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id1));  
    r.id = atoi(id_text); 
    if (r.id <= 0) {
        gtk_label_set_text(GTK_LABEL(label72), "ID invalide. Veuillez entrer un ID valide.");
        return;  
    }
    result = supprimer_reservation("reservation.txt", r.id);
    if (result) {
        gtk_label_set_text(GTK_LABEL(label72), "Réservation supprimée avec succès.");
   }else {
        gtk_label_set_text(GTK_LABEL(label72), "Erreur : Réservation introuvée avec cet ID.");
    }
}


void
on_buttonverif_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
char ch1[50], ch2[50];
    int id_tester;
    reservation r;
    
    // Recherche des widgets GTK
    GtkWidget *label190 = lookup_widget(GTK_WIDGET(button), "label190");
    GtkWidget *label200 = lookup_widget(GTK_WIDGET(button), "label200");
    GtkWidget *label210 = lookup_widget(GTK_WIDGET(button), "label210");
    GtkWidget *label220 = lookup_widget(GTK_WIDGET(button), "label220");
    GtkWidget *label230 = lookup_widget(GTK_WIDGET(button), "label230");
    GtkWidget *label240 = lookup_widget(GTK_WIDGET(button), "label240");
   /* GtkWidget *jour = lookup_widget(GTK_WIDGET(button), "jour");
    GtkWidget *mois = lookup_widget(GTK_WIDGET(button), "mois");
    GtkWidget *annee = lookup_widget(GTK_WIDGET(button), "annee");*/

    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button),"entry_id");
    GtkWidget *cin1 = lookup_widget(GTK_WIDGET(button),"cin1");
    GtkWidget *nom2 = lookup_widget(GTK_WIDGET(button),"nom2");
    GtkWidget *prenom1 = lookup_widget(GTK_WIDGET(button),"prenom1");
    GtkWidget *telephone1 = lookup_widget(GTK_WIDGET(button),"telephone1");
    GtkWidget *sannee1 = lookup_widget(GTK_WIDGET(button),"sannee1");
    GtkWidget *sjour1 = lookup_widget(GTK_WIDGET(button),"sjour1");
    GtkWidget *smois1 = lookup_widget(GTK_WIDGET(button),"smois1");
    GtkWidget *parking1 = lookup_widget(GTK_WIDGET(button),"parking1");
    GtkWidget *label270 = lookup_widget(GTK_WIDGET(button),"label270");

    // Récupération de l'ID du client
    id_tester = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    // Recherche de la réservation avec l'ID donné
    reservation r_modif =chercher_for_modif("reservation.txt",id_tester)
;
    g_print("%d", r_modif.id);
    
    if (r_modif.id != id_tester) {
        
        gtk_label_set_text(GTK_LABEL(label270), "Erreur !! : id introuvable ");
        
        // Réinitialisation des champs d'information
        gtk_label_set_text(GTK_LABEL(label190), "");
        gtk_label_set_text(GTK_LABEL(label200), " ");
        gtk_label_set_text(GTK_LABEL(label210), "");
        gtk_label_set_text(GTK_LABEL(label220), "");
        gtk_label_set_text(GTK_LABEL(label230), " ");
        gtk_label_set_text(GTK_LABEL(label240), " ");
        
        // Masquer les champs pour la modification
        gtk_widget_set_visible(nom2, FALSE);
        gtk_widget_set_visible(prenom1, FALSE);
        gtk_widget_set_visible(cin1, FALSE);
        gtk_widget_set_visible(telephone1, FALSE);
        gtk_widget_set_visible(parking1, FALSE);
        gtk_widget_set_visible(sannee1, FALSE);
        gtk_widget_set_visible(sjour1, FALSE);
        gtk_widget_set_visible(smois1, FALSE);
    } else {
        // Si l'ID est trouvé, permettre la modification des informations
        gtk_label_set_text(GTK_LABEL(label270), "Veuillez modifier vos informations");
        
        // Affichage des champs de saisie pour la modification
        gtk_widget_set_visible(nom2, TRUE);
        gtk_widget_set_visible(prenom1, TRUE);
        gtk_widget_set_visible(cin1, TRUE);
        gtk_widget_set_visible(telephone1, TRUE);
        gtk_widget_set_visible(parking1, TRUE);
        gtk_widget_set_visible(sannee1, TRUE);
        gtk_widget_set_visible(sjour1, TRUE);
        gtk_widget_set_visible(smois1, TRUE);
	gtk_widget_set_visible(nom2, TRUE);

        // Mise à jour des labels
        gtk_label_set_text(GTK_LABEL(label190), "Nom");
        gtk_label_set_text(GTK_LABEL(label200), "Prénom");
        gtk_label_set_text(GTK_LABEL(label210), "CIN");
        gtk_label_set_text(GTK_LABEL(label220), "Nom Parking");
        gtk_label_set_text(GTK_LABEL(label230), "Téléphone");
        gtk_label_set_text(GTK_LABEL(label240), "Date de Réservation");
        /*gtk_label_set_text(GTK_LABEL(jour), "Jour");
        gtk_label_set_text(GTK_LABEL(mois), "Mois");
        gtk_label_set_text(GTK_LABEL(annee), "Année");*/

        // Pré-remplir les champs avec les informations existantes
        gtk_entry_set_text(GTK_ENTRY(nom2), r_modif.client_info.nom);
        gtk_entry_set_text(GTK_ENTRY(prenom1), r_modif.client_info.prenom);
        gtk_entry_set_text(GTK_ENTRY(cin1), r_modif.client_info.cin);
        gtk_entry_set_text(GTK_ENTRY(telephone1), r_modif.client_info.num_telephone);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(sannee1), r_modif.date_reservation.annee);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(sjour1), r_modif.date_reservation.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(smois1), r_modif.date_reservation.mois);

        const gchar *selected_text_parking1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(parking1));
        if (selected_text_parking1 != NULL) {
            strcpy(r.nom_parking, selected_text_parking1);
        } else {
            strcpy(r.nom_parking, "Inconnu");
        }
    }
}
void
on_button_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *label270 = lookup_widget(GTK_WIDGET(button), "label270");
    GtkWidget *label260 = lookup_widget(GTK_WIDGET(button), "label260");
    reservation r;
    int id_test;
    // Récupération des champs du formulaire
    GtkWidget *entry_id =lookup_widget(GTK_WIDGET(button), "entry_id");
    GtkWidget *nom2=lookup_widget(GTK_WIDGET(button), "nom2");
    GtkWidget *prenom1 =lookup_widget(GTK_WIDGET(button), "prenom1");
    GtkWidget *cin1 = lookup_widget(GTK_WIDGET(button), "cin1");
    GtkWidget *telephone1 = lookup_widget(GTK_WIDGET(button), "telephone1");
    GtkWidget *sannee1 = lookup_widget(GTK_WIDGET(button), "sannee1");
    GtkWidget *sjour1 = lookup_widget(GTK_WIDGET(button), "sjour1");
    GtkWidget *smois1 = lookup_widget(GTK_WIDGET(button), "smois1");
    GtkWidget *parking1 = lookup_widget(GTK_WIDGET(button), "parking1");

    // Récupération de l'ID de la réservation
    id_test = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));

    // Mise à jour des informations de la réservation
    strcpy(r.client_info.nom, gtk_entry_get_text(GTK_ENTRY(nom2)));
    strcpy(r.client_info.prenom, gtk_entry_get_text(GTK_ENTRY(prenom1)));
    strcpy(r.client_info.cin, gtk_entry_get_text(GTK_ENTRY(cin1)));
    strcpy(r.client_info.num_telephone, gtk_entry_get_text(GTK_ENTRY(telephone1)));
    r.date_reservation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sjour1));
    r.date_reservation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sannee1));
    r.date_reservation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(smois1));
    r.id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));

    // Récupérer le parking sélectionné
    const gchar *selected_text_parking1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(parking1));
    if (selected_text_parking1 != NULL) {
        strcpy(r.nom_parking, selected_text_parking1);
    } else {
        strcpy(r.nom_parking, "Inconnu");
    }

    
    int a = modifier_reservation("reservation.txt",r.id,r);
    if (a) {
        gtk_label_set_text(GTK_LABEL(label260), "votre réservation a été ajouté avec succés \nmerci pour votre confiance 🌟😊");
    } else {
        gtk_label_set_text(GTK_LABEL(label260), "Échec de la modification !");
    }
}





void
on_AFFICHER_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
g_print("Le bouton AFFICHER a été cliqué.\n");
    GtkWidget *AFFICHER = GTK_WIDGET(button);
    GtkWidget *parent_window = gtk_widget_get_parent(AFFICHER);
    GtkWidget *tree_view = lookup_widget(parent_window, "treeview22");

    if (!tree_view) {
        g_print("Erreur : TreeView non trouvé.\n");
        return;
    }
    parking p ;
    afficher_parkings(tree_view);
}


void
on_actualisersalma_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
g_print("Le bouton Actualisersalma a été cliqué.\n");
    GtkWidget *actualisersalma = GTK_WIDGET(button);
    GtkWidget *parent_window = gtk_widget_get_parent(actualisersalma);
    GtkWidget *tree_view = lookup_widget(parent_window, "treeview11");

    if (!tree_view) {
        g_print("Erreur : TreeView non trouvé.\n");
        return;
    }
    afficher_reservation(tree_view);
}


void
on_retoursalma_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}




void on_treeview22_row_activated(GtkTreeView *treeview,
                                  GtkTreePath *path,
                                  GtkTreeViewColumn *column,
                                  gpointer user_data) {

}


#define COLUMN_ID 5  // Update to match the actual column index for `ID RESERVATION`

void on_treeview11_row_activated(GtkTreeView *treeview,
                                 GtkTreePath *path,
                                 GtkTreeViewColumn *column,
                                 gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;
    int id;  // To store the ID RESERVATION

    // Get the model from the treeview
    model = gtk_tree_view_get_model(treeview);

    // Check if the row at the activated path exists
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Get the value of ID RESERVATION from column 5
        gtk_tree_model_get(model, &iter, COLUMN_ID, &id, -1);

        // Debugging: Print the retrieved ID
        g_print("Activated row ID: %d\n", id);

        // Display a confirmation dialog
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Are you sure you want to delete the reservation with ID: %d?", id);

        int response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // If the user confirms deletion
        if (response == GTK_RESPONSE_YES) {
            // Attempt to delete the reservation from the file
            if (supprimer_reservation("reservation.txt", id)) {
                // Remove the row from the treeview model
                gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

                // Display a success dialog
                GtkWidget *success_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Reservation with ID %d has been deleted successfully.", id);

                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);
            } else {
                // Display an error dialog if deletion failed
                GtkWidget *error_dialog = gtk_message_dialog_new(
                    GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_ERROR,
                    GTK_BUTTONS_OK,
                    "Failed to delete reservation with ID: %d. Please try again.", id);

                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        }
    } else {
        g_warning("Failed to retrieve the selected row from the treeview.");
    }
}


GtkSortType selected_sort_order = GTK_SORT_ASCENDING;  // Default to ascending



void on_radiobutton3_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_sort_order = GTK_SORT_ASCENDING;
        g_print("Sort order set to ascending.\n");
    }
}

void on_radiobuttonup_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selected_sort_order = GTK_SORT_DESCENDING;
        g_print("Sort order set to descending.\n");
    }
}



void
on_search_downup_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkBuilder *builder = GTK_BUILDER(user_data);  // GTK Builder passed as user_data
    GtkWidget *tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "treeview11"));  // Retrieve tree_view

    // Debugging: Check if tree_view is valid
    if (!GTK_IS_TREE_VIEW(tree_view)) {
        g_warning("Error: tree_view is not a valid GtkTreeView.");
        return;
    }

    g_print("TreeView valid: %p\n", tree_view);

    // Call the function to display sorted reservations
    afficher_reservation_triee(tree_view, selected_sort_order);
}

int modif_anonymat = 0; int modif_experience = 0;
int anonymat = 0;int experience = 0; 
avis avis_temp;

void on_b_button_mesavisreclam_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_mesaviswindow;
    GtkWidget *treeview;
    GtkWidget *output; 
    GtkListStore *store;
    GtkTreeIter iter;
    avis a;
    FILE *f;
    char user[50] = "badis_beji"; // Utilisateur actuel
    char resultat[100];
    int res = SUCCESS;  

    
    b_mesaviswindow = create_b_mesaviswindow();
    gtk_widget_show(b_mesaviswindow);


    treeview = lookup_widget(b_mesaviswindow, "b_treeview_mesavis");
    output = lookup_widget(b_mesaviswindow, "b_res_mesavis");

    store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);

    f = fopen("avis.txt", "r");
    if (f == NULL) {
        res = ERROR_FILE_OPEN;
        debug(resultat, res); 
        gtk_label_set_text(GTK_LABEL(output), resultat); 
        return;
    }
	
    int avis_count = 0;
    while (fscanf(f, "%s \"%[^\"]\" %s %f %d %d", a.user, a.text, a.parking, &a.note, &a.experience, &a.anonymat) != EOF) {
        if (strcmp(a.user, user) == 0) {
            gtk_list_store_append(store, &iter);
                    gchar *formatted_note = g_strdup_printf("%.1f", a.note);

            gtk_list_store_set(store, &iter,
                               0, a.user,
                               1, a.text,
                               2, a.parking,
                               3, formatted_note,
                               4, a.experience,
                               5, a.anonymat,
                               -1);
	g_free(formatted_note);
            avis_count++;
        }
    }
    fclose(f);

    if (avis_count == 0) {
        res = ERROR_DOESNT_EXIST; 
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    g_object_unref(store);

    if(res==SUCCESS)strcpy(resultat,"Liste d'avis chargée avec succés");


    gtk_label_set_text(GTK_LABEL(output), resultat);
    GtkCellRenderer *renderer;

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                -1, "Utilisateur", renderer,
                                                "text", 0,
                                                NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                -1, "Texte", renderer,
                                                "text", 1,
                                                NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                -1, "Parking", renderer,
                                                "text", 2,
                                                NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                -1, "Note", renderer,
                                                "text", 3,
                                                NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                -1, "Expérience", renderer,
                                                "text", 4,
                                                NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                -1, "Anonymat", renderer,
                                                "text", 5,
                                                NULL);
}




void on_b_button_classements_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_mainwindow;
    GtkWidget *b_classementswindow;
    GtkWidget *treeview;
    GtkWidget *output; 
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    char parking[50];
    float moyenne_note;
    int nombre_notes;
    char resultat[100];
    char moyenne_formatee[10];

    if (!generate_parking_stats("avis.txt", "classements.txt")) {
        strcpy(resultat, "Erreur : Impossible de générer les classements.");
        output = lookup_widget(widget, "b_res_classments");
        gtk_label_set_text(GTK_LABEL(output), resultat);
        return;
    }
    b_mainwindow = lookup_widget(widget, "b_mainwindow");
    b_classementswindow = create_b_classementswindow();
    gtk_widget_show(b_classementswindow);
    //gtk_widget_hide(b_mainwindow);
    treeview = lookup_widget(b_classementswindow, "b_treeview_classements");
    output = lookup_widget(b_classementswindow, "b_res_classments");
    store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    f = fopen("classements.txt", "r");
    if (f == NULL) {
        strcpy(resultat, "Erreur : Impossible d'ouvrir le fichier classements.txt.");
        gtk_label_set_text(GTK_LABEL(output), resultat);
        return;
    }

    while (fscanf(f, "%s %f %d", parking, &moyenne_note, &nombre_notes) != EOF) {
        gtk_list_store_append(store, &iter);
                            gchar *formatted_note = g_strdup_printf("%.1f", moyenne_note);		
        gtk_list_store_set(store, &iter,
                           0, parking,
                           1, formatted_note,
                           2, nombre_notes,
                           -1);
                           g_free(formatted_note);
    }
    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer;

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),-1, "Parking", renderer,"text", 0,NULL);

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),-1, "Moyenne Note", renderer,"text", 1,NULL);
        
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),-1, "Nombre Notes", renderer,"text", 2,NULL);
    }
    strcpy(resultat, "Classements chargés avec succès !");
    gtk_label_set_text(GTK_LABEL(output), resultat);
}

void on_b_button_ajoutavisreclam_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_mainwindow;
    GtkWidget *b_ajoutaviswindow;
    GtkWidget *combobox;
    FILE *f;
    char ligne[256];
    b_mainwindow = lookup_widget(widget, "b_mainwindow");
    b_ajoutaviswindow = create_b_ajoutaviswindow();

    combobox = lookup_widget(b_ajoutaviswindow, "b_combox_parklisteajout");

   f = fopen("parkings.txt", "r");
    if (f != NULL) {
        while (fgets(ligne, sizeof(ligne), f)) {
            ligne[strcspn(ligne, "\n")] = '\0';
            gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), ligne);
        }
        fclose(f);
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), 0);

    gtk_widget_show(b_ajoutaviswindow);
    //gtk_widget_hide(b_mainwindow); 
}



void on_b_button_soumajout_clicked(GtkWidget *widget, gpointer user_data)
{GtkWidget *txt,*n,*park,*output ;
char text[300];
char parking[50];
char user[20]="badis_beji";
float note;
char resultat[100];int res;

txt = lookup_widget(widget, "b_entry_ajout") ;
output= lookup_widget(widget, "b_res_ajoutavis") ;
park=lookup_widget(widget, "b_combox_parklisteajout") ;
n = lookup_widget(widget, "b_spinbutton_ajoutnote");

strcpy(text,gtk_entry_get_text(GTK_ENTRY(txt))); 
strcpy(parking,gtk_combo_box_get_active_text(GTK_COMBO_BOX(park)));
note = gtk_spin_button_get_value(GTK_SPIN_BUTTON(n));

int v=1;

    if(strlen(parking)>50) v= ERROR_ENTRY ;
    if(note>5 || note<0) v= ERROR_ENTRY;
    if(experience>1 || experience<-1) v= ERROR_ENTRY;
    if(strlen(text)>MAX_TEXT_LENGTH) v= ERROR_TEXT_TOO_LONG;
    if(strlen(text)<2) v= 66;
if(v==1){
avis a;
strcpy(a.user, user);
strcpy(a.text, text);
strcpy(a.parking,parking);
a.note=note;
a.experience=experience;
a.anonymat=anonymat;
v=ajout_avis("avis.txt", a);}
debug(resultat,v);
gtk_label_set_text(GTK_LABEL(output),resultat);

}


void on_b_button_retourajout_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_ajoutaviswindow;
    GtkWidget *b_mainwindow;

    b_ajoutaviswindow = lookup_widget(GTK_WIDGET(widget), "b_ajoutaviswindow");
   // b_mainwindow = lookup_widget(GTK_WIDGET(widget), "b_mainwindow");

	//   gtk_widget_show(b_mainwindow);
    gtk_widget_destroy(b_ajoutaviswindow);

}


void on_b_checkbutton_ajoutanonymat_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        anonymat = 1; 
    } else {
        anonymat = 0;
    }
}


void on_b_radiobutton_ajouterneg_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        experience = -1;
    }
}

void on_b_radiobutton_ajouterneu_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        experience = 0; 
    }
}

void on_b_radiobutton_ajouterpos_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        experience = 1; 
    }
}

void on_b_treeview_mesavis_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {

        gchar *user;
        gchar *text;
        gchar *parking;
        gfloat note;
        gint experience;
        gint anonymat;

        gtk_tree_model_get(model, &iter,
                           0, &user,
                           1, &text,
                           2, &parking,
                           3, &note,
                           4, &experience,
                           5, &anonymat,
                           -1);

        strcpy(avis_temp.user, user);
        strcpy(avis_temp.text, text);
        strcpy(avis_temp.parking, parking);
        avis_temp.note = note;
        avis_temp.experience = experience;
        avis_temp.anonymat = anonymat;

        g_free(user);
        g_free(text);
        g_free(parking);
    }

}


void on_b_button_actualisermesavis_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *treeview;
    GtkWidget *output; 
    GtkTreeModel *model;
    GtkListStore *store;
    GtkTreeIter iter;
    avis a;
    FILE *f;
    char user[50] = "badis_beji"; // Utilisateur actuel
    char resultat[100];
    int res = SUCCESS;  

    treeview = lookup_widget(widget, "b_treeview_mesavis");
    output = lookup_widget(widget, "b_res_mesavis");
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    if (model != NULL) {
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    } else {

        store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    }

    f = fopen("avis.txt", "r");
    if (f == NULL) {
        res = ERROR_FILE_OPEN; 
        debug(resultat, res); 
        gtk_label_set_text(GTK_LABEL(output), resultat); 
        return;
    }


    int avis_count = 0;
    while (fscanf(f, "%s \"%[^\"]\" %s %f %d %d", a.user, a.text, a.parking, &a.note, &a.experience, &a.anonymat) != EOF) {
        if (strcmp(a.user, user) == 0) {
            gtk_list_store_append(store, &iter);
                    gchar *formatted_note = g_strdup_printf("%.1f", a.note);

            gtk_list_store_set(store, &iter,
                               0, a.user,
                               1, a.text,
                               2, a.parking,
                               3, formatted_note,
                               4, a.experience,
                               5, a.anonymat,
                               -1);
		g_free(formatted_note);
            avis_count++;
        }
    }
    fclose(f);

    if (avis_count == 0) {
        res = ERROR_DOESNT_EXIST; 
    }

    debug(resultat, res);
    gtk_label_set_text(GTK_LABEL(output), resultat);

    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer;

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                    -1, "Utilisateur", renderer,
                                                    "text", 0,
                                                    NULL);

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                    -1, "Texte", renderer,
                                                    "text", 1,
                                                    NULL);

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                    -1, "Parking", renderer,
                                                    "text", 2,
                                                    NULL);

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                    -1, "Note", renderer,
                                                    "text", 3,
                                                    NULL);

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                    -1, "Expérience", renderer,
                                                    "text", 4,
                                                    NULL);

        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                    -1, "Anonymat", renderer,
                                                    "text", 5,
                                                    NULL);
    }

    if (model == NULL) {
        g_object_unref(store);
    }
}
void on_b_button_enregistrermodif_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *txt, *spin_note, *check_anonymat, *output;
    char new_text[200];
    float new_note;
    char resultat[100];
    avis new_avis;
    int res;

    txt = lookup_widget(widget, "b_entry2");
    spin_note = lookup_widget(widget, "b_spinbutton_modifnote");
    check_anonymat = lookup_widget(widget, "b_checkbutton_modifanonymat");
    output = lookup_widget(widget, "b_res_modifavis");
  
    strcpy(new_text, gtk_entry_get_text(GTK_ENTRY(txt)));
    new_note = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_note));
    strcpy(new_avis.user, avis_temp.user);
    strcpy(new_avis.text, new_text);
    strcpy(new_avis.parking, avis_temp.parking);
    new_avis.note = new_note;
    new_avis.experience = modif_experience;
    new_avis.anonymat = modif_anonymat;



    res = modifier_avis("avis.txt", avis_temp, new_avis);
    debug(resultat, res);
    gtk_label_set_text(GTK_LABEL(output), resultat);
    
    	memset(&avis_temp, 0, sizeof(avis_temp));
	modif_experience = 0;
	modif_anonymat = 0;
}

 
void on_b_button_modifieravis_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_modifaviswindow;
    GtkWidget *b_mesaviswindow;
    GtkWidget *txt, *spin_note, *check_anonymat, *radio_neg, *radio_neu, *radio_pos;
    GtkWidget *output; 
    char resultat[100];

    output = lookup_widget(widget, "b_res_mesavis");

    if (strlen(avis_temp.user) == 0) {
        strcpy(resultat, "Erreur : Aucun avis sélectionné !");
        gtk_label_set_text(GTK_LABEL(output), resultat);
        return;
    }
   // b_mesaviswindow = lookup_widget(widget, "b_mesaviswindow");
    b_modifaviswindow = create_b_modifaviswindow();
    gtk_widget_show(b_modifaviswindow);
    //gtk_widget_hide(b_mesaviswindow);

    txt = lookup_widget(b_modifaviswindow, "b_entry2");
    spin_note = lookup_widget(b_modifaviswindow, "b_spinbutton_modifnote");
    check_anonymat = lookup_widget(b_modifaviswindow, "b_checkbutton_modifanonymat");
    radio_neg = lookup_widget(b_modifaviswindow, "b_radiobutton_modifneg");
    radio_neu = lookup_widget(b_modifaviswindow, "b_radiobutton_modifneu");
    radio_pos = lookup_widget(b_modifaviswindow, "b_radiobutton_modifpos");

    gtk_entry_set_text(GTK_ENTRY(txt), avis_temp.text);
    
   // gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_note), avis_temp.note);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_anonymat), avis_temp.anonymat);

    if (avis_temp.experience == -1) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_neg), TRUE);
    } else if (avis_temp.experience == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_neu), TRUE);
    } else if (avis_temp.experience == 1) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_pos), TRUE);
    }
}





void on_b_button_supprimeravis_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *output;
    char resultat[100];
    int res;

    output = lookup_widget(widget, "b_res_mesavis");
    res = supprimer_avis("avis.txt", avis_temp);
    debug(resultat, res);
       if (strlen(avis_temp.user) == 0) 
        strcpy(resultat, "Erreur : Aucun avis sélectionné !");
    gtk_label_set_text(GTK_LABEL(output), resultat);
	memset(&avis_temp, 0, sizeof(avis_temp)); 

    }


void on_b_button_retourmodif_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_modifaviswindow = lookup_widget(widget, "b_modifaviswindow");
    //GtkWidget *b_mesaviswindow = lookup_widget(widget, "b_mesaviswindow");

    gtk_widget_destroy(b_modifaviswindow);  
    //gtk_widget_show(b_mesaviswindow);  

	memset(&avis_temp, 0, sizeof(avis_temp));
	modif_experience = 0;
	modif_anonymat = 0;
    
}


void on_b_checkbutton_modifanonymat_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        modif_anonymat = 1;
    } else {
        modif_anonymat = 0;
    }
}

void on_b_radiobutton_modifneg_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        modif_experience = -1;
    }
}

void on_b_radiobutton_modifneu_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        modif_experience = 0;
    }
}

void on_b_radiobutton_modifpos_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        modif_experience = 1;
    }
}


void on_b_treeview_classements_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *parking;char label[100]="Avis/Reclamation sur le parking: ";
    
    char resultat[100];
    GtkWidget *park;
    GtkWidget *output;
  //  output = lookup_widget(GTK_WIDGET(treeview), "b_res_classements");
    //park= lookup_widget(GTK_WIDGET(treeview),"b_label_avispark");

    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &parking, -1);

        if (avisutilisateurs("avis.txt", parking) == SUCCESS) {
            GtkWidget *b_classementswindow = lookup_widget(GTK_WIDGET(treeview), "b_classementswindow");
            GtkWidget *b_avisdesutilisateurswindow = create_b_avisdesutilisateurswindow();

            GtkWidget *treeview_avis = lookup_widget(b_avisdesutilisateurswindow, "b_treeview_avispark");
            GtkListStore *store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
            GtkTreeIter iter_avis;
            FILE *f_avis;
            char parkingFile[50];
            sprintf(parkingFile, "avis_parking_%s.txt", parking);

            f_avis = fopen(parkingFile, "r");
            if (f_avis != NULL) {
                char user[50], text[200], parking_temp[50];
                float note;
                int experience, anonymat;

                while (fscanf(f_avis, "%s \"%[^\"]\" %s %f %d %d", user, text, parking_temp, &note, &experience, &anonymat) != EOF) {
                    gtk_list_store_append(store, &iter_avis);
                                                gchar *formatted_note = g_strdup_printf("%.1f", note);		
                    gtk_list_store_set(store, &iter_avis,
                                       0, user,
                                       1, text,
                                       2, parking_temp,
                                       3, formatted_note,
                                       4, experience,
                                       5, anonymat,
                                       -1);
                                g_free(formatted_note);
                }
                fclose(f_avis);

                if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview_avis)) == 0) {
                    GtkCellRenderer *renderer;

                    renderer = gtk_cell_renderer_text_new();
                    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_avis),
                                                                -1, "Utilisateur", renderer,
                                                                "text", 0,
                                                                NULL);
                                                                

                    renderer = gtk_cell_renderer_text_new();
                    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_avis),
                                                                -1, "Texte", renderer,
                                                                "text", 1,
                                                                NULL);
                                                                
                                   		    renderer = gtk_cell_renderer_text_new();
                    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_avis),
                                                                -1, "Parking", renderer,
                                                                "text", 2,
                                                                NULL);

                    renderer = gtk_cell_renderer_text_new();
                    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_avis),
                                                                -1, "Note", renderer,
                                                                "text", 3,
                                                                NULL);

                    renderer = gtk_cell_renderer_text_new();
                    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_avis),
                                                                -1, "Expérience", renderer,
                                                                "text", 4,
                                                                NULL);

                    renderer = gtk_cell_renderer_text_new();
                    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview_avis),
                                                                -1, "Anonymat", renderer,
                                                                "text", 5,
                                                                NULL);
                }

                gtk_tree_view_set_model(GTK_TREE_VIEW(treeview_avis), GTK_TREE_MODEL(store));
                g_object_unref(store);

                gtk_widget_show(b_avisdesutilisateurswindow);
            } else {
                strcpy(resultat, "Erreur : Impossible d'ouvrir le fichier des avis pour ce parking.");
            }
        } else {
            strcpy(resultat, "Erreur : Impossible de générer les avis pour ce parking.");
        }

        g_free(parking);
    } else {
        strcpy(resultat, "Erreur : Impossible de récupérer la ligne sélectionnée.");
    }
	//strcat(label,parking);gtk_label_set_text(GTK_LABEL(park), label);
//    gtk_label_set_text(GTK_LABEL(output), resultat);
}


void on_b_button_retourclass_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_classementswindow = lookup_widget(widget, "b_classementswindow");
    GtkWidget *b_mainwindow = lookup_widget(widget, "b_mainwindow");

    gtk_widget_destroy(b_classementswindow);  
   // gtk_widget_show(b_mainwindow);            
}


void on_b_button_retouravispark_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *b_avisdesutilisateurswindow = lookup_widget(widget, "b_avisdesutilisateurswindow");
    GtkWidget *b_classementswindow = lookup_widget(widget, "b_classementswindow");

    gtk_widget_destroy(b_avisdesutilisateurswindow);  
 //   gtk_widget_show(b_classementswindow);          
}

    void on_butajouter_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *idparking, *nomparking, *nbplaces, *capacite, *adresse , *labelparky  , *sortieparking ;
    char idpark[20], nb[20], cap[20], nnpark[50], adr[50];

    idparking = lookup_widget(GTK_WIDGET(button), "idparking");
    nomparking = lookup_widget(GTK_WIDGET(button), "nomparking");
    nbplaces = lookup_widget(GTK_WIDGET(button), "nbplaces");
    capacite = lookup_widget(GTK_WIDGET(button), "capacite");
    adresse = lookup_widget(GTK_WIDGET(button), "adresse");
    sortieparking= lookup_widget(GTK_WIDGET(button), "sortieparking");
  
     strcpy(idpark, gtk_entry_get_text(GTK_ENTRY(idparking)));
    strcpy(nnpark, gtk_entry_get_text(GTK_ENTRY(nomparking)));
    strcpy(nb, gtk_entry_get_text(GTK_ENTRY(nbplaces)));
    strcpy(cap, gtk_entry_get_text(GTK_ENTRY(capacite)));
    strcpy(adr, gtk_entry_get_text(GTK_ENTRY(adresse)));

    if (strlen(idpark) == 0 || strlen(nnpark) == 0 || strlen(nb) == 0 || 
        strlen(cap) == 0 || strlen(adr) == 0) {
        g_warning("Veuillez remplir tous les champs correctement");
       gtk_label_set_text(GTK_LABEL(sortieparking)," Veuillez remplir tous les champs correctement");
         return;
   }
    parking p;
    strcpy(p.id,idpark);
    strcpy(p.nomparking,nnpark);
    strcpy(p.capacite,cap);
    strcpy(p.nbplacesdispo,nb);
    strcpy(p.adresse,adr);


  int x=ajouterparking( p  );
  if (x=0){ 
   g_warning("parking non ajouté ");
    return ; }
  if (x=1) {
    g_warning("parking ajouté avec succées ");
   gtk_label_set_text(GTK_LABEL(sortieparking),"Parking ajouté  avec succées ");
     return ;}
  

}

void on_but1modifier_clicked(GtkButton *button, gpointer user_data) {

 GtkWidget *idmodif, *nommodif, *nbplacesmodif, *capacitemodif, *adressemodif, *modiflabel;
 char idparkmodif[20], nbmodif[20], capmodif[20], nnmodif[50], adrmodif[50] ,nb_str[10],cap_str[10];

    idmodif = lookup_widget(GTK_WIDGET(button), "idmodif");
    nommodif = lookup_widget(GTK_WIDGET(button), "nommodif");
    nbplacesmodif = lookup_widget(GTK_WIDGET(button), "nbplacesmodif");
    capacitemodif = lookup_widget(GTK_WIDGET(button), "capacitemodif");
    adressemodif = lookup_widget(GTK_WIDGET(button), "adressemodif");
     modiflabel= lookup_widget(GTK_WIDGET(button), "modiflabel");
    const gchar *idmodiftext= gtk_combo_box_get_active_text(GTK_COMBO_BOX(idmodif));
     strcpy(idparkmodif,idmodiftext);
    strcpy(nnmodif, gtk_entry_get_text(GTK_ENTRY(nommodif)));
   int nb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbplacesmodif));
   sprintf( nb_str, "%d", nb);
    strcpy(nbmodif,nb_str);
     int cap = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacitemodif));
   sprintf( cap_str, "%d", cap);
    strcpy(capmodif,cap_str);
    strcpy(adrmodif, gtk_entry_get_text(GTK_ENTRY(adressemodif))) ; 

   
    parking nouv ; 
    strcpy(nouv.id,idparkmodif);
    strcpy(nouv.nomparking,nnmodif);
    strcpy(nouv.capacite,capmodif);
    strcpy(nouv.nbplacesdispo,nbmodif);
    strcpy(nouv.adresse,adrmodif);
    int tr  = modifierparking( idparkmodif , nouv  );

     if (tr==0){ 
     g_warning("parking non modifie ");
    return ; }
      if (tr==1) {
    g_warning("parking modifie avec succées ");
      gtk_label_set_text(GTK_LABEL(modiflabel),"Parking modifié avec succées "); 
     return ;}

}

void
on_butsupprimer_clicked (GtkButton *button, gpointer user_data)
{
   GtkWidget *idsupprimer;
   char idparksupp[10];

  
   idsupprimer = lookup_widget(GTK_WIDGET(button), "idsupprimer");

   if (GTK_IS_COMBO_BOX(idsupprimer)) {
       const gchar *idsupprimertext = gtk_combo_box_get_active_text(GTK_COMBO_BOX(idsupprimer));
       if (idsupprimertext != NULL) {
           strcpy(idparksupp, idsupprimertext);
       } else {
           g_warning("Aucun texte sélectionné dans le combo box");
           return;
       }
   }
   
   
   int tr = supprimerparking(idparksupp);
   if (tr == 1) {
       g_warning("Parking supprimé avec succès.");
       return;
   } else {
       g_warning("Échec de la suppression du parking.");
   }
}

void on_butajouteragent_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *idagent, *nomagent, *prenomagent, *calendaragent , *sortieagent ;
    char id[50], nnagent[50], pragent[50];
    agent a;
    guint year, month, day;

    
    idagent = lookup_widget(GTK_WIDGET(button), "idagent");
    nomagent = lookup_widget(GTK_WIDGET(button), "nomagent");
    prenomagent = lookup_widget(GTK_WIDGET(button), "prenomagent");
    calendaragent = lookup_widget(GTK_WIDGET(button), "calendaragent");
    sortieagent= lookup_widget(GTK_WIDGET(button), "sortieagent");
   
     const gchar *idagenttext = gtk_combo_box_get_active_text(GTK_COMBO_BOX(idagent));
     strcpy(id, idagenttext);
      

   
    strcpy(nnagent, gtk_entry_get_text(GTK_ENTRY(nomagent)));
    strcpy(pragent, gtk_entry_get_text(GTK_ENTRY(prenomagent)));

 
    gtk_calendar_get_date(GTK_CALENDAR(calendaragent), &year, &month, &day);
    snprintf(a.date.jour, sizeof(a.date.jour), "%02d", day);
    snprintf(a.date.mois, sizeof(a.date.mois), "%02d", month + 1);  
    snprintf(a.date.annee, sizeof(a.date.annee), "%04d", year);


    if (strlen(id) == 0 || strlen(nnagent) == 0 || strlen(pragent) == 0 ||
        strlen(a.date.jour) == 0 || strlen(a.date.mois) == 0 || strlen(a.date.annee) == 0) {
        g_warning("Veuillez remplir tous les champs correctement.");
	 gtk_label_set_text(GTK_LABEL(sortieagent),"Veuillez remplir tous les champs correctement. ");
        return;
    }

    strcpy(a.idagent, id);
    strcpy(a.nomagent, nnagent);
    strcpy(a.prenomagent, pragent);
    strcpy(a.idparking, ""); 

    
    int x = ajouteragent(a);

    if (x == 0) {
        g_warning("Agent non ajouté.");
        return;
    }
    if (x == 1) {
        g_warning("Agent ajouté avec succès.");
	 gtk_label_set_text(GTK_LABEL(sortieagent),"agent ajouté avec succées ");
        return;
    }
}

void on_butaffecter_clicked(GtkWidget *objet, gpointer user_data) {
    
    GtkWidget *idagentaffecter = lookup_widget(objet,"idagentaffecter"); 
    GtkWidget *idparkingaffecter = lookup_widget(objet,"idparkingaffecter");  
	 GtkWidget *sortieaffecter ; 
    char idaffecter[50], idpaffecter[50];
	sortieaffecter= lookup_widget(GTK_WIDGET(objet), "sortieaffecter");
	 strcpy(idaffecter, gtk_combo_box_get_active_text(GTK_COMBO_BOX(idagentaffecter)));
	g_warning("id ag %s\n", idaffecter);
    if (idaffecter == NULL) {
        g_warning("Aucun agent sélectionné.");
        return;
    }
    


    const gchar *idparkingaffectertext = gtk_combo_box_get_active_text(GTK_COMBO_BOX(idparkingaffecter));
    if (idparkingaffectertext == NULL) {
        g_warning("Aucun parking sélectionné.");
        return;
    }
    strcpy(idpaffecter, idparkingaffectertext);
	g_warning("id park %s\n", idpaffecter);
  
    int x = affecteragent(idaffecter, idpaffecter);

    if (x == 0) {
        g_warning("Agent non affecté.");
	 gtk_label_set_text(GTK_LABEL(sortieaffecter),"agent non affecté  ");
    } else if (x == 1) {
        g_print("Agent affecté avec succès.\n");
	 gtk_label_set_text(GTK_LABEL(sortieaffecter),"agent affecté avec succées ");
    } else {
        g_warning("Erreur inconnue lors de l'affectation de l'agent.");
    }
}



void
on_buttonajoutprecedent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *ajoutdeparking;
ajoutdeparking=lookup_widget(GTK_WIDGET(button),"ajoutdeparking");
 gererparking = create_gererparking ();
gtk_widget_hide(ajoutdeparking);
 gtk_widget_show (gererparking);
}


void
on_buttonsupprimerprecedent_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *supprimerparking;
supprimerparking=lookup_widget(GTK_WIDGET(button),"supprimerparking");
 gererparking = create_gererparking ();
gtk_widget_hide(supprimerparking);
 gtk_widget_show (gererparking);

}


void
on_buttonmodifprecedent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *modifierparking;
modifierparking=lookup_widget(GTK_WIDGET(button),"modifierparking");
 gererparking = create_gererparking ();
gtk_widget_hide(modifierparking);
 gtk_widget_show (gererparking);
}


void
on_buttonaffichageprecent_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
 gererparking = create_gererparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (gererparking);
}


void
on_buttongereraffectationprecedent__clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *gereraffectation_;
gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");
 gererparking = create_gererparking ();
gtk_widget_hide(gereraffectation_);
 gtk_widget_show (gererparking);
}


void
on_buttonajouterparking_clicked (GtkButton       *button, gpointer         user_data)
{

GtkWidget *ajoutdeparking , *gererparking;

gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
ajoutdeparking = create_ajoutdeparking ();


gtk_widget_hide(gererparking);
gtk_widget_show (ajoutdeparking);
}


void
on_buttonmodifierparking_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modifierparking , *gererparking ;
gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
 modifierparking = create_modifierparking ();
gtk_widget_hide(gererparking);
 gtk_widget_show (modifierparking);
}


void
on_buttonsupprimerparking_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *supprimerparking , *gererparking;
gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
 supprimerparking = create_supprimerparking ();
 gtk_widget_hide(gererparking);
 gtk_widget_show (supprimerparking);
}


void
on_buttonafficherparking_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeviewparking;
	GtkWidget *afficherparking; 
	GtkWidget *gererparking ;
	gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
	gtk_widget_hide(gererparking);
	afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking"); 
	afficherparking=create_afficherparking();
	gtk_widget_show(afficherparking);
	treeviewparking=lookup_widget(afficherparking,"treeviewparking");
	afficherparking_(treeviewparking);
}


void
on_button43_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gereraffectation_ , *gererparking;
gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
 gereraffectation_ = create_gereraffectation_ ();
 gtk_widget_hide(gererparking);
 gtk_widget_show (gereraffectation_);
}


void
on_buttongereraffectation__clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *ajoutagent_ , *gereraffectation_;
gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");

ajoutagent_ = create_ajoutagent_ ();
gtk_widget_hide(gereraffectation_);

 gtk_widget_show (ajoutagent_);
}

void
on_buttongereraffectationafficher_clicked(GtkButton *button,gpointer user_data)
{
        GtkWidget *treeview1;
	GtkWidget *afficheraffectation_ ; 
	GtkWidget *gereraffectation_ ;
	gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");
	gtk_widget_hide(gereraffectation_);
	afficheraffectation_ =lookup_widget(GTK_WIDGET(button),"afficheraffectation_"); 
	afficheraffectation_ =  create_afficheraffectation_();
	gtk_widget_show(afficheraffectation_);
	treeview1=lookup_widget(afficheraffectation_ ,"treeview1");
	afficheragent(treeview1); 
}

void
on_buttongereraffecterunagent__clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affecteragent_ , *gereraffectation_;
gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");
 affecteragent_ = create_affecteragent_ ();
gtk_widget_hide(gereraffectation_);
 gtk_widget_show (affecteragent_);
}

void
on_buttonaffichagajouter_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajoutdeparking , *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
ajoutdeparking = create_ajoutdeparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (ajoutdeparking);
}


void
on_buttonaffichagemodif_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modifierparking , *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
 modifierparking = create_modifierparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (modifierparking);
}


void
on_buttonaffichagesupprimer_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *supprimerparking, *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
 supprimerparking = create_supprimerparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (supprimerparking);
}


void
on_buttonaaficherajout__clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajoutagent_ , *afficheraffectation_;
afficheraffectation_=lookup_widget(GTK_WIDGET(button),"afficheraffectation_");

ajoutagent_ = create_ajoutagent_ ();
gtk_widget_hide(afficheraffectation_);

 gtk_widget_show (ajoutagent_);
}





void
on_affecterprecedent__clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affecteragent_ , *gereraffectation_;
affecteragent_=lookup_widget(GTK_WIDGET(button),"affecteragent_");
gereraffectation_ = create_gereraffectation_ ();
gtk_widget_hide(affecteragent_);
 gtk_widget_show (gereraffectation_);;
}


void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gereraffectation_;
 gereraffectation_ = create_gereraffectation_ ();
 gtk_widget_show (gereraffectation_);
}


void
on_button44_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajoutagent_ , *gereraffectation_;
ajoutagent_=lookup_widget(GTK_WIDGET(button),"ajoutagent_");
gereraffectation_ = create_gereraffectation_ ();
gtk_widget_hide(ajoutagent_);
 gtk_widget_show (gereraffectation_);

}


void
on_buttonadministrateur_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *admincitoyen, *login;
admincitoyen=lookup_widget(GTK_WIDGET(button),"admincitoyen");
login = create_login ();
gtk_widget_hide(admincitoyen);
 gtk_widget_show (login);
}


void
on_buttonnouveaucitoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen, *ajoutcitoyen_;

	admincitoyen=lookup_widget(GTK_WIDGET(button),"admincitoyen");
	ajoutcitoyen_= create_ajoutclient__ ();

	gtk_widget_hide(admincitoyen);
	gtk_widget_show (ajoutcitoyen_);
}


void
on_buttonparking_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *gerer, *gererparking;

	gerer=lookup_widget(GTK_WIDGET(button),"gerer");
	gererparking = create_gererparking ();

	gtk_widget_hide(gerer);
 	gtk_widget_show (gererparking );
}

void on_button_add_citoyen_clicked(GtkButton *button, gpointer user_data) {
    	GtkWidget *cincitoyen, *prenomcitoyen, *nomcitoyen, *telcitoyen,*ajoutlogin,*ajoutmdp;
	GtkWidget *espace_citoyen,*msg_ajout;
	GtkWidget *ajoutclient_;

    
    char nn[50], pre[50], cin[50], tel[50],msg[50],login[50],mdp[50];
	
	ajoutlogin = lookup_widget(GTK_WIDGET(button), "ajoutlogin");
	ajoutmdp= lookup_widget(GTK_WIDGET(button), "ajoutmdp");
	nomcitoyen = lookup_widget(GTK_WIDGET(button), "nomcitoyen");
	prenomcitoyen = lookup_widget(GTK_WIDGET(button), "prenomcitoyen");
	cincitoyen = lookup_widget(GTK_WIDGET(button), "cincitoyen");
	telcitoyen = lookup_widget(GTK_WIDGET(button), "telcitoyen");
	msg_ajout= lookup_widget(GTK_WIDGET(button), "msg_ajout");

    	strcpy(nn, gtk_entry_get_text(GTK_ENTRY(nomcitoyen)));
    	strcpy(pre, gtk_entry_get_text(GTK_ENTRY(prenomcitoyen)));
    	strcpy(cin, gtk_entry_get_text(GTK_ENTRY(cincitoyen)));
    	strcpy(tel, gtk_entry_get_text(GTK_ENTRY(telcitoyen)));
	strcpy(login, gtk_entry_get_text(GTK_ENTRY(ajoutlogin)));
    	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(ajoutmdp)));

    	if (strlen(nn) == 0 || strlen(pre) == 0 || strlen(cin) == 0 || strlen(tel) == 0||strlen(login)==0 			||strlen(mdp)==0) {
        gtk_label_set_text(GTK_LABEL(msg_ajout),"veuillez remplir tout les champs");
    		}

    	else{
		Citoyen citoyen;
		strcpy(citoyen.login,login);
    		strcpy(citoyen.mdp,mdp);
    		strcpy(citoyen.id, cin);
    		strcpy(citoyen.nom, nn);
    		strcpy(citoyen.prenom, pre);
    		strcpy(citoyen.tel, tel);

    		int result = ajouterProfil("citoyen.txt",citoyen);
    		if (result == 1) {
   				gtk_label_set_text(GTK_LABEL(msg_ajout),"Félicitation! vous etes bien 	inscrit");

    				}
		}
}



void
on_saveupdate_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *updatenom,*updateprenom,*updatetel,*updateid,*updatesortie,*update_username,*edit_mdp;
	
	char nn[50],pre[50],tel[8],id[50],user[50],mdp[50];
	
	updatenom = lookup_widget(GTK_WIDGET(button), "updatenom");
    	updateprenom= lookup_widget(GTK_WIDGET(button), "updateprenom");
    	updatetel= lookup_widget(GTK_WIDGET(button), "updatetel");
    	updatesortie= lookup_widget(GTK_WIDGET(button), "updatesortie");
	updateid= lookup_widget(GTK_WIDGET(button), "updateid");
	update_username=lookup_widget(GTK_WIDGET(button), "update_username");
	edit_mdp= lookup_widget(GTK_WIDGET(button), "edit_mdp");
	
	
	
	strcpy(nn, gtk_entry_get_text(GTK_ENTRY(updatenom)));
    	strcpy(pre, gtk_entry_get_text(GTK_ENTRY(updateprenom)));
    	strcpy(tel, gtk_entry_get_text(GTK_ENTRY(updatetel)));
	strcpy(id, gtk_entry_get_text(GTK_ENTRY(updateid)));
	strcpy(user, gtk_entry_get_text(GTK_ENTRY(update_username)));
	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(edit_mdp)));
	
	if (strlen(nn) == 0 || strlen(pre) == 0 || strlen(tel) == 0  || strlen(user) == 0  || strlen(mdp) == 0 )
	{
		gtk_label_set_text(GTK_LABEL(updatesortie),"veuillez remplir tout les champs");
	}
	else
	{
		Citoyen modifier;
		strcpy(modifier.nom,nn);
		strcpy(modifier.prenom,pre);
		strcpy(modifier.tel,tel);
		strcpy(modifier.login,user);
		strcpy(modifier.mdp,mdp);
		strcpy(modifier.id,id);
		if (chercherprofil("citoyen.txt",id)==1)
		{
			modifierProfil("citoyen.txt",id,modifier);
			gtk_label_set_text(GTK_LABEL(updatesortie),"modification faite avec succées");
		}
		else
		{gtk_label_set_text(GTK_LABEL(updatesortie),"id incorrecte");}
	
    	}
}


void
on_del_citoyen_clicked                  (GtkButton       *button,
                                        gpointer         user_data){

	GtkWidget *del_id ,*checkbox_sur,*del_out;
	GtkWidget *admincitoyen, *suppressioncitoyen;

	char id[50];

	del_id= lookup_widget(GTK_WIDGET(button), "del_id");
	checkbox_sur=lookup_widget(GTK_WIDGET(button),"checkbox_sur");
	del_out= lookup_widget(GTK_WIDGET(button), "del_out");
	gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_sur));

	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_sur))){
		gtk_label_set_text(GTK_LABEL(del_out), "veuillez confirmer");}
	else{
		strcpy(id, gtk_entry_get_text(GTK_ENTRY(del_id)));
   
		int x=supprimerProfil("citoyen.txt", id);
		if (x==1) {
			suppressioncitoyen=lookup_widget(GTK_WIDGET(button),"suppressioncitoyen");
			admincitoyen= create_admincitoyen();
			gtk_widget_hide(suppressioncitoyen);
 			gtk_widget_show (admincitoyen);
        
    			}
		 else {
        		gtk_label_set_text(GTK_LABEL(del_out), "Erreur lors de la suppression");
   			 }
			}
}

void
on_boutton_afficher_citoyen_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *afficher_citoyen;
	GtkWidget *espace_citoyen;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	afficher_citoyen=create_afficher_citoyen();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(afficher_citoyen); 

}




void
on_button_supprimer_espace_citoyen_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *suppressioncitoyen;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	suppressioncitoyen = create_suppressioncitoyen();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(suppressioncitoyen);
}


void
on_button_modifier_espace_citoyen_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *espace_citoyen;
GtkWidget *modifiercitoyen;
espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
modifiercitoyen= create_modifiercitoyen();

gtk_widget_hide(espace_citoyen);
gtk_widget_show(modifiercitoyen);
}





void
on_home_supprimer_citoyen_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *suppressioncitoyen;

	suppressioncitoyen=lookup_widget(GTK_WIDGET(button),"suppressioncitoyen");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(suppressioncitoyen);
	gtk_widget_show(espace_citoyen);
}


void
on_home_afficher_citoyen_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *afficher_citoyen;

	afficher_citoyen=lookup_widget(GTK_WIDGET(button),"afficher_citoyen");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(afficher_citoyen);
	gtk_widget_show(espace_citoyen);
}


void
on_home_calculer_facture_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *calculer_facture;

	calculer_facture=lookup_widget(GTK_WIDGET(button),"calculer_facture");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(calculer_facture);
	gtk_widget_show(espace_citoyen);
}


void
on_home_modifier_citoyen_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *modifiercitoyen;

	modifiercitoyen=lookup_widget(GTK_WIDGET(button),"modifiercitoyen");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(modifiercitoyen);
	gtk_widget_show(espace_citoyen);
}


void
on_espace_calculer_facture_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *calculer_facture;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	calculer_facture= create_calculer_facture();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(calculer_facture);
}


void
on_buttonanciencitoyen_clicked         (GtkButton       *button,
                                        gpointer         user_data)

{	
	GtkWidget *admincitoyen,*logincitoyen;

	admincitoyen=lookup_widget(GTK_WIDGET(button),"admincitoyen");
	logincitoyen= create_logincitoyen();

	gtk_widget_hide(admincitoyen);
	gtk_widget_show(logincitoyen);
}


void
on_button_login_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *login_citoyen,*mdp_citoyen,*msg_logincitoyen;
	GtkWidget *espace_citoyen,*logincitoyen;
	
	char login[50],mdp[50];
	
	login_citoyen= lookup_widget(GTK_WIDGET(button), "login_citoyen");
    	mdp_citoyen= lookup_widget(GTK_WIDGET(button), "mdp_citoyen");
	msg_logincitoyen= lookup_widget(GTK_WIDGET(button), "msg_logincitoyen");
	
	strcpy(login, gtk_entry_get_text(GTK_ENTRY(login_citoyen)));
    	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(mdp_citoyen)));
    	if (strlen(login) == 0 || strlen(mdp) == 0  )
	{
		gtk_label_set_text(GTK_LABEL(msg_logincitoyen),"veuillez remplir tout \n les champs correctement!");
	}
	
	int x=verifier_connexion( login, mdp );
	if (x==1){
		logincitoyen=lookup_widget(GTK_WIDGET(button),"logincitoyen");
		espace_citoyen= create_espace_citoyen();

		gtk_widget_hide(logincitoyen);
		gtk_widget_show(espace_citoyen);
		}
	if (x==-1){gtk_label_set_text(GTK_LABEL(msg_logincitoyen),"compte innexsistant");
	}
}


void
on_retour_init_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*logincitoyen;

	logincitoyen=lookup_widget(GTK_WIDGET(button),"logincitoyen");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(logincitoyen);
	gtk_widget_show(admincitoyen);
}


void
on_deconect_espace_citoyen_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*espace_citoyen;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(admincitoyen);
}





void
on_cnx_loginadmin_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *loginadmin,*mdpadmin,*msg_loginadmin;
	GtkWidget *gerer,*login;
	
	char log[50],mdp[50];
	
	loginadmin= lookup_widget(GTK_WIDGET(button), "loginadmin");
    	mdpadmin= lookup_widget(GTK_WIDGET(button), "mdpadmin");
	msg_loginadmin= lookup_widget(GTK_WIDGET(button), "msg_loginadmin");
	
	strcpy(log, gtk_entry_get_text(GTK_ENTRY(loginadmin)));
    	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(mdpadmin)));
    	if (strlen(log) == 0 || strlen(mdp) == 0  )
	{
		gtk_label_set_text(GTK_LABEL(msg_loginadmin),"veuillez remplir tout \n les champs correctement!");
	}
	
	int x=verif_conx_admin( log, mdp );
	if (x==1){
		login=lookup_widget(GTK_WIDGET(button),"login");
		gerer= create_gerer();

		gtk_widget_hide(login);
		gtk_widget_show(gerer);
		}
	if (x==-1){gtk_label_set_text(GTK_LABEL(msg_loginadmin),"compte innexsistant");
	}
}



void
on_retour_admin_init_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*login;
	login=lookup_widget(GTK_WIDGET(button),"login");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(login);
	gtk_widget_show(admincitoyen);
}


void
on_button_retour_ladmincitoyen_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*gerer;
	gerer=lookup_widget(GTK_WIDGET(button),"gerer");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(gerer);
	gtk_widget_show(admincitoyen);
}


void
on_retour_ajout_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *ajoutclient__;

	ajoutclient__=lookup_widget(GTK_WIDGET(button),"ajoutclient__");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(ajoutclient__);
	gtk_widget_show(espace_citoyen);
	gtk_widget_hide(ajoutclient__);
}


void
on_dcnx_du_calcul_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*afficher_citoyen;

	afficher_citoyen=lookup_widget(GTK_WIDGET(button),"afficher_citoyen");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(afficher_citoyen);
	gtk_widget_show(admincitoyen);
}




void
on_button45_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *ajoutagent_ , *affecteragent_;

	ajoutagent_=lookup_widget(GTK_WIDGET(button),"ajoutagent_");
	affecteragent_ = create_affecteragent_ ();

	gtk_widget_hide(ajoutagent_);
	gtk_widget_show (affecteragent_);

}




void
on_boutton_calculer_fact_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *sortie_cout, *mois_facture, *annee_facture, *read_id;
    	int mois, annee;
	char *id;
    	char result[50]; 

	mois_facture = lookup_widget(GTK_WIDGET(button), "mois_facture");
	annee_facture = lookup_widget(GTK_WIDGET(button), "annee_facture");
	read_id = lookup_widget(GTK_WIDGET(button), "read_id");
	sortie_cout = lookup_widget(GTK_WIDGET(button), "sortie_cout");

	mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_facture));
	annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_facture));
	id = (char *)gtk_entry_get_text(GTK_ENTRY(read_id));

    
    	float facture = calculerFactureMensuelle(id, mois, annee);

    	if (facture == -1.0) {
        	snprintf(result, sizeof(result), "Aucune réservation trouvée !");
    			} 
	else {
        	snprintf(result, sizeof(result), "%.2f TND", facture);
	
    		}

    gtk_label_set_text(GTK_LABEL(sortie_cout), result);
}


void
on_deconect_facture_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*calculer_facture;

	calculer_facture=lookup_widget(GTK_WIDGET(button),"calculer_facture");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(calculer_facture);
	gtk_widget_show(admincitoyen);
}


void on_affiche_fact_clicked(GtkButton *button, gpointer user_data) {
	GtkWidget *read_id, *treeviewfact,*msg;
	char id[10];
	GtkTreeIter iter;
	msg= lookup_widget(GTK_WIDGET(button), "msg");
	read_id = lookup_widget(GTK_WIDGET(button), "read_id");
	if (!read_id || !GTK_IS_ENTRY(read_id)) {
	gtk_label_set_text(GTK_LABEL(msg),"invalid id");
		
	    }

	treeviewfact = lookup_widget(GTK_WIDGET(button), "treeviewfact");

	const char *id_text = gtk_entry_get_text(GTK_ENTRY(read_id));
	if (!id_text || strlen(id_text) == 0) {
	gtk_label_set_text(GTK_LABEL(msg),"invalid id");
		
	    }
	strcpy(id, id_text);
	GtkListStore *store = gtk_list_store_new(COLUMNNS, G_TYPE_STRING, G_TYPE_INT, 
G_TYPE_INT,G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

	    gtk_tree_view_set_model(GTK_TREE_VIEW(treeviewfact), GTK_TREE_MODEL(store));

	    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeviewfact)) == 0) {
		GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
		GtkTreeViewColumn *column;

		column = gtk_tree_view_column_new_with_attributes("ID Reservation", renderer, "text", IDRESERVATION, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", MOIS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", JOUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text", ANNEE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Service", renderer, "text", LIBELLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Cout", renderer, "text", COUT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);
	    }

	    FILE *f = fopen("reservations.txt", "r");
	    if (!f) {
		g_warning("Erreur : Impossible d'ouvrir le fichier 'reservations.txt' !");
		return;
	    }

	    char id_reservation[50], idClient[50], idParking[50], nomParking[50], id_park[50], id1[50], service[50], cout[50];
	    int placesDisponibles, mois, jour, annee;

	 
	    gtk_list_store_clear(store);

	    while (fscanf(f, "%s %s %d %d %d %s %d %s %s %s %s %s \n", id_reservation, idClient, &jour, &mois, &annee, idParking, &placesDisponibles, nomParking, id_park, id1, service, cout) != EOF) {
		if (chercherreservation("reservations.txt",id)==1) { 
		    gtk_list_store_append(store, &iter);
		    gtk_list_store_set(store, &iter,IDRESERVATION, id_reservation,MOIS, mois,JOUR, jour,ANNEE, annee,LIBELLE, service,COUT, cout, -1);
		}
	    }

	    fclose(f);

	    gtk_tree_view_set_model(GTK_TREE_VIEW(treeviewfact), GTK_TREE_MODEL(store));
	    g_object_unref(store); 
	}

void on_Affiche_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *afficher_citoyen, *id_affiche, *treeview1, *output;
    char id[10];
    afficher_citoyen = lookup_widget(GTK_WIDGET(button), "afficher_citoyen");
    treeview1 = lookup_widget(afficher_citoyen, "treeview1");
    output = lookup_widget(GTK_WIDGET(button), "output");
    id_affiche = lookup_widget(GTK_WIDGET(button), "id_affiche");


    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id_affiche));
    if (!id_text || strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(output), "ID invalide.");
        return;
    }
    strcpy(id, id_text);

   
    GtkListStore *store = NULL;
    if (GTK_IS_TREE_VIEW(treeview1)) {
        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview1)));
    }
    if (!store) {
        store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview1), GTK_TREE_MODEL(store));
    }


    if (store) {
        gtk_list_store_clear(store);
    }

    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview1)) == 0) {
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Login", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Mot de passe", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);
    }


    FILE *f = fopen("citoyen.txt", "r");
    if (!f) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    char nom[50], prenom[50], tel[30], cin[50], login[50], mdp[50];
    GtkTreeIter iter;
    int found = 0;
    while (fscanf(f, "%s %s %s %s %s %s", login, mdp, nom, prenom, cin, tel) == 6) {
        if (strcmp(id, cin) == 0) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, login,1, mdp,2, cin,3, nom, 4, prenom, 5, tel,-1);
            found = 1;
        }
    }
    fclose(f);

 
    if (!found) {
        gtk_label_set_text(GTK_LABEL(output), "Aucun citoyen trouvé avec cet ID.");
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Citoyen trouvé !");
    }

  
    gtk_widget_show_all(afficher_citoyen);
}

sign_up user_g ;
char sexe_g[50]="";

void
on_login_clicked                       (GtkWidget       *button,
                                        gpointer         user_data)
{
	char user[100]; 
    char mdp[100];
    sign_up result; 

    
    GtkWidget *input1 = lookup_widget(button, "user");
    GtkWidget *input2 = lookup_widget(button, "psw");
    GtkWidget *output = lookup_widget(button, "msg");

    
    if (input1 == NULL || input2 == NULL || output == NULL) {
        g_print("Erreur : widgets non trouvés\n");
        return;
    }

    
    const char *entry_user = gtk_entry_get_text(GTK_ENTRY(input1));
    const char *entry_mdp = gtk_entry_get_text(GTK_ENTRY(input2));


    strcpy(user, entry_user);
    strcpy(mdp, entry_mdp);
	printf("%s \n",user);
	printf("%s \n",mdp);
    
    int test = chercher("compte.txt", user,mdp);

    if (test==1) {
        
            gtk_label_set_text(GTK_LABEL(output), "Connexion réussie");
		GtkWidget *faj,*faf,*tree;
		faj=lookup_widget(button,"window1");
		gtk_widget_destroy(faj);
		faf=lookup_widget(button,"window2");
		gtk_widget_destroy(faf);
		faf=lookup_widget(button,"window2");
		faf=create_window2();
		gtk_widget_show(faf);
		tree=lookup_widget(faf,"treeview");
		afficher_sign_up(tree);;

        }
    if (test==0) {
        gtk_label_set_text(GTK_LABEL(output), "Compte introuvable");
    }
}


void
on_signin_clicked                      (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_Valider_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{
	sign_up s ;
	 GtkWidget *Nom,*Prenom,*Numtelephone,*Adressemail,*Motdepasse,*Verificationmotdepasse,*Jour,*Mois,*An,*Modepaiement;
	 Nom=lookup_widget(button,"Nom");
	 Prenom=lookup_widget(button,"Prenom");
	 Numtelephone=lookup_widget(button,"Numtelephone");
	 Adressemail=lookup_widget(button,"Adressemail");
	 Motdepasse=lookup_widget(button,"Motdepasse");
	 Verificationmotdepasse=lookup_widget(button,"Verificationmotdepasse");
	 Jour=lookup_widget(button,"Jour");
	 Mois=lookup_widget(button,"Mois");
	 An=lookup_widget(button,"An");
	 Modepaiement=lookup_widget(button,"Modepaiement");
	 strcpy(s.Nom, gtk_entry_get_text(GTK_ENTRY(Nom)));
	 strcpy(s.Prenom, gtk_entry_get_text(GTK_ENTRY(Prenom)));
	 strcpy(s.Numtelephone, gtk_entry_get_text(GTK_ENTRY(Numtelephone)));
	 strcpy(s.Adressemail, gtk_entry_get_text(GTK_ENTRY(Adressemail)));
	 strcpy(s.Motdepasse, gtk_entry_get_text(GTK_ENTRY(Motdepasse)));
	 strcpy(s.Verificationmotdepasse, gtk_entry_get_text(GTK_ENTRY(Verificationmotdepasse)));
	 s.d.Jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Jour));
	 s.d.Mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Mois));
	 s.d.An=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(An));
	 strcpy(s.Modepaiement,gtk_combo_box_get_active_text(GTK_COMBO_BOX(Modepaiement)));
	strcpy(s.sexe,sexe_g);
	 ajouter_user("compte.txt",s);
}


void
on_Homme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {  // Vérifie si le bouton est activé
        strcpy(sexe_g, "homme");
    }
}



void
on_Femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {  // Vérifie si le bouton est activé
        strcpy(sexe_g, "femme");
    }
}


void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    GtkTreeIter iter;
    gchar *nom;
    gchar *prenom;
    gchar *numtelephone;
    gchar *date_naissance;
    gchar *modepaiement;
    gchar *sexe;
    gchar *adressemail;
    gchar *motdepasse;
    gchar *verificationmotdepasse;
    extern sign_up user_g; // Déclaration de la variable globale

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Récupération des valeurs de la ligne sélectionnée dans le bon ordre
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
                           0, &nom,
                           1, &prenom,
                           2, &numtelephone,
                           3, &date_naissance,
                           4, &modepaiement,
                           5, &sexe,
                           6, &adressemail,
                           7, &motdepasse,
                           8, &verificationmotdepasse,
                           -1);

        // Copie des valeurs dans la structure sign_up globale
        if (nom) {
            strncpy(user_g.Nom, nom, sizeof(user_g.Nom) - 1);
            user_g.Nom[sizeof(user_g.Nom) - 1] = '\0';
            g_free(nom);
        }

        if (prenom) {
            strncpy(user_g.Prenom, prenom, sizeof(user_g.Prenom) - 1);
            user_g.Prenom[sizeof(user_g.Prenom) - 1] = '\0';
            g_free(prenom);
        }

        if (numtelephone) {
            strncpy(user_g.Numtelephone, numtelephone, sizeof(user_g.Numtelephone) - 1);
            user_g.Numtelephone[sizeof(user_g.Numtelephone) - 1] = '\0';
            g_free(numtelephone);
        }

        if (date_naissance) {
            sscanf(date_naissance, "%d/%d/%d", &user_g.d.Jour, &user_g.d.Mois, &user_g.d.An);
            g_free(date_naissance);
        }

        if (modepaiement) {
            strncpy(user_g.Modepaiement, modepaiement, sizeof(user_g.Modepaiement) - 1);
            user_g.Modepaiement[sizeof(user_g.Modepaiement) - 1] = '\0';
            g_free(modepaiement);
        }

        if (sexe) {
            strncpy(user_g.sexe, sexe, sizeof(user_g.sexe) - 1);
            user_g.sexe[sizeof(user_g.sexe) - 1] = '\0';
            g_free(sexe);
        }

        if (adressemail) {
            strncpy(user_g.Adressemail, adressemail, sizeof(user_g.Adressemail) - 1);
            user_g.Adressemail[sizeof(user_g.Adressemail) - 1] = '\0';
            g_free(adressemail);
        }

        if (motdepasse) {
            strncpy(user_g.Motdepasse, motdepasse, sizeof(user_g.Motdepasse) - 1);
            user_g.Motdepasse[sizeof(user_g.Motdepasse) - 1] = '\0';
            g_free(motdepasse);
        }

        if (verificationmotdepasse) {
            strncpy(user_g.Verificationmotdepasse, verificationmotdepasse, sizeof(user_g.Verificationmotdepasse) - 1);
            user_g.Verificationmotdepasse[sizeof(user_g.Verificationmotdepasse) - 1] = '\0';
            g_free(verificationmotdepasse);
        }
    }
}


void
on_ModifierCompte_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{	

	GtkWidget *fam,*faf;
		faf=lookup_widget(button,"window2");
		gtk_widget_destroy(faf);
		fam=lookup_widget(button,"window3");
		fam=create_window3();
		gtk_widget_show(fam);
	
	
	
	
	
}


void
on_ReserverParking_clicked             (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_SupprimerCmpt_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{
	supprimer_compte("compte.txt", user_g.Adressemail);
}


void
on_Enregistrer_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{
	sign_up s ;
	 GtkWidget *Nom,*Prenom,*Numtelephone,*Adressemail,*Motdepasse,*Verificationmotdepasse,*Jour,*Mois,*An,*Modepaiement;
	 Nom=lookup_widget(button,"ModifNom");
	 Prenom=lookup_widget(button,"ModifPrenom");
	 Numtelephone=lookup_widget(button,"ModifNum");
	 Motdepasse=lookup_widget(button,"Modifpsw");
	 Verificationmotdepasse=lookup_widget(button,"ModifVerif");
	 Jour=lookup_widget(button,"ModifJour");
	 Mois=lookup_widget(button,"ModifMois");
	 An=lookup_widget(button,"ModifAn");
	 Modepaiement=lookup_widget(button,"ModifModeP");
	 strcpy(s.Nom, gtk_entry_get_text(GTK_ENTRY(Nom)));
	 strcpy(s.Prenom, gtk_entry_get_text(GTK_ENTRY(Prenom)));
	 strcpy(s.Numtelephone, gtk_entry_get_text(GTK_ENTRY(Numtelephone)));
	 strcpy(s.Motdepasse, gtk_entry_get_text(GTK_ENTRY(Motdepasse)));
	 strcpy(s.Verificationmotdepasse, gtk_entry_get_text(GTK_ENTRY(Verificationmotdepasse)));
	 s.d.Jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Jour));
	 s.d.Mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Mois));
	 s.d.An=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(An));
	 strcpy(s.Modepaiement,gtk_combo_box_get_active_text(GTK_COMBO_BOX(Modepaiement)));
	 strcpy(s.sexe,user_g.sexe);
	 strcpy(s.Adressemail,user_g.Adressemail);
	 modifier_compte("compte.txt",user_g.Adressemail,s);
}


void
on_actualiser_clicked                  (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *tree;

    // Récupérez le GtkTreeView depuis la fenêtre actuelle ou la page active
    tree = lookup_widget(button, "treeview");
    if (tree != NULL)
    {
        // Videz l'ancien contenu
        //vider(tree);

        // Affichez les nouvelles données
        afficher_sign_up(tree);
    }


}



void
on_chercher_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{
	sign_up s ;
	 GtkWidget *Nom,*Prenom,*Numtelephone,*Motdepasse,*Verificationmotdepasse,*Jour,*Mois,*An,*Modepaiement;
	 Nom=lookup_widget(button,"ModifNom");
	 Prenom=lookup_widget(button,"ModifPrenom");
	 Numtelephone=lookup_widget(button,"ModifNum");
	 Motdepasse=lookup_widget(button,"Modifpsw");
	 Verificationmotdepasse=lookup_widget(button,"ModifVerif");
	 Jour=lookup_widget(button,"ModifJour");
	 Mois=lookup_widget(button,"ModifMois");
	 An=lookup_widget(button,"ModifAn");
	 Modepaiement=lookup_widget(button,"ModifModeP");
	 gtk_entry_set_text(GTK_ENTRY(Nom),user_g.Nom);
	 gtk_entry_set_text(GTK_ENTRY(Prenom),user_g.Prenom);
	 gtk_entry_set_text(GTK_ENTRY(Numtelephone),user_g.Numtelephone);
	 gtk_entry_set_text(GTK_ENTRY(Motdepasse),user_g.Motdepasse);
	 gtk_entry_set_text(GTK_ENTRY(Verificationmotdepasse),user_g.Motdepasse);
	 gtk_spin_button_set_value(GTK_SPIN_BUTTON(Jour),user_g.d.Jour);
	 gtk_spin_button_set_value(GTK_SPIN_BUTTON(Mois),user_g.d.Mois);
	 gtk_spin_button_set_value(GTK_SPIN_BUTTON(An),user_g.d.An);
	 char test[4][50] = {"Par_jour_5DT","Par_mois_150DT","Par_trimestre_300DT","Par_an_1000DT"};
	 int i1 = 0;
	while (i1 < 6 && strcmp(user_g.Modepaiement, test[i1]) != 0) { i1++; }
	gtk_combo_box_set_active(GTK_COMBO_BOX(Modepaiement), i1);
}

