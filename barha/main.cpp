#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;
double k=90000;
struct bar{
double q;
double x,y;
}b[700];
double nirohax[800][800];
double nirohay[800][800];
double niroha[800][800];

double fasele(int i,double xx,double yy){
return ((b[i].x-xx)*(b[i].x-xx))+((b[i].y-yy)*(b[i].y-yy));
}
double niro(int i,double xx,double yy){
return (k*b[i].q)/(fasele(i,xx,yy));
}
double sinb(int i,double x,double y){
return (x-b[i].x)/sqrt(fasele(i,x,y));
}
double cosb(int i,double x,double y){
return (y-b[i].y)/sqrt(fasele(i,x,y));
}
void rasm(int n,int l,int h,int zoom){
   for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
            nirohax[i][j]=0;
            nirohay[i][j]=0;
        }
    }
    for(int kk=0;kk<n;kk++){
    for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
            nirohax[i][j]+=cosb(kk,i,j)*niro(kk,i,j);
            nirohay[i][j]+=sinb(kk,i,j)*niro(kk,i,j);
        }
    }
    }
    for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
        niroha[i][j]=sqrt((nirohax[i][j])*(nirohax[i][j])+(nirohay[i][j])*(nirohay[i][j]));
        }
    }
    double maxx=niroha[0][0];
    int im=0;
    int jm=0;
    double minn=niroha[0][0];
    for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
            if(maxx<=niroha[i][j]){
                maxx=niroha[i][j];
                im=i;
                jm=j;
            }
            if(minn>=niroha[i][j]){
                minn=niroha[i][j];
            }
        }
    }
    for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
            niroha[i][j]=(niroha[i][j]*765*765*zoom)/maxx;
        }
    }
    for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
        int meghdar=int(niroha[i][j]);
        int r,g,b;
        r=0;
        g=0;
        b=0;
        if(meghdar<=255){
            r=255-meghdar;
            g=255;
            b=255;
        }
        else if(meghdar>255 && meghdar<=255*2){
            r=0;
            g=255-(meghdar-255);
            b=255;
        }
        else if(meghdar>255*2 && meghdar<=255*3){
            r=0;
            g=0;
            b=255-(meghdar-255*2);
        }
        else{
        r=0;
        g=0;
        b=0;
        }
        putpixel(i,j,COLOR(255-b,255-g,255-r));
        }
    }
    for(int i=0;i<l;i++){
        for(int j=0;j<h;j++){
            if(niroha[i][j]<0.0001){
             setcolor(3);
                circle(i,j,4);
            }
        }
    }
}
main()
{
int l=700;
int h=700;
int zoom=6;
    cout<<"1.do bar hamnam hamandaze"<<endl;
    cout<<"2.do bar nahamnam nahamandaze"<<endl;
    cout<<"3.vorood"<<endl<<endl;
    cout<<"Enter the number : ";
    int n;
    int f;
    cin>>f;
    if(f==3){
    system("CLS");
    cout<<"Number of Charges : ";
    cin>>n;
    int minb;
    int maxb;
    for(int i=0;i<n;i++){
        cout<<"x of charge "<<(i+1)<<" : ";
        cin>>b[i].x;
        cout<<"y of charge "<<(i+1)<<" : ";
        cin>>b[i].y;
        cout<<"q of charge "<<(i+1)<<" : ";
        cin>>b[i].q;
    }
    minb=b[0].q;
    maxb=b[0].q;
    for(int i=0;i<n;i++){
        if(b[i].q<minb){
            minb=b[i].q;
        }
        if(b[i].q>maxb){
            maxb=b[i].q;
        }
    }
    if(minb!=maxb){
        double sh;
        double ar;
        ar=(minb+maxb)/(minb-maxb);
        sh=(1-ar)/maxb;
        for(int i=0;i<n;i++){
            b[i].q=b[i].q;
        }
    }
    else{
        for(int i=0;i<n;i++){
            b[i].q=b[i].q/abs(b[i].q);
        }
    }
    }
    else if (f==2){
        b[0].x=100;
        b[0].y=300;
        b[1].x=200;
        b[1].y=300;
        b[0].q=4;
        b[1].q=-1;
        n=2;
        zoom=15;
    }

    else if (f==1){
        b[0].x=200;
        b[0].y=300;
        b[1].x=400;
        b[1].y=300;
        b[0].q=1;
        b[1].q=1;
        n=2;
    }
    //tedad barha ro ba n neshon midim
    initwindow(l,h);

    rasm(n,l,h,zoom);
	getch();
}
