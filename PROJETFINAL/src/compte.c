#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compte.h"
#include <gtk/gtk.h>

// Fonction pour ajouter un utilisateur
void ajouter_user(char *file, sign_up user) {
    FILE *f = fopen(file, "a");  // Utilisation de "a" pour ajouter à la fin du fichier
    if (f != NULL) {
        fprintf(f, "%s %s %s %d/%d/%d %s %s %s %s %s\n",
                user.Nom, user.Prenom, user.Numtelephone,
                user.d.Jour, user.d.Mois, user.d.An,
                user.Modepaiement, user.Adressemail,
                user.Motdepasse, user.Verificationmotdepasse,user.sexe);
        fclose(f);
        
    }
}

// Fonction pour définir le sexe
void sexe(char msg[], int choix) {
    if (choix == 1) {
        strcpy(msg, "homme");
    } else {
        strcpy(msg, "femme");
    }
}


int modifier(char *file, char *Adressemail[],char *psw[], sign_up nouv) {
    FILE *f1 = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f1 == NULL || f2 == NULL) {
        perror("Erreur d'ouverture des fichiers");
        return 0;
    }

    sign_up user;
    int deleted = 0;

    while (fscanf(f1, "%s %s %s %d/%d/%d %s %s %s %s",
                  user.Nom, user.Prenom, user.Numtelephone,
                  &user.d.Jour, &user.d.Mois, &user.d.An,
                  user.Modepaiement, user.Adressemail,
                  user.Motdepasse, user.Verificationmotdepasse) != EOF) {
        if (strcmp(user.Adressemail, nouv.Adressemail) == 0 && strcmp(nouv.Motdepasse,user.Motdepasse )) {
	    	fprintf(f2, "%s %s %s %d/%d/%d %s %s %s %s\n",
                    nouv.Nom, nouv.Prenom, nouv.Numtelephone,
                    nouv.d.Jour, nouv.d.Mois, nouv.d.An,
                    nouv.Modepaiement, nouv.Adressemail,
                    nouv.Motdepasse, nouv.Verificationmotdepasse);
            deleted = 1; // Marquer l'utilisateur comme supprimé
        } else {
            fprintf(f2, "%s %s %s %d/%d/%d %s %s %s %s\n",
                    user.Nom, user.Prenom, user.Numtelephone,
                    user.d.Jour, user.d.Mois, user.d.An,
                    user.Modepaiement, user.Adressemail,
                    user.Motdepasse, user.Verificationmotdepasse);
        }
    }

    fclose(f1);
    fclose(f2);

    remove(file);
    rename("temp.txt", file);

    return deleted;
}
// Fonction pour supprimer un utilisateur
void supprimer_compte(char *file, char *Adressemail) {
    FILE *f1 = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f1 == NULL || f2 == NULL) {
        perror("Erreur d'ouverture des fichiers");
        return 0;
    }

    sign_up user;
    int modified = 0;

    while (fscanf(f1, "%s %s %s %d/%d/%d %s %s %s %s %s",
                  user.Nom, user.Prenom, user.Numtelephone,
                  &user.d.Jour, &user.d.Mois, &user.d.An,
                  user.Modepaiement, user.Adressemail,
                  user.Motdepasse, user.Verificationmotdepasse,user.sexe) != EOF) {
        if (strcmp(user.Adressemail, Adressemail) == 0) {
            
        }
	else{ 
        // Write the updated or unchanged user info to the temp file
        fprintf(f2, "%s %s %s %d/%d/%d %s %s %s %s %s\n",
                user.Nom, user.Prenom, user.Numtelephone,
                user.d.Jour, user.d.Mois, user.d.An,
                user.Modepaiement, user.Adressemail,
                user.Motdepasse, user.Verificationmotdepasse,user.sexe);}
    }

    fclose(f1);
    fclose(f2);

    remove(file);
    rename("temp.txt", file);

    
}
void modifier_compte(char *file, char *Adressemail, sign_up new_user_info) {
    FILE *f1 = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f1 == NULL || f2 == NULL) {
        perror("Erreur d'ouverture des fichiers");
        return 0;
    }

    sign_up user;
    int modified = 0;

    while (fscanf(f1, "%s %s %s %d/%d/%d %s %s %s %s %s",
                  user.Nom, user.Prenom, user.Numtelephone,
                  &user.d.Jour, &user.d.Mois, &user.d.An,
                  user.Modepaiement, user.Adressemail,
                  user.Motdepasse, user.Verificationmotdepasse,user.sexe) != EOF) {
        if (strcmp(user.Adressemail, Adressemail) == 0) {
            // Update the user info if the email matches
            modified = 1;
            // Copy the new user information to the existing user
            user = new_user_info;
        }

        // Write the updated or unchanged user info to the temp file
        fprintf(f2, "%s %s %s %d/%d/%d %s %s %s %s %s\n",
                user.Nom, user.Prenom, user.Numtelephone,
                user.d.Jour, user.d.Mois, user.d.An,
                user.Modepaiement, user.Adressemail,
                user.Motdepasse, user.Verificationmotdepasse,user.sexe);
    }

    fclose(f1);
    fclose(f2);

    remove(file);
    rename("temp.txt", file);

    
}

