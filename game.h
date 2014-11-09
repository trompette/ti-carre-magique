#ifndef GAME
#define GAME


// pour faciliter la lecture du code
typedef short Key;


// fonction qui réinitialise le tableau de jeu
void resetBoard();

// fonction qui renvoie TRUE si une cellule n'est pas occupée
BOOL isEmptyCell(short i, short j);

// fonction qui renvoie TRUE si un coup est valide
BOOL isLegalMove(short i, short j, Key move);

// fonction qui renvoie TRUE si le jeux est fini (joueur bloqué)
BOOL isGameFinished(short i, short j);

// fonction qui affiche l'écran d'accueil
void printWelcomeScreen(void);

// fonction qui permet de choisir la première cellule
void chooseFirstCell(short * i, short * j);

// fonction qui met en valeur toutes les cases jouables
void hilightPlayableCells(short i, short j);

// fonction qui vide la liste des coups joués
void resetSavedMoves();

// fonction qui permet de sauver le coup joué
void saveMove(short i, short j, short score);

// fonction qui annule le dernier coup joué
void popLastMove();

// fonction qui lance la boucle du jeu
void play(void);


#endif
