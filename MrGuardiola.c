#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef struct Player{
    int i, j;
} Player;
Player P[9];
int hasBall=3; // Player '3' has the ball initially at kick-off, hasBall=-1 for goal condition
char field[25][41];

void simField(){
    system("cls");
    for(int j=0; j<=40; j++){
        if(j==17 || j==18 || j==19 || j==20 || j==21 || j==22 || j==23) field[0][j]='_';
        else    field[0][j]=' ';
    } // Goal post topbar
    for(int j=0; j<=40; j++){
        if(j==0 || j==1 || j==2 || j==3 || j==4 || j==5 || j==6 || j==7 || j==8 || j==9 || j==10 || j==11 || j==12 || j==13 || j==14 || j==15 || j==16) field[1][j]='_'; // Left Corner
        else if(j==17 || j==23) field[1][j]='|'; // Goal post sidebar
        else if(j==24 || j==25 || j==26 || j==27 || j==28 || j==29 || j==30 || j==31 || j==32 || j==33 || j==34 || j==35 || j==36 || j==37 || j==38 || j==39 || j==40) field[1][j]='_'; // Right Corner
        else    field[1][j]=' ';
    }
    for(int j=0; j<=40; j++){
        if(j==0 || j==40)   field[2][j]='|'; // sideline
        else    field[2][j]=' ';
    }
    for(int i=3; i<=22; i++){
        for(int j=0; j<=40; j++){
            if(j==0 || j==40)   field[i][j]='|'; // sideline
            else    field[i][j]=' ';
        }
    }
    for(int j=0; j<=40; j++){
        if(j==0 || j==40)   field[12][j]='|'; // sideline
        else    field[12][j]='-'; // midline
    }
    for(int j=0; j<=40; j++){
        if(j==0 || j==40)   field[23][j]='|'; // sideline
        else if(j==1 || j==2 || j==3 || j==4 || j==5 || j==6 || j==7 || j==8 || j==9 || j==10 || j==11 || j==12 || j==13 || j==14 || j==15 || j==16) field[23][j]='_'; // Left Corner
        else if(j==24 || j==25 || j==26 || j==27 || j==28 || j==29 || j==30 || j==31 || j==32 || j==33 || j==34 || j==35 || j==36 || j==37 || j==38 || j==39) field[23][j]='_'; // Right Corner
        else    field[23][j]=' ';
    }
    for (int j=0; j<=40; j++){
        if(j==17 || j==23) field[24][j]='|'; // Goal post sidebar
        else if(j==17 || j==18 || j==19 || j==20 || j==21 || j==22 || j==23)    field[24][j]='_'; // Goal post topbar
        else    field[24][j]=' ';
    }

    // Simulating players
    field[P[0].i][P[0].j]='0';
    field[P[1].i][P[1].j]='1';
    field[P[2].i][P[2].j]='2';
    field[P[3].i][P[3].j]='3';
    // field[P[4].i][P[4].j]='4';
    // field[P[5].i][P[5].j]='5';
    // field[P[6].i][P[6].j]='6';
    // field[P[7].i][P[7].j]='7';
    for(int i=4; i<=7; i++) field[P[i].i][P[i].j]=3;
    field[P[8].i][P[8].j]='*';
    for(int i=4; i<8; i++){ // opponent-teammate overlap
        for(int j=0; j<4; j++){
            if(P[i].i==P[j].i && P[i].j==P[j].j){
                if(field[P[j].i][P[j].j+1] != 3){
                    P[j].j++;
                    if(j==0)    field[P[j].i][P[j].j]='0';
                    if(j==1)    field[P[j].i][P[j].j]='1';
                    if(j==2)    field[P[j].i][P[j].j]='2';
                    if(j==3)    field[P[j].i][P[j].j]='3';
                }
                else if(field[P[j].i][P[j].j-1] != 3){
                    P[j].j--;
                    if(j==0)    field[P[j].i][P[j].j]='0';
                    if(j==1)    field[P[j].i][P[j].j]='1';
                    if(j==2)    field[P[j].i][P[j].j]='2';
                    if(j==3)    field[P[j].i][P[j].j]='3';
                }
            }
        }
    }
    // for(int i=4; i<8; i++){ // opponent-opponent overlap (not responding)
    //     for(int j=4; i<8; i++){
    //         if(i!=j && P[i].i==P[j].i && P[i].j==P[j].j){
    //             P[i].j++;
    //             field[P[i].i][P[i].j]=3;
    //             printf("\nfixed!\n");
    //         }
    //     }
    // }
    if(hasBall==-1) field[24][19]='o'; // goal
    else if(hasBall==-2) field[P[8].i][P[8].j+1]='o'; // save
    else field[P[hasBall].i][P[hasBall].j+1]='o';

    // Display simulation
    printf("\n\n");
    for(int i=0; i<=24; i++){
        if(i!=21 && i!=22 && i!=23)  printf("                                                          ");
        for(int j=0; j<=40; j++){
            if(i==21 && j==0)  printf("                                             Pass '0-3'   ");
            if(i==22 && j==0)  printf("                                              Shoot '4'   ");
            if(i==23 && j==0)  printf("                                             Sprint '5'   ");
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
    // for(int i=4; i<8; i++){ // overlap check
    //     printf("%d> %d,%d\n", i, P[i].i, P[i].j);
    // }
}

int distance(int x, int y){
    int d=sqrt(pow(P[x].i-P[y].i,2)+pow(P[x].j-P[y].j,2)); // distance formula
    return d;
}

void tackle(int agg){
    if(P[agg].i<P[hasBall].i)   P[agg].i=P[hasBall].i-1;
    else    P[agg].i=P[hasBall].i+1;
    P[agg].j=P[hasBall].j;
}

bool intercept(int mode){
    if(mode==1){ // Easy
        int idx1, idx2;
        for(int i=7, smallest=29; i>=4; i--){
            int d=distance(i, hasBall);
            if(d<smallest){
                smallest=d;
                idx1=i;
            }
        } // 1st most closet opponent
        
        for(int i=7, smallest=29; i>=4; i--){
            int d=distance(i, hasBall);
            if(i!=idx1 && d<smallest){
                smallest=d;
                idx2=i;
            }
        } // 2nd most closest opponent
        
        P[idx1].i=(P[hasBall].i+P[idx1].i)/2;
        P[idx1].j=(P[hasBall].j+P[idx1].j)/2;
        P[idx2].i=(P[hasBall].i+P[idx2].i)/2;
        P[idx2].j=(P[hasBall].j+P[idx2].j)/2;
        
        // interception condition
        if(distance(idx1, hasBall)<2 || distance(idx2, hasBall)<2){
            simField();
            printf("\n[Status]: Intercepted :(\n");
            return true;
        }
        simField();
        return false;
    }
    else{
        int vul; // vulnerable
        int agg; // aggresive
        int sagg; // semi-aggresive
        
        // deciding aggressive & non-aggresive interceptors
        if(distance(6,hasBall) < distance(7,hasBall)){
            agg=6;  sagg=7;
        }
        else{
            agg=7;  sagg=6;
        }

        // for aggresive
        P[agg].i=(P[hasBall].i+P[agg].i)/2; // mid-point formula
        P[agg].j=(P[hasBall].j+P[agg].j)/2;

        // for semi-aggresive
        for(int i=0, d, smallest=29; i<4; i++){
            if(i!=hasBall){
                d=distance(i, sagg);
                if(distance(i,sagg)<smallest){
                    vul=i;
                    smallest=d;
                }
            }
        }
        P[sagg].i=(P[vul].i+P[sagg].i)/2;
        P[sagg].j=(P[vul].j+P[sagg].j)/2;

        // for defenders
        if(mode==2){ // Medium
            bool mark=true;
            for(int i=4, d; i<=5; i++){
                for(int j=0, closest=29; j<4; j++){
                    d=distance(1,j);
                    if(P[j].i>=14){
                        if(mark==true){
                            if(i==hasBall || d<closest){
                                P[i].i=(P[j].i+P[i].i)/2;
                                P[i].j=(P[j].j+P[i].j)/2;
                                if(i==hasBall){
                                    mark=false;
                                    goto break_loop;
                                }
                                else    closest=d;
                            }
                        }
                        else{
                            if(i!=hasBall && d<closest){
                                P[i].i=(P[j].i+P[i].i)/2;
                                P[i].j=(P[j].j+P[i].j)/2;
                                closest=d;
                            }
                        }
                    }
                }
                break_loop:
            }
            if(distance(4,5)<2) P[5].j++;
        }

        // for defenders
        else if(mode==3){ // Hard
            // deciding aggressive & non-aggresive interceptors
            if(distance(4,hasBall) < distance(5,hasBall) && P[hasBall].i>=14){
                agg=4;  sagg=5;
            }
            else{
                agg=5;  sagg=4;
            }

            // for aggresive
            P[agg].i=(P[hasBall].i+P[agg].i)/2; // mid-point formula
            P[agg].j=(P[hasBall].j+P[agg].j)/2;

            // for semi-aggresive
            for(int i=0, d, smallest=29; i<4; i++){
                if(i!=hasBall && P[i].i>=14){
                    d=distance(i, sagg);
                    if(distance(i,sagg)<smallest){
                        vul=i;
                        smallest=d;
                    }
                }
            }
            P[sagg].i=(P[vul].i+P[sagg].i)/2;
            P[sagg].j=(P[vul].j+P[sagg].j)/2;

        }
        
        // interception condition
        if(distance(agg, hasBall)<2){
            tackle(agg);
            simField();
            printf("\n[Status]: Intercepted :(\n");
            return true;
        }
        else if(distance(sagg, hasBall)<2){
            tackle(sagg);
            simField();
            printf("\n[Status]: Intercepted :(\n");
            return true;
        }
        else if(distance(4, hasBall)<2){
            tackle(4);
            simField();
            printf("\n[Status]: Intercepted :(\n");
            return true;
        }
        else if(distance(5, hasBall)<2){
            tackle(5);
            simField();
            printf("\n[Status]: Intercepted :(\n");
            return true;
        }
        simField();
        return false;
    }
}

int mainPage(){
    system("cls");
    int op;
    printf("\n\n                                                     ||||||\n");
    printf("                                                    ||||||||\n");
    printf("                                                   (||||||||)\n");
    printf("                                                    ||||||||\n");
    printf("                                                    \\______/\n");
    printf("                                                ..--.|    |.--..\n");
    printf("                                            .-``    |      |    ``-.\n");
    printf("                                          .`        `-.__.-`        `.\n");
    printf("                                         :                           :\n");
    printf("                                         :`'-. |\\ | | |) | | |\\ |.-'`:\n");
    printf("                                         :   : | \\| | |  |_| | \\|:  :\n");
    printf("                                         :   :         _         :   :\n");
    printf("                                         :   :        (_)        :   :\n");
    printf("                                         :   :         /         :   :\n");
    printf("                                         :   :                   :   :\n");
    printf("                                         :   :                   :   :\n");
    printf("                                          /// `.               -` \\\\\\\n");
    printf("                                               | ~ ~ ~ ~ ~ ~ ~ \\\n");
    printf("                                               |                ')\n");
    printf("                                               |       | \\    ,` |\n");
    printf("                                               |       |  \\ /`   |\n");
    printf("                                               |_ _ _ _|    |    |\n");
    printf("                                               |     |      |    |\n");
    printf("                                                (    |      |____|__                2080 FUTSAL SIMULATION PROJECT\n");
    printf("                                                |    |       |_______)        ------------------------------------\n");
    printf("                                                |    |          .:::-:::.                               - Sugam K.\n");
    printf("                                                |    |        .'--:   :--'.\n");
    printf("                                                |    |       ;'._ /:::\\ _.';\n");
    printf("                                                |    |       :    :::::    ;                                      \n");
    printf("                                              __|____|        :.''\\:::/''.;                            1. Kick-Off\n");
    printf("                                             (_______|         ';..-.-..;'                                 2. Quit\n");
    printf("\n                                                                                                              - ");
    scanf("%d", &op);
    return op;
}

void loadingPage(float sec, int type){
    system("cls");
	float ms = 1000*sec;
	clock_t start_time; // Storing start time

    if(type==1){
        printf("\n\n\n\n                                              ____________________________________________________________________________\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |             -   \\O                                     ,  .-.___          |\n");
        printf("                                             |           -     /\\                                   O/  /xx\\XXX\\         |\n");
        printf("                                             |          -   __/\\ `                                  /\\  |xx|XXX|         |\n");
        printf("                                             |             `    \\, ()                              ` << |xx|XXX|         |\n");
        printf("                                             |         ^^^^^^^^`^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^      |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |                                                                           |\n");
        printf("                                             |___________________________________________________________________________|\n");
        printf("\n\n\n\n                                                                    ... L . O . A . D . I . N . G ...                       \n");
        start_time = clock();
        while (clock() < start_time + ms);
    }

    if(type==2){
        printf("\n\n                                               ____________________________________________________________________________\n");
        printf("                                              |                                                                           |\n");
        printf("                                              |                                      _ajjaa                               |\n");
        printf("                                              |                                     _Q???4Qf                              |\n");
        printf("                                              |                   _,...,_            ) a/]QQb                             |\n");
        printf("                                              |               .'@/~~~\\@'.              jQQba                              |\n");
        printf("                                              |                //~~\\___/~~\\\\          _, .?QQ#[ _                         |\n");
        printf("                                              |               |@\\__/@@@\\__/@|         ]m _.7   'asLaas_a/                 |\n");
        printf("                                              |               |@/  \\@@@/  \\@|        , ,\\J#L -!4Wba                       |\n"); 
        printf("                                              |               \\__/~~~\\__//       [aL[    \\    \\jmm     jP                 |\n");
        printf("                                              |              '.@\\___/@.'    ,b#''[     \\jmmmmm    _P.                     |\n"); 
        printf("                                              |                 `'''''''        a##'      '4P#mmm#   _ya                  |\n");
        printf("                                              |                              _P          !4####m  ?]aa/                   |\n"); 
        printf("                                              |                               /''        aaJ#U###m#   4QP'                |\n");
        printf("                                              |                               '         aa,/4!44! ''                      |\n");
        printf("                                              |                          jf         _''jQQQQyb7b /                        |\n");
        printf("                                              |                          ''         ''.QQQQ4QQPb  )?                      |\n");
        printf("                                              |                                       QQQ''QQP?''  jg/ f                  |\n");
        printf("                                              |                                     _yQP'']QQb aa                         |\n");
        printf("                                              |                                   a#W?''..QQQQ?)?   ?'                    |\n");
        printf("                                              |                                  '##'  _jQQP'                             |\n");
        printf("                                              |                                 .j?  [ jQQ'                               |\n");
        printf("                                              |                            aJ  jmaaX#L???                                 |\n");
        printf("                                              |                            ? am'                                          |\n");
        printf("                                              |                          _QjQQQ/                                          |\n");
        printf("                                              |                          )QQQP?                                           |\n");
        printf("                                              |                           4QQQ/                                           |\n");
        printf("                                              |___________________________________________________________________________|\n");
        printf("\n                                                                     ... L . O . A . D . I . N . G ...                       \n");
        start_time = clock();
        while (clock() < start_time + ms);
    }

    if(type==3){
        printf("\n\n\n\t\t\t  ______________________________________________________________________________________________________________\n");
        printf("\t\t\t  |                                                                                                            |\n");
        printf("\t\t\t  |                                                                                        ,/)                 |\n");
        printf("\t\t\t  |                                                                                        |_|                 |\n");
        printf("\t\t\t  |        _        _        _        _        _        _        _        _        _       ].[       ,~        |\n");
        printf("\t\t\t  |       |.|      |.|      |.|      |.|      |.|      |.|      |.|      |.|      |.|    /~`-'~\\     |_|       |\n");
        printf("\t\t\t  |       ]^[      ]^[      ]^[      ]^[      ]^[      ]^[      ]^[      ]^[      ]^[   (<| 1 |>)    ]0[       |\n");
        printf("\t\t\t  |     /~/^\\~\\  /~`-'~\\  /~`-'~\\  /~`-'~\\  /~`-'~\\  /~`-'~\\  /~`-'~\\  /~`-'~\\  /~`-'~\\  \\|___|/   ,-`^'~\\     |\n");
        printf("\t\t\t  |    {<| $ |>}{<| 8 |>}{<| 6 |>}{<| , |>}{<| 3 |>}{<|   |>}{<| 7 |>}{<| , |>}{<| 8 |>} {/   \\}  {<| 9 |>}    |\n");
        printf("\t\t\t  |     \\|___|/  \\|___|/  \\|___|/  \\|___|/  \\|___|/  \\|___|/  \\|___|/  \\|___|/  \\|___|/  /__/__\\   \\|,__|/     |\n");
        printf("\t\t\t  |    /\\    \\    /   \\    /   \\    /   \\    /   \\    /   \\    /   \\    /   \\    /   \\   | / \\ |   {/ \\  /     |\n");
        printf("\t\t\t  |    |/>/|__\\  /__|__\\  /__|__\\  /__|__\\  /__|__\\  /__|__\\  /__|__\\  /__|__\\  /__|__\\  |/   \\|   /__|\\/\\     |\n");
        printf("\t\t\t  |    |)   \\ |  | / \\ |  | / \\ |  | / \\ |  | / \\ |  | / \\ |  | / \\ |  | / \\ |  | / \\ |  {}   {}   | / \\ |     |\n");
        printf("\t\t\t  |   (_|    \\)  (/   \\)  (/   \\)  (/   \\)  (/   \\)  (/   \\)  (/   \\)  (/   \\)  (/   \\)  |)   (|   (/   \\)     |\n");
        printf("\t\t\t  |   / \\    (|  |)   (|  |)   (|  |)   (|  |)   (|  |)   (|  |)   (|  |)   (|  |)   (|  ||   ||  _|)   (|_    |\n");
        printf("\t\t\t  |.,.\\_/,..,|,)(.|,.,|,)(,|,.,|.)(.|,.,|,)(,|,.,|.)(.|,.,|,)(,|,.,|.)(.|,.,|,)(,|,.,|.)(.|.,.|,)(.,|.,.|,.),.,|\n");
        printf("\t\t\t  --------------------------------------------------------------------------------------------------------------\n");
        printf("\n\n\n\n                                                                    ... L . O . A . D . I . N . G ...                       \n");
        start_time = clock();
        while (clock() < start_time + ms);
    }

    if(type==4){
    printf("\n\n\n\n\t\t\t\t\t\t______________________________________________________________________\n");
    printf("\t\t\t\t\t\t|                                                                    |\n");
    printf("\t\t\t\t\t\t|            ______________________________________________          |\n");
    printf("\t\t\t\t\t\t|           | \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ |.         |\n");
    printf("\t\t\t\t\t\t|           |_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_||         |\n");
    printf("\t\t\t\t\t\t|          |\\ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ /\\         |\n");
    printf("\t\t\t\t\t\t|          |\\|/ \\_/ \\_/ \\_/ \\_/ \\|||/_/ \\_/ \\_/ \\_/ \\_/ \\|/ '.       |\n");
    printf("\t\t\t\t\t\t|         .'/|\\_/ \\_/ \\_/ \\_/ \\q O O p\\_/ \\_/ \\_/ \\_/ \\_/|\\_|        |\n");
    printf("\t\t\t\t\t\t|         | \\/ \\_/ \\_/ \\_/ \\_/ | ) |_/ \\_/ \\_/ \\_/ \\_/ \\|/ \\         |\n");
    printf("\t\t\t\t\t\t|         |_/ |_/ \\_/ \\_/ \\_/ __\\_O_/___/ \\_/ \\_/ \\_/ \\_//\\_'.       |\n");
    printf("\t\t\t\t\t\t|        |/ \\_| \\_/ \\_,--._,-\"         `-._,--. \\_/ \\_/ |_/ \\|       |\n");
    printf("\t\t\t\t\t\t|        |\\_/ |_/ \\_/ \\__/_,-\"|       |`-._\\__/_/ \\_/ \\_| \\_/\\       |\n");
    printf("\t\t\t\t\t\t|       |_/ \\_\\ \\_/ \\_/ \\_/ \\_|       | \\_/ \\_/ \\_/ \\_/ /_/ \'.       |\n");
    printf("\t\t\t\t\t\t|       | \\_/ \\|/ \\_/ \\_/ \\_//   /\\   \\_/ \\_/ \\_/ \\_/ \\|/ \\_/ |      |\n");
    printf("\t\t\t\t\t\t|      .'_/ \\_/|\\_/ \\_/ \\_/ /   /  \\   \\\\_\\_/ \\_/ \\_/|\\_/ \\_\\        |\n");
    printf("\t\t\t\t\t\t|      |/ \\_/__\\___________/   /____\\   \\_______________\\ \\_/ '.     |\n");
    printf("\t\t\t\t\t\t|      |\\_,-'           __/___/      \\___\\__             `-.__/|     |\n");
    printf("\t\t\t\t\t\t|      //              /_____/        \\____\\                 `\\      |\n");
    printf("\t\t\t\t\t\t|____________________________________________________________________|\n");
        printf("\n\n\n\n                                                                    ... L . O . A . D . I . N . G ...                       \n");
        start_time = clock();
        while (clock() < start_time + ms);
    }
}

bool obstacle(){
    P[hasBall].i+=3;
    if(P[hasBall].i<23) return false;
    return true;
}

void move(int assist){
    for(int i=0; i<4; i++){
        if(i==assist || i==hasBall) continue; // assist provider or player holding ball are not moved forward
        else{
            if(P[i].i+1<23 && (P[i].i+1<23 || field[P[i].i+1][P[i].j]!=3 || field[P[i].i+1][P[i].j]!='0' || field[P[i].i+1][P[i].j]!='1' || field[P[i].i+1][P[i].j]!='2' || field[P[i].i+1][P[i].j]!='3'))   P[i].i++; // if there's no obstacle on moving the player forward, move the player
        }
    }
}

void displayTactics(int report[]){
    printf("\n3");
    for(int i=0; i<40; i++){
        if(report[i]!=-1 && report[i]!=-2)  printf(" --> %d", report[i]);
        else    break;
    }
}

void kick_off(int mode){
    // Player initial loaction
    P[0].i=6; P[0].j=10; // LB
    P[1].i=6; P[1].j=30; // RB
    P[2].i=9; P[2].j=20; // LW
    P[3].i=12; P[3].j=20; // RW
    
    P[4].i=19; P[4].j=10; // LB
    P[5].i=19; P[5].j=30; // RB
    P[6].i=15; P[6].j=15; // LW
    P[7].i=15; P[7].j=25; // RW
    P[8].i=23; P[8].j=20; // GK
    simField();

    int assist, ps, i=0, report[40];
    while(1){
        assist=hasBall;
        scanf("%d", &ps);
        if(ps==0 || ps==1 || ps==2 || ps==3){ // Pass
            hasBall=ps;
            report[i]=hasBall;
            move(assist);
            if(intercept(mode)==true){
                printf("\n!!GAME OVER!!");
                i++;
                report[i]=-2;
                displayTactics(report);
                return;
            }
            i++;
        }
        else if(ps==4){ // Shoot
            if(distance(8, hasBall)==3){
                hasBall=-1;
                simField();
                printf("[Status]: GOAL!\n\n!!You Won!!");
                report[i]=-1;
                displayTactics(report);
                return;
            }
            else{
                hasBall=-2;
                simField();
                printf("[Status]: SAVED! :(\n\n!!GAME OVER!!");
                report[i]=-2;
                displayTactics(report);
                return;
            }
        }
        else if(ps==5){ // Sprint
            if(obstacle()==true){
                simField();
                printf("\n[Status]: Out :(\n\n!!GAME OVER!!");
                report[i]=-2;
                displayTactics(report);
                return;
            }
            move(-1);
            if(intercept(mode)==true){
                printf("\n!!GAME OVER!!");
                report[i]=-2;
                displayTactics(report);
                return;
            }
        }
    }
}

int main(){
    int op, n=0, menu, mode;
    loop:
    menu=mainPage();
    if(menu==1){
        here:
        loadingPage(1.5, 4);
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n                                                                          1. Easy\n");
        printf("                                                                         2. Medium\n");
        printf("                                                                          3. Hard\n\n");
        printf("                                                                             -");
        scanf("%d", &mode);
        loadingPage(2.2, 1);
        kick_off(mode);
        printf("\n\nRematch(1)/ GO Back(2)/ Quit(3)? ");
        scanf("%d", &op);
        if(op==1){
            loadingPage(2.2, 2);
            hasBall=3;
            goto here;
        }
        else if(op==2){
            loadingPage(2.2, 3);
            goto loop;
        }
    }
    return 0;
}