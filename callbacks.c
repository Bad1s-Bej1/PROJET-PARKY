#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "ajoutavis.h"
#include <math.h>
#include <gtk/gtk.h>
#include <string.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"

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


