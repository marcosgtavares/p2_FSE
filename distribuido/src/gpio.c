#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h> 
#include "../inc/gpio.h"

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
    switch(gadget){
        case 'A'://L1
            digitalWrite(0,atoi(on_off));
            break;
        case 'B'://L2
            digitalWrite(1,atoi(on_off));
            break;
        case 'C'://L3
            digitalWrite(2,atoi(on_off));
            break;
        case 'D'://L4
            digitalWrite(3,atoi(on_off));
            break;
        case 'E'://A1
            digitalWrite(23,atoi(on_off));
            break;
        case 'F'://A2
            digitalWrite(24,atoi(on_off));
            break;
    }
}

void initial_state(char *current){
	sensor_state_atualize(initial);
	if(digitalRead(0)==1){//L1
        current[0]='L';
    }
	else{
		current[0]='D';
	}
	if(digitalRead(1)==1){//L2
        current[1]='L';
    }
	else{
		current[1]='D';
	}
	if(digitalRead(2)==1){//L3
        current[2]='L';
    }
	else{
		current[2]='D';
	}
	if(digitalRead(3)==1){//L4
        current[3]='L';
    }
	else{
		current[3]='D';
	}
	if(digitalRead(23)==1){//A1
        current[4]='L';
    }
	else{
		current[4]='D';
	}
	if(digitalRead(24)==1){//A2
        current[5]='L';
    }
	else{
		current[5]='D';
	}
	
}
