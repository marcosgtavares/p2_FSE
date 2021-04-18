/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <signal.h>

//#include "../inc/server.h"
#include "../inc/client.h"

int socket;
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
    //int socket = open_socket(servC);

    //pthread_create(&alarm_watcher, NULL, treat_messages, (void *)&socket); 
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
struct sockaddr_in servidorAddr;
    //cliente = connect_server(servD, "192.168.0.52");

    

    if((cliente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

	// Construir struct sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);

	// Connect
	if(connect(cliente, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
		printf("Erro no connect()\n");



    //usleep(100000);

    //send_message(I, cliente, th);

    while(1){
        sleep(1);
        //send_message(T, cliente, th);
        printf("%s\n",th);
    }


    return 0;
}