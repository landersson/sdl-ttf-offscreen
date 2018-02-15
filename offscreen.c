#include "SDL.h"
#include "SDL_FontCache.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    int w = 800;
    int h = 600;
    

    if(SDL_Init(0) < 0)
    {
        SDL_Log("Failed to initialize SDL.\n");
        return 1;
    }
    
    const int W = 512;
    const int H = 512;

    uint8_t *data = (uint8_t*)malloc(W*H*4);
    uint32_t rmask = 0x000000ff;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x00ff0000;
    uint32_t amask = 0xff000000;
  
    memset(data, 255, W*H*4);
    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)data, W, H, 32, W*4,
                                                 rmask, gmask, bmask, amask);

    if (surf == NULL) {
      SDL_Log("Creating surface failed: %s", SDL_GetError());
      exit(1);
    }

    SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surf);
    if(renderer == NULL)
    {
        SDL_Log("Creating renderer failed: %s", SDL_GetError());
        return 3;
    }
    FC_Font* font = FC_CreateFont();
    FC_LoadFont(font, renderer, "Prototype.ttf", 24, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
    const char* str = "KEYBOARD";
    FC_DrawColor(font, renderer, 12, 12, FC_MakeColor(0, 0, 0, 128), "%s", str);
    FC_DrawColor(font, renderer, 10, 10, FC_MakeColor(255, 0, 0, 255), "%s", str);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect r;
    r.x = 100;
    r.y = 100;
    r.w = 100;
    r.h = 100;
    SDL_RenderDrawRect(renderer, &r);
    r.x -= 1;
    r.y -= 1;
    r.w += 2;
    r.h += 2;
    SDL_RenderDrawRect(renderer, &r);

    SDL_RenderPresent(renderer);
    SDL_SaveBMP(surf, "text.bmp");

	FC_FreeFont(font);

	SDL_Quit();
	
	return 0;
}
