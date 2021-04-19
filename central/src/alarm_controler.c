#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "../inc/alarm_controler.h"
#include "../inc/csv_gen.h"

int alarm_dl=0;
int one_on=1;
time_t rawtime;
struct tm * timeinfo;
char last_state[8];

WINDOW *interface;

void handle_change_s(char *sensor_state){//Lida com as mudanças dos estados dos sensores e se o alarme será acionado ou nao
    pthread_t audio_alarm;
    
    for(int i=0;i<8;i++){
        last_state[i]=sensor_state[i];
    }  

    time ( &rawtime );//Grava tempo atual
    timeinfo = localtime ( &rawtime );
    create_csv(asctime (timeinfo),sensor_state);//Escreve no csv

    mvwprintw(interface, 1, 2, "SP1:%c",sensor_state[0]);mvwprintw(interface, 1, 8, "SP2:%c",sensor_state[1]);
    mvwprintw(interface, 1, 14, "SA1:%c",sensor_state[2]);mvwprintw(interface, 1, 32, "SA4:%c",sensor_state[5]);
    mvwprintw(interface, 1, 20, "SA2:%c",sensor_state[3]);mvwprintw(interface, 1, 38, "SA5:%c",sensor_state[6]);
    mvwprintw(interface, 1, 26, "SA3:%c",sensor_state[4]);mvwprintw(interface, 1, 44, "SA6:%c",sensor_state[7]);
    wrefresh(interface);

    printf("inside");

    if(alarm_dl && one_on && strstr(sensor_state, "L")!=NULL ){//Caso tenha algum sensor acionado apos a mudança de estado, o alarme esta ligado, acione o alarme
        one_on=0;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        create_csv(asctime (timeinfo),"Alarme acionado");
        mvwprintw(interface, 8, 18, "ALARME ACIONADO    ");
        wrefresh(interface);
        pthread_create(&audio_alarm, NULL, play_audio, NULL);

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
    mvwprintw(interface, 8, 18, "ALARME DESATIVADO");
    time ( &rawtime );//Grava tempo atual
    timeinfo = localtime ( &rawtime );
    create_csv(asctime (timeinfo),"Alarme desativado");//Escreve no csv
    wrefresh(interface);
    one_on=1;
    pthread_exit(NULL);
}