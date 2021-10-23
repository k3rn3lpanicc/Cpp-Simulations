#include <iostream>
#include <cmath>
#include <fstream>
#include <graphics.h>
using namespace std;
struct charge{
double q;
double x;
double y;
}barha[100];
struct point{
int x;
int y;
};
double radian(int deg){
deg=-deg;
return deg*0.0175;
}
point rotate_point(float cx,float cy,float angle,point p)
{
  float s = sin(angle);
  float c = cos(angle);

  // translate point back to origin:
  p.x -= cx;
  p.y -= cy;

  // rotate point
  float xnew = p.x * c - p.y * s;
  float ynew = p.x * s + p.y * c;

  // translate point back:
  p.x = xnew + cx;
  p.y = ynew + cy;
  return p;
}
double k=900;
double Ex[700][700];
double Ey[700][700];
double fasele(double x,double y,int i){
return sqrt(((barha[i].x-x)*(barha[i].x-x))+((barha[i].y-y)*(barha[i].y-y)));
}
double meydan(double x,double y,int i){
return ((k*barha[i].q)/((fasele(x,y,i))*(fasele(x,y,i))));
}
double sint(double x,double y,int i){
return (barha[i].y-y)/(fasele(x,y,i));
}
double cost(int x,int y,int i){
return (x-barha[i].x)/(fasele(x,y,i));
}

void calc(int n){
for(int i=0;i<700;i++){
    for(int j=0;j<700;j++){
Ex[i][j]=0;
Ey[i][j]=0;
    }}
for(int i=0;i<700;i++){
    for(int j=0;j<700;j++){
     for(int l=0;l<n;l++){
     Ex[i][j]+=meydan(i,j,l)*cost(i,j,l);
     Ey[i][j]+=meydan(i,j,l)*sint(i,j,l);
     }
    }
}
for(int i=0;i<n;i++){
    for(int m=barha[i].x-10;m<=barha[i].x+10;m++){
        for(int n=barha[i].y-10;n<=barha[i].y+10;n++){
                Ex[m][n]=0;
                Ey[m][n]=0;

        }
    }
}
}
bool dist(double x,double y,int n,double d){
for(int i=0;i<n;i++){
    if(d<=fasele(x,y,i)){
        return false;
    }
}
return true;
}
double min_dist(double x, double y, int n){
double minn=fasele(x,y,0);
for(int i=0;i<n;i++){
    if(fasele(x,y,i)<minn){
        minn=fasele(x,y,i);
    }
}
return minn;
}
int check(int x,int y){
int cn=0;
for(int i=x-1;i<=x+1;i++){
    for(int j=y-1;j<=y+1;j++){
        if(getpixel(i,j)==4){
            cn++;
        }
    }
}
return cn-1;
}

