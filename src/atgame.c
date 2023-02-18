#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main()
{

    char mas [10][21];
    int i;
    char key;
    int x = 10, y = 5;
    int ox, oy;
    int ax = 6, ay = 4;
    int apples = 0;
    srand(time(NULL));
    do{

    sprintf(mas[0], "####################");
    for(i = 1; i < 9; i++){
        sprintf(mas[i], "#                  #");
    }
    sprintf(mas[9], "####################");

    mas[y][x] = '@';
    mas[ay] [ax] = '*';
    system("cls");

    for(i = 0; i <10; i++){
        printf("%s\n", mas[i]);
    }
    printf("\n collected apples: %d \n", apples);
    key = getch();
    ox = x;
    oy = y;
    if(key == 'w') y--;
    if(key == 's') y++;
    if(key == 'a') x--;
    if(key == 'd') x++;
     if(mas[y][x] == '#'){
         y = oy;
         x = ox;
     }
     if((ax == x) && (ay == y)){
        ax = rand() * 1.0 / RAND_MAX * 18 + 1;
        ay = rand() * 1.0 / RAND_MAX * 8 + 1;
        apples++;
    }
    }while(key != 'e');
    return 0;
}
