#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h> 
#include "../inc/gpio.h"

int only_once=0;

void sensor_state_atualize(char *current){

    if(digitalRead(6)==1){//PSAlA
        current[0]='L';
    }
    else{
        current[0]='D';
    }
    if(digitalRead(25)==1){//PCOZINHA
        current[1]='L';
    }
    else{
        current[1]='D';
    }
    if(digitalRead(21)==1){//DCOZINHA
        current[2]='L';
    }
    else{
        current[2]='D';
    }
    if(digitalRead(22)==1){//JCOZINHA
        current[3]='L';
    }
    else{
        current[3]='D';
    }
    if(digitalRead(26)==1){//DSALA
        current[4]='L';
    }
    else{
        current[4]='D';
    }
    if(digitalRead(27)==1){//JSALA
        current[5]='L';
    }
    else{
        current[5]='D';
    }
    if(digitalRead(28)==1){//JQ1
        current[6]='L';
    }
    else{
        current[6]='D';
    }
    if(digitalRead(29)==1){//JQ2
        current[7]='L';
    }
    else{
        current[7]='D';
    }
    current[8]='\0';
}

void on_off_gadgets(char gadget, char on_off){

    if(only_once==0){
        pinMode (0, OUTPUT);
        pinMode (1, OUTPUT);
        pinMode (2, OUTPUT);
        pinMode (3, OUTPUT);
        pinMode (23, OUTPUT);
        pinMode (24, OUTPUT); 

        only_once=1;
    }
    switch(gadget){
        case 'A'://L1
            digitalWrite(0,on_off-48);
            break;
        case 'B'://L2
            digitalWrite(1,on_off-48);
            break;
        case 'C'://L3
            digitalWrite(2,on_off-48);
            break;
        case 'D'://L4
            digitalWrite(3,on_off-48);
            break;
        case 'E'://A1
            digitalWrite(23,on_off-48);
            break;
        case 'F'://A2
            digitalWrite(24,on_off-48);
            break;
    }
}

void initial_state(char *currentI, char *currentO){
    pinMode (6, INPUT);
    pinMode (25, INPUT);
    pinMode (21, INPUT);
    pinMode (22, INPUT);
    pinMode (26, INPUT);
    pinMode (27, INPUT); 
    pinMode (28, INPUT); 
    pinMode (29, INPUT); 

	sensor_state_atualize(currentO);

    pinMode (0, INPUT);
    pinMode (1, INPUT);
    pinMode (2, INPUT);
    pinMode (3, INPUT);
    pinMode (23, INPUT);
    pinMode (24, INPUT); 

	if(digitalRead(0)==1){//L1
        currentI[0]='L';
    }
	else{
		currentI[0]='D';
	}
	if(digitalRead(1)==1){//L2
        currentI[1]='L';
    }
	else{
		currentI[1]='D';
	}
	if(digitalRead(2)==1){//L3
        currentI[2]='L';
    }
	else{
		currentI[2]='D';
	}
	if(digitalRead(3)==1){//L4
        currentI[3]='L';
    }
	else{
		currentI[3]='D';
	}
	if(digitalRead(23)==1){//A1
        currentI[4]='L';
    }
	else{
		currentI[4]='D';
	}
	if(digitalRead(24)==1){//A2
        currentI[5]='L';
    }
	else{
		currentI[5]='D';
	}
	
}
