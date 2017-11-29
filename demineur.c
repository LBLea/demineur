#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Fonctions

// Fonction Affichage
void affichage(int tab[7][7], int taille){
    for (int i = 1 ; i < taille-1 ; i++){
        for(int j = 1 ; j < taille-1 ; j++){
            if (tab[i][j]==-1){
                printf("□|");
            }
            else{
                printf("%d|",tab[i][j]);
            }
        }
        printf("\n______\n");
    }
}


int main(){
    //Initialisation des valeurs
    int taille = 7, nb_mines = 5, continuer = 1, case_decouverte = 0 ;
    int ligne = 0, colonne = 0, cpt = 0;
    int tabAffichage [taille][taille], tabValeurs[taille][taille];

    // Programme

    // Initialisation des deux tableaux à zero

    for (int i = 0 ; i<taille ; i++){
        for (int j = 0 ; j<taille ; j++){
            tabAffichage[i][j] = -1 ;
            tabValeurs[i][j] = 0 ;
        }
    }

    // Mise en place des mines
    // la mine aura la valeur 9
    srand(time(NULL));

    for ( int k = 0 ; k <nb_mines ; k++){
        tabValeurs[1+rand()%5][1+rand()%5] = 9 ;
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
        //ligne = -1 ;
        //while (ligne < 0 || taille-2 < ligne){
            printf("Entrez le numero de la colonne entre 1 et 5\n");
            scanf("%d\n",&ligne);
        //}
        //colonne =-1;
        //while (0>colonne || colonne > taille-1){
            printf("Entrez le numero de la ligne entre 1 et 5\n");
            scanf("%d\n",&colonne);
        //}

        //Si je tombe sur une mine
        if (tabValeurs[ligne][colonne] == 9){
            continuer = 0 ;
            tabAffichage[ligne][colonne] = 9 ;
            printf("Vous avez perdu\n");
            affichage(tabAffichage,taille) ;
        }
        //Si je ne tombe pas sur une mine
        else{
            if (tabAffichage[ligne][colonne] == -1 ){
                tabAffichage[ligne][colonne] = tabValeurs[ligne][colonne] ;
                case_decouverte ++ ;
                affichage(tabAffichage,taille) ;

                if (case_decouverte == (taille-2)*2 - nb_mines){
                    printf("Bravo !\n");
                    continuer = 0 ;
                }
            }
        }
    }



    //Commentaire de fin


    return 0;
}
