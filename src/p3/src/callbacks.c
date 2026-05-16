#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include"resv.h"
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

int x,y,z;
int m,n,l;

void
on_checkbutton_confres_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=1;}
}


void
on_button_retaj_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowadd, *windowaff;
windowadd=lookup_widget(button,"window_add");
gtk_widget_destroy(windowadd);
windowaff=create_window_aff();
gtk_widget_show (windowaff);
}


void
on_button_addres_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
reservations b;
GdkColor color;
GtkWidget *windowajout,*idr,*idc,*etgg,*tmprss,*secc,*combobox1,*output,*output1;
windowajout=create_window_add();
idr= lookup_widget(button,"entry_idres");
idc= lookup_widget(button,"entry_idcli");
etgg = lookup_widget(button,"spinbutton_etg");

combobox1=lookup_widget(button,"comboboxentry_tmpres");

strcpy(b.idresv,gtk_entry_get_text(GTK_ENTRY(idr)));
strcpy(b.idclient,gtk_entry_get_text(GTK_ENTRY(idc)));
b.etage=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (etgg));


if(y==1)
{strcpy(b.security,"Normal");}
else if(y==2)
{strcpy(b.security,"securise");}


if ((strcmp(b.idresv,"")==0) || (strcmp(b.idclient,"")==0) ) {
output1=lookup_widget(button,"label_nnajres");
gtk_label_set_text(GTK_LABEL(output1), "Données manquantes. \n Veuillez remplir tout les champs!");
output=lookup_widget(button,"label_ajressucc");
gtk_label_set_text(GTK_LABEL(output), "");
}
if (combobox1 != NULL) {
        gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1));

        if (selected_text != NULL) {
            // Affiche le genre sélectionné dans la console (debug)
            g_print("Genre sélectionné : %s\n", selected_text);
            // Copie le genre sélectionné dans la structure c
            strcpy(b.tempsres, selected_text);
           g_free(selected_text);
        } else {
            // Aucune option sélectionnée dans la combobox
            // Faites quelque chose en conséquence
           z=0;
        }
}
if(x==1){
ajouter_reserv(b,"reservation.txt");
output1=lookup_widget(button,"label_nnajres");
gtk_label_set_text(GTK_LABEL(output1), "");
output=lookup_widget(button,"label_ajressucc");
gtk_label_set_text(GTK_LABEL(output), "Ajouter avec Succes");

}
x=0;
y=0;
}


void
on_radiobutton_norm_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=1;}
}


void
on_radiobutton_biensec_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=2;}
}


void
on_checkbutton_modconf_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{m=1;}
}


void
on_radiobutton_modnorm_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{n=1;}
}


void
on_radiobutton_modbiensec_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{n=2;}
}


void
on_button_confmod_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
reservations b1;
GtkWidget *windowmodifier,*idr1,*idc1,*etgg1,*tmprss1,*secc1,*combobox2,*output2;
windowmodifier=create_window_mod();
idr1= lookup_widget(button,"entry_modidres");
idc1= lookup_widget(button,"entry_modidcl");
etgg1 = lookup_widget(button,"spinbutton_modetg");


combobox2=lookup_widget(button,"comboboxentry_modtmpres");

strcpy(b1.idresv,gtk_entry_get_text(GTK_ENTRY(idr1)));
strcpy(b1.idclient,gtk_entry_get_text(GTK_ENTRY(idc1)));

b1.etage=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (etgg1));


if (combobox2 != NULL) {
        gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox2));

        if (selected_text != NULL) {
            // Affiche le genre sélectionné dans la console (debug)
            g_print("Genre sélectionné : %s\n", selected_text);

            // Copie le genre sélectionné dans la structure c
            strcpy(b1.tempsres, selected_text);

            g_free(selected_text);
        } else {
            // Aucune option sélectionnée dans la combobox
            // Faites quelque chose en conséquence
           l=0;
        }


if(n==1)
{strcpy(b1.security,"Normal");}
else if(n==2)
{strcpy(b1.security,"securise");}


if(m==1){
modifier_reserv(b1.idresv,b1,"reservation.txt");
output2=lookup_widget(button,"label_modres");
gtk_label_set_text(GTK_LABEL(output2), "Modifier avec Succes");

}
m=0;
n=0;

}
}


void
on_button_retmod_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowmodifier, *windowaff;
windowmodifier=lookup_widget(button,"window_mod");
gtk_widget_destroy(windowmodifier);
windowaff=create_window_aff ();
gtk_widget_show (windowaff);
}


void
on_treeview_affres_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* idr;
gchar* idc;
gchar* etg;
gchar* tmprs;
gchar* seccr;

reservations b;
GtkTreeModel *model= gtk_tree_view_get_model(treeview);
GtkWidget* windowmodifier,*window_aff,*tre,*idrr,*idcc,*etgg,*tmprss,*seccrr;

if (gtk_tree_model_get_iter(model, &iter,path))
{


gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&idr,1,&idc,2,&etg,3,&tmprs,4,&seccr,-1);

windowmodifier=create_window_mod();
window_aff=create_window_aff();
gtk_widget_hide(window_aff);
gtk_widget_show(windowmodifier);

idrr=lookup_widget(windowmodifier,"entry_modidres");
gtk_entry_set_text(GTK_ENTRY(idrr),idr);

idcc=lookup_widget(windowmodifier,"entry_modidcl");
gtk_entry_set_text(GTK_ENTRY(idcc),idc);

etgg=lookup_widget(windowmodifier,"spinbutton_modetg");
gtk_entry_set_text(GTK_ENTRY(etgg),etg);
}
}


