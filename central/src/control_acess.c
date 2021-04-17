#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/control_acess.h"

void handle_change_s(char *sensor_state){
    int fp;
    char states[16];
    fopen(fp, "../controler.txt", r);
    if(fgetc(fp)=='L'){
        //LIGA ALARME;
    }
    fopen(fp, "../controler.txt", r);

    fgets(states, 16, fp);

    for(int i=0; i<8; i++){
        states[i+1]=sensor_state[i];
    }

    fopen(fp, "../controler.txt", w);

    fprintf(fp, states);
}