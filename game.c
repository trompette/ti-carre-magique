#include <tigcclib.h>
#include "game.h"
#include "game_io.h"


typedef struct _container
{
    void * data;
    struct _container * prev;
} Container;

typedef struct _move
{
    short i, j;
    short score;
} Move;


// le tableau de jeu
static BOOL board[10][10];

// la liste chaînée des coups joués
static Container * moves;


// fonction qui réinitialise le tableau de jeu
void resetBoard()
{
    int i, j;

    for(i = 0; i < NB_CELLS_VERT; i++)
        for(j = 0; j < NB_CELLS_HORIZ; j++)
            board[i][j] = TRUE;
}


// fonction qui renvoie TRUE si la cellule est vide
BOOL isEmptyCell(short i, short j)
{
    if( i < 0 || 9 < i || j < 0 || 9 < j )
        return FALSE;

    return board[i][j];
}


// fonction qui renvoie TRUE si un coup est valide
BOOL isLegalMove(short i, short j, Key move)
{
    switch( move )
    {
        case '1': return isEmptyCell(i+2, j-2);
        case '2': return isEmptyCell(i+3, j);
        case '3': return isEmptyCell(i+2, j+2);
        case '6': return isEmptyCell(i, j+3);
        case '9': return isEmptyCell(i-2, j+2);
        case '8': return isEmptyCell(i-3, j);
        case '7': return isEmptyCell(i-2, j-2);
        case '4': return isEmptyCell(i, j-3);
        default:  return FALSE;
    }
}


// fonction qui renvoie TRUE si le jeux est fini (joueur bloqué)
BOOL isGameFinished(short i, short j)
{
    return ! ( isLegalMove(i, j, '1') || isLegalMove(i, j, '2')
            || isLegalMove(i, j, '3') || isLegalMove(i, j, '6')
            || isLegalMove(i, j, '9') || isLegalMove(i, j, '8')
            || isLegalMove(i, j, '7') || isLegalMove(i, j, '4') );
}


// fonction qui affiche l'écran d'accueil
void printWelcomeScreen(void)
{
    Key key;

    xorCenteredStr(10, "CARRE MAGIQUE", F_8x10);
    xorCenteredStr(22, "version 2.0", F_4x6);
    xorCenteredStr(70, "[Enter] pour jouer, [ESC] pour quitter.", F_4x6);
    xorCenteredStr(94, "Réécrit en C par Bob.", F_4x6);

    do
    {
        key = ngetchx();

        if( key == KEY_ESC )
            exit(0);
    }
    while( key != KEY_ENTER );
}


// fonction qui permet de choisir la première cellule
void chooseFirstCell(short * i, short * j)
{
    Key key;

    // on affiche un petit message et le curseur
    xorCenteredStr(84, "Choisissez la première case.", F_4x6);
    xorCursor(*i, *j);

    // on gère le mouvement du curseur jusqu'à validation
    do
    {
        key = ngetchx();

        if( key == KEY_DOWN && *i < NB_CELLS_VERT - 1 )
        {
            xorCursor(*i, *j);
            ++*i;
            xorCursor(*i, *j);
        }

        if( key == KEY_UP && 0 < *i )
        {
            xorCursor(*i, *j);
            --*i;
            xorCursor(*i, *j);
        }

        if( key == KEY_RIGHT && *j < NB_CELLS_HORIZ - 1 )
        {
            xorCursor(*i, *j);
            ++*j;
            xorCursor(*i, *j);
        }

        if( key == KEY_LEFT && 0 < *j )
        {
            xorCursor(*i, *j);
            --*j;
            xorCursor(*i, *j);
        }
    }
    while( key != KEY_ENTER );

    // on efface le curseur
    xorCursor(*i, *j);
}


