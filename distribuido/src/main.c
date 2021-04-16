#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {
    unsigned short serv = atoi(argv[1]);;

    int servsocket=open_socket(serv);
    close(servsocket);

    treat_messages(servsocket);

    return 0;
}