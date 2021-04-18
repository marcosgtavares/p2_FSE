#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/alarm_controler.h"

int alarm_dl=0;
int sum_s=0;

void handle_change_s(char *sensor_state){
    
    if(sum_s!=0){
        for(int i=0;i<8;i++){
        sum_s2+=sensor_state[i];
        }
        if(sum_s<sum_s2){
            sum_s=sum_s2;
            sum_s2=0;
            if(alarm_dl){
                printf("liga alarme");    
            }
             
        }
    }
    else{
        for(int i=0;i<8;i++){
            sum_s+=sensor_state[i];
        }
        if(alarm_dl){
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