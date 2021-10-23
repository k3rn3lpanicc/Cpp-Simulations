#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;
struct fanar{
double nx;
double ny;
double azad;
double kf;
}fanarha[100];
int n=10;
double jx,jy;
double bazde=0.997;
double mass=1;
double g=9.8;
double dx,dy;
double ax,ay;

void linetojesm(int x, int y){
line(jx,jy,x,y);
}
double fasele(int i){
return sqrt((jx-fanarha[i].nx)*(jx-fanarha[i].nx)+(jy-fanarha[i].ny)*(jy-fanarha[i].ny));
}

void rasmaval(){
    for(int i=0;i<n;i++){
    if(fasele(i)>fanarha[i].azad){
        if(fasele(i)>=2.5*fanarha[i].azad){
         setcolor(COLOR(0,0,255));
        }
        else{
        setcolor(COLOR(0,255,(255*fasele(i))/(2.5*fanarha[i].azad)));
        }
    }
    else if(fasele(i)<fanarha[i].azad){
        if(fasele(i)<=((fanarha[i].azad)/(2.5))){
         setcolor(COLOR(255,0,0));
        }
        else{
        setcolor(COLOR((int)((255*2.5*fasele(i))/(fanarha[i].azad)),255,0));
        }
    }
    else{
        setcolor(3);
    }
    linetojesm(fanarha[i].nx,fanarha[i].ny);
    setcolor(3);
    fillellipse(fanarha[i].nx,fanarha[i].ny,5,5);
    putpixel(fanarha[i].nx,fanarha[i].ny,4);

    }
    fillellipse(jx,jy,10,10);
    delay(1);
}
double ffanar(int i){
return fanarha[i].kf*(fasele(i)-fanarha[i].azad);
}
double sinb(int i){
return (jy-fanarha[i].ny)/(fasele(i));
}
double cosb(int i){
return (jx-fanarha[i].nx)/(fasele(i));
}
main()
{

    //-------Settings-------
    n=10;

    bool shownemodar=false;
    jx=400;
    jy=210;
    dx=15;
    dy=-10;

    //-------fanarha--------------
    for(int i=0;i<n/2;i++){
    fanarha[i].azad=300;
    fanarha[i].kf=0.1;
    fanarha[i].nx=200;
    fanarha[i].ny=40+50*i;
    }
    int cnt=0;
    for(int i=n/2;i<n;i++){
    fanarha[i].azad=300;
    fanarha[i].kf=0.1;
    fanarha[i].nx=600;
    fanarha[i].ny=40+50*cnt;
    cnt++;
    }
    //----------------------
    initwindow(1100,800);
    int cnnt=0;
    double lastx=0,lasty=700;
    while(!kbhit()){
    /*
    for(int i=0;i<n;i++){
        fanarha[i].azad-=0.5;
    }
    */
    setfillstyle(1,0);
    if(shownemodar && cnnt==1000){
        cnnt=0;
        bar(0,0,1000,800);
    }
    if(shownemodar){
    bar(0,0,1100,550);
    }
    else{
    bar(0,0,1100,800);
    }
    cnnt++;
    setfillstyle(1,4);
    rasmaval();
    delay(2);
    ay=0; //nemidoonam chera vali bashe nabashe ziad farghi nemikone vali manteghan bayad bashe hala khodet test kon :P
    ax=0; //hamchenin P:
    for(int i=0;i<n;i++){
    ay+=(mass*g-sinb(i)*ffanar(i))/(mass);
    ax+=(ffanar(i)*cosb(i))/(mass);
    }
    ay=(ay*45)/(800*n);
    ax=(ax*45)/(800*n);
    dy+=ay; dx-=ax;
    jy+=dy; jx+=dx;
    dy*=bazde;
    dx*=bazde;
    if(shownemodar){
    setcolor(4);
    line(cnnt,700-(0.5)*mass*((dx)*(dx)+(dy)*(dy)),lastx,lasty);
    lastx=cnnt;
    lasty=700-(0.5)*mass*((dx)*(dx)+(dy)*(dy));
    setcolor(8);
    line(1,700,1000,700);
    line(1,700,1,600);
    }
    line(10,100,sqrt(dx*dx+dy*dy)*2,200);
    delay(8);
    }
	getch();
}
