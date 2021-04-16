#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "../inc/server.h"
#include "../inc/client.h"

int servsocket;

void end_exec(int sigint){
    close(servsocket);
    exit(0);
}

int main(int argc, char *argv[]) {
    unsigned short serv = atoi(argv[1]);;
    signal(SIGINT, end_exec);
    signal(SIGTSTP, end_exec);

    servsocket=open_socket(serv);
    treat_messages(servsocket);

    return 0;
}