#include <stdio.h>
int axis_x = 80;  //  размер поля по оси х //  не изменяется
int axis_y = 24;  //  размер поля по оси у //  не изменяется изначально было 25
int ball_x1 = 1;  //  положение мяча по оси х //  изменяется
int ball_y1 = 3;  //  положение мяча по оси у //  изменяется
int racket1_x = 0;  //  крайнее верхнее  положение ракетки 1 по оси х //  не изменяется
int racket1_y = 3;  //  положение ракетки 1 по оси у //  изменняется
int racket2_x = 79;  //  крайнее верхнее положение ракетки 2 по оси х //  не изменяется
int racket2_y = 21;  //  положение ракетки 2 по оси у //  изменняется
int score11 = 0;  //  количество голов ракетки 1 //  изменяется
int score22 = 0;  //  количество голов ракетки 2 //  изменяется
int tr_x1 = 1;  //  траектория ракетки 1 по оси х //  изменяется
int tr_y1 = -1;  //  траектория ракетки 1 по оси y //  изменяется
char ch1;  //  ввод команд для ракетки 1 //  изменяется
char ch2;  //  ввод команд для ракетки 2 //  изменяется

int tragectory_y(int ball_y, int tr_y)  {  //  функция изменения траектории по оси y (вниз/вверх)
    if (ball_y == axis_y && tr_y == 1)
        tr_y = tr_y * (-1);
    if (ball_y == 0 && tr_y == -1)
        tr_y = tr_y * (-1);
    tr_y1 = tr_y;
    return 0;
}

int tragectory_x(int ball_x, int ball_y, int tr_x,
    int racket_y, int racket_x )  {  //  функция изменения траектории по оси х (вправо/влево)
    if (ball_x == axis_x - 2 && tr_x == 1 && ball_y <= racket_y + 2 &&  ball_y >=racket_y)
        tr_x = tr_x * (-1);  //  для ракетки 2
    else if (ball_x == racket_x + 2 && tr_x == -1 && ball_y <= racket_x + 2 &&  ball_y >=racket_x)
        tr_x = tr_x * (-1);  //  для ракетки 1
    tr_x1 = tr_x;
    return 0;
}

int tragectory(int ball_x, int ball_y, int tr_x, int tr_y)  {  //  функция подсчета координат шарика
    ball_x = ball_x + tr_x;
    ball_y = ball_y + tr_y;
    ball_x1 = ball_x;
    ball_y1 = ball_y;
    return 0;
}

int score(int ball_x, int score1, int score2)  {
    if (ball_x == racket1_x){
        score2++;
        ball_x1 = racket2_x - 1;
        ball_y1 = racket2_y + 1;
    }
    if (ball_x == racket2_x ){
        score1++;
        ball_x1 = racket1_x + 1;
        ball_y1 = racket1_y + 1;
    }
    score11 = score1;
    score22 = score2;
    return 0;
}

int display(int ball_x, int ball_y, int racket1_x, int racket1_y,
    int racket2_x, int racket2_y, int tr_y, int tr_x)  {
    //  функция рисования всего, что есть на экране, в зависимости от координат обьектов
    tragectory_y(ball_y, tr_y);  //  вызов функции изменении траектории мячика по оси у
    tragectory_x(ball_x, ball_y, tr_x, racket1_y, racket1_x);
    //  вызов функции изменении траектории мячика по оси х для ракетки 1
    tragectory_x(ball_x, ball_y, tr_x, racket2_y, racket2_x);
    //  вызов функции изменении траектории мячика по оси х для ракетки 1
    tragectory(ball_x, ball_y, tr_x1, tr_y1);  //  вывоз функции изменения координат
    score(ball_x, score11, score22);
    for (int y = axis_y+1; y >= -1; y--) {
        for (int x = -1; x <= axis_x+1; x++) {  //  вложенный цикл отрисовки поля
            if (x == ball_x && y == ball_y)  //  условие отрисовки мяча
                printf("*");
            else if (((y == 0 || y == axis_y + 1) && x == -1) || x == -1 || x == axis_x)
                    printf("|");  //  условие отрисовки  вертикальных границ
            else if (y == -1 || y == axis_y+1)  //  условие отрисовки горизонтальных границ
                    printf("-");
            else if ((x == racket1_x && y == racket1_y)
                || (x == racket2_x && y == racket2_y))  //  условия рисования первой части ракеток
                printf("|");
            else if ((x == racket1_x && y == racket1_y + 1) || (x == racket2_x && y == racket2_y + 1))
                //  условия рисования второй части части ракеток
                printf("|");
            else if ((x == racket1_x && y == racket1_y + 2) || (x == racket2_x && y == racket2_y + 2))
                //  условия рисования третей части части ракеток
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
    //printf("%d",racket1_x);
    //printf(" %d",racket1_y);
    printf(" %d",racket2_y);
    printf(" %d",ball_x);
    printf(" %d",ball_y);
    return 0;
}

int main()  {
    while (1) {  //  бесконечный цикл, который останавливается когда один из игровок выйграл
        //printf("\e[1;1H\e[2J");
        printf("GAMER1: %d | GAMER2: %d \n", score11,score22);
        display(ball_x1, ball_y1, racket1_x, racket1_y, racket2_x, racket2_y, tr_y1, tr_x1);
        printf("\n");
        //printf("")
        scanf("%c%c", &ch1, &ch2);  //  ввод команд движения ракеток с клавиатуры
        switch (ch1)  {  //  изменение координаты y при движении ракетки 1
            case 'A':
                if (racket1_y + 2 < axis_y){  //  проверка не выйдет ли ракетка 1 за пределы поля наверху
                    racket1_y++;  //  двигаемся вверх
                }
                break;
            case 'Z':
                if (racket1_y > 0){  //  проверка не выйдет ли ракетка 1 за пределы поля внизу
                    racket1_y--;  //  двигаемся вниз
                }
                break;
            default :
                break;
        } switch (ch2)  {  //  изменение координаты y при движении ракетки 2
            case 'K':
                if (racket2_y + 2 < axis_y){  //  проверка не выйдет ли ракетка 2 за пределы поля вверху
                    racket2_y++;  //  двигаемся вверх
                }
                break;
            case 'M':
                if (racket2_y > 0){  //  проверка не выйдет ли ракетка 2 за пределы поля внизу
                    racket2_y--;  //  двигаемся вниз
                }
                break;
            default :
                break;
        }
        if (score11 == 21)  {
            printf("WIN: GAMER1");
            break;
        } else if (score22 == 21)  {
            printf("WIN: GAMER2");
            break;
        }
    }
    return 0;
}
