#ifndef UTILS_H_
#define UTILS_H_
#include "game.h"

int InitImages();
void DrawImage(SDL_Surface * img, int x, int y, int w, int h, int sx, int sy);
void GenMap();
void DrawBlock(int x, int y);
void CleanImage(int x, int y, int w, int h);
void DrawMap();
void dfs(int x, int y, int clr);
void AddColor(int clr);
void WriteText(int x, int y, char text[100], int sz, int r, int g, int b);
bool FinishGame();
void DrawStep();

#endif