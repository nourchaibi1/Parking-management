#ifndef GEST_PARKING_H_INCLUDED
#define GEST_PARKING_H_INCLUDED

#include <stdio.h>
#include <gtk/gtk.h>
// Structure pour un parking
typedef struct {
    char idpark[30];
    char idclient[10];
    char nom[10];
    char ville[10];
    int nbplace;
    char tmp[10];
    char disponibility[30];
} parking;

// Déclaration des fonctions
void ajouter_park(parking b, char *park);
void afficher_park(GtkWidget *liste);
void modifier_park(char idpark[], parking b1, char *park);
void supprimer_park(char idpark[], char *park);
int rechercher_park(char idpark[]);
void afficher_rechercher_park(GtkWidget *liste);
int remplirtabRech(parking tab[], int nb);

#endif // GEST_PARKING_H_INCLUDED

