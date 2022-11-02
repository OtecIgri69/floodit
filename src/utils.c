#include "utils.h"

extern char tmpch[100];
extern bool done;
extern SDL_Window* window;
extern SDL_Surface * screen, * block[6];
extern SDL_Event event;
extern int xpos, ypos, map[maps][maps], startclr, step;

int InitImages()
{
    for (int i = 0; i < 6; i++) // У нас будет 6 цветов
    {
        char path[20];
        for (int j = 0; j < 20; j++)
            path[j] = 0;
        sprintf(path, "assets/blocks/Block%d.bmp", i);
        block[i] = SDL_LoadBMP(path); // Загружаем BMP по заданному пути в block[i]
        if (!block[i])
            return -1;
    }
     return 1;
}

void DrawImage(SDL_Surface * img, int x, int y, int w, int h, int sx, int sy)
{
    SDL_Rect desc; // координаты, куда нужно наложить часть.
    desc.x = x;
    desc.y = y;
    SDL_Rect src; // накладываемый прямоугольник.
    src.x = sx;
    src.y = sy;
    src.w = w;
    src.h = h;
    SDL_BlitSurface(img, &src, screen, &desc);
}

void CleanImage(int x, int y, int w, int h)
{
    SDL_Rect desc;
    desc.x = x;
    desc.y = y;
    desc.w = w;
    desc.h = h;
    SDL_FillRect(screen, &desc, 0);
}

void GenMap()
{
    for (int i = 0; i < maps; i++)
        for (int j = 0; j < maps; j++)
            map[i][j] = rand() % 6;
}

void DrawBlock(int x, int y)
{
    DrawImage(block[map[x][y]], 30 * x, 30 * y, 30, 30, 0, 0); // блок в координаты 30*x, 30*y размером 30x30
}

void DrawMap()
{
    for (int i = 0; i < maps; i++)
        for (int j = 0; j < maps; j++)
            DrawBlock(i, j);
}

void dfs(int x, int y, int clr)
{
    map[x][y] = clr;
    DrawBlock(x, y);
    if (x - 1 >= 0 && map[x - 1][y] == startclr)
        dfs(x - 1, y, clr);
    if (x + 1 < maps && map[x + 1][y] == startclr)
        dfs(x + 1, y, clr);
    if (y - 1 >= 0 && map[x][y - 1] == startclr)
        dfs(x, y - 1, clr);
    if (y + 1 < maps && map[x][y + 1] == startclr)
        dfs(x, y + 1, clr);
}

void AddColor(int clr)
{
    if (clr == map[0][0])
        return;
    step++;
    startclr = map[0][0];
    dfs(0, 0, clr);
}

void WriteText(int x, int y, char text[100], int sz, int r, int g, int b)
{
    SDL_Color clr;
    clr.r = r;
    clr.g = g;
    clr.b = b;
    TTF_Font * fnt = TTF_OpenFont("assets/fonts/courier.ttf", sz);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_Surface * sText = TTF_RenderText_Blended(fnt, text, clr);
    SDL_BlitSurface(sText, NULL, screen, &dest);
    SDL_FreeSurface(sText);
    TTF_CloseFont(fnt);
}

bool FinishGame()
{
    int clr = map[0][0];
    for (int i = 0; i < maps; i++)
        for (int j = 0; j < maps; j++)
            if (map[i][j] != clr)
                return false;
    return true;
}

void DrawStep()
{
    CleanImage(430, 50, 150, 100);
    for (int i = 0; i < 100; i++)
        tmpch[i] = 0;
    if (FinishGame())
    {
        CleanImage(430, 50, 150, 20);
        for (int i = 0; i < 100; i++)
            tmpch[i] = 0;
        if (step <= 25)
            sprintf(tmpch, "You win!"), WriteText(430, 50, tmpch, 20, 0, 255, 0);
        else
            sprintf(tmpch, "Not bad!"), WriteText(430, 50, tmpch, 20, 255, 255, 0);
        for (int i = 0; i < 100; i++)
            tmpch[i] = 0;
        sprintf(tmpch, "Result:%d", step);
        WriteText(430, 80, tmpch, 20, 255, 255, 0);
        step = 0;
        GenMap();
        DrawMap();
    }
    else
    {
        sprintf(tmpch, "%d%s", step, "/25");
        if (step <= 25)
            WriteText(430, 50, tmpch, 20, 0, 255, 0);
        else
            WriteText(430, 50, tmpch, 20, 255, 0, 0);
    }
}