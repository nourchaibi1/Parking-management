#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"resv.h"
#include <gtk/gtk.h>
#include"parking.h"
enum
{ 
	EIDRES,
	EIDCLI,
	EETAG,
	ETMPSRES,
	ESEC,
	COLUMNS,
};



typedef enum {
    ENOM,       // Nom du parking
    EVILLE,     // Ville
    EREGION,    // Région
    ENBPLACE,   // Nombre de places
    EDATED,     // Date de début
    ESTATUT,    // Statut
    COLUMNS1    // Nombre total de colonnes
} ParkingColumns;
////ajouter
void ajouter_reserv(reservations b,char *reserv){
FILE * f;
f=fopen(reserv,"a");

  fprintf(f,"%s %s %d %s %s \n ",b.idresv,b.idclient,b.etage,b.tempsres,b.security);
  fclose(f);
}
///afficher
void afficher_reserv(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char idresv[30];
	char idclient[10];
	char etage[10];
	char tempsres[10];
	char security[30];
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("idresv", renderer, "text",EIDRES,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("idclient", renderer, "text",EIDCLI,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("etage", renderer, "text",EETAG,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("tempsres", renderer, "text",ETMPSRES,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("security", renderer, "text",ESEC,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	

	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("reservation.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("reservation.txt","a+");
		while(fscanf(f,"%s %s %s %s %s    \n",idresv,idclient,etage,tempsres,security)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDRES, idresv, EIDCLI,idclient, EETAG, etage, ETMPSRES, tempsres, ESEC, security ,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

////modifier
void modifier_reserv(char idresv[],reservations b1,char *reserv)
{
reservations b;
  FILE* f=fopen(reserv, "r");
  FILE* f2=fopen("resmod.txt", "w");
  
  if((f!=NULL) ||( f2!=NULL))
 {
while(fscanf(f,"%s %s %d %s %s \n ",b.idresv,b.idclient,&b.etage,b.tempsres,b.security)!=EOF)
{
if(strcmp(b.idresv,b1.idresv)==0)
  fprintf(f2,"%s %s %d %s %s \n ",b1.idresv,b1.idclient,b1.etage,b1.tempsres,b1.security);
else
 fprintf(f2,"%s %s %d %s %s \n ",b.idresv,b.idclient,b.etage,b.tempsres,b.security);
}
   fclose(f);
   fclose(f2);
remove(reserv);
rename("resmod.txt",reserv);
 }
}
///////////////////////////////Supprimerr
void supprimer_reserv(char idresv[],char *reserv)
{
reservations b;     
FILE * f=fopen(reserv,"r");
FILE * f2=fopen("reservsupp.txt","w");

while (fscanf(f,"%s %s %d %s %s \n  ",b.idresv,b.idclient,&b.etage,b.tempsres,b.security)!=EOF)
{

if(strcmp(b.idresv,idresv)!=0)

  fprintf(f2,"%s %s %d %s %s \n  ",b.idresv,b.idclient,b.etage,b.tempsres,b.security);
}
  fclose(f);

  fclose(f2);

remove(reserv);
rename("reservsupp.txt",reserv);

 
}
//fonction remplir tab
int remplirtabRech (reservations tab[],int nb)
{
    char idresv[20];
    char idclient[30];	
    int etage;
    char tempsres[20];
    char security[20];
   
  
    FILE* fichier ;
    int i;

    fichier = fopen("reservation.txt", "a+");

        while (fscanf(fichier,"%s %s %d %s %s \n ",idresv,idclient,&etage,tempsres,security)!=EOF)
        {
            
            strcpy(tab[i].idresv,idresv);
            strcpy(tab[i].idclient,idclient);
	    tab[i].etage=etage;
            strcpy(tab[i].tempsres,tempsres);
	    strcpy(tab[i].security,security);
	    
	    	
            nb++;
	    i++;    
        }
        fclose(fichier);
	return(nb);
}
//rechercher 

int rechercher_reserv(char idresv[])
{
reservations tab[100];
int nb;
int ce,i;
FILE*f;
ce=0;
nb=remplirtabRech (tab,nb);
for (i=0;i<nb;i++)
	{if ((strcmp(idresv,tab[i].idresv)==0) ||(strcmp(idresv,tab[i].idclient)==0) )
		{
		ce=1;
		f=fopen("rechresv.txt", "w+");
		if("f!=NULL")			
	{fprintf(f,"%s %s %d %s %s \n ",tab[i].idresv,tab[i].idclient,tab[i].etage,tab[i].tempsres,tab[i].security);}
		fclose(f);		
		}
	
	}
return(ce);		
}
//AFF RECH
void afficher_rechercher_reserv(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char idresv[30];
	char idclient[10];
	char etage[10];
	char tempsres[10];
	char security[30];
	
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("idresv", renderer, "text",EIDRES,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("idclient", renderer, "text",EIDCLI,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("etage", renderer, "text",EETAG,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("tempsres", renderer, "text",ETMPSRES,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("security", renderer, "text",ESEC,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("rechresv.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("rechresv.txt","a+");
		while(fscanf(f,"%s %s %s %s %s   \n",idresv,idclient,etage,tempsres,security)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDRES, idresv, EIDCLI,idclient, EETAG, etage, ETMPSRES, tempsres, ESEC,  security ,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
	
}






void afficher_rechercher_parking(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store = NULL;
    FILE *f;
    char nom[20], ville[20], region[20], datedebut[20], statut[20];
    int nbplace;


    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {
        store = gtk_list_store_new(COLUMNS1, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", EVILLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Région", renderer, "text", EREGION, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nombre de places", renderer, "text", ENBPLACE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de début", renderer, "text", EDATED, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Statut", renderer, "text", ESTATUT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }


    f = fopen("parking.txt", "r");
    if (f == NULL)
    {
        g_print("Erreur : le fichier n'a pas pu être ouvert.\n");
        return;
    }


    while (fscanf(f, "%s %s %s %d %s %s\n", nom, ville, region, &nbplace, datedebut, statut) != EOF)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ENOM, nom,
                           EVILLE, ville,
                           EREGION, region,
                           ENBPLACE, nbplace,
                           EDATED, datedebut,
                           ESTATUT, statut,
                           -1);
    }

    fclose(f);


    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));


    g_object_unref(store);
}


void show_sorted_parkingscroi(const char *filename) {  
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    parking parkings[100];
    int count = 0;


    while (fscanf(f, "%s %s %s %d %s %s\n", 
                  parkings[count].nom, 
                  parkings[count].ville, 
                  parkings[count].region, 
                  &parkings[count].nbplace, 
                  parkings[count].datedebut, 
                  parkings[count].statut) != EOF) {
        count++;
    }

    fclose(f);


    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (parkings[i].nbplace > parkings[j].nbplace) {
                parking temp = parkings[i];
                parkings[i] = parkings[j];
                parkings[j] = temp;
            }
        }
    }


    f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }


    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %s %d %s %s\n", 
                parkings[i].nom, 
                parkings[i].ville, 
                parkings[i].region, 
                parkings[i].nbplace, 
                parkings[i].datedebut, 
                parkings[i].statut);
    }

    fclose(f);

   
}
//*****************************************************************
void show_sorted_parkingsdecroi(const char *filename) {  
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    parking parkings[100];
    int count = 0;


    while (fscanf(f, "%s %s %s %d %s %s\n", 
                  parkings[count].nom, 
                  parkings[count].ville, 
                  parkings[count].region, 
                  &parkings[count].nbplace, 
                  parkings[count].datedebut, 
                  parkings[count].statut) != EOF) {
        count++;
    }

    fclose(f);


    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (parkings[i].nbplace < parkings[j].nbplace) {
                parking temp = parkings[i];
                parkings[i] = parkings[j];
                parkings[j] = temp;
            }
        }
    }


    f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }


    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %s %d %s %s\n", 
                parkings[i].nom, 
                parkings[i].ville, 
                parkings[i].region, 
                parkings[i].nbplace, 
                parkings[i].datedebut, 
                parkings[i].statut);
    }

    fclose(f);

   
}






