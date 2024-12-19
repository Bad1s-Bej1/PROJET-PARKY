#ifndef AJOUTAVIS_H
#define AJOUTAVIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define ERROR_FILE_OPEN 0
#define SUCCESS 1
#define MAX_TEXT_LENGTH 200
#define ERROR_TEXT_TOO_LONG 2
#define ERROR_EXISTS 3
#define ERROR_DOESNT_EXIST 4
#define ERROR_NBR_PARKING 6
#define ERROR_DELETING 7
#define ERROR_RENAMING 8
#define ERROR_ENTRY 9
#define ERROR_NOTFOUND 10

typedef struct {
    char user[50];
    char text[200];
    char parking[50];
    float note;
    int experience;
    int anonymat;
} avis;

typedef struct {
    char parking[50];
    float total_notes;
    int count_notes;
} ParkingStats;

int exist_avis(char* filename, char* p, char* u);
int ajout_avis(char* filename, avis a);
void debug(char* resultat, int res);
int generate_parking_stats(const char* input_file, const char* output_file);
int avisutilisateurs(char* filename, const char* parking);
int supprimer_avis(char* filename, avis a1);
int modifier_avis(char* filename, avis a, avis na);
int mesavis(char* filename, char* user);

#endif 
