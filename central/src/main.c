#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {

    unsigned short gate = atoi(argv[1]);;
    char ip[10] = "127.0.1.1";
    char message2[16] = "urdur";

    int cliente = connect_server(gate, ip);
    send_message(message2, cliente);


    return 0;
}