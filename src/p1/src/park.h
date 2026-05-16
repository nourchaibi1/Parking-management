#include<gtk/gtk.h>

typedef struct
{ 
char idpark[30];
char idclient[50];
int  etage;
char tempsres[30];
char disponibility[50];
}parking;


void ajouter_park(parking b,char *park);
void afficher_park(GtkWidget *liste);
void modifier_park(char idpark[],parking b,char *park);
void supprimer_park(char idpark[],char *park);
int rechercher_park(char idpark[]);
void afficher_rechercher_park(GtkWidget *liste);
int remplirtabRech (parking tab[],int nb) ;
