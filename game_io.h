#ifndef GAME_IO
#define GAME_IO


#define SCREEN_WIDTH    159
#define SCREEN_HEIGHT   99

#define NB_CELLS_HORIZ  10
#define NB_CELLS_VERT   10

#define CELL_WIDTH      10
#define CELL_HEIGHT     8

#define OFFSET_HORIZ    (SCREEN_WIDTH - NB_CELLS_HORIZ * CELL_WIDTH ) / 2
#define OFFSET_VERT     2


// fonction qui affiche une string centrée horizontalement
void xorCenteredStr(short row, const char * str, short font);

// fonction qui dessine le tableau de jeu
void drawBoard(void);

// fonction qui XOR le curseur
void xorCursor(short i, short j);

// fonction qui efface le contenu d'une cellule
void clearCell(short i, short j);

// fonction qui affiche une cellule en vidéo inverse
void reverseCell(short i, short j);

// fonction qui met en valeur une cellule
void hilightCell(short i, short j);

// fonction qui affiche un chiffre (ou le drapeau) dans une cellule
void printInCell(short i, short j, short number);

// fonction qui permet d'effacer la zone de texte située sous le tableau
void clearMessages(void);


#endif
