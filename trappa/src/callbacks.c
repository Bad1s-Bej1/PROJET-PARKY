#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "compte.h"
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

