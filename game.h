#ifndef GAME
#define GAME


// pour faciliter la lecture du code
typedef short Key;


// fonction qui r�initialise le tableau de jeu
void resetBoard();

// fonction qui renvoie TRUE si une cellule n'est pas occup�e
BOOL isEmptyCell(short i, short j);

// fonction qui renvoie TRUE si un coup est valide
BOOL isLegalMove(short i, short j, Key move);

// fonction qui renvoie TRUE si le jeux est fini (joueur bloqu�)
BOOL isGameFinished(short i, short j);

// fonction qui affiche l'�cran d'accueil
void printWelcomeScreen(void);

// fonction qui permet de choisir la premi�re cellule
void chooseFirstCell(short * i, short * j);

// fonction qui met en valeur toutes les cases jouables
void hilightPlayableCells(short i, short j);

// fonction qui vide la liste des coups jou�s
void resetSavedMoves();

// fonction qui permet de sauver le coup jou�
void saveMove(short i, short j, short score);

// fonction qui annule le dernier coup jou�
void popLastMove();

// fonction qui lance la boucle du jeu
void play(void);


#endif