main()
{
    srand(time(0));
    cout<<"1.do bar hamnam hamandaze"<<endl;
    cout<<"2.do bar nahamnam hamandaze"<<endl;
    cout<<"3.do safe bar bar yeknavakht"<<endl;
    cout<<"4.vorood"<<endl;
    cout<<"5.From file"<<endl<<endl;

    cout<<"Enter the number : ";
    int n;
    int f;
    cin>>f;
    if(f==5){
        ifstream file2("file1.txt",ios::in);
        cout<<"1"<<endl;
        int number;
        file2>>number;
        cout<<number<<endl;
        n=number;
        for(int i=0;i<n;i++){
            file2>>barha[i].x>>barha[i].y>>barha[i].q;
        }
        cout<<"hehe"<<endl;
    }
    else if(f==4){
    system("CLS");
    cout<<"Number of Charges : ";
    cin>>n;
    int minb;
    int maxb;
    for(int i=0;i<n;i++){
        cout<<"x of charge "<<(i+1)<<" : ";
        cin>>barha[i].x;
        cout<<"y of charge "<<(i+1)<<" : ";
        cin>>barha[i].y;
        cout<<"q of charge "<<(i+1)<<" : ";
        cin>>barha[i].q;
    }
    minb=barha[0].q;
    maxb=barha[0].q;
    for(int i=0;i<n;i++){
        if(barha[i].q<minb){
            minb=barha[i].q;
        }
        if(barha[i].q>maxb){
            maxb=barha[i].q;
        }
    }
    if(minb!=maxb){
        double sh;
        double ar;
        ar=(minb+maxb)/(minb-maxb);
        sh=(1-ar)/maxb;
        for(int i=0;i<n;i++){
            barha[i].q=barha[i].q;
        }
    }
    else{
        for(int i=0;i<n;i++){
            barha[i].q=barha[i].q/abs(barha[i].q);
        }
    }
    }
    else if(f==3){
    for(int i=0;i<20;i+=1){
    barha[i].q=0.1;
    barha[i].x=200;
    barha[i].y=200+i*10;
    }
    for(int i=20;i<40;i+=1){
    barha[i].q=-0.1;
    barha[i].x=400;
    barha[i].y=200+(i-20)*10;
    }
    n=40;
    }
    else if (f==2){
        barha[0].x=200;
        barha[0].y=300;
        barha[1].x=400;
        barha[1].y=300;
        barha[0].q=1;
        barha[1].q=-1;
        n=2;
    }

    else if (f==1){
        barha[0].x=200;
        barha[0].y=300;
        barha[1].x=400;
        barha[1].y=300;
        barha[0].q=1;
        barha[1].q=1;
        n=2;
    }



    initwindow(700,700);
    calc(n);
    for(int i=0;i<n;i++){
        if(barha[i].q>0){
        setcolor(3);
        setfillstyle(1,3);
        }
        else{
        setcolor(4);
        setfillstyle(1,4);
        }
        fillellipse(barha[i].x,barha[i].y,5,5);
    }
    double l,o;
    l=201;
    o=202;
    double ll,oo;
    ll=201;
    oo=202;
    bool A,B,C,D;
    while(!kbhit()){
    l=rand()%500+100;
    o=rand()%600;
    ll=l;
    oo=o;
    A=true;
    B=true;
    C=true;
    point p;
    point pp;
    p.x=l+Ex[(int)(l)][(int)(o)]*k;
    p.y=o-Ey[(int)(l)][(int)(o)]*k;
    if(p.x-l!=0){
    setcolor(3);
    double shib;
    double arz;
    shib=(p.y-o)/(p.x-l);
    arz=o-(shib*l);
    double fas=sqrt(((p.x-l)*(p.x-l))+((p.y-o)*(p.y-o)));
    pp.y=o+((11*(p.y-o))/fas);
    pp.x=l+((11*(p.x-l))/fas);

    point k=rotate_point(l,o,radian(140),pp);
    line(l,o,k.x,k.y);
    k=rotate_point(l,o,radian(-140),pp);
    line(l,o,k.x,k.y);
    setcolor(15);
    }
    int ss=1;
    while((A||C)&&B){
    line(l+Ex[(int)(l)][(int)(o)]*ss,o-Ey[(int)(l)][(int)(o)]*ss,l,o);
    line(ll-Ex[(int)(ll)][(int)(oo)]*ss,oo+Ey[(int)(ll)][(int)(oo)]*ss,ll,oo);
    //putpixel(l,o,4);
    //putpixel(ll,oo,4);
    l=l+Ex[(int)(l)][(int)(o)]*ss;
    o=o-Ey[(int)(l)][(int)(o)]*ss;
    ll=ll-Ex[(int)(ll)][(int)(oo)]*ss;
    oo=oo+Ey[(int)(ll)][(int)(oo)]*ss;
    A=(((Ex[(int)(l)][(int)(o)]*100!=0)&&(Ey[(int)(l)][(int)(o)])*100!=0));
    C=(((Ex[(int)(ll)][(int)(oo)]*100!=0)&&(Ey[(int)(ll)][(int)(oo)])*100!=0));
    B=(l<=700 && o<=700 && l>=0 &&o>=0&& ll<=700 && oo<=700 && ll>=0 &&oo>=0);
    }

    }


    getch();
}
