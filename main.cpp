#include <SDL/SDL.h>
#include <iostream>

#include "quickcg.h"

using namespace std;
using namespace QuickCG;

const int EDITORX = 10;
const int EDITORY = 10;
char editor[EDITORY][EDITORX];
char keypressed;

typedef struct Cursor
{
    int x;
    int y;
} Cursor;

typedef struct Player
{
    float x;
    float y;
    int radius; 
} Player;


///////////// Tiles + Editor ///////////////

ColorRGB get_color_for_tile(Cursor* Cursor, int x, int y)
{
    if(x == Cursor->x && y == Cursor->y)
        return RGB_Red;
    
    if(editor[y][x] == 'w')
        return RGB_Blue;
    
    return RGB_White;
}

void initialize_editor()
{
    for(int i = 0; i < EDITORY; ++i)
    {
        for(int j = 0; j < EDITORX; ++j)
        {
           editor[i][j] = ' ';
        }
    }
}

void manage_editor(Cursor* Cursor)
{
    if(keyPressed(SDLK_UP))
    {
        --Cursor->y;
    }
    
    if(keyPressed(SDLK_DOWN))
    {
        ++Cursor->y;
    }
    
    if(keyPressed(SDLK_LEFT))
    {
        --Cursor->x;
    }
    
    if(keyPressed(SDLK_RIGHT))
    {
        ++Cursor->x;
    }
    
    if(keyDown(SDLK_w))
    {
        editor[Cursor->y][Cursor->x] = 'w';
    }
}

void print_editor(Cursor* Cursor)
{
    int SIZE = 16;
    int offsetX = 50;
    int offsetY = 50;
    int color;
    
    for(int i = 0; i < EDITORY; ++i)
    {
        for(int j = 0; j < EDITORX; ++j)
        {
            ColorRGB color = get_color_for_tile(Cursor, j, i);
            
            int x = j * SIZE + offsetX;
            int y = i * SIZE + offsetY;
            
            drawRect(x, y, x + SIZE - 1, y + SIZE - 1, color);
        }
    }
}

///////////// Gameloop + Main //////////////

void gameloop(Player* player)
{
    float vY = 0;
    
    while(!done())
    {
        cls(RGB_Black);
        
        if(keyDown(SDLK_RIGHT))
        {
            player->x += 2;
            
            if(player->x > 639 - player->radius)
            {
                player->x = 639 - player->radius;
            }
        }
        
        if(keyDown(SDLK_LEFT))
        {
            player->x -= 2;
            
            if(player->x < 0 + player->radius)
            {
                player->x = 0 + player->radius;
            }
        }
        
        vY += 0.05;
        player->y += vY;
        
        if(player->y + player->radius > 479)
        {
            player->y = 479 - player->radius;
            vY = -vY * 0.5;
            
            if(keyDown(SDLK_UP))
            {
                vY = -3;
            }
        }
        
        drawCircle(player->x, player->y, player->radius, RGB_White);
        
        redraw();
    }
}

int main(int argc, char* argv[])
{
    Player player;
    Cursor cursor;
    
    screen(640, 480);
    player.x = 50;
    player.y = 50;
    player.radius = 4;
    cursor.x = 0;
    cursor.y = 0;
    
    initialize_editor();
    
    //gameloop(&player);
    while(!done())
    {
        manage_editor(&cursor);
        print_editor(&cursor);

        redraw();
    }
    
    return 0;
}

