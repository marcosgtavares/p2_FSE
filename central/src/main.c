#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {

    unsigned short gate = 10122;
    char ip[] = "192.168.0.52";
    char *message2 = argv[3];

    int cliente = connect_server(gate, ip);
    send_message(message2, cliente);


    return 0;
}