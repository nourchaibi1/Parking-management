#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "park.h"
#include <gtk/gtk.h>

enum { 
    EIDPARK,
    EIDCLI,
    ENOM,
    EVILLE,
    ENBPLACE,
    EDATE,
    ETMP,
    EDISP,
    COLUMNS,
};

// Ajouter un parking
void ajouter_park(parking b, char *park) {
    FILE *f;
    f = fopen(park, "a");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(f, "%s %s %s %s %d %s %s\n", b.idpark, b.idclient, b.nom, b.ville, b.nbplace, b.tmp, b.disponibility);
    fclose(f);
}

// Afficher les parkings
void afficher_park(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    char idpark[30], idclient[10], nom[10], ville[10], nbplace[10], tmp[10], disponibility[30];
    
    store = gtk_tree_view_get_model(liste);
    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("idpark", renderer, "text", EIDPARK, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("idclient", renderer, "text", EIDCLI, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ville", renderer, "text", EVILLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nbplace", renderer, "text", ENBPLACE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("tmp", renderer, "text", ETMP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("disponibility", renderer, "text", EDISP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    FILE *f = fopen("parking.txt", "r");
    if (f == NULL) {
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s\n", idpark, idclient, nom, ville, nbplace, tmp, disponibility) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, EIDPARK, idpark, EIDCLI, idclient, ENOM, nom, EVILLE, ville, ENBPLACE, nbplace, ETMP, tmp, EDISP, disponibility, -1);
    }
    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

// Modifier un parking
void modifier_park(char idpark[], parking b1, char *park) {
    parking b;
    FILE *f = fopen(park, "r");
    FILE *f2 = fopen("parkmod.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %s %s\n", b.idpark, b.idclient, b.nom, b.ville, &b.nbplace, b.tmp, b.disponibility) != EOF) {
            if (strcmp(b.idpark, b1.idpark) == 0)
                fprintf(f2, "%s %s %s %s %d %s %s\n", b.idpark, b.idclient, b.nom, b.ville, b.nbplace, b.tmp, b.disponibility);
            else
                fprintf(f2, "%s %s %s %s %d %s %s\n", b.idpark, b.idclient, b.nom, b.ville, b.nbplace, b.tmp, b.disponibility);
        }
        fclose(f);
        fclose(f2);
        remove(park);
        rename("parkmod.txt", park);
    }
}

// Supprimer un parking
void supprimer_park(char idpark[], char *park) {
    parking b;
    FILE *f = fopen(park, "r");
    FILE *f2 = fopen("parksupp.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %s %s\n", b.idpark, b.idclient, b.nom, b.ville, &b.nbplace, b.tmp, b.disponibility) != EOF) {
            if (strcmp(b.idpark, idpark) != 0)
                fprintf(f2, "%s %s %s %s %d %s %s\n", b.idpark, b.idclient, b.nom, b.ville, b.nbplace, b.tmp, b.disponibility);
        }
        fclose(f);
        fclose(f2);
        remove(park);
        rename("parksupp.txt", park);
    }
}

// Remplir le tableau de recherche
int remplirtabRech(parking tab[], int nb) {
    char idpark[30], idclient[10], nom[10], ville[10], tmp[10], disponibility[30];
    int nbplace;
    FILE *fichier;
    int i = 0;

    fichier = fopen("parking.txt", "a+");
    if (fichier == NULL) return nb;

    while (fscanf(fichier, "%s %s %s %s %d %s %s\n", idpark, idclient, nom, ville, &nbplace, tmp, disponibility) != EOF) {
        strcpy(tab[i].idpark, idpark);
        strcpy(tab[i].idclient, idclient);
        strcpy(tab[i].nom, nom);
        strcpy(tab[i].ville, ville);
        tab[i].nbplace = nbplace;
        strcpy(tab[i].tmp, tmp);
        strcpy(tab[i].disponibility, disponibility);
        nb++;
        i++;
    }
    fclose(fichier);
    return nb;
}

// Rechercher un parking
int rechercher_park(char idpark[]) {
    parking tab[100];
    int nb = 0, ce = 0, i;
    FILE *f;

    nb = remplirtabRech(tab, nb);
    for (i = 0; i < nb; i++) {
        if (strcmp(idpark, tab[i].idpark) == 0 || strcmp(idpark, tab[i].idclient) == 0) {
            ce = 1;
            f = fopen("rechpark.txt", "w+");
            if (f != NULL) {
                fprintf(f, "%s %s %s %s %d %s %s\n", tab[i].idpark, tab[i].idclient, tab[i].nom, tab[i].ville, tab[i].nbplace, tab[i].tmp, tab[i].disponibility);
                fclose(f);
            }
        }
    }
    return ce;
}

// Afficher les résultats de recherche
void afficher_rechercher_park(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    char idpark[30], idclient[10], nom[10], ville[10], nbplace[10], tmp[10], disponibility[30];

    store = gtk_tree_view_get_model(liste);
    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("idpark", renderer, "text", EIDPARK, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("idclient", renderer, "text", EIDCLI, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ville", renderer, "text", EVILLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nbplace", renderer, "text", ENBPLACE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("tmp", renderer, "text", ETMP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("disponibility", renderer, "text", EDISP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    FILE *f = fopen("rechpark.txt", "r");
    if (f == NULL) {
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s\n", idpark, idclient, nom, ville, nbplace, tmp, disponibility) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, EIDPARK, idpark, EIDCLI, idclient, ENOM, nom, EVILLE, ville, ENBPLACE, nbplace, ETMP, tmp, EDISP, disponibility, -1);
    }
    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

