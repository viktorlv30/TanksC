#include <stdio.h>
#include <windows.h>
//#include <stdlib.h>
#include <conio.h>

#include <map.h>

HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );

const int DOWN_KEY  = 80;
const int UP_KEY    = 72;
const int RIGHT_KEY = 77;
const int LEFT_KEY  = 75;
const int SHOOT_KEY = 32;
const int EXIT_KEY  = 27;

const int GUS_1 = 178;
const int GUS_2 = 176;
const int WEAPON_U = 220;
const int WEAPON_D = 223;
const int WEAPON_R = 221;
const int WEAPON_L = 222;
const int CENTR_1 = 186;
const int CENTR_2 = 202;
const int CENTR_3 = 205;
const int CENTR_4 = 203;
const int CENTR_5 = 204;
const int CENTR_6 = 185;
const int SHOOT_U = 30;
const int SHOOT_D = 31;
const int SHOOT_R = 16;
const int SHOOT_L = 17;

const int WIDE = 160;
const int HIGH = 55;

struct sTank
{
    short x;
    short y;
    int health;
    int speed;
};

enum eDirection
{
    SOUTH = 0,
    NORTH,
    EAST,
    WEST
};

void tankDrawForDirection( eDirection direct, sTank *tank )
{
    COORD pos = {tank->x, tank->y};

    int a = GUS_1;
    int b = GUS_2;

    switch (direct)
    {
    case NORTH:
        a = tank->y & 0x001 ? GUS_1 : GUS_2;
        b = tank->y & 0x001 ? GUS_2 : GUS_1;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c  ", WEAPON_U);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c  ", CENTR_1);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c", a, a, CENTR_2, a, a);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c %c%c", b, b, b, b);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c %c%c", a, a, a, a);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c", b, b, CENTR_3, b, b);
        break;
    case SOUTH:
        a = tank->y & 0x001 ? GUS_1 : GUS_2;
        b = tank->y & 0x001 ? GUS_2 : GUS_1;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c", b, b, CENTR_3, b, b);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c %c%c", a, a, a, a);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c %c%c", b, b, b, b);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c", a, a, CENTR_4, a, a);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c  ", CENTR_1);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c  ", WEAPON_D);
        break;
    case EAST:
        a = tank->x & 0x001 ? GUS_1 : GUS_2;
        b = tank->x & 0x001 ? GUS_2 : GUS_1;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c%c  ", a, a, b, b, a, a);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c    %c%c%c", CENTR_1, CENTR_5, CENTR_3, WEAPON_R);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c%c  ", a, a, b, b, a, a);
        break;
    case WEST:
        a = tank->x & 0x001 ? GUS_1 : GUS_2;
        b = tank->x & 0x001 ? GUS_2 : GUS_1;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c%c%c%c%c%c", a, a, b, b, a, a);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c    %c", WEAPON_L, CENTR_3, CENTR_6, CENTR_1);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c%c%c%c%c%c", a, a, b, b, a, a);
        break;
    }
}

COORD getBarrelPosition( eDirection direct, sTank tank )
{
    COORD barrel = { tank.x, tank.y };
    switch (direct)
    {
    case NORTH:
        barrel.X += 2;
        barrel.Y -= 1;
        break;
    case SOUTH:
        barrel.X += 2;
        barrel.Y += 6;
        break;
    case EAST:
        barrel.X += 8;
        barrel.Y += 1;
        break;
    case WEST:
        barrel.X -= 1;
        barrel.Y += 1;
        break;
    }
    return barrel;
}

