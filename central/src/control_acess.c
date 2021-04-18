#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/control_acess.h"

void init_state(char *in_state){
    printf("head");
    char states[16];
    FILE *fp;


    fp=fopen("../controler", "r");

    fgets(states, 16, fp);
    fclose(fp);
    printf("midle");
    for(int i=0; i<14; i++){
        states[i+1]=in_state[i];
    }

    fp=fopen("../controler", "w");

    fprintf(fp, states);
    printf("tail");
    fclose(fp);
}

void handle_change_s(char *sensor_state){
    FILE *fp;
    char states[16];
    fp=fopen("../controler", "r");
    if(fgetc(fp)=='L'){
        //LIGA ALARME;
    }
    fclose(fp);
    fp=fopen("../controler", "r");

    fgets(states, 16, fp);

    for(int i=0; i<8; i++){
        states[i+1]=sensor_state[i];
    }
    fclose(fp);
    fp=fopen("../controler", "w");

    fprintf(fp, states);
    fclose(fp);
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
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[9]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);

            break;
        case 'B'://L2
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[10]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);
            break;
        case 'C'://L3
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[11]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);
            break;
        case 'D'://L4
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[12]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);
            break;
        case 'E'://A1
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[13]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);
            break;
        case 'F'://A2
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[14]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);
            break;
        case 'G'://Alarm
            fp=fopen("../controler", "r");

            fgets(states, 16, fp);
            fclose(fp);
            states[0]==on_off[3];
            fp=fopen("../controler", "w");
            fprintf(fp, states);
            break;
    }
    fclose(fp);
}