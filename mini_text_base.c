#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RAWS 64
#define COLS 208
#define HEALTH 0
#define DAMAGE 0
#define ARMOUR 0
#define LEVEL 0

struct pixel{
    int x;
    int y;
    char data;
};

struct pixel tile[RAWS*COLS];
int introductions = 1;

int selection[3];


//void vertical_align(int *starting_y){
//        starting_y = RAWS/2;
//    }
//    void horizontal_align(int *starting_x){
//        starting_x = COLS/2;
//    }
//
//    void center(int *starting_x, int *starting_y){
//        vertical_align(&starting_y);
//        horizontal_align(&starting_x);
//    }
//
//maybe i could find a wy to use them...

void arrow_left(int x, int y){
    if (x > 1){
        tile[x+y*COLS-3].data = '-';
        tile[x+y*COLS-2].data = '-';
        tile[x+y*COLS-1].data = '>';
    }
}
void arrow_right(int x, int y){
    if (x > 1){
        tile[x+y*COLS].data = '<';
        tile[x+y*COLS+1].data = '-';
        tile[x+y*COLS+2].data = '-';
    }
}

void top_shush(int sx,int ex, int sy){
    int i;
    if (sy > 0){
        for (i=sx;i<ex;i++){
            tile[i+(sy-1)*COLS].data = '/';
        }
    }
}

void bot_sush(int sx,int ex, int sy){
    int i;
    if (sy < RAWS){
        for (i=sx;i<ex;i++){
            tile[i+(sy+1)*COLS].data = '/';
        }
    }
}

void selected(int x, int y){
    int i;
    char selected[8];
    selected[0] = 's';
    selected[1] = 'e';
    selected[2] = 'l';
    selected[3] = 'e';
    selected[4] = 'c';
    selected[5] = 't';
    selected[6] = 'e';
    selected[7] = 'd';
    for (i=0;i<8;i++){
        tile[x+COLS*y+i].data = selected[i];
    }
}


void sset_pixel(int starting_x, int starting_y ,char write[COLS-starting_x],int left_arrow,bool set){
    int i, ending_x;
    ending_x = starting_x + strlen(write);
    for (i = 0; i<strlen(write); i++){
        tile[starting_x+COLS*starting_y+i].data = write[i];
    }
    if (left_arrow == 1){
        arrow_left(starting_x,starting_y);
        starting_x -= 3;
    }
    if (set == true){
        arrow_right(ending_x,starting_y);
        ending_x += 3;
        selected(ending_x,starting_y);
    }
}
void set_pixel(int starting_x, int starting_y ,char write[COLS-starting_x],int left_arrow,int right_arrow,int sush_top,int sush_bot){
    int i, ending_x;
    ending_x = starting_x + strlen(write);
    for (i = 0; i<strlen(write); i++){
        tile[starting_x+COLS*starting_y+i].data = write[i];
    }
    if (left_arrow == 1){
        arrow_left(starting_x,starting_y);
        starting_x -= 3;
    }
    if (right_arrow == 1){
        arrow_right(ending_x,starting_y);
        ending_x += 3;
    }
    if (sush_top == 1){
        top_shush(starting_x, ending_x, starting_y);
    }
    if (sush_bot == 1){
        bot_sush(starting_x, ending_x, starting_y);
    }
}

void write_whole_sush(int x,int y,char string[COLS]){
    set_pixel(x,y,string,1,1,1,1);
}

void init_pixel(int quit){
    int x_indicator,y_indicator;
    for (y_indicator = 0; y_indicator < RAWS; y_indicator++){
        for(x_indicator = 0; x_indicator < COLS; x_indicator++){
            tile[y_indicator*COLS+x_indicator].x = x_indicator;
            tile[y_indicator*COLS+x_indicator].y = y_indicator;
            tile[y_indicator*COLS+x_indicator].data = ' ';
        }
    }
    if (quit == 0){
        write_whole_sush((COLS/2)-17,1,"Welcome To The Real World Warrior");
        write_whole_sush(COLS-12,RAWS-2,"q:   Quit");
        write_whole_sush(COLS-12,RAWS-4,"r: Return");
    } 
    if (introductions == 1){
        write_whole_sush(COLS-34,RAWS-6,"Press i to close introductions.");
    } else {
        write_whole_sush(COLS-33,RAWS-6,"Press i to open introductions.");
    }
}


void draw(){
    int i;
    printf("\n");
    for(i=0;i<RAWS*COLS;i++){
        printf("%c",tile[i].data);
        if (tile[i].y<tile[i+1].y){
            printf("\n");
        }
    }
    printf("\n");
}