void shootTank( COORD barrel, eDirection direct )
{
    switch (direct)
    {
    case NORTH:
        for(  ; barrel.Y >= 0 ; barrel.Y -= 2 )
        {
            SetConsoleCursorPosition( hCon, barrel );
            printf("%c", SHOOT_U);
            Sleep(100);
            SetConsoleCursorPosition( hCon, barrel );
            printf(" ");
        }
        break;
    case SOUTH:
        for(  ; barrel.Y <= HIGH ; barrel.Y += 2 )
        {
            SetConsoleCursorPosition( hCon, barrel );
            printf("%c", SHOOT_D);
            Sleep(100);
            SetConsoleCursorPosition( hCon, barrel );
            printf(" ");
        }
        break;
    case EAST:
        for(  ; barrel.X <= WIDE ; barrel.X += 4 )
        {
            SetConsoleCursorPosition( hCon, barrel );
            printf("%c", SHOOT_R);
            Sleep(100);
            SetConsoleCursorPosition( hCon, barrel );
            printf(" ");
        }
        break;
    case WEST:
        for(  ; barrel.X >= 0 ; barrel.X -= 4 )
        {
            SetConsoleCursorPosition( hCon, barrel );
            printf("%c", SHOOT_L);
            Sleep(100);
            SetConsoleCursorPosition( hCon, barrel );
            printf(" ");
        }
    }
}

void checkChangeMove( bool *control, bool *set )
{
    if( *control )
    {
        system("cls");
        *control = false;
        *set = true;
    }
}

void wipeImprintTank( eDirection direct, const sTank *tank )
{
    COORD pos = { tank->x, tank->y };

    switch (direct)
    {
    case NORTH:
        pos.Y+=5;
        SetConsoleCursorPosition(hCon, pos);
        printf("     ");
        break;
    case SOUTH:
        SetConsoleCursorPosition(hCon, pos);
        printf("     ");
        break;
    case EAST:
        SetConsoleCursorPosition(hCon, pos);
        printf(" ");
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf(" ");
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf(" ");
        break;
    case WEST:
        pos.X+=7;
        SetConsoleCursorPosition(hCon, pos);
        printf(" ");
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf(" ");
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf(" ");
        break;
    }
}



int main()
{
    system("mode con cols=160 lines=55");


    CONSOLE_CURSOR_INFO cci;
//    GetConsoleCursorInfo( hCon, &cci );
    cci.bVisible = false; //visible cursor
    cci.dwSize = 1;       // size of cursor
    SetConsoleCursorInfo( hCon, &cci );

    int num_tank = 2;
    struct sTank stanks[num_tank];
    stanks[0].x = 25;
    stanks[0].y = 45;
    stanks[1].x = 65;
    stanks[1].y = 25;

    char comm = 0;
    bool isRedDraw = false;
    eDirection curs = NORTH;
    bool horisont = ( curs == NORTH || curs == SOUTH ) ? false : true;
    bool vertical = ( curs == NORTH || curs == SOUTH ) ? true : false;
    COORD barrel;

    tankDrawForDirection( curs, &stanks[0]);
    tankDrawForDirection( NORTH, &stanks[1]);

    for(;;)
    {
        if( kbhit() != 0 )
        {
            comm = getch();
//            printf("%d", comm);
            isRedDraw = true;

            switch( comm )
            {
            case UP_KEY:
                curs = NORTH;
                wipeImprintTank( curs, &stanks[0] );
                stanks[0].y = --stanks[0].y <= 0 ? 0 : stanks[0].y;
                checkChangeMove( &horisont, &vertical );
                break;
            case DOWN_KEY:
                curs = SOUTH;
                wipeImprintTank( curs, &stanks[0] );
                stanks[0].y = ++stanks[0].y >= HIGH-6 ? HIGH-6 : stanks[0].y;
                checkChangeMove( &horisont, &vertical );
                break;
            case RIGHT_KEY:
                curs = EAST;
                wipeImprintTank( curs, &stanks[0] );
                stanks[0].x = ++stanks[0].x >= WIDE-8 ? WIDE-8 : stanks[0].x;
                checkChangeMove( &vertical, &horisont );
                break;
            case LEFT_KEY:
                curs = WEST;
                wipeImprintTank( curs, &stanks[0] );
                stanks[0].x = --stanks[0].x <= 0 ? 0 : stanks[0].x;
                checkChangeMove( &vertical, &horisont );
                break;
            case SHOOT_KEY:
                barrel = getBarrelPosition( curs, stanks[0] );
                shootTank( barrel, curs );
                break;
            case EXIT_KEY:

                return 0;
            }
        }
        if(isRedDraw)
        {
            tankDrawForDirection( curs, &stanks[0]);
            tankDrawForDirection( curs, &stanks[1]);
            isRedDraw = false;
        }
    }


    return 0;
}
