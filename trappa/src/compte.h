#ifndef COMPTE_H_INCLUDED
#define COMPTE_H_INCLUDED
#include <gtk/gtk.h>

typedef struct {
     int Jour;
     int Mois;
     int An;
} date;


typedef struct {
    char Nom[50];
    char Prenom[50];
    char Numtelephone[20];
    date d;
    char Modepaiement[50];
    char Adressemail[20];
    char Motdepasse[50];
    char Verificationmotdepasse[50]; 
    char sexe[50];   
}sign_up;


typedef struct {
    char user[50];
    char psw[50];
}login;
void ajouter_user (char * file ,sign_up s);
void supprimer_compte(char *file, char *Adressemail);
int loginooo(char *file, login user);
int chercher(const char *filename, const char *adrs,const char *psw);
void afficher_sign_up(GtkWidget *liste);
void modifier_compte(char *file, char *Adressemail, sign_up new_user_info);


#endif // COMPTE_H_INCLUDED