void quit(){
    int i;
    init_pixel(1);
    for (i=0;i<RAWS/2;i++){
        write_whole_sush((COLS/2)-4,2*i,"GOOD BYE");
    }
    system("clear");
    draw();
} 
int weaponsmith(int running){
    char selection;
    int selected[4],i;
    selected[0] = 1;
    selected[1] = 0;
    selected[2] = 0;
    selected[3] = 0;
    while (running == 1){
        init_pixel(0);
        sset_pixel(4,4," City A ",1,selected[0]);
        sset_pixel(4,7," City B ",1,selected[1]);
        sset_pixel(4,10," City C ",1,selected[2]);
        sset_pixel(4,13," City D ",1,selected[3]);
        if (introductions == 1){
            write_whole_sush(40,4,"In this city you could find cheap wapons, you can acces them until level 0.");
            write_whole_sush(40,7,"In this city you could find quite well wapons, you can acces them until level 15.");
            write_whole_sush(40,10,"In this city you could find well wapons, you can acces them until level 30.");
            write_whole_sush(40,13,"In this city you could find excellent wapons, you can acces them until level 45.");
        }
        system("clear");
        draw();
        scanf("%c",&selection);
        if (selection == 'w' || selection == 'W'){
            for (i=0;i<4;i++){
                if (selected[i] == 1){
                    if (i != 0){
                        selected[i] = 0;
                        selected[i-1] = 1;
                    }
                }
            }
        }else if (selection == 's' || selection == 'S'){
            for (i=0;i<4;i++){
                if (selected[i] == 1){
                    selected[i] = 0;
                    selected[3] = 1;
                }
            }
        }else if (selection == 'q' || selection == 'Q'){
            quit();
            return 0;
        }else if (selection == 'i' || selection == 'I'){
            if (introductions == 1){
                introductions = 0;
            } else {
                introductions = 1;
            }
        }else if (selection == 'r' || selection == 'R'){
            return 1;
        }
    }
}

int armoursmith(int running){
    char selection;
    int selected[4],i;
    selected[0] = 1;
    selected[1] = 0;
    selected[2] = 0;
    selected[3] = 0;
    while (running == 1){
        init_pixel(0);
        sset_pixel(4,4," City A ",1,selected[0]);
        sset_pixel(4,7," City B ",1,selected[1]);
        sset_pixel(4,10," City C ",1,selected[2]);
        sset_pixel(4,13," City D ",1,selected[3]);
        if (introductions == 1){
            write_whole_sush(40,4,"In this city you could find cheap wapons, you can acces them until level 0.");
            write_whole_sush(40,7,"In this city you could find quite well wapons, you can acces them until level 15.");
            write_whole_sush(40,10,"In this city you could find well wapons, you can acces them until level 30.");
            write_whole_sush(40,13,"In this city you could find excellent wapons, you can acces them until level 45.");
        }
        system("clear");
        draw();
        scanf("%c",&selection);
        if (selection == 'w' || selection == 'W'){
            for (i=0;i<4;i++){
                if (selected[i] == 1){
                    if (i != 0){
                        selected[i] = 0;
                        selected[i-1] = 1;
                    }
                }
            }
        }else if (selection == 's' || selection == 'S'){
            for (i=0;i<4;i++){
                if (selected[i] == 1){
                    selected[i] = 0;
                    selected[3] = 1;
                }
            }
        }else if (selection == 'q' || selection == 'Q'){
            quit();
            return 0;
        }else if (selection == 'i' || selection == 'I'){
            if (introductions == 1){
                introductions = 0;
            } else {
                introductions = 1;
            }
        }else if (selection == 'r' || selection == 'R'){
            return 1;
        }
    }
}

int marketplace(int running){
    char selection;
    int selected[3], i;
    selected[0] = 1;
    selected[1] = 0;
    selected[2] = 0;
    while (running == 1){
        init_pixel(0);
        sset_pixel(4,4," Weaponsmith ",1,selected[0]);
        sset_pixel(4,7," Armoursmith ",1,selected[1]);
        sset_pixel(4,10," Magic Seller ",1,selected[2]);
        if (introductions == 1){
            write_whole_sush(4,RAWS-2,"w/W = select above, s/S = select bottom, press space to enter selected menu.");
            write_whole_sush(40,4,"#You could find whole weapons from all ower the world.#");
            write_whole_sush(40,7,"#You could find whole aromurs all around the world.#");
            write_whole_sush(40,10,"#You could find whole magicians all around the worl.#s");
        }
        system("clear");
        draw();
        scanf("%c",&selection);
        if (selection == 'w' || selection == 'W'){
            for (i=0;i<3;i++){
                if (selected[i] == 1){
                    if (i != 0){
                        selected[i] = 0;
                        selected[i-1]= 1;
                    }
                }
            }
        } else if (selection == 's' || selection == 'S'){
            for (i=0;i<3;i++){
                if (selected[i] == 1){
                    if (i != 2){
                        selected[i] = 0;
                        selected[i+1]= 1;
                    }
                }
            }
        }else if(selection == ' '){
            for (i=0;i<3;i++){
                if (selected[i] == 1){
                    if (i==0){
                        if (weaponsmith(running)==0){
                            return 0;
                        }
                    } if (i==1){
                        if (armoursmith(running)==0){
                            return 0;
                        }
                    } if (i==2){

                    }
                }
            }
        }else if (selection == 'q' || selection == 'Q'){
            quit();
            return 0;
        } else if(selection == 'i' || selection == 'I'){
            if (introductions == 1){
                introductions = 0;
            } else{
                introductions = 1;
            }
        } else if (selection == 'r' || selection == 'R'){
            return 1;
        } 
        system("clear");
    }
}

