#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/control_acess.h"

void init_state(char *in_state){
    char states[16];
    FILE *fp;


    fopen(fp, "../controler.txt", 'r');

    fgets(states, 16, fp);

    for(int i=0; i<14; i++){
        states[i+1]=in_state[i];
    }

    fopen(fp, "../controler.txt", 'w');

    fprintf(fp, states);
}

void handle_change_s(char *sensor_state){
    FILE *fp;

    char states[16];
    fopen(fp, "../controler.txt", 'r');
    if(fgetc(fp)=="L"){
        //LIGA ALARME;
    }
    fopen(fp, "../controler.txt", 'r');

    fgets(states, 16, fp);

    for(int i=0; i<8; i++){
        states[i+1]=sensor_state[i];
    }

    fopen(fp, "../controler.txt", 'w');

    fprintf(fp, states);
}

void handle_on_off(char *on_off){
    char states[16];
    FILE *fp;


    if(on_off[3]=='1'){
        on_off[3]='L';
    }
    else{
        on_off[3]='D';
    }

    switch(on_off[2]){
        case 'A'://L1
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[9]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);

            break;
        case 'B'://L2
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[10]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);
            break;
        case 'C'://L3
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[11]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);
            break;
        case 'D'://L4
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[12]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);
            break;
        case 'E'://A1
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[13]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);
            break;
        case 'F'://A2
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[14]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);
            break;
        case 'G'://Alarm
            fopen(fp, "../controler.txt", 'r');

            fgets(states, 16, fp);

            states[0]==on_off[3];
            fopen(fp, "../controler.txt", 'w');
            fprintf(fp, states);
            break;
    }
}