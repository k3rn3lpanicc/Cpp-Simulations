#include "SDL.h"
#include<stdbool.h>
#define G 0.001
typedef struct object{
    SDL_Rect position;
    SDL_Texture *texture;
} _object;
_object objects[100000];
int mousex , mousey;
typedef struct point{double x; double y} point;
typedef struct Pos{point loc; double vx;double vy; double ax; double ay;} Pos;
Pos positions[10000];
void set_positions(){
    for(int i = 0; i<10000 ; i++){
        if(positions[i].loc.x>1800||positions[i].loc.x<=0){
            positions[i].vx*=-1;

        }
        if(positions[i].loc.y>900||positions[i].loc.y<=0){
            positions[i].vy*=-1;

        }
        objects[i].position.x = (int)positions[i].loc.x;
        objects[i].position.y = (int)positions[i].loc.y;
    }
}
point rotate_point(float cx,float cy,float angle,point p){
    float s = sin(angle);
    float c = cos(angle);
    p.x -= cx;
    p.y -= cy;
    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;
    p.x = xnew + cx;
    p.y = ynew + cy;
    return p;
}
double get_dist(double x1 , double y1 , double x2 , double y2){
    return (((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}
void calc_forces(){
    for(int i = 0; i < 10000 ; i++){
        double R = sqrt(sqrt(sqrt(get_dist(mousex , mousey , positions[i].loc.x , positions[i].loc.y))));
        double F = (G*10)/(R*R);
        double Fx = F*((positions[i].loc.x-mousex)/R);
        double Fy = F*((mousey-positions[i].loc.y)/R);
        positions[i].ay=Fy;
        positions[i].ax=-Fx;
        positions[i].vx+=positions[i].ax;
        positions[i].vy+=positions[i].ay;
        positions[i].vx *= 0.999;
        positions[i].vy *= 0.999;

        positions[i].loc.x+=positions[i].vx;
        positions[i].loc.y+=positions[i].vy;
    }
}
int main(int argc, char *argv[])
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *image = NULL;
    SDL_Surface *image2 = NULL;
    int posX = 100, posY = 100, width = 1800, height = 900;
    bool loopShouldStop = SDL_FALSE;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init();
    win = SDL_CreateWindow("Gravity Simulation", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_GetMouseState(&mousex , &mousey);
    image = IMG_Load("img.png");
    image2 = IMG_Load("back.png");
    SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer , image2);
    positions[0].loc.x = 900;
    positions[0].loc.y = 450;
    for(int i = 0; i <10000 ; i++){
            point mk;
            mk.x = 900 + 200;
            mk.y = 450;
            positions[i].loc = rotate_point(900 , 450 , 0.08*i , mk);
        positions[i].ax = positions[i].ay = positions[i].vx = positions[i].vy = 0;
        objects[i].position.w = 2;
        objects[i].position.h = 2;
        objects[i].texture = SDL_CreateTextureFromSurface(renderer, image);
    }

    SDL_FreeSurface(image);
    while (!loopShouldStop)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    loopShouldStop = SDL_TRUE;
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mousex , &mousey);
                    break;
            }
        }
        calc_forces();
        set_positions();
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, txt, NULL, NULL);
        for(int i = 0; i <10000 ; i++){
            SDL_RenderCopy(renderer, objects[i].texture, NULL, &(objects[i].position));
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bitmapTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
