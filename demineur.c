#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(){
    //Initialisation des valeurs
    int taille = 5, nb_mines = 5, case_decouverte = 0, perdu = 0 ;
    int ligne = 0, colonne = 0 ;
    int tabAffichage [taille][taille], tabValeurs[taille][taille];

    // Fonctions

    //fonction Affichage
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
