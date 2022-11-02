#include "game.h"
#include "utils.h"

char tmpch[100];
bool done = false;
SDL_Window* window = NULL;
SDL_Surface * screen, * block[6];
SDL_Event event;
int xpos, ypos, map[maps][maps], startclr, step;

void StartGame()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s", SDL_GetError());
        return 1;
    }
    TTF_Init();
    srand(time(NULL));
    
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    SDL_Window* window = SDL_CreateWindow("Flood it", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    screen = SDL_GetWindowSurface(window);

    InitImages();

    for (int i = 0; i < 6; i++)
        DrawImage(block[i], 440, 200 + 30 * i, 30, 30, 0, 0);
    WriteText(470, 197, ":B", 35, 77, 109, 242);
    WriteText(470, 227, ":G", 35, 34, 176, 76);
    WriteText(470, 257, ":O", 35, 255, 193, 14);
    WriteText(470, 287, ":R", 35, 236, 28, 36);
    WriteText(470, 317, ":V", 35, 111, 49, 151);
    WriteText(470, 347, ":Y", 35, 255, 241, 0);
    GenMap();
    DrawMap();
    DrawStep();
    
    SDL_UpdateWindowSurface(window);

    while (!done)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            {
                done = true;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        done = true;
                        break;
                    }
                    case SDLK_b:
                    {
                        AddColor(COLOR_BLUE), DrawStep(), SDL_UpdateWindowSurface(window);
                        break;
                    }
                    case SDLK_g:
                    {
                        AddColor(COLOR_GREEN), DrawStep(), SDL_UpdateWindowSurface(window);
                        break;
                    }
                    case SDLK_o:
                    {
                        AddColor(COLOR_ORANGE), DrawStep(), SDL_UpdateWindowSurface(window);
                        break;
                    }
                    case SDLK_r:
                    {
                        AddColor(COLOR_RED), DrawStep(), SDL_UpdateWindowSurface(window);
                        break;
                    }
                    case SDLK_v:
                    {
                        AddColor(COLOR_VIOLETT), DrawStep(), SDL_UpdateWindowSurface(window);
                        break;
                    }
                    case SDLK_y:
                    {
                        AddColor(COLOR_YELLOW), DrawStep(), SDL_UpdateWindowSurface(window);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button = SDL_BUTTON_LEFT)
                {
                    int x = event.button.x, y = event.button.y;
                    if (x < 30 * maps && y < 30 * maps)
                        AddColor(map[x / 30][y / 30]);
                    else
                        if (x >= 439 && x <= 470 && y >= 200 && y <= 410)
                            AddColor((y - 200) / 30);
                    DrawStep();
                    SDL_UpdateWindowSurface(window);
                }
                break;
            }
        }
    }
}
