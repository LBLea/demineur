#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GdkEvent *event;
    gpointer user;
    GObject *button;

    gtk_init (&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "essaie1.ui", NULL);

    /* Connect signal handlers to the constructed widgets. */
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    gtk_builder_connect_signals (builder, NULL);
    gtk_widget_show(window);
    gtk_main();


    g_signal_connect(GTK_OBJECT (table), "button-press-event",G_CALLBACK (table_press), NULL);


    user_function (window, GdkEvent  *event, gpointer   user_data)



    //
//
//     const gchar * 	gtk_button_get_label ()
//     void 	gtk_button_set_label ()
//
//
//     void button_press_event()



    return EXIT_SUCCESS;
}