int chercher(const char *filename, const char *adrs, const char *psw) {
    FILE *f = fopen(filename, "r");
    sign_up user;
    int test = 0;

    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return 0;
    }

    while (fscanf(f, "%s %s %s %d/%d/%d %s %s %s %s %s",
                  user.Nom, user.Prenom, user.Numtelephone,
                  &user.d.Jour, &user.d.Mois, &user.d.An,user.Modepaiement,
                   user.Adressemail,
                  user.Motdepasse, user.Verificationmotdepasse ,user.sexe) != EOF) {

        printf("Lecture : Adresse = %s, Mdp = %s\n", user.Adressemail, user.Motdepasse);

        // Comparer les champs "Adressemail" et "Motdepasse"
        if (strcmp(user.Adressemail, adrs) == 0 && strcmp(user.Motdepasse, psw) == 0) {
            test = 1;
            break;  // Arrêtez dès qu'un match est trouvé
        }
    }

    fclose(f);
    return test;
}

/*
int chercher(const char *filename, const char *adrs,const char *psw) {
FILE *f = fopen(filename, "r");
sign_up user;
int test=0;
if (f != NULL)
{
	printf("%s",adrs);
	printf("%s",psw);
	while (fscanf(f, "%s %s %s %d/%d/%d %s %s %s %s",
		          user.Nom, user.Prenom, user.Numtelephone,
		          &user.d.Jour, &user.d.Mois, &user.d.An,
		          user.Modepaiement, user.Adressemail,
		          user.Motdepasse, user.Verificationmotdepasse) != EOF) 
			{if (strcmp(user.Adressemail,adrs)==0 && strcmp(user.Motdepasse,psw)==0)
			{	test=1;}
			break;
			}
	return test;	

}
else {printf("fichier nnull");}
}
*/
void afficher_sign_up(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    sign_up user;  // Déclaration de la variable de type sign_up

    FILE *f;

    store = gtk_tree_view_get_model(liste);

    if (store == NULL)
    {
        // Ajouter les colonnes dans l'ordre souhaité
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Num. Telephone", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date (JJ/MM/AAAA)", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mode Paiement", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse Email", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mot de Passe", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Verification Mot de Passe", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Créer un GtkListStore avec 9 colonnes dans l'ordre souhaité
    store = gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen("compte.txt", "r");
    if (f == NULL)
    {
        return;
    }
    else
    {
        // Lecture des données depuis le fichier
        while (fscanf(f, "%s %s %s %d/%d/%d %s %s %s %s %s",
                      user.Nom, user.Prenom, user.Numtelephone, 
                      &user.d.Jour, &user.d.Mois, &user.d.An, 
                      user.Modepaiement, user.Adressemail, 
                      user.Motdepasse, user.sexe, user.Verificationmotdepasse) != EOF)
        {
            // Formater la date pour l'afficher sous le format JJ/MM/AAAA
            char date_str[20];
            snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d", user.d.Jour, user.d.Mois, user.d.An);

            // Ajouter une nouvelle ligne au GtkListStore
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, user.Nom,
                               1, user.Prenom,
                               2, user.Numtelephone,
                               3, date_str,
                               4, user.Modepaiement,
                               5, user.Verificationmotdepasse,
                               6, user.Adressemail,
                               7, user.Motdepasse,
                               8, user.sexe,
                               -1);
        }
        fclose(f);

        // Attribuer le modèle au GtkTreeView
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}




