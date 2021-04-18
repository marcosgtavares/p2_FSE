#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h> 
#include <pthread.h> 

#include "../inc/server.h"
#include "../inc/client.h"


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

int main(int argc, char *argv[]) {
    unsigned short serv = 10122;
    signal(SIGINT, end_exec);
    signal(SIGTSTP, end_exec);

    pthread_t m_tr,s_change;

    servsocket=open_socket(serv);

    //treat_messages(servsocket); // thread it
    pthread_create(&m_tr, NULL, treat_messages, (void *)&servsocket ); 

    //pthread_create(&s_change, NULL, wsensor_change, NULL);

    while(1){

    }


    

    return 0;
}