void
on_button_supprs_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
reservations b;
char idrees[20];
GtkWidget *windowaff,*tree, *rss,*output;
rss = lookup_widget(button,"entry_supp");
strcpy(idrees,gtk_entry_get_text(GTK_ENTRY(rss)));
if ((strcmp(b.idresv,"")==0)){
output=lookup_widget(button,"label_suppres");
gtk_label_set_text(GTK_LABEL(output), "donnes manquantes");
}
else{
supprimer_reserv(idrees,"reservation.txt");
windowaff=lookup_widget(button,"window_aff");
tree=lookup_widget(windowaff,"treeview_affres");
afficher_reserv(tree);



output=lookup_widget(button,"label_suppres");
gtk_label_set_text(GTK_LABEL(output), "Supprimer avec Succes");
gtk_widget_hide(windowaff);
gtk_widget_show(windowaff);
}
}


void
on_button_rechres_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowrech, *windowaff;
windowaff=lookup_widget(button,"window_aff");
gtk_widget_destroy(windowaff);
windowrech=create_window_rech ();
gtk_widget_show (windowrech);
}


void
on_button_modrs_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowmod, *windowaff;
windowaff=lookup_widget(button,"window_aff");
gtk_widget_destroy(windowaff);
windowmod=create_window_mod ();
gtk_widget_show (windowmod);
}


void
on_button_ajrs_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajouter, *windowaff;
windowaff=lookup_widget(button,"window_aff");
gtk_widget_destroy(windowaff);
windowajouter=create_window_add ();
gtk_widget_show (windowajouter);
}


void
on_button_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *tree,*window_aff;
window_aff=lookup_widget(button,"window_aff");
gtk_widget_destroy(window_aff);
window_aff=create_window_aff();
tree=lookup_widget(window_aff,"treeview_affres");

afficher_reserv(tree);

gtk_widget_hide(window_aff);
gtk_widget_show(window_aff);
}


void
on_treeview_affrech_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button_affrech_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
char idresv[20];
int c; 
GtkWidget *idr,*tree,*windowrech,*output;
windowrech=lookup_widget(button,"window_rech");
idr = lookup_widget(button,"entry_rechaff");
strcpy(idresv,gtk_entry_get_text(GTK_ENTRY(idr)));
c=rechercher_reserv(idresv);
if (c==0)
{
	output=lookup_widget(button,"label32");
	gtk_label_set_text(GTK_LABEL(output), "fiche INTROUVABLE");
}
if (c==1)
{	
tree=lookup_widget(windowrech,"treeview_affrech");
afficher_rechercher_reserv(tree);
}
}


void
on_button_Retrech_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowrech, *window_aff;
windowrech=lookup_widget(button,"window_rech");
gtk_widget_destroy(windowrech);
window_aff=create_window_aff ();
gtk_widget_show (window_aff);
}


void
on_listeparking_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowlisteparking, *window_aff,*treeviewlistparking;
window_aff=lookup_widget(button,"window_aff");
gtk_widget_destroy(window_aff);
windowlisteparking=create_windowlisteparking ();
gtk_widget_show (windowlisteparking);
treeviewlistparking=lookup_widget(windowlisteparking,"treeviewlistparking");
afficher_rechercher_parking(treeviewlistparking);

}


void
on_treeviewlistparking_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_decroissante_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
 show_sorted_parkingscroi("parking.txt") ;
GtkWidget *windowlisteparking, *window_aff,*treeviewlistparking;
windowlisteparking=lookup_widget(button,"windowlisteparking");
gtk_widget_destroy(windowlisteparking);
windowlisteparking=create_windowlisteparking ();
gtk_widget_show (windowlisteparking);
treeviewlistparking=lookup_widget(windowlisteparking,"treeviewlistparking");
afficher_rechercher_parking(treeviewlistparking);

}


void
on_croisante_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 show_sorted_parkingsdecroi("parking.txt") ;
GtkWidget *windowlisteparking, *window_aff,*treeviewlistparking;
windowlisteparking=lookup_widget(button,"windowlisteparking");
gtk_widget_destroy(windowlisteparking);
windowlisteparking=create_windowlisteparking ();
gtk_widget_show (windowlisteparking);
treeviewlistparking=lookup_widget(windowlisteparking,"treeviewlistparking");
afficher_rechercher_parking(treeviewlistparking);

}


void
on_retourlist_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowlisteparking, *window_aff;
windowlisteparking=lookup_widget(button,"windowlisteparking");
gtk_widget_destroy(windowlisteparking);
window_aff=create_window_aff ();
gtk_widget_show (window_aff);
}


void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{


    GtkWidget *window1, *window_aff,*dialog;
    GtkWidget *logi, *mtp;

        char login1[100];
    char mot_de_passe[100];

    window1 = lookup_widget(GTK_WIDGET(button), "window1");
    logi = lookup_widget(GTK_WIDGET(button), "entry1");
    mtp = lookup_widget(GTK_WIDGET(button), "entry2");

    g_strlcpy(login1, gtk_entry_get_text(GTK_ENTRY(logi)), sizeof(login1)+20);
    g_strlcpy(mot_de_passe, gtk_entry_get_text(GTK_ENTRY(mtp)), sizeof(mot_de_passe)+20);

    

	if((strcmp("admin", login1) == 0) && (strcmp("admin", mot_de_passe) == 0)){

        gtk_widget_destroy(window1);
        window_aff = create_window_aff();
        gtk_widget_show(window_aff);

}

     else {
        dialog = gtk_message_dialog_new(NULL,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_ERROR,
                                         GTK_BUTTONS_OK,
                                         "Le nom d'utilisateur ou le mot de passe est incorrect");
        gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }






}

