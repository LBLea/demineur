#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(){
    //Initialisation des valeurs
    int taille = 5, nb_mines = 5, case_decouverte = 0, perdu = 0 ;
    int ligne = 0, colonne = 0, cpt = 0;
    int tabAffichage [taille][taille], tabValeurs[taille][taille];

    // Fonctions

    //fonction Affichage 
    
    //comment prof: definissez vos fonctions a l exterieur du main 
    
    void affichage(int tab[5][5]){
        for (int i = 0 ; i < taille ; i++){
            for(int j = 0 ; j < taille ; j++){
                printf("%d",tab[i][j]);
            }
            printf("\n");
        }
    }

    // Programme

    // Initialisation des deux tableaux à zero

    for (int i = 0 ; i<taille ; i++){
        for (int j = 0 ; j<taille ; j++){
            tabAffichage[i][j] = 0 ;
            tabValeurs[i][j] = 0 ;
        }
    }

    // Mise en place des mines
    // la mine aura la valeur 9
    srand(time(NULL));

    for ( int k = 0 ; k <nb_mines ; k++){
        tabValeurs[rand()%5][rand()%5] = 9 ;
    }

    affichage(tabValeurs);
    printf("________\n");

    // Calcul du nombre de mines voisines
    
    // comment prof: il est possible de faire beaucoup plus propre a mon avis :) perso pour eviter de me prendre la tete je prefere utilisr un tableau avec une marge de 1 (une ligne au dessus, en dessous, a gauche et a droite)
    
    for(int i=0; i< taille ; i++){
        for (int j = 0 ; j < taille ; j++){
            cpt = 0 ;
            if (tabValeurs[i][j]!=9){
                //ligne 0
                if (i==0){
                    if(j == 0){
                        if (tabValeurs[0][1]==9){
                            cpt ++;
                        }
                        if (tabValeurs[1][0]==9){
                            cpt ++;
                        }
                        if (tabValeurs[1][1]==9){
                            cpt ++;
                        }
                        tabValeurs[0][0] = cpt ;
                    }
                    else{
                        if(j == 4){
                            if (tabValeurs[0][3]==9){
                                cpt ++;
                            }
                            if (tabValeurs[1][3]==9){
                                cpt ++;
                            }
                            if (tabValeurs[1][4]==9){
                                cpt ++;
                            }
                            tabValeurs[0][4] = cpt ;
                        }
                        else{
                            if (tabValeurs[i][j-1]==9){
                                cpt ++;
                            }
                            if (tabValeurs[i][j+1]==9){
                                cpt ++;
                            }
                            if (tabValeurs[i+1][j-1]==9){
                                cpt ++;
                            }
                            if (tabValeurs[i+1][j]==9){
                                cpt ++;
                            }
                            if (tabValeurs[i+1][j+1]==9){
                                cpt ++;
                            }
                            tabValeurs[i][j]= cpt ;
                        }
                    }

                }

                //ligne 4
                if(i == 4 && j == 0){
                    if (tabValeurs[3][0]==9){
                        cpt ++;
                    }
                    if (tabValeurs[3][1]==9){
                        cpt ++;
                    }
                    if (tabValeurs[4][1]==9){
                        cpt ++;
                    }
                    tabValeurs[4][0] = cpt ;
                }
                if(i == 4 && j == 4){
                    if (tabValeurs[3][3]==9){
                        cpt ++;
                    }
                    if (tabValeurs[3][4]==9){
                        cpt ++;
                    }
                    if (tabValeurs[4][3]==9){
                        cpt ++;
                    }
                    tabValeurs[4][4] = cpt ;
                }
                //colonne 0

                //colonne 4
            }
        }
    }

    affichage(tabValeurs);



    // // Jeu
    // printf("%s\n", taille*taille - nb_mines);
    //
    // while ((case_decouverte < (taille*taille - nb_mines)) && perdu = 0){
    //     printf("Entrez le numero de la ligne\n");
    //     scanf("%s\n",ligne);
    //     printf("Entrez le numero de la colonne\n");
    //     scanf("%s\n",colonne);
    //
    //
    //     if (tabValeurs[ligne,colonne] == 9){
    //         perdu = 1 ;
    //     }
    //     else{
    //         // Attention ne pas compter une case déjà affichée.
    //         case_decouverte ++ ;
    //         affichage(tabValeurs) ;
    //     }
    // }
    //
    //
    //
    // //Commentaire de fin
    // if (case_decouverte == 1){
    //     printf("Bravo !\n");
    // }
    // if (perdu == 1){
    //     printf("BOOOOM ! Perdu !! \n");
    // }

    return 0;
}
