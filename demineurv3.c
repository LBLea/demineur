#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include <string.h>

static int tabstock[7][7], tabValeurs[7][7];
static int tabAffichage[7][7], taille = 7, perdu = 0 ;
int tab[5][5];
GtkWidget *button_table[5][5];

    //______________FONCTIONS______________

void init(int taille,int tabAffichage[7][7],int tabValeurs[7][7], int nb_mines_placee, int cpt){

    //___Initialisation des valeurs
    int val1, val2 ;
    //___Initialisation des tableaux
    for (int i = 0 ; i<taille ; i++){
        for (int j = 0 ; j<taille ; j++){
            tabAffichage[i][j] = -1 ;
            tabValeurs[i][j] = 0 ;
            if (0<i && i<6){
               if (0<j && j<6){
                   tabstock[i][j] = -1 ;
               }
               else{
                   tabstock[i][j] = -2 ;
               }
           }
           else {
               tabstock[i][j] = -2 ;
           }
        }
    }

    //___Initialisation des mines
    srand(time(NULL));
    while (nb_mines_placee < 5){
        val1 = 1+rand()%5 ;
        val2 = 1+rand()%5 ;
        if (tabValeurs[val1][val1]!=9){
            tabValeurs[val1][val2] = 9 ;
            nb_mines_placee++;
        }
    }

    //___Calcul du nombre de mines voisines
    for (int i=1 ; i<(taille-1) ; i++){
        for (int j=1 ; j<(taille-1) ; j++){
            cpt = 0;
            if (tabValeurs[i][j]!=9){
                if (tabValeurs[i-1][j-1]==9){
                    cpt++;
                }
                if (tabValeurs[i-1][j]==9){
                    cpt++;
                }
                if (tabValeurs[i-1][j+1]==9){
                    cpt++;
                }
                if (tabValeurs[i][j-1]==9){
                    cpt++;
                }
                if (tabValeurs[i][j+1]==9){
                    cpt++;
                }
                if (tabValeurs[i+1][j-1]==9){
                    cpt++;
                }
                if (tabValeurs[i+1][j]==9){
                    cpt++;
                }
                if (tabValeurs[i+1][j+1]==9){
                    cpt++;
                }
                tabValeurs[i][j] = cpt ;
            }
        }
    }
}

void affichage(int tab[7][7], int taille){
    system("clear");
    for (int i = 1 ; i < taille-1 ; i++){
        for(int j = 1 ; j < taille-1 ; j++){
            if (tab[i][j]==-1){
                printf("□|");
            }
            else{
                if (tab[i][j]==0){
                    printf(" |");
                }
                else{
                    printf("%d|",tab[i][j]);
                }
            }
        }
        printf("\n_________\n");
    }
}

void afficher_case(int lig, int col){
    char val2[10] = " " ;
    sprintf(val2,"%c",tabValeurs[lig+1][col+1]+48);
    gtk_button_set_label(GTK_BUTTON (button_table[col][lig]),val2);
    gtk_button_set_relief(GTK_BUTTON(button_table[col][lig]),GTK_RELIEF_NONE);
}

void case_voisine2(int lig, int col){
    // case actuelle
    afficher_case(lig-1,col-1);
    if (lig-1 >0){
        if (col-1>0){
            afficher_case(lig-2,col-2); // en haut a gauche
        }
        afficher_case(lig-2,col-1); // en haut
        if (col+1 < 5){
            afficher_case(lig-2,col); // en haut a droite
        }
    }
    if (col-1>0){
        afficher_case(lig-1,col-2); // a gauche
    }
    //a droite
    if (col+1 < 5){
        afficher_case(lig-1,col); // a droite
    }
    if (lig+1<5){
        if (col-1>0){
            afficher_case(lig,col-2); // en bas a gauche
        }
        //en bas
        afficher_case(lig,col-1); // en bas
        if (col+1 < 5){
            afficher_case(lig,col); // en bas a droite
        }
    }
}

