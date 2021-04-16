#include <stdlib.h>
#include <stdio.h>
#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {
    unsigned short serv = 5001;

    int servsocket=open_socket(serv);

    treat_messages(servsocket);

    return 0;
}