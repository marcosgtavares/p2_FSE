#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h> 
#include <pthread.h> 

#include "../inc/server.h"
//#include "../inc/client.h"


int servsocket;

/*void monitor_sensor_state(){
    sensor_state_atualize(initial);
    sensor_state_atualize(final);
    while(!strcmp(initial, final)){
        sensor_state_atualize(final);
    }
    
    //send final
}*/

void end_exec(int sigint){
    close(servsocket);
    exit(0);
}
void ur(int sigint){
    
}

int main(int argc, char *argv[]) {
    unsigned short serv = 10122;
    signal(SIGINT, end_exec);
    signal(SIGTSTP, end_exec);
    signal(SIGUSR1, ur);

    pthread_t m_tr;

    servsocket=open_socket(serv);

    pthread_create(&m_tr, NULL, treat_messages, (void *)&servsocket ); //Cria a thread que trata os comandos do servidor central

    //pthread_create(&s_change, NULL, wsensor_change, NULL);//Cria a thread que trata as mudanças nos sensores NAO FUNCIONA MAIS agora chamado dentro da funcao treat messages

    while(1){
        usleep(1000000);
    }


    

    return 0;
}