// fonction qui met en valeur toutes les cases jouables
void hilightPlayableCells(short i, short j)
{
    if( isLegalMove(i, j, '1') )
        hilightCell(i+2, j-2);

    if( isLegalMove(i, j, '2') )
        hilightCell(i+3, j);

    if( isLegalMove(i, j, '3') )
        hilightCell(i+2, j+2);

    if( isLegalMove(i, j, '6') )
        hilightCell(i, j+3);

    if( isLegalMove(i, j, '9') )
        hilightCell(i-2, j+2);

    if( isLegalMove(i, j, '8') )
        hilightCell(i-3, j);

    if( isLegalMove(i, j, '7') )
        hilightCell(i-2, j-2);

    if( isLegalMove(i, j, '4') )
        hilightCell(i, j-3);
}


// fonction qui vide la liste des coups joués
void resetSavedMoves()
{
    Container * prev;

    if( ! moves )
        return;

    while( moves )
    {
        prev = moves->prev;

        free(moves->data);
        free(moves);

        moves = prev;
    }
}


// fonction qui permet de sauver le coup joué
void saveMove(short i, short j, short score)
{
    Move * m = (Move *)calloc(1, sizeof(*m));
    m->i = i;
    m->j = j;
    m->score = score;

    Container * c = (Container *)calloc(1, sizeof(*c));
    c->data = m;
    c->prev = moves;

    moves = c;
}


// fonction qui annule le dernier coup joué
void popLastMove(short * i, short * j, short * score)
{
    Container * prev = moves->prev;
    Move * move = (Move *)moves->data;

    *i = move->i;
    *j = move->j;
    *score = move->score;

    free(moves->data);
    free(moves);

    moves = prev;
}


// fonction qui lance la boucle du jeu
void play(void)
{
    short i, j;
    Key key;
    short score;
    char * str;

    drawBoard();
    resetBoard();
    resetSavedMoves();

    // on choisit la première cellule
    i = j = 0;
    chooseFirstCell(&i, &j);

    // on traite le choix
    score = 1;
    printInCell(i, j, score);
    hilightPlayableCells(i, j);
    board[i][j] = FALSE;

    do
    {
        clearMessages();
        xorCenteredStr(84, "Maintenant, essayer de remplir le carré !", F_4x6);

        key = ngetchx();

        if( key == KEY_ESC )
        {
            clearMessages();
            xorCenteredStr(84, "Etes-vous sur de vouloir quitter ?", F_4x6);
            xorCenteredStr(91, "Si oui, appuyer sur [Enter].", F_4x6);

            if( ngetchx() == KEY_ENTER )
                exit(0);
        }

        if( key == KEY_BACKSPACE && score != 1 )
        {
            clearCell(i, j);
            hilightPlayableCells(i, j);

            board[i][j] = TRUE;
            popLastMove(&i, &j, &score);

            reverseCell(i, j);
            hilightPlayableCells(i, j);
        }

        if( isLegalMove(i, j, key) )
        {
            reverseCell(i, j);
            hilightPlayableCells(i, j);
            saveMove(i, j, score);

            // on met à jour les coordonnées
            switch(key)
            {
                case '1':
                    i += 2, j -= 2;
                    break;

                case '2':
                    i += 3;
                    break;

                case '3':
                    i += 2, j += 2;
                    break;

                case '6':
                    j += 3;
                    break;

                case '9':
                    i -= 2, j += 2;
                    break;

                case '8':
                    i -= 3;
                    break;

                case '7':
                     i -= 2, j -= 2;
                     break;

                case '4':
                    j -= 3;
                    break;
            }

            // on traite le nouveau coup joué
            score++;
            printInCell(i, j, score);
            hilightPlayableCells(i, j);
            board[i][j] = FALSE;
        }
    }
    while( ! isGameFinished(i, j) );

    clearMessages();
    xorCenteredStr(84, "Le jeu est fini !", F_4x6);
    str = (char *)calloc(32, sizeof(*str));
    sprintf(str, "Votre score est de %d.", score);
    xorCenteredStr(91, str, F_4x6);
    free(str);
}
