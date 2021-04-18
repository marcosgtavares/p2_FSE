#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
//#include <signal.h>

//#include "../inc/server.h"
#include "../inc/client.h"

int sockets;
char *th;

/*void end_exec(int sigint){
    close(socket);
    free(th);
    exit(0);
}*/

int main(int argc, char *argv[]) {
    //signal(SIGINT, end_exec);
    //signal(SIGTSTP, end_exec);

    unsigned short servD = 10122;
    unsigned short servC = 10022;

    pthread_t alarm_watcher;
    //int sockets = open_socket(servC);

    //pthread_create(&alarm_watcher, NULL, treat_messages, (void *)&sockets); 
    printf("ASDA");

    //th=(char *)malloc(sizeof(char)*16);

    printf("ASDAasd");

/*
    char LL1[]="OA1";
    char LL2[]="OB1";
    char LL3[]="OC1";
    char LL4[]="OD1";
    char LA1[]="OE1";
    char LA2[]="OF1";

    char I[]="I";
    char T[]="T";  */

    int cliente;

    cliente = connect_server(servD, "192.168.0.52");

    

    //usleep(100000);

    //send_message(I, cliente, th);

    while(1){
        sleep(1);
        //send_message(T, cliente, th);
        printf("%s\n",th);
    }


    return 0;
}