#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 

#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {

    unsigned short servD = 10122;
    unsigned short servC = 10022;

    pthread_t alarm_watcher;
    int socket = open_socket(servC);

    pthread_create(&alarm_watcher, NULL, treat_messages, (void *)&socket); 

    char *th=(char *)malloc(sizeof(char)*11);

    char LL1[]="OA1";
    char LL2[]="OB1";
    char LL3[]="OC1";
    char LL4[]="OD1";
    char LA1[]="OE1";
    char LA2[]="OF1";

    char I[]="I";
    char T[]="T";

    char ip[]= "192.168.0.52";

    int cliente = connect_server(servD, ip);

    usleep(100000);

    send_message(I, cliente, th);

    while(1){
        sleep(1);
        send_message(T, cliente, th);
        printf("%s\n",th);
    }


    return 0;
}