#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"park.h"
#include <gtk/gtk.h>

enum
{ 
	EIDPARK,
	EIDCLI,
	EETAG,
	ETMPSRES,
	EDISP,
	COLUMNS,
};
////ajouter
void ajouter_park(parking b,char *park){
FILE * f;
f=fopen(park,"a");

  fprintf(f,"%s %s %d %s %s \n ",b.idpark,b.idclient,b.etage,b.tempsres,b.disponibility);
  fclose(f);
}
///afficher
void afficher_park(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char idpark[30];
	char idclient[10];
	char etage[10];
	char tempsres[10];
	char disponibility[30];
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("idpark", renderer, "text",EIDPARK,NULL);
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
	column = gtk_tree_view_column_new_with_attributes("disponibility", renderer, "text",EDISP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	

	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("parking.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("parking.txt","a+");
		while(fscanf(f,"%s %s %s %s %s    \n",idpark,idclient,etage,tempsres,disponibility)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDPARK, idpark, EIDCLI,idclient, EETAG, etage, ETMPSRES, tempsres, EDISP, disponibility ,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

////modifier
void modifier_park(char idpark[],parking b1,char *park)
{
parking b;
  FILE* f=fopen(park, "r");
  FILE* f2=fopen("parkmod.txt", "w");
  
  if((f!=NULL) ||( f2!=NULL))
 {
while(fscanf(f,"%s %s %d %s %s \n ",b.idpark,b.idclient,&b.etage,b.tempsres,b.disponibility)!=EOF)
{
if(strcmp(b.idpark,b1.idpark)==0)
  fprintf(f2,"%s %s %d %s %s \n ",b1.idpark,b1.idclient,b1.etage,b1.tempsres,b1.disponibility);
else
 fprintf(f2,"%s %s %d %s %s \n ",b.idpark,b.idclient,b.etage,b.tempsres,b.disponibility);
}
   fclose(f);
   fclose(f2);
remove(park);
rename("parkmod.txt",park);
 }
}
///////////////////////////////Supprimerr
void supprimer_park(char idpark[],char *park)
{
parking b;     
FILE * f=fopen(park,"r");
FILE * f2=fopen("parksupp.txt","w");

while (fscanf(f,"%s %s %d %s %s \n  ",b.idpark,b.idclient,&b.etage,b.tempsres,b.disponibility)!=EOF)
{

if(strcmp(b.idpark,idpark)!=0)

  fprintf(f2,"%s %s %d %s %s \n  ",b.idpark,b.idclient,b.etage,b.tempsres,b.disponibility);
}
  fclose(f);

  fclose(f2);

remove(park);
rename("parksupp.txt",park);

 
}
//fonction remplir tab
int remplirtabRech (parking tab[],int nb)
{
    char idpark[20];
    char idclient[30];	
    int etage;
    char tempsres[20];
    char disponibility[20];
   
  
    FILE* fichier ;
    int i;

    fichier = fopen("parking.txt", "a+");

        while (fscanf(fichier,"%s %s %d %s %s \n ",idpark,idclient,&etage,tempsres,disponibility)!=EOF)
        {
            
            strcpy(tab[i].idpark,idpark);
            strcpy(tab[i].idclient,idclient);
	    tab[i].etage=etage;
            strcpy(tab[i].tempsres,tempsres);
	    strcpy(tab[i].disponibility,disponibility);
	    
	    	
            nb++;
	    i++;    
        }
        fclose(fichier);
	return(nb);
}
//rechercher 

int rechercher_park(char idpark[])
{
parking tab[100];
int nb;
int ce,i;
FILE*f;
ce=0;
nb=remplirtabRech (tab,nb);
for (i=0;i<nb;i++)
	{if ((strcmp(idpark,tab[i].idpark)==0) ||(strcmp(idpark,tab[i].idclient)==0) )
		{
		ce=1;
		f=fopen("rechpark.txt", "w+");
		if("f!=NULL")			
	{fprintf(f,"%s %s %d %s %s \n ",tab[i].idpark,tab[i].idclient,tab[i].etage,tab[i].tempsres,tab[i].disponibility);}
		fclose(f);		
		}
	
	}
return(ce);		
}
//AFF RECH
void afficher_rechercher_park(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char idpark[30];
	char idclient[10];
	char etage[10];
	char tempsres[10];
	char disponibility[30];
	
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("idpark", renderer, "text",EIDPARK,NULL);
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
	column = gtk_tree_view_column_new_with_attributes("disponibility", renderer, "text",EDISP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("rechpark.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("rechpark.txt","a+");
		while(fscanf(f,"%s %s %s %s %s   \n",idpark,idclient,etage,tempsres,disponibility)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDPARK, idpark, EIDCLI,idclient, EETAG, etage, ETMPSRES, tempsres, EDISP,  disponibility ,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
	
}
