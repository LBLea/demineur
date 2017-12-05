//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonctions
static int cpt ;
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
    static int tabstock[7][7] ;


void case_voisine(int tabaff[7][7], int tabval[7][7], int taille, int lig, int col){
    for (int i=1; i<taille-1 ; i++){
        for (int j=1; j<taille-1 ; j++){
            if (tabaff[lig][col] == 0){
                if (tabval[lig-1][col] == 0  && tabstock[lig-1][col] == -1){
                    cpt++;
                    tabstock[lig-1][col]=0;
                    //printf("ligne -1\n");
                    case_voisine2(tabaff,tabval,taille,lig,col);
                    case_voisine(tabaff,tabval,taille,lig-1,col);

                }
                if (tabval[lig][col-1] == 0 && tabstock[lig][col-1] == -1){
                    cpt++;
                    tabstock[lig][col-1]=0;
                    //printf("col -1");
                    case_voisine2(tabaff,tabval,taille,lig,col);
                    case_voisine(tabaff,tabval,taille,lig,col-1);

                }
                if (tabval[lig+1][col] == 0  && tabstock[lig+1][col] == -1){
                    cpt++;
                    tabstock[lig+1][col]=0;
                    //printf("ligne +1\n");
                    case_voisine2(tabaff,tabval,taille,lig,col);
                    case_voisine(tabaff,tabval,taille,lig+1,col);
                }
                if (tabval[lig][col+1] == 0  && tabstock[lig][col+1] == -1){
                    cpt++;
                    tabstock[lig][col+1]=0;
                    //printf("col +1\n");
                    case_voisine2(tabaff,tabval,taille,lig,col);
                    case_voisine(tabaff,tabval,taille,lig,col+1);
                }
                case_voisine2(tabaff,tabval,taille,lig,col);
            }
        }
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
                case_decouverte ++ ;
                for (int i = 0 ; i<taille-1 ; i++){
                    for (int j = 0 ; j<taille-1 ; j++){
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
                case_voisine(tabAffichage,tabValeurs,taille,ligne,colonne);
                affichage(tabAffichage,taille) ;

                if (case_decouverte == (taille-2)*(taille-2) - nb_mines){
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
