#define USE_TI89
#define OPTIMIZE_ROM_CALLS
#define SAVE_SCREEN

#include <tigcclib.h>

#include "game.h"


void _main(void)
{
    while( TRUE )
    {
        clrscr();
        printWelcomeScreen();

        clrscr();
        play();

        ngetchx();
    }
}
