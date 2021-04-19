#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include <signal.h>

#include "../inc/server.h"
#include "../inc/client.h"
#include "../inc/alarm_controler.h"


int sockets;
char *th;
char *ret;

struct sckt_sstate{
    int sockets;
    char sstates[9];
};

void end_exec(int sigint){
    close(sockets);
    free(th);
    free(ret);
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, end_exec);
    signal(SIGTSTP, end_exec);

    unsigned short servD = 10122;
    unsigned short servC = 10022;

    pthread_t alarm_watcher;
    int sockets = open_socket(servC);

    struct sckt_sstate *alarm_params = (struct sckt_sstate *)malloc(sizeof(struct sckt_sstate));

    alarm_params->sockets=sockets;

    ret=(char *)malloc(sizeof(char)*16);
    th=(char *)malloc(sizeof(char)*16);
    sprintf(th, "%s", servD);

    pthread_create(&alarm_watcher, NULL, treat_messages, (void *)alarm_params); 

    pthread_create(&temp_humidity, NULL, temp_hum, (void *)th);

    

    

    char LL1[]="OA1";
    char LL2[]="OB1";
    char LL3[]="OC1";
    char LL4[]="OD1";
    char LA1[]="OE1";
    char LA2[]="OF1";

    char I[]="I";
    char T[]="T";  

    int cliente;

    cliente = connect_server(servD, "192.168.0.52");

    char ordem[4];

    usleep(10000);
    liga_desliga_alarme();

    send_message(I, cliente, ret);

    while(1){
        scanf("%s", ordem);
        cliente = connect_server(servD, "192.168.0.52");
        send_message(ordem, cliente, ret);
        printf("%s\n", ret);
    }


    return 0;
}