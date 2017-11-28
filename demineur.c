#include <stdio.h>
#include <stdlib.h>
#include <time.h>


 
int main(){

    int tableau[10], niveau, ok = 0 , nb_secret ;
    int nb_erreurs = 0, nb_sachet_bon = 0, perdu = 0, choix ;

    // Initialisation du tableau
    for (int i=0; i<10 ;i++){
        tableau[i] = 0 ;
    }

    // Choix du niveau
    while (ok == 0){
        printf("Choisir un niveau :\n easy   -> 0 \n medium -> 1 \n master -> 2 \n");
        scanf("%d", &niveau);
        if (niveau <3 && niveau >=0){
            ok = 1;
        }
    }



    // Creation des erreurs

    // Niveau Easy 1 erreur
    srand(time(NULL));


    if (niveau == 0){
        nb_secret = rand()%9 ;
        tableau[nb_secret] = 1 ;

    }

    else{
        // Nibeau Medium 2 erreurs
        if (niveau == 1){
            while(nb_erreurs<2){
            nb_secret = rand()%9 ;
                if (tableau[nb_secret]==0){
                    nb_erreurs ++ ;
                    tableau[nb_secret] = 1 ;
                }
            }
        }

        // Nibeau Master 3 erreurs
        else{
            while(nb_erreurs<3){
            nb_secret = rand()%9 ;
                if (tableau[nb_secret]==0){
                    nb_erreurs ++ ;
                    tableau[nb_secret] = 1 ;
                }
            }
        }

    }

    printf("Vous avez choisi le niveau : %d\n", niveau);


    while( perdu == 0 && nb_sachet_bon < 3){
        // Etat du rayon
        for(int j = 0 ; j<10 ; j++){
            if (tableau[j]==-1){
                printf("| ");
            }
            else{
                printf("|■");
            }
            if (j==9){
                printf("| \n");
            }

        }


        printf("Veuillez choisir un paquet de gruyere entre 1 et 10\n\n");
        scanf("%d",&choix);

        if(choix < 11 && choix > 0){
            if(tableau[choix-1]==1){
                printf("BOOOOOOOM \n");
                perdu = 1;
            }
            else{
                if(tableau[choix-1]==0){
                    tableau[choix-1]= -1;
                    nb_sachet_bon ++ ;
                    printf("OUFF... ! Vous avez %d sachet(s) bon\n",nb_sachet_bon);
                }
                else{
                    printf("Vous avez deja fait ce choix\n");
                }
            }
        }

    }



    return 0 ;
}
