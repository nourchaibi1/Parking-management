#include<gtk/gtk.h>

typedef struct
{ 
char idresv[30];
char idclient[50];
int  etage;
char tempsres[30];
char security[50];
}reservations;


void ajouter_reserv(reservations b,char *reserv);
void afficher_reserv(GtkWidget *liste);
void modifier_reserv(char idresv[],reservations b,char *reserv);
void supprimer_reserv(char idresv[],char *reserv);
int rechercher_reserv(char idresv[]);
void afficher_rechercher_reserv(GtkWidget *liste);
int remplirtabRech (reservations tab[],int nb) ;
void afficher_rechercher_parking(GtkWidget *liste);
void show_sorted_parkingscroi(const char *filename) ;
void show_sorted_parkingsdecroi(const char *filename) ;
