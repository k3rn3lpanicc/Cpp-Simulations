#include <iostream>
#include <graphics.h>
#include <cmath>
#include <algorithm>
using namespace std;
struct dooz{
string k[9];
}main_dooz;
void rasm(dooz d){
/*setcolor(8);
line(100,100,100,400);
line(400,100,400,400);
line(100,100,400,100);
line(100,400,400,400);
*/
setcolor(15);
line(300,100,300,400);
line(200,100,200,400);
line(100,200,400,200);
line(100,300,400,300);
setcolor(15);
for(int i=0;i<3;i++){
    if(d.k[i]=="o"){
        circle(100+50*((i+1)*2-1),150,20);
    }
    else if(d.k[i]=="x"){
        settextstyle(8,0,6);
        outtextxy(100+100*(i)+35,125,"x");
    }
}
for(int i=0;i<3;i++){
    if(d.k[i+3]=="o"){
        circle(100+50*((i+1)*2-1),250,20);
    }
    else if(d.k[i+3]=="x"){
        settextstyle(8,0,5);
        outtextxy(100+100*(i)+35,225,"x");
    }
}
for(int i=0;i<3;i++){
    if(d.k[i+6]=="o"){
        circle(100+50*((i+1)*2-1),350,20);
    }
    else if(d.k[i+6]=="x"){
        settextstyle(8,0,5);
        outtextxy(100+100*(i)+35,325,"x");
    }
}
}
bool is_win(dooz d){
string k[9]=d.k;
if(k[0]==k[1]&&k[1]==k[2]&& k[0]=="o"){
    return true;}
else if(k[3]==k[4]&&k[4]==k[5]&& k[3]=="o"){
    return true;}
else if(k[6]==k[7]&&k[7]==k[8]&& k[6]=="o"){
    return true;}
else if(k[0]==k[3]&&k[3]==k[6]&& k[0]=="o"){
    return true;}
else if(k[1]==k[4]&&k[4]==k[7]&& k[1]=="o"){
    return true;}
else if(k[2]==k[5]&&k[5]==k[8]&& k[2]=="o"){
    return true;}
else if(k[0]==k[4]&&k[4]==k[8]&& k[0]=="o"){
    return true;}
else if(k[2]==k[4]&&k[4]==k[6]&& k[2]=="o"){
    return true;}
return false;
}
int bord_o_cnt(dooz d){
int cnt=0;
for(int i=0;i<9;i++){
    if(d.k[i]=="-"){
        d.k[i]="o";
        if(is_win(d)){
            cnt++;
        }
        d.k[i]="-";
    }
}
return cnt;
}
bool is_lose(dooz d){
string k[9]=d.k;
if(k[0]==k[1]&&k[1]==k[2]&& k[0]=="x"){
    return true;}
else if(k[3]==k[4]&&k[4]==k[5]&& k[3]=="x"){
    return true;}
else if(k[6]==k[7]&&k[7]==k[8]&& k[6]=="x"){
    return true;}
else if(k[0]==k[3]&&k[3]==k[6]&& k[0]=="x"){
    return true;}
else if(k[1]==k[4]&&k[4]==k[7]&& k[1]=="x"){
    return true;}
else if(k[2]==k[5]&&k[5]==k[8]&& k[2]=="x"){
    return true;}
else if(k[0]==k[4]&&k[4]==k[8]&& k[0]=="x"){
    return true;}
else if(k[2]==k[4]&&k[4]==k[6]&& k[2]=="x"){
    return true;}
return false;
}
int is_o_twostate(dooz d){
int bord_cnt=0;
for(int i=0;i<9;i++){
    if(d.k[i]=="-"){
        main_dooz.k[i]="o";
        if(is_win(main_dooz)){
            bord_cnt++;
        }
        main_dooz.k[i]="-";
    }
}
return bord_cnt;
}
int is_x_twostate(dooz d){
int bord_cnt=0;
for(int i=0;i<9;i++){
    if(d.k[i]=="-"){
        main_dooz.k[i]="x";
        if(is_lose(main_dooz)){
            bord_cnt++;
        }
        main_dooz.k[i]="-";
    }
}
return bord_cnt;
}
bool is_finished(dooz d){
if(is_win(d)){
    settextstyle(8,0,8);
    outtextxy(100,450,"Computer wins!");
}
if(is_lose(d)){
    settextstyle(8,0,8);
    outtextxy(100,450,"Player wins!");
}
if(is_win(d)||is_lose(d)){
    return true;
}
for(int i=0;i<9;i++){
    if(d.k[i]=="-"){
        return false;
    }
}
settextstyle(8,0,8);
outtextxy(100,450,"Draw!");
return true;
}
int choose(dooz d){
int score[9];
for(int i=0;i<9;i++){
    score[i]=0;
}
for(int i=0;i<9;i++){
    if(d.k[i]=="-"){
        d.k[i]="o";
        if(is_win(d)){
            score[i]+=1000;
        }
        score[i]+=10*(is_o_twostate(d));
        for(int j=0;j<9;j++){
            if(d.k[j]=="-"){
                d.k[j]="x";
                if(is_lose(d)){
                    score[i]-=500;
                }
                d.k[j]="-";
            }
        }
        for(int j=0;j<9;j++){
            if(d.k[j]=="-"){
                d.k[j]="x";
                score[i]-=14*abs(is_x_twostate(d));//-bord_o_cnt(d));
                d.k[j]="-";
            }
        }
        d.k[i]="-";
    }
}
int maxx=-1000;
int jj=0;
for(int i=0;i<9;i++){
cout<<score[i]<<"\t";
if(maxx<=score[i]&&d.k[i]=="-"){
    maxx=score[i];
    jj=i;
}
}
cout<<endl;
return jj;
}
int get_point(int x,int y){
double row2=x/100;
double col2=y/100;
int row=round(row2);
int col=round(col2);
return ((col-1)*3+row)-1;
}
main()
{
    initwindow(800,600);
    for(int i=0;i<9;i++)
        main_dooz.k[i]="-";
    int cnt=0;
    while(!is_finished(main_dooz)){
        rasm(main_dooz);
        if(cnt%2==0){
            int n=0;
            getch();
            if(ismouseclick(WM_LBUTTONDOWN)){
                int xx,yy;
                getmouseclick(WM_LBUTTONDOWN, xx, yy);
                clearmouseclick(WM_LBUTTONDOWN);
                n=get_point(xx,yy)+1;
            }
            if(main_dooz.k[n-1]=="-")
                main_dooz.k[n-1]="x";
            rasm(main_dooz);
        }
        else{
            if(cnt==1){
                int chh[9]={4,4,4,4,2,4,4,4,4};
                int x=0;
                for(int i=0;i<9;i++){
                    if(main_dooz.k[i]=="x"){
                        x=i;
                    }
                }
                int ch=chh[x];
                if(main_dooz.k[ch]=="-")
                    main_dooz.k[ch]="o";
                rasm(main_dooz);
            }
            else if(cnt==3 && (((main_dooz.k[0]=="x"&&main_dooz.k[4]=="o"&&main_dooz.k[8]=="x"))||(main_dooz.k[2]=="x"&&main_dooz.k[4]=="o"&&main_dooz.k[6]=="x"))){
                main_dooz.k[7]="o";
                rasm(main_dooz);
            }
            else{
                int ch=choose(main_dooz);
                if(main_dooz.k[ch]=="-")
                    main_dooz.k[ch]="o";
                rasm(main_dooz);
            }
            }
    cnt++;
    }
	getch();
}