int monster_hub(int running){
    char selection;
    int i,selected[3];
    selected[0]=1;
    selected[1]=0;
    selected[2]=0;
    while (running == 1){
        init_pixel(0);
        sset_pixel(5,4," Scarab ",1,selected[0]);
        sset_pixel(5,7," Zombie ",1,selected[1]);
        sset_pixel(5,10," Skeleton ",1,selected[2]);
        system("clear");
        if (introductions == 1){
            write_whole_sush(40,4,"Easiest entity you could find in the world");
            write_whole_sush(40,7,"Moderate entity you could find in the world");
            write_whole_sush(40,10,"Hardest entity you could find in the world");
        }
        draw();
        scanf("%c",&selection);

        if (selection == 'w' || selection == 'W'){
            for (i=0;i<3;i++){
                if(selected[i] == 1){
                    if (i == 1){
                        selected[1] = 0;
                        selected[0] = 1;
                    }else if (i == 2){
                        selected[2] = 0;
                        selected[1] = 1;
                    }
                }
            } 
        }
        if (selection == 's' || selection == 'S'){
            for (i=0;i<3;i++){
                if(selected[i] == 1){
                    if (i == 0){
                        selected[0] = 0;
                        selected[2] = 1;
                    }
                }
            }
        }else if (selection == 'q'||selection == 'Q'){
            quit();
            return 0;
        } else if (selection == 'i' || selection == 'I'){
            if (introductions == 1){
                introductions = 0;
            }else{
                introductions = 1;
            }
        } else if (selection == 'r'|| selection == 'R'){
            return 1;
        }
    }
}

int stats(int running){
    char selection;
    while (running == 1){
        scanf("%c",&selection);
        if (selection == 'r' || selection == 'R'){
            return 1;
        }else if (selection == 'i' || selection == 'I'){
            if (introductions == 1){
                introductions = 0;
            } else {
                introductions = 1;
            }
        }else if (selection == 'q' || selection == 'Q'){
            return 0;
        }
    }
}
int menu(int running){
    char selected;
    int i;
    bool selection[3];
    selection[0] = 1;
    selection[1] = 0;
    selection[2] = 0;
    init_pixel(0);
    while(running == 1){
        init_pixel(0);
        sset_pixel(3,4," Marketplace",1,selection[0]);
        sset_pixel(3,7," Monsters Hub",1,selection[1]);
        sset_pixel(3,10," Stats",1,selection[2]);
        if (introductions == 1){
            write_whole_sush(4,RAWS-2,"w/W = select above, s/S = select bottom, press space to enter selected menu.");
            write_whole_sush(40,4,"You could see main market selections and buy something from there");
            write_whole_sush(40,7,"You could fid monsters all around the world, you will earn exp and gold if you can defeat them.");
            write_whole_sush(40,10,"You could see your holy stats and you can set your upgraded stat.");
        }
        system("clear");
        draw();
        scanf("%c",&selected);
        if (selected == 'w' || selected == 'W'){
            for (i=0;i<3;i++){
                if (selection[i] == 1){
                    if (i == 1 || i == 2){
                        selection[i] = 0;
                        selection[i-1] = 1;
                    } 
                }
            }
        } else if (selected == 's' || selected == 'S'){
            for (i = 0;i<3;i++){
                if (selection[i] == 1){
                    if (i == 0 || i == 1){
                        selection[i] = 0;
                        selection[i+1] = 1;
                    } 
                }
            }
        } else if(selected == 'q' || selected == 'Q'){
            quit();
            return 0;
        } else if(selected == ' '){
            for (i = 0; i<3; i++){
                if (selection[i]==1){
                    if (i == 0){
                        if(marketplace(running)==0){
                            return 0;
                        }
                    } else if(i==1){
                        if (monster_hub(running)== 0){
                            return 0;
                        }
                    } else if(i==2){
                        if (stats(running) == 0){
                            return 0;
                        }
                    }
                }
            }
        } else if (selected == 'i' || selected == 'I'){
            if (introductions == 1){
                introductions = 0;
            } else {
                introductions = 1;
            }
        }
    }
}
int main(){
    int running;
    running = 1;
    init_pixel(0);
    while (running == 1){
        if (menu(running)==0){
            running = 0;
        }
    }
    return 0;
}