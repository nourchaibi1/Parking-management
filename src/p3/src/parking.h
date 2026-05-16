#ifndef GEST_PARKING_H_INCLUDED
#define GEST_PARKING_H_INCLUDED

#include<stdio.h>

typedef struct {
  char nom[20];
  char ville[20];
  char region[20];
  int nbplace;
  char datedebut[20];
  char statut[20];
 }parking;

int ajouter_parking(parking p, char filename[]);
void modifier_parking(char nom[], parking nouv);
void supprimer_parking(char nom[]);
parking chercher_parking(char x[], char*filename);
 
#endif
  
