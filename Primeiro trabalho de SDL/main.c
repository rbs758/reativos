#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#define rXStart 300
#define rYStart 250
#define r2XStart 75
#define r2YStart 250

void loop();
void mouseInput();
void move(SDL_Rect* rec,int xMax, int yMax, int xStart, int yStart, int speed);
int isSquareClicked(SDL_MouseButtonEvent* me,SDL_Rect* r);
void render();
void exitApplication(SDL_Window* window);



SDL_Rect r = {rXStart, rYStart, 75, 75};
SDL_Rect r2 = {r2XStart, r2YStart, 50, 50};

int r1Xmax = 100, r1Ymax=150, r1State=1;
int r2Xmax = 150, r2Ymax=200, r2State=1;

SDL_Event e;
SDL_Renderer* renderer;

Uint32 now, last, last2;

int main (int argc, char* args[])
{
    /* INITIALIZATION */
    
    int err = SDL_Init(SDL_INIT_EVERYTHING);
    assert(err == 0);
    
    SDL_Window* window = SDL_CreateWindow("2 Squares",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window,-1,0);
    
    /* EXECUTION */
    loop();
    
    
    /* FINALIZATION */
    exitApplication(window);
    
    
    return 0;
}

void loop(){
    while (1){
        if (e.type == SDL_QUIT) {
            break;
        }
        SDL_WaitEventTimeout(&e, 25);
        mouseInput();
        now = SDL_GetTicks();
        if(now > last + 25){
            last = SDL_GetTicks();
            if(r1State==1){
                move(&r, r1Xmax, r1Ymax, rXStart, rYStart, 15);
            }
            if(r2State==1){
                move(&r2, r2Xmax, r2Ymax, r2XStart, r2YStart, 5);
            }
        }
        render();
    }
}

void mouseInput(){
    switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            now = SDL_GetTicks();
            if(now > last2 + 250){
                last2 = SDL_GetTicks();
                SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;
                if(isSquareClicked(me, &r)==1){
                    r1State*=-1;
                }
                if(isSquareClicked(me, &r2)==1){
                    r2State*=-1;
                }
                
            }
        break;
    }
}

void move(SDL_Rect* rec,int xMax, int yMax, int xStart, int yStart, int speed){
    if(rec->x < xMax+xStart && rec->y>=yStart){
        rec->x+=speed;
    }else if(rec->x > xStart && rec->y<=yStart-yMax){
        rec->x-=speed;
    }else if(rec->y > yStart-yMax && rec->x >= xMax+xStart){
        rec->y-=speed;
    }else if(rec->y < yStart && rec->x <= xStart){
        rec->y+=speed;
    }
}

int isSquareClicked(SDL_MouseButtonEvent* me,SDL_Rect* r){
    if(me->x >= r->x && me->x <= r->x+r->w){
        if(me->y >= r->y && me->y <= r->y+r->h){
            return 1;
        }
    }
    return 0;
}

void render(){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
    
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0x00);
    SDL_RenderFillRect(renderer, &r2);
    
    SDL_RenderPresent(renderer);
}

void exitApplication(SDL_Window* window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}




