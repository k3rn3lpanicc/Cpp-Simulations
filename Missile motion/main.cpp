#include <iostream>
#include <graphics.h>
#include <math.h>
#include <string>
using namespace std;
#define PI 3.14159265
#define g 9.8
float teta0;
struct point{
int x;
int y;
};

float _sin(float zavie){
return sin(((PI*zavie)/180));
}
float _cos(float zavie){
return cos(((PI*zavie)/180));
}
float _tan(float teta){
return _sin(teta)/_cos(teta);
}
float _cot(float teta){
return 1/_tan(teta);
}
struct _2dVector{
float axisx;
float axisy;
};

void Rasm(point a){
setfillstyle(1,3);
circle(a.x,a.y,2);
}

void LineRasm(point a , point b){
line(a.x,a.y,b.x,b.y);
}
void RasmBordar(point a , point b){
setfillstyle(2,6);
setcolor(6);
LineRasm(a,b);
setfillstyle(1,6);
fillellipse(b.x,b.y,4,4);
setcolor(15);
}


int _lx , _ly;
void Simulate(point toop , float ax, float ay,float vx , float vy){
Sleep(10);
//cleardevice();
vx += ax;
vy+= ay;
toop.x+=vx;
toop.y-=vy;
point lastp;
lastp.x = _lx;
lastp.y = _ly;
LineRasm(toop, lastp);
_lx = toop.x;
_ly = toop.y;
Rasm(toop);

point endpoint;
endpoint.x = toop.x + vx;
endpoint.y = toop.y - vy;
//RasmBordar(toop , endpoint);
if(toop.y >= 750){
    cout<<"Teta : "<<teta0<<"\tX:"<<toop.x<<endl;
    return;
}
Simulate(toop,ax,ay,vx,vy);
}
void InitialStateRasm(int x0 , int y0 , float vx0 , float vy0){
setcolor(7);
line(x0,y0 , 1900 ,y0);
line(x0,y0 , x0 , 100);
setcolor(15);
}
int main()
{

    float v0 = 90;
    cout<<"Enter teta0 : ";
    cin>>teta0;
    cout<<"Enter the V0 Value : ";
    cin>>v0;

    point toop;
    toop.x=100;
    toop.y=750;
    initwindow(1900,800);
    //while(teta0>=0){
    Rasm(toop);
    _lx = toop.x;
    _ly = toop.y;
    float vx0 = (v0 * _cos(teta0)) ;
    float vy0 = (v0 * _sin(teta0));
    InitialStateRasm(toop.x,toop.y,vx0 , vy0);
    Simulate(toop , 0 ,-0.5 , vx0,vy0);
    //teta0--;
    //}
    getch();
    closegraph();
    return 0;
}
