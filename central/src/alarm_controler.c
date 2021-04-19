#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include "../inc/alarm_controler.h"

int alarm_dl=0;
int sum_s=0;
int sum_s2=0;
int one_on=1;

void handle_change_s(char *sensor_state){
    pthread_t audio_alarm;

    if(sum_s!=0){
        for(int i=0;i<8;i++){
            sum_s2+=sensor_state[i];
        }
        if(sum_s<sum_s2){
            
            if(alarm_dl && one_on){
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
        if(alarm_dl && one_on){
            one_on=0;
            pthread_create(&audio_alarm, NULL, play_audio, NULL);
            printf("liga alarme");       
        }
    }

    
}

void liga_desliga_alarme(){
    if(alarm_dl){
        alarm_dl=0;
    }
    else{
        alarm_dl=1;
    }
}

void *play_audio(){
    while(alarm_dl){
        system("omxplayer audio/subdive.wav");
    }
    one_on=1;
    pthread_exit(NULL);
}