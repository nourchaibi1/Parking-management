#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include <stdlib.h>
#include <stdio.h>



///
void run_command(const char *command, const char *directory) {
    char full_command[1024];
    snprintf(full_command, sizeof(full_command), "cd %s && %s", directory, command);

    int result = system(full_command);
    if (result != 0) {
        fprintf(stderr, "Error: Command failed with code %d\n", result);
    }
}



int run_new_t(const char *command, const char *dir) {
    // Construct the terminal command to open a new terminal and run the command
    char terminal_command[1024];
    snprintf(terminal_command, sizeof(terminal_command),
             "gnome-terminal -- bash -c 'cd %s && %s; exec bash'", dir, command);
    
    // Run the terminal command
    if (system(terminal_command) == 0) {
        printf("Command executed successfully in a new terminal in directory: %s\n", dir);
        return 1;
    } else {
        perror("Failed to open new terminal or execute command");
        return 0;
    }
}













void
on_inscription_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
const char *d = "p3/src" ;

run_new_t("./reservation",d);


}


void
on_loginbtn_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
const char *d = "p1/src" ;


run_new_t("./gestparking ",d);

}


void
on_p2_clicked                          (GtkButton       *button,
                                        gpointer         user_data)
{
const char *d = "p2/src" ;

run_new_t("./projectagent",d);



}


	

	



