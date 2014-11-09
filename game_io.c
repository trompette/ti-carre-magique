#include <tigcclib.h>
#include "game_io.h"


// curseur pour choisir la première case
static unsigned short cursor[] =
    {0x7F00, 0xC180, 0x8080, 0x8080, 0x8080, 0xC180, 0x7F00};

// drapeau pour la dernière case
static unsigned short goal[] =
    {0xAA80, 0x5500, 0xAA80, 0x5500, 0xAA80, 0x5500, 0xAA80};


// fonction qui affiche une string centrée horizontalement
void xorCenteredStr(short row, const char * str, short font)
{
    FontSetSys(font);
    DrawStr((SCREEN_WIDTH - DrawStrWidth(str, font)) / 2, row, str, A_XOR);
}


// fonction qui dessine le tableau de jeu
void drawBoard(void)
{
    int i;

    for(i = 0; i < NB_CELLS_HORIZ + 1; i++)
    {
        DrawLine(
            OFFSET_HORIZ,
            OFFSET_VERT + CELL_HEIGHT * i,
            OFFSET_HORIZ + CELL_WIDTH * NB_CELLS_HORIZ,
            OFFSET_VERT + CELL_HEIGHT * i,
            A_NORMAL
        );
    }
    for(i = 0; i < NB_CELLS_VERT + 1; i++)
    {
        DrawLine(
            OFFSET_HORIZ + CELL_WIDTH * i,
            OFFSET_VERT,
            OFFSET_HORIZ + CELL_WIDTH * i,
            OFFSET_VERT + CELL_HEIGHT * NB_CELLS_VERT,
            A_NORMAL
        );
    }
}


// fonction qui XOR le curseur
void xorCursor(short i, short j)
{
    Sprite16(
        OFFSET_HORIZ + 1 + CELL_WIDTH * j,
        OFFSET_VERT + 1 + CELL_HEIGHT * i,
        CELL_HEIGHT - 1,
        cursor, LCD_MEM, SPRT_XOR
    );
}


// fonction qui efface le contenu d'une cellule
void clearCell(short i, short j)
{
    SCR_RECT * scr_rect = &(SCR_RECT){{
        OFFSET_HORIZ + CELL_WIDTH * j + 1,
        OFFSET_VERT + CELL_HEIGHT * i + 1,
        OFFSET_HORIZ + CELL_WIDTH * j + CELL_WIDTH - 1,
        OFFSET_VERT + CELL_HEIGHT * i + CELL_HEIGHT - 1,
    }};
    ScrRectFill(scr_rect, scr_rect, A_REVERSE);
}


// fonction qui affiche une cellule en vidéo inverse
void reverseCell(short i, short j)
{
    SCR_RECT * scr_rect = &(SCR_RECT){{
        OFFSET_HORIZ + CELL_WIDTH * j + 1,
        OFFSET_VERT + CELL_HEIGHT * i + 1,
        OFFSET_HORIZ + CELL_WIDTH * j + CELL_WIDTH - 1,
        OFFSET_VERT + CELL_HEIGHT * i + CELL_HEIGHT - 1,
    }};
    ScrRectFill(scr_rect, scr_rect, A_XOR);
}


// fonction qui met en valeur une cellule
void hilightCell(short i, short j)
{
    // 127 est le code ascii du caractère diamant
    char str[] = {127, 0};

    DrawStr(
        OFFSET_HORIZ + CELL_WIDTH * j + (CELL_WIDTH - DrawStrWidth(str, 0)) / 2,
        OFFSET_VERT + CELL_HEIGHT * i + 2,
        str, A_XOR
    );
}


// fonction qui affiche un chiffre (ou le drapeau) dans une cellule
void printInCell(short i, short j, short number)
{
    char * str;

    if( number != NB_CELLS_HORIZ * NB_CELLS_VERT )
    {
        // on affiche le nombre
        str = (char *)calloc(4, sizeof(*str));
        sprintf(str, "%d", number);
        DrawStr(
            OFFSET_HORIZ + CELL_WIDTH * j + (CELL_WIDTH - DrawStrWidth(str, 0)) / 2,
            OFFSET_VERT + CELL_HEIGHT * i + 2,
            str, A_NORMAL
        );
        free(str);

        // on passe la cellule en vidéo inverse
        reverseCell(i, j);
    }
    else
    {
        Sprite16(
            OFFSET_HORIZ + CELL_WIDTH * j + 1,
            OFFSET_VERT + CELL_HEIGHT * i + 1,
            CELL_HEIGHT - 1, goal, LCD_MEM, SPRT_XOR
        );
    }
}


// fonction qui permet d'effacer la zone de texte située sous le tableau
void clearMessages(void)
{
    SCR_RECT * scr_rect = &(SCR_RECT){{
        0, OFFSET_VERT + CELL_HEIGHT * NB_CELLS_VERT + 1,
        SCREEN_WIDTH, SCREEN_HEIGHT
    }};
    ScrRectFill(scr_rect, scr_rect, A_REVERSE);
}

