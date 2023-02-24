#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define width 65
#define height 25
typedef struct{
 int x,y,w;
}iRacket;
typedef struct{
 float x,y;
 int ix,iy;
 float alfa;
 float speed;
}iBall;

char mas[height][width+1];
iRacket racket;
iBall ball;
int hitCnt = 0;
int maxHitCnt = 0;
void moveBall (float x, float y){
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}
void initBall(){
    moveBall(2,2);
    ball.alfa = -1;
    ball.speed = 0.5;
}

void putBall(){
    mas[ball.iy][ball.ix] = '*';

}

void autoMoveBall(){
    if (ball.alfa < 0) ball.alfa += M_PI*2;
    if(ball.alfa > M_PI*2) ball.alfa-= M_PI*2;

    iBall b1 = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed
             ,ball.y + sin(ball.alfa) * ball.speed);
    if((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '@')){
            if(mas[ball.iy][ball.ix] == '@'){
                hitCnt++;
            }
        if((ball.ix != b1.ix) && (ball.iy != b1.iy)){
                if(mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix]){
                    b1.alfa = b1.alfa + M_PI;
                }else{
                    if (mas[b1.iy][ball.ix] == '#')
                        b1.alfa = (2*M_PI - b1.alfa) + M_PI;
                else{
                 b1.alfa = (2*M_PI - b1.alfa);
                 }
                }
        }else if(ball.iy == b1.iy)
            b1.alfa = (2*M_PI - b1.alfa) + M_PI;
         else
            b1.alfa = (2*M_PI - b1.alfa);

         ball = b1;
         autoMoveBall();
    }

}
void initRacket(){
     racket.w = 7;
     racket.x = (width - racket.w) / 2;
     racket.y = height - 1;
}
void putRacket(){
    for(int i = racket.x; i < racket.x + racket.w; i++){
        mas[racket.y][i] = '@';
    }
}
void init()
{
   for(int i =0; i < width; i++)
       mas[0][i] = '#';
   mas[0] [width] = '\0';

   strncpy(mas[1],mas[0], width+1);
   for(int i =1; i <width - 1; i++){
       mas[1][i] = ' ';
   }

    for(int i = 1; i < height; i++)
        strncpy(mas[i], mas[1],width+1);
 }
void show(){
    for(int i = 0; i < height; i++){
        printf("%s",mas[i]);
        if(i == 3)
            printf("\t  your score: %i  ", hitCnt);
        if(i == 4)
            printf("\t  your max score: %i  ", maxHitCnt);
        if(i < height - 1){
            printf("\n");
        }
    }
}
void moveRacket(int x)
{
    racket.x = x;
    if(racket.x < 1)
            racket.x = 1;
    if(racket.x + racket.w >= width)
        racket.x = width - 1 - racket.w;

}
void  setcur(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main(){
    BOOL run = FALSE;
    char c;
    initRacket();
    initBall();
    do{
    setcur(0,0);
    if(run)
        autoMoveBall();
    if (ball.iy > height){
        run = FALSE;
        if(hitCnt > maxHitCnt)
            maxHitCnt = hitCnt;
        hitCnt = 0;
    }
    init();
    putRacket();
    putBall();
    show();
    if(GetKeyState('A')< 0) moveRacket(racket.x - 1);
    if(GetKeyState('D')< 0) moveRacket(racket.x + 1);
    if(GetKeyState('W')< 0) run = TRUE;

    if(!run)
        moveBall(racket.x + racket.w / 2, racket.y - 1);
    Sleep(10);
    }while(GetKeyState(VK_ESCAPE)>=0);
    return 0;
}
