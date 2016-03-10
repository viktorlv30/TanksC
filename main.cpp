#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "map.h"
#include "constants.h"

enum eDirection
{
    SOUTH = 0,
    NORTH,
    EAST,
    WEST
};

struct sBullet
{
    COORD cord;
    eDirection curs;
    short strong;
    int speed;
};

struct sTank
{
    short x;
    short y;
    int health;
    int speed;
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
        pos.X += 2;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c", WEAPON_U);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c", CENTR_1);
        pos.Y++; pos.X -= 2;
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
        printf("%c%c%c%c%c%c  ", a, b, a, b, a, b);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c    %c%c%c", CENTR_1, CENTR_5, CENTR_3, WEAPON_R);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c%c%c%c  ", a, b, a, b, a, b);
        break;
    case WEST:
        a = tank->x & 0x001 ? GUS_1 : GUS_2;
        b = tank->x & 0x001 ? GUS_2 : GUS_1;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c%c%c%c%c%c", a, b, a, b, a, b);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("%c%c%c    %c", WEAPON_L, CENTR_3, CENTR_6, CENTR_1);
        pos.Y++;
        SetConsoleCursorPosition(hCon, pos);
        printf("  %c%c%c%c%c%c", a, b, a, b, a, b);
        break;
    }
}

sBullet getBarrelPosition( eDirection direct, sTank tank )
{
    sBullet barrel;
    barrel.cord = { tank.x, tank.y };
    barrel.curs = direct;
    switch (direct)
    {
    case NORTH:
        barrel.cord.X += 2;
        barrel.cord.Y -= 1;
        break;
    case SOUTH:
        barrel.cord.X += 2;
        barrel.cord.Y += 6;
        break;
    case EAST:
        barrel.cord.X += 8;
        barrel.cord.Y += 1;
        break;
    case WEST:
        barrel.cord.X -= 1;
        barrel.cord.Y += 1;
        break;
    }
    return barrel;
}

void shootTank( sBullet *bullet, bool *shoot )
{

    switch (bullet->curs)
    {
    case NORTH:
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf(" ");
        bullet->cord.Y -= 1;
        if( bullet->cord.Y < 0 )
        {
            *shoot = false;
            return;
        }
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf("%c", SHOOT_U);
        break;
    case SOUTH:
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf(" ");
        bullet->cord.Y += 1;
        if( bullet->cord.Y >= HIGH )
        {
            *shoot = false;
            return;
        }
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf("%c", SHOOT_D);
        break;
    case EAST:
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf(" ");
        bullet->cord.X += 2;
        if( bullet->cord.X >= WIDE )
        {
            *shoot = false;
            return;
        }
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf("%c", SHOOT_R);
        break;
    case WEST:
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf(" ");
        bullet->cord.X -= 2;
        if( bullet->cord.X <= 0 )
        {
            *shoot = false;
            return;
        }
        SetConsoleCursorPosition( hCon, bullet->cord );
        printf("%c", SHOOT_L);
        break;
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
    sBullet bullet;
    bool isBullet = false;

    tankDrawForDirection( curs, &stanks[0]);
    tankDrawForDirection( NORTH, &stanks[1]);

    for(;;)
    {
        if( kbhit() != 0 )
        {
            comm = getch();
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
                if( ! isBullet )
                {
                    isBullet = true;
                    Beep(1000, 25);
                    bullet = getBarrelPosition( curs, stanks[0] );
                }
                comm = 0;
                break;
            case EXIT_KEY:
                return 0;
            }
        }

        if( isBullet )
        {
            shootTank( &bullet, &isBullet );
        }

        if(isRedDraw)
        {
            tankDrawForDirection( curs, &stanks[0]);
            tankDrawForDirection( NORTH, &stanks[1]);
            isRedDraw = false;
        }
        Sleep(40);
    }


    return 0;
}
