#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>

#include "../inc/alarm_controler.h"

int alarm_dl=0;
int sum_s=0;
int sum_s2=0;
int one_on=1;

WINDOW *interface;

void handle_change_s(char *sensor_state){//Lida com as mudanças dos estados dos sensores e se o alarme será acionado ou nao
    pthread_t audio_alarm;

    mvwprintw(interface, 1, 2, "SP1:%c",sensor_state[0]);mvwprintw(interface, 1, 8, "SP2:%c",sensor_state[1]);
    mvwprintw(interface, 1, 14, "SA1:%c",sensor_state[2]);mvwprintw(interface, 1, 32, "SA4:%c",sensor_state[5]);
    mvwprintw(interface, 1, 20, "SA2:%c",sensor_state[3]);mvwprintw(interface, 1, 38, "SA5:%c",sensor_state[6]);
    mvwprintw(interface, 1, 26, "SA3:%c",sensor_state[4]);mvwprintw(interface, 1, 44, "SA6:%c",sensor_state[7]);
    wrefresh(interface);

    if(sum_s!=0){
        for(int i=0;i<8;i++){
            sum_s2+=sensor_state[i];
        }
        if(sum_s<sum_s2){//Caso mais um sensor tenha sido acionado 
            
            if(alarm_dl && one_on){//Caso tenha pelo menos um sensor acionado e o audio nao esteja tocando
                one_on=0;
                pthread_create(&audio_alarm, NULL, play_audio, NULL);
            }
             
        }
        sum_s=sum_s2;
        sum_s2=0;
    }
    else{
        for(int i=0;i<8;i++){
            sum_s+=sensor_state[i];
        }
        if(alarm_dl && one_on && sum_s>544){//Caso tenha pelo menos um sensor acionado e o audio nao esteja tocando
            one_on=0;
            pthread_create(&audio_alarm, NULL, play_audio, NULL);
        }
    }

    
}

void liga_desliga_alarme(){//Liga e deliga o alarme
    if(alarm_dl){
        alarm_dl=0;
    }
    else{
        alarm_dl=1;
    }
}

void set_interface(void *inter){
    interface=(WINDOW *)inter;
}

void *play_audio(){//Da play no audio do alarme(apenas um por vez)
    while(alarm_dl){
        system("aplay audio/subdive.wav > /dev/null 2>&1");
    }
    one_on=1;
    pthread_exit(NULL);
}