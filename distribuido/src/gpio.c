#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h> 
#include "../inc/gpio.h"

#define L_1_OUT 0
#define L_2_OUT 1
#define L_3_OUT 2
#define L_4_OUT 3
#define A_1_OUT 23
#define A_2_OUT 24
#define S_P_1_IN 6
#define S_P_2_IN 25
#define S_A_1_IN 21
#define S_A_2_IN 22
#define S_A_3_IN 26
#define S_A_4_IN 27
#define S_A_5_IN 28
#define S_A_6_IN 29

int only_once=0;
int only_once2=1;
int switchonoff=0;

void sensor_state_atualize(char *current){//Atualiza a string com os estados dos sensores no formato "DDDDDDDD" "LLLLLLLL" D significa desligado e L ligado
    if(only_once==0){ 
        wiringPiSetup();
        

        only_once=1;
    }
    
    if(only_once2){//Define o pinmode apenas uma vez
        only_once2=0;
        pinMode (6, INPUT);
        pinMode (25, INPUT);
        pinMode (21, INPUT);
        pinMode (22, INPUT);
        pinMode (26, INPUT);
        pinMode (27, INPUT); 
        pinMode (28, INPUT); 
        pinMode (29, INPUT); 
    }

    if(digitalRead(S_P_1_IN)==1){//PSAlA
        current[0]='L';
    }
    else{
        current[0]='D';
    }
    if(digitalRead(S_P_2_IN)==1){//PCOZINHA
        current[1]='L';
    }
    else{
        current[1]='D';
    }
    if(digitalRead(S_A_1_IN)==1){//DCOZINHA
        current[2]='L';
    }
    else{
        current[2]='D';
    }
    if(digitalRead(S_A_2_IN)==1){//JCOZINHA
        current[3]='L';
    }
    else{
        current[3]='D';
    }
    if(digitalRead(S_A_3_IN)==1){//DSALA
        current[4]='L';
    }
    else{
        current[4]='D';
    }
    if(digitalRead(S_A_4_IN)==1){//JSALA
        current[5]='L';
    }
    else{
        current[5]='D';
    }
    if(digitalRead(S_A_5_IN)==1){//JQ1
        current[6]='L';
    }
    else{
        current[6]='D';
    }
    if(digitalRead(S_A_6_IN)==1){//JQ2
        current[7]='L';
    }
    else{
        current[7]='D';
    }
    current[8]='\0';
}

void on_off_gadgets(char gadget, char on_off){//Liga ou desliga os gadgets de acordo com o input, "OA1" significa ligar lampada 1;
    if(only_once==0){
        wiringPiSetup();
        only_once=1;
    }

    if(switchonoff){//Caso tenha lido o estado anteriormente
        pinMode (L_1_OUT, OUTPUT);
        pinMode (L_2_OUT, OUTPUT);
        pinMode (L_3_OUT, OUTPUT);
        pinMode (L_4_OUT, OUTPUT);
        pinMode (A_1_OUT, OUTPUT);
        pinMode (A_2_OUT, OUTPUT); 
        switchonoff=0;
    }
    

    switch(gadget){
        case 'A'://L1
            digitalWrite(L_1_OUT,on_off-48);
            break;
        case 'B'://L2
            digitalWrite(L_2_OUT,on_off-48);
            break;
        case 'C'://L3
            digitalWrite(L_3_OUT,on_off-48);
            break;
        case 'D'://L4
            digitalWrite(L_4_OUT,on_off-48);
            break;
        case 'E'://A1
            digitalWrite(A_1_OUT,on_off-48);
            break;
        case 'F'://A2
            digitalWrite(A_2_OUT,on_off-48);
            break;
    }
}

void initial_state(char *currentO, char *currentI){//Captura os estados dos sensores(currentO) e dos gadgets(currentI)
    if(only_once==0){
        wiringPiSetup();
        only_once=1;
    }

	sensor_state_atualize(currentO);

    if(!switchonoff){
        pinMode (L_1_OUT, OUTPUT);
        pinMode (L_2_OUT, OUTPUT);
        pinMode (L_3_OUT, OUTPUT);
        pinMode (L_4_OUT, OUTPUT);
        pinMode (A_1_OUT, OUTPUT);
        pinMode (A_2_OUT, OUTPUT);
        switchonoff=1;
    }

    

	if(digitalRead(L_1_OUT)==1){//L1
        currentI[0]='L';
    }
	else{
		currentI[0]='D';
	}
	if(digitalRead(L_2_OUT)==1){//L2
        currentI[1]='L';
    }
	else{
		currentI[1]='D';
	}
	if(digitalRead(L_3_OUT)==1){//L3
        currentI[2]='L';
    }
	else{
		currentI[2]='D';
	}
	if(digitalRead(L_4_OUT)==1){//L4
        currentI[3]='L';
    }
	else{
		currentI[3]='D';
	}
	if(digitalRead(A_1_OUT)==1){//A1
        currentI[4]='L';
    }
	else{
		currentI[4]='D';
	}
	if(digitalRead(A_2_OUT)==1){//A2
        currentI[5]='L';
    }
	else{
		currentI[5]='D';
	}

    currentI[6]='\0';
	
}

