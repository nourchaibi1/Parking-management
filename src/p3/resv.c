#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"resv.h"
#include <gtk/gtk.h>

enum
{ 
	EIDRES,
	EIDCLI,
	EETAG,
	ETMPSRES,
	ESEC,
	COLUMNS,
};
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
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column)  ;


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






