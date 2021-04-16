#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {

    unsigned short gate = atoi(argv[1]);;
    char ip[13] = "192.168.0.53";
    char message2[16] = "urdur";

    int cliente = connect_server(gate, ip);
    send_message(message2, cliente);


    return 0;
}