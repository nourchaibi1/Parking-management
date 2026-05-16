#include <gtk/gtk.h>


void
on_checkbutton_confpark_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_disp_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_nndisp_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_addpark_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_retaj_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_moddisp_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_modnndisp_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_modconf_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_retmod_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_confmod_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_affres_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_modrs_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechres_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprs_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajrs_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_affrech_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_affrech_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_Retrech_clicked              (GtkButton       *button,
                                        gpointer         user_data);
