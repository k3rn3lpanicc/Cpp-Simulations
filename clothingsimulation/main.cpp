#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <math.h>
using namespace std;
double g = 8;
double _ax=4;
int martabe = 11;
double k = 10; //you don't wanna mess with this little shit
double azad = 40;
double initializeLength = 40;

struct point{
double x;
double y;
};
struct jesm{
point shetab;
point velocity;
point position;
bool is_static;
double mass;
int neighbours[4];
}jesms[121]; /*Make this number : martabe*martabe :P */
bool is_neighbour(int p){
if(p==-1){
    return false;
}
return true;
}
jesm get_jesm_by_position(point pos){
for(int i = 0 ; i < martabe*martabe ; i++){
    if(jesms[i].position.x == pos.x && jesms[i].position.y == pos.y)
        return jesms[i];
}
jesm nullpoint;
nullpoint.position.x=-1;
nullpoint.position.y = -1;
return nullpoint;
}
void rasmline(point mabda , point maghsad){
line(mabda.x, mabda.y , maghsad.x,maghsad.y);
}
void rasm(){
for(int i = 0 ; i < martabe ; i++){
    for(int j = 0 ; j<martabe ; j++){
        int ind = martabe*i + j;
        //setcolor(j);
        circle(jesms[ind].position.x,jesms[ind].position.y,3);

        for(int k = 0 ; k<4 ; k++){
            if(jesms[ind].neighbours[k]!=-1){
                //rasmline(jesms[ind].position , jesms[jesms[ind].neighbours[k]].position);
            }
        }
    }
}

}
point shetab(jesm p1 , jesm p2){
double dx = p2.position.x-p1.position.x;
double dy = p2.position.y- p1.position.y;
double dist = sqrt(dx*dx + dy*dy);
double deltx = dist-azad;
point shet;
shet.x = (dx/dist) * (k*(pow(deltx,1)));
shet.y = (dy/dist) * (k*(pow(deltx,1)));
return shet;
}
double dist(point p1 , point p2){
return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p2.y-p1.y)*(p2.y-p1.y));}
void doforces(){
    for(int i = 0 ; i < martabe ; i++){
        for(int j = 0 ; j < martabe ; j++){
            int ind =i*martabe + j;
            if(jesms[ind].is_static==true)
            continue;
            double ax = _ax;
            double ay = g;
            for(int k = 0 ; k<4 ; k++){
                if(jesms[ind].neighbours[k]!=-1){
                    point shetb = shetab(jesms[ind], jesms[jesms[ind].neighbours[k]]);
                        double _dist = dist(jesms[ind].position ,jesms[jesms[ind].neighbours[k]].position);
                        if(_dist>50){
                            if(_dist>=2.5*50){
                             setcolor(COLOR(0,0,255));
                            }
                            else{
                            setcolor(COLOR(0,255,(255*_dist)/(2.5*50)));
                            }
                        }
                        else if(_dist<50){
                            if(_dist<=(50/(2.5))){
                             setcolor(COLOR(255,0,0));
                            }
                            else{
                            setcolor(COLOR((int)((255*2.5*_dist)/(50)),255,0));
                            }
                        }
                        else{
                            setcolor(3);
                        }
                        rasmline(jesms[ind].position ,jesms[jesms[ind].neighbours[k]].position);
                    ax+=shetb.x;
                    ay+=shetb.y;
                }
            }

            jesms[ind].shetab.x = ax/40;
            jesms[ind].shetab.y = ay/40;
        }
    }

}
void doshit(){
for(int i = 0 ; i<martabe ; i++){
    for(int j = 0 ; j < martabe ;j ++){
        int ind = martabe*i +j;
        if(jesms[ind].is_static==true)
            continue;

        jesms[ind].velocity.x += jesms[ind].shetab.x;
        jesms[ind].velocity.y+=jesms[ind].shetab.y;
        jesms[ind].velocity.x*=0.999;
        jesms[ind].velocity.y*=0.999;

        jesms[ind].position.x += jesms[ind].velocity.x;
        jesms[ind].position.y += jesms[ind].velocity.y;
    }
}
}
int main()
{

    int nullpoint;
    nullpoint = -1;
    _ax=4;
    g = 8;
    for(int i = 0; i<martabe ; i++){
        for(int j = 0 ; j<martabe ; j++){
            int ind = martabe*i + j;
            jesms[ind].is_static=false;
            jesms[ind].mass=1;
            jesms[ind].position.x = 150+ i * initializeLength;
            jesms[ind].position.y = 50+ j*initializeLength;
            jesms[ind].shetab.x=0;
            jesms[ind].shetab.y = g;
            jesms[ind].velocity.x = 0;
            jesms[ind].velocity.y = 0;
        }
    }
    for(int i = 0 ; i < martabe ; i++){
        for(int j = 0 ; j < martabe ; j++){
            int ind = martabe*i + j;
            jesms[ind].neighbours[0] = ind%martabe==0 ? nullpoint : ind-1;
            jesms[ind].neighbours[1] = (ind<=martabe-1 && ind>=0) ? nullpoint : ind-martabe;
            jesms[ind].neighbours[2] = ind%martabe == martabe-1 ? nullpoint : ind+1;
            jesms[ind].neighbours[3] = (ind<=(martabe*martabe -1) && ind>=(martabe*(martabe-1))) ? nullpoint : ind+martabe;
        }
    }
     /*
     for(int i = 0 ; i < martabe ; i++){
        for(int j = 0 ; j < martabe ; j++){
            int ind = martabe*i + j;
            if(ind%martabe==0 || ind%martabe == martabe-1 ||(ind<=(martabe*martabe -1) && ind>=(martabe*(martabe-1))) || (ind<=martabe-1 && ind>=0) ){
                jesms[ind].is_static = true;
            }

        }
        }
        */
    for(int i = 0 ; i < martabe*martabe ;i+=(2*martabe)){
    jesms[i].is_static = true;
    }
    //jesms[].is_static =true;
    //jesms[22].is_static = true;
    /*the array :
    0 10 20 30 40 50 60 70 80 90
    1 11 21 31 41 51 61 71 81 91
    2 12 22 32 42 52 62 72 82 92
    3 ...
    .
    .
    .
    */
    initwindow(1800, 1000);
    while(!kbhit()){
    rasm();
    doforces();
    doshit();
    delay(1);
    cleardevice();
    }
    getch();
    closegraph();
    return 0;
}
