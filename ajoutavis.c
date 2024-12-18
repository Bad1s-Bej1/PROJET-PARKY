#include "ajoutavis.h"
#include <gtk/gtk.h>

int exist_avis(char* filename,char* p,char* u){
    int v=-1; avis a;
    FILE* f=fopen(filename,"r");
    if (f==NULL){
    return ERROR_FILE_OPEN ;
    }

    while(fscanf(f,"%s \"%[^\"]\" %s %f %d %d",a.user,a.text,a.parking,&a.note,&a.experience,&a.anonymat)!= EOF )
{	  
	if(strcmp(u,a.user)==0 && strcmp(p,a.parking)==0){v=1;break;}}
    fclose(f);
    return v ;
}

int ajout_avis(char * filename, avis a)
{     FILE * f=fopen(filename, "a");
    int v=exist_avis(filename,a.parking,a.user) ;
    if(v==1)
        return ERROR_EXISTS;
    if(v==ERROR_FILE_OPEN)
        return ERROR_FILE_OPEN;
    if(f==NULL)
        return ERROR_FILE_OPEN;
        fprintf(f,"%s \"%s\" %s %f %d %d\n",a.user,a.text,a.parking,a.note,a.experience,a.anonymat);
        fclose(f);
        return SUCCESS;
    }

void debug(char *resultat,int res){  
switch (res) {
        case 0: strcpy(resultat, "Erreur: ouverture du fichier"); break;
        case 1: strcpy(resultat, "Succès"); break;
        case 2: strcpy(resultat, "Erreur: le texte est trop long"); break;
        case 3: strcpy(resultat, "Erreur: avis existe déjà"); break;
        case 9: strcpy(resultat, "Erreur: entrée erronée"); break;
        case 66:strcpy(resultat, "Erreur:le texte est trop court"); break;
        default: strcpy(resultat, "Erreur inconnue"); break;
    }
}

int supprimer_avis(char *filename, avis a1) {
    avis a;
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    int v=0;
    if (f == NULL || temp == NULL){
        if (f != NULL) fclose(f);
        if (temp != NULL) fclose(temp);
        return ERROR_FILE_OPEN;
    }
    while (fscanf(f, "%s \"%[^\"]\" %s %f %d %d", a.user, a.text, a.parking, &a.note, &a.experience, &a.anonymat) != EOF) {
        if (strcmp(a.user, a1.user) == 0 && strcmp(a.parking,a1.parking)==0) {
            v=1;
        } else {
            fprintf(temp, "%s \"%s\" %s %f %d %d\n", a.user, a.text, a.parking, a.note, a.experience, a.anonymat);
        }
    }
    fclose(f);
    fclose(temp);
    if(remove(filename)!=0)return ERROR_DELETING;
    if(rename("temp.txt", filename)!=0)return ERROR_RENAMING;
    if(v!=1)
        return ERROR_DOESNT_EXIST;
    return  SUCCESS ;
}


int modifier_avis(char *filename, avis a,avis na) {
    int res = supprimer_avis(filename, a);
    if (res!= SUCCESS) {
        return res;
    }
    return ajout_avis(filename, na);
}

int generate_parking_stats(const char *input_file, const char *output_file) {
    FILE *f_in = fopen(input_file, "r");
    FILE *f_out = fopen(output_file, "w");
    if (f_in == NULL || f_out == NULL) {
        if (f_in != NULL) fclose(f_in);
        if (f_out != NULL) fclose(f_out);
        return 0;
    }

    ParkingStats stats[100]; 
    int parking_count = 0;

    char user[50], text[200], parking[50];
    float note;
    int experience, anonymat;

    while (fscanf(f_in, "%s \"%[^\"]\" %s %f %d %d", user, text, parking, &note, &experience, &anonymat) != EOF) {
        int found = 0;

        for (int i = 0; i < parking_count; i++) {
            if (strcmp(stats[i].parking, parking) == 0) {
                stats[i].total_notes += note;
                stats[i].count_notes++;
                found = 1;
                break;
            }
        }


        if (!found && parking_count < 100) {
            strcpy(stats[parking_count].parking, parking);
            stats[parking_count].total_notes = note;
            stats[parking_count].count_notes = 1;
            parking_count++;
        }
    }
    fclose(f_in);

    for (int i = 0; i < parking_count; i++) {
        stats[i].total_notes /= stats[i].count_notes;
    }


    for (int i = 0; i < parking_count - 1; i++) {
        for (int j = 0; j < parking_count - i - 1; j++) {
            if (stats[j].total_notes < stats[j + 1].total_notes) {
                ParkingStats temp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < parking_count; i++) {
        fprintf(f_out, "%s %f %d\n", stats[i].parking, stats[i].total_notes, stats[i].count_notes);
    }
    fclose(f_out);

    return 1; 
}
int avisutilisateurs(char* filename, const char* parking)
 {
    avis a;
    char parkingFile[50];
    sprintf(parkingFile, "avis_parking_%s.txt", parking);

    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen(parkingFile, "w");
    if (f == NULL || f2 == NULL) {
        if (f != NULL) fclose(f);
        if (f2 != NULL) fclose(f2);
        return ERROR_FILE_OPEN;
    }

    while (fscanf(f, "%s \"%[^\"]\" %s %f %d %d", a.user, a.text, a.parking, &a.note, &a.experience, &a.anonymat) != EOF) {
        if (strcmp(a.parking, parking) == 0) {
            if (a.anonymat == 1) {
                fprintf(f2, "Utilisateur_Anonyme \"%s\" %s %f %d %d\n", a.text, a.parking, a.note, a.experience, a.anonymat);
            } else {
                fprintf(f2, "%s \"%s\" %s %f %d %d\n", a.user, a.text, a.parking, a.note, a.experience, a.anonymat);
            }
        }
    }

    fclose(f);
    fclose(f2);

    return SUCCESS;
}
int mesavis(char* filename, char* user) {
    avis a;char userfile[60];sprintf(userfile,"avis_%s.txt",user);
    FILE *f = fopen(filename, "r");
        if (f == NULL) 
        return ERROR_FILE_OPEN;
    
    while (fscanf(f, "%s \"%[^\"]\" %s %f %d %d", a.user, a.text, a.parking, &a.note, &a.experience, &a.anonymat) != EOF) {
        if (strcmp(a.user, user) == 0) {;

        }
    }
    fclose(f);
    return (SUCCESS) ;
}
