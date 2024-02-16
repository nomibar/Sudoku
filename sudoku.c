
/**
*
* \brief Implémentation d'un jeu Sudoku
*
* \author BARBOTAUD
*
* \version 1.5.2
*
* \date 1 NOVEMBRE 2023
*
* ce programme propose un jeu de sudoku 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*****************************************************
                  * DEFINE *
*****************************************************/

#define N 3 //taille d'un bloc
#define TAILLE N*N //taille de la grille

/*****************************************************
                  * STRUCTURE *
*****************************************************/

/**
*
* \typedef typTab
*
* \brief type tableau de TAILLE de longueur et TAILLE de largueur
*
* Le type typTab sert de grille pour jouer au sudoku 
*
*/

typedef int tGrille[TAILLE][TAILLE]; // Définition du type pour la grille Sudoku

tGrille grille1;

/*****************************************************
                  *  GLOBALES *
*****************************************************/


int numLigne, numColonne, valeur; 

/*****************************************************
            * FONCTION ET PROCEDURE *
*****************************************************/


/**
 * \fn chargerGrille(tGrille g)
 * \brief Charge une grille Sudoku depuis un fichier .
 * \param g La grille Sudoku à charger.
 */

void chargerGrille(tGrille g){

    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
   
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
        } else {
            fread(g, sizeof(int), TAILLE*TAILLE, f);
        }
        fclose(f);
}

/**
 * \fn afficherGrille(tGrille t)
 * \brief Affiche la grille Sudoku.
 * \param t La grille Sudoku à afficher.
 */
void afficherGrille(tGrille t){
    printf("    1  2  3   4  5  6   7  8  9 \n");
    int ligne; // indice de ligne
    int colonne; // indice de colonne
    for (ligne=0 ; ligne<TAILLE ; ligne++){
        if (ligne%N==0){
            printf("  +---------+---------+---------+\n");
        }
        printf("%d |",ligne+1);
        for(colonne=0 ; colonne<TAILLE ; colonne++){
            // acces a chaque case t[ligne][colonne] du tableau
            if (colonne%N==0 && colonne!=0){
                printf("|");//tout les N valeur affiche un | pour la formatation
            }
            if (t[ligne][colonne]==0){
                printf(" . ");//affiche un . quand la case est vide 
            }
            
            else{
                printf(" %d ",t[ligne][colonne]);//affiche la case du tableau correspondante
            }
        }
        printf("|\n");
            
    }
    printf("  +---------+---------+---------+\n");
    
}

/**
 * \fn pleine(tGrille t)
 * \brief Vérifie si la grille Sudoku est pleine.
 * \param t La grille Sudoku à vérifier.
 * \return Vrai si la grille est pleine, faux sinon.
 * Consiste à vérifier si toutes les cases de la grille sont remplies.
 */

bool pleine(tGrille t){
    int ligne; // indice de ligne
    int colonne; // indice de colonne
    bool verif = true;
    for (ligne=0 ; ligne<TAILLE ; ligne++){
        for (colonne=0 ; colonne<TAILLE ; colonne++){
            // acces a chaque case t[ligne][colonne] du tableau
            if (t[ligne][colonne] == 0){
                verif=false; //si on rencontre une case vide on renvoie faux 
            }
        }
        
    }
    return verif;
    
}

/**
 * \fn saisir(int *val)
 * \brief Lit une entrée entière dans une plage spécifiée.
 * \param val Pointeur pour stocker la valeur d'entrée.
 */
void saisir(int *val){
    char ch[100];
    printf("entier entre 1 et %d : ",TAILLE);
    scanf("%s",ch);


    while (sscanf(ch, "%d", val) != 1 || *val > TAILLE || *val < 1 || ch[1] != '\0') {

        printf("erreur reesayer \n");
        printf("entier entre 1 et %d : ",TAILLE);
        scanf("%s",ch);
    }

   
}

/**
 * \fn possible(tGrille t, int nbligne, int nbcolonne, int val)
 * \brief Vérifie s'il est possible d'insérer une valeur à une position spécifique dans la grille Sudoku.
 * \param t La grille Sudoku.
 * \param nbligne Indice de ligne.
 * \param nbcolonne Indice de colonne.
 * \param val La valeur à insérer.
 * \return Vrai si l'insertion est possible, faux sinon.
 * Consiste à vérifier les contraintes du Sudoku pour l'insertion de la valeur à la position spécifiée.
 */

bool possible(tGrille t ,int nbligne,int nbcolonne , int val){
    int ligne,colonne; //indice de ligne et de colonne

    int resteligne,restecol;//reste de la division de nbligne et nbcolonne par N
    int valligne,valcol;//valeur temporaire de nbligne et nbcolonne
    bool verifie = true;

    valligne=nbligne; 
    valcol=nbcolonne;

    for(ligne=0;ligne<TAILLE;ligne++){
        if(t[nbligne][ligne]== val || t[ligne][nbcolonne] == val){ // on verifie la ligne et la colonne 
            verifie= false;
        }

    }
    
    valligne=valligne+1;
    valcol=valcol+1;

    resteligne=nbligne%N; // reste de la division pour connaitre la case dans le sudoku 
    restecol=nbcolonne%N;// reste de la division pour connaitre la case dans le sudoku

    valligne=valligne-resteligne; // on se position en haut a gauche du block 
    valcol=valcol-restecol;// on se position en haut a gauche du block 

    for(ligne=0;ligne<N;ligne++){
        for(colonne=0;colonne<N;colonne++){//on parcours en le block en 3 par 3
            if((t[valligne+ligne-1][valcol+colonne-1]==val) && (t[valligne+ligne-1][valcol+colonne-1]!=t[nbligne-1][nbcolonne-1])){// on verfie chaque case sauf celle ou l'on est 
                verifie= false; 
                
            }
        }

    }
    return verifie;
}


/*****************************************************
            * PROGRAMME PRINCIPAL *
*****************************************************/


/**
 * \fn main()
 * \brief Fonction principale pour jouer au Sudoku.
 */
int main(){
    bool booleen = false;
    tGrille grille1={};
    
    afficherGrille(grille1);
    booleen=pleine(grille1); 
   
    while(booleen==false){
        
        afficherGrille(grille1);
        booleen=pleine(grille1);
        
        printf("Indices de la case ? \n");
        printf("num ligne :");
        saisir(&numLigne);

        printf("num colonne :");
        saisir(&numColonne);
        printf("ligne :%d colonne: %d \n",numLigne,numColonne);
        numLigne=numLigne-1;
        numColonne=numColonne-1;
        
      
        if(grille1[numLigne][numColonne] != 0){

            printf("IMPOSSIBLE, la case n'est pas libre. \n");

        }
        else{
            printf("Valeur à insérer ? ");
            saisir(&valeur);
            printf("ligne :%d colonne: %d \n",numLigne,numColonne);
            if (possible(grille1, numLigne, numColonne, valeur)){
                
                grille1[numLigne][numColonne] = valeur;
            }
            else{
                printf("impossible valeurs impossible \n");
            }
        }
        

    }
    printf("Grille pleine, fin de partie");



}
