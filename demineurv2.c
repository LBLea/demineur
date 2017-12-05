//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int tabstock[7][7] ;

// Fonctions
// Fonction Affichage

void affichage(int tab[7][7], int taille){
    //system("clear");
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
        printf("\n______\n");
    }
}

void case_voisine2(int tab[7][7], int tab2[7][7], int taille, int lig, int col){
    tab[lig-1][col-1] = tab2[lig-1][col-1] ;
    tab[lig-1][col] = tab2[lig-1][col] ;
    tab[lig-1][col+1] = tab2[lig-1][col+1] ;

    tab[lig][col-1] = tab2[lig][col-1] ;
    tab[lig][col+1] = tab2[lig][col+1] ;

    tab[lig+1][col-1] = tab2[lig+1][col-1] ;
    tab[lig+1][col] = tab2[lig+1][col] ;
    tab[lig+1][col+1] = tab2[lig+1][col+1] ;
}

void case_voisine(int tabaff[7][7], int tabval[7][7], int taille, int lig, int col){
    // J'utilise un troisieme tableau stock pour ne pas me retrouver bloquer et
    // pouvoir faire tout le tour de la zone à découvrir
    // je change la valeur de la position du tableau une fois que je suis allée sur la case

    for (int i=1; i<taille-1 ; i++){
        for (int j=1; j<taille-1 ; j++){
            if (tabaff[lig][col] == 0){ // pas de mines sur les cases voisines
                // Je contrôle que la valeur disponible dans le tableau de Valeur est une case sans mine dans ces voisines
                // & je contrôle que je ne suis jamais allée sur cette case dans le tableau stock
                if (tabval[lig-1][col] == 0  && tabstock[lig-1][col] == -1){
                    tabstock[lig-1][col]=0;
                    //printf("ligne -1\n");
                    case_voisine2(tabaff,tabval,taille,lig,col); // Affichage des valeurs voisines
                    case_voisine(tabaff,tabval,taille,lig-1,col); // Appel recursif de la fonction

                }
                if (tabval[lig][col-1] == 0 && tabstock[lig][col-1] == -1){
                    tabstock[lig][col-1]=0;
                    //printf("col -1");
                    case_voisine2(tabaff,tabval,taille,lig,col); // Affichage des valeurs voisines
                    case_voisine(tabaff,tabval,taille,lig,col-1); // Appel recursif de la fonction

                }
                if (tabval[lig+1][col] == 0  && tabstock[lig+1][col] == -1){
                    tabstock[lig+1][col]=0;
                    //printf("ligne +1\n");
                    case_voisine2(tabaff,tabval,taille,lig,col); // Affichage des valeurs voisines
                    case_voisine(tabaff,tabval,taille,lig+1,col); // Appel recursif de la fonction
                }
                if (tabval[lig][col+1] == 0  && tabstock[lig][col+1] == -1){
                    tabstock[lig][col+1]=0;
                    //printf("col +1\n");
                    case_voisine2(tabaff,tabval,taille,lig,col); // Affichage des valeurs voisines
                    case_voisine(tabaff,tabval,taille,lig,col+1); // Appel recursif de la fonction
                }
                case_voisine2(tabaff,tabval,taille,lig,col); // Affichage des valeurs voisines
            }
        }
    }
}

int nb_case_decouverte(int tabaff[7][7], int taille){
    int nb_case_dec = 0 ;
    for (int i1=1 ; i1<taille-1 ; i1++){
        for (int j1=1 ; j1<taille-1 ; j1++){
            if (tabaff[i1][j1] != -1){
                nb_case_dec ++;
                //printf("%d \n",nb_case_dec);
            }
        }
    }
    return nb_case_dec ;
}

int main(){
    //Initialisation des valeurs
    int taille = 7, nb_mines = 5, continuer = 1, nb_case_dec ;
    int ligne = 0, colonne = 0, cpt = 0, val1, val2, nb_mines_placee = 0;
    int tabAffichage [taille][taille], tabValeurs[taille][taille];

    // Programme

    // Initialisation des tableaux

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

    // Mise en place des mines
    // la mine aura la valeur 9
    srand(time(NULL));
    while (nb_mines_placee < 5){
        val1 = 1+rand()%5 ;
        val2 = 1+rand()%5 ;
        if (tabValeurs[val1][val1]!=9){
            tabValeurs[val1][val2] = 9 ;
            nb_mines_placee++;
        }
    }

    // Calcul du nombre de mines voisines
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

    // Jeu

    affichage(tabValeurs,taille);
    while (continuer == 1){
        ligne = -1 ;
        while (ligne < 0 || taille-2 < ligne){
            printf("Entrez le numero de la ligne entre 1 et 5\n");
            scanf("%d",&ligne);
        }
        colonne =-1;
        while (0>colonne || colonne > taille-1){
            printf("Entrez le numero de la colonne entre 1 et 5\n");
            scanf("%d",&colonne);
        }

        //Si je tombe sur une mine
        if (tabValeurs[ligne][colonne] == 9){
            continuer = 0 ;
            tabAffichage[ligne][colonne] = 9 ;
            affichage(tabValeurs,taille) ;
            printf("Vous avez perdu\n");
        }

        //Si je ne tombe pas sur une mine
        else{
            if (tabAffichage[ligne][colonne] == -1 ){
                tabAffichage[ligne][colonne] = tabValeurs[ligne][colonne] ;
                case_voisine(tabAffichage,tabValeurs,taille,ligne,colonne);
                affichage(tabAffichage,taille) ;
                if ( nb_case_decouverte(tabAffichage,taille) == ((taille-2)*(taille-2) - nb_mines)){
                    printf("Bravo !\n");
                    continuer = 0 ;
                }
            }
            else{
                printf("Cette case est deja decouverte \n");
            }
        }
    }
    return 0;
}