void case_voisine(int lig, int col){
    // J'utilise un troisieme tableau stock pour ne pas me retrouver bloquer et
    // pouvoir faire tout le tour de la zone à découvrir
    // je change la valeur de la position du tableau une fois que je suis allée sur la case
    for (int i=1; i<taille-1 ; i++){
        for (int j=1; j<taille-1 ; j++){

                // Je contrôle que la valeur disponible dans le tableau de Valeur est une case sans mine dans ces voisines
                // & je contrôle que je ne suis jamais allée sur cette case dans le tableau stock
            if (tabValeurs[lig-1][col] == 0  && tabstock[lig-1][col] == -1){
                tabstock[lig-1][col]=0;
                case_voisine2(lig,col); // Affichage des valeurs voisines
                if (lig-1 >0){
                    case_voisine(lig-1,col); // Appel recursif de la fonction
                }
            }
            if (tabValeurs[lig][col-1] == 0 && tabstock[lig][col-1] == -1){
                tabstock[lig][col-1]=0;
                case_voisine2(lig,col); // Affichage des valeurs voisines
                if (col-1 >0){
                    case_voisine(lig,col-1); // Appel recursif de la fonction
                }
            }
            if (tabValeurs[lig+1][col] == 0  && tabstock[lig+1][col] == -1){
                tabstock[lig+1][col]=0;
                case_voisine2(lig,col); // Affichage des valeurs voisines
                if (lig+1 <6){
                    case_voisine(lig+1,col); // Appel recursif de la fonction
                }
            }
            if (tabValeurs[lig][col+1] == 0  && tabstock[lig][col+1] == -1){
                tabstock[lig][col+1]=0;
                case_voisine2(lig,col); // Affichage des valeurs voisines
                if (col+1<6){
                    case_voisine(lig,col+1); // Appel recursif de la fonction
                }
            }
            case_voisine2(lig,col); // Affichage des valeurs voisines
        }
    }
}

// int nb_case_decouverte(){
//     int nb_case_dec = 0 ;
//     int v;
//     sprintf(v,"%s","   ");
//     for (int i1=0 ; i1<5 ; i1++){
//         for (int j1=0 ; j1<5 ; j1++){
//             sprintf(v,"%s",gtk_button_get_label(GTK_BUTTON(button_table[i1][j1])));
//             if (v==0|| v==1){
//                 nb_case_dec ++;
//                 printf("%d \n",nb_case_dec);
//             }
//         }
//     }
//     return nb_case_dec ;
// }

static void a_button_clicked(GtkWidget *widget,gpointer data){
    int x,y;

    //Je recupère les données x et y que j'ai caché dans les propriétés x et y de mon objet
    x=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"x")); // x -> col
    y=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"y")); // y -> lig
    //Je change mon button (label + profondeur)
    char val[10];
    //Il n'y a pas de mines dans les cases voisines
    if (tabValeurs[y+1][x+1]==0 && perdu ==0){
        case_voisine(y+1,x+1);
        //nb_case_decouverte();
    }
    //Il y a une plusieurs mines dans les cases voisines
    else {
        // Si je perds, le jeu s'arrete
        if (tabValeurs[y+1][x+1]==9 && perdu ==0){
            printf("Fin de partie\n");
            perdu = 1 ;
            for (int i =0;i<5;i++){
                for (int j=0;j<5;j++){
                    afficher_case(i,j);
                }
            }
        }
        // Le jeu continue
        else{
            if (perdu==0){
                sprintf(val,"%c",tabValeurs[y+1][x+1]+48);
                gtk_button_set_label(GTK_BUTTON (widget),val);
                gtk_button_set_relief(GTK_BUTTON(widget),GTK_RELIEF_NONE);
                //nb_case_decouverte();
            }
        }
    }
}

static void activate (GtkApplication *app,gpointer user_data){
    GtkWidget *window;
    GtkWidget *grid;

    int nb_rows=5;
    int x, y;

    /* create a new window, and set its title */
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "DEMINEUR");
    gtk_container_set_border_width(GTK_CONTAINER (window), 40);

    // Création de la grille
    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);

    for (x=0;x<nb_rows;x++){
       for (y=0;y<nb_rows;y++){
          //construct the button id
          button_table[x][y]= gtk_button_new_with_label("   ");

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

int main (int    argc, char **argv){
    //___Initialisation valeurs
    int nb_mines = 5, continuer = 1, nb_case_dec ;
    int ligne = 0, colonne = 0, cpt = 0, nb_mines_placee = 0;

    init(taille,tabAffichage,tabValeurs, nb_mines_placee, cpt);

    //affichage(tabValeurs, taille);
    printf("Demarrage du demineur\n");
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    //lancement de la fenetre
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
