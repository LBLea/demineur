#include <gtk/gtk.h>

//variables globales
int tab[8][8];
GtkWidget *button_table[8][8]={0};

GdkColor red = {0, 0xffff, 0x0000, 0x0000};
GdkColor blue = {0, 0x0000, 0x0000, 0xffff};
GdkColor green = {0, 0x0000, 0xffff,0x0000, };


static void a_button_clicked(GtkWidget *widget,gpointer data)
{
    int x,y;

    //Je recupère les données x et y que j'ai caché dans les propriétés x et y de mon objet
    x=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"x"));
    y=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"y"));

    //Je change mon button (label + profondeur)
    gtk_button_set_label(GTK_BUTTON (widget),"0");
    gtk_button_set_relief(GTK_BUTTON(widget),GTK_RELIEF_NONE);

    //idem pour la case à proximité (avec un changement de couleur pout tester)
    gtk_button_set_label(GTK_BUTTON (button_table[x][y-1]),"5");
    gtk_button_set_relief(GTK_BUTTON(button_table[x][y-1]),GTK_RELIEF_NONE);
    //gtk_widget_modify_fg(button_table[x][y-1], GTK_STATE_NORMAL,&red);


}

static void activate (GtkApplication *app,gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;

    int nb_rows=8;
    int x, y;

    /* create a new window, and set its title */
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);

    // Création de la grille
    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);

    for (x=0;x<nb_rows;x++)
    {
       for (y=0;y<nb_rows;y++)
       {
          //construct the button id
          button_table[x][y]= gtk_button_new_with_label(" ");

          // j'ajoute des données perso x et y pour chaque bouton
          g_object_set_data(G_OBJECT(button_table[x][y]),"x",GINT_TO_POINTER(x));
          g_object_set_data(G_OBJECT(button_table[x][y]),"y",GINT_TO_POINTER(y));

          // je connecte mon bouton à la fonction callback a_button_clicked
          g_signal_connect(button_table[x][y], "clicked", G_CALLBACK (a_button_clicked), NULL);
          gtk_grid_attach(GTK_GRID (grid),button_table[x][y], x, y, 1, 1);
       }
    }
    gtk_widget_show_all (window);
}


int main (int    argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}
