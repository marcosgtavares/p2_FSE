#include <stdlib.h>
#include <stdio.h>
#include "../inc/server.h"
#include "../inc/client.h"

int main(int argc, char *argv[]) {

    unsigned short gate = 5000;
    char ip[12] = "192.168.0.8";
    char message2[16] = "urdur";

    int cliente = connect_server(gate, ip);
    send_message(message2, cliente);


    return 0;
}