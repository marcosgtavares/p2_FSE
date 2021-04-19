#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include "../inc/alarm_controler.h"

int alarm_dl=0;
int sum_s=0;
int sum_s2=0;
int one_on=1;

void handle_change_s(char *sensor_state){//Lida com as mudanças dos estados dos sensores e se o alarme será acionado ou nao
    pthread_t audio_alarm;

    if(sum_s!=0){
        for(int i=0;i<8;i++){
            sum_s2+=sensor_state[i];
        }
        if(sum_s<sum_s2){//Caso mais um sensor tenha sido acionado 
            
            if(alarm_dl && one_on){//Caso tenha pelo menos um sensor acionado e o audio nao esteja tocando
                one_on=0;
                pthread_create(&audio_alarm, NULL, play_audio, NULL);
                printf("liga alarme");    
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
            printf("liga alarme");       
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

void *play_audio(){//Da play no audio do alarme(apenas um por vez)
    while(alarm_dl){
        system("aplay audio/subdive.wav");
    }
    one_on=1;
    pthread_exit(NULL);
}